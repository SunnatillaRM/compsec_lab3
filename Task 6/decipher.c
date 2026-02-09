#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_TEXT_SIZE 10000

int main() {
    FILE *in = fopen("columns.txt", "r");
    if (!in) { 
        perror("Error opening columns.txt"); 
        return 1; 
    }

    int unused_gcd;
    char ciphertext[MAX_TEXT_SIZE];
    char keyword[100];

    fscanf(in, "%d", &unused_gcd);
    fscanf(in, "%s", ciphertext);
    fclose(in);

    printf("Enter the keyword: ");
    scanf("%99s", keyword);
    
    int key_len = strlen(keyword);
    for(int i = 0; i < key_len; i++) {
        keyword[i] = tolower(keyword[i]);
    }

    int text_len = strlen(ciphertext);
    char plaintext[MAX_TEXT_SIZE];

    for (int i = 0; i < text_len; i++) {
        int c_val = ciphertext[i] - 'a';
        int k_val = keyword[i % key_len] - 'a';

        int p_val = (c_val - k_val + 26) % 26;

        plaintext[i] = p_val + 'a';
    }
    plaintext[text_len] = '\0';

    FILE *out = fopen("plain.txt", "w");
    if (out == NULL) {
        perror("Error creating plain.txt");
        return 1;
    }
    fprintf(out, "%s\n", plaintext);
    fclose(out);

    printf("\nplain.txt updated\n");

    return 0;
}