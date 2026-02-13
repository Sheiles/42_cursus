# CPP Module 03 - État et Validation

## ✅ Tous les exercices sont complets !

### 📊 Structure vérifiée

```
CPP_module03/
├── ex00/ ✅ ClapTrap (Classe de base)
│   ├── ClapTrap.hpp    - Classe de base avec attributs protected
│   ├── ClapTrap.cpp    - attack(), takeDamage(), beRepaired()
│   ├── main.cpp        - Tests ClapTrap
│   └── Makefile
│
├── ex01/ ✅ ScavTrap (Héritage simple)
│   ├── ClapTrap.hpp    
│   ├── ClapTrap.cpp    
│   ├── ScavTrap.hpp    - Hérite de ClapTrap
│   ├── ScavTrap.cpp    - guardGate() + constructeurs spécifiques
│   ├── main.cpp        - Tests héritage et chaînage construction
│   └── Makefile
│
├── ex02/ ✅ FragTrap (Héritage simple)
│   ├── ClapTrap.hpp    
│   ├── ClapTrap.cpp    
│   ├── FragTrap.hpp    - Hérite de ClapTrap
│   ├── FragTrap.cpp    - highFivesGuys() + stats différentes
│   ├── main.cpp        - Tests FragTrap
│   └── Makefile
│
└── ex03/ ✅ DiamondTrap (Héritage multiple + virtuel) - BONUS
    ├── ClapTrap.hpp    
    ├── ClapTrap.cpp    
    ├── ScavTrap.hpp    - Héritage VIRTUEL: virtual public ClapTrap
    ├── ScavTrap.cpp    
    ├── FragTrap.hpp    - Héritage VIRTUEL: virtual public ClapTrap
    ├── FragTrap.cpp    
    ├── DiamondTrap.hpp - Hérite de FragTrap ET ScavTrap
    ├── DiamondTrap.cpp - whoAmI() + résolution ambiguïté
    ├── main.cpp        - Tests Diamond Problem résolu
    └── Makefile
```

## 🎯 Concepts implémentés

### Ex00 - ClapTrap (Classe de base)
```cpp
class ClapTrap {
protected:  // Protected pour permettre l'héritage
    std::string _name;
    unsigned int _hitPoints;     // 10
    unsigned int _energyPoints;  // 10
    unsigned int _attackDamage;  // 0
public:
    void attack(const std::string& target);
    void takeDamage(unsigned int amount);
    void beRepaired(unsigned int amount);
};
```
- ✅ Orthodox Canonical Form
- ✅ Attributs `protected` pour l'héritage
- ✅ Messages de debug pour constructeurs/destructeur
- ✅ Logique : attaquer/réparer coûte 1 energy point

### Ex01 - ScavTrap (Héritage simple)
```cpp
class ScavTrap : public ClapTrap {
public:
    ScavTrap(const std::string &name);  // HP:100, Energy:50, Damage:20
    void attack(const std::string& target);  // Override
    void guardGate(void);  // Nouvelle capacité
};
```
- ✅ Héritage public de ClapTrap
- ✅ Stats différentes (HP:100, Energy:50, Damage:20)
- ✅ Override de `attack()` avec message différent
- ✅ Capacité spéciale : `guardGate()`
- ✅ **Chaînage construction** : ClapTrap → ScavTrap
- ✅ **Chaînage destruction** : ScavTrap → ClapTrap (ordre inverse)

### Ex02 - FragTrap (Héritage simple)
```cpp
class FragTrap : public ClapTrap {
public:
    FragTrap(const std::string &name);  // HP:100, Energy:100, Damage:30
    void attack(const std::string& target);  // Override
    void highFivesGuys(void);  // Nouvelle capacité
};
```
- ✅ Héritage public de ClapTrap
- ✅ Stats différentes (HP:100, Energy:100, Damage:30)
- ✅ Override de `attack()` avec message différent
- ✅ Capacité spéciale : `highFivesGuys()`
- ✅ Chaînage construction/destruction

### Ex03 - DiamondTrap (Héritage multiple + Diamond Problem) - BONUS
```cpp
// Dans ex03/ScavTrap.hpp et ex03/FragTrap.hpp
class ScavTrap : virtual public ClapTrap { ... };
class FragTrap : virtual public ClapTrap { ... };

// Dans ex03/DiamondTrap.hpp
class DiamondTrap : public FragTrap, public ScavTrap {
private:
    std::string _name;  // Nom DiamondTrap
    // ClapTrap::_name contient "<name>_clap_name"
public:
    DiamondTrap(const std::string &name);
    void whoAmI(void);  // Affiche les deux noms
    void attack(const std::string& target);  // Utilise ScavTrap::attack()
};
```

**Héritage combiné :**
- ✅ HP: 100 (de FragTrap)
- ✅ Energy: 50 (de ScavTrap)  
- ✅ Damage: 30 (de FragTrap)
- ✅ `attack()` : de ScavTrap
- ✅ Résolution du Diamond Problem avec `virtual` inheritance
- ✅ Une seule instance de ClapTrap grâce à l'héritage virtuel

## 🔍 Le Diamond Problem résolu

### Sans héritage virtuel (❌ Problème)
```
      ClapTrap
       /    \
  ScavTrap  FragTrap
       \    /
    DiamondTrap
```
→ **2 instances** de ClapTrap dans DiamondTrap !
→ Ambiguïté : `_name` de quelle ClapTrap ?

### Avec héritage virtuel (✅ Solution)
```cpp
class ScavTrap : virtual public ClapTrap { ... };
class FragTrap : virtual public ClapTrap { ... };
```
→ **1 seule instance** de ClapTrap partagée
→ Pas d'ambiguïté !

## 📚 Messages de construction/destruction

L'ordre est important pour comprendre l'héritage :

### Ex01 - ScavTrap
```
Construction:
1. ClapTrap constructor called (base)
2. ScavTrap constructor called (derived)

Destruction (ordre inverse):
1. ScavTrap destructor called
2. ClapTrap destructor called
```

### Ex03 - DiamondTrap
```
Construction:
1. ClapTrap constructor called (base virtuelle, une seule fois)
2. FragTrap constructor called
3. ScavTrap constructor called
4. DiamondTrap constructor called

Destruction:
1. DiamondTrap destructor called
2. ScavTrap destructor called
3. FragTrap destructor called
4. ClapTrap destructor called
```

## 🧪 Tests sur Linux

Pour compiler et tester tous les exercices :

```bash
cd CPP_module03/ex00 && make && ./claptrap && make fclean && cd ..
cd ex01 && make && ./scavtrap && make fclean && cd ..
cd ex02 && make && ./fragtrap && make fclean && cd ..
cd ex03 && make && ./diamondtrap && make fclean
```

Ou avec le script global :
```bash
cd /mnt/c/Users/"Sam Heiles"/Documents/42_cursus
./test_all_cpp.sh
```

## 💡 Points clés du Module 03

### 1. Attributs `protected`
```cpp
protected:  // Accessible dans les classes dérivées
    std::string _name;
```
- `private` : accessible uniquement dans la classe
- `protected` : accessible dans la classe ET ses dérivées
- `public` : accessible partout

### 2. Héritage public
```cpp
class Derived : public Base { ... };
```
- Les membres `public` de Base restent `public` dans Derived
- Les membres `protected` de Base restent `protected` dans Derived

### 3. Override de méthodes
```cpp
// Dans ClapTrap
void attack(const std::string& target);

// Dans ScavTrap (override)
void attack(const std::string& target);  // Message différent
```
Pas de mot-clé `override` en C++98 (introduit en C++11)

### 4. Héritage virtuel
```cpp
class Derived : virtual public Base { ... };
```
- Résout le Diamond Problem
- Une seule instance de la classe de base
- Essentiel pour l'héritage multiple

### 5. Chaînage de constructeurs
Le constructeur de la classe dérivée doit appeler celui de la base :
```cpp
ScavTrap::ScavTrap(const std::string &name) : ClapTrap(name) {
    // Initialisation spécifique à ScavTrap
    _hitPoints = 100;
    _energyPoints = 50;
    _attackDamage = 20;
}
```

## ⚠️ Flags de compilation utiles

Le sujet mentionne :
```bash
-Wshadow    # Avertit si une variable cache une autre
-Wno-shadow # Désactive ces avertissements
```

Utile pour DiamondTrap qui a un attribut `_name` qui cache `ClapTrap::_name`.

## 🎮 Exemple d'utilisation

```cpp
int main() {
    // Ex00
    ClapTrap basic("Rob");
    basic.attack("target");
    basic.takeDamage(5);
    basic.beRepaired(3);
    
    // Ex01
    ScavTrap guard("Guard");
    guard.attack("intruder");
    guard.guardGate();
    
    // Ex02
    FragTrap party("Party");
    party.attack("enemy");
    party.highFivesGuys();
    
    // Ex03
    DiamondTrap hybrid("Hybrid");
    hybrid.attack("boss");      // Utilise ScavTrap::attack()
    hybrid.guardGate();         // De ScavTrap
    hybrid.highFivesGuys();     // De FragTrap
    hybrid.whoAmI();            // Affiche "Hybrid" et "Hybrid_clap_name"
    
    return 0;
}
```

## 🚀 Statut du module

**CPP_module03 : 100% complet** (4/4 exercices + bonus) ✅

- ex00: ClapTrap ✅
- ex01: ScavTrap ✅
- ex02: FragTrap ✅
- ex03: DiamondTrap ✅ (BONUS - Diamond Problem résolu)

**Prochains modules :**
- CPP_module04 : Polymorphisme et classes abstraites
- CPP_module05 : Exceptions
- CPP_module06 : Casts
