# nppColdFusion

![Build Status](https://github.com/alsovdev/nppcoldfusion/actions/workflows/build.yml/badge.svg)
![Latest Release](https://img.shields.io/github/v/release/alsovdev/nppcoldfusion)
![License](https://img.shields.io/github/license/alsovdev/nppcoldfusion)
![Platform](https://img.shields.io/badge/platform-Windows%20x64-blue)

---

**nppColdFusion** — плагин для **Notepad++** (x64, версия 8+), обеспечивающий полную поддержку **ColdFusion / CFML** (файлы `.cfm`, `.cfc`, `.cfml`):

- ✅ **Синтаксическая подсветка** — CF-теги, CFScript, HTML, JavaScript, CSS, SQL (в `<cfquery>`)
- ✅ **Свертка кода (folding)** — CF-теги (`<cfif>`/`</cfif>`), HTML-теги, JS/CSS блоки, `{}` в CFScript
- ✅ **Автодополнение** — встроенные constexpr структуры + XML (`nppColdFusion.xml`) — теги, атрибуты, функции
- ✅ **Автоопределение типа файла** — `.cfc` (component) vs `.cfm` по ключевому слову `component`
- ✅ **Подсветка вложенных блоков** — `<cfquery>`, `<cfscript>`, `<script>`, `<style>` — отдельные лексеры

---

**nppColdFusion** is a **Notepad++** plugin (x64, v8+) providing full **ColdFusion / CFML** support (`.cfm`, `.cfc`, `.cfml` files):

- ✅ **Syntax highlighting** — CF tags, CFScript, HTML, JavaScript, CSS, SQL (inside `<cfquery>`)
- ✅ **Code folding** — CF tags (`<cfif>`/`</cfif>`), HTML tags, JS/CSS blocks, `{}` in CFScript
- ✅ **Auto-completion** — built-in constexpr structures + XML (`nppColdFusion.xml`) — tags, attributes, functions
- ✅ **File type auto-detection** — `.cfc` (component) vs `.cfm` via `component` keyword
- ✅ **Nested block highlighting** — `<cfquery>`, `<cfscript>`, `<script>`, `<style>` — separate lexers

---

## 📥 Установка / Installation

### Через Plugin Admin (рекомендуется, после добавления в nppPluginList)
### Via Plugin Admin (recommended, once added to nppPluginList)

1. Откройте **Plugins → Plugin Admin** / Open **Plugins → Plugin Admin**
2. Найдите **nppColdFusion** / Find **nppColdFusion**
3. Установите и перезапустите Notepad++ / Install and restart Notepad++

### Вручную (текущий способ) / Manual (current way)

1. Скачайте артефакты с последнего [релиза](https://github.com/alsovdev/nppcoldfusion/releases/latest): / Download artifacts from the latest [release](https://github.com/alsovdev/nppcoldfusion/releases/latest):
   - `nppColdFusion.dll`
   - `nppColdFusion.xml`
   - `nppColdFusion.db3`
2. Создайте папку: / Create folder: `%ProgramFiles%\Notepad++\plugins\nppColdFusion\`
3. Скопируйте `nppColdFusion.dll` в эту папку / Copy `nppColdFusion.dll` there
4. Скопируйте `nppColdFusion.xml` и `nppColdFusion.db3` в: / Copy `nppColdFusion.xml` and `nppColdFusion.db3` to: `%AppData%\Notepad++\plugins\config\`

#### Для Portable-версии Notepad++ / For Portable Notepad++

```
<Notepad++>/
├── notepad++.exe
└── plugins/
    ├── nppColdFusion/
    │   └── nppColdFusion.dll
    └── config/
        ├── nppColdFusion.xml
        └── nppColdFusion.db3
```

---

## 🖥 Требования / Requirements

- **Notepad++ 8.0+** (x64)
- **Windows 10/11** (x64)
- **Visual C++ Redistributable 2015-2022** (обычно уже есть в системе / usually already installed)

---

## 🛠 Сборка из исходников / Building from Source

### Предварительные требования / Prerequisites

- Visual Studio 2022 (Community/Professional/Enterprise) с нагрузкой **Desktop development with C++**
- Windows 10 SDK (10.0.19041+)
- Python 3.x (для генерации автодополнения из YAML / for generating autocomplete from YAML)

### Шаги / Steps

```cmd
git clone https://github.com/alsovdev/nppcoldfusion.git
cd nppcoldfusion
# Генерация данных автодополнения из YAML / Generate autocomplete data from YAML
python scripts/generate_autocomplete.py
# Откройте vs.proj\nppColdFusion.sln в Visual Studio 2022 / Open vs.proj\nppColdFusion.sln in VS 2022
# Выберите конфигурацию: Unicode Release | x64 / Select config: Unicode Release | x64
# Build → Build Solution
```

Артефакты появятся в `vs.proj\x64\Release\`. / Artifacts will appear in `vs.proj\x64\Release\`.

### Автоматическая сборка (CI) / Automated Build (CI)

GitHub Actions настроен для автоматической сборки при пуше тегов `v*`. Смотрите [workflow](.github/workflows/build.yml). / GitHub Actions builds automatically on `v*` tag pushes. See [workflow](.github/workflows/build.yml).

---

## 📖 История изменений / Changelog

См. [CHANGELOG.md](CHANGELOG.md) / See [CHANGELOG.md](CHANGELOG.md)

---

## 📄 Лицензия / License

**GNU General Public License v2.0 or later** — см. [LICENSE](LICENSE) / See [LICENSE](LICENSE)

Оригинальный автор: **Ben Bluemel** (2011), email: ben1982@gmail.com  
Original author: **Ben Bluemel** (2011), email: ben1982@gmail.com

Текущий мейнтейнер: **smishchuk** — форк для x64 и Notepad++ 8+ (Lexilla API)  
Current maintainer: **smishchuk** — fork for x64 and Notepad++ 8+ (Lexilla API)

---

## 🔗 Полезные ссылки / Useful Links

- [Репозиторий (форк) / Repository (fork)](https://github.com/alsovdev/nppcoldfusion)
- [Оригинальный репозиторий / Original repository](https://github.com/smishchuk/nppcoldfusion)
- [Релизы / Releases](https://github.com/alsovdev/nppcoldfusion/releases)
- [Обсуждение на форуме NPP / NPP Forum Discussion](https://community.notepad-plus-plus.org/topic/17677/coldfusion-lexer-and-npp-after-7-5-9)
- [Lexilla API](https://github.com/lexilla/lexilla)
- [NPP Plugin List (x64)](https://github.com/notepad-plus-plus/nppPluginList/blob/master/src/pl.x64.json)

---

## 🤝 Участие в разработке / Contributing

PR и Issues приветствуются! Особенно нужны: / PRs and Issues welcome! Especially needed:

- Добавление тегов CF2021/2023 (`cfdocument`, `cfpdf`, `queryExecute` и др.) / Add CF2021/2023 tags (`cfdocument`, `cfpdf`, `queryExecute`, etc.)
- Unit-тесты для лексера / Unit tests for the lexer
- Рефакторинг `Colourise_Doc` (разбить на отдельные классы) / Refactor `Colourise_Doc` (split into separate classes)
- LSP-интеграция (cflint-lsp / vscode-cfml) / LSP integration (cflint-lsp / vscode-cfml)

---

## 📸 Скриншоты / Screenshots

> *Скриншоты будут добавлены в следующем релизе / Screenshots will be added in the next release*

![Syntax Highlighting](docs/images/syntax-highlighting.png)
![Code Folding](docs/images/code-folding.png)
![Auto-completion](docs/images/autocomplete.png)