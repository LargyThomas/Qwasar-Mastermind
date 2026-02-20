#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>  // read()

void generation_code(char *code) {
    int utiliser[9] = {0};
    int i = 0;
    while (i < 4) {
        int chiffre = rand() % 9;
        if (!utiliser[chiffre]) {
            utiliser[chiffre] = 1;
            code[i] = '0' + chiffre;
            i++;
        }
    }
    code[4] = '\0';
}

int strlen_bis(char* chaine) {
    int len = 0;
    while (chaine[len] != '\0')
        len++;
    return len;
}

int validation_format(char *code) {
    if (!code || strlen_bis(code) != 4)
        return 0;
    int vu[9] = {0};
    for (int i = 0; i < 4; i++) {
        if (code[i] < '0' || code[i] > '8')
            return 0;
        int chiffre = code[i] - '0';
        if (vu[chiffre])
            return 0;
        vu[chiffre] = 1;
    }
    return 1;
}

void compare_codes(char *code_secret, char *code_user, int *bien_places, int *mall_places) {
    int i;
    int compteur_secret[9] = {0};
    int compteur_user[9] = {0};

    *bien_places = 0;
    *mall_places = 0;


    for (i = 0; i < 4; i++) {
        if (code_secret[i] == code_user[i])
            (*bien_places)++;
        else {
            
            compteur_secret[code_secret[i] - '0']++;
            compteur_user[code_user[i] - '0']++;
        }
    }

    for (i = 0; i < 9; i++) {
        if (compteur_secret[i] > 0 && compteur_user[i] > 0) {
            if (compteur_secret[i] < compteur_user[i]) {
                *mall_places += compteur_secret[i];
            }
            else {
                *mall_places += compteur_user[i];
            }
        }
    }
}

int lecture_code(char* buffer, int maxlen) {
    size_t lecture;
    char c;
    int len = 0;
    while((lecture = read(0, &c, 1)) > 0) {
        if (c == '\n') break;
        if (len < maxlen - 1) {
            buffer[len++] = c;
        }
    }
    if (lecture == 0 && len == 0)
        return 1;
    buffer[len] = '\0';
    return 0;
}

void gestion_arguments(int argc, char* argv[], char* code_secret, int* attempts) {
    *attempts = 10;
    int has_secret = 0;

    for (int i = 1; i < argc; i++) {
        if (argv[i][0] == '-' && argv[i][1] == 'c' && i + 1 < argc) {
            if (validation_format(argv[i+1])) {
                for (int j = 0; j < 5; j++)
                    code_secret[j] = argv[i+1][j];
                has_secret = 1;
            }
        }
        if (argv[i][0] == '-' && argv[i][1] == 't' && i + 1 < argc)
            *attempts = atoi(argv[i+1]);
    }

    if (!has_secret)
        generation_code(code_secret);
}

int main(int argc, char** argv) {
    srand(time(NULL));
    int attempts;
    char code_secret[5];

    gestion_arguments(argc, argv, code_secret, &attempts);

    printf("Will you find the secret code?\n");
    printf("Please enter a valid guess\n");

    for (int round = 0; round < attempts; round++) {
        printf("---\nRound %d\n>", round);

        char code_user[5];
        if (lecture_code(code_user, 5) == 1)
            return 0;

        if (!validation_format(code_user)) {
            printf("Wrong input!\n");
            round--;
            continue;
        }

        int bien, mal;
        compare_codes(code_secret, code_user, &bien, &mal);

        if (bien == 4) {
            printf("Congratz! You did it!\n");
            return 0;
        }

        printf("Well placed pieces: %d\n", bien);
        printf("Misplaced pieces: %d\n", mal);
    }
    return 0;
}
