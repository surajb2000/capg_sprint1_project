#ifndef HEADER_H
#define HEADER_H
#include <pthread.h>
#define STR_SIZE 500
#define SIZE 500
#define ARR_SIZE 50
#define project_id_str "Project ID"
#define keyword_str "Keyword"
#define project_title_str "Project Title"

typedef struct project {
    char projectId[STR_SIZE];
    char projectTitle[STR_SIZE];
    struct project *next;
} sp;

typedef struct keyword {
    char key[ARR_SIZE];
    char projectIds[ARR_SIZE][20];
    char projectTitle[ARR_SIZE][STR_SIZE];
    int index;
    // to do define keyword mutex
    pthread_mutex_t lock;
    struct keyword *next;
} skw;

extern sp *projectll;
extern skw *keywordll;

void *extract_project_details(void *);
void keywordSearch(sp *, char *, skw **);
int validation(char *tempfile);
int result_Valid(char *key);
void cleanFunc();

void print_output(skw *);
int write_output(skw *);

#endif