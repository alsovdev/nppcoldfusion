# nppColdFusion — Руководство по релизу для майнтейнера

> **Аудитория**: Майнтейнер (`smishchuk` / `alsovdev`)  
> **Цель**: Собрать подписанные артефакты, создать GitHub Release, опубликовать в Notepad++ Plugin Admin

---

## 1. Предварительные требования (разовая настройка)

| Инструмент | Версия | Примечания |
|------------|---------|-----------|
| Windows 10/11 x64 | 21H2+ | Хост для сборки |
| Visual Studio 2022 | 17.8+ | Нагрузка **Desktop development with C++** |
| Windows 10 SDK | 10.0.19041+ | |
| Python | 3.10+ | `python -m pip install -U pip` |
| Git | 2.40+ | `git config --global core.autocrlf false` |
| GitHub CLI (`gh`) | 2.40+ | `gh auth login --scopes repo,workflow` |
| `sha256sum` / `certutil` | встроены | Для контрольных сумм |

> **Совет**: Используйте чистую VM или GitHub Actions `windows-latest` для воспроизводимых сборок.

---

## 2. Структура репозитория (что клонировать)

```bash
# Апстрим (авторитетный источник)
git clone https://github.com/smishchuk/nppcoldfusion.git
cd nppcoldfusion

# Добавляем свой форк как remote (для пуша тегов)
git remote add fork https://github.com/alsovdev/nppcoldfusion.git
```

**Политика веток**:  
- `master` = готовый к релизу, всегда зелёный  
- Feature-ветки → PR → squash-merge в `master`

---

## 3. Локальная сборка (проверка перед тегом)

```cmd
# 1. Генерация артефактов автодополнения (AutoCompleteData.h, nppColdFusion.db3, nppColdFusion.xml)
python scripts/generate_autocomplete.py

# 2. Открытие решения
start vs.proj\nppColdFusion.sln
```

**В Visual Studio**:  
- Configuration: **Unicode Release** | **x64** (для 64-bit) или **Win32** (для 32-bit)
- Build → Build Solution (Ctrl+Shift+B)

**Ожидаемые артефакты**:  
- **x64** в `vs.proj\x64\Unicode Release\`:
  ```
  nppColdFusion.dll        (~890 KB)
  nppColdFusion.xml        (~3.6 KB)
  nppColdFusion.db3        (~450 KB)
  ```
- **Win32** в `vs.proj\Win32\Unicode Release\`:
  ```
  nppColdFusion.dll        (~750 KB)
  nppColdFusion.xml        (~3.6 KB)
  nppColdFusion.db3        (~450 KB)
  ```

**Дымовый тест**:  
1. Скопируйте три файла в тестовый portable Notepad++:
   ```
   <test-npp>/
   ├── notepad++.exe
   └── plugins/
       ├── nppColdFusion/
       │   └── nppColdFusion.dll
       └── config/
           ├── nppColdFusion.xml
           └── nppColdFusion.db3
   ```
2. Запустите `notepad++.exe`, откройте `.cfm` файл → подсветка, сворачивание, автодополнение работают.

---

## 4. Создание пакета релизных артефактов (классическая структура)

Классическая структура релиза разделяет архитектурно-зависимые и общие ассеты:

```
release_artifacts/
├── x64/          # x64-специфичные (только DLL)
│   └── nppColdFusion.dll
├── x86/          # Win32-специфичные (только DLL)
│   └── nppColdFusion.dll
└── shared/       # Независимые от платформы
    ├── nppColdFusion.xml
    ├── nppColdFusion.db3
    ├── INSTALL.txt
    └── SHA256SUMS.txt
```

```cmd
# Из корня репозитория
mkdir release_artifacts
mkdir release_artifacts\x64
mkdir release_artifacts\x86
mkdir release_artifacts\shared

# x64 DLL
copy vs.proj\x64\Unicode Release\nppColdFusion.dll release_artifacts\x64\

# Win32 DLL
copy vs.proj\Win32\Unicode Release\nppColdFusion.dll release_artifacts\x86\

# Общие ассеты (одинаковые для обеих архитектур)
copy vs.proj\x64\Unicode Release\nppColdFusion.xml release_artifacts\shared\
copy vs.proj\x64\Unicode Release\nppColdFusion.db3 release_artifacts\shared\

# INSTALL.txt (универсальный, подходит для обеих архитектур)
echo nppColdFusion v0.9.1 - Установка> release_artifacts\shared\INSTALL.txt
echo.>> release_artifacts\shared\INSTALL.txt
echo 1. Создайте папку: %%ProgramFiles%%\Notepad++\plugins\nppColdFusion\>> release_artifacts\shared\INSTALL.txt
echo 2. Скопируйте nppColdFusion.dll (x64 или x86) туда>> release_artifacts\shared\INSTALL.txt
echo 3. Скопируйте nppColdFusion.xml и nppColdFusion.db3 в: %%AppData%%\Notepad++\plugins\config\>> release_artifacts\shared\INSTALL.txt
echo.>> release_artifacts\shared\INSTALL.txt
echo Для Portable Notepad++:>> release_artifacts\shared\INSTALL.txt
echo   Скопируйте nppColdFusion.dll в ^<Notepad++^>\plugins\nppColdFusion\>> release_artifacts\shared\INSTALL.txt
echo   Скопируйте nppColdFusion.xml и nppColdFusion.db3 в ^<Notepad++^>\plugins\config\>> release_artifacts\shared\INSTALL.txt

# SHA256 контрольные суммы (обязательны для Plugin Admin) - считаем для ВСЕХ файлов
certutil -hashfile release_artifacts\x64\nppColdFusion.dll SHA256 > release_artifacts\shared\SHA256SUMS.txt
certutil -hashfile release_artifacts\x86\nppColdFusion.dll SHA256 >> release_artifacts\shared\SHA256SUMS.txt
certutil -hashfile release_artifacts\shared\nppColdFusion.xml SHA256 >> release_artifacts\shared\SHA256SUMS.txt
certutil -hashfile release_artifacts\shared\nppColdFusion.db3 SHA256 >> release_artifacts\shared\SHA256SUMS.txt
```

**Проверьте** формат `SHA256SUMS.txt` (оставляйте только hex-строки, без подписей):
```
nppColdFusion.dll a1b2c3d4...
nppColdFusion.dll e5f6g7h8...
nppColdFusion.xml i9j0k1l2...
nppColdFusion.db3 m3n4o5p6...
```

> **Примечание**: Обе DLL (x64 и x86) перечислены в одном `SHA256SUMS.txt` с их хэшами. Plugin Admin использует первый подходящий хэш DLL для каждой архитектуры.

---

## 5. Тег и пуш в апстрим

```bash
# Убедимся, что master актуален
git fetch upstream
git checkout master
git pull upstream master

# Аннотированный тег (semver)
git tag -a v0.9.1 -m "Release v0.9.1

- Миграция на современный C++20 (Boost → std::)
- Удалены link-зависимости SQLite (runtime-only через db3)
- CI/CD исправлен (GitHub Actions + MSBuild)
- Конфигурация сборки исправлена (OutDir/IntDir для x64 Release)
- Двуязычная документация: README.md/ru.md, CHANGELOG.md/ru.md
- Автогенерируемые артефакты включены (AutoCompleteData.h, db3, xml)
- Win32 сборка включена"

# Пуш тега в АПСТРИМ (не в форк!)
git push upstream v0.9.1
```

> **Критично**: Тег должен попасть в `smishchuk/nppcoldfusion`, а не в ваш форк.

---

## 6. Создание GitHub Release (через CLI)

```bash
# Из корня репозитория (где лежит release_artifacts/)
gh release create v0.9.1 \
  --repo smishchuk/nppcoldfusion \
  --title "nppColdFusion v0.9.1" \
  --notes-file CHANGELOG.md \
  release_artifacts/x64/nppColdFusion.dll \
  release_artifacts/x86/nppColdFusion.dll \
  release_artifacts/shared/nppColdFusion.xml \
  release_artifacts/shared/nppColdFusion.db3 \
  release_artifacts/shared/INSTALL.txt \
  release_artifacts/shared/SHA256SUMS.txt
```

**Или через Web UI**:  
https://github.com/smishchuk/nppcoldfusion/releases/new → выберите тег `v0.9.1` → перетащите 6 файлов → Publish.

---

## 7. Проверка релиза

- [ ] Страница релиза показывает 6 ассетов (2 DLL + 4 общих)
- [ ] Обе `nppColdFusion.dll` скачиваются и загружаются в Notepad++
- [ ] `SHA256SUMS.txt` совпадает со скачанными файлами

---

## 8. Отправка в Notepad++ Plugin Admin (nppPluginList)

### 8.1 Форк и правка
```bash
git clone https://github.com/notepad-plus-plus/nppPluginList.git
cd nppPluginList
git checkout -b add-nppcoldfusion-0.9.1
```

### 8.2 Правка `src/pl.x64.json` (x64) и `src/pl.x86.json` (Win32)
Добавьте **новую запись** (по алфавиту по `folder-name`):

```json
// pl.x64.json
{
  "folder-name": "nppColdFusion",
  "display-name": "nppColdFusion",
  "version": "0.9.1",
  "id": "nppcoldfusion",
  "author": "Ben Bluemel / smishchuk / alsovdev",
  "homepage": "https://github.com/smishchuk/nppcoldfusion",
  "plugin-url": "https://github.com/smishchuk/nppcoldfusion/releases/download/v0.9.1/nppColdFusion.dll",
  "xml-url": "https://github.com/smishchuk/nppcoldfusion/releases/download/v0.9.1/nppColdFusion.xml",
  "checksum": "ВСТАВЬТЕ_X64_DLL_SHA256_ЗДЕСЬ_LOWERCASE_БЕЗ_ПРОБЕЛОВ",
  "description": "ColdFusion/CFML syntax highlighting, folding, auto-completion for Notepad++ x64 (v8+)",
  "npp-compatible-versions": "8.0.0 -"
}
```

```json
// pl.x86.json
{
  "folder-name": "nppColdFusion",
  "display-name": "nppColdFusion",
  "version": "0.9.1",
  "id": "nppcoldfusion",
  "author": "Ben Bluemel / smishchuk / alsovdev",
  "homepage": "https://github.com/smishchuk/nppcoldfusion",
  "plugin-url": "https://github.com/smishchuk/nppcoldfusion/releases/download/v0.9.1/nppColdFusion.dll",
  "xml-url": "https://github.com/smishchuk/nppcoldfusion/releases/download/v0.9.1/nppColdFusion.xml",
  "checksum": "ВСТАВЬТЕ_WIN32_DLL_SHA256_ЗДЕСЬ_LOWERCASE_БЕЗ_ПРОБЕЛОВ",
  "description": "ColdFusion/CFML syntax highlighting, folding, auto-completion for Notepad++ x86 (v8+)",
  "npp-compatible-versions": "8.0.0 -"
}
```

> **checksum**: скопируйте **первую строку** (хэш DLL) из `SHA256SUMS.txt` — **lowercase, без пробелов**.

### 8.3 PR и мёрж
```bash
git add src/pl.x64.json src/pl.x86.json
git commit -m "Add nppColdFusion v0.9.1 (x64 + x86)"
git push origin add-nppcoldfusion-0.9.1
# Откройте PR на GitHub → дождитесь CI (валидация схемы) → merge
```

После мёржа: плагин появится в **Plugins → Plugin Admin** в течение 24 ч.

---

## 9. Пострелизный чек-лист

| Шаг | Готово? |
|-----|---------|
| Тег `v0.9.1` запушен в `upstream/master` | ☐ |
| GitHub Release создан с 6 ассетами (2 DLL + 4 общих) | ☐ |
| Обе DLL протестированы на чистом Notepad++ | ☐ |
| `SHA256SUMS.txt` совпадает с ассетами | ☐ |
| PR в `nppPluginList` замержен (x64 + x86) | ☐ |
| `CHANGELOG.md` обновлён с версией/датой | ☐ |
| Анонс на форуме NPP / Discord (по желанию) | ☐ |

---

## 10. Автоматизация (по желанию — добавьте в `.github/workflows/build.yml`)

```yaml
# Добавьте как новый job после 'build'
release:
  needs: [build-windows, build-win32]
  if: startsWith(github.ref, 'refs/tags/v')
  runs-on: ubuntu-latest
  permissions:
    contents: write
  steps:
    - uses: actions/download-artifact@v4
      with:
        name: nppColdFusion-x64-Release
        path: artifacts/x64
    - uses: actions/download-artifact@v4
      with:
        name: nppColdFusion-Win32-Release
        path: artifacts/x86
    - name: Prepare classic release structure
      run: |
        mkdir -p release_artifacts/x64 release_artifacts/x86 release_artifacts/shared
        cp artifacts/x64/nppColdFusion.dll release_artifacts/x64/
        cp artifacts/x86/nppColdFusion.dll release_artifacts/x86/
        cp artifacts/x64/nppColdFusion.xml release_artifacts/shared/
        cp artifacts/x64/nppColdFusion.db3 release_artifacts/shared/
        cp artifacts/x64/INSTALL.txt release_artifacts/shared/
        # SHA256SUMS.txt со всеми файлами
        cd release_artifacts
        sha256sum x64/nppColdFusion.dll x86/nppColdFusion.dll shared/nppColdFusion.xml shared/nppColdFusion.db3 > shared/SHA256SUMS.txt
    - uses: softprops/action-gh-release@v1
      with:
        files: |
          release_artifacts/x64/nppColdFusion.dll
          release_artifacts/x86/nppColdFusion.dll
          release_artifacts/shared/nppColdFusion.xml
          release_artifacts/shared/nppColdFusion.db3
          release_artifacts/shared/INSTALL.txt
          release_artifacts/shared/SHA256SUMS.txt
        generate_release_notes: true
      env:
        GITHUB_TOKEN: ${{ secrets.GITHUB_TOKEN }}
```

Тогда **только шаг 5 (пуш тега)** остаётся ручным — всё остальное отрабатывает автоматически.

---

## 11. Типичные проблемы и решения

| Симптом | Лечение |
|---------|---------|
| `OutDir` отсутствует в сборке | Проверьте `vs.proj/nppColdFusion.vcxproj` — `Unicode Release|x64` должен иметь `OutDir`/`IntDir` |
| Заголовки Boost не найдены | Убедитесь, что NuGet Boost **закомментирован** в `.vcxproj`; используем только `std::` |
| Ошибка линковки `sqlite3.lib` | Удалите из `AdditionalDependencies` во всех конфигурациях — runtime-only через `db3` |
| Plugin Admin отвергает checksum | Только lowercase hex, без пробелов, **только DLL** |
| `gh release create` падает | `gh auth refresh --scopes repo,workflow` |
| Win32 LNK1181 на `.obj` | Собирайте решение с `Platform=x86` + явные `IntDir`/`OutDir` |

---

## 12. Политика версионирования

- **MAJOR** — ломающий API/ABI (маловероятно для лексического плагина)
- **MINOR** — новые теги, фичи, значимые фиксы
- **PATCH** — багфиксы, обновления доков, правки CI

Текущая: **v0.9.1** (minor — миграция на C++20 + Win32 + двуязычные доки)

---

*Храните этот файл в репозитории как `RELEASE.ru.md` для будущих майнтейнеров.*