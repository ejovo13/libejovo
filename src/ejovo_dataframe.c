
#include "ejovo_dataframe.h"

// Routines dealing with the manipulating of multiple columns of data

Chain *newChain(const char *__str) {

    Chain *chain = (Chain *) malloc(sizeof(Chain));

    chain->next = NULL;
    chain->data = newStr(__str);

    // Duplicate the string so that chain is in charge of the strings that it carries
    return chain;
}

// Return the root node of the chain just in case the chain is initially empty
Chain *appendChain(Chain *__chain, const char *__str) {

    if (!__chain) return newChain(__str);

    Chain *it = __chain;

    while (it->next) {

        it = it->next;

    }

    it->next = newChain(__str);
    return __chain;
}

int sizeChain(const Chain *__chain) {

    int count = 0;
    const Chain *it = __chain;

    while (it) {
        count ++;
        it = it->next;
    }

    return count;
}

void printChain(const Chain *__chain) {

    if (!__chain) {
        printf("Chain does not exist!\n");
        return;
    };

    printf("Chain with size %d:\n", sizeChain(__chain));

    const Chain *it = __chain;
    while (it) {

        printf("%s -> ", it->data->str);
        it = it->next;
    }
    printf("\n");
}

Chain *newChainVar(int __count, ...) {

    va_list ptr;

    va_start(ptr, __count);
    char *s = va_arg(ptr, char *);

    if (__count == 0) return NULL;

    Chain *chain = newChain(s);

    for (int i = 1; i < __count; i++) {
        appendChain(chain, va_arg(ptr, char *));
    }

    return chain;
}

/**========================================================================
 *!                           Space functions
 *========================================================================**/
Space *newSpace( Vector_d *__v) {

    Space *space = (Space *) malloc(sizeof(Space));

    space->data = __v;
    space->next = NULL;

    return space;
}

Space *appendSpace(Space *__space, Vector_d *__v) {

    if (!__space) return newSpace(__v);

    Space *it = __space;

    while (it->next) {

        it = it->next;

    }

    it->next = newSpace(__v);
    return __space;
}

Space *newSpaceVar(int __count, ...) {

    va_list ptr;

    va_start(ptr, __count);
    Vector_d *v = va_arg(ptr, Vector_d *);

    if (__count == 0) return NULL;

    Space *space = newSpace(v);

    for (int i = 1; i < __count; i++) {
        appendSpace(space, va_arg(ptr, Vector_d *));
    }

    return space;
}


// Count the number of vectors in the space
int dimSpace(const Space *__space) {

    const Space *it = __space;
    int count = 0;

    while (it) {
        count ++;
        it = it->next;
    }

    return count;
}

// Print the number and addresses of the vectors in this space
void printSpace(const Space *__space) {

    if (!__space) {
        printf("Space does not exist\n");
        return;
    }

    printf("Space of dim %d\n", dimSpace(__space));

    const Space *it = __space;

    while (it) {
        printf("%p -> ", it->data);
        it = it->next;
    }
    printf("\n");
}

// verify that the dimensions of the matrices in __space are all the same
bool uniformSpace(const Space *__space) {

    if (!__space) return false;

    if (!__space->next) return true; // There is only one matrix

    const Space *it = __space;

    while (it->next) {

        if (!Matrix_comp_add_d(it->data, it->next->data)) return false;
        it = it->next;
    }

    return true;
}

// Now I want a structure that is a pointer to a chain and a pointer to a space.
// This object will be used for data exportation

// I should also be able to add a new column to a data frame
// when given a string and a conforming vector

DataFrame *newDataFrame(Chain *__chain, Space *__space) {

    DataFrame *df = (DataFrame *) malloc(sizeof(DataFrame));

    if (!df) return NULL;

    // Verify that the chain and the space have the same size
    if (sizeChain(__chain) != dimSpace(__space)) {
        printf("Error: chain and space are different sizes!!\n");
        return NULL;
    }

    if (!uniformSpace(__space)) {
        printf("Error: matrices in __space are not the same size!!\n");
        return NULL;
    }

    df->chain = __chain;
    df->space = __space;

    return df;
}

int dimDataFrame(const DataFrame *__df) {
    return dimSpace(__df->space);
}

void foreachSV(const DataFrame *__df, string_vector_fn fn) {

    if (!__df) return;

    const Chain *cit = __df->chain;
    const Space *sit = __df->space;

    while (cit && sit) {

        fn(cit->data, sit->data); // Call the function for some combination of chain and space

        cit = cit->next;
        sit = sit->next;

    }
}

void foreachString(const DataFrame *__df, string_fn fn) {

    if (!__df) return;

    const Chain *cit = __df->chain;

    while (cit) {

        fn(cit->data);

        cit = cit->next;

    }
}

void foreachVector(const DataFrame *__df, vector_fn fn) {

    if (!__df) return;

    const Space *sit = __df->space;

    while (sit) {

        fn(sit->data);
        sit = sit->next;
    }
}

// print the name of the col and then the first __nel elements
void printDataFrameCol(const String *__str, const Vector_d *__v) {

    print(__str);
    printf(": ");

    size_t nel = 10;
    // Print the first __nel elements
    int n = nel < Matrix_size_d(__v) ? nel : Matrix_size_d(__v); // get the smaller element

    printf("{");

    for (int i = 0; i < n - 1; i++) {
        printf("%7.3lf, ", Vector_at_d(__v, i));
    }

    printf("%7.3lf}\n", Vector_at_d(__v, n - 1));

}

void printDataFrame(const DataFrame *__df) {

    // first print the dimension and number of cols

    int nobs = Matrix_size_d(__df->space->data);

    printf("Df with %d observations and %d colums\n", nobs, dimDataFrame(__df));
    foreachSV(__df, printDataFrameCol);

}

void writeDelimiter(const DataFrame *__df, const char *__filename, const char delim) {

    if (!__df) return;

    FILE *f = fopen(__filename, "w");

    // the first line is all of the strings, separated with a column
    Chain *it = __df->chain;

    while (it->next) {

        fprintf(f, "%s,", it->data->str);
        it = it->next;
    }
    fprintf(f, "%s\n", it->data->str);

    // now iterate through all of vectors, accessing the ith print at each point.

    int size = Vector_size_d(__df->space->data);

    for (int i = 0; i < size; i++) {

        Space *it = __df->space;

        while (it->next) {

            fprintf(f, "%lf%c", Vector_at_d(it->data, i), delim);
            it = it->next;
        }
        fprintf(f, "%lf\n", Vector_at_d(it->data, i));
    }

    fclose(f);

}

void writeCSV(const DataFrame *__df, const char *__filename) {
    writeDelimiter(__df, __filename, ',');
}

void writeGP(const DataFrame *__df, const char *__filename) {

    if (!__df) return;

    FILE *f = fopen(__filename, "w");

    // the first line is all of the strings, separated with a column
    Chain *it = __df->chain;

    fprintf(f, "#");
    while (it->next) {

        fprintf(f, "%s,", it->data->str);
        it = it->next;
    }
    fprintf(f, "%s\n", it->data->str);

    // now iterate through all of vectors, accessing the ith print at each point.

    int size = Vector_size_d(__df->space->data);

    for (int i = 0; i < size; i++) {

        Space *it = __df->space;

        while (it->next) {

            fprintf(f, "%lf ", Vector_at_d(it->data, i));
            it = it->next;
        }
        fprintf(f, "%lf\n", Vector_at_d(it->data, i));
    }

    fclose(f);

}

// Return a pointer to the column in question
// Columns shall be ZERO indexed
 Vector_d *getColDF(const DataFrame *__df, int __j) {

    if (!__df) return NULL;

    const Space *it = __df->space;

    while (it && __j > 0) {
        it = it->next;
        __j --;
    }

    if (it) return it->data;
    else return NULL;
}

 Vector_d *save_doubles(double_fn fn, int n) {
    // Allocate a row vector of appropriate space
    Vector_d *out = Matrix_new_d(1, n);

    for (size_t i = 0; i < Matrix_size_d(out); i++) {
        out->data[i] = fn();
    }

    return out;
}