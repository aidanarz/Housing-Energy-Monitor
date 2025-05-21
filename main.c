#include <stdio.h>
#include <string.h>

#define KILO 1000

const char* namaAlat[] = {"AC", "KULKAS", "MESIN CUCI", "SETRIKA", "DISPENSER", "POMPA AIR", "TV", "LAMPU", "RICE COOKER"};

typedef enum{
    NORMAL,
    OVER
}statusAlat;

typedef struct {
    int jumlahAlat;
    int jamPemakaian;    
    statusAlat status;
} alat;

typedef enum tipeRumah{
    KECIL,
    SEDANG,
    BESAR
}; 

int perbandingan(int konsumsi[9]) {

    konsumsi[0] -= 84000;
    konsumsi[1] -= 108000;
    konsumsi[2] -= 6000;
    konsumsi[3] -= 5000;
    konsumsi[4] -= 30000;
    konsumsi[5] -= 15000;
    konsumsi[6] -= 18000;
    konsumsi[7] -= 30000;
    konsumsi[8] -= 24000;

    for (int i = 0; i < 9; i++) {
        if (konsumsi[i] > 0) {
                return i;
        }
    }
}

void rekomendasi(alat listAlat[9]){
    printf("Rekomendasi: \n");
    for(int i = 0; i < 9; i++){
        switch(i){
            case 0:
                if(listAlat[i].status == OVER){
                    printf("- Kurangi durasi pemakaian\n- Atur suhu 26-27°C\n- Gunakan mode eco/sleep\n- Servis filter berkala\n");
                }
                break;
            case 1:
                if(listAlat[i].status == OVER){
                    printf("- Cek karet pintu & freon\n- Jangan buka pintu terlalu lama\n- Jaga jarak kulkas dari dinding\n");
                }
                break;
            case 2:
                if(listAlat[i].status == OVER){
                    printf("- Gunakan air suhu normal\n- Cuci dengan muatan penuh\n- Gunakan mode eco\n- Hindari mode pengering berlebihan\n");
                }
                break;
            case 3:
                if(listAlat[i].status == OVER){
                    printf("- Gunakan suhu sesuai bahan\n- Setrika banyak pakaian sekaligus\n");
                }
                break;
            case 4:
                if(listAlat[i].status == OVER){
                    printf("- Matikan saat tidak digunakan\n- Ganti dengan termos listrik pintar\n");
                }
                break;
            case 5:
                if(listAlat[i].status == OVER){
                    printf("- Deteksi kebocoran\n- Gunakan toren besar\n- Pasang pelampung otomatis\n");
                }
                break;
            case 6:
                if(listAlat[i].status == OVER){
                    printf("- Gunakan TV LED\n- Matikan saat tidak digunakan\n- Gunakan mode eco\n- Batasi waktu menonton\n");
                }
                break;
            case 7:
                if(listAlat[i].status == OVER){
                    printf("- Gunakan lampu LED\n- Matikan saat tidak digunakan\n");
                }
                break;
            case 8:
                if(listAlat[i].status == OVER){
                    printf("- Matikan mode keep warm setelah 1-2 jam setelah memasak\n- Gunakan magic jar terpisah jika hanya ingin menghangatkan\n");
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
    }

    for (int i = 0; i < 9; i++) {
        printf("\nSetiap %d %s menyala selama %d jam/hari", alat1[i].jumlahAlat, namaAlat[i], alat1[i].jamPemakaian);
    }
    
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

    return 0;
}