#include <stdio.h>
#include <stdlib.h>
#include <time.h>



void diziyi_doldur(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        arr[i] = i;
    }
}


int lineerArama(int dizi[], int size, int hedef) {
    for (int i = 0; i < size; i++) {
        if (dizi[i] == hedef) {
            return i; 
        }
    }
    return -1; 
}

int main() {

    int boyutlar[] = {1000, 10000, 100000};

   
       for (int k = 0; k < 3; k++) {
        int boyut = boyutlar[k];
        int *dizi = (int*)malloc(boyut * sizeof(int));

        
        diziyi_doldur(dizi, boyut);

    
        int hedef = boyut - 1; 

       
        struct timespec baslangic, bitis;
        double sure;

      
        clock_gettime(CLOCK_MONOTONIC, &baslangic);
        int sonuc = lineerArama(dizi, boyut, hedef);
        clock_gettime(CLOCK_MONOTONIC, &bitis);


       
        sure = (bitis.tv_sec - baslangic.tv_sec) * 1000.0 + (bitis.tv_nsec - baslangic.tv_nsec) / 1000000.0;

        printf("Dizi boyutu: %d, Arama zamanı: %f ms\n", boyut, sure);

   
        free(dizi);
    }

    return 0;
}
