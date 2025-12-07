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

void tampilkanSemuaData(struct Mahasiswa m){
     float total = 0;
    for (int i = 0; i < m.jumlahMK; i++){
        total += m.mk[i].nilai;
    }

    float rata = total / m.jumlahMK;
    
    printf("\n=== DATA MAHASISWA ===\n");
    printf("Nama\t: %s", m.nama);
    printf("NIM\t: %s", m.NIM);
    printf("\nDaftar Nilai:\n");
    for (int i = 0; i < m.jumlahMK; i++){
        printf(" %d. %sNilai: %.2f\n", i + 1, m.mk[i].namaMK, m.mk[i].nilai);
    }

    printf("\n===== NILAI RATA-RATA =====\n");
    printf("Rata-rata Nilai: %.2f\n", rata);
    printf("Grade: %s\n", grade(rata));
    printf("IPK: %.2f\n", getBobotGrade(rata) );
    printf("Status: ");
    if (rata >= 60)
        printf(GREEN "Lulus\n" RESET);
    else
        printf(RED "Tidak Lulus\n" RESET);

    FILE *fr = fopen("data.txt", "r");
    if (!fr){
        printf("File kosong\n");
        return;
    }
    printf("\n===SEMUA DATA DALAM FILE===\n");
    char baris[100];
    int lanjut = 0;
    int jumlahMK = 0;
    int hitungMK = 0;

    while (fgets(baris, sizeof(baris), fr)){
        hapusNewline(baris);
        if (lanjut == 0){
            printf("Nama    : %s\n", baris);
            lanjut = 1;
        }
        else if (lanjut == 1){
            printf("NIM     : %s\n", baris);
            lanjut = 2;
        }
        else if (lanjut == 2){
            jumlahMK = toInt(baris);
            printf("Jumlah MK: %d\n", jumlahMK);
            lanjut = 3;
            hitungMK = 0;
        }
        else if (lanjut == 3){
            printf("Mata Kuliah: %s\n", baris);
            lanjut = 4;
        }
        else if (lanjut == 4){
            printf("Nilai: %s\n", baris);
            hitungMK++;
            if (hitungMK == jumlahMK) lanjut = 0;
            }
            else{
                lanjut = 3;
        }
    }
    fclose(fr);
}

// input

int main(){
    struct Mahasiswa mhs; 
    int choice;
    int dataYgAda = 0;

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
            if (dataYgAda == 0){
                printf(RED"\nData mahasiswa belum diinputkan. Silakan input data terlebih dahulu.\n"RESET);
                continue;
            }
            tampilkanSemuaData(mhs);
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