#include <stdio.h>
#include <locale.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include "forca.h"

//Vari�veis globais
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
    scanf(" %c", &chute); //o espa�o antes da m�scar ignora o buffer da tecla Enter

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

//inclui uma palavra ao arquivo
void adicionapalavra() {
    char quer;
    printf("\n\nVoc� deseja adicionar uma palavra no jogo? (s/n)");
    scanf(" %c", &quer);

    if(quer == 's') {
        char novapalavra[20];
        printf("\n\nQual a nova palavra? ");
        scanf("%s", novapalavra);

        FILE *f;
        f = fopen("palavras.txt", "r+"); //abre o arquivo em modo de leitura e escrita a atribui ao ponteiro

        //testa se o arquivo foi encontrado
        if(f == 0) {
            printf("Banco de dados n�o dispon�vel\n\n");
            exit(1); //encerra o programa
        }

        //atualiza quantidade de palavras
        int qtd;
        fscanf(f, "%d", &qtd);
        qtd++;
        fseek(f, 0, SEEK_SET); //move a posi��o de leitura, no caso 0 bytes a partir do in�cio do arquivo (SEEK_SET)
        fprintf(f, "%d", qtd);

        //inclui a palavra no final do arquivo
        fseek(f, 0, SEEK_END); //move a posi��o de leitura, 0 bytes a partir do final do arquivo (SEEK_END)
        fprintf(f, "\n%s", novapalavra);
        fclose(f);
    }
}

//seleciona a palavra atrav�s de um arquivo
void escolheapalavra(){
    FILE *f; // cria ponteiro para o arquivo

    f = fopen("palavras.txt", "r"); //abre o arquivo somente pra leitura e atribu� ao ponteiro

    //testa se o arquivo foi encontrado
    if(f == 0) {
        printf("Banco de dados n�o dispon�vel\n\n");
        exit(1); //encerra o programa
    }

    int qtdpalavras;
    fscanf(f, "%d", &qtdpalavras); //l� a primeira linha contendo o n�mero de palavras e armazena na vari�vel
    srand(time(0)); //cria uma semente de n�mero rand�mico baseado no hor�rio 0:00 de 01/01/1970
    int randomico = rand() % qtdpalavras; //divide o n�mero rand�mico pela quantidade de palavras e atribu� o resto � vari�vel

    //varre a lista de palavras at� a linha indicada pela vari�vel 'randomico'
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

    adicionapalavra();

    return 0;
}
