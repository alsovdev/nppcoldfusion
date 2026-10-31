# nppColdFusion

![Build Status](https://github.com/alsovdev/nppcoldfusion/actions/workflows/build.yml/badge.svg)
![Latest Release](https://img.shields.io/github/v/release/alsovdev/nppcoldfusion)
![License](https://img.shields.io/github/license/alsovdev/nppcoldfusion)
![Platform](https://img.shields.io/badge/platform-Windows%20x64-blue)

---

**nppColdFusion** is a **Notepad++** plugin (x64, v8+) providing full **ColdFusion / CFML** support (`.cfm`, `.cfc`, `.cfml` files):

- ✅ **Syntax highlighting** — CF tags, CFScript, HTML, JavaScript, CSS, SQL (inside `<cfquery>`)
- ✅ **Code folding** — CF tags (`<cfif>`/`</cfif>`), HTML tags, JS/CSS blocks, `{}` in CFScript
- ✅ **Auto-completion** — built-in constexpr structures + XML (`nppColdFusion.xml`) — tags, attributes, functions
- ✅ **File type auto-detection** — `.cfc` (component) vs `.cfm` via `component` keyword
- ✅ **Nested block highlighting** — `<cfquery>`, `<cfscript>`, `<script>`, `<style>` — separate lexers

---

## 📥 Installation

### Via Plugin Admin (recommended, once added to nppPluginList)

1. Open **Plugins → Plugin Admin**
2. Find **nppColdFusion**
3. Install and restart Notepad++

### Manual (current way)

1. Download artifacts from the latest [release](https://github.com/alsovdev/nppcoldfusion/releases/latest):
   - `nppColdFusion.dll`
   - `nppColdFusion.xml`
   - `nppColdFusion.db3`
2. Create folder: `%ProgramFiles%\Notepad++\plugins\nppColdFusion\`
3. Copy `nppColdFusion.dll` there
4. Copy `nppColdFusion.xml` and `nppColdFusion.db3` to: `%AppData%\Notepad++\plugins\config\`

#### For Portable Notepad++

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

## 🖥 Requirements

- **Notepad++ 8.0+** (x64)
- **Windows 10/11** (x64)
- **Visual C++ Redistributable 2015-2022** (usually already installed)

---

## 🛠 Building from Source

### Prerequisites

- Visual Studio 2022 (Community/Professional/Enterprise) with **Desktop development with C++** workload
- Windows 10 SDK (10.0.19041+)
- Python 3.x (for generating autocomplete data from YAML)

### Steps

```cmd
git clone https://github.com/alsovdev/nppcoldfusion.git
cd nppcoldfusion
# Generate autocomplete data from YAML
python scripts/generate_autocomplete.py
# Open vs.proj\nppColdFusion.sln in Visual Studio 2022
# Select config: Unicode Release | x64
# Build → Build Solution
```

Artifacts will appear in `vs.proj\x64\Release\`.

### Automated Build (CI)

GitHub Actions builds automatically on `v*` tag pushes. See [workflow](.github/workflows/build.yml).

---

## 📖 Changelog

See [CHANGELOG.md](CHANGELOG.md)

---

## 📄 License

**GNU General Public License v2.0 or later** — see [LICENSE](LICENSE)

Original author: **Ben Bluemel** (2011), email: ben1982@gmail.com  
Current maintainer: **smishchuk** — fork for x64 and Notepad++ 8+ (Lexilla API)

---

## 🔗 Useful Links

- [Repository (fork)](https://github.com/alsovdev/nppcoldfusion)
- [Original repository](https://github.com/smishchuk/nppcoldfusion)
- [Releases](https://github.com/alsovdev/nppcoldfusion/releases)
- [NPP Forum Discussion](https://community.notepad-plus-plus.org/topic/17677/coldfusion-lexer-and-npp-after-7-5-9)
- [Lexilla API](https://github.com/lexilla/lexilla)
- [NPP Plugin List (x64)](https://github.com/notepad-plus-plus/nppPluginList/blob/master/src/pl.x64.json)

---

## 🤝 Contributing

PRs and Issues welcome! Especially needed:

- Add CF2021/2023 tags (`cfdocument`, `cfpdf`, `queryExecute`, etc.)
- Unit tests for the lexer
- Refactor `Colourise_Doc` (split into separate classes)
- LSP integration (cflint-lsp / vscode-cfml)

---

## 📸 Screenshots

> *Screenshots will be added in the next release*

![Syntax Highlighting](docs/images/syntax-highlighting.png)
![Code Folding](docs/images/code-folding.png)
![Auto-completion](docs/images/autocomplete.png)