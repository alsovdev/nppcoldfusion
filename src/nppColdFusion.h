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

#ifdef UNICODE
#define generic_strncpy_s wcsncpy_s
#else
#define generic_strncpy_s strncpy_s
#endif

//#pragma once
//#include "SparseState.h" ///
#include "nppCFShared.h"
#include <algorithm>
#include <cctype>
#ifdef UNICODE
#define STRINGIFY(x) L##x
#else
#define STRINGIFY(x) x
#endif

namespace nppColdFusionNS
{
	constexpr const TCHAR* LEXER_NAME = STRINGIFY("ColdFusion");
	constexpr const TCHAR* PLUGIN_NAME = STRINGIFY("nppColdFusion");
	constexpr const TCHAR* PLUGIN_VERSION = STRINGIFY("0.9.1");
	constexpr const TCHAR* PLUGIN_STATUS_TEXT = STRINGIFY("ColdFusion Lexer for Notepad++");

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

	inline static const char* LexerName();



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
				std::transform(nameLowered.begin(), nameLowered.end(), nameLowered.begin(),
					[](unsigned char c){ return std::tolower(c); });
			}

	};
	/*
	template <typename T>
	class PublicSparseState : public Lexilla::SparseState<T> {
	public:
		PublicSparseState() { }
		~PublicSparseState() { }
		const Lexilla::SparseState<T>stateVector getStates() { return this->states; }
		void setPositionFirst(int positionFirst_) { this->positionFirst = positionFirst_; }
	};*/
	template <typename T>
	class PublicSparseState : public Lexilla::SparseState<T> {
	public:
		PublicSparseState() {}
		~PublicSparseState() {}
		const Lexilla::SparseState<T>::stateVector getStates() { return this->states; }
		void setPositionFirst(int positionFirst_) { this->positionFirst = positionFirst_; }
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
		typedef PublicSparseState<CFBaseType>::stateVector stateVector; ///
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

		const std::string getSortedList(PublicSparseState<CFBaseType>& list, const char* append = "\0") {
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

		std::string getLocalsSorted(const char* append = "\0") {
			if (dirtyLocals || append[0] != '\0') {
				sortedLocals.assign(getSortedList(locals, append));
			}
			return sortedLocals;
		}

		std::string getArgumentssSorted(const char* append = "\0") {
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

	class LexerColdFusion final : public Lexilla::LexerBase
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
		Lexilla::SparseState<unsigned int> cfCommentDepths;
		Lexilla::SparseState<unsigned int> cfOutputDepths;
		Lexilla::SparseState<std::string> coldFusionTags;
		Lexilla::SparseState<std::string> htmlTags;
		Lexilla::SparseState<bool> scriptBlocks;
		Lexilla::SparseState<bool> cfQueryBlocks;
		Lexilla::SparseState<bool> jsBlocks;
		Lexilla::SparseState<bool> cssBlocks;
		Lexilla::SparseState<bool> inCFSets;

		LexerColdFusion();
		~LexerColdFusion();
		Lexilla::SparseState<CFUserFunction> cfUserFunctions;

		void SCI_METHOD Lex(Sci_PositionU startPos, Sci_Position length, int initStyle, Scintilla::IDocument* pAccess);
		void SCI_METHOD Fold(Sci_PositionU startPos, Sci_Position length, int initStyle, Scintilla::IDocument* pAccess);
		Status Colourise_Doc(Sci_PositionU startPos, Sci_Position length, int initStyle, Lexilla::LexAccessor& styler, bool dostyling = true);
		Sci_Position SCI_METHOD WordListSet(int n, const char* wl);
		static ILexer5* LexerFactory() {
			try {
				return new LexerColdFusion();
			}
			catch (...) {
				// Should not throw into caller as may be compiled with different compiler or options
				return 0;
			}
		}
		static ILexer5* SCI_METHOD CreateLexer(const char* name);
		const char* SCI_METHOD PropertyGet(const char* key);
		/// ILexer5 methods from LexerBase
		//const char* SCI_METHOD GetName();
		//int SCI_METHOD GetIdentifier();
		//const char* SCI_METHOD PropertyGet(const char* key);
		int SCI_METHOD Version() const override;
	};

	LRESULT nppMessageProc(UINT Message, WPARAM wParam, LPARAM lParam);
};

#endif

