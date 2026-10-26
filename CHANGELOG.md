# Changelog

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

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
- Пересборка под **x64** и **Notepad++ 8+** (Lexilla API)
- Поддержка современных стандартов C++20
- Исправления автодополнения (dropdown, int assertion)

### Known Issues
- Нет CI/CD — сборка только локально в VSCode
- Нет README.md, CHANGELOG.md, LICENSE
- Релиз помечен как pre-release / alpha
- Ассеты не загрузились в GitHub Releases
- Нет в официальном списке плагинов NPP (Plugin Admin)
- Отсутствует `sqlite3.dll` в дистрибутиве
- Отсутствует `.def` файл для экспорта

## [0.8.3 and earlier] - Legacy (Ben Bluemel, 2011-201x)

- Оригинальный плагин для Notepad++ 32-bit (≤ 7.5.9)
- Scintilla-based lexer (до перехода NPP на Lexilla)
- SourceForge: https://sourceforge.net/projects/npp-plugins/files/NppColdFusion/