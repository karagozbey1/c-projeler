#include <stdio.h>
#include <stdlib.h>

struct Dugum {
    int katsayi;
    int us;
    struct Dugum* sonraki;
};

struct Dugum* yeniDugum(int katsayi, int us) {
    struct Dugum* yeniDugum = (struct Dugum*)malloc(sizeof(struct Dugum));
    yeniDugum->katsayi = katsayi;
    yeniDugum->us = us;
    yeniDugum->sonraki = NULL;
    return yeniDugum;
}

void ekle(struct Dugum** bas, int katsayi, int us) {
    struct Dugum* temp = *bas;
    if (temp == NULL) {
        *bas = yeniDugum(katsayi, us);
        return;
    }
    while (temp->sonraki != NULL)
        temp = temp->sonraki;
    temp->sonraki = yeniDugum(katsayi, us);
}

void dugumleriYazdir(struct Dugum* dugum) {
    while (dugum != NULL) {
        printf("%dx^%d ", dugum->katsayi, dugum->us);
        dugum = dugum->sonraki;
    }
    printf("\n");
}

void diziYazdir(int dizi[], int derece) {
    int i;
    for (i = derece; i >= 0; i--) {
        printf("%dx^%d ", dizi[i], i);
    }
    printf("\n");
}

struct Dugum* polinomlariTopla(int dizi[], int derece, struct Dugum* bas) {
    struct Dugum* sonuc = NULL;
    struct Dugum* sonucSonu = NULL;
    int i;
    for (i = derece; i >= 0; i--) {
        int katsayi = dizi[i];
        if (bas != NULL && bas->us == i) {
            katsayi += bas->katsayi;
            bas = bas->sonraki;
        }
        if (katsayi != 0) {
            if (sonucSonu != NULL) {
                sonucSonu->sonraki = yeniDugum(katsayi, i);
                sonucSonu = sonucSonu->sonraki;
            } else {
                sonuc = sonucSonu = yeniDugum(katsayi, i);
            }
        }
    }
    return sonuc;
}

int main() {
    int dizi1[] = {1, 2, 3, 4};
    int d1_derece = sizeof(dizi1) / sizeof(dizi1[0]) - 1;

    struct Dugum* bas = NULL;
    ekle(&bas, 5, 3);
    ekle(&bas, 4, 2);
    ekle(&bas, 3, 1);
    ekle(&bas, 2, 0);

    printf("Birinci polinom: ");
    diziYazdir(dizi1, d1_derece);
    printf("Ikinci polinom: ");
    dugumleriYazdir(bas);

    struct Dugum* sonuc = polinomlariTopla(dizi1, d1_derece, bas);
    printf("Toplam polinom: ");
    dugumleriYazdir(sonuc);

    return 0;
}
