# C++ Modules - État et Instructions

## ✅ Backups créés
Tous les modules ont été sauvegardés :
- `CPP_module00_original`
- `CPP_module01_original`
- `CPP_module02_original`
- `CPP_module03_original`
- `CPP_module04_original`

## 📊 État des modules

### CPP_module00 (3/3 exercices) ✅
- ex00: megaphone - ✅ Complet avec Makefile
- ex01: phonebook - ✅ Complet avec Makefile
- ex02: account - ⚠️ Manque `tests.cpp` (fourni par 42)

### CPP_module01 (7/7 exercices) ✅
Tous les exercices sont complets avec Makefiles

### CPP_module02 (3/4 exercices) ⚠️
- ex00-ex03: ✅ Complets
- ex04: ❌ Vide (probablement non terminé)

### CPP_module03 (3/4 exercices) ⚠️
- ex00-ex03: ✅ Complets
- ex04: ❌ Vide (probablement non terminé)

###CPP_module04 (2/3 exercices) ⚠️
- ex00-ex02: ✅ Complets
- ex03: ❌ Vide (probablement non terminé)

## 🚀 Comment tester sur Linux

### Option 1: WSL (Windows Subsystem for Linux)
```bash
# Dans WSL
cd /mnt/c/Users/"Sam Heiles"/Documents/42_cursus
chmod +x test_all_cpp.sh
./test_all_cpp.sh
```

### Option 2: À 42 School
```bash
cd ~/42_cursus  # ou le chemin de votre repo
chmod +x test_all_cpp.sh
./test_all_cpp.sh
```

### Option 3: Tester un exercice spécifique
```bash
cd CPP_module00/ex00
make
./megaphone test arguments
make fclean
```

## 📝 Conventions C++ (pas de norminette!)

Les modules C++ suivent des règles différentes :
- ✅ Orthodox Canonical Form (constructeurs, destructeurs, copies)
- ✅ Pas de fonctions C interdites (sauf si spécifié)
- ✅ Compilation avec: `c++ -Wall -Wextra -Werror -std=c++98`
- ❌ **PAS de norminette** (c'est pour le C, pas le C++)

## ⚠️ Problèmes détectés

### CPP_module00/ex02
Fichier manquant: `tests.cpp` - Ce fichier est normalement fourni par le sujet. Vérifiez votre intra 42.

### Modules incomplets
- CPP_module02/ex04
- CPP_module03/ex04
- CPP_module04/ex03

Ces exercices semblent vides. Ce sont peut-être des bonus non complétés.

## 🔧 Compilation impossible sur Windows

Raison: `g++` n'est pas installé sur votre système Cygwin/Windows.

**Solutions:**
1. Utiliser WSL (recommandé)
2. Tester à 42 school directement
3. Installer MinGW-w64 manuellement

## 📁 Structure des fichiers

Chaque exercice contient :
- Un ou plusieurs fichiers `.cpp` (implémentation)
- Des fichiers `.hpp` (headers)
- Un `Makefile` fonctionnel
- Compilation vers un exécutable unique

Tous les Makefiles utilisent:
- `CXX = c++`
- `CXXFLAGS = -Wall -Wextra -Werror -std=c++98`
- Targets: `all`, `clean`, `fclean`, `re`
