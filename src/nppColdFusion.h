//this file is part of nppColdFusion
//Copyright (C)2011 Ben Bluemel ( ben1982@gmail.com )
//
//This program is free software; you can redistribute it and/or
//modify it under the terms of the GNU General Public License
//as published by the Free Software Foundation; either
//version 2 of the License, or (at your option) any later version.
//
//This program is distributed in the hope that it will be useful,
//but WITHOUT ANY WARRANTY; without even the implied warranty of
//MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//GNU General Public License for more details.
//
//You should have received a copy of the GNU General Public License
//along with this program; if not, write to the Free Software
//Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.


#ifndef NPP_COLDFUSION_H
#define NPP_COLDFUSION_H

//#include "nppLexCommon.h"
#ifdef UNICODE
#define generic_strncpy_s wcsncpy_s
#else
#define generic_strncpy_s strncpy_s
#endif

#include "nppCFShared.h"
#include <boost\algorithm\string\case_conv.hpp>
namespace nppColdFusion
{
	typedef struct {
		int value;
		int shift;
		int mask;
	} storagebit;

	static inline int getstoredbitvalue(int bittree, storagebit sb)
	{
		return (bittree >> sb.shift) & sb.mask;
	}
	static inline int changestoredbitvalue(int bittree, storagebit sb)
	{

		return (bittree & ~(sb.mask << sb.shift) | (sb.value & sb.mask) << sb.shift);
	}
	class nppCFShared;
	class Status;

	template <typename T>
	class PublicSparseState : public SparseState<typename T> {
	public:
		PublicSparseState() {}
		~PublicSparseState() {}
		const stateVector getStates() { return states; }
		void setPositionFirst(int positionFirst_) { positionFirst = positionFirst_; }
	};


	class CFBaseType {
	public:
		unsigned int pos;
		bool scripted;
		std::string name;
		std::string nameLowered;
		CFBaseType() {}
		~CFBaseType() {}
		inline bool operator<(const CFBaseType& other) const {
			return pos < other.pos;
		}
		inline bool operator==(const CFBaseType& other) const {
			return (pos == other.pos) && (name == other.name);
		}
		inline bool operator!=(const CFBaseType& other) const {
			return (pos != other.pos) || (name != other.name);
		}

		void setName(const char* sName) {
			name.assign(sName);
			nameLowered.assign(sName);
			boost::to_lower(nameLowered);

		}

	};

	class CFUserFunction : public CFBaseType {
	private:
		std::string sortedLocals;
		std::string sortedArguments;
	public:
		bool dirtyLocals;
		bool dirtyArguments;
		PublicSparseState<CFBaseType> arguments;
		PublicSparseState<CFBaseType> locals;
		PublicSparseState<unsigned int> bracketDepths;
		typedef PublicSparseState<CFBaseType>::stateVector stateVector;
		CFUserFunction();
		CFUserFunction(unsigned int ipos);

		inline bool operator<(const CFUserFunction& other) const {
			return pos < other.pos;
		}
		inline bool operator==(const CFUserFunction& other) const {
			return (pos == other.pos) && (name == other.name) && (locals.size() == other.locals.size() && !other.dirtyLocals) && (arguments.size() == other.arguments.size() && !other.dirtyArguments);
		}
		inline bool operator!=(const CFUserFunction& other) const {
			return (pos != other.pos) || (name != other.name) || (locals.size() != other.locals.size() || other.dirtyLocals) || (arguments.size() != other.arguments.size() || other.dirtyArguments);
		}

		const std::string getSortedList(PublicSparseState<CFBaseType>& list, char* append = "\0") {
			std::vector<std::string> tmp;
			std::vector<std::string>::iterator it;
			std::string sortedList;
			stateVector states = list.getStates();
			for (stateVector::iterator thisstate = states.begin(); thisstate != states.end(); ++thisstate) {
				tmp.push_back((*thisstate).value.name);
			}
			std::sort(tmp.begin(), tmp.end());
			for (it = tmp.begin(); it != tmp.end(); ++it) {
				sortedList.append(*it);
				if (append[0] != '\0') {
					sortedList.append(append);
				}
				sortedList.append(" ");
			}
			return sortedList;
		}

		std::string getLocalsSorted(char* append = "\0") {
			if (dirtyLocals || append[0] != '\0') {
				sortedLocals.assign(getSortedList(locals, append));
			}
			return sortedLocals;
		}

		std::string getArgumentssSorted(char* append = "\0") {
			if (dirtyArguments || append[0] != '\0') {
				sortedArguments.assign(getSortedList(arguments, append));
			}
			return sortedArguments;
		}

		bool hasLocalVar(char* var) {

			stateVector states = locals.getStates();
			for (stateVector::iterator thisstate = states.begin(); thisstate != states.end(); ++thisstate) {
				if ((*thisstate).value.nameLowered == var) {
					return true;
				}
			}
			return false;
		};
		~CFUserFunction();
	};

	class nppCFShared;
	class Status;

	class LexerColdFusion : public LexerBase
	{
	private:
		nppCFShared* cfs;
		bool isScriptCFC;
		bool hasDeterminedType;
		bool inScriptComment;
		bool inScriptLineComment;
		int sharedid;
		unsigned int componentPos;
		unsigned int invalidPos;
		unsigned int currentDoc;
	public:
		SparseState<unsigned int> cfCommentDepths;
		SparseState<unsigned int> cfOutputDepths;
		SparseState<std::string> coldFusionTags;
		SparseState<std::string> htmlTags;
		SparseState<bool> scriptBlocks;
		SparseState<bool> cfQueryBlocks;
		SparseState<bool> jsBlocks;
		SparseState<bool> cssBlocks;
		SparseState<bool> inCFSets;

		LexerColdFusion();
		~LexerColdFusion();

		SparseState<CFUserFunction> cfUserFunctions;

		void SCI_METHOD Lex(unsigned int startPos, int length, int initStyle, IDocument* pAccess);
		void SCI_METHOD Fold(unsigned int startPos, int length, int initStyle, IDocument* pAccess);
		Status Colourise_Doc(unsigned int startPos, int length, int initStyle, LexAccessor& styler, bool dostyling = true);
		int SCI_METHOD WordListSet(int n, const char* wl);
		static ILexer* LexerFactory() {
			try {
				return new LexerColdFusion();
			}
			catch (...) {
				// Should not throw into caller as may be compiled with different compiler or options
				return 0;
			}
		}
	};

	LRESULT nppMessageProc(UINT Message, WPARAM wParam, LPARAM lParam);
};

#endif

