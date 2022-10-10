#include "../include/valid.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int validation(char *tempfile) {
    FILE *fptr = fopen((char *)tempfile, "r");
    if (fptr == NULL) {
        printf("File Error");
        exit(0);
    }

    int proID, proT, keyw;
    proID = proT = keyw = 0;

    char str[SIZE], *token;
    while (fgets(str, SIZE, fptr)) {
        token = strtok(str, "-");

        if (strcmp(token, project_id_str) == 0)
            proID += 1;
        else if (strcmp(token, project_title_str) == 0)
            proT += 1;
        else if (strcmp(token, keyword_str) == 0)
            keyw += 1;

        if (proID && proT && keyw)
            break;
    }

    (void)fclose(fptr);

    if (proID && proT && keyw)
        return 1;

    return 0;
}
