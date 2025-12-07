#include <stdio.h>
#include <string.h>

// warna teks
#define RED "\033[31m"
#define GREEN "\033[32m"
#define RESET "\033[0m"

struct MataKuliah
{
    char namaMK[50];
    float nilai;
};

struct Mahasiswa
{
    char nama[50];
    char NIM[20];
    int jumlahMK;
    struct MataKuliah mk[20];
};

void hapusNewline(char *str)
{
  int len = strlen(str);
  if (len > 0 && str[len - 1] == '\n'){
      str[len - 1] = '\0';
  }
}

int toInt(const char *str)
{
    int result = 0;
    while (*str)
    {
        result = result * 10 + (*str - '0');
        str++;
    }
    return result;
}

//  nyari grade berdasarkan rata-rata nilai

const char *grade(float rata)
{
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

// nyari ipk berdasarkan rata-rata nilai

float getBobotGrade(float rata)
{
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

float toFloat(const char *str) {
    float result = 0;
    int i = 0;
    int decimal = 0; 
    float factor = 0.1;

    while (str[i]) {
        if (str[i] >= '0' && str[i] <= '9') {
            if (!decimal) {
                result = result * 10 + (str[i] - '0');
            } else {
                result += (str[i] - '0') * factor;
                factor /= 10;
            }
        } else if (str[i] == '.') {
            decimal = 1;
        }
        i++;
    }
    return result;
}

void tampilkanSemuaDataFile() {
    FILE *fr = fopen("data.txt", "r");
    if (!fr) {
        printf("File kosong atau tidak ditemukan.\n");
        return;
    }

    char baris[100];
    char nama[50], NIM[20];
    int jumlahMK;
    int mahasiswaKe = 0;

    while (fgets(baris, sizeof(baris), fr)) {
        hapusNewline(baris);
        if (strlen(baris) == 0 || strcmp(baris, "---") == 0) continue;

        strcpy(nama, baris);

        if (!fgets(baris, sizeof(baris), fr)) break;
        hapusNewline(baris);
        strcpy(NIM, baris);

        if (!fgets(baris, sizeof(baris), fr)) break;
        hapusNewline(baris);
        jumlahMK = toInt(baris);

        printf("\n=== Mahasiswa ke-%d ===\n", ++mahasiswaKe);
        printf("Nama\t: %s\n", nama);
        printf("NIM\t: %s\n", NIM);
        printf("Jumlah MK: %d\n", jumlahMK);

        for (int i = 0; i < jumlahMK; i++) {
            char namaMK[50];
            float nilai;

            if (!fgets(baris, sizeof(baris), fr)) break;
            hapusNewline(baris);
            strcpy(namaMK, baris);

            if (!fgets(baris, sizeof(baris), fr)) break;
            hapusNewline(baris);
            nilai = toFloat(baris);

            printf("%d. %s : %.2f\n", i + 1, namaMK, nilai);
        }
    }

    fclose(fr);
}

// input

int main(){
    struct Mahasiswa mhs; 
    int choice;
    int dataYgAda = 1;

    while (1)
    {
        printf(RED"\n==="RESET" MENU UTAMA MENGELOLA NILAI MAHASISWA"RED" ===\n" RESET);
        printf(GREEN "1. Input Data Mahasiswa\n" RESET);
        printf(GREEN "2. Tampilkan Semua Data\n" RESET);
        printf(RED "3. Keluar\n" RESET);
        printf("Pilih opsi: ");
        scanf("%d", &choice);
        getchar(); 

        if (choice == 1)
        {
            // Input data mahasiswa
            int i;
            float total = 0;

            printf("\n=== Input Data Mahasiswa ===\n");

            printf("Masukkan Nama Mahasiswa : ");
            fgets(mhs.nama, sizeof(mhs.nama), stdin);
            hapusNewline(mhs.nama);

            printf("Masukkan NIM : ");
            fgets(mhs.NIM, sizeof(mhs.NIM), stdin);
            hapusNewline(mhs.NIM);

            printf("Masukkan jumlah mata kuliah : ");
            scanf("%d", &mhs.jumlahMK);
            getchar();

            printf("\n=== Input Mata Kuliah & Nilai ===\n");

            for (i = 0; i < mhs.jumlahMK; i++)
            {
                printf("\nMata Kuliah ke-%d\n", i + 1);

                printf("Nama Mata Kuliah : ");
                fgets(mhs.mk[i].namaMK, sizeof(mhs.mk[i].namaMK), stdin);

                printf("Nilai : ");
                scanf("%f", &mhs.mk[i].nilai);
                getchar();
                total += mhs.mk[i].nilai;

            }
            // nyimpan file

            FILE *fp = fopen("data.txt", "a");
            if (fp)
            {
                fprintf(fp, "%s\n", mhs.nama);
                fprintf(fp, "%s\n", mhs.NIM);
                fprintf(fp, "%d\n", mhs.jumlahMK);

                for (int j = 0; j < mhs.jumlahMK; j++){
                    fprintf(fp, "%s\n", mhs.mk[j].namaMK);
                    fprintf(fp, "%.2f\n", mhs.mk[j].nilai);
                }
                fprintf(fp, "---\n");
                fclose(fp);
                printf(GREEN"Data berhasil disimpan ke file.\n"RESET);
            }
            else{
            printf(RED"Gagal menyimpan ke file.\n"RESET);
            }
            dataYgAda = 1;
        }
        else if (choice == 2){
            tampilkanSemuaDataFile();
        }
        else if (choice == 3){
            printf("Terimakasih\n");
            break;
        }

        else{
            printf("Pilihan tidak valid. Silakan coba lagi.\n");
        }
    }
    return 0;
}