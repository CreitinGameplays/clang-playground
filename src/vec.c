#include "../include/vec.h"

// c11 - unused codeblock
/*
#define get_type(x) _Generic((x), \
    int: "int", \
    char: "char", \
    char*: "string", \
    double: "double", \
    float: "float", \
    default: "unknown" \
)
*/

// start
int push_int(Vec* vector, int value){
    Value* v = malloc(sizeof(Value));
    if (!v) return 1;
    v->i = value;
    priv_push_back(vector, v, TYPE_INT);
    return 0;
}

int push_string(Vec* vector, char* value){
    Value* v = malloc(sizeof(Value));
    if (!v) return 1;
    v->s = value;
    priv_push_back(vector, v, TYPE_STRING);
    return 0;
}

int push_char(Vec* vector, char value){
    Value* v = malloc(sizeof(Value));
    if (!v) return 1;
    v->c = value;
    priv_push_back(vector, v, TYPE_CHAR);
    return 0;
}

int push_double(Vec* vector, double value){
    Value* v = malloc(sizeof(Value));
    if (!v) return 1;
    v->d = value;
    priv_push_back(vector, v, TYPE_DOUBLE);
    return 0;
}

int push_float(Vec* vector, float value){
    Value* v = malloc(sizeof(Value));
    if (!v) return 1;
    v->f = value;
    priv_push_back(vector, v, TYPE_FLOAT);
    return 0;
}
// end

int init_vector(Vec *vector) {
    vector->size = 0;
    vector->capacity = 4;
    vector->items = malloc(sizeof(*vector->items) * vector->capacity);
    if (vector->items == NULL) { // malloc fail
        fprintf(stderr, "malloc fail\n");
        return 1;
    }

    vector->dataType = malloc(sizeof(*vector->dataType) * vector->capacity);
    if (vector->dataType == NULL) { // malloc fail (MALLOCA)
        fprintf(stderr, "malloc fail\n");
        return 1;
    }
    return 0;
}

int priv_push_back(Vec *vector, void* data, dataType v_type) {
    if (vector->size == vector->capacity){
        vector->capacity *= 2;
        Value** temp = (Value**)realloc(vector->items, vector->capacity * sizeof(void*)); // items needs to be realloc'd
        
        if (temp == NULL){ // realloc fail
            fprintf(stderr, "realloc fail\n");
            return 1;
        }
        // ALSO realloc dataType
        dataType* temp2 = realloc(vector->dataType, vector->capacity * sizeof(dataType));

        if (temp2 == NULL){ // realloc fail
            fprintf(stderr, "realloc fail\n");
            return 1;
        }
        vector->items = temp;
        vector->dataType = temp2; // grow dataType
    }

    vector->items[vector->size] = data;
    vector->dataType[vector->size] = v_type;
    vector->size++;
    return 0;
}

int pop_back(Vec *vector) {
    if (vector->size == 0){
        fprintf(stderr, "error: vector is already empty.\n");
        return 1;
    } else {
        vector->size--; // less one

        // remove item
        if (vector->items[vector->size] != NULL){
            vector->items[vector->size] = NULL; // null first
            vector->dataType[vector->size] = 0;
            free(vector->items[vector->size]); // then free
        }

        if (vector->size < vector->capacity / 4) { // 25%
            vector->capacity /= 2;
            void** temp = realloc(vector->items, vector->capacity * sizeof(void*));
            
            if (temp == NULL){ // realloc fail
                fprintf(stderr, "realloc fail\n");
                return 1;
            }
            // realloc dataType
            void** temp2 = realloc(vector->dataType, vector->capacity * sizeof(void*));

            if (temp2 == NULL){ // realloc fail
                fprintf(stderr, "realloc fail\n");
                return 1;
            }
        }
    }
    return 0;
}

int clean_vec(Vec *vector) {
    if (vector->items != NULL) {
        vector->items = NULL;
        vector->dataType = NULL;
        free(vector->items);
        free(vector->dataType);
        printf("clean-up sucess\n");
    } else {
        fprintf(stderr, "clean-up fail\n");
        return 1;
    }
    return 0;
}

