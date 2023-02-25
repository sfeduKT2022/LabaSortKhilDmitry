#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <Windows.h>
#include <time.h>
const int N = 22222;
int mas[N];
int mas1[N];

void SortPuzir()
{
    int t;
    for (int i = 0; i < N; ++i)
    {
        for (int j = 0; j < N - 1; ++j)
        {
            if (mas[j] > mas[j + 1])
            {
                t = mas[j];
                mas[j] = mas[j + 1];
                mas[j + 1] = t;
            }
        }
    }
}
void SortShella()
{
    int t, j;
    for (int move = N / 2; move > 0; move /= 2)
        for (int i = move; i < N; i++)
        {
            t = mas[i];
            for (j = i; j >= move; j -= move)
            {
                if (t < mas[j - move])
                    mas[j] = mas[j - move];
                else
                    break;
            }
            mas[j] = t;
        }
}
void SortSlil(int i, int j, int mas[], int mas1[]) {
    if (j <= i) {
        return;
    }
    int middle = (i + j) / 2;
    SortSlil(i, middle, mas, mas1);
    SortSlil(middle + 1, j, mas, mas1);
    int left = i;
    int right = middle + 1;
    int k;
    for (k = i; k <= j; k++) {
        if (left == middle + 1) {
            mas1[k] = mas[right];
            right++;
        }
        else if (right == j + 1) {
            mas1[k] = mas[left];
            left++;
        }
        else if (mas[left] < mas[right]) {
            mas1[k] = mas[left];
            left++;
        }
        else {
            mas1[k] = mas[right];
            right++;
        }
    }
    for (k = i; k <= j; k++) {
        mas[k] = mas1[k];
    }
}
void Random(FILE* f)
{
    for (int i = 0; i < N; ++i)
    {
        fprintf_s(f, "%d ", 0 + rand() % N);
    }
}
int main()
{
    FILE* f = fopen("input.txt", "w");
    if (f == NULL)
    {
        printf_s("Файл не открылся!");
        return 0;
    }
    Random(f);
    fclose(f);
    FILE* f1 = fopen("input.txt", "r");
    if (f1 == NULL)
    {
        printf_s("Файл не открылся!");
        return 0;
    }
    for (int i = 0; i < N; i++)
    {
        fscanf_s(f1, "%d", &mas[i]);
    }
    clock_t start1 = clock();
    SortPuzir();
    clock_t end1 = clock();
    double seconds1 = (double)(end1 - start1) / CLOCKS_PER_SEC;
    clock_t start2 = clock();
    SortShella();
    clock_t end2 = clock();
    double seconds2 = (double)(end2 - start2) / CLOCKS_PER_SEC;
    clock_t start3 = clock();
    SortSlil(0, N - 1, mas, mas1);
    clock_t end3 = clock();
    double seconds3 = (double)(end3 - start3) / CLOCKS_PER_SEC;
    fclose(f1);
    FILE* f2 = fopen("output.txt", "w");
    for (int i = 0; i < N; i++)
    {
        fprintf(f2, "%d ", mas[i]);
    }
    fclose(f2);
    printf("Time - %f\n", seconds1);
    printf("Time - %f\n", seconds2);
    printf("Time - %f\n", seconds3);
}
