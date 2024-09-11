#ifndef _PROJECT__H_
#define _PROJECT__H_

typedef struct {
    char *name;
    int gold;
    int silver;
    int bronze;
} Nation;

int addNation(const char* name);

int addMedals(const char* nation ,int gold, int silver, int bronze);

int printAllNations();

int writeFile(char *filename);

int loadFile(char *filename);

void releaseMemory();

char *strdup(const char *src);

int compareNations(const void *a, const void *b);

#endif //! _PROJECT__H_