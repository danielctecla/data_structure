#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>

void clear_screen() {
    #ifdef _WIN32
        system("cls");   //Windows
    #else
        system("clear"); //Linux and macOS
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

    return key % TAM;
}

void initialize_table(struct node **);
void insert(struct node **,int , char *, char *, char *);
void display_hashT(struct node **);
bool searchOn(struct node**,int ,int);
void freeNodes(struct node **);
bool delete(struct node**, int);


//<------------------------------------- main -------------------------------------------------->
int main(){

    int select,id;//option and key
    char name[25],surname[25],career[50];
    struct node **hash_table;
    if((hash_table = (struct node **)malloc(sizeof(struct node *)*TAM))==NULL){
        printf("Error allocating memory");
        return 0;
    }

    initialize_table(hash_table);

    insert(hash_table,2021600230,"Daniel","Catonga","Artificial Intelligence");//1
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
        printf("\n\t2. Insert\n\t3. Delete\n\t4. Exit");
        printf("\n\n\t\toption: ");
        scanf("%d",&select);
        getchar();
        
        if(select == 1){

            clear_screen();
            printf("Enter your control number: ");
            scanf("%d",&id);
            getchar();
            searchOn(hash_table,id,0);
            printf("\n\nPress enter to continue...");
            getchar();

        }else if(select == 2){

            clear_screen();
            do{
                printf("\n\tControl number: ");
                scanf("%d",&id);
                getchar();
            }while(searchOn(hash_table,id,1));
            
            printf("\tName: ");
            fgets(name, sizeof(name), stdin);
            strtok(name, "\n");
            printf("\tSurname: ");
            fgets(surname, sizeof(surname), stdin);
            strtok(surname, "\n");
            printf("\tCareer: ");
            fgets(career, sizeof(career), stdin);
            strtok(career, "\n");
            insert(hash_table,id,name,surname,career);
            display_hashT(hash_table);
            printf("\n\nPress enter to continue...");
            getchar();

        }else if(select == 3){
            clear_screen();
            printf("Enter the control number to delete: ");
            scanf("%d",&id);
            getchar();
            if(delete(hash_table,id)){
                printf("The user has been deleted");
                display_hashT(hash_table);
            }else
                printf("This user does not exist");
            
            
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
    
    
    freeNodes(hash_table);
    //display_hashT(hash_table);
    free(hash_table);
    clear_screen();
    printf("Press enter to exit...");
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
bool searchOn(struct node**hashTable,int Skey,int type){
    int index_k = hashKey(Skey);

    if(*(hashTable+index_k) == NULL){
        if(type == 0){
            printf("The key value doesn't exist");
            return false;
        }else
            return false;
    }

    struct node *sNode = *(hashTable+index_k);
    while(Skey != sNode->pkey && sNode->next_node!=NULL){
        sNode = sNode->next_node;
    }

    if(type == 0){

        if(sNode->pkey == Skey)
            printf("\n\nUser found it");
        else{
            printf("\n\nThis user doesn't exist");
            return false;
        }
        printf("\n\n\tThe user is:\n\tid:%d\n\tname: %s\n\tsurname: %s\n\tcareer: %s",sNode->value->id,sNode->value->name,sNode->value->surname,sNode->value->career);
    
    }else{

        if(sNode->pkey == Skey){
            printf("This control number is already used.\n\n");
            return true;
        }else
            return false;
            
    }
}

bool delete(struct node**hashTable, int control_num){
    int index_k = hashKey(control_num);

    if(*(hashTable+index_k) == NULL)
        return false;

    struct node *sNode = *(hashTable+index_k),*temp_sNode;
    struct value *value_;

    if(sNode->pkey == control_num){
        *(hashTable+index_k) = sNode->next_node;
        value_ = sNode->value;
        free(value_->name);
        free(value_->surname);
        free(value_->career);

        free(sNode);

        return true;
    }
    

    while(sNode->next_node != NULL && control_num != sNode->pkey){
        temp_sNode = sNode;
        sNode = sNode->next_node;
    }

    if(sNode->pkey == control_num){
        temp_sNode->next_node = sNode->next_node;
        
        value_ = sNode->value;
        free(value_->name);
        free(value_->surname);
        free(value_->career);

        free(sNode);

        return true;
    }else
        return false;
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