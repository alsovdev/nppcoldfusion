# nppColdFusion — Maintainer Release Guide

> **Audience**: Maintainer (`smishchuk` / `alsovdev`)  
> **Goal**: Build signed artefacts, create GitHub Release, publish to Notepad++ Plugin Admin

---

## 1. Prerequisites (one-time setup)

| Tool | Version | Notes |
|------|---------|-------|
| Windows 10/11 x64 | 21H2+ | Build host |
| Visual Studio 2022 | 17.8+ | **Desktop development with C++** workload |
| Windows 10 SDK | 10.0.19041+ | |
| Python | 3.10+ | `python -m pip install -U pip` |
| Git | 2.40+ | `git config --global core.autocrlf false` |
| GitHub CLI (`gh`) | 2.40+ | `gh auth login --scopes repo,workflow` |
| `sha256sum` / `certutil` | built-in | For checksums |

> **Tip**: Use a clean VM or GitHub Actions `windows-latest` for reproducible builds.

---

## 2. Repository layout (what to clone)

```bash
# Upstream (authoritative)
git clone https://github.com/smishchuk/nppcoldfusion.git
cd nppcoldfusion

# Add your fork as remote (for pushing tags)
git remote add fork https://github.com/alsovdev/nppcoldfusion.git
```

**Branch policy**:  
- `master` = release-ready, always green  
- Feature branches → PR → squash-merge to `master`

---

## 3. Local build (verify before tag)

```cmd
# 1. Generate autocomplete artefacts (AutoCompleteData.h, nppColdFusion.db3, nppColdFusion.xml)
python scripts/generate_autocomplete.py

# 2. Open solution
start vs.proj\nppColdFusion.sln
```

**In Visual Studio**:  
- Configuration: **Unicode Release** | **x64** (for 64-bit) or **Win32** (for 32-bit)
- Build → Build Solution (Ctrl+Shift+B)

**Expected artefacts**:  
- **x64** in `vs.proj\x64\Unicode Release\`:
  ```
  nppColdFusion.dll        (~890 KB)
  nppColdFusion.xml        (~3.6 KB)
  nppColdFusion.db3        (~450 KB)
  ```
- **Win32** in `vs.proj\Win32\Unicode Release\`:
  ```
  nppColdFusion.dll        (~750 KB)
  nppColdFusion.xml        (~3.6 KB)
  nppColdFusion.db3        (~450 KB)
  ```

**Smoke test**:  
1. Copy the three files to a test Notepad++ portable:
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
2. Run `notepad++.exe`, open a `.cfm` file → syntax highlighting, folding, autocomplete work.

---

## 4. Create release artefacts package (classic structure)

The classic release structure separates architecture-specific and shared assets:

```
release_artifacts/
├── x64/          # x64-specific (DLL only)
│   └── nppColdFusion.dll
├── x86/          # Win32-specific (DLL only)
│   └── nppColdFusion.dll
└── shared/       # Platform-independent
    ├── nppColdFusion.xml
    ├── nppColdFusion.db3
    ├── INSTALL.txt
    └── SHA256SUMS.txt
```

```cmd
# From repo root
mkdir release_artifacts
mkdir release_artifacts\x64
mkdir release_artifacts\x86
mkdir release_artifacts\shared

# x64 DLL
copy vs.proj\x64\Unicode Release\nppColdFusion.dll release_artifacts\x64\

# Win32 DLL
copy vs.proj\Win32\Unicode Release\nppColdFusion.dll release_artifacts\x86\

# Shared assets (same for both architectures)
copy vs.proj\x64\Unicode Release\nppColdFusion.xml release_artifacts\shared\
copy vs.proj\x64\Unicode Release\nppColdFusion.db3 release_artifacts\shared\

# INSTALL.txt (generic, works for both)
echo nppColdFusion v0.9.1 - Installation> release_artifacts\shared\INSTALL.txt
echo.>> release_artifacts\shared\INSTALL.txt
echo 1. Create folder: %%ProgramFiles%%\Notepad++\plugins\nppColdFusion\>> release_artifacts\shared\INSTALL.txt
echo 2. Copy nppColdFusion.dll (x64 or x86) to that folder>> release_artifacts\shared\INSTALL.txt
echo 3. Copy nppColdFusion.xml and nppColdFusion.db3 to: %%AppData%%\Notepad++\plugins\config\>> release_artifacts\shared\INSTALL.txt
echo.>> release_artifacts\shared\INSTALL.txt
echo For Portable Notepad++:>> release_artifacts\shared\INSTALL.txt
echo   Copy nppColdFusion.dll to ^<Notepad++^>\plugins\nppColdFusion\>> release_artifacts\shared\INSTALL.txt
echo   Copy nppColdFusion.xml and nppColdFusion.db3 to ^<Notepad++^>\plugins\config\>> release_artifacts\shared\INSTALL.txt

# SHA256 checksums (required for Plugin Admin) - compute on ALL files
certutil -hashfile release_artifacts\x64\nppColdFusion.dll SHA256 > release_artifacts\shared\SHA256SUMS.txt
certutil -hashfile release_artifacts\x86\nppColdFusion.dll SHA256 >> release_artifacts\shared\SHA256SUMS.txt
certutil -hashfile release_artifacts\shared\nppColdFusion.xml SHA256 >> release_artifacts\shared\SHA256SUMS.txt
certutil -hashfile release_artifacts\shared\nppColdFusion.db3 SHA256 >> release_artifacts\shared\SHA256SUMS.txt
```

**Verify** `SHA256SUMS.txt` format (keep only hex lines, no labels):
```
nppColdFusion.dll a1b2c3d4...
nppColdFusion.dll e5f6g7h8...
nppColdFusion.xml i9j0k1l2...
nppColdFusion.db3 m3n4o5p6...
```

> **Note**: Both DLLs (x64 and x86) are listed in the same SHA256SUMS.txt with their respective hashes. Plugin Admin uses the first matching DLL hash for each architecture.

---

## 5. Tag & push to upstream

```bash
# Ensure master is up-to-date
git fetch upstream
git checkout master
git pull upstream master

# Annotated tag (semver)
git tag -a v0.9.1 -m "Release v0.9.1

- Modern C++20 migration (Boost → std::)
- SQLite link deps removed (runtime-only via db3)
- CI/CD fixed (GitHub Actions + MSBuild)
- Build config fixed (OutDir/IntDir for x64 Release)
- Bilingual docs: README.md/ru.md, CHANGELOG.md/ru.md
- Auto-generated artefacts included (AutoCompleteData.h, db3, xml)
- Win32 build enabled"

# Push tag to UPSTREAM (not fork!)
git push upstream v0.9.1
```

> **Critical**: Tag must land on `smishchuk/nppcoldfusion`, not your fork.

---

## 6. Create GitHub Release (via CLI)

```bash
# From repo root (where release_artifacts/ sits)
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

**Or via Web UI**:  
https://github.com/smishchuk/nppcoldfusion/releases/new → choose tag `v0.9.1` → drag 6 files → Publish.

---

## 7. Verify Release

- [ ] Release page shows 6 assets (2 DLLs + 4 shared)
- [ ] Both `nppColdFusion.dll` download and load in Notepad++
- [ ] `SHA256SUMS.txt` matches downloaded files

---

## 8. Submit to Notepad++ Plugin Admin (nppPluginList)

### 8.1 Fork & edit
```bash
git clone https://github.com/notepad-plus-plus/nppPluginList.git
cd nppPluginList
git checkout -b add-nppcoldfusion-0.9.1
```

### 8.2 Edit `src/pl.x64.json` (x64) and `src/pl.x86.json` (Win32)
Add **new entry** (alphabetical by `folder-name`):

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
  "checksum": "PASTE_X64_DLL_SHA256_HERE_LOWERCASE_NO_SPACES",
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
  "checksum": "PASTE_WIN32_DLL_SHA256_HERE_LOWERCASE_NO_SPACES",
  "description": "ColdFusion/CFML syntax highlighting, folding, auto-completion for Notepad++ x86 (v8+)",
  "npp-compatible-versions": "8.0.0 -"
}
```

> **checksum**: copy the **first line** (DLL hash) from `SHA256SUMS.txt` — **lowercase, no spaces**.

### 8.3 PR & merge
```bash
git add src/pl.x64.json src/pl.x86.json
git commit -m "Add nppColdFusion v0.9.1 (x64 + x86)"
git push origin add-nppcoldfusion-0.9.1
# Open PR on GitHub → wait for CI (schema validation) → merge
```

After merge: plugin appears in **Plugins → Plugin Admin** within 24 h.

---

## 9. Post-release checklist

| Step | Done? |
|------|-------|
| Tag `v0.9.1` pushed to `upstream/master` | ☐ |
| GitHub Release created with 6 assets (2 DLLs + 4 shared) | ☐ |
| Both DLLs smoke-tested on clean Notepad++ | ☐ |
| `SHA256SUMS.txt` matches assets | ☐ |
| PR to `nppPluginList` merged (x64 + x86) | ☐ |
| `CHANGELOG.md` updated with version/date | ☐ |
| Announce in NPP forum / Discord (optional) | ☐ |

---

## 10. Automation (optional — add to `.github/workflows/build.yml`)

```yaml
# Add as a new job after 'build'
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
        # SHA256SUMS.txt with all files
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

Then **only step 5 (tag push)** is manual — everything else runs automatically.

---

## 11. Troubleshooting

| Symptom | Fix |
|---------|-----|
| `OutDir` missing in build | Check `vs.proj/nppColdFusion.vcxproj` — `Unicode Release|x64` must have `OutDir`/`IntDir` |
| Boost headers not found | Ensure NuGet Boost is **commented out** in `.vcxproj`; we use `std::` only |
| `sqlite3.lib` link error | Remove from `AdditionalDependencies` in all configs — runtime-only via `db3` |
| Plugin Admin rejects checksum | Lowercase hex, no spaces, **DLL only** |
| `gh release create` fails | `gh auth refresh --scopes repo,workflow` |
| Win32 LNK1181 on `.obj` | Build solution with `Platform=x86` + explicit `IntDir`/`OutDir` |

---

## 12. Versioning policy

- **MAJOR** — breaking API/ABI (unlikely for lexer plugin)
- **MINOR** — new tags, features, significant fixes
- **PATCH** — bugfixes, doc updates, CI tweaks

Current: **v0.9.1** (minor — C++20 migration + Win32 + bilingual docs)

---

*Keep this file in repo as `RELEASE.md` for future maintainers.*