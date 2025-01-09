#include "task2.h"

#define NMAX 256

int main(int argc, char *argv[]) {
    // TODO(student): Task 2
    FILE* file = fopen(argv[1], "r");
    if (file == NULL) {
        return 0;
    }

    char* line = malloc(NMAX * sizeof(char));
    int number = 0;
    while (fgets(line, NMAX, file) != NULL) {
        sscanf(line, "%d", &number);

        line[strcspn(line, "\r\n")] = 0;

        if (line[0] == '\0') {
            continue;
        }
    }


    return 0;
}
