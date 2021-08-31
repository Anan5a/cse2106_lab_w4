#include <iostream>

using namespace std;

/*
 * Problem: You are a programmer in charge of creating a Zoo management system.
 * Write a basic program to keep track of the animals
 */
string getZooName();

/*
 * Clear input buffer i.e newline
 */
void clear_input_buffer() {
    while (getchar() != '\n');
}
/*
 * Struct to hold unit data
 */
struct Animal {
    string name;
    string location;
    int male = 0;
    int female = 0;
    int childMale = 0;
    int childFemale = 0;
};
/*
 * Actual program
 * This handle all functionality of the management
 */
class ZooAnimalManager {
    /* Animal list, holds struct of unique animal */
    struct Animal *animals;
    /*
     * size of the animals pointer
     */
    int pointerSize = 0;
    /* Name of the zoo */
    string ZooName;
public:
    /*
     * constructor, allocate memory 0 bytes to create a valid pointer
     */
    ZooAnimalManager() {
        animals = (struct Animal *) malloc(sizeof(struct Animal) * 0);
    }
    /*
     * constructor, allocate memory 0 bytes to create a valid pointer
     * also update ZooName
     */

    ZooAnimalManager(string name) {
        animals = (struct Animal *) malloc(sizeof(struct Animal) * 0);
        ZooName = name;
    }
    /*
     * Setter: Sets zoo name at a later point in program execution
     */
    void setZooName(string);
    /*
     * Add a new animal to the list
     */
    void addAnimal(struct Animal);
    /*
     * Get populations
     */
    int getPopulationChildMale();

    int getPopulationChildFemale();

    int getPopulationMale();

    int getPopulationFemale();

    int getPopulationChild();

    int getPopulation();
    /*
     * Get ZooName while running the program
     */
    string getZooName();
    /*
     * return an animal if it exists
     */
    struct Animal *getAnimal(string);
    /*
     * return pointer size
     */
    int getTotalUniqueAnimal() {
        return pointerSize;
    }
    /*
     * return the base pointer of animals
     */
    struct Animal *getBasePointer() {
        return animals;
    }
    /*
     * friend function, gets zoo name from outside the class
     */
    friend string getZooName(ZooAnimalManager);

private:
    struct Animal *findAnimal(struct Animal);
};
/*
 * Implementations
 */
string getZooName(ZooAnimalManager zoo) {
    return zoo.ZooName;
}

inline void ZooAnimalManager::setZooName(string name) {
    ZooName = name;
}

inline string ZooAnimalManager::getZooName() {
    return ZooName;
}

void ZooAnimalManager::addAnimal(struct Animal animal) {
    struct Animal *animalptr = findAnimal(animal);
    if (animalptr != nullptr) {
        /* The animal already in zoo, increase population */
        animalptr->childFemale += animal.childFemale;
        animalptr->childMale += animal.childMale;
        animalptr->male += animal.male;
        animalptr->female += animal.female;
    } else {
        /* new animal in the zoo! */
        struct Animal *tmp = (struct Animal *) realloc(animals, sizeof(struct Animal) * (++pointerSize));
        if (tmp != NULL) {
            animals = tmp;
        }
        animals[pointerSize - 1] = animal;
    }
}

struct Animal *ZooAnimalManager::findAnimal(struct Animal animal) {
    int i = pointerSize;
    while (i >= 0) {
        if (animals[i - 1].name.compare(animal.name) == 0) {
            return &animals[i - 1];
        }
        i--;
    }
    return nullptr;
}

struct Animal *ZooAnimalManager::getAnimal(string name) {
    struct Animal animal;
    animal.name = name;
    struct Animal *animalptr = findAnimal(animal);
    return animalptr;
}

int ZooAnimalManager::getPopulation() {
    int population = 0;
    for (int i = 0; i < pointerSize; ++i) {
        population += animals[i].male + animals[i].female + animals[i].childFemale + animals[i].childMale;
    }
    return population;
}

int ZooAnimalManager::getPopulationChild() {
    int population = 0;
    for (int i = 0; i < pointerSize; ++i) {
        population += animals[i].childFemale + animals[i].childMale;
    }
    return population;
}

int ZooAnimalManager::getPopulationChildFemale() {
    int population = 0;
    for (int i = 0; i < pointerSize; ++i) {
        population += animals[i].childFemale;
    }
    return population;
}

int ZooAnimalManager::getPopulationChildMale() {
    int population = 0;
    for (int i = 0; i < pointerSize; ++i) {
        population += animals[i].childMale;
    }
    return population;
}

int ZooAnimalManager::getPopulationFemale() {
    int population = 0;
    for (int i = 0; i < pointerSize; ++i) {
        population += animals[i].female;
    }
    return population;
}

int ZooAnimalManager::getPopulationMale() {
    int population = 0;
    for (int i = 0; i < pointerSize; ++i) {
        population += animals[i].male;
    }
    return population;
}

/*
 * End Implementations
 */

/*
 * Print unit animal
 */
void PrintAnimal(struct Animal *animal) {
    cout << "Animal name: " << animal->name << endl << "Located at: " << animal->location << endl
         << "Population Child: " << animal->childMale << "(M) + " << animal->childFemale << "(F)" << endl;
    cout << "Population Adult: " << animal->male << "(M) + " << animal->female << "(F)" << endl;
    cout << "Total: " << animal->male + animal->female + animal->childFemale + animal->childMale << endl;
}
/*
 * Print choice list
 */
void PrintChoice() {
    cout << "What to do?" << endl << "a: add more animal" << endl << "b: print all animals" << endl
         << "c: find about an animal" << endl << "d: get zoo status" << endl << "e: exit program" << endl;
}
/*
 * Print program banner
 */
void printHeader() {
    cout << "===Welcome to ZooManager===" << endl;
    cout << "Name your zoo to start!" << endl;
}
/*
 * Take input of an animal
 */
void TakeInputAnimal(ZooAnimalManager *zoo) {
    struct Animal animal;
    cout << "Enter an animal name: ";
    getline(cin, animal.name);
    cout << "Where is it located inside zoo? ";
    getline(cin, animal.location);
    cout << "How many males are there? ";
    cin >> animal.male;
    cout << "How many females are there? ";
    cin >> animal.female;
    cout << "How many male childs are there? ";
    cin >> animal.childMale;
    cout << "How many female childs are there? ";
    cin >> animal.childFemale;
    zoo->addAnimal(animal);
    clear_input_buffer();

    return;
}
/*
 * Find an animal by name
 */
void Action_find_Animal(ZooAnimalManager *zoo) {
    string name;
    cout << "Enter the animal name: ";
    getline(cin, name);
    struct Animal *animal = zoo->getAnimal(name);
    if (animal != NULL)
        PrintAnimal(animal);
    else
        cout << "No animal found by this name!" << endl;
    cout << endl;
}
/*
 * Print all animal in the zoo
 */
void PrintAllAnimal(ZooAnimalManager *zoo) {
    struct Animal *ptr = zoo->getBasePointer();
    for (int i = 0; i < zoo->getTotalUniqueAnimal(); ++i) {
        PrintAnimal(&ptr[i]);
    }
    cout << endl;
}
/*
 * Print zoo status
 */
void PrintZooStatus(ZooAnimalManager *zoo) {
    cout << "Zoo name: " << zoo->getZooName() << endl;
    cout << "Unique animals: " << zoo->getTotalUniqueAnimal() << endl;
    cout << "Total animals: " << zoo->getPopulation() << endl;
    cout << "Males: " << zoo->getPopulationMale() << endl;
    cout << "Females: " << zoo->getPopulationFemale() << endl;
    cout << "Child Males: " << zoo->getPopulationChildMale() << endl;
    cout << "Child Females: " << zoo->getPopulationChildFemale() << endl;
    cout << endl;
}
/*
 * main()
 */
int main() {
    printHeader();
    string name;
    getline(cin, name);
    ZooAnimalManager zoo(name);
    label:
    PrintChoice();
    char choice;
    cin >> choice;
    clear_input_buffer();
//    system("clear");
    switch (choice) {
        case 'a':
            TakeInputAnimal(&zoo);
            break;
        case 'b':
            PrintAllAnimal(&zoo);
            break;
        case 'c':
            Action_find_Animal(&zoo);
            break;
        case 'd':
            PrintZooStatus(&zoo);
            break;
        case 'e':
            return 0;
            break;
        default:
            goto label;
    }
    goto label;
    return 0;
}
