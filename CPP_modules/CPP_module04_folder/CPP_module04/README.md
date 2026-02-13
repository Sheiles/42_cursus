# CPP Module 04 - État et Validation

## ✅ 3/4 exercices complets (ex03 bonus manquant)

### 📊 Structure vérifiée

```
CPP_module04/
├── ex00/ ✅ Polymorphism (Héritage + méthodes virtuelles)
│   ├── Animal.hpp      - Classe de base avec virtual makeSound()
│   ├── Animal.cpp      - Implémentation
│   ├── Dog.hpp/cpp     - Hérite d'Animal, override makeSound()
│   ├── Cat.hpp/cpp     - Hérite d'Animal, override makeSound()
│   ├── WrongAnimal.hpp/cpp  - Exemple SANS virtual (polymorphisme raté)
│   ├── WrongCat.hpp/cpp     - Hérite de WrongAnimal
│   ├── main.cpp        - Tests polymorphisme
│   └── Makefile
│
├── ex01/ ✅ Brain & Deep Copy
│   ├── Animal.hpp/cpp  - Classe de base
│   ├── Dog.hpp/cpp     - Contient Brain* (allocation dynamique)
│   ├── Cat.hpp/cpp     - Contient Brain* (allocation dynamique)
│   ├── Brain.hpp/cpp   - Tableau de 100 std::string ideas
│   ├── main.cpp        - Tests deep copy, memory leaks
│   └── Makefile
│
├── ex02/ ✅ Abstract Class
│   ├── AAnimal.hpp     - Classe abstraite : virtual makeSound() = 0
│   ├── AAnimal.cpp     - Non instanciable !
│   ├── Dog.hpp/cpp     - Hérite d'AAnimal + Brain*
│   ├── Cat.hpp/cpp     - Hérite d'AAnimal + Brain*
│   ├── Brain.hpp/cpp   - Tableau de 100 ideas
│   ├── main.cpp        - Tests classe abstraite
│   └── Makefile
│
└── ex03/ ❌ Interface & Materia System (VIDE)
    Bonus non réalisé :
    - AMateria (pure abstract)
    - Ice & Cure (materias concrètes)
    - ICharacter (interface)
    - Character (inventaire 4 slots)
    - IMateriaSource (interface)
    - MateriaSource (factory pattern)
```

## 🎯 Concepts implémentés

### Ex00 - Polymorphisme de sous-type

**Animal (classe de base polymorphe) :**
```cpp
class Animal {
protected:
    std::string type;
public:
    Animal(void);
    virtual ~Animal(void);              // Destructeur VIRTUEL (important !)
    virtual void makeSound(void) const; // Méthode VIRTUELLE
    std::string getType(void) const;
};
```

**Dog et Cat (classes dérivées) :**
```cpp
class Dog : public Animal {
public:
    Dog(void);  // type = "Dog"
    virtual void makeSound(void) const;  // "Woof woof!"
};

class Cat : public Animal {
public:
    Cat(void);  // type = "Cat"
    virtual void makeSound(void) const;  // "Meow meow!"
};
```

**Polymorphisme en action :**
```cpp
const Animal* dog = new Dog();
const Animal* cat = new Cat();

dog->makeSound();  // "Woof woof!" (appelle Dog::makeSound)
cat->makeSound();  // "Meow meow!" (appelle Cat::makeSound)

delete dog;  // Appelle ~Dog() puis ~Animal() grâce à virtual ~Animal()
delete cat;  // Appelle ~Cat() puis ~Animal()
```

**WrongAnimal (contre-exemple SANS virtual) :**
```cpp
class WrongAnimal {
public:
    void makeSound() const;  // PAS VIRTUAL !
};

class WrongCat : public WrongAnimal {
public:
    void makeSound() const;  // Override mais sans polymorphisme
};

// Résultat :
const WrongAnimal* cat = new WrongCat();
cat->makeSound();  // Appelle WrongAnimal::makeSound() (MAUVAIS !)
                   // Pas de polymorphisme sans virtual
```

✅ **Points clés :**
- Destructeur `virtual` obligatoire pour éviter les fuites mémoire
- Méthodes `virtual` pour activer le polymorphisme
- Binding dynamique (à l'exécution) vs binding statique (à la compilation)

---

### Ex01 - Deep Copy & Memory Management

**Brain (ressource dynamique) :**
```cpp
class Brain {
private:
    std::string ideas[100];  // 100 idées stockées
public:
    Brain(void);
    Brain(const Brain &copy);        // Deep copy
    Brain &operator=(const Brain &rhs);  // Deep assignment
    ~Brain(void);
};
```

**Dog avec Brain* :**
```cpp
class Dog : public Animal {
private:
    Brain* _brain;  // Allocation dynamique !
public:
    Dog(void) {
        _brain = new Brain();  // Alloue en construction
    }
    
    Dog(const Dog &copy) : Animal(copy) {
        _brain = new Brain(*copy._brain);  // DEEP COPY !
    }
    
    ~Dog(void) {
        delete _brain;  // Libère en destruction
    }
};
```

**Tests obligatoires :**
```cpp
int main() {
    // Tableau mixte d'animaux
    const Animal* animals[10];
    
    for (int i = 0; i < 5; i++)
        animals[i] = new Dog();
    for (int i = 5; i < 10; i++)
        animals[i] = new Cat();
    
    // Suppression via pointeur Animal* (polymorphisme)
    for (int i = 0; i < 10; i++)
        delete animals[i];  // Appelle ~Dog() ou ~Cat() puis ~Animal()
    
    // Test deep copy
    Dog original;
    Dog copy = original;  // Doit créer un nouveau Brain
    // Modification de 'copy' ne doit PAS affecter 'original'
    
    return 0;
}
```

✅ **Points clés :**
- `new Brain()` en construction, `delete _brain` en destruction
- Copy constructor DOIT faire une deep copy : `new Brain(*other._brain)`
- Assignment operator DOIT supprimer l'ancien puis créer un nouveau
- Destructeur virtuel essentiel pour la polymorphie

---

### Ex02 - Classe Abstraite (Abstract Class)

**AAnimal (classe abstraite) :**
```cpp
class AAnimal {
protected:
    std::string type;
public:
    AAnimal(void);
    virtual ~AAnimal(void);
    
    // Méthode PURE VIRTUELLE = classe abstraite
    virtual void makeSound(void) const = 0;  // = 0 rend la classe abstraite
    
    std::string getType(void) const;
};
```

**Conséquences :**
```cpp
AAnimal animal;  // ❌ ERREUR : impossible d'instancier une classe abstraite
AAnimal* ptr = new Dog();  // ✅ OK : pointeur vers classe dérivée
```

**Dog et Cat implémentent makeSound() :**
```cpp
class Dog : public AAnimal {
public:
    void makeSound(void) const {  // Implémentation obligatoire
        std::cout << "Woof!" << std::endl;
    }
};
```

✅ **Points clés :**
- `= 0` après une méthode virtuelle → classe abstraite
- Impossible d'instancier directement une classe abstraite
- Les classes dérivées DOIVENT implémenter les méthodes pures virtuelles
- Utile pour forcer un contrat (interface) dans les classes dérivées
- Ex02 reprend Ex01 mais Animal → AAnimal (abstraite)

---

### Ex03 - Interfaces & Materia System (❌ NON FAIT)

**Ce qui devrait être implémenté :**

1. **AMateria (classe abstraite de base) :**
```cpp
class AMateria {
protected:
    std::string _type;
public:
    AMateria(std::string const & type);
    virtual ~AMateria();
    
    std::string const & getType() const;
    virtual AMateria* clone() const = 0;      // Pure virtual
    virtual void use(ICharacter& target);
};
```

2. **Ice et Cure (materias concrètes) :**
```cpp
class Ice : public AMateria {
public:
    Ice();
    AMateria* clone() const;  // return new Ice(*this);
    void use(ICharacter& target);  // "* shoots an ice bolt at <name> *"
};

class Cure : public AMateria {
public:
    Cure();
    AMateria* clone() const;  // return new Cure(*this);
    void use(ICharacter& target);  // "* heals <name>'s wounds *"
};
```

3. **ICharacter (interface) :**
```cpp
class ICharacter {
public:
    virtual ~ICharacter() {}
    virtual std::string const & getName() const = 0;
    virtual void equip(AMateria* m) = 0;
    virtual void unequip(int idx) = 0;
    virtual void use(int idx, ICharacter& target) = 0;
};
```

4. **Character (implémentation) :**
```cpp
class Character : public ICharacter {
private:
    std::string _name;
    AMateria* _inventory[4];  // Max 4 materias
public:
    Character(std::string const & name);
    // Implémentation de toutes les méthodes de ICharacter
    // Deep copy obligatoire !
};
```

5. **IMateriaSource & MateriaSource (factory pattern) :**
```cpp
class IMateriaSource {
public:
    virtual ~IMateriaSource() {}
    virtual void learnMateria(AMateria*) = 0;
    virtual AMateria* createMateria(std::string const & type) = 0;
};

class MateriaSource : public IMateriaSource {
private:
    AMateria* _templates[4];  // Max 4 templates
public:
    void learnMateria(AMateria* m);       // Clone et stocke
    AMateria* createMateria(std::string const & type);  // Clone le template
};
```

**Pattern utilisé :** Factory Pattern (MateriaSource crée des Materias à partir de templates)

---

## 🧪 Tests sur Linux

Pour compiler et tester :

```bash
cd CPP_module04/ex00 && make && ./polymorphism && make fclean && cd ..
cd ex01 && make && ./brain && make fclean && cd ..
cd ex02 && make && ./abstract && make fclean
```

Ou avec le script global :
```bash
cd /mnt/c/Users/"Sam Heiles"/Documents/42_cursus
./test_all_cpp.sh
```

---

## 💡 Points clés du Module 04

### 1. Mot-clé `virtual`

**Destructeur virtuel (OBLIGATOIRE) :**
```cpp
class Base {
public:
    virtual ~Base() {}  // TOUJOURS virtual dans une classe de base polymorphe
};

// Sans virtual :
Base* ptr = new Derived();
delete ptr;  // ❌ Appelle seulement ~Base(), fuite mémoire dans Derived !

// Avec virtual :
delete ptr;  // ✅ Appelle ~Derived() puis ~Base(), pas de fuite
```

**Méthodes virtuelles :**
```cpp
class Base {
public:
    virtual void method();  // Peut être override
};

class Derived : public Base {
public:
    void method();  // Override (C++98 n'a pas le mot-clé 'override')
};
```

### 2. Classe abstraite (Abstract Class)

```cpp
class Abstract {
public:
    virtual void pureVirtual() = 0;  // = 0 → méthode pure virtuelle
};

// Impossible d'instancier :
Abstract obj;  // ❌ ERREUR : cannot instantiate abstract class

// Uniquement via pointeur/référence :
Abstract* ptr = new Concrete();  // ✅ OK si Concrete implémente pureVirtual()
```

### 3. Interface (en C++98)

**En C++, une interface = classe abstraite pure :**
```cpp
class IInterface {
public:
    virtual ~IInterface() {}
    virtual void method1() = 0;
    virtual void method2() = 0;
    // Toutes les méthodes sont pures virtuelles
    // Pas d'attributs (ou alors protected)
};
```

### 4. Deep Copy avec pointeurs

```cpp
class Container {
private:
    Resource* _ptr;
public:
    Container() : _ptr(new Resource()) {}
    
    // Copy constructor (DEEP)
    Container(const Container &other) {
        _ptr = new Resource(*other._ptr);  // Nouvelle allocation
    }
    
    // Assignment operator (DEEP)
    Container &operator=(const Container &other) {
        if (this != &other) {
            delete _ptr;  // Supprime l'ancien
            _ptr = new Resource(*other._ptr);  // Nouvelle allocation
        }
        return *this;
    }
    
    ~Container() {
        delete _ptr;  // Libération
    }
};
```

### 5. Factory Pattern (ex03)

```cpp
// Factory crée des objets sans exposer la logique de création
class Factory {
public:
    Product* createProduct(std::string type) {
        if (type == "A") return new ProductA();
        if (type == "B") return new ProductB();
        return nullptr;
    }
};
```

---

## ⚠️ Erreurs courantes

### 1. Oublier `virtual` sur le destructeur
```cpp
class Base {
public:
    ~Base() {}  // ❌ PAS VIRTUAL !
};

Base* ptr = new Derived();
delete ptr;  // Fuite mémoire : ~Derived() pas appelé !
```

### 2. Shallow copy avec pointeurs
```cpp
class Bad {
    Resource* _ptr;
public:
    // Utilise le copy constructor par défaut
    // → SHALLOW COPY : copie juste le pointeur !
    // → Double delete si deux objets pointent vers même Resource
};
```

### 3. Instancier une classe abstraite
```cpp
AAnimal animal;  // ❌ ERREUR : classe abstraite !
```

### 4. Ne pas implémenter les méthodes pures virtuelles
```cpp
class Derived : public Abstract {
    // ❌ Oublie d'implémenter pureVirtual()
    // → Derived est aussi abstraite !
};
```

---

## 🚀 Statut du module

**CPP_module04 : 75% complet** (3/4 exercices)

- ex00: Polymorphism ✅
- ex01: Brain & Deep Copy ✅
- ex02: Abstract Class ✅
- ex03: Interface & Materia ❌ (BONUS - non fait)

**Note :** Le module peut être validé sans l'exercice 03 (bonus).

### Récapitulatif global

| Module | Exercices | État | Concept principal |
|--------|-----------|------|-------------------|
| CPP_module00 | 3/3 | ✅ | Introduction C++, Classes |
| CPP_module01 | 7/7 | ✅ | Références, Pointeurs, Memory |
| CPP_module02 | 4/4 | ✅ | Surcharge opérateurs, OCF |
| CPP_module03 | 4/4 | ✅ | Héritage, Diamond Problem |
| **CPP_module04** | **3/4** | **⚠️** | **Polymorphisme, Classes Abstraites** |

**Prochains modules :**
- CPP_module05 : Exceptions (try/catch)
- CPP_module06 : Casts (static_cast, dynamic_cast, etc.)
- CPP_module07 : Templates
