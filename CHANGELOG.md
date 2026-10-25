# Changelog

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## [1.0.0] - 2026-10-25

### Added
- **GitHub Actions CI/CD** — автоматическая сборка x64, релизы с артефактами (`.dll`, `.xml`, `.db3`, `sqlite3.dll`, `INSTALL.txt`)
- **README.md** — полная документация: установка, требования, сборка, лицензия
- **LICENSE** — GNU GPL v2+
- **src/nppColdFusion_Plugin.def** — модуль экспорта DLL (исправлена линковка)
- **extern/sqlite3/x64/sqlite3.dll** — предустановленная SQLite 3.54.1 для Windows x64
- **src/nppColdFusion.db3** — база автодополнения (восстановлена из релиза v0.8.4)
- **INSTALL.txt** в артефактах релиза — инструкция по установке

### Changed
- Версионирование: переход с alpha `0.8.4` на стабильную `1.0.0` (SemVer)
- Версия теперь читается из git-тегов (`git describe --tags`) в CI
- Обновлён `CFMLPlugin.cpp`: версия плагина теперь подставляется автоматически при сборке

### Fixed
- Отсутствующий `.def` файл, вызывающий ошибки линкера
- Отсутствие `sqlite3.dll` в дистрибутиве (runtime зависимость)
- Битые ассеты в GitHub Releases (теперь загружаются автоматически через workflow)

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

---

**Note:** Версии до 1.0.0 считаются pre-release. Начиная с 1.0.0 соблюдается Semantic Versioning.