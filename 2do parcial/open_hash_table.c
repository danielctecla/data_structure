#include<stdio.h>
#include<stdlib.h>
#include<string.h>

/*Funcion para borrar pantalla dependiendo del sistema*/
void clear_screen() {
    #ifdef _WIN32
        system("cls");   // Para Windows
    #else
        system("clear"); // Para Linux y macOS
    #endif
}

#define TAM 13

/*Struct of our nodes*/
struct node{
    int pkey;
    struct value *value;
    struct node *next_node;
};

struct value{
    int id;
    char *name;
    char *surname;
    char *career;
};

int hashKey(int key){
    //Change to your own distribuiton function key
    return key % TAM;
}

void initialize_table(struct node **);
void insert(struct node **,int , char *, char *, char *);
void display_hashT(struct node **);
void searchOn(struct node**,int );
void freeNodes(struct node **);


//<------------------------------------- main -------------------------------------------------->
int main(){

    int select,key_search;
    struct node **hash_table;
    if((hash_table = (struct node **)malloc(sizeof(struct node *)*TAM))==NULL){
        printf("Error allocating memory");
        return 0;
    }

    initialize_table(hash_table);

    insert(hash_table,2021600260,"Daniel","Catonga","Artificial Intelligence");//1
    insert(hash_table,2021687423,"Manuel","Olguin","Artificial Intelligence");//2
    insert(hash_table,2023636238,"Itziar","Segura","Artificial Intelligence");//3
    insert(hash_table,2023566645,"Antonio","Estrada","Artificial Intelligence");//4
    insert(hash_table,2023743794,"Ilse","Castro","Artificial Intelligence");//5
    insert(hash_table,2023865348,"Alexis","Chavez","Artificial Intelligence");//6
    insert(hash_table,2023786557,"Ariadna","Chico","Artificial Intelligence");//7
    insert(hash_table,2023587469,"Valeria","Rivero","Artificial Intelligence");//8
    insert(hash_table,2023535477,"Emmanuel","Ponce","Artificial Intelligence");//9
    insert(hash_table,2023378528,"Daniel","Ugalde","Artificial Intelligence");//10
    insert(hash_table,2023698949,"Uday","Victoria","Artificial Intelligence");//11
    insert(hash_table,2023274859,"Carlos","Hernandez","Data Science");//12

    do{
        clear_screen();
        printf("\n\tMenu");
        printf("\n\t1. Search");
        printf("\n\t2. Display\n\t3. Exit");
        printf("\n\n\t\toption: ");
        scanf("%d",&select);
        getchar();
        
        if(select == 1){

            clear_screen();
            printf("Ingrese el numero de control: ");
            scanf("%d",&key_search);
            getchar();
            searchOn(hash_table,key_search);
            printf("\n\nPress enter to continue...");
            getchar();

        }else if(select == 2){

            clear_screen();
            display_hashT(hash_table);
            printf("\n\nPress enter to continue...");
            getchar();

        }else if(select == 3){
            break;
        }else{
            printf("\n\tThis option doesn't exist");
            printf("\n\nPress enter to continue...");
            getchar();
        }

    }while(select != 3);
    
    
    freeNodes(hash_table);
    display_hashT(hash_table);
    free(hash_table);
    getchar();
}

//<--------------------------------------- code functions ----------------------------------------->

// INITILIZATION
void initialize_table(struct node **hash_table){
    for(int u=0 ; u<TAM ; u++)
        *(hash_table+u) = NULL;        
}

//INSERT
void insert(struct node **hash_t,int key, char *name, char *surname, char *career){
    int index_key;

    //We get index value where data is going to save it
    index_key = hashKey(key);

    struct node *hash_node;
    struct value *hash_node_value;

    //Memory allocating
    if((hash_node = (struct node *)malloc(sizeof(struct node)))==NULL){
        printf("Error allocating memory in node");
        return;
    }
    if((hash_node_value = (struct value *)malloc(sizeof(struct value)))==NULL){
        printf("Error allocating memory in value");
        free(hash_node);
        return;
    }
    if((hash_node_value->name = (char *)malloc(sizeof(char)*50))==NULL){
        printf("Error allocating memory in node->name");
        free(hash_node_value);
        free(hash_node);
        return;
    }
    if((hash_node_value->surname = (char *)malloc(sizeof(char)*50))==NULL){
        printf("Error allocating memory in node->surname");
        free(hash_node_value->name);
        free(hash_node_value);
        free(hash_node);
        return;
    }
    if((hash_node_value->career = (char *)malloc(sizeof(char)*50))==NULL){
        printf("Error allocating memory in node->career");
        free(hash_node_value->surname);
        free(hash_node_value->name);
        free(hash_node_value);
        free(hash_node);
        return;
    }

    //set data to node
    hash_node->pkey = key;
    hash_node_value->id = key;
    strcpy(hash_node_value->name,name);
    strcpy(hash_node_value->surname,surname);
    strcpy(hash_node_value->career,career);

    hash_node->value = hash_node_value;

    /*When is first node whe need to set to NULL*/
    if(*(hash_t+index_key) == NULL)
        hash_node->next_node = NULL;

    //in a different case node needs to point to the first node in n_index hash table
    else
        hash_node->next_node = *(hash_t+index_key);

    //n_index hash_table point to new node
    *(hash_t+index_key) = hash_node;

}


//SHOW HASH TABLE
void display_hashT(struct node **hash_table){
    struct node *temp_node;
    /*We use a for() to show the data is save in hash_table
    */
    for(int v=0 ;v<TAM ;v++ ){

        //if in the n-index in hash table is equal to null means there's not any data on it
        if(*(hash_table+v)==NULL)
            printf("\n[%i]-->NULL",v);

        //in a different case the n-index cointains data
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

/* SEARCH FUNCTION!!!!!!!!!!!! */
void searchOn(struct node**hashTable,int Skey){
    int index_k = hashKey(Skey);

    if(*(hashTable+index_k) == NULL){
        printf("The key value doesn't exist");
        return;
    }

    struct node *sNode = *(hashTable+index_k);
    while(Skey != sNode->pkey && sNode->next_node!=NULL){
        sNode = sNode->next_node;
    }

    if(sNode->pkey == Skey)
        printf("\n\nUser found it");
    else{
        printf("\n\nThis user doesn't exist");
        return;
    }
    
    printf("\n\n\tThe user is:\n\tid:%d\n\tname: %s\n\tsurname: %s\n\tcareer: %s",sNode->value->id,sNode->value->name,sNode->value->surname,sNode->value->career);
    
}

void freeNodes(struct node **hash_table){
    struct node *free_node,*temp_node;
    struct value *free_value;

    for(int i = 0; i < TAM; i++){
        if(*(hash_table+i) != NULL){
            free_node = *(hash_table+i);
            while(free_node != NULL){
                temp_node = free_node->next_node;

                free_value = free_node->value;
                
                free(free_value->name);
                free(free_value->surname);
                free(free_value->career);
                free(free_value);

                printf("\nNode with %d is free now",free_node->pkey);

                free(free_node);
                free_node = temp_node;
            }

            *(hash_table+i) = NULL;

        }
    }
    
}