#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int *make_mas(int);
void printarr(int*, int);
void delete(int*, int, int);
int *add(int*, int, int, int);

int main()
{
    srand(time(NULL));
    
    int n;
    printf("Enter a size of array: ");
    scanf("%d", &n);
    
    int *arr = make_mas(n);
    
    printf("Your array:\n");
    printarr(arr, n);
    
    int m;
    printf("Enter a number to delete: ");
    scanf("%d", &m);
    
    delete(arr, n, m);
    n--;
    
    printf("Array without specified element:\n");
    printarr(arr, n);
    
    int k;
    printf("How many element do you want to add after deleted?: ");
    scanf("%d", &k);
    
    int *newarr = add(arr, m, n, k);
    n += k;
    printf("Your new array:\n");
    printarr(newarr, n);
    
    free(newarr);
    
    return 0;
}

int *make_mas(int n)
{
    int *mas;
    mas = (int*)malloc(n * sizeof(int));
    for(int i = 0; i < n; i++)
        mas[i] = rand() % 10;
    return mas;
}
void printarr(int* mas, int n)
{
    for (int i = 0; i < n; i++)
        printf("%d ", mas[i]);
    printf("\n");
}
void delete(int* mas, int n, int k)
{
    for (int i = 0, j = 0; i < n; i++)
        if (i != k)
            mas[j++] = mas[i];
    mas = (int*)realloc(mas, sizeof(int) * (n - 1));
}
int *add(int* mas, int num, int n, int k)
{
    if (k == 0)
        return mas;
    
    int temp[n];
    
    for (int i = 0; i < n; i++)
        temp[i] = mas[i];
    
    int *newmas = (int*)realloc(mas, sizeof(int) * (n + k));
    
    int i = 0;
    int size = n + k;
    
    for ( ; i < num; i++)
        newmas[i] = temp[i];
    
    int j = i;
    for ( ; j < num + k; j++)
    {
        newmas[j] = rand() % 10;
    }
    
    for ( ; j < size; j++)
        newmas[j] = temp[i++];
    
    return newmas;
}
