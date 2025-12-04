#include <stdio.h>

struct MataKuliah {
    char namaMK[50];
    float nilai;
};

struct Mahasiswa {
    char nama[50];
    char NIM[20];
    int jumlahMK;
    struct MataKuliah mk[20];
};

int main() {
    struct Mahasiswa mhs;
    int i;
    float total = 0, rata;

    printf("=== Input Data Mahasiswa ===\n");

    printf("Masukkan Nama Mahasiswa : ");
    fgets(mhs.nama, sizeof(mhs.nama), stdin);

    printf("Masukkan NIM : ");
    fgets(mhs.NIM, sizeof(mhs.NIM), stdin);

    printf("Masukkan jumlah mata kuliah : ");
    scanf("%d", &mhs.jumlahMK);
    getchar();

    printf("\n=== Input Mata Kuliah & Nilai ===\n");

    for(i = 0; i < mhs.jumlahMK; i++){
        printf("\nMata Kuliah ke-%d\n", i+1);

        printf("Nama Mata Kuliah : ");
        fgets(mhs.mk[i].namaMK, sizeof(mhs.mk[i].namaMK), stdin);

        printf("Nilai : ");
        scanf("%f", &mhs.mk[i].nilai);
        getchar();

        total += mhs.mk[i].nilai;
    }

    rata = total / mhs.jumlahMK;

    printf("\n=== DATA MAHASISWA ===\n");
    printf("Nama\t: %s", mhs.nama);
    printf("NIM\t: %s", mhs.NIM);

    printf("\nDaftar Nilai:\n");
    for(i = 0; i < mhs.jumlahMK; i++){
        printf(" %d. %sNilai: %.2f\n", i+1, mhs.mk[i].namaMK, mhs.mk[i].nilai);
    }

    printf("\nRata-rata Nilai: %.2f\n", rata);

    return 0;
}