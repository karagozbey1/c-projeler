#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_DUGUMLER 100
#define SONSUZ INT_MAX

// Graph veri yapısı
typedef struct {
    int V; // Düğüm sayısı
    int E; // Kenar sayısı
    int komsuluk[MAX_DUGUMLER][MAX_DUGUMLER]; // Komsuluk matrisi
} Graph;

// Graph oluşturma fonksiyonu
Graph* graphOlustur(int V) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->V = V;
    graph->E = 0;

    // Tüm kenarları sonsuz olarak ayarla
    for (int i = 0; i < V; ++i) {
        for (int j = 0; j < V; ++j) {
            graph->komsuluk[i][j] = SONSUZ;
        }
    }

    return graph;
}

// Graph'a kenar ekleme fonksiyonu
void kenarEkle(Graph* graph, int kaynak, int hedef, int agirlik) {
    graph->komsuluk[kaynak][hedef] = agirlik;
    graph->komsuluk[hedef][kaynak] = agirlik; // Graph'ın undirected olduğunu varsayalım
    graph->E++;
}

// Kruskal algoritması için yardımcı yapılar ve fonksiyonlar
typedef struct {
    int kaynak, hedef, agirlik;
} Kenar;

typedef struct {
    Kenar* kenarlar[MAX_DUGUMLER];
    int boyut;
} KenarListesi;

KenarListesi* kenarListesiOlustur() {
    KenarListesi* liste = (KenarListesi*)malloc(sizeof(KenarListesi));
    liste->boyut = 0;
    return liste;
}

void listeyeEkle(KenarListesi* liste, Kenar* kenar) {
    liste->kenarlar[liste->boyut++] = kenar;
}

int parentBul(int parent[], int i) {
    if (parent[i] == -1)
        return i;
    return parentBul(parent, parent[i]);
}

void kumeleriBirlestir(int parent[], int x, int y) {
    int xkume = parentBul(parent, x);
    int ykume = parentBul(parent, y);
    parent[xkume] = ykume;
}

int kenarKarsilastir(const void* a, const void* b) {
    Kenar* kenar1 = (Kenar*)a;
    Kenar* kenar2 = (Kenar*)b;
    return kenar1->agirlik - kenar2->agirlik;
}

// Kruskal algoritması
void kruskalMST(Graph* graph) {
    KenarListesi* kenarListesi = kenarListesiOlustur();
    int V = graph->V;
    Kenar sonucMST[V - 1];
    int e = 0; // resultMST[] için index
    int i = 0; // sıralı kenarlar için index

    for (int kaynak = 0; kaynak < V; kaynak++) {
        for (int hedef = kaynak + 1; hedef < V; hedef++) {
            if (graph->komsuluk[kaynak][hedef] != SONSUZ) {
                Kenar* kenar = (Kenar*)malloc(sizeof(Kenar));
                kenar->kaynak = kaynak;
                kenar->hedef = hedef;
                kenar->agirlik = graph->komsuluk[kaynak][hedef];
                listeyeEkle(kenarListesi, kenar);
            }
        }
    }

    qsort(kenarListesi->kenarlar, kenarListesi->boyut, sizeof(Kenar*), kenarKarsilastir);

    int parent[V];
    for (int v = 0; v < V; v++)
        parent[v] = -1;

    while (e < V - 1 && i < kenarListesi->boyut) {
        Kenar* sonrakiKenar = kenarListesi->kenarlar[i++];
        int x = parentBul(parent, sonrakiKenar->kaynak);
        int y = parentBul(parent, sonrakiKenar->hedef);

        if (x != y) {
            sonucMST[e++] = *sonrakiKenar;
            kumeleriBirlestir(parent, x, y);
        }
    }

    printf("Kruskal Minimum Geren Agac:\n");
    for (int i = 0; i < e; ++i)
        printf("%d -- %d == %d\n", sonucMST[i].kaynak, sonucMST[i].hedef, sonucMST[i].agirlik);
}

int main() {
    int V = 4; // Düğüm sayısı
    Graph* graph = graphOlustur(V);

    // Kenarları ekleyelim
    kenarEkle(graph, 0, 1, 10);
    kenarEkle(graph, 0, 2, 6);
    kenarEkle(graph, 0, 3, 5);
    kenarEkle(graph, 1, 3, 15);
    kenarEkle(graph, 2, 3, 4);

    kruskalMST(graph);

    return 0;
}
