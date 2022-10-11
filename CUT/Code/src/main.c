#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../header/header.h"

//head pointer to keyword linked list
skw *keywordll;

int main(int argc, char **argv) {

    keywordll = NULL;
    int filecount = argc - 1;

    // checking if arguments are provided.
    if (filecount < 1) {
        printf("Please provide  filename as argument!\n");
        printf("Usage ./main <Research Papaer file1> <Research Papaer file2> ...\n");
        exit(0);
    }

    //Create an empty invalid file.txt
    FILE *ptr = fopen("data/invalid.txt", "w+");
    fclose(ptr);


    /*
    creates a new thread for each file.
    filter and create new linklist containing valid filenames.
    */
    pthread_t pthreads[filecount];
    int i;
    for (i = 0; i < filecount; i++) {
        int ret = pthread_create(&pthreads[i], NULL, extract_project_details, (void *)(argv[i + 1]));

        // check if thread created for return value
        if (ret != 0) {
            printf("\nError! Thread creation falied! Return code from is: %d\n", ret);
            exit(0);
        }
    }

    // Wait for pthread_join before resuming the program.
    for (i = 0; i < filecount; i++) {
        pthread_join(pthreads[i], NULL);
    }

    // Function defined in output.c to output the keyword linkedlist
    print_output(keywordll);

    // Function defined in output.c to write the output to a file
    int c = write_output(keywordll);
    if (c == EXIT_FAILURE)
        return EXIT_FAILURE;


    cleanFunc();
    return 0;
}
