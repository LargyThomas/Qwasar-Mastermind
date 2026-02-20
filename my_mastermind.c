#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>  // read()

// Generate a 4-digit code if the user doesn't provide one.
// Each digit is unique and between 0 and 8.
void generate_code(char *code) {
    int used[9] = {0};
    int i = 0;
    while (i < 4) {
        int digit = rand() % 9;
        if (!used[digit]) {
            used[digit] = 1;
            code[i] = '0' + digit;
            i++;
        }
    }
    code[4] = '\0';
}

// Recreation of the existing function str_len.
// Returns the length of a string without counting the null terminator.
int strlen_bis(char* str) {
    int len = 0;
    while (str[len] != '\0')
        len++;
    return len;
}

// Validates the format of the code: must be 4 unique digits between 0 and 8.
int validation_format(char *code) {
    if (!code || strlen_bis(code) != 4)
        return 0;
    int seen[9] = {0};
    for (int i = 0; i < 4; i++) {
        if (code[i] < '0' || code[i] > '8')
            return 0;
        int digit = code[i] - '0';
        if (seen[digit])
            return 0;
        seen[digit] = 1;
    }
    return 1;
}

// Compares the secret code with the user's guess.
// Counts well-placed and misplaced digits.
void compare_codes(char *secret, char *guess, int *well_placed, int *misplaced) {
    int i;
    int count_secret[9] = {0};
    int count_guess[9] = {0};
    *well_placed = 0;
    *misplaced = 0;
    for (i = 0; i < 4; i++) {
        if (secret[i] == guess[i])
            (*well_placed)++;
        else {
            count_secret[secret[i] - '0']++;
            count_guess[guess[i] - '0']++;
        }
    }
    for (i = 0; i < 9; i++) {
        if (count_secret[i] > 0 && count_guess[i] > 0) {
            if (count_secret[i] < count_guess[i])
                *misplaced += count_secret[i];
            else
                *misplaced += count_guess[i];
        }
    }
}

// Reads a line from stdin character by character.
// Returns 1 if EOF is reached with no input, 0 otherwise.
int read_code(char* buffer, int maxlen) {
    size_t bytes_read;
    char c;
    int len = 0;
    while ((bytes_read = read(0, &c, 1)) > 0) {
        if (c == '\n') break;
        if (len < maxlen - 1)
            buffer[len++] = c;
    }
    if (bytes_read == 0 && len == 0)
        return 1;
    buffer[len] = '\0';
    return 0;
}

// Parses command-line arguments to set the secret code and number of attempts.
// -c <code>     : sets a custom secret code (must be valid)
// -t <attempts> : sets the number of allowed attempts (default: 10)
void handle_arguments(int argc, char* argv[], char* secret, int* attempts) {
    *attempts = 10;
    int has_secret = 0;
    for (int i = 1; i < argc; i++) {
        if (argv[i][0] == '-' && argv[i][1] == 'c' && i + 1 < argc) {
            if (validation_format(argv[i + 1])) {
                for (int j = 0; j < 5; j++)
                    secret[j] = argv[i + 1][j];
                has_secret = 1;
            }
        }
        if (argv[i][0] == '-' && argv[i][1] == 't' && i + 1 < argc)
            *attempts = atoi(argv[i + 1]);
    }
    if (!has_secret)
        generate_code(secret);
}

int main(int argc, char** argv) {
    srand(time(NULL));
    int attempts;
    char secret[5];

    handle_arguments(argc, argv, secret, &attempts);

    printf("Will you find the secret code?\n");
    printf("Please enter a valid guess\n");

    for (int round = 0; round < attempts; round++) {
        printf("---\nRound %d\n>", round);
        char guess[5];
        if (read_code(guess, 5) == 1)
            return 0;
        if (!validation_format(guess)) {
            printf("Wrong input!\n");
            round--;
