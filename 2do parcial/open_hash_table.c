#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define TAM 13
/*Struct of our nodes*/
struct node{
    int pkey;
    char *name;
    char *surname;
    char *career;
    struct node *next_node;
};

int hashKey(int key){
    //Change to your own distribuiton function key
    return key % TAM;
}

void initialize_table(struct node **);
void insert(struct node **,int , char *, char *, char *);
void display_hashT(struct node **);

int main(){
    struct node **hash_table;
    if((hash_table = (struct node **)malloc(sizeof(struct node *)*TAM))==NULL){
        printf("Error allocating memory");
        return 0;
    }

    initialize_table(hash_table);

    insert(hash_table,2021600230,"Daniel","Catonga","Artificial Intelligence");
    

    display_hashT(hash_table);


    free(hash_table);
    return 0;
}

void initialize_table(struct node **hash_table){
    for(int u=0 ; u<TAM ; u++)
        *(hash_table+u) = NULL;        
}

void insert(struct node **hash_t,int key, char *name, char *surname, char *career){
    int index_key;

    index_key = hashKey(key);

    struct node *hash_node;

    if((hash_node = (struct node *)malloc(sizeof(struct node)))==NULL){
        printf("Error allocating memory in node");
        return;
    }
    if((hash_node->name = (char *)malloc(sizeof(char)*50))==NULL){
        printf("Error allocating memory in node->name");
        return;
    }
    if((hash_node->surname = (char *)malloc(sizeof(char)*50))==NULL){
        printf("Error allocating memory in node->surname");
        return;
    }
    if((hash_node->career = (char *)malloc(sizeof(char)*50))==NULL){
        printf("Error allocating memory in node->career");
        return;
    }

    hash_node->pkey = key;
    strcpy(hash_node->name,name);
    strcpy(hash_node->surname,surname);
    strcpy(hash_node->career,career);

    /*When is first node whe need to set to NULL*/
    if(*(hash_t+index_key) == NULL)
        hash_node->next_node = NULL;
    else
        hash_node->next_node = *(hash_t+index_key);

    *(hash_t+index_key) = hash_node;

    printf("Insertado con exito");
}

void display_hashT(struct node **hash_table){
    struct node *temp_node;
    for(int v=0 ;v<TAM ;v++ ){

        if(*(hash_table+v)==NULL)
            printf("\n[%i]-->NULL",v);
        else{
            printf("\n[%d]-->",v);
            temp_node = *(hash_table+v);
            while(temp_node != NULL){
                printf("%d-->",temp_node->pkey);
                temp_node = temp_node->next_node;
            }
            printf("NULL");
        }

    }
}