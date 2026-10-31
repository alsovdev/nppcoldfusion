# История изменений

Все заметные изменения в этом проекте документируются в этом файле.

Формат основан на [Keep a Changelog](https://keepachangelog.com/ru/1.0.0/),
и проект следует [Semantic Versioning](https://semver.org/lang/ru/).

**In English: [CHANGELOG.md](CHANGELOG.md)**

---

## [0.9.1] - 2026-10-26

### Изменено

- **Миграция на современный C++20**: полностью удалена зависимость от Boost
  - `boost::shared_ptr` → `std::shared_ptr` с `std::make_shared`
  - `boost::to_lower` → `std::transform` + `std::tolower`
  - Импорт Boost через NuGet в `.vcxproj` закомментирован
- **Удалены зависимости sqlite3.lib** — SQLite использовался только в рантайме через предгенерированный `nppColdFusion.db3`
- **Исправлена конфигурация сборки** для `Unicode Release|x64`:
  - Добавлены отсутствующие свойства `OutDir`/`IntDir`
  - Скорректированы пути артефактов GitHub Actions на `x64/Unicode Release/`
- **Исправлены сломанные range-based for loops** в функции `Colourise_Doc` (строки 492, 853)
- **Сгенерированы отсутствующие артефакты**: `AutoCompleteData.h`, `nppColdFusion.db3`, `nppColdFusion.xml`

### Исправлено

- GitHub Actions CI/CD теперь успешно собирается на `windows-latest` + MSBuild
- Для сборки не требуются внешние NuGet-зависимости
- Артефакты сборки попадают в правильную структуру директорий

## [0.8.4] - 2024-10-17 (pre-release / alpha)

### Добавлено

- Пересборка под **x64** и **Notepad++ 8+** (Lexilla API)
- Поддержка современного стандарта C++20
- Исправления автодополнения (dropdown, int assertion)

### Известные проблемы

- Нет CI/CD — сборка только локально в VSCode
- Отсутствуют README.md, CHANGELOG.md, LICENSE
- Релиз помечен как pre-release / alpha
- Ассеты не загружены в GitHub Releases
- Нет в официальном списке плагинов NPP (Plugin Admin)
- Отсутствует `sqlite3.dll` в дистрибутиве
- Отсутствует `.def` файл для экспорта

## [0.8.3 и ранее] — Legacy (Ben Bluemel, 2011-201x)

- Оригинальный плагин для Notepad++ 32-bit (≤ 7.5.9)
- Scintilla-лексер (до перехода NPP на Lexilla)
- SourceForge: https://sourceforge.net/projects/npp-plugins/files/NppColdFusion/