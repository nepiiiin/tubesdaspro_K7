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
//  untuk menentukan grade berdasarkan rata-rata nilai
const char * grade (float rata){
     if (rata >= 80)
        return "A";
    else if (rata >= 75)
        return "B+";
    else if (rata >= 70)
        return "B";
    else if (rata >= 65)
        return "C+";
    else if (rata >= 60)
        return "C";
    else if (rata >= 50)
        return "D";
    else
        return "E";
}
// untuk menentukan ipk berdasarkan rata-rata nilai
float getBobotGrade(float rata) {
    if (rata >= 80)
        return 4.00;
    else if (rata >= 75)
        return 3.50;
    else if (rata >= 70)
        return 3.00;
    else if (rata >= 65)
        return 2.50;
    else if (rata >= 60)
        return 2.00;
    else if (rata >= 50)
        return 1.00;
    else
        return 0.00;
}
// input dan output data mahasiswa
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
    printf("Grade: %s\n", grade(rata));
    printf("IPK: %.2f\n", getBobotGrade(rata));

    return 0;
}