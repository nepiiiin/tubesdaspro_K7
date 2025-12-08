#include <stdio.h>
#include <string.h>

// warna teks
#define RED "\033[31m"
#define GREEN "\033[32m"
#define BLUE "\033[34m"
#define YELLOW "\033[33m"
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
    int i = 0;
    while (str[i] && (str[i] >= '0' && str[i] <= '9'))
    {
        result = result * 10 + (str[i] - '0');
        i++;
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

const char *statusKelulusan(float ipk)
{
    if (ipk >= 2.00)
        return "Lulus";
    else
        return "Tidak Lulus";
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
        } else {
            break; 
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
    int mhsKe = 0;

    printf(BLUE "\n=== DATA MAHASISWA YANG SUDAH ADA ===\n" RESET);

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

        if (jumlahMK < 1 || jumlahMK > 9) {
            printf(RED "Data mahasiswa ke-%d tidak valid (jumlah MK: %d). Melewati...\n" RESET, ++mhsKe, jumlahMK);
            while (fgets(baris, sizeof(baris), fr)) {
                hapusNewline(baris);
                if (strcmp(baris, "---") == 0) break;
            }
            continue;
        }

        printf(YELLOW"\n=== Mahasiswa ke-%d ===\n"RESET, ++mhsKe);
        printf("Nama\t: %s\n", nama);
        printf("NIM\t: %s\n", NIM);
        printf("Jumlah MK: %d\n", jumlahMK);

        float total = 0.0;
        int validMK = 0;
        for (int i = 0; i < jumlahMK; i++) {
            char namaMK[50];
            float nilai;

            if (!fgets(baris, sizeof(baris), fr)) break;
            hapusNewline(baris);
            strcpy(namaMK, baris);

            if (!fgets(baris, sizeof(baris), fr)) break;
            hapusNewline(baris);
            nilai = toFloat(baris);

            if (nilai < 0 || nilai > 100) {
                printf(RED "  %d. %s : %.2f (Nilai tidak valid)\n" RESET, i + 1, namaMK, nilai);
                continue;
        }
        printf("  %d. %s : %.2f\n", i + 1, namaMK, nilai);
            total += nilai;
            validMK++;
    }
    if (validMK == 0) {
            printf(RED "Tidak ada mata kuliah valid untuk mahasiswa ini.\n" RESET);
            continue;
}
float rata = total / validMK;
        const char *grd = grade(rata);
        float ipk = getBobotGrade(rata);
        const char *status = statusKelulusan(ipk);

        printf(GREEN "Rata-rata Nilai: %.2f\n" RESET, rata);
        printf(GREEN "Grade: %s\n" RESET, grd);
        printf(GREEN "IPK: %.2f\n" RESET, ipk);
        printf(GREEN "Status Kelulusan: %s\n" RESET, status);
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

            printf("Masukkan jumlah mata kuliah (1-9): ");
            scanf("%d", &mhs.jumlahMK);
            getchar();

            // batasi jumlahMK
            if (mhs.jumlahMK < 1 || mhs.jumlahMK > 9) {
                printf(RED "Jumlah mata kuliah harus antara 1 dan 9. Input dibatalkan.\n" RESET);
                continue;
            }

            printf("\n=== Input Mata Kuliah & Nilai ===\n");

            for (i = 0; i < mhs.jumlahMK; i++)
            {
                printf("\nMata Kuliah ke-%d\n", i + 1);

                printf("Nama Mata Kuliah : ");
                fgets(mhs.mk[i].namaMK, sizeof(mhs.mk[i].namaMK), stdin);

                printf("Nilai (0-100): ");
                scanf("%f", &mhs.mk[i].nilai);
                getchar();

                if (mhs.mk[i].nilai < 0 || mhs.mk[i].nilai > 100) {
                    printf(RED "Nilai harus antara 0 dan 100. Masukkan ulang.\n" RESET);
                    i--;  
                    continue;
                }
                total += mhs.mk[i].nilai;
            }

            // Hitung rata-rata, grade, IPK untuk data baru
            float rata = total / mhs.jumlahMK;
            const char *grd = grade(rata);
            float ipk = getBobotGrade(rata);
            const char *status = statusKelulusan(ipk);

            printf(BLUE "\n=== RINGKASAN DATA BARU ===\n" RESET);
            printf("Nama\t: %s\n", mhs.nama);
            printf("NIM\t: %s\n", mhs.NIM);
            printf("Jumlah MK: %d\n", mhs.jumlahMK);
            for (int j = 0; j < mhs.jumlahMK; j++) {
                printf("  %d. %s : %.2f\n", j + 1, mhs.mk[j].namaMK, mhs.mk[j].nilai);
            }
            printf(GREEN "Rata-rata Nilai: %.2f\n" RESET, rata);
            printf(GREEN "Grade: %s\n" RESET, grd);
            printf(GREEN "IPK: %.2f\n" RESET, ipk);
            printf(GREEN "Status Kelulusan: %s\n" RESET, status);

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