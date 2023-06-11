#include <stdio.h>
#include <stdlib.h>
#include<stdbool.h>

void clear_screen() {
    #ifdef _WIN32
        system("cls");   //Windows
    #else
        system("clear"); //Linux and macOS
    #endif
}

//<---------------------------------DATA STRUCT------------------------------->
struct node{
    int data;
    struct node *left;
    struct node *right;
};



//<---------------------------------FUNCTIONS----------------------------------->
void create_tree(struct node **);

void insertElement(struct node **, int);
void preOrderT(struct node *);
void inOrderT(struct node *);
void postOrderT(struct node *);
bool Search( struct node *, int);
void deleteElement(struct node **, int);
void deleteTree(struct node *);

void printfTree(struct node *tree){
    int n;
    clear_screen();
     printf("Choose the order in which the tree is to be printed.\n\t1. preorder\n\t2. inorder\n\t3. postorder");
    do{

        printf("\n\noption: ");
        scanf("%d",&n);
        getchar();

    }while( n<= 0 || n>= 4);

    if(n == 1){
        printf("Tree in preorder is: \n");
        preOrderT(tree);
    }else if( n == 2){
        printf("Tree in inorder is: \n");
        inOrderT(tree);
    }else{
        printf("Tree in postorder is: \n");
        postOrderT(tree);
    }
        

}


//<------------------------------------MAIN-------------------------------------->
void main(){
    int flag;
    int select=0,numbr;
    struct node *tree;

    create_tree(&tree);
    clear_screen();
    
    insertElement(&tree,25);
    insertElement(&tree,15);
    insertElement(&tree,10);
    insertElement(&tree,4);
    insertElement(&tree,12);
    insertElement(&tree,22);
    insertElement(&tree,18);
    insertElement(&tree,24);
    insertElement(&tree,50);
    insertElement(&tree,35);
    insertElement(&tree,31);
    insertElement(&tree,44);
    insertElement(&tree,70);
    insertElement(&tree,66);
    insertElement(&tree,90);
    
    while(select!=5){
        clear_screen();
        printf("\n\t1. Insert\n\t2. Search\n\t3. Delete\n\t4. Print Tree \n\t5. Exit\n\n");

        do{
            printf("Choose your option: ");
            scanf("%d",&select);
        }while(select <= 0 || select >= 6);
        


        if(select == 1){
            flag = 0;
            clear_screen();
            do{
                if(flag!=0)
                    printf("this value is already in the tree.\n");
                printf("\nEnter a number: ");
                scanf("%d",&numbr);
                getchar();
            }while(Search(tree,numbr));
            insertElement(&tree,numbr);
            printf("\nsuccessfully saved\n\nPress enter...");
            getchar();

        }else if(select == 2){

            clear_screen();
            printf("\nEnter a number to search: ");
            scanf("%d",&numbr);
            getchar();
            if(Search(tree,numbr))
                printf("\nTRUE\n\nThe number exists in the tree\n\nPress enter to continue...");
            else
                printf("\nFalse\n\nThe number doesn't exists in the tree\n\nPress enter to continue...");
            
            getchar();
            

        }else if(select == 3){

            clear_screen();
            printf("Enter a number to delete: ");
            scanf("%d",&numbr);
            getchar();
            deleteElement(&tree,numbr);
            printf("\n\nPress enter to continue...");
            getchar();

        }else if(select == 4){

            printfTree(tree);
            printf("\n\nPress enter to continue...");
            getchar();
        
        }else if(select == 5){
            
            getchar();
            deleteTree(tree);
            printf("\n\nTree has been removed (cut down)");
            printf("\n\nPress enter to continue...");
            getchar();

        }

    }
    
    
}

//<---------------------------------BODY FUNCTIONS------------------------------->

void create_tree(struct node **tree){
    *tree = NULL;
}

void insertElement(struct node **tree, int value){

    struct node *ptr, *nodeptr, *parentptr;
    ptr = (struct node *)malloc(sizeof(struct node));

    ptr->data = value;
    ptr->left = NULL;
    ptr->right = NULL;

    if(*tree == NULL)
        *tree = ptr;
    else{
        
        parentptr = NULL;
        nodeptr = *tree;

        while(nodeptr != NULL){

            parentptr = nodeptr;
            
            if(value < nodeptr->data)
                nodeptr = nodeptr->left;
            else
                nodeptr = nodeptr->right;
        }

        if(value < parentptr->data)
            parentptr->left = ptr;
        else
            parentptr->right = ptr;
        
    }

}

void deleteElement(struct node** tree, int val) {
    if (*tree == NULL) {
        printf("\nThe tree is empty");
        return;
    }

    struct node* cur = *tree;
    struct node* parent = NULL;

    // Buscar el nodo a eliminar
    while (cur != NULL && cur->data != val) {
        parent = cur;
        if (val < cur->data)
            cur = cur->left;
        else
            cur = cur->right;
    }

    // Si no se encontró el nodo
    if (cur == NULL) {
        printf("\nThe value to be deleted is not present in the tree.");
        return;
    }

    // Caso 1: Nodo hoja
    if (cur->left == NULL && cur->right == NULL) {
        if (parent == NULL)
            *tree = NULL;
        else if (parent->left == cur)
            parent->left = NULL;
        else
            parent->right = NULL;
        free(cur);
    }
    // Caso 2: Nodo con un hijo
    else if (cur->left == NULL) {
        if (parent == NULL)
            *tree = cur->right;
        else if (parent->left == cur)
            parent->left = cur->right;
        else
            parent->right = cur->right;
        free(cur);
    } else if (cur->right == NULL) {
        if (parent == NULL)
            *tree = cur->left;
        else if (parent->left == cur)
            parent->left = cur->left;
        else
            parent->right = cur->left;
        free(cur);
    }

    // Caso 3: Nodo con dos hijos
    else {
        struct node* sc = cur->right;
        struct node* scParent = cur;

        while (sc->left != NULL) {
            scParent = sc;
            sc = sc->left;
        }

        cur->data = sc->data;

        if (scParent->left == sc)
            scParent->left = sc->right;
        else
            scParent->right = sc->right;

        free(sc);
    }
    printf("\n\ndeleted item");
    return;
}

bool Search( struct node *tree,int value){
    if(tree == NULL){
        //printf("El valor no existe en el arbol");
        return false;
    }else if(value == tree->data){
        //printf("El valor %d esta en el arbol.",value);
        return true;
    }

    if(value <= tree->data)
       return Search(tree->left,value);
    else
       return Search(tree->right,value);
}

void deleteTree(struct node *tree){
    if(tree == NULL)
        return;
    
    deleteTree(tree->left);
    deleteTree(tree->right);
    free(tree);
}

void preOrderT(struct node *tree){
    if(tree!=NULL){
        printf("%d\t",tree->data);
        preOrderT(tree->left);
        preOrderT(tree->right);
    }
}

void inOrderT(struct node *tree){
    if(tree!=NULL){
        inOrderT(tree->left);
        printf("%d\t",tree->data);
        inOrderT(tree->right);
    }
}
void postOrderT(struct node *tree){
    if(tree != NULL){
        postOrderT(tree->left);
        postOrderT(tree->right);
        printf("%d\t",tree->data);
    }
}
