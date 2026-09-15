#include "../include/conversor.h"
#include "windows.h"

int encode_utf8(uint64_t input, unsigned char utf8[4]) {
    if (input <= 127){
        utf8[0] = input;
        return 1;
    }

    if (input <= 2047){
        utf8[0] = 192 | (input >> 6);
        utf8[1] = 128 | (input & 63);
        return 2;
    }

    if (input <= 65535) {
        if (input >= 55296 && input <= 57343){
            return 0;
        }

        utf8[0] = 224 | (input >> 12);
        utf8[1] = 128 | ((input >> 6) & 63);
        utf8[2] = 128 | (input & 63);
        return 3;
    }

    if (input <= 1114111){
        utf8[0] = 240 | (input >> 18);
        utf8[1] = 128 | ((input >> 12) & 63);

        utf8[2] = 128 | ((input >> 6) & 63);
        // for math lovers, the line above is literally just:
        // utf8[2] = 128 + (input / (int)pow(2, 6)) % (63 + 1);

        utf8[3] = 128 | (input & 63);
        return 4;
    }

    return 0;
}

int encode_utf8_math_edition(uint64_t input, unsigned char utf8[4]) {
    if (input <= 127){
        utf8[0] = input;
        return 1;
    }

    if (input <= 2047){
        utf8[0] = 192 + (input / (int)power_of(2,6));
        utf8[1] = 128 + (input % (63 + 1));

        return 2;
    }

    if (input <= 65535) {
        if (input >= 55296 && input <= 57343){
            return 0;
        }
        utf8[0] = 224 + (input / (int)power_of(2,12));
        utf8[1] = 128 + ((input / (int)power_of(2,6)) % (63 + 1));
        utf8[2] = 128 + (input % (63 + 1));

        return 3;
    }

    if (input <= 1114111){
        utf8[0] = 240 + (input / (int)power_of(2,18));
        utf8[1] = 128 + (input / (int)power_of(2,12)) % (63 + 1);
        utf8[2] = 128 + (input / (int)power_of(2,6)) % (63 + 1);
        utf8[3] = 128 + (input % (63 + 1));

        return 4;
    }

    return 0;
}

// FUCK <math.h> (jk)
// this function sucks anyway
double power_of(int x, int y) {
    double result = 1;
    if (y == 0) {
        return result;
    } else if (y >= 1) {
        for (int i = 0; i < y; i++){
            result = result * x;
        }
    } else {
        int pos_y = y * (-1);
        for (int i = 0; i < pos_y; i++){
            result = result * x;
        }
        result = 1 / result;
    }

    return result;
}

int rest(int time) {
    // still windows only, sadly
    Sleep(1000 * time);
    // dev note: i hate Win32 API so much
    return 0;
}

// end
