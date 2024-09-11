#include "project.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INITIAL_CAPACITY 10

Nation *nations = NULL;  //list of the nations given
int numNations = 0;  //number of nations given 
int capacity = 0;  //capacity of nations  which is actually arbitrarily increasing

//string copying function strdup (string duplicate)
char *strdup(const char *src){
    size_t len = strlen(src) + 1;
    char *dest = (char *)malloc(len);
    if(dest){
        memcpy(dest, src, len);
    }
    return dest;
}

//nation adding function
int addNation(const char* name){

    //check if the nation already exists
    for(int i = 0; i < numNations; i++){ 
        if(strcmp(nations[i].name, name) == 0){
            printf("Nation \"%s\" is already in the database.\n", name);
            return 1;
        }
    }

    // Ensure enough capacity and allocate memory
    if (numNations == capacity) {
        capacity += INITIAL_CAPACITY;
        nations = realloc(nations, capacity * sizeof(Nation));
        if (!nations) {
            printf("Error: Memory allocation failed.\n");
            exit(EXIT_FAILURE);
        }
    }

    // Add the new nation
    nations[numNations].name = strdup(name);
    nations[numNations].gold = 0;
    nations[numNations].silver = 0;
    nations[numNations].bronze = 0;
    numNations++;

    
    return 0;
}

int addMedals(const char* nation, int gold, int silver, int bronze){

    //check for the given nation
    for(int i = 0; i < numNations; i++){
        if(strcmp(nations[i].name, nation) == 0){

            //check if the medals we get after addition are positive
            if((gold < 0 && abs(nations[i].gold) < abs(gold) ) || (silver < 0 && abs(nations[i].silver) < abs(silver)) || (bronze < 0 && abs(nations[i].bronze) < abs(bronze))){
                printf("A nation cannot have negative number of medals\n");
                return 1;
            } 
            //add medals 
            nations[i].gold += gold;
            nations[i].silver += silver;
            nations[i].bronze += bronze; 
            return 0;
        }
    }
    printf("error: Nation not found\n");
    return 1;
}

//comparing function with sorts nations for printAllNations function
int compareNations(const void *a, const void *b){
    const Nation *nationA = (const Nation *)a;
    const Nation *nationB = (const Nation *)b;

    if(nationA->gold != nationB->gold){
        return nationB->gold - nationA->gold; //sort by gold medals in descending order
    } else if(nationA->silver != nationB->silver){
        return nationB->silver - nationA->silver; //sort by silver medals in descending order 
    } else if(nationA->bronze != nationB->bronze){
        return nationB->bronze - nationA->bronze; //sort by bronze medals in descending order 
    } else { 
        return 0; //else print in the given order
    }
}

//prints nations in medals order (most golds then most silvers etc.)
// nation A(medals) == nation B(medals) then print in given order 
int printAllNations(){

    // Sort the nations array using the custom sorting function
    qsort(nations, numNations, sizeof(Nation), compareNations);

    //print the sorted nations
    for(int i = 0; i < numNations; i++){
        printf("%s %d %d %d\n", nations[i].name, nations[i].gold, nations[i].silver, nations[i].bronze);
    }
    return 0;
}

//writes the current state of the program into a txt file
int writeFile(char *filename){

    //open file
    FILE *file = fopen(filename, "w");
    if(!file){
        printf("error couldn't open file\n");
        return 1;
    }

    //print all nations to the file 
    for(int i = 0; i < numNations; i++){
        fprintf(file, "%s %d %d %d\n", nations[i].name, nations[i].gold, nations[i].silver, nations[i].bronze);
    }

    //close file
    fclose(file);
    return 0;
}

//loads a program state from file
int loadFile(char *filename){

    //open file to "readmode"
    FILE *file = fopen(filename, "r");

    if(!file){
        printf("Cannot open file invalid-test.txt for reading.\n");
        return 1;
    }

    //read file line by line
    char input[1000];
    while(fgets(input, sizeof(input), file)){
        char name[1000];
        int gold;
        int silver; 
        int bronze;

        //get the nation names and medals
        int argumentsGotten = sscanf(input, "%s %d %d %d", name, &gold, &silver, &bronze);

        //error if not enough arguments gotten
        if (argumentsGotten != 4){
            printf("error invalid data format in file\n");
            fclose(file);
            return 1; 
        }
        
        //check if nation is already given so the program doesn't get duplicates
        int nationIndex = -1;
        for(int i = 0; i < numNations; i++){
            if(strcmp(nations[i].name,name) == 0){
                nationIndex = i;
                break;
            }
        }

        //if nation already given then change the state of that nation
        if(nationIndex != -1){
            nations[nationIndex].gold = gold;
            nations[nationIndex].silver = silver;
            nations[nationIndex].bronze = bronze;
        } else {
            addNation(name);
            addMedals(name, gold, silver, bronze);
        }

    }

    //close file
    fclose(file);
    return 0;

}

//release memory when exiting program
void releaseMemory() {
    if (nations == NULL) {
        return; // Nothing to release
    }
    for (int i = 0; i < numNations; i++) {
        free(nations[i].name);
    }
    free(nations);
}
