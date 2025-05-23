#include <stdio.h>
#include <string.h>

// define beberapa variabel tetap yang akan digunakan
// Daya setiap alat berdasarkan referensi di README.md
#define KILO 1000
#define WATT_AC 500
#define WATT_KULKAS 150
#define WATT_MESIN_CUCI 500
#define WATT_SETRIKA 300
#define WATT_DISPENSER 150
#define WATT_POMPA_AIR 500
#define WATT_TV 120
#define WATT_LAMPU 10
#define WATT_RICE_COOKER 400

// membuat list alat tetap yang akan digunakan dalam bentuk array
const char* namaAlat[] = {"AC", "KULKAS", "MESIN CUCI", "SETRIKA", "DISPENSER", "POMPA AIR", "TV", "LAMPU", "RICE COOKER"};

// membuat enum, dan struct yang dibutuhkan 
typedef enum{
    NORMAL,
    OVER
}statusAlat;

typedef enum {
    KOS,
    KECIL,
    SEDANG,
    BESAR
}tipeRumah; 

typedef struct {
    int jumlahAlat;
    int jamPemakaian;    
    statusAlat status;
    int jumlahKonsumsi;
} alat;

typedef struct {
    float total;
    tipeRumah tpRumah;
}info;

// mendefinisikan function yang digunakan
void tipe_rumah(alat *alat_point, info *infoRumah);
void total_konsumsi(alat *alat_point);
void perbandingan(alat *alat_point);
void rekomendasi(alat *alat_point);
void sort(alat *alat_point, char namaAlatSorted[][20]);

int main() {
    // define variabel struct dan array
    alat alat1[9];
    info infoRumah;
    char namaAlatSorted[9][20];

    // looping untuk mencopy string dari array namaAlat ke namaAlatSorted
    for(int i = 0; i < 9; i++) {
        strcpy(namaAlatSorted[i], namaAlat[i]);
    }

    // meminta input dari user dengan validasi jam pemakaian tidak boleh lebih dari 24 jam, dan jumlah alat serta jam pemakaian tidak bisa di bawah 0
    for(int i = 0; i < 9; i++) {
        printf("Jumlah %s: ", namaAlat[i]);
        scanf("%d", &alat1[i].jumlahAlat);
        printf("Jam Pemakaian %s: ", namaAlat[i]);
        scanf("%d", &alat1[i].jamPemakaian);

        // error handling untuk inputan user
        if(alat1[i].jamPemakaian > 24 || alat1[i].jumlahAlat < 0 || alat1[i].jamPemakaian < 0) {
            printf("Jumlah perangkat atau jam penggunaannya salah!\n");
            i--; // repeat this alat
        }
    }

    // memanggil function total_konsumsi yang mengirimkan pointer dari struct alat
    total_konsumsi(alat1);

    // memanggil fungsi tipe_rumah
    tipe_rumah(alat1, &infoRumah);

    // memanggil fungsi perbandingan
    perbandingan(alat1);

    printf("\n-----------------------------------------------------------------\n");
    printf("Total Konsumsi Listrik Selama Sebulan adalah %.2f KWh", (infoRumah.total / KILO));

    // memanggil fungsi sorting yang berisi tabel penggunaan setiap alat 
    // yang telah disorting berdasarkan beban daya dari yang tertinggi
    sort(alat1, namaAlatSorted);

    // memanggil fungsi rekomendasi
    rekomendasi(alat1);

    puts("");

    // menampilkan tipe rumah yang didapatkan dari hasil validasi fungsi tipe_rumah
    switch (infoRumah.tpRumah) {
        case KOS:
            puts("Anda tinggal di KOS!\n");
            break;
        case KECIL:
            puts("Tipe rumah anda KECIL!\n");
            break;
        case SEDANG:
            puts("Tipe rumah anda SEDANG!\n");
            break;
        case BESAR:
            puts("Tipe rumah anda BESAR!\n");
            break;
    }

    return 0;
}

// fungsi tipe_rumah, berfungsi sebagai menghitung seluruh nilai konsumsi alat-alat yang ada, dan nilai tersebut dilakukan validasi untuk dimasukkan ke dalam struct infoRumah
void tipe_rumah(alat *alat_point, info *infoRumah) {
    infoRumah->total = 0;

    for(int i = 0; i < 9; i++) {
        infoRumah->total += alat_point[i].jumlahKonsumsi;
    } 
    
    if(infoRumah->total >= 50 * KILO && infoRumah->total <= 150 * KILO) {
        infoRumah->tpRumah = KECIL;
    }
    else if(infoRumah->total > 150 * KILO && infoRumah->total <= 300 * KILO) {
        infoRumah->tpRumah = SEDANG;
    }
    else if(infoRumah->total > 300 * KILO) {
        infoRumah->tpRumah = BESAR;
    }
    else {
        infoRumah->tpRumah = KOS;
    }
}

// fungsi total_konsumsi, berfungsi untuk menghitung seluruh nilai dari masing-masing alat, berapa jumlah konsumsi nya dalam sebulan
void total_konsumsi(alat *alat_point) {
    int daya[] = {
        WATT_AC, WATT_KULKAS, WATT_MESIN_CUCI, WATT_SETRIKA,
        WATT_DISPENSER, WATT_POMPA_AIR, WATT_TV, WATT_LAMPU, WATT_RICE_COOKER
    };

    for(int i = 0; i < 9; i++) {
        alat_point[i].jumlahKonsumsi = daya[i] * alat_point[i].jamPemakaian * alat_point[i].jumlahAlat * 30;
    }
}

// fungsi perbandingan, berfungsi untuk melakukan perhitungan dan membandingkan jumlah konsumsi setiap alat dengan batas normal yang datanya didapatkan dari PLN, jika over atau normal akan dimasukkan ke dalam struct
void perbandingan(alat *alat_point) {
    int batas[] = {
    84 * KILO, 108 * KILO, 25 * KILO, 25 * KILO,
    45 * KILO, 30 * KILO, 20 * KILO, 2 * KILO, 35 * KILO
    };


    for (int i = 0; i < 9; i++) {
        if (alat_point[i].jumlahKonsumsi > batas[i]) {
            alat_point[i].status = OVER;
        } else {
            alat_point[i].status = NORMAL;
        }
    }
}

// fungsi rekomendasi, berfungsi untuk menampilkan hasil dari validasi yang telah dilakukan di fungsi perbandingan. Jika over akan diberikan saran, dan jika normal tidak menampilkan apa2.
void rekomendasi(alat *alat_point) {
    printf("\nRekomendasi: \n");
    for(int i = 0; i < 9; i++){
        switch(i){
            case 0:
                if(alat_point[i].status == OVER){
                    printf("AC: \n");
                    printf("- Kurangi durasi pemakaian\n- Atur suhu 26-27°C\n- Gunakan mode eco/sleep\n- Servis filter berkala\n");
                }
                break;
            case 1:               
                if(alat_point[i].status == OVER){
                    printf("\nKULKAS: \n");
                    printf("- Cek karet pintu & freon\n- Jangan buka pintu terlalu lama\n- Jaga jarak kulkas dari dinding\n");
                }
                break;
            case 2:                
                if(alat_point[i].status == OVER){
                    printf("\nMESIN CUCI: \n");
                    printf("- Gunakan air suhu normal\n- Cuci dengan muatan penuh\n- Gunakan mode eco\n- Hindari mode pengering berlebihan\n");
                }
                break;
            case 3:                
                if(alat_point[i].status == OVER){
                    printf("\nSETRIKA: \n");
                    printf("- Gunakan suhu sesuai bahan\n- Setrika banyak pakaian sekaligus\n");
                }
                break;
            case 4:                
                if(alat_point[i].status == OVER){
                    printf("\nDISPENSER: \n");
                    printf("- Matikan saat tidak digunakan\n- Ganti dengan termos listrik pintar\n");
                }
                break;
            case 5:                
                if(alat_point[i].status == OVER){
                    printf("\nPOMPA AIR: \n");
                    printf("- Deteksi kebocoran\n- Gunakan toren besar\n- Pasang pelampung otomatis\n");
                }
                break;
            case 6:                
                if(alat_point[i].status == OVER){
                    printf("\nTV: \n");
                    printf("- Gunakan TV LED\n- Matikan saat tidak digunakan\n- Gunakan mode eco\n- Batasi waktu menonton\n");
                }
                break;
            case 7:                
                if(alat_point[i].status == OVER){
                    printf("\nLampu: \n");
                    printf("- Gunakan lampu LED\n- Matikan saat tidak digunakan\n");
                }
                break;
            case 8:                
                if(alat_point[i].status == OVER){
                    printf("\nRICE COOKER: \n");
                    printf("- Matikan mode keep warm setelah 1-2 jam setelah memasak\n- Gunakan magic jar terpisah jika hanya ingin menghangatkan\n");
                }
                break;
        }
    }
}

// fungsi sort, berfungsi untuk melakukan sorting pada array nama alat, yang diurutkan berdasarkan jumlah konsumsi tertinggi dari yang terendah
void sort(alat *alat_point, char namaAlatSorted[][20]){
    int i, j;
    alat temp;
    char tempNama[20];

    for (i = 0; i < 9 - 1; i++) {
        for (j = 0; j < 9 - i - 1; j++) {
            if (alat_point[j].jumlahKonsumsi > alat_point[j + 1].jumlahKonsumsi) {
                temp = alat_point[j];
                alat_point[j] = alat_point[j + 1];
                alat_point[j + 1] = temp;

                strcpy(tempNama, namaAlatSorted[j]);
                strcpy(namaAlatSorted[j], namaAlatSorted[j + 1]);
                strcpy(namaAlatSorted[j + 1], tempNama);
            }
        }
    }

    printf("\n-----------------------------------------------------------------\n");
    printf("%-15s %-10s %-10s %-20s %-10s\n", "Alat", "Jumlah", "Jam/Hari", "Konsumsi/Bln(Wh)", "Status");
    printf("-----------------------------------------------------------------\n");

    for (int i = 8; i >= 0; i--) {
        printf("%-15s %-10d %-10d %-20d %-10s\n", 
            namaAlatSorted[i], 
            alat_point[i].jumlahAlat, 
            alat_point[i].jamPemakaian, 
            alat_point[i].jumlahKonsumsi, 
            alat_point[i].status == OVER ? "OVER" : "NORMAL");
    }
}