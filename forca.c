#include <stdio.h>
#include <locale.h>
#include <string.h>

//Variáveis globais
char palavrasecreta[20];
char chutes[26];
int tentativas = 0;

void abertura() {
    printf("***********************************\n");
    printf("*          Jogo da forca          *\n");
    printf("***********************************\n\n");
}

void chuta() {
    char chute;
    scanf(" %c", &chute);

    chutes[tentativas] = chute;

    (tentativas)++;
}

int jachutou(char letra) {
    int achou = 0;

    for(int j = 0; j < tentativas; j++) {
        if(chutes[j] == letra) {
            achou = 1;
            break;
        }
    }

    return achou;
}

void desenhaforca() {
    for(int i = 0; i < strlen(palavrasecreta); i++) {
            
            int achou = jachutou(palavrasecreta[i]);

            if(achou) {
                printf("%c ", palavrasecreta[i]);
            } else {
                printf("_ ");
            }
        }
    printf("\n");
}

void escolheapalavra(){
    sprintf(palavrasecreta, "MELANCIA");
}

int main() {
    setlocale(LC_ALL, "portuguese");

    escolheapalavra();

    int acertou = 0;
    int enforcou = 0;


    abertura();

    do {
        desenhaforca();

        chuta();

    } while(!acertou && !enforcou);

    return 0;
}
