#include "../include/vec.h"

// start
int push_int(Vec* vector, int value){
    Value* v = malloc(sizeof(Value));
    if (!v) return 1;
    v->i = value;
    if (priv_push_back(vector, v, TYPE_INT) != 0){
        free(v);
        return 1;
    }
    return 0;
}

// string is special
int push_string(Vec* vector, char* value){
    Value* v = malloc(sizeof(Value));
    if (!v) return 1;
    v->s = malloc(strlen(value) + 1);

    if (!v->s) { // error check
        free(v);
        return 1;
    }

    strcpy(v->s, value);
    if (priv_push_back(vector, v, TYPE_STRING) != 0) {
        free(v->s);
        free(v);
        return 1;
    }
    return 0;
}

int push_char(Vec* vector, char value){
    Value* v = malloc(sizeof(Value));
    if (!v) return 1;
    v->c = value;
    if (priv_push_back(vector, v, TYPE_CHAR) != 0) {
        free(v);
        return 1;
    }
    return 0;
}

int push_double(Vec* vector, double value){
    Value* v = malloc(sizeof(Value));
    if (!v) return 1;
    v->d = value;
    if (priv_push_back(vector, v, TYPE_DOUBLE) != 0){
        free(v);
        return 1;
    }
    return 0;
}

int push_float(Vec* vector, float value){
    Value* v = malloc(sizeof(Value));
    if (!v) return 1;
    v->f = value;
    if (priv_push_back(vector, v, TYPE_FLOAT) != 0){
        free(v);
        return 1;
    }
    return 0;
}

// end
int init_vector(Vec *vector) {
    vector->size = 0;
    vector->capacity = 4;
    vector->items = malloc(sizeof(*vector->items) * vector->capacity);
    if (vector->items == NULL) { // malloc fail
        fprintf(stderr, "malloc fail\n");
        free(vector->items);
        vector->items = NULL;
        return 1;
    }

    vector->dataType = malloc(sizeof(*vector->dataType) * vector->capacity);
    if (vector->dataType == NULL) { // malloc fail (MALLOCA)
        fprintf(stderr, "malloc fail\n");
        free(vector->dataType);
        vector->dataType = NULL;
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
            free(vector->items[vector->size]); // free
            vector->items[vector->size] = NULL;
            vector->dataType[vector->size] = 0;
        }

        if (vector->size < vector->capacity / 4) { // 25%
            vector->capacity /= 2;
            void** temp = realloc(vector->items, vector->capacity * sizeof(void*));
            
            if (temp == NULL){ // realloc fail
                fprintf(stderr, "realloc fail\n");
                free(temp);
                return 1;
            }
            // realloc dataType
            void** temp2 = realloc(vector->dataType, vector->capacity * sizeof(void*));

            if (temp2 == NULL){ // realloc fail
                fprintf(stderr, "realloc fail\n");
                free(temp);
                return 1;
            }
        }
    }
    return 0;
}

int clean_vec(Vec *vector) {
    if (vector == NULL) {
        fprintf(stderr, "clean-up fail\n");
        return 1;
    }
    if (vector->items != NULL) {
        for (int a = 0; a < vector->size; a++){
            if (vector->dataType[a] == TYPE_STRING){ // free string
                free(vector->items[a]->s);
            }
            free(vector->items[a]); // free each element
        }
        free(vector->items);
        vector->items = NULL;
    }

    if (vector->dataType != NULL) {
        free(vector->dataType);
        vector->dataType = NULL;
    }

    vector->size = 0;
    vector->capacity = 0;
    printf("clean-up success\n");

    return 0;
}

