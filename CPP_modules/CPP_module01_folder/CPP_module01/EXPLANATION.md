# CPP Module 01 - Explication Détaillée des Exercices

## 📚 Vue d'ensemble du Module

**Concepts principaux :**
- Allocation mémoire dynamique (`new` / `delete`)
- Stack vs Heap
- Pointeurs vs Références
- Pointeurs vers membres de classe
- Gestion de fichiers (`std::ifstream`, `std::ofstream`)
- Switch statement

---

## Exercice 00 : BraiiiiiiinnnzzzZ

### 🎯 Objectif
Comprendre la différence entre l'allocation sur la **stack** et sur le **heap**.
Créer des zombies et comprendre quand utiliser `new`/`delete`.

### 📋 Ce que fait le programme

**Comportement :**
```bash
./zombie
# Sortie :
# StackZombie: BraiiiiinnnzzzZ...
# HeapZombie: BraiiiiinnnzzzZ...
```

**Différence clé :**
- **Stack zombie** : Détruit automatiquement à la fin de la fonction
- **Heap zombie** : Doit être détruit manuellement avec `delete`

### 🏗️ Structure

#### Classe `Zombie`

**Attributs privés :**
```cpp
std::string _name;  // Nom du zombie
```

**Méthodes publiques :**

1. **`Zombie(std::string name)`** - Constructeur
   ```cpp
   Zombie::Zombie(std::string name) : _name(name)
   {
       std::cout << _name << " is created" << std::endl;
   }
   ```
   - **Liste d'initialisation** : `: _name(name)` initialise `_name` directement
   - Plus efficace que `_name = name;` dans le corps

2. **`~Zombie(void)`** - Destructeur
   ```cpp
   Zombie::~Zombie(void)
   {
       std::cout << _name << " is destroyed" << std::endl;
   }
   ```
   - Appelé automatiquement quand le zombie est détruit
   - Utile pour débugger les fuites mémoire

3. **`void announce(void)`**
   ```cpp
   void Zombie::announce(void)
   {
       std::cout << _name << ": BraiiiiinnnzzzZ..." << std::endl;
   }
   ```
   - Fait annoncer le zombie

#### Fonctions Globales

1. **`Zombie* newZombie(std::string name)`**
   ```cpp
   Zombie* newZombie(std::string name)
   {
       return new Zombie(name);  // Allocation sur le HEAP
   }
   ```
   - **Rôle** : Créer un zombie sur le heap
   - **`new Zombie(name)`** : Alloue la mémoire dynamiquement
   - **Retourne un pointeur** : Le zombie persiste après la fin de la fonction
   - **⚠️ IMPORTANT** : L'appelant DOIT faire `delete` !

2. **`void randomChump(std::string name)`**
   ```cpp
   void randomChump(std::string name)
   {
       Zombie zombie(name);  // Allocation sur la STACK
       zombie.announce();
   }  // Zombie détruit automatiquement ici
   ```
   - **Rôle** : Créer un zombie temporaire sur la stack
   - **Destruction automatique** : Le destructeur est appelé à la fin des accolades
   - **Usage** : Pour des objets temporaires qui n'ont pas besoin de persister

### 🔍 Analyse du `main()`

```cpp
int main(void)
{
    // Stack allocated zombie
    randomChump("StackZombie");
    // StackZombie créé et détruit immédiatement après announce()

    // Heap allocated zombie
    Zombie* heapZombie = newZombie("HeapZombie");
    heapZombie->announce();
    delete heapZombie;  // ⚠️ OBLIGATOIRE : libère la mémoire
    // Sans delete : FUITE MÉMOIRE !

    return 0;
}
```

### 💡 Concepts Clés

**Stack vs Heap :**

| Stack | Heap |
|-------|------|
| `Zombie z("name");` | `Zombie* z = new Zombie("name");` |
| Destruction automatique | `delete z;` obligatoire |
| Rapide | Plus lent |
| Taille limitée | Grande taille disponible |
| Portée limitée (fonction) | Persiste jusqu'au `delete` |

**Quand utiliser quoi ?**
- **Stack** : Objets temporaires, petits objets, scope limité
- **Heap** : Objets qui doivent persister, grande taille, scope global

**Syntaxe Pointeurs :**
```cpp
Zombie* ptr = new Zombie("Bob");
ptr->announce();     // Utilise ->
(*ptr).announce();   // Équivalent (déréférencement puis .)
delete ptr;
```

---

## Exercice 01 : Moar brainz!

### 🎯 Objectif
Créer un tableau (horde) de zombies alloué dynamiquement.
Tous les zombies doivent avoir le même nom.

### 📋 Ce que fait le programme

**Fonction à implémenter :**
```cpp
Zombie* zombieHorde(int N, std::string name);
```

**Comportement :**
```cpp
Zombie* horde = zombieHorde(10, "Zombie");
// Crée 10 zombies tous nommés "Zombie"
for (int i = 0; i < 10; i++)
    horde[i].announce();
delete[] horde;  // ⚠️ delete[] pour les tableaux !
```

### 🏗️ Structure

#### Classe `Zombie` (modifiée)

**Nouveau constructeur :**
```cpp
Zombie::Zombie(void) : _name("")
{
    // Constructeur par défaut nécessaire pour new[]
}
```
- **Pourquoi ?** `new Zombie[N]` appelle le constructeur par défaut N fois
- Sans constructeur par défaut, compilation échoue !

**Nouvelle méthode :**
```cpp
void Zombie::setName(std::string name)
{
    _name = name;
}
```
- **Rôle** : Définir le nom après la construction

#### Fonction `zombieHorde()`

```cpp
Zombie* zombieHorde(int N, std::string name)
{
    Zombie* horde = new Zombie[N];  // Alloue un tableau de N zombies
    
    for (int i = 0; i < N; i++)
        horde[i].setName(name);     // Nomme chaque zombie
    
    return horde;
}
```

**Détails :**
1. **`new Zombie[N]`** : Alloue N objets contiguës en mémoire
2. **Appelle le constructeur par défaut** N fois
3. **Retourne un pointeur** vers le premier élément
4. **Accès aux éléments** : `horde[0]`, `horde[1]`, ..., `horde[N-1]`

### 🔍 Analyse du `main()` typique

```cpp
int main(void)
{
    int N = 5;
    Zombie* horde = zombieHorde(N, "HordeZombie");
    
    for (int i = 0; i < N; i++)
        horde[i].announce();
    
    delete[] horde;  // ⚠️ delete[] pour les tableaux !
    // Sans [] : comportement indéfini, fuites mémoire
    
    return 0;
}
```

### 💡 Concepts Clés

**`new` vs `new[]` :**

| Single Object | Array |
|--------------|-------|
| `Zombie* z = new Zombie("Bob");` | `Zombie* arr = new Zombie[10];` |
| `delete z;` | `delete[] arr;` |
| Appelle 1 constructeur | Appelle N constructeurs |
| Appelle 1 destructeur | Appelle N destructeurs |

**⚠️ ERREUR FRÉQUENTE :**
```cpp
Zombie* horde = new Zombie[5];
delete horde;      // ❌ MAUVAIS : fuite de 4 zombies !
delete[] horde;    // ✅ BON : détruit les 5 zombies
```

**Constructeur par défaut :**
- Si vous définissez un constructeur avec paramètres, le compilateur ne génère PAS de constructeur par défaut
- Solution : Déclarez explicitement `Zombie(void);`

---

## Exercice 02 : HI THIS IS BRAIN

### 🎯 Objectif
Comprendre la différence entre **pointeurs** et **références**.

### 📋 Ce que fait le programme

**Code complet :**
```cpp
int main(void)
{
    std::string str = "HI THIS IS BRAIN";
    std::string* stringPTR = &str;       // Pointeur
    std::string& stringREF = str;        // Référence

    std::cout << "String address: " << &str << std::endl;
    std::cout << "Pointer address: " << stringPTR << std::endl;
    std::cout << "Reference address: " << &stringREF << std::endl;
    std::cout << std::endl;
    std::cout << "String value: " << str << std::endl;
    std::cout << "Pointer value: " << *stringPTR << std::endl;
    std::cout << "Reference value: " << stringREF << std::endl;

    return 0;
}
```

**Sortie :**
```
String address: 0x7ffc12345678
Pointer address: 0x7ffc12345678
Reference address: 0x7ffc12345678

String value: HI THIS IS BRAIN
Pointer value: HI THIS IS BRAIN
Reference value: HI THIS IS BRAIN
```

### 🔍 Analyse

**Pointeur :**
```cpp
std::string* stringPTR = &str;
```
- **Type** : `std::string*` (pointeur vers string)
- **Valeur** : Adresse mémoire de `str`
- **Accès** : `*stringPTR` (déréférencement)
- **Peut être `NULL`** : Oui
- **Peut changer** : `stringPTR = &other;`

**Référence :**
```cpp
std::string& stringREF = str;
```
- **Type** : `std::string&` (référence vers string)
- **Valeur** : Alias de `str` (même adresse)
- **Accès** : `stringREF` (pas de déréférencement)
- **Peut être `NULL`** : Non
- **Peut changer** : Non (liée à vie)

### 💡 Comparaison Pointeurs vs Références

| Caractéristique | Pointeur | Référence |
|-----------------|----------|-----------|
| Syntaxe déclaration | `int* ptr` | `int& ref` |
| Initialisation | Optionnelle | **Obligatoire** |
| Peut être NULL | ✅ Oui | ❌ Non |
| Réassignable | ✅ Oui | ❌ Non |
| Accès valeur | `*ptr` | `ref` directement |
| Arithmétique | ✅ `ptr++` | ❌ Impossible |
| Usage typique | Tableaux, optionnel | Alias, paramètres |

**Exemple d'usage :**
```cpp
void increment(int* ptr)    // Pointeur : peut être NULL
{
    if (ptr != NULL)
        (*ptr)++;
}

void increment(int& ref)    // Référence : jamais NULL
{
    ref++;                  // Plus simple, pas de check
}
```

---

## Exercice 03 : Unnecessary violence

### 🎯 Objectif
Implémenter deux classes `HumanA` et `HumanB` qui utilisent une arme (`Weapon`).
**HumanA** a TOUJOURS une arme (référence).
**HumanB** peut ne PAS avoir d'arme (pointeur).

### 📋 Ce que fait le programme

**Classes :**
- `Weapon` : Arme avec un type (ex: "crude spiked club")
- `HumanA` : Humain avec une arme **obligatoire**
- `HumanB` : Humain avec une arme **optionnelle**

**Test attendu :**
```cpp
{
    Weapon club = Weapon("crude spiked club");
    HumanA bob("Bob", club);
    bob.attack();
    club.setType("some other type of club");
    bob.attack();
}
{
    Weapon club = Weapon("crude spiked club");
    HumanB jim("Jim");
    jim.setWeapon(club);
    jim.attack();
    club.setType("some other type of club");
    jim.attack();
}
```

**Sortie attendue :**
```
Bob attacks with their crude spiked club
Bob attacks with their some other type of club
Jim attacks with their crude spiked club
Jim attacks with their some other type of club
```

### 🏗️ Structure

#### Classe `Weapon`

```cpp
class Weapon
{
private:
    std::string _type;

public:
    Weapon(std::string type);
    ~Weapon(void);

   const std::string& getType(void) const;
    void setType(std::string newType);
};
```

**Méthodes :**

1. **`Weapon(std::string type)`**
   ```cpp
   Weapon::Weapon(std::string type) : _type(type) {}
   ```

2. **`const std::string& getType(void) const`**
   ```cpp
   const std::string& Weapon::getType(void) const
   {
       return _type;  // Retourne une référence constante (pas de copie)
   }
   ```
   - **`const std::string&`** : Évite la copie, lecture seule
   - **`const` à la fin** : Méthode ne modifie pas l'objet

3. **`void setType(std::string newType)`**
   ```cpp
   void Weapon::setType(std::string newType)
   {
       _type = newType;
   }
   ```

#### Classe `HumanA` (Arme OBLIGATOIRE)

```cpp
class HumanA
{
private:
    std::string _name;
    Weapon& _weapon;  // ⚠️ RÉFÉRENCE : arme obligatoire

public:
    HumanA(std::string name, Weapon& weapon);
    ~HumanA(void);

    void attack(void) const;
};
```

**Implémentation :**

1. **Constructeur**
   ```cpp
   HumanA::HumanA(std::string name, Weapon& weapon)
       : _name(name), _weapon(weapon)
   {
       // Liste d'initialisation OBLIGATOIRE pour les références
   }
   ```
   - **Pourquoi liste d'initialisation ?** Les références DOIVENT être initialisées à la déclaration
   - Impossible de faire `_weapon = weapon;` dans le corps

2. **`void attack(void) const`**
   ```cpp
   void HumanA::attack(void) const
   {
       std::cout << _name << " attacks with their "
                 << _weapon.getType() << std::endl;
   }
   ```
   - **`const`** : Promesse de ne pas modifier `_name` ni `_weapon`

#### Classe `HumanB` (Arme OPTIONNELLE)

```cpp
class HumanB
{
private:
    std::string _name;
    Weapon* _weapon;  // ⚠️ POINTEUR : arme optionnelle

public:
    HumanB(std::string name);
    ~HumanB(void);

    void setWeapon(Weapon& weapon);
    void attack(void) const;
};
```

**Implémentation :**

1. **Constructeur**
   ```cpp
   HumanB::HumanB(std::string name) : _name(name), _weapon(NULL)
   {
       // Pas de paramètre weapon : initialise à NULL
   }
   ```
   - **En C++98** : Utiliser `NULL` (pas `nullptr` qui est C++11)

2. **`void setWeapon(Weapon& weapon)`**
   ```cpp
   void HumanB::setWeapon(Weapon& weapon)
   {
       _weapon = &weapon;  // Stocke l'adresse de l'arme
   }
   ```

3. **`void attack(void) const`**
   ```cpp
   void HumanB::attack(void) const
   {
       if (_weapon == NULL)
           std::cout << _name << " has no weapon!" << std::endl;
       else
           std::cout << _name << " attacks with their "
                     << _weapon->getType() << std::endl;
   }
   ```
   - **Check NULL** : Obligatoire car l'arme est optionnelle !

### 🔍 Analyse du `main()`

```cpp
int main(void)
{
    {
        Weapon club = Weapon("crude spiked club");
        
        HumanA bob("Bob", club);  // Bob DOIT avoir une arme
        bob.attack();
        
        club.setType("some other type of club");
        bob.attack();  // Bob voit le changement (référence)
    }
    {
        Weapon club = Weapon("crude spiked club");
        
        HumanB jim("Jim");        // Jim n'a pas encore d'arme
        jim.attack();             // "Jim has no weapon!"
        
        jim.setWeapon(club);      // Donne une arme à Jim
        jim.attack();
        
        club.setType("some other type of club");
        jim.attack();             // Jim voit le changement (pointeur)
    }
    
    return 0;
}
```

### 💡 Concepts Clés

**Quand utiliser Référence vs Pointeur ?**

| Situation | Solution |
|-----------|----------|
| Attribut OBLIGATOIRE | Référence `&` |
| Attribut OPTIONNEL | Pointeur `*` |
| Ne change jamais | Référence `&` |
| Peut changer | Pointeur `*` |
| Pas de NULL possible | Référence `&` |
| NULL possible | Pointeur `*` |

**Initialisation des références :**
```cpp
class Example
{
    int& _ref;  // Référence
    
    // ❌ ERREUR : ne compile pas
    Example(int& r)
    {
        _ref = r;  // Trop tard ! La référence doit être initialisée
    }
    
    // ✅ BON
    Example(int& r) : _ref(r)  // Liste d'initialisation
    {
    }
};
```

---

## Exercice 04 : Sed is for losers

### 🎯 Objectif
Créer un programme qui remplace toutes les occurrences d'une chaîne (`s1`) par une autre (`s2`) dans un fichier.
Créer un fichier `<filename>.replace` avec le résultat.

### 📋 Ce que fait le programme

**Usage :**
```bash
./replace file.txt "old" "new"
# Crée file.txt.replace avec toutes les occurrences de "old" remplacées par "new"
```

**Exemple :**
```bash
echo "Hello world, world!" > test.txt
./replace test.txt "world" "universe"
cat test.txt.replace
# Sortie : Hello universe, universe!
```

### 🏗️ Implémentation

**Fichier unique : `main.cpp`**

```cpp
#include <iostream>
#include <fstream>
#include <string>

int main(int argc, char** argv)
{
    if (argc != 4)
    {
        std::cerr << "Usage: " << argv[0] << " <filename> <s1> <s2>" << std::endl;
        return 1;
    }

    std::string filename = argv[1];
    std::string s1 = argv[2];
    std::string s2 = argv[3];

    if (s1.empty())
    {
        std::cerr << "Error: s1 cannot be empty" << std::endl;
        return 1;
    }

    std::ifstream inputFile(filename.c_str());
    if (!inputFile.is_open())
    {
        std::cerr << "Error: cannot open file " << filename << std::endl;
        return 1;
    }

    std::string outputFilename = filename + ".replace";
    std::ofstream outputFile(outputFilename.c_str());
    if (!outputFile.is_open())
    {
        std::cerr << "Error: cannot create output file " << outputFilename << std::endl;
        inputFile.close();
        return 1;
    }

    std::string line;
    while (std::getline(inputFile, line))
    {
        size_t pos = 0;
        while ((pos = line.find(s1, pos)) != std::string::npos)
        {
            line.erase(pos, s1.length());
            line.insert(pos, s2);
            pos += s2.length();
        }
        outputFile << line << std::endl;
    }

    inputFile.close();
    outputFile.close();

    std::cout << "File processed successfully: " << outputFilename << std::endl;

    return 0;
}
```

### 🔍 Analyse Détaillée

#### 1. Gestion des Arguments

```cpp
if (argc != 4)
{
    std::cerr << "Usage: " << argv[0] << " <filename> <s1> <s2>" << std::endl;
    return 1;
}

std::string filename = argv[1];
std::string s1 = argv[2];
std::string s2 = argv[3];
```
- **`argc`** : Nombre d'arguments (inclut le nom du programme)
- **`argv`** : Tableau de chaînes C (`char*`)
- **Conversion automatique** : `argv[1]` → `std::string`

#### 2. Validation

```cpp
if (s1.empty())
{
    std::cerr << "Error: s1 cannot be empty" << std::endl;
    return 1;
}
```
- **Pourquoi ?** `find("")` trouve TOUJOURS une occurrence → boucle infinie !

#### 3. Ouverture du Fichier d'Entrée

```cpp
std::ifstream inputFile(filename.c_str());
if (!inputFile.is_open())
{
    std::cerr << "Error: cannot open file " << filename << std::endl;
    return 1;
}
```
- **`std::ifstream`** : Input File Stream (lecture)
- **`.c_str()`** : C++98 nécessite un `const char*` (pas `std::string`)
- **`.is_open()`** : Vérifie si l'ouverture a réussi

#### 4. Création du Fichier de Sortie

```cpp
std::string outputFilename = filename + ".replace";
std::ofstream outputFile(outputFilename.c_str());
if (!outputFile.is_open())
{
    std::cerr << "Error: cannot create output file " << outputFilename << std::endl;
    inputFile.close();  // ⚠️ N'oublie pas de fermer inputFile !
    return 1;
}
```
- **`std::ofstream`** : Output File Stream (écriture)
- **Gestion d'erreur** : Ferme le fichier d'entrée avant de quitter

#### 5. Boucle de Remplacement

```cpp
std::string line;
while (std::getline(inputFile, line))  // Lit ligne par ligne
{
    size_t pos = 0;
    while ((pos = line.find(s1, pos)) != std::string::npos)  // Cherche s1
    {
        line.erase(pos, s1.length());    // Supprime s1
        line.insert(pos, s2);            // Insère s2
        pos += s2.length();              // Avance après s2
    }
    outputFile << line << std::endl;     // Écrit la ligne modifiée
}
```

**Détails :**

1. **`std::getline(inputFile, line)`**
   - Lit une ligne complète (jusqu'au `\n`)
   - Retourne `false` à la fin du fichier

2. **`line.find(s1, pos)`**
   - Cherche `s1` dans `line` à partir de `pos`
   - Retourne l'index si trouvé
   - Retourne `std::string::npos` si non trouvé (constante spéciale = valeur maximale de `size_t`)

3. **`line.erase(pos, s1.length())`**
   - Supprime `s1.length()` caractères à partir de `pos`

4. **`line.insert(pos, s2)`**
   - Insère `s2` à la position `pos`

5. **`pos += s2.length()`**
   - Avance après `s2` pour éviter de le traiter à nouveau
   - **Important** : Si `s2` contient `s1`, évite la boucle infinie
   - Exemple : remplacer "a" par "aa" dans "aaa"
     - Sans avance : "aaa" → "aaaa" → "aaaaa" → ... (infini)
     - Avec avance : "aaa" → "aaaa" → "aaaaa" → "aaaaaa" (3 remplacements)

#### 6. Fermeture des Fichiers

```cpp
inputFile.close();
outputFile.close();
```
- **Optionnel** : Les destructeurs ferment automatiquement
- **Bonne pratique** : Fermer explicitement

### 💡 Concepts Clés

**Gestion de Fichiers en C++:**

| Classe | Usage | Mode |
|--------|-------|------|
| `std::ifstream` | Lecture | Input |
| `std::ofstream` | Écriture | Output |
| `std::fstream` | Lecture/Écriture | Input/Output |

**Méthodes importantes :**
```cpp
std::ifstream file("file.txt");
file.is_open();           // Vérifie si ouvert
std::getline(file, str);  // Lit une ligne
file >> x;                // Lit un mot/nombre
file.eof();               // Vérifie fin de fichier
file.close();             // Ferme
```

**`std::string::npos` :**
- Valeur spéciale = "pas trouvé"
- Égale à la valeur maximale de `size_t` (généralement `-1` en unsigned)
- Utilisée par `find()`, `rfind()`, `find_first_of()`, etc.

**Erreurs fréquentes :**
```cpp
// ❌ MAUVAIS : boucle infinie si s1 vide
while ((pos = line.find(s1)) != std::string::npos)
{
    line.replace(pos, s1.length(), s2);
}

// ✅ BON : valide s1 non vide ET avance la position
if (!s1.empty())
{
    while ((pos = line.find(s1, pos)) != std::string::npos)
    {
        line.erase(pos, s1.length());
        line.insert(pos, s2);
        pos += s2.length();  // Important !
    }
}
```

---

## Exercice 05 : Harl 2.0

### 🎯 Objectif
Créer une classe `Harl` qui se plaint à différents niveaux (DEBUG, INFO, WARNING, ERROR).
Utiliser des **pointeurs vers fonctions membres** pour appeler la bonne méthode.

### 📋 Ce que fait le programme

**Comportement :**
```cpp
Harl harl;
harl.complain("DEBUG");
harl.complain("INFO");
harl.complain("WARNING");
harl.complain("ERROR");
harl.complain("UNKNOWN");  // Ne fait rien
```

**Sortie :**
```
[ DEBUG ]
I love having extra bacon for my 7XL-double-cheese-triple-pickle-special-ketchup burger. I really do!
[ INFO ]
I cannot believe adding extra bacon costs more money...
[ WARNING ]
I think I deserve to have some extra bacon for free...
[ ERROR ]
This is unacceptable! I want to speak to the manager now.
```

### 🏗️ Structure

#### Classe `Harl`

```cpp
class Harl
{
private:
    void debug(void);
    void info(void);
    void warning(void);
    void error(void);

public:
    Harl(void);
    ~Harl(void);

    void complain(std::string level);
};
```

#### Méthodes Privées

```cpp
void Harl::debug(void)
{
    std::cout << "[ DEBUG ]" << std::endl;
    std::cout << "I love having extra bacon for my 7XL-double-cheese-triple-pickle-special-ketchup burger. I really do!" << std::endl;
}

void Harl::info(void)
{
    std::cout << "[ INFO ]" << std::endl;
    std::cout << "I cannot believe adding extra bacon costs more money..." << std::endl;
}

void Harl::warning(void)
{
    std::cout << "[ WARNING ]" << std::endl;
    std::cout << "I think I deserve to have some extra bacon for free..." << std::endl;
}

void Harl::error(void)
{
    std::cout << "[ ERROR ]" << std::endl;
    std::cout << "This is unacceptable! I want to speak to the manager now." << std::endl;
}
```

#### Méthode `complain()` - LE CŒUR DE L'EXERCICE

```cpp
void Harl::complain(std::string level)
{
    // 1. Définition du type de pointeur vers fonction membre
    typedef void (Harl::*HarlMemFuncPtr)(void);

    // 2. Tableau de pointeurs vers fonctions membres
    HarlMemFuncPtr funcs[4] = {
        &Harl::debug,
        &Harl::info,
        &Harl::warning,
        &Harl::error
    };

    // 3. Tableau de noms correspondants
    std::string levels[4] = {
        "DEBUG",
        "INFO",
        "WARNING",
        "ERROR"
    };

    // 4. Cherche le niveau et appelle la fonction
    for (int i = 0; i < 4; i++)
    {
        if (levels[i] == level)
        {
            (this->*funcs[i])();  // ⚠️ Syntaxe spéciale !
            return;
        }
    }
    
    // Si niveau non trouvé, ne fait rien
}
```

### 🔍 Analyse Détaillée - Pointeurs vers Fonctions Membres

#### 1. Déclaration du Type

```cpp
typedef void (Harl::*HarlMemFuncPtr)(void);
```

**Décomposition :**
- `void` : Type de retour
- `Harl::` : Classe à laquelle la méthode appartient
- `*HarlMemFuncPtr` : Nom du type de pointeur
- `(void)` : Paramètres de la fonction

**Équivalent sans typedef :**
```cpp
void (Harl::*ptr)(void) = &Harl::debug;  // Compliqué à lire !
```

#### 2. Création du Tableau

```cpp
HarlMemFuncPtr funcs[4] = {
    &Harl::debug,
    &Harl::info,
    &Harl::warning,
    &Harl::error
};
```

**Points clés :**
- **`&Harl::debug`** : Adresse de la méthode `debug` de la classe `Harl`
- **PAS d'instance** : On stocke l'adresse de la méthode, pas d'un objet
- **Tableau de pointeurs** : Comme un tableau de pointeurs de fonctions en C, mais pour des méthodes

#### 3. Appel de la Fonction

```cpp
(this->*funcs[i])();
```

**Syntaxe complexe décomposée :**
1. **`this`** : Pointeur vers l'objet courant (obligatoire)
2. **`->*`** : Opérateur de déréférencement de pointeur vers membre
3. **`funcs[i]`** : Le pointeur vers la fonction membre
4. **`()`** : Appel de la fonction

**Pourquoi `->*` et pas just `->` ?**
- **`->`** : Accès à un membre (variable ou méthode) directement
- **`->*`** : Déréférence un *pointeur* vers membre

**Exemples équivalents :**
```cpp
// Avec this (pointeur)
(this->*funcs[i])();

// Avec un objet (référence)
Harl& harl = *this;
(harl.*funcs[i])();

// Appel direct (sans tableau)
(this->*(&Harl::debug))();

// Ou plus simplement
this->debug();
```

#### 4. Alternatives (moins "C++98 style")

**Avec if/else :**
```cpp
void Harl::complain(std::string level)
{
    if (level == "DEBUG")
        debug();
    else if (level == "INFO")
        info();
    else if (level == "WARNING")
        warning();
    else if (level == "ERROR")
        error();
}
```
- ❌ **Problème** : Répétitif, pas élégant
- ✅ **Avantage** : Plus simple à lire

**Avec switch (exercice 06) :**
- Nécessite de convertir string → enum
- Voir exercice suivant

### 💡 Concepts Clés

**Pointeurs vers Fonctions Membres :**

| Type | Syntaxe | Appel |
|------|---------|-------|
| Fonction globale | `void (*ptr)()` | `(*ptr)()` ou `ptr()` |
| Méthode de classe | `void (Class::*ptr)()` | `(obj.*ptr)()` ou `(ptr_obj->*ptr)()` |

**Pourquoi utiliser des pointeurs vers fonctions membres ?**
- Éviter les longues chaînes de `if/else`
- Table de dispatch (comme un `switch` mais avec des strings)
- Pattern Command/Strategy
- Callbacks

**Syntaxe complète :**
```cpp
// Déclaration
typedef ReturnType (ClassName::*PointerName)(ParamType1, ParamType2);

// Assignation
PointerName ptr = &ClassName::methodName;

// Appel avec objet
ClassName obj;
(obj.*ptr)(arg1, arg2);

// Appel avec pointeur vers objet
ClassName* ptrObj = &obj;
(ptrObj->*ptr)(arg1, arg2);
```

---

## Exercice 06 : Harl filter

### 🎯 Objectif
Filtrer les plaintes de Harl selon un niveau minimum.
Utiliser un **switch statement** avec fall-through.

### 📋 Ce que fait le programme

**Usage :**
```bash
./harlFilter "WARNING"
```

**Comportement :**
- Affiche WARNING, ERROR (et tous les niveaux supérieurs)
- Ignore DEBUG, INFO (niveaux inférieurs)

**Sortie avec "WARNING" :**
```
[ WARNING ]
I think I deserve to have some extra bacon for free...
[ ERROR ]
This is unacceptable! I want to speak to the manager now.
```

**Sortie avec "DEBUG" :**
```
[ DEBUG ]
I love having extra bacon...
[ INFO ]
I cannot believe...
[ WARNING ]
I think I deserve...
[ ERROR ]
This is unacceptable!
```

**Sortie avec niveau invalide :**
```
[ Probably complaining about insignificant problems ]
```

### 🏗️ Implémentation

**Classe `Harl` identique à l'exercice 05.**

**`main.cpp` :**

```cpp
#include "Harl.hpp"
#include <iostream>
#include <string>

int main(int argc, char** argv)
{
    if (argc != 2)
    {
        std::cerr << "Usage: " << argv[0] << " <level>" << std::endl;
        return 1;
    }

    std::string level = argv[1];
    Harl harl;

    // Conversion string → int pour le switch
    int levelIndex = -1;
    if (level == "DEBUG") levelIndex = 0;
    else if (level == "INFO") levelIndex = 1;
    else if (level == "WARNING") levelIndex = 2;
    else if (level == "ERROR") levelIndex = 3;

    // Switch avec fall-through
    switch (levelIndex)
    {
        case 0:
            harl.complain("DEBUG");
            // Pas de break : continue vers INFO
        case 1:
            harl.complain("INFO");
            // Pas de break : continue vers WARNING
        case 2:
            harl.complain("WARNING");
            // Pas de break : continue vers ERROR
        case 3:
            harl.complain("ERROR");
            break;  // Fin
        default:
            std::cout << "[ Probably complaining about insignificant problems ]" << std::endl;
    }

    return 0;
}
```

### 🔍 Analyse Détaillée

#### 1. Conversion String → Int

```cpp
int levelIndex = -1;
if (level == "DEBUG") levelIndex = 0;
else if (level == "INFO") levelIndex = 1;
else if (level == "WARNING") levelIndex = 2;
else if (level == "ERROR") levelIndex = 3;
```

**Pourquoi ?**
- `switch` ne fonctionne qu'avec des **types entiers** (int, char, enum)
- `switch(string)` ne compile pas en C++98 ! (C++11+)

**Alternative avec map (C++98) :**
```cpp
std::map<std::string, int> levelMap;
levelMap["DEBUG"] = 0;
levelMap["INFO"] = 1;
levelMap["WARNING"] = 2;
levelMap["ERROR"] = 3;

int levelIndex = levelMap[level];  // 0 si non trouvé
```

#### 2. Switch avec Fall-Through

```cpp
switch (levelIndex)
{
    case 0:
        harl.complain("DEBUG");
        // ⚠️ PAS DE BREAK : continue vers case 1
    case 1:
        harl.complain("INFO");
        // ⚠️ PAS DE BREAK : continue vers case 2
    case 2:
        harl.complain("WARNING");
        // ⚠️ PAS DE BREAK : continue vers case 3
    case 3:
        harl.complain("ERROR");
        break;  // Arrête ici
    default:
        std::cout << "[ Probably complaining about insignificant problems ]" << std::endl;
}
```

**Fall-Through :**
- **Normalement** : `break` après chaque `case`
- **Ici** : Volontairement omis pour exécuter tous les cas suivants
- **Utile** : Quand les cas sont cumulatifs (chaque niveau inclut les suivants)

**Exemple d'exécution avec "WARNING" (levelIndex = 2) :**
1. Saute `case 0` et `case 1`
2. Entre dans `case 2` :
   - Exécute `harl.complain("WARNING")`
   - **Pas de break** → continue
3. Entre dans `case 3` :
   - Exécute `harl.complain("ERROR")`
   - **Break** → sort du switch

### 💡 Concepts Clés

**Switch Statement :**

```cpp
switch (expression)  // Expression doit être un entier (int, char, enum)
{
    case value1:
        // Code si expression == value1
        break;  // Sort du switch
    
    case value2:
        // Code si expression == value2
        break;
    
    default:
        // Code si aucun case ne correspond
        break;  // Optionnel
}
```

**Fall-Through Volontaire :**
```cpp
switch (x)
{
    case 1:
    case 2:
    case 3:
        // Exécuté si x == 1 OU x == 2 OU x == 3
        break;
}
```

**Fall-Through Cumulatif (comme ici) :**
```cpp
switch (x)
{
    case 1:
        doA();
        // Pas de break : fait aussi B, C, D
    case 2:
        doB();
        // Pas de break : fait aussi C, D
    case 3:
        doC();
        // Pas de break : fait aussi D
    case 4:
        doD();
        break;
}
```

**Différences switch vs if/else :**

| `switch` | `if/else` |
|----------|-----------|
| Types entiers uniquement | N'importe quelle condition |
| Compile vers jump table (rapide) | Comparaisons séquentielles |
| Fall-through naturel | Pas de fall-through |
| Moins de duplication | Plus de duplication |

**Erreurs fréquentes :**
```cpp
// ❌ ERREUR : switch sur string (C++98)
switch (level)  // level est std::string
{
    case "DEBUG":  // Ne compile pas !
}

// ❌ ERREUR : oubli de break non intentionnel
switch (x)
{
    case 1:
        doA();
        // Oubli de break : doB() exécuté aussi !
    case 2:
        doB();
}

// ✅ BON : commentaire si fall-through intentionnel
switch (x)
{
    case 1:
        doA();
        // Fallthrough intentionnel
    case 2:
        doB();
        break;
}
```

---

## 📖 Résumé des Concepts du Module 01

### Ce que vous avez appris

1. **Allocation Dynamique**
   - `new` / `delete` (objet unique)
   - `new[]` / `delete[]` (tableau)
   - Stack vs Heap

2. **Pointeurs vs Références**
   - Pointeurs : `*`, peuvent être NULL, réassignables
   - Références : `&`, jamais NULL, liées à vie
   - Quand utiliser l'un ou l'autre

3. **Pointeurs vers Membres de Classe**
   - `void (Class::*ptr)()`
   - `(obj.*ptr)()`
   - `(ptr->*ptr)()`

4. **Gestion de Fichiers**
   - `std::ifstream` (lecture)
   - `std::ofstream` (écriture)
   - `std::getline()`, `.is_open()`, `.close()`

5. **Switch Statement**
   - Types entiers uniquement
   - Fall-through volontaire
   - Conversion string → int pour utiliser switch

6. **Constructeurs Spéciaux**
   - Constructeur par défaut
   - Liste d'initialisation
   - Initialisation des références (obligatoire en liste)

### Différences importantes

| C | C++ |
|---|-----|
| `malloc()`/`free()` | `new`/`delete` |
| `FILE*`, `fopen()` | `std::ifstream`/`std::ofstream` |
| Pointeurs uniquement | Pointeurs ET références |
| Pas de pointeurs vers fonctions membres | `(obj.*ptr)()` |

---

## ✅ Checklist de Validation

- [x] **ex00** : Zombies stack vs heap, `delete` obligatoire
- [x] **ex01** : Tableau de zombies avec `new[]` et `delete[]`
- [x] **ex02** : Différence pointeurs/références démontrée
- [x] **ex03** : HumanA (référence), HumanB (pointeur)
- [x] **ex04** : Remplacement de strings dans un fichier
- [x] **ex05** : Pointeurs vers fonctions membres
- [x] **ex06** : Switch avec fall-through

---

**Module 01 terminé !** Vous maîtrisez maintenant la gestion mémoire, les pointeurs/références, et les fichiers en C++. 🎉
