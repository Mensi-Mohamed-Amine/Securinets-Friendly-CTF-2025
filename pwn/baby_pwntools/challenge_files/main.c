// gcc main.c -o main
#include <stdio.h>
#include <stdlib.h>

#define CYAN   "\033[36m"
#define YELLOW "\033[33m"
#define GREEN  "\033[32m"
#define RED    "\033[31m"
#define RESET  "\033[0m"

void setup();
void banner();
void win();

void vuln() {
    int64_t secret = 0xc0d3b4b3;

    printf("My secret is 0x%016lx\n> ", secret);
    fgets((char*)&secret, 0x8, stdin);

    puts("Did you pull it off?");
    puts("Moment of truth...");
    printf("My secret is now 0x%016lx\n", secret);

    if (secret == 0x0) {
        puts("You did it!");
        puts("Thank you");
        win();
    } else {
        puts("There are still traces of my secret out there!");
        puts("The memory needs to be nulled");
        puts("Please use pwntools to wipe it out");
    }
}

int main(void) {
    setup();
    banner();
    vuln(); // The vulnerability is right here. This is the ONLY function you need to focus on.
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

void win() {
    FILE *f = fopen("./flag", "rb");
    if (!f) { perror("fopen"); exit(-1); }

    char c;
    while((c = fgetc(f)) != EOF) {
        fputc(c, stdout);
    }
    fclose(f);
}

void banner() {
    puts("I have a secret locked in memory.");
    puts("Wipe it clean, and a reward awaits you.");
    puts("Null bytes are forbidden by your keyboard.");
    puts("You’ll need more than typing—pwntools is your friend.");
    puts("");
}
