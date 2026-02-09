#include <stdio.h>
#include <string.h>

#define MAX_TEXT_SIZE 10000

int main() {
    FILE *in = fopen("columns.txt", "r");
    if (!in) { perror("Error opening columns.txt"); return 1; }

    int gcd;
    char text[MAX_TEXT_SIZE];

    fscanf(in, "%d", &gcd);
    fscanf(in, "%s", text);
    fclose(in);

    int len = strlen(text);
    int freq[gcd][26];

    for (int i = 0; i < gcd; i++) 
        for (int j = 0; j < 26; j++) freq[i][j] = 0;

    for (int i = 0; i < len; i++) {
        freq[i % gcd][text[i] - 'a']++;
    }

    printf("Frequency Analysis (Key Length: %d)\n", gcd);
    for (int c = 0; c < gcd; c++) {
        printf("\nColumn %d most common letters:\n", c + 1);
        for (int top = 0; top < 3; top++) {
            int max = -1, max_letter = -1;
            for (int l = 0; l < 26; l++) {
                if (freq[c][l] > max) {
                    max = freq[c][l];
                    max_letter = l;
                }
            }
            if (max > 0) {
                printf("  %c : %d\n", max_letter + 'a', max);
                freq[c][max_letter] = -1;
            }
        }
    }

    return 0;
}