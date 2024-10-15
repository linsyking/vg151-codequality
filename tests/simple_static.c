#include <stdlib.h>
#include <getopt.h>

typedef struct {
    char *s;
} kb;

static int x = 10;

int ashkdas = 132;

static char y;  // Not allowed

const char *res[10] = {"123"};

void test_malloc() {
    kb                   ff;
    static const int     sjl = 2130;
    static int           slls;    // Allowed
    static int           dhkasd;  // Allowed
    static struct option long_options[] = {};
    char                *Test1          = (char *)malloc(14);
    int                 *Tt             = NULL;
    *Tt                                 = 23;
    Tt                                  = calloc(sizeof(int) * 10, 12);
    ff.s                                = malloc(12);
    if (ff.s == NULL) {
        return;
    }
    free(Test1);
}

void static_test() {
    static int i = 0;  // Allowed
    while (1) {
        static char l = 0;  // Allowed
    }
}
