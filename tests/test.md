# Test

## `unchecked-malloc-result` 

### Input

```c
#include <stdlib.h>

typedef struct {
    char *data;
} test;


void bad_malloc() {
    test d1;
    test *d2 = malloc(sizeof(test));

    int *int_data = (int *)malloc(sizeof(int)); // test comment
    int *ll = NULL;     // test comment
    // test comment
    if(1){   // Test if
        char *temp = malloc(sizeof(char)*100);
        if(temp && ll){
            // test condition which includes other unrelated variables
            return;
        }
        // no check here
        for(int i = 0; i < 10; ++i){
            // nested here
            char *ks = malloc(10);

            d2->data = malloc(10); // test modify
        }
        ll = calloc(1,1); // test calloc

        d1.data = malloc(sizeof(test));
        // test bad if check
        if (1){
            return;
        }
    }
    /*
    d2 = malloc(sizeof(test));
    Comment test
    */
}

void good_malloc() {
    test d1;
    test *d2 = malloc(sizeof(test));
    if(d2){}    // in one line

    int *int_data = (int *)malloc(sizeof(int)); // test comment
    if(!int_data){}
    int *ll = NULL;    // test comment
    // test comment
    if(1){   // Test if
        char *temp = malloc(sizeof(char)*100);
        if(1 && temp || 0 ){
            // test other condition
            return;
        }
        // no check here
        for(int i = 0; i < 10; ++i){
            // nested here
            char *ks = malloc(10);
            if(ks != NULL){
                // use != NULL
                return;
            }

            d2->data = malloc(10); // test modify
            if(d2->data == NULL){
                // use NULL
                return;
            }
        }
        ll = calloc(1,1); // test calloc
        if(ll){ // use ()
            return;
        }


        d1.data = malloc(sizeof(test));
        // test bad if check
        if (!d1.data){   // use !
            free(d2->data);
            exit(-1);   // use other things
        }
    }
    /*
    d2 = malloc(sizeof(test));
    Comment test
    */
}
```

### Output

```
/home/linsy/Projects/JI/vg151-codequality/tests/complicated_malloc.c:10:16: error: variable 'd2' is dynamically allocated here, but you don't check if its value is NULL [codequality-unchecked-malloc-result,-warnings-as-errors]
    test *d2 = malloc(sizeof(test));
               ^
/home/linsy/Projects/JI/vg151-codequality/tests/complicated_malloc.c:12:5: note: add 'if' to check whether it's NULL
    int *int_data = (int *)malloc(sizeof(int)); // test comment
    ^
/home/linsy/Projects/JI/vg151-codequality/tests/complicated_malloc.c:12:28: error: variable 'int_data' is dynamically allocated here, but you don't check if its value is NULL [codequality-unchecked-malloc-result,-warnings-as-errors]
    int *int_data = (int *)malloc(sizeof(int)); // test comment
                           ^
/home/linsy/Projects/JI/vg151-codequality/tests/complicated_malloc.c:13:5: note: add 'if' to check whether it's NULL
    int *ll = NULL;     // test comment
    ^
/home/linsy/Projects/JI/vg151-codequality/tests/complicated_malloc.c:16:22: error: variable 'temp' is dynamically allocated here, but you don't check if its value is NULL [codequality-unchecked-malloc-result,-warnings-as-errors]
        char *temp = malloc(sizeof(char)*100);
                     ^
/home/linsy/Projects/JI/vg151-codequality/tests/complicated_malloc.c:17:12: note: this 'if' statement is not checking 'temp' properly
        if(temp && ll){
           ^
/home/linsy/Projects/JI/vg151-codequality/tests/complicated_malloc.c:24:24: error: variable 'ks' is dynamically allocated here, but you don't check if its value is NULL [codequality-unchecked-malloc-result,-warnings-as-errors]
            char *ks = malloc(10);
                       ^
/home/linsy/Projects/JI/vg151-codequality/tests/complicated_malloc.c:26:13: note: add 'if' to check whether it's NULL
            d2->data = malloc(10); // test modify
            ^
/home/linsy/Projects/JI/vg151-codequality/tests/complicated_malloc.c:26:24: error: variable 'd2' is dynamically allocated here, but you don't check if its value is NULL [codequality-unchecked-malloc-result,-warnings-as-errors]
            d2->data = malloc(10); // test modify
                       ^
/home/linsy/Projects/JI/vg151-codequality/tests/complicated_malloc.c:26:33: note: add 'if' to check whether it's NULL
            d2->data = malloc(10); // test modify
                                ^
/home/linsy/Projects/JI/vg151-codequality/tests/complicated_malloc.c:28:14: error: variable 'll' is dynamically allocated here, but you don't check if its value is NULL [codequality-unchecked-malloc-result,-warnings-as-errors]
        ll = calloc(1,1); // test calloc
             ^
/home/linsy/Projects/JI/vg151-codequality/tests/complicated_malloc.c:30:9: note: add 'if' to check whether it's NULL
        d1.data = malloc(sizeof(test));
        ^
/home/linsy/Projects/JI/vg151-codequality/tests/complicated_malloc.c:30:19: error: variable 'd1' is dynamically allocated here, but you don't check if its value is NULL [codequality-unchecked-malloc-result,-warnings-as-errors]
        d1.data = malloc(sizeof(test));
                  ^
/home/linsy/Projects/JI/vg151-codequality/tests/complicated_malloc.c:32:13: note: this 'if' statement is not checking 'd1' properly
        if (1){
            ^
```

