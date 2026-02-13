# CPP Module 02 - État et Validation

## ✅ Tous les exercices sont complets !

### 📊 Structure vérifiée

```
CPP_module02/
├── ex00/ ✅ My First Class in Orthodox Canonical Form
│   ├── Fixed.hpp       - Classe avec Orthodox Canonical Form
│   ├── Fixed.cpp       - Implémentation basique
│   ├── main.cpp        - Tests
│   └── Makefile        - Compilation
│
├── ex01/ ✅ Towards a more useful fixed-point number class
│   ├── Fixed.hpp       - Constructeurs int/float + conversions
│   ├── Fixed.cpp       - toInt(), toFloat(), operator<<
│   ├── main.cpp        - Tests avec conversions
│   └── Makefile
│
├── ex02/ ✅ Now we're talking
│   ├── Fixed.hpp       - Surcharge des opérateurs
│   ├── Fixed.cpp       - Comparaison, arithmétique, incrémentation, min/max
│   ├── main.cpp        - Tests des opérateurs
│   └── Makefile
│
└── ex03/ ✅ BSP (Binary Space Partitioning) - BONUS
    ├── Fixed.hpp       - Classe Fixed complète
    ├── Fixed.cpp
    ├── Point.hpp       - Classe Point avec Fixed const x, y
    ├── Point.cpp
    ├── bsp.cpp         - Fonction de détection point dans triangle
    ├── main.cpp        - Tests BSP
    └── Makefile
```

## 🎯 Concepts implémentés

### Ex00 - Orthodox Canonical Form
- ✅ Constructeur par défaut
- ✅ Constructeur de copie
- ✅ Opérateur d'affectation (copy assignment)
- ✅ Destructeur
- ✅ getRawBits() / setRawBits()

### Ex01 - Conversions
- ✅ Constructeur depuis `int`
- ✅ Constructeur depuis `float`
- ✅ Conversion vers `int` (toInt)
- ✅ Conversion vers `float` (toFloat)
- ✅ Surcharge de `operator<<` pour std::ostream

### Ex02 - Surcharge d'opérateurs
- ✅ Opérateurs de comparaison: `>`, `<`, `>=`, `<=`, `==`, `!=`
- ✅ Opérateurs arithmétiques: `+`, `-`, `*`, `/`
- ✅ Pré/post incrémentation: `++a`, `a++`
- ✅ Pré/post décrémentation: `--a`, `a--`
- ✅ Fonctions statiques: `min()`, `max()` (versions const et non-const)

### Ex03 - BSP (Bonus)
- ✅ Classe Point avec attributs Fixed const
- ✅ Fonction `bool bsp(Point const a, Point const b, Point const c, Point const point)`
- ✅ Détection si un point est à l'intérieur d'un triangle

## 🧪 Tests sur Linux

Pour compiler et tester tous les exercices :

```bash
cd CPP_module02/ex00 && make && ./fixed && make fclean && cd ..
cd ex01 && make && ./fixed && make fclean && cd ..
cd ex02 && make && ./fixed && make fclean && cd ..
cd ex03 && make && ./fixed_bsp && make fclean
```

Ou utiliser le script global :
```bash
cd /mnt/c/Users/"Sam Heiles"/Documents/42_cursus
./test_all_cpp.sh
```

## 📝 Points clés du Module 02

### Fixed-Point Numbers
Les nombres à virgule fixe sont un compromis entre :
- **Performance** : Plus rapide que les float sur certains systèmes
- **Précision** : Meilleure que les int, contrôlable
- **Plage** : Entre int et float

Formule de conversion :
- `int → fixed` : `value << fractional_bits` (multiplier par 2^8 = 256)
- `fixed → float` : `value / (1 << fractional_bits)` (diviser par 256)
- `float → fixed` : `roundf(f * (1 << fractional_bits))`

### Orthodox Canonical Form
Chaque classe doit avoir les 4 fonctions membres :
1. **Constructeur par défaut** : `Fixed(void);`
2. **Constructeur de copie** : `Fixed(const Fixed &copy);`
3. **Opérateur d'affectation** : `Fixed &operator=(const Fixed &rhs);`
4. **Destructeur** : `~Fixed(void);`

### Surcharge d'opérateurs
```cpp
// Opérateur binaire (membre)
bool operator<(const Fixed &rhs) const;

// Opérateur d'incrémentation
Fixed &operator++();      // Pré-incrémentation (++a)
Fixed operator++(int);    // Post-incrémentation (a++)

// Opérateur de flux (non-membre, friend ou externe)
std::ostream &operator<<(std::ostream &out, const Fixed &fixed);
```

## ⚠️ Points d'attention

### Epsilon pour incrémentation
Le plus petit epsilon représentable :
```cpp
Fixed &Fixed::operator++() {
    this->_value++;  // Incrémente de 1 en représentation brute
    return *this;    // = 1/256 = 0.00390625 en décimal
}
```

### Division par zéro
Selon le sujet : "If you ever do a division by 0, it is acceptable that the program crashes"

### Attributs const dans Point (ex03)
```cpp
private:
    const Fixed _x;  // Attributs constants
    const Fixed _y;  // Doivent être initialisés dans la liste d'initialisation
```

## 🚀 Prochaines étapes

Votre CPP_module02 est **100% complet** (y compris le bonus) !

**Modules suivants :**
- CPP_module03 : Héritage
- CPP_module04 : Polymorphisme
- CPP_module05 : Exceptions
