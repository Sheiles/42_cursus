# CPP Module 02 - Explication Détaillée des Exercices

## 📚 Vue d'ensemble du Module

**Concepts principaux :**
- **Orthodox Canonical Form (OCF)** : Les 4 fonctions obligatoires
- **Surcharge d'opérateurs** : Redéfinir `+`, `-`, `*`, `/`, `<<`, `>>`, etc.
- **Fixed-point numbers** : Représenter des nombres à virgule avec des entiers
- **Ad-hoc polymorphism** : Polymorphisme par surcharge

---

## 🎓 Orthodox Canonical Form (OCF)

**Les 4 fonctions OBLIGATOIRES dans toute classe C++98 :**

1. **Constructeur par défaut** : `Class(void)`
2. **Copy constructor** : `Class(const Class &copy)`
3. **Copy assignment operator** : `Class &operator=(const Class &rhs)`
4. **Destructeur** : `~Class(void)`

**Pourquoi obligatoires ?**
- Le compilateur les génère automatiquement si vous ne les définissez pas
- Les versions par défaut font des **shallow copies** (copie bit-à-bit)
- **Problème** : Si votre classe alloue de la mémoire dynamique, shallow copy → double free !
- **Solution** : Définir explicitement ces 4 fonctions

---

## Exercice 00 : My First Class in Orthodox Canonical Form

### 🎯 Objectif
Créer une classe `Fixed` représentant un nombre à virgule fixe.
Implémenter les 4 fonctions de l'OCF et comprendre leur rôle.

### 📋 Nombre à Virgule Fixe (Fixed-Point)

**Qu'est-ce qu'un fixed-point number ?**
- Alternative aux nombres flottants (`float`, `double`)
- Stocké comme un **entier** avec une partie fractionnaire implicite
- Plus rapide sur des processeurs sans FPU (Floating Point Unit)
- Utilisé dans l'embarqué, le jeu vidéo rétro, etc.

**Format Q8.8 (8 bits entiers, 8 bits fractionnaires) :**
```
Valeur réelle = valeur_entière / 2^8
Exemple : 256 représente 1.0 (256 / 256 = 1.0)
          512 représente 2.0 (512 / 256 = 2.0)
          128 représente 0.5 (128 / 256 = 0.5)
```

**Avantages :**
- Précision déterministe (pas d'erreurs d'arrondi flottant)
- Plus rapide sur hardware sans FPU
- Taille fixe

**Inconvénients :**
- Plage limitée
- Précision fixe

### 🏗️ Structure de la Classe `Fixed`

```cpp
class Fixed
{
private:
    int _value;                      // Valeur brute (valeur * 2^8)
    static const int _frac_bits = 8; // Nombre de bits fractionnaires

public:
    Fixed(void);                          // Constructeur par défaut
    Fixed(const Fixed &copy);             // Copy constructor
    Fixed &operator=(const Fixed &rhs);   // Copy assignment operator
    ~Fixed(void);                         // Destructeur

    int getRawBits(void) const;
    void setRawBits(int const raw);
};
```

### 🔍 Analyse Détaillée des Méthodes

#### 1. Constructeur par Défaut

```cpp
Fixed::Fixed(void) : _value(0)
{
    std::cout << "Default constructor called" << std::endl;
}
```

**Rôle :**
- Initialise l'objet à 0.0
- `_value(0)` : Liste d'initialisation (plus efficace que `_value = 0;` dans le corps)

**Quand appelé ?**
```cpp
Fixed a;              // Appelle le constructeur par défaut
Fixed arr[10];        // Appelle 10 fois le constructeur par défaut
```

#### 2. Copy Constructor

```cpp
Fixed::Fixed(const Fixed &copy)
{
    std::cout << "Copy constructor called" << std::endl;
    *this = copy;  // Utilise l'assignment operator
}
```

**Rôle :**
- Créer un nouvel objet comme copie d'un objet existant
- `*this = copy;` : Appelle `operator=` pour copier les valeurs

**Quand appelé ?**
```cpp
Fixed a;
Fixed b(a);           // Copy constructor
Fixed c = a;          // Copy constructor (PAS assignment !)
void func(Fixed f);   // Copy constructor lors du passage par valeur
Fixed func() { Fixed x; return x; }  // Copy constructor lors du retour
```

**Pourquoi `const Fixed &copy` ?**
- `const` : Promesse de ne pas modifier l'original
- `&` : Référence (évite une copie récursive infinie !)

#### 3. Copy Assignment Operator

```cpp
Fixed &Fixed::operator=(const Fixed &rhs)
{
    std::cout << "Copy assignment operator called" << std::endl;
    if (this != &rhs)              // Protection contre auto-assignation
        this->_value = rhs.getRawBits();
    return *this;                  // Retourne *this pour chaînage
}
```

**Rôle :**
- Copier les valeurs d'un objet existant vers un autre objet existant
- **Différence avec copy constructor** : Les deux objets existent déjà

**Quand appelé ?**
```cpp
Fixed a, b;
a = b;                // Assignment operator
a = b = c;            // Assignment operator (chaîné)
```

**Détails techniques :**

1. **`if (this != &rhs)`** - Protection contre l'auto-assignation
   ```cpp
   Fixed a;
   a = a;  // Sans ce check, comportement dangereux !
   ```

2. **`return *this;`** - Permet le chaînage
   ```cpp
   a = b = c;  // Équivalent à : a.operator=(b.operator=(c))
   ```
   - `b = c` retourne `b`
   - `a = b` utilise le `b` retourné

3. **Type de retour `Fixed &`** - Référence pour éviter copie
   - `Fixed` (sans `&`) créerait une copie à chaque assignation
   - `Fixed &` retourne l'objet lui-même

#### 4. Destructeur

```cpp
Fixed::~Fixed(void)
{
    std::cout << "Destructor called" << std::endl;
}
```

**Rôle :**
- Nettoyer les ressources avant la destruction de l'objet
- Ici : rien à libérer (pas d'allocation dynamique)

**Quand appelé ?**
```cpp
{
    Fixed a;
}  // Destructeur appelé ici (fin de scope)

Fixed* ptr = new Fixed();
delete ptr;  // Destructeur appelé ici
```

#### 5. Getters et Setters

```cpp
int Fixed::getRawBits(void) const
{
    std::cout << "getRawBits member function called" << std::endl;
    return this->_value;
}

void Fixed::setRawBits(int const raw)
{
    this->_value = raw;
}
```

**Rôle :**
- **`getRawBits()`** : Accéder à `_value` privé (lecture seule grâce à `const`)
- **`setRawBits()`** : Modifier `_value` privé

### 💡 Concepts Clés

**Shallow Copy vs Deep Copy :**

```cpp
class Simple
{
    int value;
    // Copy constructor par défaut fait une shallow copy : OK
};

class WithPointer
{
    int* ptr;
    // Copy constructor par défaut copie l'adresse → DANGER !
    // Besoin de deep copy : ptr = new int(*copy.ptr)
};
```

**Auto-assignation :**
```cpp
Fixed a;
a = a;  // Sans check, peut causer des problèmes
```

**Retour par référence vs par valeur :**
```cpp
Fixed operator=(const Fixed &rhs)   // ❌ Crée une copie
Fixed &operator=(const Fixed &rhs)  // ✅ Retourne l'objet lui-même
```

---

## Exercice 01 : Towards a more useful fixed-point number class

### 🎯 Objectif
Ajouter des constructeurs pour convertir `int` et `float` vers `Fixed`.
Ajouter des méthodes pour convertir `Fixed` vers `int` et `float`.
Surcharger l'opérateur `<<` pour afficher un `Fixed`.

### 🏗️ Constructeurs Additionnels

#### Constructeur depuis `int`

```cpp
Fixed::Fixed(const int n)
{
    std::cout << "Int constructor called" << std::endl;
    this->_value = n << this->_frac_bits;  // Décalage de 8 bits à gauche
}
```

**Conversion int → fixed-point :**
```
Valeur fixed = int * 2^8
Exemple : 5 → 5 * 256 = 1280
```

**Opération bit-à-bit :**
- `n << 8` : Décale `n` de 8 bits à gauche
- Équivalent à `n * 256` mais plus rapide (opération CPU native)
- Exemple : `5 << 8 = 1280` (binaire : `101` → `10100000000`)

**Usage :**
```cpp
Fixed a(5);       // a représente 5.0 (interne : 1280)
Fixed b = 42;     // b représente 42.0 (conversion implicite)
```

#### Constructeur depuis `float`

```cpp
Fixed::Fixed(const float f)
{
    std::cout << "Float constructor called" << std::endl;
    this->_value = roundf(f * (1 << this->_frac_bits));
}
```

**Conversion float → fixed-point :**
```
Valeur fixed = float * 2^8
Exemple : 3.5 → 3.5 * 256 = 896
```

**Détails :**
1. **`(1 << _frac_bits)`** : Calcule 2^8 = 256
2. **`f * 256`** : Multiplie le float
3. **`roundf()`** : Arrondit au plus proche entier
   - `3.7 * 256 = 947.2` → `947`
   - Sans `roundf()` : troncature (perte de précision)

**Pourquoi `roundf()` et pas `round()` ?**
- `roundf()` : Retourne `float` (C++98 compatible)
- `round()` : Retourne `double` (moins efficace)
- `#include <cmath>` nécessaire

**Usage :**
```cpp
Fixed a(3.5f);    // a représente 3.5 (interne : 896)
Fixed b = 2.75f;  // b représente 2.75 (conversion implicite)
```

### 🏗️ Méthodes de Conversion

#### `toFloat()` - Fixed → float

```cpp
float Fixed::toFloat(void) const
{
    return (float)this->_value / (1 << this->_frac_bits);
}
```

**Conversion fixed-point → float :**
```
Valeur float = valeur_brute / 2^8
Exemple : 896 → 896 / 256 = 3.5
```

**Cast explicite :**
- `(float)this->_value` : Convertit `int` en `float` avant division
- Sans cast : division entière (perte de décimales)

**Usage :**
```cpp
Fixed a(3.5f);
float f = a.toFloat();  // f = 3.5
```

#### `toInt()` - Fixed → int

```cpp
int Fixed::toInt(void) const
{
    return this->_value >> this->_frac_bits;  // Décalage de 8 bits à droite
}
```

**Conversion fixed-point → int :**
```
Valeur int = valeur_brute / 2^8 (partie entière)
Exemple : 896 → 896 / 256 = 3 (troncature)
```

**Opération bit-à-bit :**
- `_value >> 8` : Décale de 8 bits à droite
- Équivalent à `_value / 256` (division entière) mais plus rapide
- Exemple : `896 >> 8 = 3` (binaire : `1110000000` → `11`)

**Usage :**
```cpp
Fixed a(3.75f);
int i = a.toInt();  // i = 3 (troncature, pas d'arrondi)
```

### 🏗️ Surcharge de l'Opérateur `<<`

```cpp
std::ostream &operator<<(std::ostream &os, const Fixed &fixed)
{
    os << fixed.toFloat();
    return os;
}
```

**Rôle :**
- Permet d'utiliser `std::cout << fixed;`
- Affiche la représentation float du nombre

**Détails techniques :**

1. **Fonction globale** (pas méthode membre)
   - Déclarée à l'extérieur de la classe
   - `friend` optionnel mais pas nécessaire (utilise méthode publique `toFloat()`)

2. **`std::ostream &os`** - Référence vers le stream
   - `std::ostream` : Classe de base pour `std::cout`, `std::cerr`, fichiers, etc.
   - `&` : Référence (ne peut pas copier un stream)

3. **`return os;`** - Permet le chaînage
   ```cpp
   std::cout << a << " and " << b << std::endl;
   // Équivalent à :
   operator<<(operator<<(operator<<(std::cout, a), " and "), b);
   ```

**Usage :**
```cpp
Fixed a(3.5f);
std::cout << "Value: " << a << std::endl;
// Sortie : Value: 3.5
```

**Pourquoi pas méthode membre ?**
```cpp
// ❌ Ne fonctionne pas : std::cout.operator<<(a) n'existe pas
class Fixed {
    std::ostream& operator<<(std::ostream &os);
};

// ✅ Fonctionne : operator<<(std::cout, a)
std::ostream& operator<<(std::ostream &os, const Fixed &fixed);
```

### 💡 Concepts Clés

**Conversion implicite vs explicite :**
```cpp
Fixed a = 5;        // Implicite : appelle Fixed(int)
Fixed b = 3.5f;     // Implicite : appelle Fixed(float)
Fixed c(5);         // Explicite
```

**Opérations bit-à-bit :**
```cpp
x << n  // Décalage à gauche de n bits (multiplication par 2^n)
x >> n  // Décalage à droite de n bits (division par 2^n)
```

**Arrondi vs Troncature :**
```cpp
roundf(3.7) = 4    // Arrondi
(int)3.7 = 3       // Troncature
```

---

## Exercice 02 : Now we're talking

### 🎯 Objectif
Surcharger tous les opérateurs mathématiques et de comparaison.
Implémenter les opérateurs d'incrémentation/décrémentation.
Ajouter des fonctions statiques `min()` et `max()`.

### 🏗️ Opérateurs de Comparaison

```cpp
bool Fixed::operator>(const Fixed &rhs) const
{
    return this->_value > rhs._value;
}

bool Fixed::operator<(const Fixed &rhs) const
{
    return this->_value < rhs._value;
}

bool Fixed::operator>=(const Fixed &rhs) const
{
    return this->_value >= rhs._value;
}

bool Fixed::operator<=(const Fixed &rhs) const
{
    return this->_value <= rhs._value;
}

bool Fixed::operator==(const Fixed &rhs) const
{
    return this->_value == rhs._value;
}

bool Fixed::operator!=(const Fixed &rhs) const
{
    return this->_value != rhs._value;
}
```

**Rôle :**
- Comparer deux nombres fixed-point
- Comparaison directe sur `_value` (pas besoin de convertir en float)

**Usage :**
```cpp
Fixed a(3.5f);
Fixed b(2.0f);

if (a > b)        // true
if (a == b)       // false
if (a != b)       // true
```

### 🏗️ Opérateurs Arithmétiques

#### Addition

```cpp
Fixed Fixed::operator+(const Fixed &rhs) const
{
    Fixed result;
    result.setRawBits(this->_value + rhs._value);
    return result;
}
```

**Rôle :**
- Additionner deux nombres fixed-point
- Somme directe des valeurs brutes

**Exemple :**
```
3.5 (896) + 2.0 (512) = 5.5 (1408)
896 + 512 = 1408 ✓
```

#### Soustraction

```cpp
Fixed Fixed::operator-(const Fixed &rhs) const
{
    Fixed result;
    result.setRawBits(this->_value - rhs._value);
    return result;
}
```

**Exemple :**
```
3.5 (896) - 2.0 (512) = 1.5 (384)
896 - 512 = 384 ✓
```

#### Multiplication

```cpp
Fixed Fixed::operator*(const Fixed &rhs) const
{
    Fixed result;
    result.setRawBits((this->_value * rhs._value) >> _frac_bits);
    return result;
}
```

**Rôle :**
- Multiplier deux nombres fixed-point
- **Problème** : Multiplier deux Q8.8 donne un Q16.16 !
- **Solution** : Décaler à droite de 8 bits pour revenir en Q8.8

**Exemple mathématique :**
```
3.5 (896) * 2.0 (512) = 7.0 (1792)

Sans correction :
896 * 512 = 458'752 (représenterait 1792.0 en Q16.16)

Avec correction (>> 8) :
458'752 >> 8 = 1792 ✓ (représente 7.0 en Q8.8)
```

**Pourquoi le décalage ?**
```
(a * 2^8) * (b * 2^8) = a * b * 2^16
On veut : a * b * 2^8
Donc : / 2^8 = >> 8
```

#### Division

```cpp
Fixed Fixed::operator/(const Fixed &rhs) const
{
    Fixed result;
    result.setRawBits((this->_value << _frac_bits) / rhs._value);
    return result;
}
```

**Rôle :**
- Diviser deux nombres fixed-point
- **Problème** : Diviser deux Q8.8 donne un Q0.16 !
- **Solution** : Décaler à gauche de 8 bits avant division

**Exemple mathématique :**
```
7.0 (1792) / 2.0 (512) = 3.5 (896)

Sans correction :
1792 / 512 = 3 (représenterait 0.01171875 en Q8.8)

Avec correction (<< 8) :
(1792 << 8) / 512 = 458'752 / 512 = 896 ✓
```

**Pourquoi le décalage ?**
```
(a * 2^8) / (b * 2^8) = a / b
On veut : (a / b) * 2^8
Donc : * 2^8 avant division = << 8
```

### 🏗️ Opérateurs d'Incrémentation/Décrémentation

#### Pré-incrémentation (`++a`)

```cpp
Fixed &Fixed::operator++(void)
{
    this->_value++;
    return *this;
}
```

**Rôle :**
- Incrémente l'objet PUIS le retourne
- `++` sur la valeur brute = `+1/256` en valeur réelle
- **Retourne une référence** vers l'objet modifié

**Usage :**
```cpp
Fixed a(5.0f);
Fixed b = ++a;   // a = 5.00390625, b = 5.00390625
```

#### Post-incrémentation (`a++`)

```cpp
Fixed Fixed::operator++(int)
{
    Fixed temp(*this);    // Sauvegarde l'ancien état
    this->_value++;       // Incrémente
    return temp;          // Retourne l'ancien état
}
```

**Rôle :**
- Sauvegarde l'ancien état, incrémente, retourne l'ancien
- **Paramètre `int`** : Dummy parameter pour différencier de `++a`
- **Retourne une copie** de l'ancien état

**Usage :**
```cpp
Fixed a(5.0f);
Fixed b = a++;   // a = 5.00390625, b = 5.0
```

**Différence pré vs post :**
```cpp
Fixed a(5.0f);

++a;     // a est incrémenté, retourne a (nouveau)
a++;     // a est incrémenté, retourne copie de l'ancien a

// Performance :
++a;     // Rapide : pas de copie
a++;     // Moins rapide : crée une copie temporaire
```

#### Pré-décrémentation (`--a`)

```cpp
Fixed &Fixed::operator--(void)
{
    this->_value--;
    return *this;
}
```

#### Post-décrémentation (`a--`)

```cpp
Fixed Fixed::operator--(int)
{
    Fixed temp(*this);
    this->_value--;
    return temp;
}
```

### 🏗️ Fonctions Statiques `min()` et `max()`

```cpp
// Version non-const
Fixed &Fixed::min(Fixed &a, Fixed &b)
{
    return (a < b) ? a : b;
}

// Version const
const Fixed &Fixed::min(const Fixed &a, const Fixed &b)
{
    return (a < b) ? a : b;
}

// Version non-const
Fixed &Fixed::max(Fixed &a, Fixed &b)
{
    return (a > b) ? a : b;
}

// Version const
const Fixed &Fixed::max(const Fixed &a, const Fixed &b)
{
    return (a > b) ? a : b;
}
```

**Rôle :**
- Retourner le minimum/maximum de deux `Fixed`
- **Fonctions statiques** : Appelées sur la classe, pas sur un objet

**Pourquoi 2 versions ?**
- **Version non-const** : Pour objets modifiables
- **Version const** : Pour objets constants (promesse de ne pas modifier)

**Usage :**
```cpp
Fixed a(3.5f);
Fixed b(2.0f);

Fixed &minVal = Fixed::min(a, b);     // Retourne référence vers b
const Fixed &maxVal = Fixed::max(a, b); // Retourne référence vers a

minVal = Fixed(10.0f);  // OK : minVal n'est pas const
maxVal = Fixed(10.0f);  // ❌ ERREUR : maxVal est const
```

**Opérateur ternaire :**
```cpp
return (a < b) ? a : b;
// Équivalent à :
if (a < b)
    return a;
else
    return b;
```

### 💡 Concepts Clés

**Pré vs Post incrémentation :**
```cpp
int i = 5;
int a = ++i;  // i = 6, a = 6 (pré)
int b = i++;  // i = 7, b = 6 (post)
```

**Surcharge d'opérateurs - Signatures :**
```cpp
// Membre : a.operator+(b)
Fixed operator+(const Fixed &rhs) const;

// Global : operator<<(cout, a)
std::ostream& operator<<(std::ostream &os, const Fixed &f);
```

**Fonctions statiques :**
```cpp
class Fixed {
    static Fixed &min(Fixed &a, Fixed &b);  // Pas de 'this'
};

Fixed::min(a, b);  // Appel sur la classe, pas sur un objet
```

---

## Exercice 03 : BSP (Binary Space Partitioning) - Bonus

### 🎯 Objectif
Implémenter une fonction `bsp()` qui détermine si un point est à l'intérieur d'un triangle.
Utiliser la classe `Point` avec des coordonnées `Fixed`.

### 📋 Algorithme BSP

**Binary Space Partitioning :**
- Technique pour diviser un espace en régions
- Ici : Vérifier si un point P est dans le triangle ABC

**Méthode utilisée : Somme des aires**

**Principe :**
1. Calculer l'aire du triangle ABC
2. Calculer les aires des 3 sous-triangles : ABP, ACP, BCP
3. Si P est dans ABC : aire(ABP) + aire(ACP) + aire(BCP) = aire(ABC)
4. Si P est sur le bord ou à l'extérieur : somme ≠ aire(ABC)

**Visualisation :**
```
        A
       /|\
      / | \
     /  P  \
    /  / \  \
   / /     \ \
  //         \\
 B-------------C

aire(ABP) + aire(ACP) + aire(BCP) = aire(ABC) → P dans ABC
```

### 🏗️ Classe `Point`

```cpp
class Point
{
private:
    const Fixed _x;  // Coordonnée X constante
    const Fixed _y;  // Coordonnée Y constante

public:
    Point(void);                                    // (0, 0)
    Point(float const x, float const y);            // (x, y)
    Point(const Point &copy);
    Point &operator=(const Point &rhs);
    ~Point(void);

    Fixed getX(void) const;
    Fixed getY(void) const;
};
```

**Attributs constants :**
- **`const Fixed _x`** : Ne peut pas être modifié après construction
- **Immutabilité** : Un point ne change pas de position
- **Initialisation obligatoire** : Dans la liste d'initialisation du constructeur

**Constructeurs :**
```cpp
Point::Point(void) : _x(0), _y(0)
{
}

Point::Point(float const x, float const y) : _x(x), _y(y)
{
}

Point::Point(const Point &copy) : _x(copy._x), _y(copy._y)
{
}
```

**Copy assignment operator avec attributs constants :**
```cpp
Point &Point::operator=(const Point &rhs)
{
    // ⚠️ Impossible de modifier _x et _y (constants) !
    // L'assignment est inutile mais requis par l'OCF
    (void)rhs;  // Supprime le warning "unused parameter"
    return *this;
}
```

**Problème conceptuel :**
- `_x` et `_y` sont `const` → ne peuvent pas être modifiés
- `operator=` doit normalement copier les valeurs
- **Solution** : Retourner `*this` sans rien faire (l'objet est déjà correctement initialisé par le copy constructor)

### 🏗️ Fonction `computeArea()`

```cpp
static Fixed computeArea(Point const a, Point const b, Point const c)
{
    Fixed area;

    // Formule de l'aire d'un triangle (déterminant)
    area = ((a.getX() * (b.getY() - c.getY())
        + b.getX() * (c.getY() - a.getY())
        + c.getX() * (a.getY() - b.getY())) / Fixed(2));

    // Valeur absolue
    if (area < Fixed(0))
        area = area * Fixed(-1);

    return area;
}
```

**Formule mathématique :**
```
Aire = |x₁(y₂ - y₃) + x₂(y₃ - y₁) + x₃(y₁ - y₂)| / 2
```

**Origine : Déterminant de matrice**
```
| x₁  y₁  1 |
| x₂  y₂  1 | / 2
| x₃  y₃  1 |
```

**Détails :**
1. **Calcul du déterminant** : Donne l'aire signée (peut être négative)
2. **Division par 2** : `/ Fixed(2)` utilise l'opérateur `/` surchargé
3. **Valeur absolue** : `if (area < 0) area = area * -1`

**Pourquoi `static` ?**
- Fonction helper interne au fichier
- Pas accessible depuis l'extérieur (scope limité)

### 🏗️ Fonction `bsp()`

```cpp
bool bsp(Point const a, Point const b, Point const c, Point const point)
{
    Fixed areaABC = computeArea(a, b, c);  // Aire du triangle principal
    Fixed areaABP = computeArea(a, b, point);  // Aire sous-triangle 1
    Fixed areaACP = computeArea(a, c, point);  // Aire sous-triangle 2
    Fixed areaBCP = computeArea(b, c, point);  // Aire sous-triangle 3

    // Si point à l'intérieur : somme des sous-aires = aire totale
    return (areaABC == (areaABP + areaACP + areaBCP));
}
```

**Logique :**
1. **Calcule aire(ABC)** : Aire du triangle principal
2. **Calcule 3 sous-aires** : ABP, ACP, BCP
3. **Teste l'égalité** : Si somme = aire totale → point à l'intérieur

**Cas particuliers :**

| Situation | Résultat |
|-----------|----------|
| Point à l'intérieur | `true` |
| Point à l'extérieur | `false` (somme > aire) |
| Point sur le bord | `false` (une sous-aire = 0) |
| Point sur un sommet | `false` (deux sous-aires = 0) |

**Exemple numérique :**
```
Triangle ABC : A(0,0), B(4,0), C(2,3)
Point P(2,1)

aire(ABC) = 6.0
aire(ABP) = 2.0
aire(ACP) = 2.0
aire(BCP) = 2.0

2.0 + 2.0 + 2.0 = 6.0 ✓ → P dans ABC
```

### 💡 Concepts Clés

**Attributs constants :**
```cpp
class Example {
    const int value;
    
    // ✅ OK : initialisation dans la liste
    Example(int v) : value(v) {}
    
    // ❌ ERREUR : ne compile pas
    Example(int v) { value = v; }
};
```

**Limites de la précision fixed-point :**
```cpp
Fixed a(0.1f);
Fixed b(0.2f);
Fixed c(0.3f);

(a + b) == c  // Peut être false à cause des arrondis !
```

**BSP dans les jeux vidéo :**
- Utilisé pour le ray tracing, collision detection
- Doom (1993) utilisait BSP pour le rendu 3D
- Optimise les tests d'intersection

---

## 📖 Résumé des Concepts du Module 02

### Ce que vous avez appris

1. **Orthodox Canonical Form (OCF)**
   - Constructeur par défaut, copy constructor, assignment operator, destructeur
   - Protection contre auto-assignation
   - Retour par référence dans `operator=`

2. **Fixed-Point Arithmetic**
   - Alternative aux flottants
   - Décalages bit-à-bit (`<<`, `>>`)
   - Conversions int/float ↔ fixed

3. **Surcharge d'Opérateurs**
   - Opérateurs de comparaison (`<`, `>`, `==`, etc.)
   - Opérateurs arithmétiques (`+`, `-`, `*`, `/`)
   - Opérateurs d'incrémentation (`++`, `--`)
   - Opérateur d'insertion (`<<`)

4. **Pré vs Post Incrémentation**
   - `++a` : incrémente puis retourne (référence)
   - `a++` : sauvegarde, incrémente, retourne copie

5. **Fonctions Statiques**
   - Appelées sur la classe (`Fixed::min()`)
   - Pas d'accès à `this`

6. **Attributs Constants**
   - `const` membres doivent être initialisés dans la liste
   - Immutabilité des objets

7. **BSP (Binary Space Partitioning)**
   - Algorithme géométrique
   - Test point-dans-triangle par somme d'aires

### Points techniques importants

**Opérations Fixed-Point :**
```cpp
int → fixed :  value = int << 8
float → fixed: value = roundf(float * 256)
fixed → int :  value >> 8
fixed → float: value / 256.0f
fixed * fixed: (a * b) >> 8
fixed / fixed: (a << 8) / b
```

**Signatures d'opérateurs :**
```cpp
// Retourne nouvel objet
Fixed operator+(const Fixed &rhs) const;

// Retourne référence (modification)
Fixed &operator++();

// Paramètre dummy int pour post-increment
Fixed operator++(int);

// Fonction globale pour <<
std::ostream &operator<<(std::ostream &os, const Fixed &f);
```

---

## ✅ Checklist de Validation

- [x] **ex00** : OCF implémenté (4 fonctions)
- [x] **ex01** : Constructeurs int/float, conversions, `operator<<`
- [x] **ex02** : Tous les opérateurs surchargés
- [x] **ex02** : Fonctions `min()` et `max()` statiques
- [x] **ex03** : Classe `Point` avec coordonnées constantes
- [x] **ex03** : Algorithme BSP fonctionnel

---

**Module 02 terminé !** Vous maîtrisez maintenant la surcharge d'opérateurs et l'arithmetic fixed-point en C++. 🎉
