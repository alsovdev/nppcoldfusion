# nppColdFusion

![Build Status](https://github.com/alsovdev/nppcoldfusion/actions/workflows/build.yml/badge.svg)
![Latest Release](https://img.shields.io/github/v/release/alsovdev/nppcoldfusion)
![License](https://img.shields.io/github/license/alsovdev/nppcoldfusion)
![Platform](https://img.shields.io/badge/platform-Windows%20x64%20%7C%20x86-blue)

---

**nppColdFusion** — плагин для **Notepad++** (x64, x86, версия 8+), обеспечивающий полную поддержку **ColdFusion / CFML** (файлы `.cfm`, `.cfc`, `.cfml`):

- ✅ **Синтаксическая подсветка** — CF-теги, CFScript, HTML, JavaScript, CSS, SQL (в `<cfquery>`)
- ✅ **Свертка кода (folding)** — CF-теги (`<cfif>`/`</cfif>`), HTML-теги, JS/CSS блоки, `{}` в CFScript
- ✅ **Автодополнение** — встроенные constexpr структуры + XML (`nppColdFusion.xml`) — теги, атрибуты, функции
- ✅ **Автоопределение типа файла** — `.cfc` (component) vs `.cfm` по ключевому слову `component`
- ✅ **Подсветка вложенных блоков** — `<cfquery>`, `<cfscript>`, `<script>`, `<style>` — отдельные лексеры

---

**Available in English: [README.md](README.md)**

---

## 📥 Установка

### Вручную (текущий способ)

1. Скачайте артефакты с последнего [релиза](https://github.com/alsovdev/nppcoldfusion/releases/latest):
   - **x64** (Notepad++ 64-bit): `nppColdFusion-x64.dll`, `nppColdFusion.xml`, `INSTALL.txt`
   - **x86** (Notepad++ 32-bit): `nppColdFusion-x86.dll`, `nppColdFusion.xml`, `INSTALL.txt`
   - **Shared**: `SHA256SUMS.txt`

2. **Переименуйте DLL** чтобы имя совпадало с папкой плагина:
   - `nppColdFusion-x64.dll` → `nppColdFusion.dll` (для x64)
   - `nppColdFusion-x86.dll` → `nppColdFusion.dll` (для x86)

3. **Скопируйте DLL в папку плагина** (создайте её при необходимости):
   ```
   %ProgramFiles%\Notepad++\plugins\nppColdFusion\nppColdFusion.dll
   ```

4. **Скопируйте XML в папку Config в AppData** (это ЕДИНСТВЕННЫЙ рабочий путь для установленного Notepad++):
   ```
   %APPDATA%\Notepad++\plugins\config\nppColdFusion.xml
   ```

> ⚠️ **Важно: расположение XML файла**
>
> Notepad++ ищет XML лексера в **`plugins\Config\`** при загрузке — **не** рядом с DLL.
>
> - **DLL** → `%ProgramFiles%\Notepad++\plugins\nppColdFusion\nppColdFusion.dll`
> - **XML** → `%APPDATA%\Notepad++\plugins\config\nppColdFusion.xml` **(рекомендуется, всегда работает)**
>
> Папка `plugins\Config\` в Program Files требует прав администратора для записи. AppData доступен для записи пользователем и работает без повышения прав.
>
> **Примечание**: Начиная с Notepad++ v8.9.3, N++ может автоматически копировать файлы `*.model.xml` из папки установки в AppData при первом запуске. Если положить `nppColdFusion.xml` в `%ProgramFiles%\Notepad++\plugins\Config\`, он *может* скопироваться в AppData автоматически — но для XML плагинов-лексеров это не гарантируется. Путь через AppData — самый надежный.
>
> Для portable-версии Notepad++ положите оба файла в `<Notepad++>\plugins\nppColdFusion\`.

#### Для Portable-версии Notepad++

```
<Notepad++>/
├── notepad++.exe
└── plugins/
    └── nppColdFusion/
        ├── nppColdFusion.dll
        └── nppColdFusion.xml
```

### Проверка установки

1. Перезапустите Notepad++
2. Откройте **Plugins → nppColdFusion → About** — должна отображаться версия (например, `v0.9.6`)
3. Откройте файл `.cfm` или `.cfc` — синтаксическая подсветка должна включиться автоматически

### Проверка целостности (опционально)

Сравните с `SHA256SUMS.txt` из релиза:
```cmd
certutil -hashfile nppColdFusion.dll SHA256
```

---

## 🖥 Требования

- **Notepad++ 8.0+** (x64 или x86)
- **Windows 10/11** (x64 или x86)
- **Visual C++ Redistributable 2015-2022** (обычно уже установлен)

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
# Выберите конфигурацию: Unicode Release | x64  (или Win32 для x86)
# Build → Build Solution
```

Артефакты появятся в `vs.proj\x64\Unicode Release\` (или `Win32\Unicode Release\`).

### Автоматическая сборка (CI)

GitHub Actions настроен для автоматической сборки при пуше тегов `v*`. Смотрите [workflow](.github/workflows/build.yml).

---

## 📖 История изменений

См. [CHANGELOG.ru.md](CHANGELOG.ru.md) / [Changelog](CHANGELOG.md)

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

PR и Issues приветствуются! Принимаются вклады любого рода — сообщения об ошибках, предложения функций, улучшения кода, обновления документации и многое другое.