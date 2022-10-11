#include <stdio.h>
#include <stdlib.h>


#include "../header/header.h"

//Function to print
void print_output(skw *temp) {
    while (temp != NULL) {
        printf("\n%s", temp->key);
        int i;
        for (i = 0; i < temp->index; ++i) {
            printf("\n%s", temp->projectIds[i]);
            printf("\n%s", temp->projectTitle[i]);
        }

        printf("\n\n");
        temp = temp->next;
    }
}


//Function to write output to the file
int write_output(skw *temp) {
    FILE *fptr;
    fptr = fopen("data/keywordProject.txt", "w");
    if (!fptr) {
        printf("\nerror");
        return EXIT_FAILURE;
    }

    while (temp != NULL) {
        fprintf(fptr, "Key-%s", temp->key);
        int i;
        for (i = 0; i < temp->index; ++i) {
            fprintf(fptr, "\n%s", temp->projectIds[i]);
            fprintf(fptr, "\n%s", temp->projectTitle[i]);
        }

        fprintf(fptr, "\n\n\n");

        temp = temp->next;
    }

    (void)fclose(fptr);
    return EXIT_SUCCESS;
}
