#include <stdio.h>
int main()
{
    int angka;
    printf("Masukkan sebuah angka: ");
    scanf("%d", &angka);

    if (angka % 2 == 0)
    {
        printf("Angka %d adalah genap.\n", angka);
    }
    else
    {
        printf("Angka %d adalah ganjil.\n", angka);
    }   
    return 0;
}