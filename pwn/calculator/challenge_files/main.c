// gcc main.c -o main
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

#define CYAN   "\033[36m"
#define YELLOW "\033[33m"
#define GREEN  "\033[32m"
#define RED    "\033[31m"
#define RESET  "\033[0m"

void setup();
void banner();
void win();

void alarm_handler() {
    puts("You took too long");
    exit(0);
}

void vuln() {
    int64_t sum = 0;
    for (int i = 0; i < 60; i++) {
        int temp = random() % 100;
        sum += temp;
        printf("%d\n", temp);
    }
    puts("--------------------------------");

    signal(SIGALRM, alarm_handler);
    alarm(2);

    int64_t input;
    printf("> ");
    scanf("%lld", &input);

    if (input == sum) {
        win();
    } else {
        puts("You can't do math");
    }

}

int main(void) {
    setup();
    banner();
    vuln();
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
    puts("YOU WIN");

    FILE *f = fopen("./flag", "rb");
    if (!f) { perror("fopen"); exit(-1); }

    char c;
    while((c = fgetc(f)) != EOF) {
        fputc(c, stdout);
    }
    fclose(f);
}

void banner() {
    puts("I need you to crunch some numbers.");
    puts("Fast—time is ticking.");
    puts("What’s the sum of these numbers?");
    puts("--------------------------------");
}
