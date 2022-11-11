#include <stdio.h>
#include <string.h>
#include <stdbool.h>

// constants
#define MAX_NAME 100
#define MAX_TABLE_SIZE 10

// content
typedef struct {
    char name[MAX_NAME];
    unsigned int age;
} Person;

// Table
Person *persons[MAX_TABLE_SIZE];

void init_hash_table() {
    for(int i = 0; i < MAX_TABLE_SIZE; i++) persons[i] = NULL;
}


void print_hash_table() {
    for(int i = 0; i < MAX_TABLE_SIZE; i++) {
        if(persons[i] == NULL) {
            printf("%d\t--\n", i);
        } else {
            printf("%d\t%s\n", i, persons[i]->name);
        }
    }
}

// hash function
unsigned int hash(const char *name) {
    int len = strlen(name);
    unsigned int hashed_value = 0;
    for(int i = 0; i < len; i++) {
        hashed_value += name[i];
        hashed_value = (hashed_value * name[i]) % MAX_TABLE_SIZE;
    }
    // hashed_value = hashed_value % MAX_TABLE_SIZE;
    return hashed_value;
}

// insert into hash table
bool insert(Person *p) {
    if(p == NULL) return false; 
    int h = hash(p->name);
    if(persons[h] == NULL) {
        persons[h] = p;
        return true;
    }
    return false;
}


// look up or access
Person *lookup(const char *name) {
    int h = hash(name);
    if(persons[h] == NULL)  return NULL;
    else if( (persons[h] != NULL) &&  (strcmp(persons[h]->name, name) == 0) )   return persons[h];
    else    return NULL;
}


// delete
Person *delete(const char *name) {
    int h = hash(name);
    if((persons[h] != NULL) && (strcmp(persons[h]->name, name) == 0)) {
        Person *tmp = persons[h];
        persons[h] = NULL;
        return tmp;
    }
    return NULL;
}


int main() {
    
    init_hash_table();

    Person deshrit = {.name = "Deshrit Baral", .age = 23};
    Person sabin = {.name = "Sabin Baral", .age = 23};

    insert(&deshrit);
    insert(&sabin);
    insert(&sabin);

    print_hash_table();

    // Person *t = lookup("Deshrit Baral");
    Person *t = lookup("Sabin Baral");

    if(t == NULL) {
        printf("\nnot found **");
        return 0;
    }
    printf("\nfound **");
    Person *tmp = delete("Sabin Baral");
    if(tmp != NULL) {
        printf("\nDeleted\n\n");
    }

    print_hash_table();
}