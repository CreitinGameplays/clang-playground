#include "include/vec.h"
//#include "windows.h" // FUCK Win32 API

int main(void) {
    Vec my_vec;
    init_vector(&my_vec); // make the vec

    // test with different types
    push_back(&my_vec, 2.4);
    push_back(&my_vec, "hey there");
    push_back(&my_vec, 'L');
    push_back(&my_vec, 80);
    push_back(&my_vec, "im the five");
    push_back(&my_vec, "femboys are tuff");
    
    // push +30k times
    for (int i = 0; i < 32768; i++){
        char x[72];
        snprintf(x, sizeof(x), "hey i am the string number %d", i);
        char* val = strdup(x); // alloc
        push_back(&my_vec, val);
    }

    // casting boring
    printf("TEST: %s, %f, %s, %c, %d\n",
        my_vec.items[5]->s, my_vec.items[0]->d,
        my_vec.items[1400]->s, my_vec.items[2]->c,
        my_vec.items[3]->i
    );

    clean_vec(&my_vec); clean_vec(&my_vec); // no double free, second call will fail gracefully (should at least)
    return 0;
}
