#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#ifndef VEC_H
#define VEC_H

// different approach
#define push_back(VEC, DATA) _Generic((DATA), \
    int: push_int, \
    char*: push_string, \
    char: push_char, \
    double: push_double, \
    float: push_float \
)(VEC, DATA)

// struct, enum and union
typedef union {
    int i;
    double d;
    float f;
    char c;
    char* s;
    void* p;
} Value;

typedef enum {
    TYPE_INT,
    TYPE_CHAR,
    TYPE_STRING,
    TYPE_DOUBLE,
    TYPE_FLOAT,
} dataType;

typedef struct {
    Value** items; // dynamic array of pointers
    dataType* dataType; // i'm not refactoring the name now bro :broken_heart:
    int capacity;
    int size;
} Vec;

// declarations
int push_int(Vec* vector, int value);
int push_string(Vec* vector, char* value);
int push_char(Vec* vector, char value);
int push_double(Vec* vector, double value);
int push_float(Vec* vector, float value);

int init_vector(Vec *vector);
int priv_push_back(Vec *vector, Value* data, dataType v_type);
int pop_back(Vec *vector);
int clean_vec(Vec *vector);

#endif // vec.h
