#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_TEXT_SIZE 10000
#define SEQ_LEN 3

int main() {
    FILE *file = fopen("vigenere.txt", "r");
    if (!file) { perror("Error opening vigenere.txt"); return 1; }

    char raw_text[MAX_TEXT_SIZE], clean_text[MAX_TEXT_SIZE];
    int clean_idx = 0;

    while (fgets(raw_text, sizeof(raw_text), file)) {
        for (int i = 0; raw_text[i] != '\0'; i++) {
            if (isalpha(raw_text[i])) clean_text[clean_idx++] = tolower(raw_text[i]);
        }
    }
    clean_text[clean_idx] = '\0';
    fclose(file);

    printf("Kasiski Repetitions\n");
    for (int i = 0; i < clean_idx - SEQ_LEN; i++) {
        char search_gram[SEQ_LEN + 1];
        strncpy(search_gram, &clean_text[i], SEQ_LEN);
        search_gram[SEQ_LEN] = '\0';

        char *found = strstr(clean_text + i + 1, search_gram);
        if (found != NULL) {
            printf("'%s' First: %d Second: %ld (distance: %ld)\n", 
                    search_gram, i, (found - clean_text), (found - clean_text) - i);
        }
    }

    int gcd;
    printf("\nEnter estimated GCD: ");
    scanf("%d", &gcd);

    FILE *out = fopen("columns.txt", "w");
    fprintf(out, "%d\n", gcd);
    fprintf(out, "%s", clean_text);
    fclose(out);

    printf("\ncolumns.txt updated");
    return 0;
}