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

void tipe_rumah(alat *alat_point, info *infoRumah);
void total_konsumsi(alat *alat_point);
void perbandingan(alat *alat_point);
void rekomendasi(alat *alat_point);

int main() {
    alat alat1[9];
    info infoRumah;

    for(int i = 0; i < 9; i++) {
        printf("input jumlah perangkat %s dan berapa jam digunakan dalam sehari\n", namaAlat[i]);
        scanf("%d %d", &alat1[i].jumlahAlat, &alat1[i].jamPemakaian);
        if(alat1[i].jamPemakaian > 24 || alat1[i].jumlahAlat < 0 || alat1[i].jamPemakaian < 0) {
            printf("Jumlah perangkat atau jam penggunaannya salah!\n");
            i--;
        }
    }

    total_konsumsi(alat1);

    for (int i = 0; i < 9; i++) {
        printf("%d %s menyala selama %d jam/hari dengan masing masing memakan daya: %d Wh\n", alat1[i].jumlahAlat, namaAlat[i], alat1[i].jamPemakaian, (alat1[i].jumlahKonsumsi/30));
    }

    tipe_rumah(alat1, &infoRumah);
    perbandingan(alat1);
    printf("\nTotal Konsumsi Listrik Selama Sebulan %.2f KWh", (infoRumah.total / KILO));
    rekomendasi(alat1);

    puts("");

    switch (infoRumah.tpRumah) {
        case KOS:
            puts("Anda tinggal di KOS!");
            break;
        case KECIL:
            puts("Tipe rumah anda KECIL!");
            break;
        case SEDANG:
            puts("Tipe rumah anda SEDANG!");
            break;
        case BESAR:
            puts("Tipe rumah anda BESAR!");
            break;
    }
    
    printf("\n%-15s %-10s %-10s %-15s %-10s\n", "Alat", "Jumlah", "Jam/Hari", "Konsumsi/Bln", "Status");
    for (int i = 0; i < 9; i++) {
        printf("%-15s %-10d %-10d %-15d %-10s\n", namaAlat[i], alat1[i].jumlahAlat, alat1[i].jamPemakaian, alat1[i].jumlahKonsumsi, alat1[i].status == OVER ? "OVER" : "NORMAL");
    }
    return 0;
}

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

void total_konsumsi(alat *alat_point) {

    int daya[] = {
        WATT_AC, WATT_KULKAS, WATT_MESIN_CUCI, WATT_SETRIKA,
        WATT_DISPENSER, WATT_POMPA_AIR, WATT_TV, WATT_LAMPU, WATT_RICE_COOKER
    };

    for(int i = 0; i < 9; i++) {
        alat_point[i].jumlahKonsumsi = (daya[i] * alat_point[i].jamPemakaian * alat_point[i].jumlahAlat * 30);        
    }    
}

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

void rekomendasi(alat *alat_point) {
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
                    printf("- Cek karet pintu & freon\n- Jangan buka pintu terlalu lama\n- Jaga jarak kulkas dari dinding\n");
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
                    printf("- Gunakan lampu LED\n- Matikan saat tidak digunakan\n");
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