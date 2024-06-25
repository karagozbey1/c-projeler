#include <stdio.h>
#include <stdlib.h>

typedef struct Dugum {
    int anahtar;
    struct Dugum *sol;
    struct Dugum *sag;
    int yukseklik;
} Dugum;

int maksimum(int a, int b) {
    return (a > b) ? a : b;
}

int yukseklik(Dugum *N) {
    if (N == NULL)
        return 0;
    return N->yukseklik;
}

Dugum* yeniDugum(int anahtar) {
    Dugum* dugum = (Dugum*)malloc(sizeof(Dugum));
    dugum->anahtar = anahtar;
    dugum->sol = NULL;
    dugum->sag = NULL;
    dugum->yukseklik = 1;
    return(dugum);
}

Dugum *sagRotasyon(Dugum *y) {
    Dugum *x = y->sol;
    Dugum *T2 = x->sag;

    x->sag = y;
    y->sol = T2;

    y->yukseklik = maksimum(yukseklik(y->sol), yukseklik(y->sag)) + 1;
    x->yukseklik = maksimum(yukseklik(x->sol), yukseklik(x->sag)) + 1;

    return x;
}

Dugum *solRotasyon(Dugum *x) {
    Dugum *y = x->sag;
    Dugum *T2 = y->sol;

    y->sol = x;
    x->sag = T2;

    x->yukseklik = maksimum(yukseklik(x->sol), yukseklik(x->sag)) + 1;
    y->yukseklik = maksimum(yukseklik(y->sol), yukseklik(y->sag)) + 1;

    return y;
}

int dengeFaktoru(Dugum *N) {
    if (N == NULL)
        return 0;
    return yukseklik(N->sol) - yukseklik(N->sag);
}

Dugum* ekle(Dugum* dugum, int anahtar) {
    if (dugum == NULL)
        return(yeniDugum(anahtar));

    if (anahtar < dugum->anahtar)
        dugum->sol = ekle(dugum->sol, anahtar);
    else if (anahtar > dugum->anahtar)
        dugum->sag = ekle(dugum->sag, anahtar);
    else
        return dugum;

    dugum->yukseklik = 1 + maksimum(yukseklik(dugum->sol), yukseklik(dugum->sag));

    int denge = dengeFaktoru(dugum);

    if (denge > 1 && anahtar < dugum->sol->anahtar)
        return sagRotasyon(dugum);

    if (denge < -1 && anahtar > dugum->sag->anahtar)
        return solRotasyon(dugum);

    if (denge > 1 && anahtar > dugum->sol->anahtar) {
        dugum->sol = solRotasyon(dugum->sol);
        return sagRotasyon(dugum);
    }

    if (denge < -1 && anahtar < dugum->sag->anahtar) {
        dugum->sag = sagRotasyon(dugum->sag);
        return solRotasyon(dugum);
    }

    return dugum;
}

Dugum *enKucukDegerDugum(Dugum* dugum) {
    Dugum* gecerli = dugum;

    while (gecerli->sol != NULL)
        gecerli = gecerli->sol;

    return gecerli;
}

Dugum* sil(Dugum* kok, int anahtar) {
    if (kok == NULL)
        return kok;

    if (anahtar < kok->anahtar)
        kok->sol = sil(kok->sol, anahtar);
    else if (anahtar > kok->anahtar)
        kok->sag = sil(kok->sag, anahtar);
    else {
        if ((kok->sol == NULL) || (kok->sag == NULL)) {
            Dugum *temp = kok->sol ? kok->sol : kok->sag;

            if (temp == NULL) {
                temp = kok;
                kok = NULL;
            } else
                *kok = *temp;
            free(temp);
        } else {
            Dugum* temp = enKucukDegerDugum(kok->sag);

            kok->anahtar = temp->anahtar;

            kok->sag = sil(kok->sag, temp->anahtar);
        }
    }

    if (kok == NULL)
        return kok;

    kok->yukseklik = maksimum(yukseklik(kok->sol), yukseklik(kok->sag)) + 1;

    int denge = dengeFaktoru(kok);

    if (denge > 1 && dengeFaktoru(kok->sol) >= 0)
        return sagRotasyon(kok);

    if (denge > 1 && dengeFaktoru(kok->sol) < 0) {
        kok->sol = solRotasyon(kok->sol);
        return sagRotasyon(kok);
    }

    if (denge < -1 && dengeFaktoru(kok->sag) <= 0)
        return solRotasyon(kok);

    if (denge < -1 && dengeFaktoru(kok->sag) > 0) {
        kok->sag = sagRotasyon(kok->sag);
        return solRotasyon(kok);
    }

    return kok;
}

void onDolasim(Dugum *kok) {
    if (kok != NULL) {
        printf("%d ", kok->anahtar);
        onDolasim(kok->sol);
        onDolasim(kok->sag);
    }
}

void icDolasim(Dugum *kok) {
    if (kok != NULL) {
        icDolasim(kok->sol);
        printf("%d ", kok->anahtar);
        icDolasim(kok->sag);
    }
}

void sonDolasim(Dugum *kok) {
    if (kok != NULL) {
        sonDolasim(kok->sol);
        sonDolasim(kok->sag);
        printf("%d ", kok->anahtar);
    }
}

int main() {
    Dugum *kok = NULL;

    kok = ekle(kok, 10);
    kok = ekle(kok, 20);
    kok = ekle(kok, 30);
    kok = ekle(kok, 40);
    kok = ekle(kok, 50);
    kok = ekle(kok, 25);

    printf("Ön Dolaşım: ");
    onDolasim(kok);
    printf("\n");

    printf("İç Dolaşım: ");
    icDolasim(kok);
    printf("\n");

    printf("Son Dolaşım: ");
    sonDolasim(kok);
    printf("\n");

    kok = sil(kok, 40);

    printf("Silmeden sonra Ön Dolaşım: ");
    onDolasim(kok);
    printf("\n");

    printf("Silmeden sonra İç Dolaşım: ");
    icDolasim(kok);
    printf("\n");

    printf("Silmeden sonra Son Dolaşım: ");
    sonDolasim(kok);
    printf("\n");

    return 0;
}
