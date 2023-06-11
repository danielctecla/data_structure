#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include<ctype.h>

void clear_screen() {
    #ifdef _WIN32
        system("cls");   //Windows
    #else
        system("clear"); //Linux y macOS
    #endif
}

#define TAM 13

/*Struct of our nodes*/
struct node{
    int pkey;
    struct  data_car *car;
    struct node *next_node;
};

struct data_car{
    char *matricula;
    char *brand;
    int penalties;
};

int hashKey(char *matric_){
    int key_ = 0;
    for(int i=0;i<strlen(matric_);i++)
        key_ += matric_[i];
    
    
    key_ = key_%TAM;
    return key_;
}

void initialize_table(struct node **);
void insert(struct node **,char *, char *,bool);
void display_hashT(struct node **);
bool searchOn(struct node **,int ,char *,bool);


void freeNodes(struct node **);
bool equal_char(char *string1, char *string2);

void message(struct node **hash_table){
    struct node *node,*temp_node;
    struct data_car *_value;
    printf("\n");
    for(int i = 0; i < TAM; i++){
        if(*(hash_table+i) != NULL){
            node = *(hash_table+i);
            while(node != NULL){
                temp_node = node->next_node;

                _value = node->car;
                
                if(_value->penalties>=2)
                    printf("\nWarning! %s have %d penalties.",_value->matricula,_value->penalties);

                node = temp_node;
            }
        }
    }
    
}


//<------------------------------------- main -------------------------------------------------->
int main(){

    int select;
    char matricula_[10],brand_[20];
    struct node **hash_table;
    if((hash_table = (struct node **)malloc(sizeof(struct node *)*TAM))==NULL){
        printf("Error allocating memory");
        return 0;
    }

    initialize_table(hash_table);

    insert(hash_table,"012ABG","Mazda",true);
    insert(hash_table,"012ABG","Mazda",false);
    clear_screen();

    
    
    do{
        clear_screen();
        message(hash_table);
        printf("\n\n\n\tMenu");
        printf("\n\t1. Do a penalty fee");
        printf("\n\t2. Display\n\t3. Search\n\t4. Exit");
        printf("\n\n\t\toption: ");
        scanf("%d",&select);
        getchar();
        
        if(select == 1){

            clear_screen();
            printf("Matricula: ");
            scanf("%s",matricula_);
            getchar();
            if(searchOn(hash_table,hashKey(matricula_),matricula_,false)){
                printf("\n\nPress enter to continue...");
                getchar();
                continue;
            }
            printf("Brand: ");
            scanf("%s",brand_);
            insert(hash_table,matricula_,brand_,true);
            getchar();
            printf("\n\nPress enter to continue...");
            getchar();

        }else if(select == 2){

            clear_screen();
            display_hashT(hash_table);
            printf("\n\nPress enter to continue...");
            getchar();

        }else if(select == 3){
            clear_screen();
            printf("Matricula: ");
            scanf("%s",matricula_);
            getchar();
            searchOn(hash_table,hashKey(matricula_),matricula_,true);
            printf("\n\nPress enter to continue...");
            getchar();
        }else if(select == 4){
            break;
        }else{
            printf("\n\tThis option doesn't exist");
            printf("\n\nPress enter to continue...");
            getchar();
        }

    }while(select != 4);
    
    display_hashT(hash_table);
    freeNodes(hash_table);
    free(hash_table);
    getchar();
}

//<--------------------------------------- code functions ----------------------------------------->

// INITILIZATION
void initialize_table(struct node **hash_table){
    for(int u=0 ; u<TAM ; u++)
        *(hash_table+u) = NULL;        
}

bool equal_char(char *s1, char *s2){
    int i=0;
    /*Comparamos las cadenas que sean iguales poniendo todo en mayusculas pero sin modificar nada
    esto para que el programa sea mas amigable y no importe tanto las mayusculas o minusculas*/
    while (s1[i] != '\0' && s2[i] != '\0') {
        if (toupper(s1[i]) != toupper(s2[i])) {
            return false; // Las cadenas son diferentes
        }
        i++;
    }
    return (s1[i] == '\0' && s2[i] == '\0'); //Retorna True ya que las cadenas son iguales
}

//INSERT
void insert(struct node **hash_t,char *matric_, char *brand_,bool penalt_){
    
    int index_key;

    //We get index data_car where data is going to save it
    index_key = hashKey(matric_);

    if(penalt_ == true){
    

        struct node *hash_node;
        struct data_car *hash_node_data;

        //Memory allocating
        if((hash_node = (struct node *)malloc(sizeof(struct node)))==NULL){
            printf("Error allocating memory in node");
            return;
        }
        if((hash_node_data = (struct data_car *)malloc(sizeof(struct data_car)))==NULL){
            printf("Error allocating memory in data_car");
            free(hash_node);
            return;
        }
        if((hash_node_data->matricula = (char *)malloc(sizeof(char)*50))==NULL){
            printf("Error allocating memory in node->name");
            free(hash_node_data);
            free(hash_node);
            return;
        }
        if((hash_node_data->brand = (char *)malloc(sizeof(char)*50))==NULL){
            printf("Error allocating memory in node->surname");
            free(hash_node_data->matricula);
            free(hash_node_data);
            free(hash_node);
            return;
        }


        //set data to node
        hash_node->pkey = index_key;
        strcpy(hash_node_data->matricula,matric_);
        strcpy(hash_node_data->brand,brand_);
        hash_node_data->penalties = 1;

        hash_node->car = hash_node_data;

        /*When is first node whe need to set to NULL*/
        if(*(hash_t+index_key) == NULL)
            hash_node->next_node = NULL;

        //in a different case node needs to point to the first node in n_index hash table
        else
            hash_node->next_node = *(hash_t+index_key);

        //n_index hash_table point to new node
        *(hash_t+index_key) = hash_node;
        printf("\n\nsuccessfully added.");
    }else
        searchOn(hash_t,index_key,matric_,false);

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
                printf("%s-->",temp_node->car->matricula);
                temp_node = temp_node->next_node;
            }
            printf("NULL"); 
        }

    }
}

/* SEARCH FUNCTION!!!!!!!!!!!! */
bool searchOn(struct node**hashTable,int index_k,char *matric_,bool request){

    if(*(hashTable+index_k) == NULL){
        if(request == true)
            printf("\n\nThe key value doesn't exist\n\n");
        return false;
    }

    struct node *sNode = *(hashTable+index_k);

    while(!equal_char(matric_,sNode->car->matricula) && sNode->next_node!=NULL){
        sNode = sNode->next_node;
    }

    if(equal_char(matric_,sNode->car->matricula)){
        if(request == true){
            printf("\n\nMatricula found it\n\n");
            printf("The car is:\n\tMatricula: %s\n\tBrand: %s\n\tPenalties: %d",sNode->car->matricula,sNode->car->brand,sNode->car->penalties);
        }else{
            sNode->car->penalties++;
            printf("\n\nWarning this car: %s has passed %d times the speed limit.",sNode->car->matricula,sNode->car->penalties);
        }
            
        
        return true;
    }else{
        if(request == true)
            printf("\n\nMatricula not found it\n\n");
            
        return false;
    }
    
}

void freeNodes(struct node **hash_table){
    struct node *free_node,*temp_node;
    struct data_car *free_value;

    for(int i = 0; i < TAM; i++){
        if(*(hash_table+i) != NULL){
            free_node = *(hash_table+i);
            while(free_node != NULL){
                temp_node = free_node->next_node;

                free_value = free_node->car;
                
                free(free_value->matricula);
                free(free_value->brand);
                free(free_value);

                printf("\nNode with %d is free now",free_node->pkey);

                free(free_node);
                free_node = temp_node;
            }

            *(hash_table+i) = NULL;

        }
    }
    
}