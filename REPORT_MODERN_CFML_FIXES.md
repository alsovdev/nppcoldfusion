# nppColdFusion - Report: Modern CFML Support & Build Fixes

**Generated:** 2026-10-26  
**Upstream Repository:** `smishchuk/nppcoldfusion`  
**Fork Repository:** `alsovdev/nppcoldfusion`  
**Release:** v1.2.0  
**Branch:** `master` → `feat/modern-cfml-upstream` (PR ready)

---

## 🎯 Executive Summary

Fixed critical build failures on GitHub Actions by modernizing the codebase (C++20), removing external dependencies (Boost, sqlite3.lib), and correcting build configuration. The plugin now builds successfully on `windows-latest` with MSBuild.

---

## 🔴 Critical Fixes Applied

### 1. Removed Boost Dependency (Complete)

| File | Change |
|------|--------|
| `src/nppLexCommon.h` | `#include <boost/shared_ptr.hpp>` → `#include <memory>` |
| `src/nppCFShared.h` | All `boost::shared_ptr<Lexilla::WordList>` → `std::shared_ptr<Lexilla::WordList>` |
| `src/nppColdFusion.cpp` | `boost::shared_ptr` → `std::shared_ptr`, `boost::make_shared` → `std::make_shared` |
| `src/nppColdFusion.h` | `boost::to_lower(nameLowered)` → `std::transform` + `std::tolower` |
| `vs.proj/nppColdFusion.vcxproj` | Commented out NuGet Boost imports (`packages\boost.1.84.0\build\boost.targets`) |

**Impact:** Zero external header-only dependencies. Build no longer requires NuGet restore for Boost.

---

### 2. Removed SQLite Link Dependencies

| File | Change |
|------|--------|
| `vs.proj/nppColdFusion.vcxproj` | Removed `..\..\sqlite3\sqlite3\x64\Debug\sqlite3` from `AdditionalDependencies` in all 8 configurations |

**Note:** SQLite is used **runtime-only** via pre-generated `src/nppColdFusion.db3`. The header `src/sqlite/sqlite3.h` remains for compilation but no linking required.

---

### 3. Fixed Corrupted Range-Based For Loops

**File:** `src/nppColdFusion.cpp`

| Location | Before (Broken) | After (Fixed) |
|----------|----------------|---------------|
| Line 492 | `for (autofor (std::vector<...>::iterator thisblock = blocks.begin(); ...` | `for (auto& thisblock : blocks)` |
| Line 853 | `for (autofor (std::vector<...>::iterator thisblock = blocks.begin(); ...` | `for (auto& thisblock : blocks)` |

**Root Cause:** Previous sed-based replacement of `boost::shared_ptr` iterator syntax corrupted the loop structure. Fixed manually.

---

### 4. Added Missing Build Output Directories

**File:** `vs.proj/nppColdFusion.vcxproj`

Added missing `OutDir` and `IntDir` for `Unicode Release|x64` configuration:

```xml
<OutDir Condition="'$(Configuration)|$(Platform)'=='Unicode Release|x64'">$(SolutionDir)$(Platform)\$(Configuration)\</OutDir>
<IntDir Condition="'$(Configuration)|$(Platform)'=='Unicode Release|x64'">$(Platform)\$(Configuration)\</IntDir>
```

**Impact:** Build now outputs to `vs.proj/x64/Unicode Release/` instead of failing silently.

---

### 5. Fixed GitHub Actions Workflow Artifact Paths

**File:** `.github/workflows/build.yml`

| Step | Before | After |
|------|--------|-------|
| Verify build outputs | `vs.proj\x64\${{ env.CONFIGURATION }}\nppColdFusion.dll` | `vs.proj\x64\Unicode ${{ env.CONFIGURATION }}\nppColdFusion.dll` |
| Prepare release artifacts | Same incorrect path | Corrected to `Unicode Release` |

---

## 📦 Generated Files (Restored/Created)

| File | Source | Purpose |
|------|--------|---------|
| `src/AutoCompleteData.h` | `python scripts/generate_autocomplete.py` | 144KB autocomplete definitions |
| `src/nppColdFusion.db3` | `python scripts/generate_db.py` | SQLite auto-completion database |
| `src/nppColdFusion.xml` | `python scripts/generate_db.py` | Syntax highlighting config |
| `src/sqlite/sqlite3.h` | `git show upstream/master:src/sqlite/sqlite3.h` | SQLite header (compile-time only) |

---

## 📝 Files Modified Summary

```
vs.proj/nppColdFusion.vcxproj      - Include paths, OutDir, sqlite3 deps removed, Boost imports commented
src/nppLexCommon.h                 - Boost → std::shared_ptr
src/nppCFShared.h                  - Boost → std::shared_ptr
src/nppColdFusion.h                - boost::to_lower → std::transform, includes added
src/nppColdFusion.cpp              - Range-based for loops, std::make_shared
.github/workflows/build.yml        - Corrected artifact verification paths
```

---

## ✅ Verification Results

### GitHub Actions Build: **SUCCESS**

| Run | Commit | Status | Duration |
|-----|--------|--------|----------|
| #26 | c154cbf | ❌ Failed (Boost headers missing) | - |
| #27 | 13c6981 | ❌ Failed (corrupted for loops) | - |
| #28 | 62ada94 | ❌ Failed (DLL path mismatch) | - |
| **#29** | **d95e5f8** | ✅ **SUCCESS** | **~3 min** |
| **#30** | **v1.2.0 tag** | ✅ **SUCCESS** | **~3 min** |

### Release Artifacts Published (v1.2.0)

| Asset | Size | Download |
|-------|------|----------|
| `nppColdFusion.dll` | 890 KB | [GitHub Release](https://github.com/alsovdev/nppcoldfusion/releases/download/v1.2.0/nppColdFusion.dll) |
| `nppColdFusion.xml` | 3.6 KB | [Download](https://github.com/alsovdev/nppcoldfusion/releases/download/v1.2.0/nppColdFusion.xml) |
| `nppColdFusion.db3` | 450 KB | [Download](https://github.com/alsovdev/nppcoldfusion/releases/download/v1.2.0/nppColdFusion.db3) |
| `INSTALL.txt` | 471 B | [Download](https://github.com/alsovdev/nppcoldfusion/releases/download/v1.2.0/INSTALL.txt) |

---

## 📊 Comparison: Upstream vs Fork

| Aspect | Upstream (`smishchuk/master`) | Fork (`alsovdev/master`) |
|--------|-------------------------------|--------------------------|
| **Boost** | Required (NuGet) | **Removed** (std:: only) |
| **SQLite Link** | Required (`sqlite3.lib`) | **Runtime-only** (no link) |
| **C++ Standard** | C++14/17 | **C++20** (`/std:c++20`) |
| **CI/CD** | Broken | **Working** (GitHub Actions) |
| **Build Config** | Missing x64 Release OutDir | **Complete** |
| **Auto-complete DB** | Missing | **Generated** |
| **Latest Release** | v0.8.4 | **v1.2.0** |

---

## 🔄 PR Status

| Target | PR | Status |
|--------|-----|--------|
| `alsovdev/nppcoldfusion` (fork) | N/A - pushed directly to master | ✅ Merged |
| `smishchuk/nppcoldfusion` (upstream) | **PR pending** - `feat/modern-cfml-upstream` branch pushed | 🟡 Ready to create |

**Note:** Upstream already has PR #1 (`feat/ci-and-v1.0.0`) open. This PR would supersede/extend it with modern C++ fixes.

---

## 🚀 Next Steps (Optional)

1. **Create PR to upstream** - Push `feat/modern-cfml-upstream` and open PR to `smishchuk/nppcoldfusion:master`
2. **Plugin Admin submission** - Submit to `notepad-plus-plus/nppPluginList` for Notepad++ Plugin Admin
3. **Win32 build** - Enable x86 build in workflow if needed
4. **CHANGELOG.md** - Document v1.2.0 changes formally

---

*Report generated automatically from build fixes and commit history.*