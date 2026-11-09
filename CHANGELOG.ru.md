# История изменений

Все заметные изменения в этом проекте документируются в этом файле.

Формат основан на [Keep a Changelog](https://keepachangelog.com/ru/1.0.0/),
и проект следует [Semantic Versioning](https://semver.org/lang/ru/).

**In English: [CHANGELOG.md](CHANGELOG.md)**

---
## [0.9.8] - 2026-11-09

### Исправлено

- **Сортировка атрибутов автокомплита** — `listTagAttributes()` теперь возвращает атрибуты, отсортированные алфавитно (без учета регистра) для корректного префиксного совпадения в автокомплите Notepad++; исправлено отсутствие атрибута `collection` в `cfloop`
- **Проверки границ** — добавлена проверка `a > 0` для `sc.Forward(a-1)` в ветке `hasReservedWord` (строка 949) для предотвращения крашей при вводе одиночных символов
- **Переключение комментариев** — XML конфиг использует стиль HTML-комментариев (`<!-- -->`) для совместимости с функцией toggle comment в Notepad++; лексер при этом подсвечивает и HTML (`<!-- -->`, стиль 9), и CFML (`<!--- --->`, стиль 12) комментарии разными цветами

### Изменено

- **Версия плагина** — 0.9.7 → 0.9.8 в `nppColdFusion.h`, `nppColdFusion.rc` (FILEVERSION/PRODUCTVERSION)
- **Зависимости** — добавлены заголовочные файлы `<vector>` и `<algorithm>` в `nppCFShared.cpp` для сортировки атрибутов

## [0.9.7] - 2026-11-04

### Исправлено

- **Обработка кириллицы/Unicode в лексере** — `IsAWordChar` теперь разрешает Unicode-символы (≥0x80) как часть слова; добавлен `SafeMakeLowerCase`, который lowercases только ASCII, а Unicode пропускает неизменным; предотвращает краши при вводе кириллицы внутри `<cfquery>`
- **Подсветка SQL-ключевых слов внутри `<cfquery>`** — реализован `DescribeWordListSets()` для передачи списков ключевых слов из Notepad++; `WordListSet()` сохраняет списки; `Colourise_Doc` заполняет ключевые слова BlockType; `CFQueryBlock::validateforkeyword` теперь находит ключевые слова в состоянии `_DEFAULT`
- **Автокомплит cfelse/cfelseif** — изменено `closing_required: false` в `data/tags.yaml`; больше не генерирует `</cfelse>` или `</cfelseif>`
- **Границы массивов** — увеличены `originallists`/`loweredlists` с 10 до 31 для соответствия `numWordLists = 31` (KEYWORDSET_MAX+1)
- **Синтаксические ошибки** — убраны лишние скобки в `Colourise_Doc` (строки 1017, 1107)
- **Проверки границ Forward** — добавлены проверки `a>0` на всех вызовах `sc.Forward(a-1)` (8 мест) для предотвращения крашей на неполных словах

### Изменено

- **Версия плагина** — 0.9.6 → 0.9.7 в `nppColdFusion.h`, `nppColdFusion.rc` (FILEVERSION/PRODUCTVERSION)
- **Документация** — уточнено: XML конфиг должен лежать в `%APPDATA%\Notepad++\plugins\config\nppColdFusion.xml` (единственный надежный путь); обновлены README.md и README.ru.md

## [0.9.6] - 2026-11-03

### Добавлено

- **Интеграционные тесты с реальными CFM/CFC файлами** из open source проектов:
  - Taffy framework (atuttle/Taffy): 14 файлов включая Application.cfc, ресурсные CFC, примеры consumer
  - Lucee docs (lucee/lucee-docs): 4 файла включая build-скрипты
  - Лексер токенизирует все 18 фикстур без крашей
  - Тесты проверяют CFML конструкции: component, function, cfquery, cfargument, cfoutput, cfloop, cfset, cffile

- **Стили по умолчанию в плагине** (работает без XML):
  - Реализованы `NamedStyles()`, `NameOfStyle()`, `DescriptionOfStyle()`, `TagsOfStyle()` в лексере
  - **24 ID стилей** (0-23), соответствующие nppColdFusion.xml (с пропусками 11, 18, 20)
  - **22 стиля** определены в XML с цветами
  - Если nppColdFusion.xml отсутствует, используются встроенные цвета по умолчанию

- **XML конфиг в той же папке что и DLL**:
  - Структура релиза изменена: XML кладется рядом с DLL в папки x64/ и x86/
  - Обновлен INSTALL.txt с новыми инструкциями по установке
  - Если XML отсутствует, плагин использует встроенные цвета по умолчанию

### Изменено

- **Объединены feature-ветки**: feat/boost-cleanup, feat/fix-review-issues, feat/v0.9.4-all-fixes
  - Boost полностью удален из проекта
  - Исправлен x64 краш (TargetMachine=MachineX64 + исправление экспорта)
  - Применены правки из ревью: Instance() возвращает ref, откат std::array, критические исправления
  - P9-P11: naming consistency, string_view кэш, BlockType::updateWordList
  - DLL переименованы в релизе для уникальных имен (x64, x86 суффиксы)
  - db3 удален из артефактов релиза (legacy, не используется)

### Покрытие тестами

- **27 тестов проходит** (7 lexer + 4 functions + 4 autocomplete + 12 integration)
- Doctest v2.4.11 (header-only, без внешних зависимостей)
- Тесты запускаются при каждом push в master

## [0.9.2] - 2026-11-02

### Изменено

- **Boost полностью удалён** из проекта:
  - Удалён `vs.proj/packages.config` (неиспользуемая NuGet-ссылка)
  - Удалены все закомментированные импорты/ошибки Boost из `.vcxproj`
  - Удалён закомментированный `#include <boost/thread/thread.hpp>` из `CFMLPlugin.cpp`
- Система сборки очищена: никаких NuGet-зависимостей не требуется

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