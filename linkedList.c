#include <stdio.h>
#include <stdlib.h>

// Bağlı Liste Düğümü
struct linkedList
{
    int veri;
    struct linkedList *sonraki;
};

// Başlangıçta baş ve temp pointer'ları NULL olarak başlatılır
struct linkedList *head = NULL;
struct linkedList *temp = NULL;

// Yeni bir düğüm oluşturma fonksiyonu
struct linkedList *yeniDugum(int veri)
{
    struct linkedList *dugum = (struct linkedList *)malloc(sizeof(struct linkedList));
    if (dugum == NULL)
    {
        printf("Hafıza tahsisi başarısız!\n");
        exit(EXIT_FAILURE);
    }
    dugum->veri = veri;
    dugum->sonraki = NULL;
    return dugum;
}

// Listenin sonuna eleman ekleme
void sonaElemanEkle(int veri)
{
    struct linkedList *node = yeniDugum(veri);
     node->veri = veri;
     node->sonraki =NULL;

    if (head == NULL)
    {
      
        head = node;
        head->sonraki=NULL;
   }
    else
    { 
         temp = head;                                      
        while (temp->sonraki != NULL)
        {
            temp = temp->sonraki;
        }
   
        temp->sonraki = node;
    }
}

// Başa elaman ekleme
void basaElamanEkle(int veri){
struct linkedList *node=malloc(sizeof(struct linkedList));
 node->veri=veri;
 node->sonraki=NULL;
if(head== NULL) {
 
  head=node;
}
else{
node->sonraki=head; 
head=node;
}  



 }
void arayaEkle(int veri,int n){
struct linkedList *elaman=(struct linkedList *)malloc(sizeof(struct linkedList));
elaman->veri=veri;
elaman->sonraki=NULL;

temp=head;
while(temp->sonraki->veri !=n){
temp=temp->sonraki;

}
struct linkedList *temp2=(struct linkedList *)malloc(sizeof(struct linkedList));
temp2=temp->sonraki;
temp->sonraki=elaman;
elaman->sonraki=temp2;


}






 





// Bağlı listeyi yazdırma fonksiyonu
void listeyiYazdir()
{
    struct linkedList *iter = head;

    printf("Bağlı Liste: ");
    while (iter != NULL)
    {
        printf("%d -> ", iter->veri);
        iter = iter->sonraki;
    }
    printf("NULL\n");
}

int main()
{
    // Eleman ekleme işlemleri
    basaElamanEkle(27);
    basaElamanEkle(12);
    sonaElemanEkle(10);
    sonaElemanEkle(20);
    sonaElemanEkle(30);
    sonaElemanEkle(40);
    arayaEkle(48, 10);
   
    // Bağlı listeyi yazdır
    listeyiYazdir();

    return 0;
}
 