#include <stdio.h>
#include <locale.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include "forca.h"

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

//seleciona a palavra através de um arquivo
void escolheapalavra(){
    FILE *f; // cria ponteiro para o arquivo

    f = fopen("palavras.txt", "r"); //abre o arquivo somente pra leitura e atribuí ao ponteiro

    //testa se o arquivo foi encontrado
    if(f == 0) {
        printf("Banco de dados não disponível\n\n");
        exit(1); //encerra o programa
    }

    int qtdpalavras;
    fscanf(f, "%d", &qtdpalavras); //lê a primeira linha contendo o número de palavras e armazena na variável
    srand(time(0)); //cria uma semente de número randômico baseado no horário 0:00 de 01/01/1970
    int randomico = rand() % qtdpalavras; //divide o número randômico pela quantidade de palavras e atribuí o resto à variável

    //varre a lista de palavras até a linha indicada pela variável 'randomico'
    for(int i = 0; i <= randomico; i++) {
        fscanf(f, "%s", palavrasecreta);
    }

    fclose(f); //fecha o arquivo
}

int acertou() {
    for(int i = 0; i < strlen(palavrasecreta); i++) {
        if(!jachutou(palavrasecreta[i])) {
            return 0;
        }
    }
    return 1;
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

    abertura();

    do {
        desenhaforca();

        chuta();

    } while(!acertou() && !enforcou());

    return 0;
}
