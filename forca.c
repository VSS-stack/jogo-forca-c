#include <stdio.h>
#include <locale.h>
#include <string.h>

//Variáveis globais
char palavrasecreta[20];
char chutes[26];
int chutesdados = 0;

void abertura() {
    printf("***********************************\n");
    printf("*          Jogo da forca          *\n");
    printf("***********************************\n\n");
}

void chuta() {
    char chute;
    scanf(" %c", &chute);

    chutes[chutesdados] = chute;

    (chutesdados)++;
}

int jachutou(char letra) {
    int achou = 0;

    for(int j = 0; j < chutesdados; j++) {
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

int enforcou() {
    int erros = 0;
    
    for(int i = 0; i < chutesdados; i++) {
        int existe = 0;

        for(int j = 0; j < strlen(palavrasecreta); j++) {
            if(chutes[i] == palavrasecreta[j]) {
                existe = 1;
                break;
            }
        }

        if(!existe) {
            erros++;
        }
    }

    return (erros >= 5);
}

int main() {
    setlocale(LC_ALL, "portuguese");

    escolheapalavra();

    int acertou = 0;

    abertura();

    do {
        desenhaforca();

        chuta();

    } while(!acertou && !enforcou());

    return 0;
}
