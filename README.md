# nppColdFusion

![Build Status](https://github.com/alsovdev/nppcoldfusion/actions/workflows/build.yml/badge.svg)
![Latest Release](https://img.shields.io/github/v/release/alsovdev/nppcoldfusion)
![License](https://img.shields.io/github/license/alsovdev/nppcoldfusion)
![Platform](https://img.shields.io/badge/platform-Windows%20x64-blue)

**nppColdFusion** — плагин для **Notepad++** (x64, версия 8+), обеспечивающий полную поддержку **ColdFusion / CFML** (файлы `.cfm`, `.cfc`, `.cfml`):

- ✅ **Синтаксическая подсветка** — CF-теги, CFScript, HTML, JavaScript, CSS, SQL (в `<cfquery>`)
- ✅ **Свертка кода (folding)** — CF-теги (`<cfif>`/`</cfif>`), HTML-теги, JS/CSS блоки, `{}` в CFScript
- ✅ **Автодополнение** — встроенные constexpr структуры + XML (`nppColdFusion.xml`) — теги, атрибуты, функции
- ✅ **Автоопределение типа файла** — `.cfc` (component) vs `.cfm` по ключевому слову `component`
- ✅ **Подсветка вложенных блоков** — `<cfquery>`, `<cfscript>`, `<script>`, `<style>` — отдельные лексеры

---

## 📥 Установка

### Через Plugin Admin (рекомендуется, после добавления в nppPluginList)
1. Откройте **Plugins → Plugin Admin**
2. Найдите **nppColdFusion**
3. Установите и перезапустите Notepad++

### Вручную (текущий способ)
1. Скачайте артефакты с последнего [релиза](https://github.com/alsovdev/nppcoldfusion/releases/latest):
   - `nppColdFusion.dll`
   - `nppColdFusion.xml`
   - `nppColdFusion.db3`
2. Создайте папку: `%ProgramFiles%\Notepad++\plugins\nppColdFusion\`
3. Скопируйте `nppColdFusion.dll` в эту папку
4. Скопируйте `nppColdFusion.xml` и `nppColdFusion.db3` в: `%AppData%\Notepad++\plugins\config\`

#### Для Portable-версии Notepad++
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

## 🖥 Требования

- **Notepad++ 8.0+** (x64)
- **Windows 10/11** (x64)
- **Visual C++ Redistributable 2015-2022** (обычно уже есть в системе)

---

## 🛠 Сборка из исходников

### Предварительные требования
- Visual Studio 2022 (Community/Professional/Enterprise) с нагрузкой **Desktop development with C++**
- Windows 10 SDK (10.0.19041+)
- Python 3.x (для генерации автодополнения из YAML)

### Шаги
```cmd
git clone https://github.com/alsovdev/nppcoldfusion.git
cd nppcoldfusion
# Генерация данных автодополнения из YAML
python scripts/generate_autocomplete.py
# Откройте vs.proj\nppColdFusion.sln в Visual Studio 2022
# Выберите конфигурацию: Unicode Release | x64
# Build → Build Solution
```

Артефакты появятся в `vs.proj\x64\Release\`.

### Автоматическая сборка (CI)
GitHub Actions настроен для автоматической сборки при пуше тегов `v*`. Смотрите [workflow](.github/workflows/build.yml).

---

## 📖 История изменений

См. [CHANGELOG.md](CHANGELOG.md)

---

## 📄 Лицензия

**GNU General Public License v2.0 or later** — см. [LICENSE](LICENSE)

Оригинальный автор: **Ben Bluemel** (2011), email: ben1982@gmail.com  
Текущий мейнтейнер: **smishchuk** — форк для x64 и Notepad++ 8+ (Lexilla API)

---

## 🔗 Полезные ссылки

- [Репозиторий (форк)](https://github.com/alsovdev/nppcoldfusion)
- [Оригинальный репозиторий](https://github.com/smishchuk/nppcoldfusion)
- [Релизы](https://github.com/alsovdev/nppcoldfusion/releases)
- [Обсуждение на форуме NPP](https://community.notepad-plus-plus.org/topic/17677/coldfusion-lexer-and-npp-after-7-5-9)
- [Lexilla API](https://github.com/lexilla/lexilla)
- [NPP Plugin List (x64)](https://github.com/notepad-plus-plus/nppPluginList/blob/master/src/pl.x64.json)

---

## 🤝 Участие в разработке

PR и Issues приветствуются! Особенно нужны:
- Добавление тегов CF2021/2023 (`cfdocument`, `cfpdf`, `queryExecute` и др.)
- Unit-тесты для лексера
- Рефакторинг `Colourise_Doc` (разбить на отдельные классы)
- LSP-интеграция (cflint-lsp / vscode-cfml)

---

## 📸 Скриншоты

> *Скриншоты будут добавлены в следующем релизе*

![Syntax Highlighting](docs/images/syntax-highlighting.png)
![Code Folding](docs/images/code-folding.png)
![Auto-completion](docs/images/autocomplete.png)