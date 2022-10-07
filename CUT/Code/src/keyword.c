#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../header/header.h"

void *extract_project_details(void *tempfile) {
    FILE *fptr = fopen((char *)tempfile, "r");

    // Check for file error
    if (fptr == NULL) {
        printf("\nError! file not found: %s\n", (char *)tempfile);
    }
    // Check for Valid text file according to guides lines
    else if (validation((char *)tempfile) == 0) {
        printf("\nError! File invalid <%s>\n", (char *)tempfile);
        FILE *inv = fopen("data/invalid.txt", "w+");
        if (inv == NULL) {
            printf("File Error");
            exit(0);
        }
        fprintf(inv, "%s\n", (char *)tempfile);

    }
    // Extract details if file valid
    else {
        printf("\nExtracting.. %s", (char *)tempfile);

        sp *new_pro_node = (sp *)calloc(1, sizeof(sp));
        if (new_pro_node == NULL) {
            printf("Memory Error");
            exit(0);
        }
        // new_pro_node->next = NULL;

        int proID, proT, keyw;
        proID = proT = keyw = 0;

        char str[SIZE], *token, keySearch[SIZE];
        while (fgets(str, SIZE, fptr)) {
            token = strtok(str, "-");
            while (token != NULL) {
                if (strcmp(token, project_id_str) == 0)
                    proID += 1;

                else if (proID == 1) {
                    token[strlen(token) - 1] = '\0';
                    strcpy(new_pro_node->projectId, token);
                    proID = 0;
                    /*

                    if (projectll == NULL)
                        projectll = new_pro_node;
                    else {
                        sp *temp = projectll;

                        while (temp->next != NULL) {
                            temp = temp->next;
                        }
                        temp->next = new_pro_node;
                        new_pro_node->next = NULL;

                    }
                    */
                }

                else if (strcmp(token, project_title_str) == 0)
                    proT += 1;

                else if (proT == 1) {
                    token[strlen(token) - 1] = '\0';
                    strcpy(new_pro_node->projectTitle, token);
                    proT = 0;
                }

                else if (strcmp(token, keyword_str) == 0)
                    keyw += 1;

                else if (keyw == 1) {
                    strcpy(keySearch, token);
                    keywordSearch(new_pro_node, keySearch, &keywordll);
                    keyw = 0;
                }

                token = strtok(NULL, "-");
            }
        }
        free(new_pro_node);
    }

    (void)fclose(fptr);
}

skw *createNode(sp *p1, char token[]) {
    // printf("%s",token);
    skw *newNode = (skw *)calloc(1, sizeof(skw));
    if (newNode == NULL) {
        printf("Memory Error");
        exit(0);
    }
    strcpy(newNode->key, token);
    // newNode->index = 0;
    strcpy(newNode->projectIds[newNode->index], p1->projectId);
    strcpy(newNode->projectTitle[newNode->index], p1->projectTitle);
    newNode->index += 1;
    // newNode->next = NULL;
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

    if ((*keywordll) == NULL) {
        /*
        skw *newNode = (skw *)calloc(1, sizeof(skw));
        strcpy(newNode->key, token);
        newNode->index = 0;
        strcpy(newNode->projectIds[newNode->index], p1->projectId);
        strcpy(newNode->projectTitle[newNode->index], p1->projectTitle);
        newNode->index += 1;
        newNode->next = NULL;
        // Initialize Mutex
        if (pthread_mutex_init(&(newNode->lock), NULL) != 0) {
            printf("\nError! Mutex init has failed\n");
            cleanFunc();
            exit(0);
        }
        */

        skw *newNode = (skw *)createNode(p1, token);
        (*keywordll) = newNode;

    } else {
        skw *temp = *keywordll;
        if (strcmp(temp->key, token) == 0) {
            /*
            // Lock Mutex
            pthread_mutex_lock(&(temp->lock));

            strcpy(temp->projectIds[temp->index], p1->projectId);
            strcpy(temp->projectTitle[temp->index], p1->projectTitle);
            temp->index += 1;

            // unlock Mutex
            pthread_mutex_unlock(&(temp->lock));
            */
            updateNode(p1, temp);
        } else {
            while (temp->next != NULL) {
                if (strcmp(temp->next->key, token) == 0) {
                    /*
                    // Lock Mutex
                    pthread_mutex_lock(&(temp->next->lock));

                    strcpy(temp->next->projectIds[temp->next->index], p1->projectId);
                    strcpy(temp->next->projectTitle[temp->next->index], p1->projectTitle);
                    temp->next->index += 1;

                    // Unlock Mutex
                    pthread_mutex_unlock(&(temp->next->lock));
                    */
                    updateNode(p1, temp->next);
                    return;
                }
                temp = temp->next;
            }
            temp->next = createNode(p1, token);
            /*
            (skw *)calloc(1, sizeof(skw));
            strcpy(temp->next->key, token);
            strcpy(temp->next->projectIds[temp->next->index], p1->projectId);
            strcpy(temp->next->projectTitle[temp->next->index], p1->projectTitle);
            temp->next->index += 1;
            temp->next->next = NULL;

            // Initialize Mutex
            if (pthread_mutex_init(&(temp->next->lock), NULL) != 0) {
                printf("\nError! Mutex init has failed\n");
                cleanFunc();
                exit(0);
            }
            */
        }
    }
}

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

void cleanFunc() {
    /*
    sp *temp;
    while (projectll != NULL) {
        temp = projectll;
        projectll = projectll->next;

        free(temp);
    }
    */

    skw *temp1;
    while (keywordll != NULL) {
        temp1 = keywordll;
        keywordll = keywordll->next;

        (void)pthread_mutex_destroy(&(temp1->lock));
        free(temp1);
    }
}

/*

int result_Valid(char *key) {
  FILE *fptr = fopen("../data/result.txt", "r");
  if (!fptr) printf("\nError: Result file not found");

  int flag = 0, count = 0;
  char str[SIZE], *token;

  // reading line by line
  while (fgets(str, SIZE, stdin)) {
    token = strtok(str, " ");

    if (flag == 1) {
      if (strcmp(token, "Keyword:") == 0) break;

      count += 1;
    }


    while (token != NULL && flag != 1) {
      if (strcmp(key, token) == 0) {
        flag = 1;
      }

      token = strtok(NULL, " ");
    }
  }

  return count;
}

*/
