#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define BUF 512
#define SEP '|'

void simple_trim(char *s) {
    int i, len = strlen(s);
   
    if (len > 0 && s[len-1] == '\n') s[--len] = '\0';
 
    while (len > 0 && s[len-1] == ' ') s[--len] = '\0';
    
    i = 0;
    while (s[i] == ' ') i++;
    if (i) memmove(s, s + i, strlen(s + i) + 1);
}


int equal_ci(const char *a, const char *b) {
    while (*a && *b) {
        if (tolower((unsigned char)*a) != tolower((unsigned char)*b)) return 0;
        a++; b++;
    }
    return *a == 0 && *b == 0;
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s questions.txt\n", argv[0]);
        return 1;
    }

    FILE *f = fopen(argv[1], "r");
    if (!f) {
        perror("Cannot open file");
        return 1;
    }

    char line[BUF], user[BUF];
    int total = 0, score = 0;

    while (fgets(line, sizeof(line), f)) {
        simple_trim(line);
        if (line[0] == '\0') continue; 

        char *sep = strchr(line, SEP);
        if (!sep) continue; 

        *sep = '\0';
        char *question = line;
        char *answer = sep + 1;
        simple_trim(question);
        simple_trim(answer);

        printf("\nQ%d: %s\nYour answer: ", total + 1, question);
        if (!fgets(user, sizeof(user), stdin)) break;
        simple_trim(user);

        if (equal_ci(user, answer)) {
            printf("Correct!\n");
            score++;
        } else {
            printf("Wrong. Correct: %s\n", answer);
        }
        total++;
    }

    fclose(f);
    printf("\nFinal Score: %d / %d\n", score, total);
    return 0;
}
