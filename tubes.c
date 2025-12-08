#include <stdio.h>
#include <string.h>

// warna teks
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define BLUE    "\033[34m"
#define YELLOW  "\033[33m"
#define RESET   "\033[0m"

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

void hapusNewline(char *str) {
    int len = strlen(str);
    if (len > 0 && str[len - 1] == '\n')
        str[len - 1] = '\0';
}

int toInt(const char *str) {
    int result = 0, i = 0;
    while (str[i] >= '0' && str[i] <= '9') {
        result = result * 10 + (str[i] - '0');
        i++;
    }
    return result;
}

float toFloat(const char *str) {
    float result = 0;
    int i = 0, decimal = 0;
    float factor = 0.1;

    while (str[i]) {
        if (str[i] >= '0' && str[i] <= '9') {
            if (!decimal)
                result = result * 10 + (str[i] - '0');
            else {
                result += (str[i] - '0') * factor;
                factor /= 10;
            }
        } else if (str[i] == '.') {
            decimal = 1;
        } else break;
        i++;
    }
    return result;
}

const char *grade(float rata) {
    if (rata >= 80) return "A";
    else if (rata >= 75) return "B+";
    else if (rata >= 70) return "B";
    else if (rata >= 65) return "C+";
    else if (rata >= 60) return "C";
    else if (rata >= 50) return "D";
    else return "E";
}

float getBobotGrade(float rata) {
    if (rata >= 80) return 4.00;
    else if (rata >= 75) return 3.50;
    else if (rata >= 70) return 3.00;
    else if (rata >= 65) return 2.50;
    else if (rata >= 60) return 2.00;
    else if (rata >= 50) return 1.00;
    else return 0.00;
}

const char *statusKelulusan(float ipk) {
    if (ipk >= 2.00) return GREEN "Lulus" RESET;
    return RED "Tidak Lulus" RESET;
}

//  Tampilkan Semua Data

void tampilkanSemuaDataFile() {
    FILE *fr = fopen("data.txt", "r");
    if (!fr) {
        printf(RED "Tidak ada data yang tersimpan.\n" RESET);
        return;
    }

    printf("\n=== DATA MAHASISWA ===\n");
    char baris[100];
    int mhsKe = 0;

    while (fgets(baris, sizeof(baris), fr)) {
        hapusNewline(baris);
        if (strlen(baris) == 0 || strcmp(baris, "---") == 0) continue;

        char nama[50], NIM[20];
        int jumlahMK;

        strcpy(nama, baris);
        fgets(NIM, sizeof(NIM), fr); hapusNewline(NIM);
        fgets(baris, sizeof(baris), fr);
        jumlahMK = toInt(baris);

        printf("\n Mahasiswa ke-%d \n", ++mhsKe);
        printf("Nama       : %s\n", nama);
        printf("NIM        : %s\n", NIM);
        printf("Jumlah MK  : %d\n", jumlahMK);

        float total = 0;
        for (int i = 0; i < jumlahMK; i++) {
            char mk[50];
            float nilai;

            fgets(mk, sizeof(mk), fr); hapusNewline(mk);
            fgets(baris, sizeof(baris), fr);
            nilai = toFloat(baris);

            printf("  %d. %-20s : %.2f\n", i + 1, mk, nilai);
            total += nilai;
        }

        float rata = total / jumlahMK;
        printf(GREEN "Rata-rata  : %.2f\n" RESET, rata);
        printf(GREEN "Grade      : %s\n" RESET, grade(rata));
        printf(GREEN "IPK        : %.2f\n" RESET, getBobotGrade(rata));
        printf(GREEN "Status     : %s\n" RESET, statusKelulusan(getBobotGrade(rata)));
    }

    fclose(fr);

    if (mhsKe == 0) {
        printf(RED "Tidak ada data yang tersimpan.\n" RESET);
    }
}

int main() {
    struct Mahasiswa mhs;
    int choice;

    while (1) {
        printf("\n=== MENU UTAMA ===\n");
        printf(GREEN"1. Input Data Mahasiswa\n"RESET);
        printf(GREEN"2. Tampilkan Semua Data\n"RED);
        printf(RED"3. Keluar\n"RESET);
        printf("Pilih opsi: ");
        scanf("%d", &choice);
        getchar();

        if (choice == 1) {
            printf("\n=== INPUT DATA MAHASISWA ===\n");

            printf("Masukkan Nama : ");
            fgets(mhs.nama, sizeof(mhs.nama), stdin); hapusNewline(mhs.nama);

            printf("Masukkan NIM : ");
            fgets(mhs.NIM, sizeof(mhs.NIM), stdin); hapusNewline(mhs.NIM);

            printf("Jumlah MK (1-9): ");
            scanf("%d", &mhs.jumlahMK); getchar();

            if (mhs.jumlahMK < 1 || mhs.jumlahMK > 9) {
                printf(RED "Jumlah MK tidak valid!\n" RESET);
                continue;
            }

            float total = 0;

            for (int i = 0; i < mhs.jumlahMK; i++) {
                printf("\nMata Kuliah ke-%d\n", i + 1);
                printf("Nama MK : ");
                fgets(mhs.mk[i].namaMK, sizeof(mhs.mk[i].namaMK), stdin);
                hapusNewline(mhs.mk[i].namaMK);

                printf("Nilai (0-100): ");
                scanf("%f", &mhs.mk[i].nilai);
                getchar();

                if (mhs.mk[i].nilai < 0 || mhs.mk[i].nilai > 100) {
                    printf(RED "Nilai tidak valid! Ulangi.\n" RESET);
                    i--;
                    continue;
                }

                total += mhs.mk[i].nilai;
            }

            float rata = total / mhs.jumlahMK;
            float ipk = getBobotGrade(rata);

            printf("\n=== RINGKASAN DATA ===\n");
            printf("Nama  : %s\n", mhs.nama);
            printf("NIM   : %s\n", mhs.NIM);
            printf(GREEN "Rata-rata : %.2f\n" RESET, rata);
            printf(GREEN "Grade     : %s\n" RESET, grade(rata));
            printf(GREEN "IPK       : %.2f\n" RESET, ipk);
            printf(GREEN "Status    : %s\n" RESET, statusKelulusan(ipk));

            // Simpan file
            FILE *fp = fopen("data.txt", "a");
            if (!fp) {
                printf(RED "Gagal menulis file!\n" RESET);
                continue;
            }

            fprintf(fp, "%s\n%s\n%d\n", mhs.nama, mhs.NIM, mhs.jumlahMK);
            for (int j = 0; j < mhs.jumlahMK; j++) {
                fprintf(fp, "%s\n%.2f\n", mhs.mk[j].namaMK, mhs.mk[j].nilai);
            }
            fprintf(fp, "---\n");
            fclose(fp);

            printf(GREEN "Data berhasil disimpan.\n" RESET);

        } else if (choice == 2) {
            tampilkanSemuaDataFile();

        } else if (choice == 3) {
            printf(GREEN "Terima kasih!\n" RESET);
            break;

        } else {
            printf(RED "Pilihan tidak valid!\n" RESET);
        }
    }

    return 0;
}
