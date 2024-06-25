#include <stdio.h>
#include <stdlib.h>

// Graf düğümünü temsil eden yapısı
struct GrafDugumu {
    int veri;
    struct GrafDugumu* sonraki;
};

// Graf veri yapısını temsil eden yapı
struct Graf {
    int dugumSayisi;
    struct GrafDugumu** komsulukListesi;
};

// Yeni bir düğüm oluştur
struct GrafDugumu* dugumOlustur(int veri) {
    struct GrafDugumu* yeniDugum = (struct GrafDugumu*)malloc(sizeof(struct GrafDugumu));
    if (!yeniDugum) {
        perror("Düğüm oluşturma başarısız");
        exit(EXIT_FAILURE);
    }
    yeniDugum->veri = veri;
    yeniDugum->sonraki = NULL;
    return yeniDugum;
}

// Yeni bir graf oluştur
struct Graf* grafOlustur(int dugumSayisi) {
    struct Graf* graf = (struct Graf*)malloc(sizeof(struct Graf));
    if (!graf) {
        perror("Graf oluşturma başarısız");
        exit(EXIT_FAILURE);
    }
    graf->dugumSayisi = dugumSayisi;

    // Komsuluk listeleri için bellek ayır
    graf->komsulukListesi = (struct GrafDugumu**)malloc(dugumSayisi * sizeof(struct GrafDugumu*));
    if (!graf->komsulukListesi) {
        perror("Komsuluk listesi oluşturma başarısız");
        exit(EXIT_FAILURE);
    }

    // Tüm komsuluk listelerini başlangıçta boş olarak ayarla
    for (int i = 0; i < dugumSayisi; i++) {
        graf->komsulukListesi[i] = NULL;
    }
    return graf;
}

// Grfa bir kenar ekle
void kenarEkle(struct Graf* graf, int kaynak, int hedef) {
    // Kaynak düğüm için yeni bir düğüm oluştur ve hedef düğüme bağla
    struct GrafDugumu* yeniDugum = dugumOlustur(hedef);
    yeniDugum->sonraki = graf->komsulukListesi[kaynak];
    graf->komsulukListesi[kaynak] = yeniDugum;

    
}

//(BFS) algoritması
void BFS(struct Graf* graf, int baslangicDugumu) {
    // Ziyaret edilen düğümleri takip etmek için bir dizi oluştur
    int* ziyaretEdildi = (int*)malloc(graf->dugumSayisi * sizeof(int));
    for (int i = 0; i < graf->dugumSayisi; i++) {
        ziyaretEdildi[i] = 0;
    }

    // BFS için bir kuyruk oluştur
    int* kuyruk = (int*)malloc(graf->dugumSayisi * sizeof(int));
    int bas = 0, son = 0;

    // Başlangıç düğümünü işaretle ve kuyruğa ekle
    ziyaretEdildi[baslangicDugumu] = 1;
    kuyruk[son++] = baslangicDugumu;

    // BFS döngüsü
    while (bas < son) {
        // Kuyruğun başındaki düğümü al ve ekrana yazdır
        int suankiDugum = kuyruk[bas++];
        printf("%d ", suankiDugum);

        // Şu anki düğümün komşularını gez
        struct GrafDugumu* gecici = graf->komsulukListesi[suankiDugum];
        while (gecici) {
            int komsuDugum = gecici->veri;
            if (!ziyaretEdildi[komsuDugum]) {
                ziyaretEdildi[komsuDugum] = 1;
                kuyruk[son++] = komsuDugum;
            }
            gecici = gecici->sonraki;
        }
    }
    free(ziyaretEdildi);
    free(kuyruk);
}

// Derinlik öncelikli arama (DFS) algoritması
void DFSUtil(struct Graf* graf, int dugum, int* ziyaretEdildi) {
    // Şu anki düğümü işaretle ve ekrana yazdır
    ziyaretEdildi[dugum] = 1;
    printf("%d ", dugum);

    // Şu anki düğümün komşularını gez
    struct GrafDugumu* gecici = graf->komsulukListesi[dugum];
    while (gecici) {
        int komsuDugum = gecici->veri;
        if (!ziyaretEdildi[komsuDugum]) {
            DFSUtil(graf, komsuDugum, ziyaretEdildi);
        }
        gecici = gecici->sonraki;
    }
}

// DFS algoritması
void DFS(struct Graf* graf, int baslangicDugumu) {
    // Ziyaret edilen düğümleri takip etmek için bir dizi oluştur
    int* ziyaretEdildi = (int*)malloc(graf->dugumSayisi * sizeof(int));
    for (int i = 0; i < graf->dugumSayisi; i++) {
        ziyaretEdildi[i] = 0;
    }

    // DFS fonksiyonunu başlangıç düğümüyle çağır
    DFSUtil(graf, baslangicDugumu, ziyaretEdildi);
    free(ziyaretEdildi);
}

int main() {
    struct Graf* graf = grafOlustur(5);
    kenarEkle(graf, 0, 1);
    kenarEkle(graf, 0, 2);
    kenarEkle(graf, 1, 3);
    kenarEkle(graf, 1, 4);
    kenarEkle(graf, 2, 4);

    printf("BFS gezintisi: ");
    BFS(graf, 0);
    printf("\n");

    printf("DFS gezintisi: ");
    DFS(graf, 0);
    printf("\n");

    return 0;
}
