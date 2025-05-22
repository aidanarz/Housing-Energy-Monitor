#include <stdio.h>
#include <string.h>

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

const char* namaAlat[] = {"AC", "KULKAS", "MESIN CUCI", "SETRIKA", "DISPENSER", "POMPA AIR", "TV", "LAMPU", "RICE COOKER"};

typedef enum{
    NORMAL,
    OVER
}statusAlat;

typedef struct {
    int jumlahAlat;
    int jamPemakaian;    
    statusAlat status;
    int jumlahKonsumsi;
} alat;

typedef enum {
    KECIL,
    SEDANG,
    BESAR
}tipeRumah; 

void total_konsumsi(alat *alat_point) {
    int daya[] = {
        WATT_AC, WATT_KULKAS, WATT_MESIN_CUCI, WATT_SETRIKA,
        WATT_DISPENSER, WATT_POMPA_AIR, WATT_TV, WATT_LAMPU, WATT_RICE_COOKER
    };

    for(int i = 0; i < 9; i++) {
        alat_point[i].jumlahKonsumsi = daya[i] * alat_point[i].jamPemakaian * alat_point[i].jumlahAlat;
    }
}

void perbandingan(alat *alat_point) {
    int batas[] = {
        84 * KILO, 108 * KILO, 6 * KILO, 5 * KILO,
        30 * KILO, 15 * KILO, 18 * KILO, 30 * KILO, 24 * KILO
    };

    for (int i = 0; i < 9; i++) {
        if (alat_point[i].jumlahKonsumsi > batas[i]) {
            alat_point[i].status = OVER;
        } else {
            alat_point[i].status = NORMAL;
        }
    }
}

void rekomendasi(alat *alat_point){
    printf("\n\nRekomendasi: \n");
    for(int i = 0; i < 9; i++){
        switch(i){
            case 0:
                printf("AC: \n");
                if(alat_point[i].status == OVER){
                    printf("- Kurangi durasi pemakaian\n- Atur suhu 26-27°C\n- Gunakan mode eco/sleep\n- Servis filter berkala\n");
                }
                else{
                    printf("Sudah digunakan secara efisien\n");
                }
                break;
            case 1:
                printf("\nKULKAS: \n");
                if(alat_point[i].status == OVER){
                    printf("- Cek karet pintu & freon\n- Jangan buka pint1u terlalu lama\n- Jaga jarak kulkas dari dinding\n");
                }
                else{
                    printf("Sudah digunakan secara efisien\n");
                }
                break;
            case 2:
                printf("\nMESIN CUCI: \n");
                if(alat_point[i].status == OVER){
                    printf("- Gunakan air suhu normal\n- Cuci dengan muatan penuh\n- Gunakan mode eco\n- Hindari mode pengering berlebihan\n");
                }
                else{
                    printf("Sudah digunakan secara efisien\n");
                }
                break;
            case 3:
                printf("\nSETRIKA: \n");
                if(alat_point[i].status == OVER){
                    printf("- Gunakan suhu sesuai bahan\n- Setrika banyak pakaian sekaligus\n");
                }
                else{
                    printf("Sudah digunakan secara efisien\n");
                }
                break;
            case 4:
                printf("\nDISPENSER: \n");
                if(alat_point[i].status == OVER){
                    printf("- Matikan saat tidak digunakan\n- Ganti dengan termos listrik pintar\n");
                }
                else{
                    printf("Sudah digunakan secara efisien\n");
                }
                break;
            case 5:
                printf("\nPOMPA AIR: \n");
                if(alat_point[i].status == OVER){
                    printf("- Deteksi kebocoran\n- Gunakan toren besar\n- Pasang pelampung otomatis\n");
                }
                else{
                    printf("Sudah digunakan secara efisien\n");
                }
                break;
            case 6:
                printf("\nTV: \n");
                if(alat_point[i].status == OVER){
                    printf("- Gunakan TV LED\n- Matikan saat tidak digunakan\n- Gunakan mode eco\n- Batasi waktu menonton\n");
                }
                else{
                    printf("Sudah digunakan secara efisien\n");
                }
                break;
            case 7:
                printf("\nLampu: \n");
                if(alat_point[i].status == OVER){
                    printf("LAMPU: \n- Gunakan lampu LED\n- Matikan saat tidak digunakan\n");
                }
                else{
                    printf("Sudah digunakan secara efisien\n");
                }
                break;
            case 8:
                printf("\nRICE COOKER: \n");
                if(alat_point[i].status == OVER){
                    printf("- Matikan mode keep warm setelah 1-2 jam setelah memasak\n- Gunakan magic jar terpisah jika hanya ingin menghangatkan\n");
                }
                else{
                    printf("Sudah digunakan secara efisien\n");
                }
                break;
        }
    }
}

int main() {
    alat alat1[9];

    for(int i = 0; i < 9; i++) {
        printf("input jumlah perangkat %s dan berapa jam digunakan dalam sehari\n", namaAlat[i]);
        scanf("%d %d", &alat1[i].jumlahAlat, &alat1[i].jamPemakaian);
        if(alat1[i].jamPemakaian > 24 || alat1[i].jumlahAlat < 1 || alat1[i].jamPemakaian < 1) {
            printf("Jumlah perangkat atau jam penggunaannya salah!\n");
            i--;
        }
    }

    for (int i = 0; i < 9; i++) {
        printf("\nSetiap %d %s menyala selama %d jam/hari", alat1[i].jumlahAlat, namaAlat[i], alat1[i].jamPemakaian);
    }

    total_konsumsi(alat1);
    perbandingan(alat1);
    rekomendasi(alat1);
    
    // list batas normal
    // AC = 84 kWh / 30 hari, 4jam/hari
    // KULKAS = 108 kWh / 30 hari, 24jam/hari
    // MESIN CUCI = 6 kWh / 30 hari, 2jam/hari
    // SETRIKA = 5 kWh / 30 hari, 1jam/hari
    // DISPENSER = 30 kWh / 30 hari, 24jam/hari
    // POMPA AIR = 15 kWh / 30 hari, 1jam/hari
    // TV = 18 kWh / 30 hari, 5jam/hari
    // LAMPU(10) = 30 kWh / 6 hari, 18jam/hari
    // RICE COOKER = 24 kWh / 30 hari, 2jam/hari

    // list daya
    // AC = 500 watt
    // KULKAS = 150 watt
    // MESIN CUCI = 500 watt
    // SETRIKA = 300 watt
    // DISPENSER = 150 watt
    // POMPA AIR = 500 watt
    // TV = 120 watt
    // LAMPU = 10 watt
    // RICE COOKER = 400 watt

    // fungsi hitung total konsumsi
    // fungsi nentuin tipe rumah pake enum
    // fungsi perbandingan batas normal
    // fungsi ngasih tau rekomendasi efisiensi daya
    // Tes jarararararod
    // ketwa hahaha 

    return 0;
}