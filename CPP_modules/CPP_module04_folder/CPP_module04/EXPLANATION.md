# CPP Module 04 - Explication Détaillée des Exercices

## 📚 Vue d'ensemble du Module

**Concepts principaux :**
- **Polymorphisme** : Capacité d'utiliser des objets dérivés via des pointeurs/références de base
- **Fonctions virtuelles** : Permettent le polymorphisme en C++
- **Destructeurs virtuels** : Essentiels pour éviter les fuites mémoire
- **Classes abstraites** : Classes non-instantiables avec fonctions pures
- **Deep copy** : Copie profonde avec pointeurs

---

## 🎓 Introduction au Polymorphisme

### Qu'est-ce que le polymorphisme ?

**Définition :**
- "Plusieurs formes" : un même code peut fonctionner avec différents types
- Permet de traiter des objets dérivés via des références/pointeurs de la classe de base
- Clé du paradigme orienté objet

**Exemple simple :**
```cpp
Animal* animal1 = new Dog();
Animal* animal2 = new Cat();

animal1->makeSound();  // "Woof! Woof!"
animal2->makeSound();  // "Meow! Meow!"

// Même pointeur Animal, comportements différents !
```

### Fonctions virtuelles

**Sans `virtual` :**
```cpp
class Animal {
public:
    void makeSound() const { std::cout << "Some animal sound" << std::endl; }
};

class Dog : public Animal {
public:
    void makeSound() const { std::cout << "Woof!" << std::endl; }
};

Animal* dog = new Dog();
dog->makeSound();  // ❌ Affiche "Some animal sound" (appelle Animal::makeSound)
```

**Avec `virtual` :**
```cpp
class Animal {
public:
    virtual void makeSound() const { std::cout << "Some animal sound" << std::endl; }
};

class Dog : public Animal {
public:
    void makeSound() const { std::cout << "Woof!" << std::endl; }
};

Animal* dog = new Dog();
dog->makeSound();  // ✅ Affiche "Woof!" (appelle Dog::makeSound)
```

**Comment ça marche ?**
- Chaque classe avec fonctions virtuelles a une **vtable** (Virtual Table)
- Chaque objet a un pointeur vers la vtable de sa classe réelle
- Lors de l'appel, le programme regarde dans la vtable pour trouver la bonne fonction

### Destructeurs virtuels

**Problème sans destructeur virtuel :**
```cpp
class Base {
public:
    ~Base() { std::cout << "Base destructor" << std::endl; }
};

class Derived : public Base {
private:
    int* data;
public:
    Derived() : data(new int[100]) {}
    ~Derived() {
        delete[] data;  // Libère la mémoire
        std::cout << "Derived destructor" << std::endl;
    }
};

Base* ptr = new Derived();
delete ptr;  // ❌ Appelle seulement ~Base() !
             // Fuite mémoire : data n'est jamais libéré
```

**Solution : destructeur virtuel**
```cpp
class Base {
public:
    virtual ~Base() { std::cout << "Base destructor" << std::endl; }
};

// ...

delete ptr;  // ✅ Appelle ~Derived() puis ~Base()
             // data est correctement libéré
```

**Règle d'or :**
> Si une classe a au moins une fonction virtuelle, son destructeur doit être virtuel.

---

## Exercice 00 : Polymorphism

### 🎯 Objectif
Créer une hiérarchie `Animal` / `Dog` / `Cat` pour démontrer le polymorphisme.
Comparer avec une hiérarchie incorrecte `WrongAnimal` / `WrongCat`.

### 📋 Structure

**Animal (correct) :**
- Fonction `virtual void makeSound() const`
- Destructeur `virtual ~Animal()`

**WrongAnimal (incorrect) :**
- Fonction `void makeSound() const` (sans virtual !)
- Destructeur `~WrongAnimal()` (sans virtual !)

### 🏗️ Classe Animal

**Animal.hpp :**
```cpp
class Animal
{
protected:
    std::string type;

public:
    Animal(void);
    Animal(const Animal &copy);
    Animal &operator=(const Animal &rhs);
    virtual ~Animal(void);  // ⚠️ Destructeur virtuel

    virtual void makeSound(void) const;  // ⚠️ Fonction virtuelle
    std::string getType(void) const;
};
```

**Animal.cpp :**
```cpp
Animal::Animal(void) : type("")
{
    std::cout << "Animal constructor called" << std::endl;
}

Animal::~Animal(void)
{
    std::cout << "Animal destructor called" << std::endl;
}

void Animal::makeSound(void) const
{
    std::cout << "Some animal sound..." << std::endl;
}

std::string Animal::getType(void) const
{
    return this->type;
}
```

### 🏗️ Classe Dog

**Dog.hpp :**
```cpp
class Dog : public Animal
{
public:
    Dog(void);
    Dog(const Dog &copy);
    Dog &operator=(const Dog &rhs);
    ~Dog(void);

    void makeSound(void) const;  // Override de la fonction virtuelle
};
```

**Dog.cpp :**
```cpp
Dog::Dog(void)
{
    this->type = "Dog";
    std::cout << "Dog constructor called" << std::endl;
}

Dog::~Dog(void)
{
    std::cout << "Dog destructor called" << std::endl;
}

void Dog::makeSound(void) const
{
    std::cout << "Woof! Woof!" << std::endl;
}
```

**Séquence de construction :**
```
Animal constructor called
Dog constructor called
```

**Séquence de destruction :**
```
Dog destructor called
Animal destructor called
```

### 🏗️ Classe Cat

Même structure que `Dog`, mais avec :
```cpp
void Cat::makeSound(void) const
{
    std::cout << "Meow! Meow!" << std::endl;
}
```

### 🔍 Test du polymorphisme

**main.cpp :**
```cpp
int main()
{
    const Animal* meta = new Animal();
    const Animal* j = new Dog();
    const Animal* i = new Cat();

    std::cout << j->getType() << " " << std::endl;
    std::cout << i->getType() << " " << std::endl;

    i->makeSound();  // ✅ Affiche "Meow! Meow!" (polymorphisme)
    j->makeSound();  // ✅ Affiche "Woof! Woof!" (polymorphisme)
    meta->makeSound();  // Affiche "Some animal sound..."

    delete meta;
    delete j;
    delete i;

    return 0;
}
```

**Sortie attendue :**
```
Animal constructor called
Animal constructor called
Dog constructor called
Animal constructor called
Cat constructor called
Dog
Cat
Meow! Meow!
Woof! Woof!
Some animal sound...
Animal destructor called
Dog destructor called
Animal destructor called
Cat destructor called
Animal destructor called
```

### 🏗️ Hiérarchie WrongAnimal (contre-exemple)

**WrongAnimal.hpp :**
```cpp
class WrongAnimal
{
protected:
    std::string type;

public:
    WrongAnimal(void);
    WrongAnimal(const WrongAnimal &copy);
    WrongAnimal &operator=(const WrongAnimal &rhs);
    ~WrongAnimal(void);  // ❌ PAS virtuel !

    void makeSound(void) const;  // ❌ PAS virtuel !
    std::string getType(void) const;
};
```

**WrongCat.hpp :**
```cpp
class WrongCat : public WrongAnimal
{
public:
    WrongCat(void);
    WrongCat(const WrongCat &copy);
    WrongCat &operator=(const WrongCat &rhs);
    ~WrongCat(void);

    void makeSound(void) const;  // Override, mais sans virtual dans la base
};
```

**Test :**
```cpp
const WrongAnimal* wrong = new WrongCat();
wrong->makeSound();  // ❌ Affiche "Some wrong animal sound" (pas de polymorphisme)
delete wrong;        // ⚠️ Appelle seulement ~WrongAnimal() (fuite potentielle)
```

**Pourquoi ?**
- Sans `virtual`, le compilateur choisit la fonction selon **le type du pointeur** (WrongAnimal*)
- Pas selon le type réel de l'objet (WrongCat)

### 💡 Comparaison

| Aspect | Animal (correct) | WrongAnimal (incorrect) |
|--------|------------------|-------------------------|
| Destructeur | `virtual ~Animal()` | `~WrongAnimal()` |
| makeSound() | `virtual` | Non virtuel |
| Polymorphisme | ✅ Fonctionne | ❌ Ne fonctionne pas |
| Pointeur base | Appelle la fonction dérivée | Appelle la fonction de base |
| Sécurité | ✅ Destructeur dérivé appelé | ⚠️ Risque de fuite |

---

## Exercice 01 : I don't want to set the world on fire

### 🎯 Objectif
Ajouter une classe `Brain` pour les animaux qui ont un cerveau.
Gérer la **Deep Copy** correctement avec des pointeurs.

### 📋 Concepts : Shallow Copy vs Deep Copy

**Shallow Copy (copie superficielle) :**
```cpp
class Dog {
private:
    Brain* brain;
public:
    Dog(const Dog &copy) : brain(copy.brain) {}
    // ❌ Problème : brain pointe vers le même objet que copy.brain
};
```

**Problème :**
- Deux objets partagent le même `Brain*`
- Si l'un est détruit, l'autre a un pointeur dangling
- Si l'un modifie le Brain, l'autre est affecté

**Deep Copy (copie profonde) :**
```cpp
class Dog {
private:
    Brain* brain;
public:
    Dog(const Dog &copy) : brain(new Brain(*copy.brain)) {}
    // ✅ Solution : nouveau Brain copié depuis l'original
};
```

### 🏗️ Classe Brain

**Brain.hpp :**
```cpp
class Brain
{
private:
    std::string ideas[100];  // 100 idées

public:
    Brain(void);
    Brain(const Brain &copy);
    Brain &operator=(const Brain &rhs);
    ~Brain(void);

    void setIdea(int idx, const std::string &idea);
    std::string getIdea(int idx) const;
};
```

**Brain.cpp :**
```cpp
Brain::Brain(void)
{
    std::cout << "Brain constructor called" << std::endl;
}

Brain::Brain(const Brain &copy)
{
    std::cout << "Brain copy constructor called" << std::endl;
    for (int i = 0; i < 100; i++)
        this->ideas[i] = copy.ideas[i];  // Copie chaque idée
}

Brain &Brain::operator=(const Brain &rhs)
{
    std::cout << "Brain copy assignment operator called" << std::endl;
    if (this != &rhs)
    {
        for (int i = 0; i < 100; i++)
            this->ideas[i] = rhs.ideas[i];
    }
    return *this;
}

Brain::~Brain(void)
{
    std::cout << "Brain destructor called" << std::endl;
}

void Brain::setIdea(int idx, const std::string &idea)
{
    if (idx >= 0 && idx < 100)
        this->ideas[idx] = idea;
}

std::string Brain::getIdea(int idx) const
{
    if (idx >= 0 && idx < 100)
        return this->ideas[idx];
    return "";
}
```

### 🏗️ Classe Dog (avec Brain)

**Dog.hpp :**
```cpp
class Dog : public Animal
{
private:
    Brain* brain;  // ⚠️ Pointeur vers Brain

public:
    Dog(void);
    Dog(const Dog &copy);
    Dog &operator=(const Dog &rhs);
    ~Dog(void);

    void makeSound(void) const;
};
```

**Dog.cpp :**
```cpp
Dog::Dog(void) : brain(new Brain())
{
    this->type = "Dog";
    std::cout << "Dog constructor called" << std::endl;
}

// Copy constructor avec Deep Copy
Dog::Dog(const Dog &copy) : Animal(copy), brain(new Brain(*copy.brain))
{
    std::cout << "Dog copy constructor called" << std::endl;
}

// Assignment operator avec Deep Copy
Dog &Dog::operator=(const Dog &rhs)
{
    std::cout << "Dog copy assignment operator called" << std::endl;
    if (this != &rhs)
    {
        Animal::operator=(rhs);
        delete this->brain;            // ⚠️ Libère l'ancien Brain
        this->brain = new Brain(*rhs.brain);  // Crée un nouveau Brain copié
    }
    return *this;
}

Dog::~Dog(void)
{
    delete this->brain;  // ⚠️ Libère le Brain
    std::cout << "Dog destructor called" << std::endl;
}

void Dog::makeSound(void) const
{
    std::cout << "Woof! Woof!" << std::endl;
}
```

### 🔍 Analyse des fonctions OCF

#### 1. Copy Constructor

```cpp
Dog::Dog(const Dog &copy) : Animal(copy), brain(new Brain(*copy.brain))
```

**Étapes :**
1. **`Animal(copy)`** : Copie les attributs d'Animal (type)
2. **`brain(new Brain(*copy.brain))`** :
   - Crée un nouveau Brain avec `new`
   - Initialise avec une copie de `copy.brain` (via copy constructor de Brain)
   - **Deep Copy** : objets indépendants

**Séquence d'appel :**
```
Animal copy constructor called
Brain copy constructor called
Dog copy constructor called
```

#### 2. Assignment Operator

```cpp
Dog &Dog::operator=(const Dog &rhs)
{
    if (this != &rhs)
    {
        Animal::operator=(rhs);     // Copie les attributs Animal
        delete this->brain;         // Libère l'ancien Brain
        this->brain = new Brain(*rhs.brain);  // Crée un nouveau Brain
    }
    return *this;
}
```

**Étapes critiques :**
1. **Protection auto-assignation** : `if (this != &rhs)`
2. **Copie de la base** : `Animal::operator=(rhs)`
3. **Libération** : `delete this->brain` (évite fuite mémoire)
4. **Deep Copy** : `new Brain(*rhs.brain)`

**⚠️ Danger sans `delete` :**
```cpp
// ❌ Sans delete
this->brain = new Brain(*rhs.brain);
// L'ancien Brain n'est jamais libéré → FUITE MÉMOIRE
```

#### 3. Destructeur

```cpp
Dog::~Dog(void)
{
    delete this->brain;  // ⚠️ Essentiel pour libérer la mémoire
    std::cout << "Dog destructor called" << std::endl;
}
```

**Séquence de destruction :**
```
Brain destructor called
Dog destructor called
Animal destructor called
```

### 💡 Test de Deep Copy

**main.cpp :**
```cpp
int main()
{
    Dog dog1;
    dog1.getBrain()->setIdea(0, "I want food");

    Dog dog2 = dog1;  // Copy constructor
    dog2.getBrain()->setIdea(0, "I want to play");

    std::cout << "Dog1 idea: " << dog1.getBrain()->getIdea(0) << std::endl;
    std::cout << "Dog2 idea: " << dog2.getBrain()->getIdea(0) << std::endl;

    return 0;
}
```

**Sortie attendue :**
```
Animal constructor called
Brain constructor called
Dog constructor called
Animal copy constructor called
Brain copy constructor called
Dog copy constructor called
Dog1 idea: I want food
Dog2 idea: I want to play
Brain destructor called
Dog destructor called
Animal destructor called
Brain destructor called
Dog destructor called
Animal destructor called
```

**Analyse :**
- Deux Brains distincts créés
- Modifier `dog2.brain` n'affecte pas `dog1.brain`
- Deux destructeurs Brain appelés (pas de double free)

---

## Exercice 02 : Abstract class

### 🎯 Objectif
Créer une classe abstraite `AAnimal` qui ne peut pas être instantiée.
Utiliser une **fonction virtuelle pure**.

### 📋 Concept : Classe Abstraite

**Définition :**
- Classe avec au moins une fonction virtuelle pure
- Ne peut pas être instantiée directement
- Force les classes dérivées à implémenter les fonctions pures

**Syntaxe :**
```cpp
class AbstractClass {
public:
    virtual void pureFunction() const = 0;  // ⚠️ = 0 : fonction pure
};
```

**Conséquences :**
```cpp
AbstractClass obj;  // ❌ ERREUR : classe abstraite non-instantiable
```

### 🏗️ Classe AAnimal (Abstract Animal)

**AAnimal.hpp :**
```cpp
class AAnimal
{
protected:
    std::string type;

public:
    AAnimal(void);
    AAnimal(const AAnimal &copy);
    AAnimal &operator=(const AAnimal &rhs);
    virtual ~AAnimal(void);

    virtual void makeSound(void) const = 0;  // ⚠️ Fonction pure virtuelle
    std::string getType(void) const;
};
```

**Différence avec Animal :**
```cpp
// Module 04 - ex00
virtual void makeSound(void) const;  // Virtuelle avec implémentation par défaut

// Module 04 - ex02
virtual void makeSound(void) const = 0;  // Pure virtuelle : pas d'implémentation
```

**AAnimal.cpp :**
```cpp
AAnimal::AAnimal(void) : type("")
{
    std::cout << "AAnimal constructor called" << std::endl;
}

AAnimal::~AAnimal(void)
{
    std::cout << "AAnimal destructor called" << std::endl;
}

std::string AAnimal::getType(void) const
{
    return this->type;
}

// ⚠️ Pas d'implémentation de makeSound() !
```

### 🏗️ Classes Dog et Cat (dérivées)

**Dog.hpp :**
```cpp
class Dog : public AAnimal
{
private:
    Brain* brain;

public:
    Dog(void);
    Dog(const Dog &copy);
    Dog &operator=(const Dog &rhs);
    ~Dog(void);

    void makeSound(void) const;  // ⚠️ OBLIGATOIRE d'implémenter
};
```

**Dog.cpp :**
```cpp
void Dog::makeSound(void) const
{
    std::cout << "Woof! Woof!" << std::endl;
}
```

**Si Dog n'implémente pas `makeSound()` :**
```cpp
class Dog : public AAnimal {
    // ❌ Pas d'implémentation de makeSound()
};

Dog dog;  // ❌ ERREUR : Dog est aussi abstraite !
```

### 🔍 Test de la classe abstraite

**main.cpp :**
```cpp
int main()
{
    // AAnimal animal;  // ❌ ERREUR de compilation : classe abstraite

    const AAnimal* dog = new Dog();
    const AAnimal* cat = new Cat();

    dog->makeSound();  // ✅ "Woof! Woof!"
    cat->makeSound();  // ✅ "Meow! Meow!"

    delete dog;
    delete cat;

    return 0;
}
```

### 💡 Concepts Clés

**Fonction virtuelle pure :**
```cpp
virtual void func() const = 0;  // = 0 : pas d'implémentation
```

**Classe abstraite :**
- ≥ 1 fonction pure virtuelle
- Non-instantiable
- Peut avoir constructeur/destructeur (appelés par classes dérivées)

**Classe concrète :**
- Toutes les fonctions pures sont implémentées
- Instantiable

**Interface (en C++) :**
- Classe avec **seulement** des fonctions pures virtuelles
- Pas d'attributs, pas de constructeur par défaut
- Exemple :
```cpp
class ICharacter {
public:
    virtual ~ICharacter() {}
    virtual void attack() = 0;
    virtual void defend() = 0;
};
```

### 🔗 Hiérarchie

```
     AAnimal (abstraite)
      /      \
     /        \
   Dog      Cat
(concrète) (concrète)
```

**Règles :**
- `AAnimal` ne peut pas être instanciée
- `Dog` et `Cat` doivent implémenter `makeSound()`
- On peut utiliser des pointeurs/références `AAnimal*` ou `AAnimal&`

---

## Exercice 03 : (vide - bonus non implémenté)

Cet exercice est vide dans votre code. Typiquement, il s'agit d'un exercice bonus qui n'est pas requis pour valider le module.

**Bonus possibles :**
- Interface pour d'autres types d'animaux
- Gestion avancée du polymorphisme
- Patterns comme Factory ou Strategy

---

## 📖 Résumé des Concepts du Module 04

### Ce que vous avez appris

#### 1. Polymorphisme

**Définition :**
- Utiliser des objets dérivés via des pointeurs/références de base
- Comportement adapté au type réel de l'objet

**Syntaxe :**
```cpp
Base* ptr = new Derived();
ptr->virtualFunction();  // Appelle Derived::virtualFunction()
```

#### 2. Fonctions Virtuelles

**Déclaration :**
```cpp
virtual void function() const;
```

**Effet :**
- Résolution dynamique (à l'exécution)
- Via la vtable (Virtual Table)

**Sans virtual :**
```cpp
void function() const;  // Résolution statique (à la compilation)
```

#### 3. Destructeurs Virtuels

**Règle :**
> Si une classe a au moins une fonction virtuelle, son destructeur DOIT être virtuel.

**Raison :**
```cpp
Base* ptr = new Derived();
delete ptr;  // Sans destructeur virtuel : seulement ~Base() appelé → FUITE
```

**Bonne pratique :**
```cpp
virtual ~Base() {}  // Assure que ~Derived() est appelé
```

#### 4. Classes Abstraites

**Définition :**
```cpp
class Abstract {
public:
    virtual void pureFunction() = 0;  // Fonction pure virtuelle
};
```

**Propriétés :**
- Non-instantiable
- Force les classes dérivées à implémenter les fonctions pures
- Peut avoir constructeur/destructeur

#### 5. Deep Copy vs Shallow Copy

**Shallow Copy :**
```cpp
Dog(const Dog &copy) : brain(copy.brain) {}  // ❌ Partage le même pointeur
```

**Deep Copy :**
```cpp
Dog(const Dog &copy) : brain(new Brain(*copy.brain)) {}  // ✅ Copie l'objet pointé
```

**Règle :**
> Si une classe a des pointeurs, implémentez toujours une Deep Copy dans :
> - Copy constructor
> - Assignment operator

#### 6. OCF avec Pointeurs

**Ce qu'il faut faire :**

**Copy Constructor :**
```cpp
Dog(const Dog &copy) : Animal(copy), brain(new Brain(*copy.brain)) {}
```

**Assignment Operator :**
```cpp
Dog &operator=(const Dog &rhs) {
    if (this != &rhs) {
        Animal::operator=(rhs);
        delete this->brain;              // Libère l'ancien
        this->brain = new Brain(*rhs.brain);  // Copie le nouveau
    }
    return *this;
}
```

**Destructor :**
```cpp
~Dog() {
    delete this->brain;  // Libère la mémoire
}
```

### Tableau récapitulatif

| Concept | ex00 | ex01 | ex02 |
|---------|------|------|------|
| Polymorphisme | ✅ | ✅ | ✅ |
| Fonctions virtuelles | ✅ | ✅ | ✅ |
| Destructeur virtuel | ✅ | ✅ | ✅ |
| Deep Copy | ❌ | ✅ | ✅ |
| Classe abstraite | ❌ | ❌ | ✅ |
| Gestion mémoire | Basique | Avancée | Avancée |

### Erreurs courantes à éviter

1. **Oublier le destructeur virtuel**
   ```cpp
   class Base {
   public:
       ~Base() {}  // ❌ Devrait être virtual
   };
   ```

2. **Shallow Copy avec pointeurs**
   ```cpp
   Dog(const Dog &copy) : brain(copy.brain) {}  // ❌ Partage le même Brain
   ```

3. **Oublier de libérer dans l'assignment operator**
   ```cpp
   Dog &operator=(const Dog &rhs) {
       brain = new Brain(*rhs.brain);  // ❌ Fuite : ancien brain non libéré
   }
   ```

4. **Double free**
   ```cpp
   Dog::~Dog() {
       delete brain;
   }
   // Si shallow copy, le même brain est supprimé deux fois → CRASH
   ```

5. **Instancier une classe abstraite**
   ```cpp
   AAnimal animal;  // ❌ ERREUR : classe abstraite
   ```

### Bonnes pratiques

1. **Toujours destructeur virtuel dans une classe de base**
   ```cpp
   class Base {
   public:
       virtual ~Base() {}
   };
   ```

2. **Deep Copy systématique avec pointeurs**
   ```cpp
   // Copy constructor
   Dog(const Dog &copy) : brain(new Brain(*copy.brain)) {}

   // Assignment operator
   Dog &operator=(const Dog &rhs) {
       if (this != &rhs) {
           delete brain;
           brain = new Brain(*rhs.brain);
       }
       return *this;
   }
   ```

3. **Protection auto-assignation**
   ```cpp
   if (this != &rhs) {
       // ...
   }
   ```

4. **Utiliser const pour les getters**
   ```cpp
   std::string getType(void) const;  // Ne modifie pas l'objet
   ```

5. **Utiliser const pour les méthodes virtuelles**
   ```cpp
   virtual void makeSound(void) const;  // Peut être appelée sur const Animal*
   ```

---

## ✅ Checklist de Validation

- [x] **ex00** : Classe Animal avec fonctions virtuelles
- [x] **ex00** : Destructeur virtuel
- [x] **ex00** : Classes Dog et Cat héritent d'Animal
- [x] **ex00** : Polymorphisme fonctionne (makeSound via Animal*)
- [x] **ex00** : WrongAnimal sans virtual (contre-exemple)
- [x] **ex01** : Classe Brain avec OCF complet
- [x] **ex01** : Dog et Cat ont un attribut Brain*
- [x] **ex01** : Deep Copy dans copy constructor
- [x] **ex01** : Deep Copy dans assignment operator
- [x] **ex01** : delete brain dans destructeur
- [x] **ex02** : Classe AAnimal abstraite
- [x] **ex02** : makeSound() est pure virtuelle (= 0)
- [x] **ex02** : AAnimal ne peut pas être instantiée
- [x] **ex02** : Dog et Cat implémentent makeSound()

---

**Module 04 terminé !** Vous maîtrisez maintenant le polymorphisme, les fonctions virtuelles, les classes abstraites et la gestion mémoire avancée avec Deep Copy. 🎉
