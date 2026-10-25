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

#include "nppCFShared.h"



namespace nppColdFusionNS
{
nppCFShared* nppCFShared::pinstance( 0 );


	


		DBNamespace::DBNamespace(sqlite3* thedb) {
			this->database = thedb;
			this->keywordsset = false;
			this->tagsset = false;
		}
		char* DBNamespace::listAllTags() {
			return listAllTags(false);
		}
		char* DBNamespace::listAllTags(bool forautoc) {
			char* copyvalue = NULL;

			int length = 0;
			if (this->ns > 0) {
				int sqlitePrepare;
				sqlite3_stmt* stmt;
				const char* sql = "\
					SELECT '%s' || GROUP_CONCAT(b.name, '%s') || '%s' FROM ( \
                    SELECT t.name FROM namespaces n \
                    INNER JOIN namespacetags nt ON n.id = nt.namespaceid \
                    INNER JOIN tags t ON nt.tagid = t.id \
                    WHERE n.id = ? ORDER BY t.name \
                ) AS b";

				if (forautoc) {
					sql = sqlite3_mprintf(sql, "", "?1 ", "?1");
				}
				else {
					sql = sqlite3_mprintf(sql, " ", " ", " ");
				}
				sqlitePrepare = sqlite3_prepare_v2(this->database, sql, -1, &stmt, NULL);
				sqlite3_bind_int(stmt, 1, this->ns);

				if (SQLITE_ROW == sqlite3_step(stmt)) {
					const char* values = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
					length = sqlite3_column_bytes(stmt, 0);
					copyvalue = new char[length + 9];
					strcpy_s(copyvalue, length + 1, values);
					copyvalue[length] = '\0';

				}
				if (length == 0) {
					::MessageBoxA(0, "DBNamespace::ListAllTags length is 0", "nppColdFusion Error", MB_OK);
					return const_cast<char*>("");
				}
				sqlite3_finalize(stmt);
			}

			return copyvalue;

		}
		char* DBNamespace::listAllKeywords() {
			return listAllKeywords(false, false);
		}
		char* DBNamespace::listAllKeywords(bool lowered) {
			return listAllKeywords(lowered, false);
		}
		char* DBNamespace::listAllKeywords(bool lowered, bool forautoc) {
			char* copyvalue = NULL;
			int length = 0;
			if (this->ns > 0) {
				int sqlitePrepare;
				sqlite3_stmt* stmt;
				const char* sql = "\
						SELECT '%s' || GROUP_CONCAT(b.name, '%s') || '%s', ' ' || LOWER(GROUP_CONCAT(b.name, ' ')) FROM ( \
                   SELECT k.name FROM namespaces AS n \
						INNER JOIN namespacekeywordsets AS nks ON n.id = nks.namespaceid \
						INNER JOIN keywordsets AS ks ON nks.keywordsetid = ks.id \
						INNER JOIN keywordsetkeywords AS ksk ON ks.id = ksk.keywordsetid \
						INNER JOIN keywords AS k ON ksk.keywordid = k.id \
						WHERE n.id = ? ORDER BY k.name \
                ) AS b";

				if (forautoc) {
					sql = sqlite3_mprintf(sql, "", "?1 ", "?1");
				}
				else {
					sql = sqlite3_mprintf(sql, " ", " ", " ");
				}

				sqlitePrepare = sqlite3_prepare_v2(this->database, sql, -1, &stmt, NULL);

				sqlite3_bind_int(stmt, 1, this->ns);
				// Run the query with sqlite3_step
				if (SQLITE_ROW == sqlite3_step(stmt)) {
					const char* values;
					if (lowered) {
						values = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1)); // The 0 here means we only take the first column returned. And it is the snippet as there is only one column
						length = sqlite3_column_bytes(stmt, 1);
					}
					else {
						values = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0)); // The 0 here means we only take the first column returned. And it is the snippet as there is only one column
						length = sqlite3_column_bytes(stmt, 0);
					}

					/*strncpy(&copyvalue, values, length);
					*(&copyvalue + length) = '=';
					*(&copyvalue + length +1) = '\0';*/
					copyvalue = new char[length + 5];
					/*if (forautoc) {
						strcpy_s( copyvalue,length, values );
					} else {
						strcpy_s( copyvalue,length +1, values );
						}*/
					strcpy_s(copyvalue, length + 1, values);
					copyvalue[length] = '\0';
					//copyvalue[length +1] = '\0';


				}
				sqlite3_finalize(stmt);
			}
			return copyvalue;
		}

		bool DBNamespace::isKeyword(char* keyword) {
			auto length = strnlen_s(keyword, 100);
			if (strstr(keyword, ".") != NULL || strstr(keyword, "'") != NULL) {
				return false;
			}

			if (this->ns > 0 && length > 0) {

				char* copyvalue = new char[length + 4];

				strcpy_s(copyvalue, length + 2, " ");
				strcat_s(copyvalue, length + 2, keyword);
				copyvalue[length + 1] = ' ';
				copyvalue[length + 2] = '\0';
				if (!this->keywordsset) {
					this->allkeywords = this->listAllKeywords(true);
					this->keywordsset = true;
				}
				return (strstr(this->allkeywords, copyvalue) != NULL);
			}
			return false;
		}
		//virtual bool isCustomTag(char* tag_) {
		//	return false;
		//}

		bool DBNamespace::isTag(char* tag) {
			auto length = strnlen_s(tag, 100);

			if (length == 0 || strstr(tag, ".") != NULL || strstr(tag, "'") != NULL) {
				return false;
			}

			if (this->ns > 0) {
				if (this->isCustomTag(tag)) {
					return true;
				}

				if (!this->tagsset) {
					this->alltags = this->listAllTags();
					this->tagsset = true;
				}
				return (strstr(this->alltags, tag) != NULL);
			}
			return false;
		}

		char* DBNamespace::listTagAttributes(char* tag) {
			return listTagAttributes(tag, false, false, false);
		}
		char* DBNamespace::listTagAttributes(char* tag, bool forautoc) {
			return listTagAttributes(tag, false, false, forautoc);
		}
		char* DBNamespace::listTagAttributes(char* tag, bool onlyrequired, bool hasFingerText) {
			return listTagAttributes(tag, onlyrequired, hasFingerText, false);
		}
		char* DBNamespace::listTagAttributes(char* tag, bool onlyrequired, bool hasFingerText, bool forautoc) {
			char* copyvalue = NULL;
			int length = 0;
			if (this->ns > 0) {
				int sqlitePrepare;
				sqlite3_stmt* stmt;
				char* sql = const_cast<char*>("\
                SELECT GROUP_CONCAT(b.name, '%s%s ') || '%s%s' FROM ( \
                    SELECT a.name FROM namespaces n \
                    INNER JOIN namespacetags nt ON n.id = nt.namespaceid \
                    INNER JOIN tags t ON nt.tagid = t.id \
                    INNER JOIN tagattributes ta ON t.id = ta.tagid \
                    INNER JOIN attributes a ON ta.attributeid = a.id \
					WHERE n.id = ? AND t.name = ? AND (ta.required = 1 OR ta.required = ?) ORDER BY a.name \
                ) AS b");
				const char* extra = "?1";

				if (!forautoc) {
					extra = "";
				}

				if (onlyrequired) {
					if (hasFingerText) {
						sql = sqlite3_mprintf(sql, "=\"$[![]!]\"", extra, "=\"$[![]!]\"", extra);
					}
					else {
						sql = sqlite3_mprintf(sql, "=\"\"", extra, "=\"\"", extra);
					}
				}
				else {
					sql = sqlite3_mprintf(sql, "=", extra, "=", extra);
				}
				sqlitePrepare = sqlite3_prepare_v2(this->database, sql, -1, &stmt, NULL);
				sqlite3_bind_int(stmt, 1, this->ns);
				sqlite3_bind_text(stmt, 2, tag, -1, SQLITE_STATIC);
				sqlite3_bind_int(stmt, 3, onlyrequired);
				// Run the query with sqlite3_step
				if (SQLITE_ROW == sqlite3_step(stmt)) {
					const char* values = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0)); // The 0 here means we only take the first column returned. And it is the snippet as there is only one column
					length = sqlite3_column_bytes(stmt, 0);
					/*strncpy(&copyvalue, values, length);
					*(&copyvalue + length) = '=';
					*(&copyvalue + length +1) = '\0';*/
					if (length > 0) {
						copyvalue = new char[length + 20];
						strcpy_s(copyvalue, length + 1, values);
						/*if ( onlyrequired ) {
							if ( hasFingerText ) {
								strcat_s( copyvalue, length + 20, "=\"$[![]!]\"$[![]!]" );
							} else {
								strcat_s( copyvalue, length + 20, "=\"\"" );
							}


						} else {
							copyvalue[length] = '=';
							copyvalue[length +1] = '\0';
						}*/
					}
					sqlite3_finalize(stmt);
					return copyvalue;
				}
			}
			return NULL;
		}

		bool DBNamespace::tagHasAttribute(char* tag, char* attribute) {
			bool result = false;
			int sqlitePrepare;
			bool cached = false;
			if (strstr(tag, ".") != NULL || strstr(tag, "'") != NULL) {
				return false;
			}

			if (this->ns > 0) {
				if (this->isCustomTag(tag)) {
					return true;
				}
				sqlite3_stmt* stmt;
				char* sql = sqlite3_mprintf("SELECT value FROM memcache.cache WHERE name = '%d|tha|%s|%s'", this->ns, tag, attribute);
				sqlitePrepare = sqlite3_prepare_v2(this->database, sql, -1, &stmt, NULL);
				int res = sqlite3_step(stmt);
				sqlite3_free(sql);
				if (SQLITE_ROW == res) {
					const char* values = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
					result = 0 == strcmp(values, "1");
					cached = true;
				}
				res = sqlite3_finalize(stmt);
				if (cached == false) {
					sqlite3_stmt* stmt;
					char* sql = const_cast<char*>("\
							SELECT t.name as tagname, a.name as attributename \
							FROM namespaces AS n \
							INNER JOIN namespacetags AS nt ON n.id = nt.namespaceid \
							INNER JOIN tags AS t ON nt.tagid = t.id \
							INNER JOIN tagattributes AS ta on t.[id] = ta.tagid \
							INNER JOIN attributes AS a ON ta.[attributeid] = a.id \
							WHERE n.id = ? AND t.name = ? AND a.name = ? ORDER BY t.name, a.name");
					sqlitePrepare = sqlite3_prepare_v2(this->database, sql, -1, &stmt, NULL);
					sqlite3_bind_int(stmt, 1, this->ns);
					sqlite3_bind_text(stmt, 2, tag, -1, SQLITE_STATIC);
					sqlite3_bind_text(stmt, 3, attribute, -1, SQLITE_STATIC);

					// Run the query with sqlite3_step

					if (SQLITE_ROW == sqlite3_step(stmt)) {
						result = true;
					}

					sqlite3_finalize(stmt);

					sql = sqlite3_mprintf("INSERT INTO memcache.cache (name, value) VALUES ('%d|tha|%s|%s',%d)", this->ns, tag, attribute, result);

					sqlitePrepare = sqlite3_prepare_v2(this->database, sql, -1, &stmt, NULL);
					res = sqlite3_step(stmt);
					if (SQLITE_ROW == res) {

					}
					sqlite3_finalize(stmt);
					return tagHasAttribute(tag, attribute);
				}
			}
			return result;
		}
		char* DBNamespace::listAttributeValues(char* tag, char* attribute) {
			char* copyvalue = NULL;
			if (this->ns > 0) {
				int sqlitePrepare;
				sqlite3_stmt* stmt;
				char* sql = const_cast<char*>("\
						SELECT GROUP_CONCAT(o.value, '\" ') FROM namespaces AS n \
						INNER JOIN namespacetags AS nt ON n.id = nt.namespaceid \
						INNER JOIN tags AS t ON nt.tagid = t.id \
						INNER JOIN tagattributes AS ta ON t.id = ta.tagid \
						INNER JOIN attributes AS a ON ta.attributeid = a.id \
						INNER JOIN types AS ty ON ty.id = a.typeid \
						INNER JOIN typeoptions AS tyo ON ty.id = tyo.typeid \
						INNER JOIN options AS o ON tyo.optionid = o.id \
						WHERE n.id = ? AND t.name = ? AND a.name = ?  ORDER BY o.value");

				sqlitePrepare = sqlite3_prepare_v2(this->database, sql, -1, &stmt, NULL);
				sqlite3_bind_int(stmt, 1, this->ns);
				sqlite3_bind_text(stmt, 2, tag, -1, SQLITE_STATIC);
				sqlite3_bind_text(stmt, 3, attribute, -1, SQLITE_STATIC);
				// Run the query with sqlite3_step
				if (SQLITE_ROW == sqlite3_step(stmt)) {
					const char* values = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0)); // The 0 here means we only take the first column returned. And it is the snippet as there is only one column
					int length = sqlite3_column_bytes(stmt, 0);
					if (length > 0) {
						copyvalue = new char[length + 5];
						//strcpy_s( copyvalue, length +1, values );
						strcpy_s(copyvalue, static_cast<rsize_t>(length) + 1, values); // *** not sure
						copyvalue[length] = '"';
						copyvalue[length + 1] = '\0';
					}
					sqlite3_finalize(stmt);
					return copyvalue;
				}
			}
			return 0;
		}


		nppCFShared* nppCFShared::Instance() { //static
			if (pinstance == 0) {
				pinstance = new nppCFShared();
			}
			return pinstance;
		}


		unsigned int nppCFShared::registerLexer(LexerColdFusion* thisLexer) {
			lexers.push_back(thisLexer);
			return lexers.size() - 1;
		}

		bool nppCFShared::linkDocToLexer(unsigned int const& lexID, unsigned int const& docID) {
			doclinks.insert(docLinks::value_type(docID, lexID));
			//lexlinks.insert(lexLinks::value_type(lexID, docID));
			return true;
		}

		LexerColdFusion* nppCFShared::getLexerForDoc(unsigned int const& docID) {
			docLinks::iterator iter = doclinks.find(docID);
			if (iter != doclinks.end()) {
				return lexers[iter->second];
			}
			return NULL;
		}

		bool nppCFShared::unregisterLexer(unsigned int const& lexID, unsigned int const& docID) {
			lexers.push_back(NULL);
			std::swap(lexers[lexID], lexers[lexers.size() - 1]);
			doclinks.erase(docID);
			lexers.erase(lexers.begin() + lexers.size() - 1);
			while (lexers.size() > 0 && lexers[lexers.size() - 1] == NULL) {
				lexers.erase(lexers.begin() + lexers.size() - 1);
			}
			return true;
		}

		void nppCFShared::setDB(char* dbfile) {
			integrateWithFingerText = true;
			completeCFsqltype = false;
			alwaysCompleteReqAttributes = false;
			nppReady = false;
			int rc;
			rc = sqlite3_open(dbfile, &this->database);
			if (rc) {
				sqlite3_close(this->database);
			}

			char* userdb;
			userdb = new char[strnlen_s(dbfile, 512) + 6];
			strcpy_s(userdb, strnlen_s(dbfile, 512) + 1, dbfile);
			strcpy_s(userdb + (strnlen_s(dbfile, 512) - 3), 9, "user.db3");
			int sqlitePrepare;
			sqlite3_stmt* stmt;

			char* sql = sqlite3_mprintf("ATTACH DATABASE '%s' AS usercfg;", userdb);
			sqlitePrepare = sqlite3_prepare_v2(this->database, sql, -1, &stmt, NULL);
			sqlite3_step(stmt);
			sqlite3_free(sql);

			sqlite3_finalize(stmt);

			sql = const_cast<char*>("CREATE TABLE IF NOT EXISTS usercfg.settings (id INT, \
													name UNIQUE COLLATE NOCASE, \
													value TEXT);");

			sqlitePrepare = sqlite3_prepare_v2(this->database, sql, -1, &stmt, NULL);
			int a = sqlite3_step(stmt);
			if (SQLITE_DONE == a) {
				// Shouldn't do anything here.
			}
			sqlite3_finalize(stmt);


			sql = const_cast<char*>("SELECT name FROM usercfg.settings");

			sqlitePrepare = sqlite3_prepare_v2(this->database, sql, -1, &stmt, NULL);

			while (SQLITE_ROW == sqlite3_step(stmt)) {
				const char* value = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0)); // The 0 here means we only take the first column returned. And it is the snippet as there is only one column
				int length = sqlite3_column_bytes(stmt, 0);
				if (length > 0) {
					if (strstr(value, "integrateWithFingerText") != 0) {
						integrateWithFingerText = false;
						continue;
					}
					if (strstr(value, "alwaysCompleteReqAttributes") != 0) {
						alwaysCompleteReqAttributes = true;
						continue;
					}
					if (strstr(value, "completeCFsqltype") != 0) {
						completeCFsqltype = true;
						continue;
					}
				}

			}
			sqlite3_finalize(stmt);

			sql = const_cast<char*>("ATTACH DATABASE ':memory:' AS memcache;");

			sqlitePrepare = sqlite3_prepare_v2(this->database, sql, -1, &stmt, NULL);
			a = sqlite3_step(stmt);
			if (SQLITE_DONE == a) {
				// Shouldn't do anything here.
			}
			sqlite3_finalize(stmt);
			sql = const_cast<char*>("CREATE TABLE memcache.cache (createdat DATETIME, \
													name UNIQUE COLLATE NOCASE, \
													value TEXT);");

			sqlitePrepare = sqlite3_prepare_v2(this->database, sql, -1, &stmt, NULL);
			a = sqlite3_step(stmt);
			if (SQLITE_DONE == a) {
				// Shouldn't do anything here.
			}
			sqlite3_finalize(stmt);

			coldfusionNS = new CFNamespace(this->database);
			htmlNS = new HTMLNamespace(this->database);
			sqlNS = new SQLNamespace(this->database);
			javascriptNS = new JSNamespace(this->database);
			cssNS = new CSSNamespace(this->database);
		}

		void nppCFShared::cleanupDB() {

			int sqlitePrepare;
			sqlite3_stmt* stmt;
			const char* sql = "DETACH DATABASE memcache;";

			sqlitePrepare = sqlite3_prepare_v2(this->database, sql, -1, &stmt, NULL);
			if (SQLITE_ROW == sqlite3_step(stmt)) {
				// Shouldn't do anything here.
			}
			sqlite3_finalize(stmt);

			sql = "DELETE FROM usercfg.settings";
			sqlitePrepare = sqlite3_prepare_v2(this->database, sql, -1, &stmt, NULL);
			if (SQLITE_ROW == sqlite3_step(stmt)) {
				// Shouldn't do anything here.
			}
			sqlite3_finalize(stmt);

			if (!integrateWithFingerText) {
				sql = "INSERT INTO usercfg.settings (name) VALUES (\"integrateWithFingerText\")";
				sqlitePrepare = sqlite3_prepare_v2(this->database, sql, -1, &stmt, NULL);
				if (SQLITE_ROW == sqlite3_step(stmt)) {
					// Shouldn't do anything here.
				}
				sqlite3_finalize(stmt);
			}
			if (alwaysCompleteReqAttributes) {
				sql = "INSERT INTO usercfg.settings (name) VALUES (\"alwaysCompleteReqAttributes\")";
				sqlitePrepare = sqlite3_prepare_v2(this->database, sql, -1, &stmt, NULL);
				if (SQLITE_ROW == sqlite3_step(stmt)) {
					// Shouldn't do anything here.
				}
				sqlite3_finalize(stmt);
			}
			if (completeCFsqltype) {
				sql = "INSERT INTO usercfg.settings (name) VALUES (\"completeCFsqltype\")";
				sqlitePrepare = sqlite3_prepare_v2(this->database, sql, -1, &stmt, NULL);
				if (SQLITE_ROW == sqlite3_step(stmt)) {
					// Shouldn't do anything here.
				}
				sqlite3_finalize(stmt);
			}


			sql = "DETACH DATABASE usercfg";
			sqlitePrepare = sqlite3_prepare_v2(this->database, sql, -1, &stmt, NULL);
			if (SQLITE_ROW == sqlite3_step(stmt)) {
				// Shouldn't do anything here.
			}
			sqlite3_finalize(stmt);
			sqlite3_close(database);
		}



		int BlockType::getKeywordState() const {
			return this->keywordstate;
		}		

		void BlockType::updatefromlinestate(int linestate) {
			this->inBlock = (linestate >> this->bitshift) & this->bitmask;
		}

		void BlockType::updatelinestate(int& linestate) const {
			linestate = (linestate & ~(this->bitmask << this->bitshift) | (this->inBlock & this->bitmask) << this->bitshift);
		}

		void BlockType::updateWordList(Lexilla::WordList& wl) {
			this->keywords.reset(&wl);
		}




		bool CSSBlock::validateforkeyword(Lexilla::StyleContext sc) {
			return sc.state != Styles::CF_VALUE && sc.GetRelative(-1) != '#' && sc.GetRelative(-1) != '.';
		}
		bool CSSBlock::hasKeyword(char* keyword) {
			nppCFShared& ref = *nppCFShared::Instance();
			return ref.cssNS->isKeyword(keyword);
		}

	
		bool JSBlock::validateforkeyword(Lexilla::StyleContext sc) {
			return sc.state != Styles::CF_VALUE;
		}
		bool JSBlock::hasKeyword(char* keyword) {
			nppCFShared& ref = *nppCFShared::Instance();
			return ref.javascriptNS->isKeyword(keyword);
		}


		bool CFScriptBlock::validateforkeyword(Lexilla::StyleContext sc, bool inCFSet) {
			///return validateforkeyword(sc);
			return false; ///***
		}
		bool CFScriptBlock::validateforkeyword(Lexilla::StyleContext sc) {
			return sc.state != Styles::CF_VALUE && sc.state != Styles::_COMMENT && sc.state != Styles::_COMMENTBLOCK && sc.state != Styles::_SINGLESTRING && sc.state != Styles::_DOUBLESTRING;
		}
		bool CFScriptBlock::hasKeyword(char* keyword) {
			auto length = strnlen_s(keyword, 100);
			if (length > 1 && length < 40) {//*** maybe define constants
				nppCFShared& ref = *nppCFShared::Instance();
				return ref.coldfusionNS->isKeyword(keyword);
			}
			return false;
		}
		bool CFScriptBlock::hasOperator(char* operatorword) {
			auto length = strnlen_s(operatorword, 100);
			if (length > 7 || length == 1) {
				return false;
			}
			char* copyvalue = new char[length + 10];
			strcpy_s(copyvalue, 2, (const char*)" ");

			strcat_s(copyvalue, length + 2, operatorword);
			copyvalue[length + 1] = ' ';
			copyvalue[length + 2] = '\0';

			const char* operators = " lt le lte gt ge gte is eq neq equal not contains does contain than greater or less to and xor eqv imp mod ";
			if (length > 1 && length < 40) {
				return (strstr(operators, copyvalue) != NULL);
			}
			return false;
		}
		bool CFScriptBlock::hasReservedWord(const char* reservedword) { ///
				//
				auto length = strnlen_s(reservedword, 100);

				if (length > 12 || length == 1) {
					return false;
				}
				char* copyvalue = new char[length + 10];
				strcpy_s(copyvalue, 2, (const char*)" ");

				strcat_s(copyvalue, length + 2, reservedword);
				copyvalue[length + 1] = ' ';
				copyvalue[length + 2] = '\0';

				const char* rwords = " component property function break if else switch case catch continue default do for in return try var while abstract final static null interface implements extends override ";
				return (strstr(rwords, copyvalue) != NULL);
			}


		bool CFQueryBlock::validateforkeyword(Lexilla::StyleContext sc) {
			return sc.state != Styles::CF_VALUE;
		}
		bool CFQueryBlock::hasKeyword(char* keyword) {
			nppCFShared& ref = *nppCFShared::Instance();
			return ref.sqlNS->isKeyword(keyword);
		}

} // namespace nppColdFusion
