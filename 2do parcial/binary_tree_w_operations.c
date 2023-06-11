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



//<---------------------------------FUNCTIONS (Binary Search Tree)----------------------------------->
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

void displayTree(struct node *root, int level) {
    if (root != NULL) {
        displayTree(root->right, level + 1); 

        for (int i = 0; i < level; i++) {
            printf("____");
        }

        printf("%d\n", root->data);
        displayTree(root->left, level + 1);
    }
}

//<------------------------------More Options------------------------------------------------>
int totalNodes(struct node *);
int totalExternalNodes(struct node *);
int Height(struct node *);
int sum_nodes(struct node *);
struct node *mirrorI(struct node *);

void more_opt(struct node *tree){
    int option;
    clear_screen();
    printf("\nSelect your option\n\t1. Total nodes\n\t2. Total tree leaves\n\t3. Tree heigh\n\t4. Sum of the nodes\n\t5. Mirror\n\n");
    do{
        printf("Option: ");
        scanf("%d",&option);
        getchar();
    }while(option <= 0 || option >= 6);

    if(option == 1)
        printf("\n\nThe total number of nodes in the tree is: %d",totalNodes(tree));
    else if(option == 2)
        printf("\n\nThe total number of tree leaves is: %d",totalExternalNodes(tree));
    else if(option == 3)
        printf("\n\nThe height of the tree is: %d",Height(tree));
    else if(option == 4)
        printf("\n\nThe sum of the nodes is: %d",sum_nodes(tree));
    else{
        struct node *Tree_mirror;
        Tree_mirror = mirrorI(tree);
        displayTree(Tree_mirror,0);
        deleteTree(Tree_mirror);
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
    

    while(select!=6){
        clear_screen();
        displayTree(tree,0);
        printf("\n\t1. Insert\n\t2. Search\n\t3. Delete\n\t4. Print Tree\n\t5. More Options\n\t6. Exit\n\n");

        do{
            printf("Choose your option: ");
            scanf("%d",&select);
        }while(select <= 0 || select >= 7);
        


        if(select == 1){
            flag = 0;

            clear_screen();
            do{
                if(flag!=0)
                    printf("this value is already in the tree.\n");
                printf("\nEnter a number: ");
                scanf("%d",&numbr);
                getchar();
                flag++;
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
        
        }else if( select == 5){

            getchar();
            more_opt(tree);
            printf("\n\nPress enter to continue...");
            getchar();

        }else if(select == 6){
            
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

    // Search node
    while (cur != NULL && cur->data != val) {
        parent = cur;
        if (val < cur->data)
            cur = cur->left;
        else
            cur = cur->right;
    }

    // if the element isn't in the tree
    if (cur == NULL) {
        printf("\nThe value to be deleted is not present in the tree.");
        return;
    }

    // cases 1 leaves node
    if (cur->left == NULL && cur->right == NULL) {
        if (parent == NULL)
            *tree = NULL;
        else if (parent->left == cur)
            parent->left = NULL;
        else
            parent->right = NULL;
        free(cur);
    }
    // case 2 node with a son
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

    // case 3 node with 2 sons
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
        return false;
    }else if(value == tree->data){
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

int totalNodes(struct node *tree){
    if(tree == NULL)
        return 0;
    else
        return ( totalNodes(tree->left) + totalNodes(tree->right) + 1);
}

int totalExternalNodes(struct node *tree){
    if(tree == NULL)
        return 0;
    else if((tree->left == NULL) && (tree->right == NULL))
        return 1;
    else
        return (totalExternalNodes(tree->left) + totalExternalNodes(tree->right)); 
}

int Height(struct node *tree){
    int leftHeight,rightHeight;
    if(tree == NULL)
        return 0;
    else{
        leftHeight = Height(tree->left);
        rightHeight = Height(tree->right);

        if(leftHeight > rightHeight)
            return (leftHeight + 1);
        else
            return (rightHeight +1 );
    }
}

int sum_nodes(struct node *tree){
    if(tree == NULL)
        return 0;
    
    return (sum_nodes(tree->left) + sum_nodes(tree->right) + tree->data);
}

struct node *mirrorI(struct node *tree){

    if(tree != NULL){
        
        struct node *ptr = (struct node *)malloc(sizeof(struct node));
        ptr->data = tree->data;
        ptr->left = mirrorI(tree->right);
        ptr->right = mirrorI(tree->left);
        

        return ptr;
    }
    
    return NULL;

}



