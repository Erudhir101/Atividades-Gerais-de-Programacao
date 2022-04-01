#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_VAL 100000

double calcularTempo(clock_t ini, clock_t fim)
{
    return (double)(fim - ini) * 1000.0 / CLOCKS_PER_SEC;
}

void recolocarDados(int vetPrincipal[], int vetAux[])
{
    int i;
    for (i = 0; i < MAX_VAL; i++)
        vetAux[i] = vetPrincipal[i];
}

void mostrarDados(int vet[])
{
    int i;
    printf("\n");
    for (i = 0; i < MAX_VAL; i++)
        printf("%d ", vet[i]);
    printf("\n");
}

void bubbleSort(int a[], int tam)
{
    int i = 0, j, aux, trocou = 1, count = 0;
    while (trocou)
    {
        count += 2;
        trocou = 0;
        for (j = 1; j < tam - i; j++)
        {
            count++;
            if (a[j - 1] > a[j])
            {
                count += 4;
                aux = a[j - 1];
                a[j - 1] = a[j];
                a[j] = aux;
                trocou = 1;
            }
        }
        i++;
    }
    printf("%d - valor de vezes do BubbleSort", count);
}

void selectionSort(int vet[], int n)
{
    int i, j, min, aux, count = 0;
    for (i = 0; i < n - 1; i++)
    {
        min = i;
        for (j = i + 1; j < n; j++)
        {
            count++;
            if (vet[j] < vet[min])
            {
                count++;
                min = j;
            }
        }
        count += 4;
        aux = vet[i];
        vet[i] = vet[min];
        vet[min] = aux;
    }
    printf("\n%d - valor de vezes do selectionSort", count);
}

int merge(int p, int q, int r, int v[])
{
    int *w, count = 3;
    w = malloc((r - p) * sizeof(int));
    int i = p, j = q;
    int k = 0;
    while (i < q && j < r)
    {
        count += 2;
        if (v[i] <= v[j])
            w[k++] = v[i++];
        else
            w[k++] = v[j++];
    }
    while (i < q)
    {
        count++;
        w[k++] = v[i++];
    }
    while (j < r)
    {
        count++;
        w[k++] = v[j++];
    }
    for (i = p; i < r; ++i)
    {
        count++;
        v[i] = w[i - p];
    }
    free(w);
    return count;
}

int mergeSort(int vet[], int ini, int fim)
{
    int meio, count = 4;
    if (ini < fim - 1)
    {
        meio = (ini + fim) / 2;
        count += mergeSort(vet, ini, meio);
        count += mergeSort(vet, meio, fim);
        count += merge(ini, meio, fim, vet);
    }
    return count;
}

int quickSort(int A[], int ini, int fim)
{
    int i = ini, f = fim, pivo = A[(ini + fim) / 2], aux, count = 0;
    do
    { // separação das listas
        while (A[i] < pivo)
        {
            count++;
            i++;
        }
        while (A[f] > pivo)
        {
            count++;
            f--;
        }
        count++;
        if (i <= f)
        {
            count += 3;
            aux = A[i];
            A[i++] = A[f];
            A[f--] = aux;
        }
    } while (i <= f);
    count += 2;
    if (ini < f)
        count += quickSort(A, ini, f);
    if (i < fim)
        count += quickSort(A, i, fim);
    return count;
}

void insertionSort(int A[], int tam)
{
    int i, j, aux, count = 0;
    for (j = 1; j < tam; j++)
    {
        count += 3;
        aux = A[j];
        i = j - 1;
        while ((i >= 0) && (A[i] > aux))
        {
            count++;
            A[i + 1] = A[i--];
        }
        A[i + 1] = aux;
    }
    printf("\n%d - valor de vezes do insertionSort", count);
}

void shellSort(int A[], int tam)
{
    int i, j, aux, gap = 1, count = 0;
    while (gap < tam)
    {
        count++;
        gap = (gap * 3) + 1;
    }
    while (gap > 1)
    {
        count++;
        gap /= 3;
        for (i = gap; i < tam; i++)
        {
            count += 3;
            aux = A[i];
            j = i - gap;
            while ((j >= 0) && (aux < A[j]))
            {
                count += 2;
                A[j + gap] = A[j];
                j -= gap;
            }
            A[j + gap] = aux;
        }
    }
    printf("\n%d - valor de vezes do shellSort", count);
}

void heapSort(int A[], int tam)
{
    int i = tam / 2, pai, filho, t, count = 0;

    while (1)
    {
        count += 4;
        if (i > 0)
        {
            count += 2;
            i--;
            t = A[i];
        }
        else
        {
            count += 2;
            tam--;
            if (tam == 0)
            {
                printf("\n%d - valor de vezes do heapSort", count);
                return;
            }
            count += 2;
            t = A[tam];
            A[tam] = A[0];
        }
        pai = i;
        filho = (i * 2) + 1;
        while (filho < tam)
        {
            count += 2;
            if ((filho + 1 < tam) && (A[filho + 1] > A[filho]))
            {
                count++;
                filho++;
            }
            if (A[filho] > t)
            {
                count += 3;
                A[pai] = A[filho];
                pai = filho;
                filho = (pai * 2) + 1;
            }
            else
                break;
        }
        A[pai] = t;
    }
}

int main()
{
    int i, vet[MAX_VAL], vetAux[MAX_VAL], count = 0;
    clock_t start, stop;
    srand(time(NULL));

    for (i = 0; i < MAX_VAL; i++)
    {
        vetAux[i] = vet[i] = rand() % MAX_VAL;
    }
    //mostrarDados(vet);
    printf("\n\n");

    start = clock();
    bubbleSort(vetAux, MAX_VAL);
    stop = clock();
    // mostrarDados(vetAux);
    printf("\n\nTempo percorrido pelo bubbleSort: %.2lf ms\n", calcularTempo(start, stop));
    recolocarDados(vet, vetAux);

    start = clock();
    selectionSort(vet, MAX_VAL);
    stop = clock();
    // mostrarDados(vetAux);
    printf("\n\nTempo percorrido pelo selectionSort: %.2lf ms\n", calcularTempo(start, stop));
    recolocarDados(vet, vetAux);

    start = clock();
    count = mergeSort(vetAux, 0, MAX_VAL);
    stop = clock();
    // mostrarDados(vetAux);
    printf("\n%d - valor de vezes do mergeSort", count);
    printf("\n\nTempo percorrido pelo mergeSort: %.2lf ms\n", calcularTempo(start, stop));
    recolocarDados(vet, vetAux);

    start = clock();
    count = quickSort(vetAux, 0, MAX_VAL);
    stop = clock();
    // mostrarDados(vetAux);
    printf("\n%d - valor de vezes do quickSort", count);
    printf("\n\nTempo percorrido pelo quickSort: %.2lf ms\n", calcularTempo(start, stop));
    recolocarDados(vet, vetAux);

    start = clock();
    insertionSort(vetAux, MAX_VAL);
    stop = clock();
    // mostrarDados(vetAux);
    printf("\n\nTempo percorrido pelo insertionSort: %.2lf ms\n", calcularTempo(start, stop));
    recolocarDados(vet, vetAux);

    start = clock();
    shellSort(vetAux, MAX_VAL);
    stop = clock();
    // mostrarDados(vetAux);
    printf("\n\nTempo percorrido pelo shellSort: %.2lf ms\n", calcularTempo(start, stop));
    recolocarDados(vet, vetAux);

    start = clock();
    heapSort(vetAux, MAX_VAL);
    stop = clock();
    // mostrarDados(vetAux);
    printf("\n\nTempo percorrido pelo HeapSort: %.2lf ms\n", calcularTempo(start, stop));
    recolocarDados(vet, vetAux);

    //mostrarDados(vetAux);
    return 0;
}