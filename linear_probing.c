#include <stdio.h>
#include <string.h>
#include <stdbool.h>

// Constants
#define MAX_NAME 100
#define MAX_TABLE_SIZE 10

// Content
typedef struct {
    char name[MAX_NAME];
    unsigned int age;
} Person;

// Hash Table
Person *persons[MAX_TABLE_SIZE];


// Initialize hash table with default NULL
void init_hash_table() {
    for(int i = 0; i < MAX_TABLE_SIZE; i++) persons[i] = NULL;
}


// Print the contents of hash table
void print_hash_table() {
    for(int i = 0; i < MAX_TABLE_SIZE; i++) {
        if(persons[i] == NULL) {
            printf("%d\t--\n", i);
        } else {
            printf("%d\t%s\n", i, persons[i]->name);
        }
    }
}


// Hash function
unsigned int hash(const char *name) {
    int len = strlen(name);
    unsigned int hashed_value = 0;
    for(int i = 0; i < len; i++) {
        hashed_value += name[i];
        hashed_value = (hashed_value * name[i]) % MAX_TABLE_SIZE;
    }
    return hashed_value;
}


// Insert into hash table
bool insert(Person *p) {
    if(p == NULL) return false; 
    int h = hash(p->name);
    // Linear probing
    for(int i = 0; i < MAX_TABLE_SIZE; i++) {
        h = (h + i) % MAX_TABLE_SIZE;
        if(persons[h] == NULL) {
            persons[h] = p;
            return true;
        }
    }
    return false;
}


// Look up or Access
Person *lookup(const char *name) {
    int h = hash(name);
    if(persons[h] == NULL)  return NULL;
    for(int i = 0; i < MAX_TABLE_SIZE; i++) {
        h = (h + i) % MAX_TABLE_SIZE;
        if((persons[h] != NULL) && (strcmp(persons[h]->name, name) == 0)) {
            return persons[h];
        }
    }
    return NULL;
}


// Delete
Person *delete(const char *name) {
    int h = hash(name);

    for(int i = 0; i < MAX_TABLE_SIZE; i++) {
        h = (h + i) % MAX_TABLE_SIZE;
        if((persons[h] != NULL) && (strcmp(persons[h]->name, name) == 0)) {
            Person *tmp = persons[h];
            persons[h] = NULL;
            return tmp;
        }
    }
    return NULL;
}




int main() {
    
    init_hash_table();

    Person deshrit = {.name = "Deshrit Baral", .age = 23};
    Person sabin = {.name = "Sabin Baral", .age = 23};
    Person kabin = {.name = "Kabin", .age = 20};
    Person babin = {.name = "Babin Tamang", .age = 19};
    Person rabin = {.name = "Rabin Khatiwada", .age = 25};
    Person monkey = {.name = "Monkey Khatiwada", .age = 25};
    Person donkey = {.name = "Donkey Karki", .age = 25};

    insert(&deshrit);
    insert(&sabin);
    insert(&kabin);
    insert(&babin);
    insert(&rabin);
    insert(&monkey);
    insert(&donkey);

    print_hash_table();

    

    // Find
    const char *name = "Sabin Baral";
    Person *tmp = lookup(name);
    if(tmp == NULL) {
        printf("\n'%s'not found **", name);
        return 0;
    }
    printf("\n'%s' found **", name);

    

    // Delete
    tmp = delete(name);
    if(tmp != NULL) {
        printf("\nDeleted\n\n");
    }


    // print the table
    print_hash_table();
}