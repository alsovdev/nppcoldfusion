# Changelog

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

**На русском: [CHANGELOG.ru.md](CHANGELOG.ru.md)**

---

## [0.9.8] - 2026-11-09

### Fixed

- **Autocomplete attribute sorting** — `listTagAttributes()` now returns attributes sorted alphabetically (case-insensitive) for proper prefix matching in Notepad++ autocomplete; fixes `cfloop` `collection` attribute not appearing
- **Bounds checks** — added `a > 0` guard for `sc.Forward(a-1)` in `hasReservedWord` branch (line 949) to prevent crashes on single-character input
- **Comment toggle** — XML config uses HTML comment style (`<!-- -->`) for Notepad++ toggle feature compatibility; lexer still highlights both HTML (`<!-- -->`, style 9) and CFML (`<!--- --->`, style 12) comments with different colors

### Changed

- **Plugin version** — 0.9.7 → 0.9.8 in `nppColdFusion.h`, `nppColdFusion.rc` (FILEVERSION/PRODUCTVERSION)
- **Dependencies** — added `<vector>` and `<algorithm>` includes to `nppCFShared.cpp` for attribute sorting

## [0.9.7] - 2026-11-04

### Fixed

- **Cyrillic/Unicode handling in lexer** — `IsAWordChar` now allows Unicode characters (≥0x80) as word characters; added `SafeMakeLowerCase` wrapper that only lowercases ASCII and passes Unicode through unchanged; prevents crashes when typing Cyrillic inside `<cfquery>`
- **SQL keyword highlighting inside `<cfquery>`** — implemented `DescribeWordListSets()` so Notepad++ sends keyword lists; `WordListSet()` stores lists; `Colourise_Doc` populates BlockType keywords from stored lists; `CFQueryBlock::validateforkeyword` now detects keywords in `_DEFAULT` state
- **cfelse/cfelseif autocomplete** — changed `closing_required: false` in `data/tags.yaml`; no longer generates `</cfelse>` or `</cfelseif>`
- **Array bounds** — increased `originallists`/`loweredlists` arrays from 10 to 31 to match `numWordLists = 31` (KEYWORDSET_MAX+1)
- **Syntax errors** — removed extra parentheses in `Colourise_Doc` (lines 1017, 1107)
- **Forward bounds checks** — added `a>0` guards on all `sc.Forward(a-1)` calls (8 locations) to prevent crashes on incomplete words

### Changed

- **Plugin version** — 0.9.6 → 0.9.7 in `nppColdFusion.h`, `nppColdFusion.rc` (FILEVERSION/PRODUCTVERSION)
- **Documentation** — clarified XML config must go to `%APPDATA%\Notepad++\plugins\config\nppColdFusion.xml` (only reliable path); updated README.md and README.ru.md

## [0.9.6] - 2026-11-03

### Added

- **Integration tests with real CFM/CFC files** from open source projects:
  - Taffy framework (atuttle/Taffy): 14 files including Application.cfc, resource CFCs, consumer examples
  - Lucee docs (lucee/lucee-docs): 4 files including build scripts
  - Lexer tokenizes all 18 fixtures without crashing
  - Tests verify CFML constructs: component, function, cfquery, cfargument, cfoutput, cfloop, cfset, cffile

- **Default styles in plugin** (works without XML):
  - Implemented `NamedStyles()`, `NameOfStyle()`, `DescriptionOfStyle()`, `TagsOfStyle()` in lexer
  - **24 style IDs** (0-23) matching nppColdFusion.xml exactly (with gaps at 11, 18, 20)
  - **22 styles** defined in XML with colors
  - If nppColdFusion.xml is missing, default colors from plugin are used

- **XML config file in same folder as DLL**:
  - Release structure changed: XML placed alongside DLL in x64/ and x86/ folders
  - Updated INSTALL.txt with new installation instructions
  - If XML missing, plugin uses built-in default colors

### Changed

- **Merged feature branches**: feat/boost-cleanup, feat/fix-review-issues, feat/v0.9.4-all-fixes
  - Boost completely removed from project
  - x64 crash fixed (TargetMachine=MachineX64 + export fix)
  - Review fixes applied: Instance() ref return, std::array revert, critical issues
  - P9-P11 fixes: naming consistency, string_view cache, BlockType::updateWordList
  - DLL renamed in release for unique asset names (x64, x86 suffixes)
  - db3 removed from release artifacts (legacy, not used)

### Test Coverage

- **27 tests passing** (7 lexer + 4 functions + 4 autocomplete + 12 integration)
- Doctest v2.4.11 (header-only, no external deps)
- Tests run on every push to master

## [0.9.2] - 2026-11-02

### Changed

- **Boost completely removed** from project:
  - Deleted `vs.proj/packages.config` (unused NuGet reference)
  - Removed all commented Boost imports/errors from `.vcxproj`
  - Removed commented `#include <boost/thread/thread.hpp>` from `CFMLPlugin.cpp`
- Build system cleaned: no NuGet dependencies required

## [0.9.1] - 2026-10-26

### Changed

- **Modern C++20 migration**: Removed Boost dependency entirely
  - `boost::shared_ptr` → `std::shared_ptr` with `std::make_shared`
  - `boost::to_lower` → `std::transform` + `std::tolower`
  - Commented out NuGet Boost imports in `.vcxproj`
- **Removed sqlite3.lib link dependencies** — SQLite used runtime-only via pre-generated `nppColdFusion.db3`
- **Fixed build configuration** for `Unicode Release|x64`:
  - Added missing `OutDir`/`IntDir` properties
  - Corrected GitHub Actions artifact paths to `x64/Unicode Release/`
- **Fixed corrupted range-based for loops** in `Colourise_Doc` function (lines 492, 853)
- **Generated missing artifacts**: `AutoCompleteData.h`, `nppColdFusion.db3`, `nppColdFusion.xml`

### Fixed

- GitHub Actions CI/CD now builds successfully on `windows-latest` + MSBuild
- No external NuGet dependencies required for build
- Build outputs to correct directory structure

## [0.8.4] - 2024-10-17 (pre-release / alpha)

### Added

- Rebuild for **x64** and **Notepad++ 8+** (Lexilla API)
- Modern C++20 standard support
- Auto-completion fixes (dropdown, int assertion)

### Known Issues

- No CI/CD — local build only in VSCode
- Missing README.md, CHANGELOG.md, LICENSE
- Marked as pre-release / alpha
- Assets not uploaded to GitHub Releases
- Not in official NPP Plugin List (Plugin Admin)
- Missing `sqlite3.dll` in distribution
- Missing `.def` file for exports

## [0.8.3 and earlier] - Legacy (Ben Bluemel, 2011-201x)

- Original plugin for Notepad++ 32-bit (≤ 7.5.9)
- Scintilla-based lexer (before NPP switched to Lexilla)
- SourceForge: https://sourceforge.net/projects/npp-plugins/files/NppColdFusion/