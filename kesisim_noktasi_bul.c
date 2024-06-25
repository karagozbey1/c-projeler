#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct Dugum {
    int veri;
    struct Dugum* sonraki;
};

struct Dugum* yeniDugum(int veri) {
    struct Dugum* dugum = (struct Dugum*)malloc(sizeof(struct Dugum));
    dugum->veri = veri;
    dugum->sonraki = NULL;
    return dugum;
}

int kesisimBul(struct Dugum* liste1, struct Dugum* liste2) {
    if (liste1 == NULL || liste2 == NULL)
        return -1;

    struct Dugum* simdiki1 = liste1;
    struct Dugum* simdiki2 = liste2;

    int uzunluk1 = 0, uzunluk2 = 0;

    while (simdiki1 != NULL) {
        uzunluk1++;
        simdiki1 = simdiki1->sonraki;
    }
    while (simdiki2 != NULL) {
        uzunluk2++;
        simdiki2 = simdiki2->sonraki;
    }

    // Her iki listenin de başına geri dönme
    simdiki1 = liste1;
    simdiki2 = liste2;

    // Uzun olan listeyi kısa olanın uzunluğuna kadar ilerletme
    int fark = abs(uzunluk1 - uzunluk2);
    if (uzunluk1 > uzunluk2) {
        for (int i = 0; i < fark; i++)
            simdiki1 = simdiki1->sonraki;
    } else {
        for (int i = 0; i < fark; i++)
            simdiki2 = simdiki2->sonraki;
    }

    // Kesişim noktasını bulma
    while (simdiki1 != NULL && simdiki2 != NULL) {
        if (simdiki1 == simdiki2)
            return simdiki1->veri;

        simdiki1 = simdiki1->sonraki;
        simdiki2 = simdiki2->sonraki;
    }

    return -1;
}

void listeYazdir(struct Dugum* liste) {
    while (liste != NULL) {
        printf("%d ", liste->veri);
        liste = liste->sonraki;
    }
    printf("\n");
}

int main() {
    struct Dugum* liste1 = NULL;
    struct Dugum* liste2 = NULL;
    struct Dugum* temp1 = NULL;
    struct Dugum* temp2 = NULL;

    srand(time(NULL));

    // Liste 1 ve Liste 2'yi oluşturma
    for (int i = 0; i < 10; i++) {
        int rastgeleSayi1 = rand() % 100;
        struct Dugum* yeniDugum1 = yeniDugum(rastgeleSayi1);

        if (liste1 == NULL) {
            liste1 = yeniDugum1;
            temp1 = liste1;
        } else {
            temp1->sonraki = yeniDugum1;
            temp1 = temp1->sonraki;
        }

        int rastgeleSayi2 = rand() % 100;
        struct Dugum* yeniDugum2 = yeniDugum(rastgeleSayi2);

        if (liste2 == NULL) {
            liste2 = yeniDugum2;
            temp2 = liste2;
        } else {
            temp2->sonraki = yeniDugum2;
            temp2 = temp2->sonraki;
        }
    }

    // Kesişim noktasını bulma ve sonucu yazdırma
    printf("Liste 1: ");
    listeYazdir(liste1);
    printf("Liste 2: ");
    listeYazdir(liste2);

    int kesisim = kesisimBul(liste1, liste2);
    if (kesisim != -1)
        printf("Kesişim noktası: %d\n", kesisim);
    else
        printf("Listeler kesişmiyor.\n");

    return 0;
}
