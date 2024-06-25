    #include <stdio.h>
    #include <stdlib.h>

    struct TreeNode {
        int veri;
        struct TreeNode* sol;
        struct TreeNode* sag;
    };


    struct TreeNode* yeniDugumOlustur(int veri) {
        struct TreeNode* yeniDugum = (struct TreeNode*)malloc(sizeof(struct TreeNode));
        yeniDugum->veri = veri;
        yeniDugum->sol = NULL;
        yeniDugum->sag = NULL;
        return yeniDugum;
    }


    struct TreeNode* ekle(struct TreeNode* kok, int veri) {

        if (kok == NULL) {
            return yeniDugumOlustur(veri);
        }

        else if (veri < kok->veri) {
            kok->sol = ekle(kok->sol, veri);
        }

        else {
            kok->sag = ekle(kok->sag, veri);
        }
        return kok;
    }


    void inorderDolasma(struct TreeNode* kok) {
        if (kok != NULL) {
            inorderDolasma(kok->sol);
            printf("%d ", kok->veri);
            inorderDolasma(kok->sag);
        }
    }


    void preorderDolasma(struct TreeNode* kok) {
        if (kok != NULL) {
            printf("%d ", kok->veri);
            preorderDolasma(kok->sol);
            preorderDolasma(kok->sag);
        }
    }


    void postorderDolasma(struct TreeNode* kok) {
        if (kok != NULL) {
            postorderDolasma(kok->sol);
            postorderDolasma(kok->sag);
            printf("%d ", kok->veri);
        }
    }

    int main() {
        struct TreeNode* kok = NULL;
        int n;
        printf("Dizinin eleman sayısını girin: ");
        scanf("%d", &n);
        
        printf("Tamsayıları girin:\n");
        for (int i = 0; i < n; i++) {
            int num;
            scanf("%d", &num);
            kok = ekle(kok, num);
        }
        
        printf("Inorder dolaşma : ");
        inorderDolasma(kok);
        printf("\n");
        
        printf("Preorder dolaşma: ");
        preorderDolasma(kok);
        printf("\n");
        
        printf("Postorder dolaşma: ");
        postorderDolasma(kok);
        printf("\n");
        
        return 0;
    }
