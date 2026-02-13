# CPP Module 00 - Explication Détaillée des Exercices

## 📚 Vue d'ensemble du Module

**Concepts principaux :**
- Introduction au C++ (différences avec C)
- Namespaces (`std::`)
- Classes et objets
- Méthodes membres et encapsulation
- Input/Output streams (`std::cin`, `std::cout`)
- Accesseurs (getters) et mutateurs (setters)

---

## Exercice 00 : Megaphone

### 🎯 Objectif
Créer un programme qui convertit tous les arguments en majuscules et les affiche.
Si aucun argument n'est fourni, afficher un message par défaut.

### 📋 Ce que fait le programme

**Comportement :**
```bash
./megaphone "shhhhh... I think the students are asleep..."
# Sortie : SHHHHH... I THINK THE STUDENTS ARE ASLEEP...

./megaphone Damnit " ! " "Sorry students, I thought this thing was off."
# Sortie : DAMNIT ! SORRY STUDENTS, I THOUGHT THIS THING WAS OFF.

./megaphone
# Sortie : * LOUD AND UNBEARABLE FEEDBACK NOISE *
```

### 🔍 Analyse détaillée du code

#### Fonction `toUpper()`
```cpp
static std::string toUpper(const std::string &s)
{
    std::string out = s;
    for (std::string::size_type i = 0; i < out.size(); ++i)
    {
        if (out[i] >= 'a' && out[i] <= 'z')
            out[i] = static_cast<char>(out[i] - 'a' + 'A');
    }
    return out;
}
```

**Rôle :** Convertir une chaîne en majuscules

**Détails techniques :**
1. **`static`** : Fonction utilisable uniquement dans ce fichier (scope limité)
2. **`const std::string &s`** : Référence constante (évite la copie, paramètre non modifiable)
3. **`std::string out = s`** : Copie de la chaîne d'entrée
4. **`std::string::size_type`** : Type adapté pour les tailles de string (unsigned)
5. **Conversion manuelle** : 
   - Teste si le caractère est une minuscule (`'a'` à `'z'`)
   - Soustrait `'a'` pour obtenir la position dans l'alphabet (0-25)
   - Ajoute `'A'` pour obtenir la majuscule correspondante
   - `static_cast<char>` : conversion explicite du résultat en char (C++98 style)
6. **Pourquoi pas `std::toupper()` ?** : Peut dépendre de la locale, cette méthode est portable

#### Fonction `main()`
```cpp
int main(int argc, char **argv)
{
    if (argc <= 1)
    {
        std::cout << "* LOUD AND UNBEARABLE FEEDBACK NOISE *" << std::endl;
        return 0;
    }

    for (int i = 1; i < argc; ++i)
        std::cout << toUpper(argv[i]);

    std::cout << std::endl;
    return 0;
}
```

**Logique :**
1. **Pas d'arguments** (`argc <= 1`) : Affiche le message par défaut
   - `argc` = nombre d'arguments (inclut le nom du programme)
   - `argc == 1` signifie seulement `./megaphone` sans arguments
2. **Avec arguments** : Boucle sur tous les arguments
   - Commence à `i = 1` (saute `argv[0]` qui est le nom du programme)
   - Convertit chaque argument en majuscules
   - Les affiche sans espace entre eux (concaténation automatique)
3. **`std::endl`** : Retour à la ligne + flush du buffer de sortie

**Points C++ importants :**
- `std::cout` : stream de sortie standard (comme `printf` en C)
- `std::endl` : retour à la ligne ET flush (vs `\n` qui ne flush pas)
- Pas de `#include <ctype.h>` ou `toupper()` : tout est fait manuellement

---

## Exercice 01 : PhoneBook (Mon Annuaire Génial)

### 🎯 Objectif
Créer un annuaire téléphonique avec:
- **Capacité** : 8 contacts maximum (circulaire: le 9ème remplace le 1er)
- **Commandes** : ADD (ajouter), SEARCH (rechercher), EXIT (quitter)
- **Champs par contact** : Prénom, Nom, Surnom, Téléphone, Secret

### 📋 Fonctionnement général

**Commandes disponibles :**
```
ADD    : Ajoute un nouveau contact (5 champs à remplir)
SEARCH : Affiche un tableau de tous les contacts, puis permet d'en sélectionner un
EXIT   : Quitte le programme
```

**Interface SEARCH :**
```
     Index|First Name| Last Name|  Nickname
─────────────────────────────────────────
         0|      John|       Doe|     JDoe
         1|     Alice|     Smith|    Alicat
```

### 🏗️ Structure des Classes

#### Classe `Contact`

**Attributs privés :**
```cpp
std::string _firstName;
std::string _lastName;
std::string _nickname;
std::string _phoneNumber;
std::string _darkestSecret;
bool        _isSet;       // Indique si le contact est valide
```

**Méthodes publiques :**

1. **Constructeur** `Contact()`
   - Initialise tous les champs à vide
   - Met `_isSet` à `false`

2. **Destructeur** `~Contact()`
   - Libère les ressources (rien de spécial ici car std::string gère sa mémoire)

3. **Setters (mutateurs)** :
   ```cpp
   void setFirstName(const std::string &v)    // Définit le prénom
   void setLastName(const std::string &v)     // Définit le nom
   void setNickname(const std::string &v)     // Définit le surnom
   void setPhoneNumber(const std::string &v)  // Définit le téléphone
   void setDarkestSecret(const std::string &v)// Définit le secret
   void markSet(bool v)                       // Marque le contact comme valide
   ```
   **Rôle** : Modifier les attributs privés (encapsulation)

4. **Getters (accesseurs)** :
   ```cpp
   const std::string &getFirstName() const     // Retourne le prénom
   const std::string &getLastName() const      // Retourne le nom
   const std::string &getNickname() const      // Retourne le surnom
   const std::string &getPhoneNumber() const   // Retourne le téléphone
   const std::string &getDarkestSecret() const // Retourne le secret
   bool isSet() const                          // Vérifie si le contact est valide
   ```
   **Détails techniques** :
   - `const std::string &` : retourne une référence (évite la copie, plus efficace)
   - `const` à la fin : méthode ne modifie pas l'objet (promesse au compilateur)

#### Classe `PhoneBook`

**Attributs privés :**
```cpp
Contact _contacts[8];  // Tableau fixe de 8 contacts
int     _count;        // Nombre de contacts effectivement sauvegardés (0 à 8)
int     _nextIndex;    // Indice où écrire le prochain contact (0 à 7, circulaire)
```

**Méthodes publiques :**

1. **Constructeur** `PhoneBook()`
   - Initialise `_count` à 0
   - Initialise `_nextIndex` à 0
   - Les 8 contacts sont automatiquement construits (constructeur de `Contact`)

2. **Destructeur** `~PhoneBook()`
   - Les 8 contacts sont automatiquement détruits

3. **`void addContact(const Contact &c)`**
   - **Rôle** : Ajouter un contact à l'annuaire
   - **Logique** :
     ```cpp
     _contacts[_nextIndex] = c;        // Écrit dans le slot actuel
     _nextIndex = (_nextIndex + 1) % 8; // Avance (circulaire avec modulo)
     if (_count < 8) _count++;         // Incrémente le compteur jusqu'à 8
     ```
   - **Comportement circulaire** :
     - Contact 1 → index 0
     - Contact 2 → index 1
     - ...
     - Contact 8 → index 7
     - Contact 9 → index 0 (écrase le 1er)

4. **`void printTable() const`**
   - **Rôle** : Afficher le tableau de tous les contacts
   - **Format** : Colonnes de 10 caractères alignées à droite
   - **Troncature** : Si un champ > 10 caractères, affiche les 9 premiers + '.'
   - **Exemple** :
     ```
          Index|First Name| Last Name|  Nickname
     ─────────────────────────────────────────
              0|  Jonathan|     Smith|     Jonny
              1|     Alice|  Verylong.|    Alicat
     ```

5. **`void printContact(int index) const`**
   - **Rôle** : Afficher les détails complets d'un contact
   - **Affiche** : Tous les champs sans troncature
   - **Exemple** :
     ```
     First name: Jonathan
     Last name: Smith
     Nickname: Jonny
     Phone number: 555-1234
     Darkest secret: Afraid of spiders
     ```

6. **`int count() const`**
   - **Rôle** : Retourner le nombre de contacts actuels
   - **Utilité** : Savoir si l'annuaire est vide ou combien de contacts existent

### 🔍 Analyse détaillée de `main.cpp`

#### Fonctions utilitaires

1. **`readLine(const std::string &prompt, std::string &out)`**
   ```cpp
   static bool readLine(const std::string &prompt, std::string &out)
   {
       std::cout << prompt;
       if (!std::getline(std::cin, out))
           return false;  // EOF ou erreur
       return true;
   }
   ```
   - **Rôle** : Afficher un prompt et lire une ligne
   - **Gestion EOF** : Retourne `false` si `Ctrl+D` (Unix) ou `Ctrl+Z` (Windows)
   - **Paramètre `out`** : Référence non-const, sera modifiée avec la ligne lue

2. **`readNonEmptyField(const std::string &prompt)`**
   ```cpp
   static std::string readNonEmptyField(const std::string &prompt)
   {
       std::string s;
       while (true)
       {
           if (!readLine(prompt, s))
               return std::string();  // EOF : retourne chaîne vide
           if (!s.empty())
               return s;
           std::cout << "Field cannot be empty." << std::endl;
       }
   }
   ```
   - **Rôle** : Lire un champ non vide (redemande tant que vide)
   - **Boucle infinie** : `while(true)` avec `return` pour sortir
   - **Validation** : Refuse les chaînes vides

3. **`isDigitsSpacesPlus(const std::string &s)`**
   ```cpp
   static bool isDigitsSpacesPlus(const std::string &s)
   {
       for (std::string::size_type i = 0; i < s.size(); ++i)
       {
           char c = s[i];
           if ((c >= '0' && c <= '9') || c == ' ' || c == '+' || 
               c == '-' || c == '(' || c == ')' || c == '.')
               continue;
           return false;
       }
       return !s.empty();
   }
   ```
   - **Rôle** : Valider qu'un numéro de téléphone ne contient que des caractères autorisés
   - **Caractères acceptés** : chiffres, espaces, +, -, (, ), .
   - **Exemples valides** : "555-1234", "+33 6 12 34 56 78", "(555) 123-4567"

4. **`readPhone(const std::string &prompt)`**
   - **Rôle** : Lire un numéro de téléphone valide
   - **Validation** : Appelle `isDigitsSpacesPlus()`

5. **`parseIndex1to8(const std::string &s)`**
   ```cpp
   static int parseIndex1to8(const std::string &s)
   {
       std::istringstream iss(s);
       int x;
       char extra;
       if (!(iss >> x))        // Essaie de lire un entier
           return -1;
       if (iss >> extra)       // Vérifie qu'il n'y a pas de caractères en trop
           return -1;
       if (x < 1 || x > 8)     // Vérifie la plage
           return -1;
       return x;
   }
   ```
   - **Rôle** : Convertir une chaîne en index (1-8)
   - **Validation stricte** :
     - Doit être un nombre entier unique
     - Refuse "3abc" (caractères en trop)
     - Refuse "0" ou "9" (hors plage)
   - **`std::istringstream`** : Stream d'entrée depuis une string (comme `sscanf` en C)

#### Boucle principale

```cpp
int main()
{
    PhoneBook pb;              // Créé l'annuaire
    std::string cmd;

    while (true)               // Boucle infinie
    {
        std::cout << "Enter command (ADD, SEARCH, EXIT): ";
        if (!std::getline(std::cin, cmd))
            break;             // EOF : quitte

        if (cmd == "EXIT")
            break;
        else if (cmd == "ADD")
        {
            // Lecture des 5 champs
            Contact c;
            std::string fn = readNonEmptyField("First name: ");
            if (std::cin.eof()) break;
            // ... (idem pour les autres champs)
            
            c.setFirstName(fn);
            // ... (idem pour les autres champs)
            c.markSet(true);
            pb.addContact(c);
            std::cout << "Contact added successfully." << std::endl;
        }
        else if (cmd == "SEARCH")
        {
            if (pb.count() == 0)
            {
                std::cout << "Phonebook is empty." << std::endl;
                continue;
            }
            
            pb.printTable();   // Affiche le tableau
            
            std::string indexStr;
            if (!readLine("Enter index (1-8): ", indexStr))
                break;
            
            int idx = parseIndex1to8(indexStr);
            if (idx == -1)
            {
                std::cout << "Invalid index." << std::endl;
                continue;
            }
            
            pb.printContact(idx - 1);  // idx - 1 car utilisateur entre 1-8, internal 0-7
        }
        else
        {
            std::cout << "Invalid command." << std::endl;
        }
    }

    std::cout << "Goodbye!" << std::endl;
    return 0;
}
```

**Flux d'exécution :**

1. **Création de l'annuaire** : `PhoneBook pb;`
2. **Boucle infinie** : Attend une commande
3. **Commande ADD** :
   - Crée un `Contact` temporaire
   - Lit les 5 champs (avec validation)
   - Vérifie EOF après chaque lecture
   - Ajoute le contact à l'annuaire
4. **Commande SEARCH** :
   - Vérifie que l'annuaire n'est pas vide
   - Affiche le tableau
   - Demande un index (1-8)
   - Valide et affiche le contact
5. **Commande EXIT** : Sort de la boucle
6. **Gestion EOF** : `Ctrl+D` ou `Ctrl+Z` sort du programme proprement

**Points C++ importants :**

- **`std::getline(std::cin, str)`** : Lit une ligne complète (contrairement à `cin >> str` qui s'arrête aux espaces)
- **`std::cin.eof()`** : Teste si on a atteint la fin du flux d'entrée
- **`std::istringstream`** : Parse une string comme un flux d'entrée
- **Encapsulation** : Les attributs `_contacts`, `_count`, `_nextIndex` sont privés, accessibles uniquement via les méthodes
- **Références constantes** : `const std::string &` pour éviter les copies inutiles

---

## Exercice 02 : Account (Gestion de Comptes Bancaires)

### 🎯 Objectif
Implémenter une classe `Account` en se basant sur un fichier header fourni.
Reproduire exactement le comportement d'un log de comptes bancaires avec horodatage.

### 📋 Ce que fait le programme

**Fonctionnalités :**
- Créer des comptes avec un dépôt initial
- Effectuer des dépôts et retraits
- Afficher l'état de chaque compte
- Afficher les informations globales (total, nb comptes, etc.)
- Logger chaque action avec un timestamp

**Format de sortie attendu :**
```
[19920104_091532] index:0;amount:42;created
[19920104_091532] index:1;amount:54;created
...
[19920104_091532] accounts:8;total:20049;deposits:0;withdrawals:0
[19920104_091532] index:0;amount:42;deposits:0;withdrawals:0
...
[19920104_091532] index:0;p_amount:42;deposit:5;amount:47;nb_deposits:1
...
```

### 🏗️ Structure de la Classe `Account`

**Attributs privés statiques (partagés par toutes les instances) :**
```cpp
static int _nbAccounts;         // Nombre total de comptes
static int _totalAmount;        // Somme totale dans tous les comptes
static int _totalNbDeposits;    // Nombre total de dépôts
static int _totalNbWithdrawals; // Nombre total de retraits
```

**Attributs privés d'instance (spécifiques à chaque compte) :**
```cpp
int _accountIndex;   // Numéro du compte (0, 1, 2...)
int _amount;         // Montant actuel dans ce compte
int _nbDeposits;     // Nombre de dépôts effectués sur ce compte
int _nbWithdrawals;  // Nombre de retraits effectués sur ce compte
```

### 🔍 Analyse détaillée des Méthodes

#### Méthodes Statiques (Classe)

1. **`static int getNbAccounts(void)`**
   - **Rôle** : Retourner le nombre total de comptes
   - **Implémentation** : `return _nbAccounts;`

2. **`static int getTotalAmount(void)`**
   - **Rôle** : Retourner la somme totale de tous les comptes
   - **Implémentation** : `return _totalAmount;`

3. **`static int getNbDeposits(void)`**
   - **Rôle** : Retourner le nombre total de dépôts
   - **Implémentation** : `return _totalNbDeposits;`

4. **`static int getNbWithdrawals(void)`**
   - **Rôle** : Retourner le nombre total de retraits
   - **Implémentation** : `return _totalNbWithdrawals;`

5. **`static void displayAccountsInfos(void)`**
   - **Rôle** : Afficher les informations globales
   - **Format** : `[timestamp] accounts:X;total:Y;deposits:Z;withdrawals:W`
   - **Exemple** :
     ```cpp
     _displayTimestamp();
     std::cout << " accounts:" << _nbAccounts
               << ";total:" << _totalAmount
               << ";deposits:" << _totalNbDeposits
               << ";withdrawals:" << _totalNbWithdrawals
               << std::endl;
     ```

6. **`static void _displayTimestamp(void)`** (privée)
   - **Rôle** : Afficher l'horodatage actuel
   - **Format** : `[YYYYMMDD_HHMMSS]`
   - **Implémentation typique** :
     ```cpp
     time_t now = time(0);
     tm* ltm = localtime(&now);
     std::cout << "[" 
               << (1900 + ltm->tm_year)
               << (ltm->tm_mon + 1 < 10 ? "0" : "") << (ltm->tm_mon + 1)
               << (ltm->tm_mday < 10 ? "0" : "") << ltm->tm_mday
               << "_"
               << (ltm->tm_hour < 10 ? "0" : "") << ltm->tm_hour
               << (ltm->tm_min < 10 ? "0" : "") << ltm->tm_min
               << (ltm->tm_sec < 10 ? "0" : "") << ltm->tm_sec
               << "]";
     ```
   - **Libraries nécessaires** : `<ctime>` ou `<time.h>`

#### Méthodes d'Instance

1. **`Account(int initial_deposit)` (Constructeur)**
   - **Rôle** : Créer un nouveau compte
   - **Logique** :
     ```cpp
     _accountIndex = _nbAccounts;      // Assigne l'index
     _amount = initial_deposit;        // Définit le montant initial
     _nbDeposits = 0;
     _nbWithdrawals = 0;
     
     _nbAccounts++;                    // Incrémente le compteur global
     _totalAmount += initial_deposit;  // Ajoute au total global
     
     _displayTimestamp();
     std::cout << " index:" << _accountIndex
               << ";amount:" << _amount
               << ";created" << std::endl;
     ```
   - **Variables statiques** : Chaque instance incrémente `_nbAccounts` et `_totalAmount`

2. **`~Account(void)` (Destructeur)**
   - **Rôle** : Détruire un compte
   - **Logique** :
     ```cpp
     _displayTimestamp();
     std::cout << " index:" << _accountIndex
               << ";amount:" << _amount
               << ";closed" << std::endl;
     ```
   - **Note** : Ne décrémente PAS `_nbAccounts` (comportement attendu par le sujet)

3. **`void makeDeposit(int deposit)`**
   - **Rôle** : Effectuer un dépôt
   - **Logique** :
     ```cpp
     int p_amount = _amount;           // Sauvegarde l'ancien montant
     _amount += deposit;               // Ajoute le dépôt
     _nbDeposits++;                    // Incrémente le compteur local
     _totalAmount += deposit;          // Ajoute au total global
     _totalNbDeposits++;               // Incrémente le compteur global
     
     _displayTimestamp();
     std::cout << " index:" << _accountIndex
               << ";p_amount:" << p_amount
               << ";deposit:" << deposit
               << ";amount:" << _amount
               << ";nb_deposits:" << _nbDeposits
               << std::endl;
     ```

4. **`bool makeWithdrawal(int withdrawal)`**
   - **Rôle** : Effectuer un retrait
   - **Retour** : `true` si succès, `false` si refusé (fonds insuffisants)
   - **Logique** :
     ```cpp
     int p_amount = _amount;
     
     _displayTimestamp();
     std::cout << " index:" << _accountIndex
               << ";p_amount:" << p_amount
               << ";withdrawal:";
     
     if (_amount >= withdrawal)
     {
         _amount -= withdrawal;
         _nbWithdrawals++;
         _totalAmount -= withdrawal;
         _totalNbWithdrawals++;
         
         std::cout << withdrawal
                   << ";amount:" << _amount
                   << ";nb_withdrawals:" << _nbWithdrawals
                   << std::endl;
         return true;
     }
     else
     {
         std::cout << "refused" << std::endl;
         return false;
     }
     ```

5. **`int checkAmount(void) const`**
   - **Rôle** : Retourner le montant actuel
   - **Implémentation** : `return _amount;`
   - **`const`** : Promet de ne pas modifier l'objet

6. **`void displayStatus(void) const`**
   - **Rôle** : Afficher l'état du compte
   - **Format** : `[timestamp] index:X;amount:Y;deposits:Z;withdrawals:W`
   - **Implémentation** :
     ```cpp
     _displayTimestamp();
     std::cout << " index:" << _accountIndex
               << ";amount:" << _amount
               << ";deposits:" << _nbDeposits
               << ";withdrawals:" << _nbWithdrawals
               << std::endl;
     ```

### 💡 Concepts C++ Importants

**Variables Statiques :**
```cpp
// Dans Account.cpp (pas le .hpp !)
int Account::_nbAccounts = 0;
int Account::_totalAmount = 0;
int Account::_totalNbDeposits = 0;
int Account::_totalNbWithdrawals = 0;
```
- **Déclaration** : Dans le `.hpp` avec `static`
- **Définition** : Dans le `.cpp` avec `ClassName::varName = value`
- **Portée** : Partagée par toutes les instances de la classe
- **Utilité** : Compter le nombre d'objets, maintenir des totaux globaux

**Méthodes Statiques vs Instance :**
- **Statique** : Appelée sur la classe (`Account::getNbAccounts()`)
- **Instance** : Appelée sur un objet (`account.makeDeposit(50)`)

**Ordre de Construction/Destruction :**
1. Variables statiques initialisées au démarrage du programme
2. Constructeur appelé pour chaque `Account` créé
3. Destructeur appelé à la fin de la portée ou lors d'un `delete`
4. Variables statiques persistent jusqu'à la fin du programme

**Exemple d'utilisation :**
```cpp
int main()
{
    Account acc1(42);           // Crée compte 0 avec 42€
    Account acc2(54);           // Crée compte 1 avec 54€
    
    Account::displayAccountsInfos();  // Affiche totaux : 2 comptes, 96€
    
    acc1.makeDeposit(5);        // Dépôt de 5€ : 42 → 47
    acc2.makeWithdrawal(10);    // Retrait de 10€ : 54 → 44
    
    acc1.displayStatus();       // Affiche état du compte 1
    
    return 0;                   // Destructeurs appelés ici
}
```

---

## 📖 Résumé des Concepts du Module 00

### Ce que vous avez appris

1. **Bases du C++**
   - `#include <iostream>` et `std::cout`
   - `std::string` (meilleur que `char*` en C)
   - `std::endl` vs `\n`

2. **Classes et Encapsulation**
   - Attributs privés (`private:`)
   - Méthodes publiques (`public:`)
   - Constructeur et destructeur
   - Getters et setters

3. **Références**
   - `const std::string &` : référence constante (pas de copie)
   - Différence avec les pointeurs

4. **Méthodes const**
   - `void method() const` : promesse de ne pas modifier l'objet
   - Permet d'appeler la méthode sur des objets constants

5. **Variables et Méthodes Statiques**
   - `static` : partagé par toutes les instances
   - Utile pour compter, maintenir des totaux

6. **Input/Output Streams**
   - `std::cin` : entrée standard
   - `std::cout` : sortie standard
   - `std::getline()` : lire une ligne complète
   - `std::istringstream` : parser une string

7. **Validation d'Entrées**
   - Boucles de validation
   - Gestion de l'EOF
   - Conversion string → int

### Différences majeures avec le C

| C | C++ |
|---|-----|
| `printf()` | `std::cout <<` |
| `scanf()` | `std::cin >>` ou `std::getline()` |
| `char*` / `char[]` | `std::string` |
| Structures + fonctions | Classes (structure + méthodes) |
| Pas d'encapsulation | `private`/`public` |
| Pas de références | Références `&` |
| `malloc()`/`free()` | `new`/`delete` (pas encore vu) |

---

## ✅ Checklist de Validation

- [x] **ex00** : Megaphone convertit en majuscules
- [x] **ex01** : PhoneBook gère 8 contacts circulaires
- [x] **ex01** : Commandes ADD, SEARCH, EXIT fonctionnent
- [x] **ex01** : Tableau avec troncature à 10 caractères
- [x] **ex02** : Logs avec timestamps corrects
- [x] **ex02** : Variables statiques correctement gérées
- [x] **ex02** : Dépôts et retraits modifient les totaux

---

**Module 00 terminé !** Vous maîtrisez maintenant les bases du C++ orienté objet. 🎉
