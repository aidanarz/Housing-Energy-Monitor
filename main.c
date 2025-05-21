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

    konsumsi[0] -= 84 * KILO;
    konsumsi[1] -= 108 * KILO;
    konsumsi[2] -= 6 * KILO;
    konsumsi[3] -= 5 * KILO;
    konsumsi[4] -= 30 * KILO;
    konsumsi[5] -= 15 * KILO;
    konsumsi[6] -= 18 * KILO;
    konsumsi[7] -= 30 * KILO;
    konsumsi[8] -= 24 * KILO;

    for (int i = 0; i < 9; i++) {
        if (konsumsi[i] > 0) {
                return i;
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