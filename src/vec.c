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

    strcpy(v->s, value); // "string copy?"
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
    // NULLing them before mallocs is mandatory, we're using goto for cleanup
    // we cannot safely free something that was never even initialized
    vector->items = NULL;
    vector->dType = NULL;

    vector->items = malloc(sizeof(*vector->items) * vector->capacity);
    if (vector->items == NULL) { // malloc fail
        fprintf(stderr, "malloc fail\n");
        goto clean;
    }

    vector->dType = malloc(sizeof(*vector->dType) * vector->capacity);
    if (vector->dType == NULL) { // malloc fail (MALLOCA)
        fprintf(stderr, "malloc fail\n");
        goto clean;
    }

    return 0;

// I just thought goto would be a cleaner approach, Claude agreed
// must be here at the end
clean:
    free(vector->items);
    vector->items = NULL;
    free(vector->dType);
    vector->dType = NULL;
    return 1;
}

int priv_push_back(Vec *vector, Value* data, dataType v_type) {
    if (vector->size == vector->capacity){
        int new_cap = vector->capacity * 2; // separate var for safety

        Value** temp = realloc(vector->items, new_cap * sizeof(*vector->items)); // items needs to be realloc'd
        if (temp == NULL){ // realloc fail
            fprintf(stderr, "realloc fail\n");
            return 1;
        }
        vector->items = temp;

        // ALSO realloc dType
        dataType* temp2 = realloc(vector->dType, new_cap * sizeof(dataType));
        if (temp2 == NULL){ // realloc fail
            fprintf(stderr, "realloc fail\n");
            return 1;
        }
        vector->dType = temp2;
        vector->capacity = new_cap; // assign now, reallocs worked
    }

    // assign the values
    vector->items[vector->size] = data;
    vector->dType[vector->size] = v_type; // v_type enum
    vector->size++;
    return 0;
}

int pop_back(Vec *vector) {
    if (vector->size == 0){
        fprintf(stderr, "error: vector is already empty.\n");
        return 1;
    } else {
        vector->size--; // decrease one
        // if the last item of the vector is not null
        if (vector->items[vector->size] != NULL){
            // God's optimization
            // strings are big af
            if (vector->dType[vector->size] == TYPE_STRING){ // if the last item is a TYPE_STRING
                free(vector->items[vector->size]->s); // free it
            }
            free(vector->items[vector->size]); // free the last item
            vector->items[vector->size] = NULL;
        }

        // resize the vector
        if (vector->size < vector->capacity / 4) { // 25%
            int new_cap = vector->capacity / 2;
            Value** temp = realloc(vector->items, new_cap * sizeof(*vector->items));
            
            if (temp == NULL){ // realloc fail
                fprintf(stderr, "realloc fail\n");
                return 1;
            }
            vector->items = temp;

            // realloc dType
            dataType* temp2 = realloc(vector->dType, new_cap * sizeof(dataType));

            if (temp2 == NULL){ // realloc fail
                fprintf(stderr, "realloc fail\n");
                return 1;
            }
            vector->dType = temp2;
            vector->capacity = new_cap; // vector capacity = vector capacity / 2 (after realloc's for safety)
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
        // loop each vector item
        for (int a = 0; a < vector->size; a++){
            if (vector->dType[a] == TYPE_STRING){ // free strings, they're big
                free(vector->items[a]->s);
            }
            free(vector->items[a]); // free each element
        }
        free(vector->items);
        vector->items = NULL;
    }

    // free dType if it's not NULL
    if (vector->dType != NULL) {
        free(vector->dType);
        vector->dType = NULL;
    }

    // then zero everything
    vector->size = 0;
    vector->capacity = 0;
    printf("clean-up success\n");

    return 0;
}

