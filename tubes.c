#include <stdio.h>

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

// input

int main()
{
    struct Mahasiswa mhs; 
    int choice;

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
            // Input data mahasiswa (mirip kode asli, tapi untuk mhs[count])
            int i;
            float total = 0, rata;

            printf("\n=== Input Data Mahasiswa ===\n");

            printf("Masukkan Nama Mahasiswa : ");
            fgets(mhs.nama, sizeof(mhs.nama), stdin);

            printf("Masukkan NIM : ");
            fgets(mhs.NIM, sizeof(mhs.NIM), stdin);

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

                total += mhs    .mk[i].nilai;
            }

            rata = total / mhs.jumlahMK;

            // output

            printf("\n=== DATA MAHASISWA ===\n");
            printf("Nama\t: %s", mhs.nama);
            printf("NIM\t: %s", mhs.NIM);

            printf("\nDaftar Nilai:\n");
            for (i = 0; i < mhs.jumlahMK; i++)
            {
                printf(" %d. %sNilai: %.2f\n", i + 1, mhs.mk[i].namaMK, mhs.mk[i].nilai);
            }

            printf("\nRata-rata Nilai: %.2f\n", rata);
            printf("Grade: %s\n", grade(rata));
            printf("IPK: %.2f\n", getBobotGrade(rata));

            printf("Status: ");
            if (rata >= 60)
                printf(GREEN "Lulus\n" RESET);
            else
                printf(RED "Tidak Lulus\n" RESET);

            // nyimpan file

            FILE *fp = fopen("data.txt", "a");
            if (fp)
            {
                fprintf(fp, "%s", mhs.nama);
                fprintf(fp, "%s", mhs.NIM);
                fprintf(fp, "%d\n", mhs.jumlahMK);

                for (int j = 0; j < mhs.jumlahMK; j++){
                    fprintf(fp, "%s", mhs.mk[j].namaMK);
                    fprintf(fp, "%.2f\n", mhs.mk[j].nilai);
                }
                fclose(fp);
                printf("\nData berhasil disimpan ke file!\n");
            }
            else{
            printf("Gagal menyimpan ke file.\n");
            }

            //nampilin data

            printf("\n===SEMUA DATA DALAM FILE===\n");
            FILE *fr = fopen("data.txt", "r");
            if (!fr){
                printf("File kosong\n");
                return 0;
            }

            char baris[100];
            while (fgets(baris, sizeof(baris), fr))
            {
                if (baris[0] == '\n')
                printf("\n");
                else
                printf("%s", baris);
            }
            fclose(fr);

            return 0;
                    
        }
        else if (choice == 2)
        {
            printf("Input Data Mahasiswa Terlebih Dahulu\n");
            break;
        }
        else
        {
            printf("Terimakasih\n");
        }
    }

    return 0;
}
