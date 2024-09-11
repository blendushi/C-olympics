#include "project.c"


int main(void){
    
    char input[1000]; //given input 
    char givenCommand; //given command 
    char nation[1000]; //given nation
    int gold; //num of gold medals
    int silver; //num of silver medals
    int bronze; //num of bronze medals
    char filename[1000]; //filename of the file in which we write
    char loadfilename[1000]; //filename of the file that we read of
    
    while(1){

        fgets(input, sizeof(input), stdin); //get given input

        sscanf(input, " %c ", &givenCommand); //scan for the command
        

        switch (givenCommand) //choose action based on command
        {
        case 'Q': //exit command
            printf("SUCCESS");
            releaseMemory();
            return 1;

        case 'A': //add nation command 
            if (sscanf(input, " %c %s", &givenCommand, nation) == 2) {
                if (addNation(nation) == 0) {
                    printf("SUCCESS\n");
                } 
            } else {
                printf("A should be followed by exactly 1 argument.\n");
            }
            break;

        case 'M': //add medals commmand
            if(sscanf(input, " %c %s %d %d %d", &givenCommand, nation, &gold, &silver, &bronze) == 5){
                if(addMedals(nation, gold, silver, bronze)==0){
                    printf("SUCCESS\n");
                }
            } else {
                printf("M should be followed by exactly 4 arguments.\n");
            }
            break;

        case 'L': //print all the nations command 
            printAllNations();
            printf("SUCCESS\n");
            break;

        case 'W': //write to file command 
            sscanf(input, " %c %s", &givenCommand, filename);
            int result = writeFile(filename);
            if(result == 0){
                printf("SUCCESS\n");
            }
            break;

        case 'O': //load from file command
            sscanf(input, " %c %s", &givenCommand, loadfilename);
            int loadresult = loadFile(loadfilename);
            if(loadresult == 0){
                printf("SUCCESS\n");
            }
            break;

        default: //if non of the above are given
            printf("Invalid command %c\n", givenCommand);
            break;

        }
    }
    
}