#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#ifndef CONVERSOR_H
#define CONVERSOR_H

// declare
double power_of(int x, int y);
int encode_utf8(uint64_t input, unsigned char utf8[4]);
int encode_utf8_math_edition(uint64_t input, unsigned char utf8[4]);
double power_of(int x, int y);

// use unsigned char[5] to properly use encode_utf8 functions

#endif // conversor.h
