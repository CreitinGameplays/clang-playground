#include "include/vec.h"
#include "include/conversor.h"
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
    
    // TEST ONE
    // push 1mi times
    for (int i = 0; i < 1000000; i++){
        char x[72];
        snprintf(x, sizeof(x), "hey i am the string number %d", i);
        char* val = strdup(x);
        push_back(&my_vec, val);
        free(val); // clean up after push_back
    }

    printf("before sleep, going sleep...\n");
    
    rest(10);

    printf("after sleep\n");

    // casting boring
    printf("TEST: %s, %f, %s, %c, %d\n",
        my_vec.items[5]->s, my_vec.items[0]->d,
        my_vec.items[1400]->s, my_vec.items[2]->c,
        my_vec.items[3]->i
    );

    printf("freeing...\n");
    clean_vec(&my_vec); clean_vec(&my_vec); // no double free, second call
    // will fail gracefully (should at least)
    printf("sleep again after free...\n");
    rest(10);
    printf("done\n");

    // TEST TWO
    init_vector(&my_vec); // make the vec

    // push 1mi times, again
    for (int i = 0; i < 1000000; i++){
        char x[72];
        snprintf(x, sizeof(x), "hey there again i am the string number %d", i);
        char* val = strdup(x);
        push_back(&my_vec, val);
        free(val); // clean up after push_back
    }

    printf("before sleep, going sleep...\n");
    rest(10);
    printf("after sleep\n");

    printf("freeing...\n");
    clean_vec(&my_vec);
    printf("sleep again after free...\n");
    rest(10);
    printf("done\n");

    // DECIMAL TEST
    // test the decimal to utf-8
    unsigned char test[5] = {0}; // must initialize with zeros or this will crash
    encode_utf8_math_edition(128405, test);
    // output
    printf("Decimal to UTF-8: %s", test);

    return 0;
}
