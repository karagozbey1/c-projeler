#include <stdio.h>
#include <stdlib.h>

#define BOYUT 50

// Kuyruk yapısı ve fonksiyon prototipleri
typedef struct {
    int veri[BOYUT];
    int bas, son;
} Kuyruk;

Kuyruk* kuyrukOlustur();
int bosMu(Kuyruk *kuyruk);
int doluMu(Kuyruk *kuyruk);
void ekle(Kuyruk *kuyruk, int deger);
int cikar(Kuyruk *kuyruk);

// Kuyruk oluşturma
Kuyruk* kuyrukOlustur() {
    Kuyruk *kuyruk = (Kuyruk*)malloc(sizeof(Kuyruk));
    kuyruk->bas = 0;
    kuyruk->son = 0;
    return kuyruk;
}

// Kuyruk boş mu kontrolü
int bosMu(Kuyruk *kuyruk) {
    return (kuyruk->bas == kuyruk->son);
}

// Kuyruk dolu mu kontrolü
int doluMu(Kuyruk *kuyruk) {
    
    
    return ((kuyruk->son + 1) % BOYUT == kuyruk->bas);
}

// Kuyruğa eleman ekleme
void ekle(Kuyruk *kuyruk, int deger) {
    if (doluMu(kuyruk)) {
        printf("Kuyruk dolu, eleman eklenemiyor!\n");
        return;
    }
    kuyruk->veri[kuyruk->son] = deger;
    kuyruk->son = (kuyruk->son + 1) % BOYUT;
}

// Kuyruktan eleman çıkarma
int cikar(Kuyruk *kuyruk) {
    if (bosMu(kuyruk)) {
        printf("Kuyruk boş\n");
        return -1;
    }
    int cikarilanEleman = kuyruk->veri[kuyruk->bas];
    kuyruk->bas = (kuyruk->bas + 1) % BOYUT;
    return cikarilanEleman;
}

// Ana işlem fonksiyonu
void islemleriYonet(int islemler[], int islemSayisi) {
    Kuyruk *kuyruk = kuyrukOlustur();

    // Tüm işleri kuyruğa ekle
    for (int i = 0; i < islemSayisi; i++) {
        ekle(kuyruk, islemler[i]);
    }

    // İşlemleri sırayla gerçekleştir
    while (!bosMu(kuyruk)) {
        int suankiIslem = cikar(kuyruk);
        printf("İşlem tamamlandı: %d\n", suankiIslem);
    }

    free(kuyruk);
}

int main() {
    int islemler[] = {5, 10, 15, 20, 25}; // Örnek işlemler
    int islemSayisi = sizeof(islemler) / sizeof(islemler[0]);

    islemleriYonet(islemler, islemSayisi);

    return 0;
}
