// gcc main.c -o main
#include <stdio.h>
#include <stdlib.h>

void setup();

int main(void) {
    setup(); // Ignore this
    system("/bin/sh");
    return 0;
}

//
//
//
// NOTE for players: The functions below are ONLY debugging/utility helpers.
// They are NOT related to the vulnerability or required to solve the challenge.
// Focus on the main code above.
//
//
//

void setup() {
    setbuf(stdin, NULL);
    setbuf(stdout, NULL);
    setbuf(stderr, NULL);
}
