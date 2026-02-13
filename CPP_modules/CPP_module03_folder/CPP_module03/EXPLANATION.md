# CPP Module 03 - Explication Détaillée des Exercices

## 📚 Vue d'ensemble du Module

**Concepts principaux :**
- **Héritage simple** : Une classe dérive d'une autre
- **Héritage multiple** : Une classe dérive de plusieurs classes
- **Diamond Problem** : Problème d'héritage en diamant
- **Virtual inheritance** : Solution au Diamond Problem
- **Protected members** : Accessibilité intermédiaire entre private et public

---

## 🎓 Introduction à l'Héritage

### Qu'est-ce que l'héritage ?

**Définition :**
- Mécanisme permettant à une classe (dérivée/enfant) d'hériter des attributs et méthodes d'une autre classe (base/parent)
- Relation "est-un" : `ScavTrap` **est un** `ClapTrap`

**Syntaxe :**
```cpp
class Base {
    // Attributs et méthodes de base
};

class Derived : public Base {
    // Hérite de Base + ajoute ses propres membres
};
```

**Types d'accès à l'héritage :**
```cpp
class Derived : public Base     // public reste public, protected reste protected
class Derived : protected Base  // public et protected deviennent protected
class Derived : private Base    // tout devient private
```

**Note :** Dans ce module, on utilise toujours `public` inheritance.

### Niveaux d'accès

| Modificateur | Classe elle-même | Classes dérivées | Extérieur |
|--------------|------------------|------------------|-----------|
| `private` | ✅ | ❌ | ❌ |
| `protected` | ✅ | ✅ | ❌ |
| `public` | ✅ | ✅ | ✅ |

---

## Exercice 00 : Aaaaand... OPEN!

### 🎯 Objectif
Créer une classe `ClapTrap` qui représente un robot de combat.
C'est la classe de base pour tous les exercices suivants.

### 📋 Ce que fait ClapTrap

**Attributs :**
- **Name** : Nom du robot
- **Hit points** : Points de vie (10 au départ)
- **Energy points** : Points d'énergie (10 au départ)
- **Attack damage** : Dégâts d'attaque (0 au départ)

**Actions :**
- **attack()** : Attaque une cible (coûte 1 énergie)
- **takeDamage()** : Subit des dégâts (réduit HP)
- **beRepaired()** : Se répare (coûte 1 énergie, gagne HP)

**Règles :**
- Pas d'énergie → Impossible d'attaquer ou se réparer
- 0 HP → Mort, ne peut plus rien faire

### 🏗️ Structure de ClapTrap

```cpp
class ClapTrap
{
protected:  // ⚠️ protected : accessible aux classes dérivées
    std::string _name;
    unsigned int _hitPoints;
    unsigned int _energyPoints;
    unsigned int _attackDamage;

public:
    ClapTrap(void);                          // Constructeur par défaut
    ClapTrap(const std::string &name);       // Constructeur avec nom
    ClapTrap(const ClapTrap &copy);          // Copy constructor
    ClapTrap &operator=(const ClapTrap &rhs);// Assignment operator
    ~ClapTrap(void);                         // Destructeur

    void attack(const std::string &target);
    void takeDamage(unsigned int amount);
    void beRepaired(unsigned int amount);
};
```

### 🔍 Analyse Détaillée

#### 1. Constructeur par Défaut

```cpp
ClapTrap::ClapTrap(void) 
    : _name("Default"), _hitPoints(10), _energyPoints(10), _attackDamage(0)
{
    std::cout << "ClapTrap " << this->_name << " created! (Default constructor)" << std::endl;
}
```

**Rôle :**
- Initialise un ClapTrap avec des valeurs par défaut
- **Liste d'initialisation** : Plus efficace que l'assignation dans le corps

#### 2. Constructeur avec Paramètre

```cpp
ClapTrap::ClapTrap(const std::string &name) 
    : _name(name), _hitPoints(10), _energyPoints(10), _attackDamage(0)
{
    std::cout << "ClapTrap " << this->_name << " created!" << std::endl;
}
```

**Usage :**
```cpp
ClapTrap robot("R2D2");  // Crée un ClapTrap nommé "R2D2"
```

#### 3. Méthode `attack()`

```cpp
void ClapTrap::attack(const std::string &target)
{
    if (this->_hitPoints == 0)
    {
        std::cout << "ClapTrap " << this->_name << " is dead and can't attack!" << std::endl;
        return;
    }
    if (this->_energyPoints == 0)
    {
        std::cout << "ClapTrap " << this->_name << " has no energy left!" << std::endl;
        return;
    }
    this->_energyPoints--;
    std::cout << "ClapTrap " << this->_name << " attacks " << target 
              << ", causing " << this->_attackDamage << " points of damage!" << std::endl;
}
```

**Logique :**
1. **Vérifie si mort** (HP = 0) : Bloque l'action
2. **Vérifie l'énergie** (EP = 0) : Bloque l'action
3. **Consomme 1 énergie**
4. **Affiche l'attaque** (les dégâts réels sont gérés par `takeDamage()`)

#### 4. Méthode `takeDamage()`

```cpp
void ClapTrap::takeDamage(unsigned int amount)
{
    if (this->_hitPoints <= amount)
    {
        this->_hitPoints = 0;
        std::cout << "ClapTrap " << this->_name << " takes " << amount 
                  << " damage and dies!" << std::endl;
    }
    else
    {
        this->_hitPoints -= amount;
        std::cout << "ClapTrap " << this->_name << " takes " << amount 
                  << " damage. HP: " << this->_hitPoints << std::endl;
    }
}
```

**Logique :**
- Si dégâts ≥ HP : Mort (HP = 0)
- Sinon : Réduit HP

#### 5. Méthode `beRepaired()`

```cpp
void ClapTrap::beRepaired(unsigned int amount)
{
    if (this->_hitPoints == 0)
    {
        std::cout << "ClapTrap " << this->_name << " is dead and can't be repaired!" << std::endl;
        return;
    }
    if (this->_energyPoints == 0)
    {
        std::cout << "ClapTrap " << this->_name << " has no energy left!" << std::endl;
        return;
    }
    this->_energyPoints--;
    this->_hitPoints += amount;
    std::cout << "ClapTrap " << this->_name << " repairs itself, gaining " << amount 
              << " hit points. HP: " << this->_hitPoints << std::endl;
}
```

**Logique :**
1. Vérifie si mort : Bloque
2. Vérifie l'énergie : Bloque
3. Consomme 1 énergie
4. Gagne des HP

### 💡 Concepts Clés

**Protected vs Private :**
```cpp
class Base {
private:
    int _private;    // ❌ Inaccessible aux classes dérivées

protected:
    int _protected;  // ✅ Accessible aux classes dérivées

public:
    int _public;     // ✅ Accessible partout
};
```

**unsigned int :**
- Entier non signé (≥ 0)
- Évite les HP ou énergie négatifs
- `unsigned int` sur 32 bits : 0 à 4'294'967'295

---

## Exercice 01 : Serena, my love!

### 🎯 Objectif
Créer une classe `ScavTrap` qui hérite de `ClapTrap`.
ScavTrap a des stats différentes et une fonction spéciale.

### 📋 Différences ScavTrap vs ClapTrap

| Attribut | ClapTrap | ScavTrap |
|----------|----------|----------|
| Hit Points | 10 | 100 |
| Energy Points | 10 | 50 |
| Attack Damage | 0 | 20 |
| Fonction spéciale | - | `guardGate()` |

### 🏗️ Structure de ScavTrap

```cpp
class ScavTrap : public ClapTrap  // ⚠️ : public ClapTrap
{
public:
    ScavTrap(void);
    ScavTrap(const std::string &name);
    ScavTrap(const ScavTrap &copy);
    ScavTrap &operator=(const ScavTrap &rhs);
    ~ScavTrap(void);

    void attack(const std::string &target);  // Override
    void guardGate(void);                    // Nouvelle fonction
};
```

### 🔍 Analyse Détaillée

#### 1. Constructeur par Défaut

```cpp
ScavTrap::ScavTrap(void) : ClapTrap()  // ⚠️ Appelle le constructeur de ClapTrap
{
    this->_hitPoints = 100;     // Modifie les valeurs héritées
    this->_energyPoints = 50;
    this->_attackDamage = 20;
    std::cout << "ScavTrap default constructor called" << std::endl;
}
```

**Séquence d'appel :**
1. **`ClapTrap()`** est appelé en premier (classe de base)
2. **Corps de `ScavTrap()`** est exécuté
3. Les valeurs de `ClapTrap` sont modifiées

**Sortie console :**
```
ClapTrap Default created! (Default constructor)
ScavTrap default constructor called
```

#### 2. Constructeur avec Paramètre

```cpp
ScavTrap::ScavTrap(const std::string &name) : ClapTrap(name)
{
    this->_hitPoints = 100;
    this->_energyPoints = 50;
    this->_attackDamage = 20;
    std::cout << "ScavTrap constructor called" << std::endl;
}
```

**Usage :**
```cpp
ScavTrap robot("ST-3V3");
// Sortie :
// ClapTrap ST-3V3 created!
// ScavTrap constructor called
```

#### 3. Copy Constructor

```cpp
ScavTrap::ScavTrap(const ScavTrap &copy) : ClapTrap(copy)
{
    std::cout << "ScavTrap copy constructor called" << std::endl;
}
```

**Détails :**
- **`ClapTrap(copy)`** : Appelle le copy constructor de `ClapTrap`
- `copy` est un `ScavTrap` mais accepté par `ClapTrap(const ClapTrap &)` (upcasting)
- Copie automatiquement `_hitPoints`, `_energyPoints`, `_attackDamage`, `_name`

#### 4. Assignment Operator

```cpp
ScavTrap &ScavTrap::operator=(const ScavTrap &rhs)
{
    std::cout << "ScavTrap copy assignment operator called" << std::endl;
    ClapTrap::operator=(rhs);  // ⚠️ Appelle l'assignment de la classe de base
    return *this;
}
```

**Pourquoi appeler `ClapTrap::operator=()` ?**
- Copie les attributs hérités (`_name`, `_hitPoints`, etc.)
- Évite la duplication de code
- Utilise la logique déjà implémentée dans la classe de base

#### 5. Destructeur

```cpp
ScavTrap::~ScavTrap(void)
{
    std::cout << "ScavTrap destructor called" << std::endl;
}
```

**Séquence de destruction :**
1. **`~ScavTrap()`** est appelé
2. **`~ClapTrap()`** est appelé automatiquement après

**Sortie console :**
```
ScavTrap destructor called
ClapTrap ST-3V3 destroyed!
```

**⚠️ Ordre inverse** de la construction !

#### 6. Override de `attack()`

```cpp
void ScavTrap::attack(const std::string &target)
{
    if (this->_hitPoints == 0)
    {
        std::cout << "ScavTrap " << this->_name << " is dead and can't attack!" << std::endl;
        return;
    }
    if (this->_energyPoints == 0)
    {
        std::cout << "ScavTrap " << this->_name << " has no energy left!" << std::endl;
        return;
    }
    this->_energyPoints--;
    std::cout << "ScavTrap " << this->_name << " attacks " << target 
              << ", causing " << this->_attackDamage << " points of damage!" << std::endl;
}
```

**Différence avec `ClapTrap::attack()` :**
- Affiche "ScavTrap" au lieu de "ClapTrap"
- Même logique, message différent

**Appel :**
```cpp
ScavTrap st("Bob");
st.attack("Enemy");  // Appelle ScavTrap::attack(), pas ClapTrap::attack()
```

#### 7. Fonction Spéciale `guardGate()`

```cpp
void ScavTrap::guardGate(void)
{
    std::cout << "ScavTrap " << this->_name << " is now in Gatekeeper mode!" << std::endl;
}
```

**Rôle :**
- Fonction unique à `ScavTrap`
- `ClapTrap` n'a pas cette fonction

**Usage :**
```cpp
ScavTrap st("Guardian");
st.guardGate();  // OK
ClapTrap ct("Basic");
ct.guardGate();  // ❌ ERREUR : ClapTrap n'a pas guardGate()
```

### 💡 Concepts Clés

**Ordre de construction/destruction :**
```
Construction : Base → Dérivée
Destruction :  Dérivée → Base
```

**Upcasting (conversion implicite) :**
```cpp
ScavTrap st("Bob");
ClapTrap& ct = st;  // OK : ScavTrap EST UN ClapTrap
ct.attack("Enemy"); // ⚠️ Appelle ClapTrap::attack() (pas de virtual !)
```

**Accès aux membres protected :**
```cpp
this->_hitPoints = 100;  // OK : _hitPoints est protected dans ClapTrap
```

---

## Exercice 02 : Repetitive work

### 🎯 Objectif
Créer une classe `FragTrap` qui hérite aussi de `ClapTrap`.
Même principe que `ScavTrap` mais avec des stats et une fonction différentes.

### 📋 Différences FragTrap vs ClapTrap

| Attribut | ClapTrap | FragTrap |
|----------|----------|----------|
| Hit Points | 10 | 100 |
| Energy Points | 10 | 100 |
| Attack Damage | 0 | 30 |
| Fonction spéciale | - | `highFivesGuys()` |

### 🏗️ Structure de FragTrap

```cpp
class FragTrap : public ClapTrap
{
public:
    FragTrap(void);
    FragTrap(const std::string &name);
    FragTrap(const ScavTrap &copy);
    FragTrap &operator=(const FragTrap &rhs);
    ~FragTrap(void);

    void attack(const std::string &target);  // Override
    void highFivesGuys(void);                // Nouvelle fonction
};
```

### 🔍 Implémentation (similaire à ScavTrap)

**Constructeur :**
```cpp
FragTrap::FragTrap(const std::string &name) : ClapTrap(name)
{
    this->_hitPoints = 100;
    this->_energyPoints = 100;
    this->_attackDamage = 30;
    std::cout << "FragTrap constructor called" << std::endl;
}
```

**Fonction spéciale :**
```cpp
void FragTrap::highFivesGuys(void)
{
    std::cout << "FragTrap " << this->_name << " requests a high five!" << std::endl;
}
```

### 💡 Hiérarchie Actuelle

```
        ClapTrap
         /    \
        /      \
   ScavTrap  FragTrap
```

- **ScavTrap** et **FragTrap** sont frères (siblings)
- Les deux héritent de **ClapTrap**
- Pas d'interaction directe entre ScavTrap et FragTrap

---

## Exercice 03 : Now it's weird! (BONUS - Diamond Problem)

### 🎯 Objectif
Créer une classe `DiamondTrap` qui hérite à la fois de `ScavTrap` ET `FragTrap`.
Résoudre le **Diamond Problem** avec **virtual inheritance**.

### 📋 Le Diamond Problem

**Hiérarchie sans virtual :**
```
        ClapTrap
         /    \
        /      \
   ScavTrap  FragTrap
        \      /
         \    /
       DiamondTrap
```

**Problème :**
- `DiamondTrap` hérite de `ScavTrap` et `FragTrap`
- `ScavTrap` et `FragTrap` héritent tous deux de `ClapTrap`
- **Résultat** : `DiamondTrap` a **2 copies** de `ClapTrap` !

**Conséquences :**
```cpp
DiamondTrap dt;
dt._name = "Bob";  // ❌ ERREUR : Ambiguïté ! Quel _name ?
                   // ScavTrap::ClapTrap::_name ou FragTrap::ClapTrap::_name ?
```

**Solution : Virtual Inheritance**
```cpp
class ScavTrap : virtual public ClapTrap { /* ... */ };
class FragTrap : virtual public ClapTrap { /* ... */ };
```

**Résultat :**
- Une seule copie de `ClapTrap` est partagée
- Plus d'ambiguïté

### 🏗️ Structure avec Virtual Inheritance

**ScavTrap.hpp :**
```cpp
class ScavTrap : virtual public ClapTrap  // ⚠️ virtual
{
    // ...
};
```

**FragTrap.hpp :**
```cpp
class FragTrap : virtual public ClapTrap  // ⚠️ virtual
{
    // ...
};
```

**DiamondTrap.hpp :**
```cpp
class DiamondTrap : public FragTrap, public ScavTrap
{
private:
    std::string _name;  // Nom propre du DiamondTrap

public:
    DiamondTrap(void);
    DiamondTrap(const std::string &name);
    DiamondTrap(const DiamondTrap &copy);
    DiamondTrap &operator=(const DiamondTrap &rhs);
    ~DiamondTrap(void);

    void whoAmI(void);  // Affiche les deux noms
    void attack(const std::string &target);  // Utilise ScavTrap::attack()
};
```

### 🔍 Analyse Détaillée

#### 1. Constructeur de DiamondTrap

```cpp
DiamondTrap::DiamondTrap(const std::string &name) 
    : ClapTrap(name + "_clap_name"),  // ⚠️ Appel explicite à ClapTrap
      FragTrap(name),                 // Appelle FragTrap
      ScavTrap(name),                 // Appelle ScavTrap
      _name(name)                     // Nom propre du DiamondTrap
{
    this->_hitPoints = 100;      // De FragTrap
    this->_energyPoints = 50;    // De ScavTrap
    this->_attackDamage = 30;    // De FragTrap
    std::cout << "DiamondTrap constructor called" << std::endl;
}
```

**Détails importants :**

1. **`ClapTrap(name + "_clap_name")`**
   - **Avec virtual inheritance**, c'est `DiamondTrap` qui doit appeler directement `ClapTrap`
   - Sans cet appel, `ClapTrap()` par défaut serait appelé
   - Le nom `ClapTrap` est différent du nom `DiamondTrap`

2. **Ordre d'initialisation :**
   - `ClapTrap` (base virtuelle) en premier
   - `FragTrap` (ordre de déclaration)
   - `ScavTrap` (ordre de déclaration)
   - `DiamondTrap`

3. **Stats hybrides :**
   - HP de `FragTrap` (100)
   - Energy de `ScavTrap` (50)
   - Damage de `FragTrap` (30)

**Sortie console :**
```
ClapTrap Bob_clap_name created!
FragTrap constructor called
ScavTrap constructor called
DiamondTrap constructor called
```

#### 2. Méthode `whoAmI()`

```cpp
void DiamondTrap::whoAmI(void)
{
    std::cout << "DiamondTrap name: " << this->_name 
              << ", ClapTrap name: " << ClapTrap::_name << std::endl;
}
```

**Rôle :**
- Afficher les deux noms : celui du `DiamondTrap` et celui du `ClapTrap`
- **`ClapTrap::_name`** : Qualification explicite pour accéder au nom de la classe de base

**Usage :**
```cpp
DiamondTrap dt("Bob");
dt.whoAmI();
// Sortie : DiamondTrap name: Bob, ClapTrap name: Bob_clap_name
```

#### 3. Override de `attack()`

```cpp
void DiamondTrap::attack(const std::string &target)
{
    ScavTrap::attack(target);  // ⚠️ Utilise explicitement ScavTrap
}
```

**Pourquoi ?**
- `DiamondTrap` hérite de **deux** méthodes `attack()` : celle de `ScavTrap` et celle de `FragTrap`
- **Ambiguïté** : Le compilateur ne sait pas laquelle choisir
- **Solution** : Qualification explicite `ScavTrap::attack()`

**Sans qualification :**
```cpp
dt.attack("Enemy");  // ❌ ERREUR : Ambiguïté !
```

**Avec qualification :**
```cpp
dt.attack("Enemy");  // ✅ OK : Appelle ScavTrap::attack()
```

#### 4. Destructeur

**Ordre de destruction :**
1. `~DiamondTrap()`
2. `~ScavTrap()`
3. `~FragTrap()`
4. `~ClapTrap()` (une seule fois grâce à virtual)

**Sortie console :**
```
DiamondTrap destructor called
ScavTrap destructor called
FragTrap destructor called
ClapTrap Bob_clap_name destroyed!
```

### 💡 Concepts Clés

**Virtual Inheritance :**
```cpp
// Sans virtual : 2 copies de ClapTrap
class DiamondTrap : public ScavTrap, public FragTrap

// Avec virtual : 1 seule copie de ClapTrap (partagée)
class ScavTrap : virtual public ClapTrap
class FragTrap : virtual public ClapTrap
```

**Appel explicite de la base virtuelle :**
```cpp
// Avec virtual, c'est la classe la plus dérivée qui appelle la base
DiamondTrap::DiamondTrap() : ClapTrap(), FragTrap(), ScavTrap()
```

**Ambiguïté et résolution :**
```cpp
dt.attack("Enemy");         // ❌ Ambiguë
ScavTrap::attack("Enemy");  // ✅ Explicite
dt._hitPoints;              // ✅ OK (une seule copie)
```

**Ordre d'initialisation avec virtual :**
1. Bases virtuelles (dans l'ordre de déclaration dans la hiérarchie)
2. Bases non-virtuelles (dans l'ordre de déclaration)
3. Membres de la classe
4. Corps du constructeur

---

## 📖 Résumé des Concepts du Module 03

### Ce que vous avez appris

1. **Héritage Simple**
   - `class Derived : public Base`
   - Accès aux membres `protected` de la base
   - Ordre construction : Base → Dérivée
   - Ordre destruction : Dérivée → Base

2. **Protected Members**
   - Accessible dans la classe et les classes dérivées
   - Intermédiaire entre `private` et `public`

3. **Override de Méthodes**
   - Redéfinir une méthode héritée
   - Même signature, comportement différent

4. **Constructeurs en Héritage**
   - Appel explicite : `Derived() : Base(args)`
   - La base est construite en premier

5. **Copy Constructor en Héritage**
   - `Derived(const Derived &copy) : Base(copy)`
   - Upcasting automatique

6. **Assignment Operator en Héritage**
   - Appeler l'assignment de la base : `Base::operator=(rhs)`
   - Évite duplication de code

7. **Héritage Multiple**
   - `class Derived : public Base1, public Base2`
   - Ordre de construction : Base1 → Base2 → Derived

8. **Diamond Problem**
   - Héritage en diamant crée des copies multiples
   - Ambiguïté lors de l'accès aux membres

9. **Virtual Inheritance**
   - `class Derived : virtual public Base`
   - Une seule copie de la base partagée
   - La classe la plus dérivée appelle la base virtuelle

### Hiérarchie finale

```
          ClapTrap (virtual)
           /      \
          /        \
   ScavTrap      FragTrap
   (virtual)     (virtual)
          \        /
           \      /
         DiamondTrap
```

### Règles importantes

**Ordre de construction :**
```
1. Bases virtuelles (ordre hiérarchique)
2. Bases non-virtuelles (ordre déclaration)
3. Membres de la classe
4. Corps du constructeur
```

**Ordre de destruction :**
```
Inverse de la construction
```

**Résolution d'ambiguïté :**
```cpp
dt.Base1::method();  // Qualification explicite
```

---

## ✅ Checklist de Validation

- [x] **ex00** : ClapTrap avec OCF complet
- [x] **ex00** : Attributs `protected`
- [x] **ex00** : Méthodes attack/takeDamage/beRepaired
- [x] **ex01** : ScavTrap hérite de ClapTrap
- [x] **ex01** : Override de attack()
- [x] **ex01** : Fonction guardGate()
- [x] **ex02** : FragTrap hérite de ClapTrap
- [x] **ex02** : Fonction highFivesGuys()
- [x] **ex03** : Virtual inheritance (ScavTrap et FragTrap)
- [x] **ex03** : DiamondTrap hérite des deux
- [x] **ex03** : Méthode whoAmI() affiche les deux noms
- [x] **ex03** : attack() utilise ScavTrap::attack()
- [x] **ex03** : Une seule copie de ClapTrap

---

**Module 03 terminé !** Vous maîtrisez maintenant l'héritage simple, multiple et le Diamond Problem en C++. 🎉
