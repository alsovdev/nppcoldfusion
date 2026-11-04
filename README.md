# nppColdFusion

![Build Status](https://github.com/alsovdev/nppcoldfusion/actions/workflows/build.yml/badge.svg)
![Latest Release](https://img.shields.io/github/v/release/alsovdev/nppcoldfusion)
![License](https://img.shields.io/github/license/alsovdev/nppcoldfusion)
![Platform](https://img.shields.io/badge/platform-Windows%20x64%20%7C%20x86-blue)

---

**nppColdFusion** is a **Notepad++** plugin (x64, x86, v8+) providing full **ColdFusion / CFML** support (`.cfm`, `.cfc`, `.cfml` files):

- ✅ **Syntax highlighting** — CF tags, CFScript, HTML, JavaScript, CSS, SQL (inside `<cfquery>`)
- ✅ **Code folding** — CF tags (`<cfif>`/`</cfif>`), HTML tags, JS/CSS blocks, `{}` in CFScript
- ✅ **Auto-completion** — built-in constexpr structures + XML (`nppColdFusion.xml`) — tags, attributes, functions
- ✅ **File type auto-detection** — `.cfc` (component) vs `.cfm` via `component` keyword
- ✅ **Nested block highlighting** — `<cfquery>`, `<cfscript>`, `<script>`, `<style>` — separate lexers

---

**Доступен на русском: [README.ru.md](README.ru.md)**

---

## 📥 Installation

### Manual (current way)

1. Download artifacts from the latest [release](https://github.com/alsovdev/nppcoldfusion/releases/latest):
   - **x64** (Notepad++ 64-bit): `nppColdFusion-x64.dll`, `nppColdFusion.xml`, `INSTALL.txt`
   - **x86** (Notepad++ 32-bit): `nppColdFusion-x86.dll`, `nppColdFusion.xml`, `INSTALL.txt`
   - **Shared**: `SHA256SUMS.txt`

2. **Rename the DLL** to match the plugin folder name:
   - Rename `nppColdFusion-x64.dll` → `nppColdFusion.dll` (for x64)
   - Rename `nppColdFusion-x86.dll` → `nppColdFusion.dll` (for x86)

3. **Copy the DLL to the plugin folder** (create it if needed):
   ```
   %ProgramFiles%\Notepad++\plugins\nppColdFusion\nppColdFusion.dll
   ```

4. **Copy the XML to the AppData Config folder** (this is the ONLY working location for installed Notepad++):
   ```
   %APPDATA%\Notepad++\plugins\config\nppColdFusion.xml
   ```

> ⚠️ **Important: XML file location**
>
> Notepad++ searches for the lexer XML in **`plugins\Config\`** at load time — **not** next to the DLL.
>
> - **DLL** → `%ProgramFiles%\Notepad++\plugins\nppColdFusion\nppColdFusion.dll`
> - **XML** → `%APPDATA%\Notepad++\plugins\config\nppColdFusion.xml` **(recommended, always works)**
>
> The `plugins\Config\` folder under Program Files requires admin rights to write. The AppData location is user-writable and works without elevation.
>
> **Note**: Since Notepad++ v8.9.3, N++ may automatically copy `*.model.xml` files from the installation directory to AppData on first run. If you place `nppColdFusion.xml` in `%ProgramFiles%\Notepad++\plugins\Config\`, it *might* be copied to AppData automatically — but this is not guaranteed for plugin lexer XMLs. The AppData path is the reliable choice.
>
> If you use portable Notepad++, place both files in `<Notepad++>\plugins\nppColdFusion\`.

#### For Portable Notepad++

```
<Notepad++>/
├── notepad++.exe
└── plugins/
    └── nppColdFusion/
        ├── nppColdFusion.dll
        └── nppColdFusion.xml
```

### Verify Installation

1. Restart Notepad++
2. Open **Plugins → nppColdFusion → About** — should show version (e.g., `v0.9.6`)
3. Open a `.cfm` or `.cfc` file — syntax highlighting should activate automatically

### Verify Integrity (optional)

Check `SHA256SUMS.txt` from the release:
```cmd
certutil -hashfile nppColdFusion.dll SHA256
```

---

## 🖥 Requirements

- **Notepad++ 8.0+** (x64 or x86)
- **Windows 10/11** (x64 or x86)
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
# Select config: Unicode Release | x64  (or Win32 for x86)
# Build → Build Solution
```

Artifacts will appear in `vs.proj\x64\Unicode Release\` (or `Win32\Unicode Release\`).

### Automated Build (CI)

GitHub Actions builds automatically on `v*` tag pushes. See [workflow](.github/workflows/build.yml).

---

## 📖 Changelog

See [CHANGELOG.md](CHANGELOG.md) / [История изменений](CHANGELOG.ru.md)

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

PRs and Issues welcome! Contributions of any kind are appreciated — bug reports, feature requests, code improvements, documentation updates, and more.