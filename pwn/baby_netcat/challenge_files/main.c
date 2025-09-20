// gcc main.c -o main
#include <stdio.h>

void setup();
void win();

int main(void) {
    setup(); // Ignore this
    win();
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

void win() {
    FILE *f = fopen("./flag", "rb");
    if (!f) { perror("fopen"); return; }

    char c;
    while((c = fgetc(f)) != EOF) {
        fputc(c, stdout);
    }
    fclose(f);
}

void setup() {
    setbuf(stdin, NULL);
    setbuf(stdout, NULL);
    setbuf(stderr, NULL);
}

