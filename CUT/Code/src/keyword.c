#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../header/header.h"

// Function to validate the input file
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
    }

    (void)fclose(fptr);

    if (proID == 1 && proT == 1 && keyw >= 1)
        return 1;

    return 0;
}

// Extract the project details from the given text files
void *extract_project_details(void *tempfile) {
    FILE *fptr = fopen((char *)tempfile, "r");

    // Check for file error
    if (fptr == NULL) {
        printf("\nError! file not found: %s\n", (char *)tempfile);
        return NULL;
    }
    // Check for Valid text file according to guides lines
    else if (validation((char *)tempfile) == 0) {
        printf("\nError! File invalid <%s>\n", (char *)tempfile);
        FILE *inv = fopen("data/invalid.txt", "a+");
        if (inv == NULL) {
            printf("File Error");
            exit(0);
        }
        fprintf(inv, "%s\n", (char *)tempfile);
        fclose(inv);

    }
    // Extract details if file valid
    else {
        printf("\nExtracting.. %s", (char *)tempfile);

        sp *new_pro_node = (sp *)calloc(1, sizeof(sp));
        if (new_pro_node == NULL) {
            printf("Memory Error");
            exit(0);
        }

        char str[SIZE], *token, keySearch[SIZE];
        while (fgets(str, SIZE, fptr)) {
            token = strtok(str, "-");
            while (token != NULL) {
                if (strcmp(token, project_id_str) == 0) {
                    token = strtok(NULL, "-");
                    token[strlen(token) - 1] = '\0';
                    strcpy(new_pro_node->projectId, token);
                }

                else if (strcmp(token, project_title_str) == 0) {
                    token = strtok(NULL, "-");
                    token[strlen(token) - 1] = '\0';
                    strcpy(new_pro_node->projectTitle, token);
                }

                else if (strcmp(token, keyword_str) == 0) {
                    token = strtok(NULL, "-");
                    strcpy(keySearch, token);
                    keywordSearch(new_pro_node, keySearch, &keywordll);
                }

                token = strtok(NULL, "-");
            }
        }
        free(new_pro_node);
    }

    (void)fclose(fptr);
}


skw *createNode(sp *p1, char token[]) {
    skw *newNode = (skw *)calloc(1, sizeof(skw));
    if (newNode == NULL) {
        printf("Memory Error");
        exit(0);
    }
    strcpy(newNode->key, token);
    strcpy(newNode->projectIds[newNode->index], p1->projectId);
    strcpy(newNode->projectTitle[newNode->index], p1->projectTitle);
    newNode->index += 1;

    //  Initialize Mutex
    if (pthread_mutex_init(&(newNode->lock), NULL) != 0) {
        printf("\nError! Mutex init has failed\n");
        cleanFunc();
        exit(0);
    }
    return newNode;
}

void updateNode(sp *p1, skw *temp) {

    // lock mutex
    (void)pthread_mutex_lock(&(temp->lock));

    strcpy(temp->projectIds[temp->index], p1->projectId);
    strcpy(temp->projectTitle[temp->index], p1->projectTitle);
    temp->index += 1;

    // unlock Mutex
    (void)pthread_mutex_unlock(&(temp->lock));
}


void keywordSearch(sp *p1, char *token, skw **keywordll) {
    token[strlen(token) - 1] = '\0';

    // check if the linked list is empty
    if ((*keywordll) == NULL) {
        skw *newNode = (skw *)createNode(p1, token);
        (*keywordll) = newNode;
    } else {
        skw *temp = *keywordll, *last;
        while (temp != NULL) {
            if (strcmp(temp->key, token) == 0) {
                updateNode(p1, temp);
                return;
            }
            last = temp;
            temp = temp->next;
        }
        last->next = createNode(p1, token);
    }
}


// Function to free the memory at the end of program
void cleanFunc() {
    skw *temp1;
    while (keywordll != NULL) {
        temp1 = keywordll;
        keywordll = keywordll->next;
        (void)pthread_mutex_destroy(&(temp1->lock));
        free(temp1);
    }
}
