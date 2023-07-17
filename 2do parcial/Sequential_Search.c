#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include <ctype.h>

void clear_screen() {
    #ifdef _WIN32
        system("cls");   //Windows
    #else
        system("clear"); //Linux y macOS
    #endif
}

//<-------------------------------- STRUCT ------------------------------------------>
typedef struct alumno{
    int boleta;
    char *nombre;
    char *ap_pat;
    char *ap_mat;
    float prom;

    struct alumno *next_alumn;
}ALUMNO;

typedef struct lista_escuela{
    struct alumno *init;
    struct alumno *end;
    int tot;
}LISTA;


//<-------------------------------- FUNCTIONS ------------------------------------------>
void inicializar(struct lista_escuela *list){
    list->init = NULL;
    list->end = NULL;
    list->tot = 0;
}
/*Para el ejemplo práctico solo insertaremos de forma que se agregue al final
sin tener que insertar antes o después de un nodo
ES POR CUESTIONES PRÁCTICAS INSERTAMOS SOLO EN EL FINAL
*/
void insertar(struct lista_escuela *,char *nom,char *ap_p,char *ap_mat,int blt, float prm);
void display(struct lista_escuela *);
void delete_list(struct lista_escuela *);
bool busqueda(struct lista_escuela *,char dtype, int n_control, char *ap_patbus);
bool equal_char(char *string1, char *string2);


//<-------------------------------- MAIN ------------------------------------------>
int main(){
    int boleta;
    char type='n',apellido[50];
    struct lista_escuela *lista;

    if((lista = (struct lista_escuela*)malloc(sizeof(struct lista_escuela)))== NULL){
        printf("Error al asignar la memoria en lista");
        return 0;
    }else
        inicializar(lista);
    
    //Insertamos alumnos para ahorrar la inserción de 1 por 1
    insertar(lista,"Daniel","Catonga","xxxxxx",2021600230,7.14);
    insertar(lista,"Pedro","Ugalde","xxxxxx",2023625230,8.7);
    insertar(lista,"Itziar","Segura","xxxxxx",2023827830,7.7);
    insertar(lista,"Alexis","Chavez","xxxxxx",2023827230,8.16);
    insertar(lista,"Uday","Chavez","xxxxxx",2023826230,4.16);

    while(type != 'd'){
        do{

            clear_screen();
            printf("Vamos iniciar una busqueda secuencial.\n\n");
            printf("\nEscoge el metodo de busqueda por:\na) Boleta\nb) Apellido Paterno\nc) Display Alumnos\nd) Salir\n\nIngresa: ");
            scanf("%c",&type);
            getchar();
        }while(type!='a' && type!='b' && type!='c' && type!='d' );
        
        
        
        clear_screen();

        if(type == 'a'){
            
            printf("Busqueda por Boleta\n\nIngrese la boleta para la busqueda: ");
            scanf("%d",&boleta);
            getchar();

        }else if(type == 'b'){
            
            printf("Busqueda por Apellido\n\nIngrese el apellido paterno: ");
            scanf("%s",apellido);
            getchar();

        }else if(type == 'c'){

            printf("Los alumnos son: \n\n");
            display(lista);
            getchar();
        
        }

        if(type == 'a' || type == 'b'){

            busqueda(lista,type,boleta,apellido);
            getchar();
            
        }

    }

    clear_screen();
    printf("Se ha salido de la busqueda Binaria\nPulse enter para salir: ");
    getchar();  

    delete_list(lista);//Borramos los nodos de la lista
    free(lista);//Borramos la lista
    clear_screen();
}


//<-------------------------------- CODE FUNCTIONS ------------------------------------------>
bool busqueda(struct lista_escuela *list,char dtype, int n_control, char *ap_patbus){
    int verify = 0;
    clear_screen();
    if(list->init == NULL && list->end == NULL){
        printf("La lista esta vacia");
        return false;
    }

    struct alumno *node = list->init;
    if(dtype == 'a'){

        while(node != list->end && node->boleta != n_control)
            node = node->next_alumn;
        
        if(node->boleta == n_control){
            printf("\nSe ah encontrado al alumno con la boleta %d: ",n_control);
            printf("\n\nBoleta: %d\nNombre: %s\nApellido Paterno: %s\nApellido Materno: %s\nPromedio: %.2f\n\nPulse enter...",node->boleta,node->nombre,node->ap_pat,node->ap_mat,node->prom);
            return true;
        }else
            printf("\n\nNo se ah encontrado a ningun alumno con el numero de control: %d \n\nPulse enter...",n_control);
        
            
    }else{

        while(node != list->end){

            if(equal_char(node->ap_pat,ap_patbus)){
                printf("\nSe ah encontrado al alumno con el apellido %s: ",ap_patbus);
                printf("\n\nBoleta: %d\nNombre: %s\nApellido Paterno: %s\nApellido Materno: %s\nPromedio: %.2f\n",node->boleta,node->nombre,node->ap_pat,node->ap_mat,node->prom);
                verify++;
            }
            node = node->next_alumn;
        
        }
                
    }
    
    if(equal_char(node->ap_pat,ap_patbus)){//Checa si el apellido es el mismo ya que puede que haya llegado al final
        printf("\nSe ah encontrado al alumno con el apellido %s: ",ap_patbus);
        printf("\n\nBoleta: %d\nNombre: %s\nApellido Paterno: %s\nApellido Materno: %s\nPromedio: %.2f\n",node->boleta,node->nombre,node->ap_pat,node->ap_mat,node->prom);
        verify++;
    }

    if(verify == 0)
        printf("\n\nNo se ah encontrado a ningun alumno con el nombre: %s \n\nPulse enter...",ap_patbus);
    else
        printf("\n\nPulse enter...");
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

void display(struct lista_escuela *list){
    struct alumno *node;
    
    /*El if es por si hubo errores en la asignacion de memoria en nuestros nodos
      y es el caso en el que nuestra lista este en NULL*/
    if(list->init == NULL && list->end == NULL){
        printf("La lista esta vacia");
        return;
    }
    
    node = list->init;

    while(node != list->end){
        printf("\nBoleta: %d\nNombre: %s\nApellido Paterno: %s\nApellido Materno: %s\nPromedio: %.2f\n",node->boleta,node->nombre,node->ap_pat,node->ap_mat,node->prom);
        node = node->next_alumn;
    }
    printf("\nBoleta: %d\nNombre: %s\nApellido Paterno: %s\nApellido Materno: %s\nPromedio: %.2f\n",node->boleta,node->nombre,node->ap_pat,node->ap_mat,node->prom);
}

void insertar(struct lista_escuela *list,char *nom,char *ap_p,char *ap_mat,int blt, float prm){
    
    struct alumno *nodo;

    if((nodo = (struct alumno *)malloc(sizeof(struct alumno))) == NULL){
        printf("Error al asignar memoria en nodo");
        return;
    }else if((nodo->nombre=(char *)malloc(50*sizeof(char))) == NULL){
        printf("Error al asignar memoria en nodo->nombre");
        return;
    }else if((nodo->ap_pat=(char *)malloc(50*sizeof(char))) == NULL){
        printf("Error al asignar memoria en nodo->ap_pat");
        return;
    }else if((nodo->ap_mat=(char *)malloc(50*sizeof(char))) == NULL){
        printf("Error al asignar memoria en nodo->ap_mat");
        return;
    }

    /*asignamos los datos al nodo*/
    strcpy(nodo->nombre,nom);
    strcpy(nodo->ap_pat,ap_p);
    strcpy(nodo->ap_mat,ap_mat);
    nodo->boleta=blt;
    nodo->prom=prm;

    if(list->init==NULL && list->end == NULL)
        list->init = nodo;
    else if(list->end != NULL)
        list->end->next_alumn = nodo;

    nodo->next_alumn = NULL;
    list->end = nodo;

    list->tot++;
    printf("agregado correctamente\n");
}

void delete_list(struct lista_escuela *list) {
    struct alumno *nodo, *free_node;

    if (list->init == NULL && list->end == NULL) {
        printf("La lista esta vacia");
        return;
    }

    free_node = list->init;
    while (free_node != NULL) {
        nodo = free_node->next_alumn;

        //printf("\nSe va a liberar a: %s",free_node->nombre);

        free(free_node->nombre);
        free(free_node->ap_pat);
        free(free_node->ap_mat);
        free(free_node);
        free_node = nodo;
        //printf("\tLiberado.");
        
    }

    list->init = NULL;
    list->end = NULL;
}