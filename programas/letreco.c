// game de adivinhar palavras "letreco"
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#define LIMPAR_TELA system("cls")
#define LIMPAR_BUFFER fflush(stdin);
#define QTD_ROUD 6

typedef struct
{
    char *string;
    int *estado;
    int tamString;
} teclado;

enum COLOR
{
    BLACK = 0,
    BLUE = 1,
    GREEN = 2,
    CYAN = 3,
    RED = 4,
    MAGENTA = 5,
    BROWN = 6,
    LIGHTGRAY = 7,
    DARKGRAY = 8,
    LIGHTBLUE = 9,
    LIGHTGREEN = 10,
    LIGHTCYAN = 11,
    LIGHTRED = 12,
    LIGHTMAGENTA = 13,
    YELLOW = 14,
    WHITE = 15
};

void textcolor(int color)
{
    static int __BACKGROUND;
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbiInfo;
    GetConsoleScreenBufferInfo(h, &csbiInfo);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
                            color + (__BACKGROUND << 4));
}

int tamString(char string[])
{
    int tam = 0;
    for (char *i = string; (*i) != '\0'; i++)
        tam++;
    return tam;
}

int indexChar(char caracter, teclado tec)
{
    int i = -1;
    for (i = 0; i < tec.tamString; i++)
    {
        if (caracter == tec.string[i])
            break;
    }
    return i;
}

void compararStrings(char frase[], teclado palavra, teclado tec)
{
    int i, j, count;
    if (tamString(frase) == palavra.tamString)
    {
        for (i = 0; i < palavra.tamString; i++)
        {
            count = 0;
            for (j = 0; j < palavra.tamString; j++)
            {
                if (toupper(frase[i]) == palavra.string[j])
                {
                    count = 1;
                    if (i == j)
                    {
                        palavra.estado[j] = tec.estado[indexChar(palavra.string[j], tec)] = 1;
                    }
                    else
                        palavra.estado[j] = tec.estado[indexChar(palavra.string[j], tec)] = 2;
                }
            }
            if (count == 0)
                tec.estado[indexChar(toupper(frase[i]), tec)] = 3;
        }
    }
}

void trocarCor(char caract, int caso)
{
    switch (caso)
    {
    case 1:
        textcolor(GREEN);
        break;
    case 2:
        textcolor(YELLOW);
        break;
    case 3:
        textcolor(RED);
        break;
    case 0:
    default:
        textcolor(WHITE);
        break;
    }
    printf("%c ", caract);
}

teclado iniciarString(char string[], int tamString)
{
    teclado palavra;
    palavra.string = malloc(sizeof(char) * tamString);
    palavra.estado = malloc(sizeof(int) * tamString);
    for (int i = 0; i < tamString; i++)
    {
        palavra.string[i] = toupper(string[i]);
        palavra.estado[i] = 0;
    }
    palavra.tamString = tamString;
    return palavra;
}

void telaPalavra(teclado palavra)
{
    int i;
    printf("▼ PALAVRA PARA ADIVINHAR ▼\n");
    printf(" ");
    for (i = 0; i < (palavra.tamString * 4) - 1; i++)
        printf("-");
    printf("\n");
    textcolor(WHITE);
    for (i = 0; i < palavra.tamString; i++)
    {
        printf("| ");
        if (palavra.estado[i] == 1)
            trocarCor(palavra.string[i], palavra.estado[i]);
        else
        {
            printf("%c ", '0');
        }
        textcolor(WHITE);
    }
    printf("|\n ");
    for (i = 0; i < (palavra.tamString * 4) - 1; i++)
        printf("-");
}

void telaTeclado(teclado tec)
{
    int i;
    printf("\n");
    printf("| ");
    trocarCor(tec.string[0], tec.estado[0]);
    textcolor(WHITE);
    for (i = 1; i < tec.tamString - 1; i++)
    {
        printf("- ");
        trocarCor(tec.string[i], tec.estado[i]);
        textcolor(WHITE);
    }
    printf("|\n");
}

int verifGanhou(teclado palavra)
{
    int i, count = 0;
    for (i = 0; i < palavra.tamString; i++)
        if (palavra.estado[i] == 1)
            count++;
    if (count == palavra.tamString)
        return 1;
    return 0;
}

void game()
{
    int i, j;
    char stringJogo[] = "nome", stringTec[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ", chute[QTD_ROUD][50];
    teclado palavra, tec;
    tec = iniciarString(stringTec, tamString(stringTec));
    palavra = iniciarString(stringJogo, tamString(stringJogo));
    LIMPAR_TELA;
    LIMPAR_BUFFER;
    for (i = 0; i < QTD_ROUD; i++)
    {
        LIMPAR_TELA;
        printf(" ---------\n| ROUND %i |\n ---------\n", (i + 1));
        telaPalavra(palavra);
        printf("\n");
        telaTeclado(tec);
        printf("\n");
        do
        {
            printf("--CHUTES---\n");
            for (j = 0; j < i; j++)
                printf("chute %d: %s\n", (j + 1), chute[j]);
            printf("\n");
            printf("DIGITE A POSSIVEL FRASE (TAM = %i): ", palavra.tamString);
            scanf("%s", chute[i]);

            if (tamString(chute[i]) != palavra.tamString)
                printf("A frase não tem o tamanho da palavra\tTente novamente...\n");
        } while (tamString(chute[i]) != palavra.tamString);

        compararStrings(chute[i], palavra, tec);

        if (verifGanhou(palavra))
        {
            printf("\n\n -----------------------\n");
            textcolor(GREEN);
            printf("  VOCE GANHOU O JOGO!!!\n");
            textcolor(WHITE);
            printf("  A PALAVRA ERA \"%s\"\n  CHUTES NECESSARIOS: %d\n", palavra.string, (i + 1));
            break;
        }
        else
        {
            printf("\n\n -----------------------\n");
            textcolor(RED);
            printf("  VOCE PERDEU O JOGO!!!\n");
            textcolor(WHITE);
            printf("  A PALAVRA ERA \"%s\"\n", palavra.string);
        }
    }
}

int main()
{
    game();
    return 0;
}
