#include <stdlib.h>

typedef struct {
    char *data;
} test;

void bad_malloc() {
    test  d1;
    test *d2 = malloc(sizeof(test));

    int *int_data = (int *)malloc(sizeof(int));  // test comment
    int *ll       = NULL;                        // test comment
    // test comment
    if (1) {  // Test if
        char *temp = malloc(sizeof(char) * 100);
        // no check here
        for (int i = 0; i < 10; ++i) {
            // nested here
            char *ks = malloc(10);

            d2->data = malloc(10);  // test modify
        }
        ll = calloc(1, 1);  // test calloc

        d1.data = malloc(sizeof(test));
        // test bad if check
        if (1) {
            return;
        }
    }
    /*
    d2 = malloc(sizeof(test));
    Comment test
    */
}

void good_malloc() {
    test  d1;
    test  list[10];
    test *d2 = malloc(sizeof(test));
    if (d2) {
    }  // in one line

    int *int_data = (int *)malloc(sizeof(int));  // test comment
    if (!int_data) {
    }
    int *ll = NULL;  // test comment
    // test comment
    if (1) {  // Test if
        char *temp = malloc(sizeof(char) * 100);
        if (1 && temp || 0) {
            // test other condition
            return;
        }
        // no check here
        for (int i = 0; i < 10; ++i) {
            // nested here
            char *ks = malloc(10);
            if (ks != NULL) {
                // use != NULL
                return;
            }

            d2->data = malloc(10);  // test modify
            if (d2->data == NULL) {
                // use NULL
                return;
            }

            list[i].data = malloc(i * 100);  // Array
            if (d2->data && list[i].data || NULL) {
                return;
            }
        }
        ll = calloc(1, 1);  // test calloc
        if (ll == NULL) {   // use ()
            return;
        }

        if (ll = malloc(4)) {  // FIXME: known false-positive
            // Do sth
        }

        if (!(ll = malloc(4))) {  // FIXME: known false-positive
            exit(-1);
        }

        d1.data = malloc(sizeof(test));
        // test bad if check
        if (!d1.data) {  // use !
            free(d2->data);
            exit(-1);  // use other things
        }
    }
    switch (0) {
        case 1:
            char *a = malloc(10);
            if (!a) {
                exit(-1);
            }
            break;
        case 2:
            (void)0;
            char *b = malloc(10);
            if (!b) {
                exit(-1);
            }
            break;
        case 3:
            int k = 1;
            char *c = malloc(10);
            break;
    }
    /*
    d2 = malloc(sizeof(test));
    Comment test
    */
}
