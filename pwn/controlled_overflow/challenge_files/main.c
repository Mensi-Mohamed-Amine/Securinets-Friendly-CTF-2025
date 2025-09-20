// gcc main.c -o main -Wno-implicit-function-declaration

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
void dump_stack();

void vuln() {
    int64_t key = 0x1337;
    volatile int64_t pad = 0x0;
    char buffer[8];
    dump_stack(); // This function is ONLY here for debugging/visibility. Skip it.
    gets(buffer);
    dump_stack(); // This function is ONLY here for debugging/visibility. Skip it.

    if (key == 0x1337) {
        puts("key is intact, no flag for you");
    } else if (key == 0x3030303030303030) {
        puts("Woah! how did you do that");
        win();
    } else {
        printf("Key should be 0x3030303030303030\n");
        printf("But currently it is 0x%016lx\n", key);
        puts("You need to put the right value in the key variable");
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

void dump_stack() {
    int64_t *pointer;
    pointer = (int64_t*)&pointer + 6;

    puts("");
    puts(RED "╭─────────────────────┬────────────┬────────────────────╮");
    puts("│       " RESET "address" RED "       │  " RESET "variable" RED "  │       " RESET "value" RED "        │");
    for (int i = 0; i < 4; i++) {
        char *var_name;
        switch (i) {
            case 0:
                var_name = "buffer";
                break;
            case 1:
                var_name = "pad";
                break;
            case 2:
                var_name = "key";
                break;
            default:
                var_name = "...";
                break;
        }
        puts(RED "├─────────────────────┼────────────┼────────────────────┤");
        printf("│ " YELLOW "0x%016lx" RED "  │ " CYAN "%-10s" RED " │ " GREEN "0x%016lx" RED " │\n", pointer, var_name, *pointer);
        pointer++;
    }
    puts(RED "╰─────────────────────┴────────────┴────────────────────╯" RESET);
    puts("");
}

void banner() {
    puts("───────────────────────────────");
    puts("Hint");
    puts("The value of '0' in hex is 0x30");
    puts("───────────────────────────────");
    puts("The floor is once again yours, express yourself");
    printf("> ");
}
