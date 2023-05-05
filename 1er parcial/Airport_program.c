#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <conio.h>

typedef struct elemento_avion{
    char *destino;
    char *compania;
    int hora;
    int minutos;
    int pasajeros;

    struct elemento_avion *back;
    struct elemento_avion *next;
}Airplane;

typedef struct list_ident{
    Airplane *start;
    Airplane *end;
    int num;
}Airport;

void inicializacion(Airport *lista);
Airplane *alloc(Airplane * nuevo_avion);

int ins_lista_vacia(Airport *lista, char *, char *,int,int,int);
int ins_inicio_lista(Airport *lista, char *, char *,int,int,int);
int ins_fin_lista(Airport *lista, char *, char *,int,int,int);
int ins_despues(Airport *lista, char *, char *,int,int,int,int pos);
int ins_antes(Airport *lista, char *, char *,int,int,int,int pos);

int delete(Airport *lista, int hora,int minutos,int n);

void display(Airport *lista);


int main(){
    int n,opt,posicion;
    char destino[100];
    char compania[100];
    int hora,minutos,pasajeros;
    struct list_ident AIFA;
    system("cls");
    printf("\nBienvenido al Aeropuerto");
    //primero iniciamos la lista
    inicializacion(&AIFA);
    do{
        printf("\n\n\tAIFA");
        printf("\nMenu\n1.Ingresar\n2.Hora actual\n3.Display\n4.Salir\n\n\topcion:");
        scanf("%d",&n);
        
        getchar();
        switch (n)
        {
        case 1:
            printf("\n\n\tIngrese destino: ");
            fgets(destino, sizeof(destino), stdin);
            //scanf("%s",destino);
            strtok(destino, "\n");
            printf("\tIngrese compania: ");
            fgets(compania, sizeof(compania), stdin);
            //scanf("%s",compania);
            strtok(destino, "\n");
            do{
            printf("\tIngrese hora de salida: ");
            scanf("%d",&hora);
            }while(hora<0 || hora>23);
            do{
            printf("\tIngrese minutos: ");
            scanf("%d",&minutos);
            }while(minutos<0 || minutos>59);
            printf("\tIngrese numeros  de pasajeros: ");
            scanf("%d",&pasajeros);
            system("cls");
            if(AIFA.num==0){
                if(ins_lista_vacia(&AIFA,destino,compania,hora,minutos,pasajeros)==0)
                    printf("\n\nAgregado Correctamente");
                else
                    printf("\n\nError al agregar");
            }else{
                printf("\nComo lo quieres agregar. \n1.Inicio Lista\n2.Final Lista\n3.Despues de un Elemento\n4.Antes de un Elemento\n\n\tOpcion: ");
                scanf("%d",&opt);
                system("cls");
                if (opt == 1){
                    if(ins_inicio_lista(&AIFA,destino,compania,hora,minutos,pasajeros)==0)
                        printf("\n\nAgregado Correctamente");
                    else
                        printf("\n\nError al agregar");
                }else if(opt==2){
                    if(ins_fin_lista(&AIFA,destino,compania,hora,minutos,pasajeros)==0)
                        printf("\n\nAgregado Correctamente");
                    else
                        printf("\n\nError al agregar");
                }else if(opt == 3){
                    printf("Ingrese la posicion recuerde que hay %d aviones en la lista",AIFA.num);
                    do{
                        printf("\nColocar despues del avion: ");
                        scanf("%d",&posicion);
                    }while(posicion<0 || posicion>AIFA.num);
                    if(ins_despues(&AIFA,destino,compania,hora,minutos,pasajeros,posicion)==0){
                        system("cls");
                        printf("\nAgregado Correctamente");
                        
                    }else{
                        system("cls");
                        printf("Error al agregar");
                    }
                }else{
                    printf("\nIngrese la posicion. \nRecuerde que hay %d aviones en la lista",AIFA.num);
                    do{
                        printf("\nColocar antes del avion: ");
                        scanf("%d",&posicion);
                    }while(posicion<0 || posicion>AIFA.num);
                    
                    if(ins_antes(&AIFA,destino,compania,hora,minutos,pasajeros,posicion)==0){
                        system("cls");
                        printf("\nAgregado Correctamente");

                    }else{
                        system("cls");
                        printf("Error al agregar");
                    }
                }
                
            }
            break;
        case 2:
        system("cls");
            printf("\nVamos a actualizar la lista de aviones\n\n");
            do{
                printf("\n\tIngrese hora actual: ");
                scanf("%d",&hora);
            }while(hora<0 || hora>23);
            do{
                printf("\n\tIngrese los minutos actuales: ");
                scanf("%d",&minutos);
            }while(minutos<0 || minutos>59);
            system("cls");
            if(delete(&AIFA,hora, minutos,0) == -1)
                printf("\n\nEsta vacio el Aeropuerto");
            else
                printf("\n\n\nlos vuelos que estaban antes de la hora actual han despegado(Si es que habian)");
            break;
        case 3:
            system("cls");
            display(&AIFA);
            break;
        default:
            system("cls");
            printf("Esta operacion no existe\n\n");
            break;
        }
    }while(n!=4);
    
    system("cls");
    
    delete(&AIFA,24,60,1);//Borramos a todos los aviones de la lista
    //printf("%p y %p",AIFA.start,AIFA.end);
    printf("\n\nPulse Enter para Salir: ");
    getch();   
}

void inicializacion(Airport *lista){
    lista->start = NULL;
    lista->end = NULL;
    lista->num = 0;
}

int ins_lista_vacia(Airport *lista, char *dest, char *comp,int hr,int min,int pasa){
    Airplane *nuevo_avion;

    if((nuevo_avion = alloc(nuevo_avion))==NULL)
    return -1;

    strcpy(nuevo_avion->destino,dest);
    strcpy(nuevo_avion->compania,comp);
    nuevo_avion->hora = hr;
    nuevo_avion->minutos = min;
    nuevo_avion->pasajeros = pasa;

    nuevo_avion->next = NULL;
    nuevo_avion->back = NULL;

    lista->start = nuevo_avion;
    lista->end = nuevo_avion;
    
    lista->num++;

    return 0;
    
}

int ins_inicio_lista(Airport *lista, char *dest, char *comp,int hr,int min,int pasa){
    Airplane *nuevo_avion;
    if((nuevo_avion = alloc(nuevo_avion))==NULL)
        return -1;

    strcpy(nuevo_avion->destino,dest);
    strcpy(nuevo_avion->compania,comp);
    nuevo_avion->hora = hr;
    nuevo_avion->minutos = min;
    nuevo_avion->pasajeros = pasa;

    nuevo_avion->back = NULL;
    nuevo_avion->next = lista->start;

    lista->start->back = nuevo_avion;    
    lista->start = nuevo_avion;

    lista->num++;

    return 0;
}

int ins_fin_lista(Airport *lista, char *dest, char *comp,int hr,int min,int pasa){
    Airplane *nuevo_avion;
    if((nuevo_avion = alloc(nuevo_avion))==NULL)
        return -1;

    strcpy(nuevo_avion->destino,dest);
    strcpy(nuevo_avion->compania,comp);
    nuevo_avion->hora = hr;
    nuevo_avion->minutos = min;
    nuevo_avion->pasajeros = pasa;

    nuevo_avion->back = lista->end;
    nuevo_avion->next = NULL;

    lista->end->next = nuevo_avion;
    lista->end = nuevo_avion;

    lista->num++;

    return 0;
}

int ins_despues(Airport *lista, char *dest, char *comp,int hr,int min,int pasa,int pos){
    Airplane *nuevo_avion,*w_airplane;
    if((nuevo_avion = alloc(nuevo_avion))==NULL)
        return -1;

    strcpy(nuevo_avion->destino,dest);
    strcpy(nuevo_avion->compania,comp);
    nuevo_avion->hora = hr;
    nuevo_avion->minutos = min;
    nuevo_avion->pasajeros = pasa;

    w_airplane = lista->start;

    for(int i=1;i < pos;i ++)
        w_airplane = w_airplane->next;
    
    nuevo_avion->next = w_airplane->next;
    nuevo_avion->back = w_airplane;

    if(w_airplane->next==NULL)
        lista->end = nuevo_avion;
    else
        w_airplane->next->back = nuevo_avion;

    w_airplane->next = nuevo_avion;

    lista->num++;

    return 0;
}

int ins_antes(Airport *lista, char *dest, char *comp,int hr,int min,int pasa,int pos){
    Airplane *nuevo_avion,*w_airplane;
    if((nuevo_avion = alloc(nuevo_avion))==NULL)
        return -1;

    strcpy(nuevo_avion->destino,dest);
    strcpy(nuevo_avion->compania,comp);
    nuevo_avion->hora = hr;
    nuevo_avion->minutos = min;
    nuevo_avion->pasajeros = pasa;

    w_airplane = lista->start;

    for(int i=1;i < pos;i ++)
        w_airplane = w_airplane->next;

    nuevo_avion->next = w_airplane;
    nuevo_avion->back = w_airplane->back;

    if(w_airplane->back==NULL)
        lista->start = nuevo_avion;
    else
        w_airplane->back->next = nuevo_avion;
    
    w_airplane->back = nuevo_avion;

    lista->num++;

    return 0;
}

int delete(Airport *lista, int hora, int minutos,int n){
    Airplane *avion_salida;
    if(lista->num == 0 && n == 1){
        printf("Salio del programa y el aeropuerto esta vacio.\n\n ");
        
    }else if(lista->num == 0)
        return -1;
    else if(n==1){
        printf("Salio del programa entonces todos los aviones despegaron.\n\n ");
        printf("Los aviones que despegaron son:\n\n");
    }
    avion_salida = lista->start;
    while(avion_salida != NULL){
        if(hora >= avion_salida->hora && minutos >= avion_salida->minutos){
            if(avion_salida->back != NULL)
                avion_salida->back->next = avion_salida->next;
            if(avion_salida->next != NULL)
                avion_salida->next->back = avion_salida->back;
            if(lista->start == avion_salida)
                lista->start = avion_salida->next;
            if(lista->end == avion_salida)
                lista->end = avion_salida->back;

            Airplane *despego = avion_salida;
            
            avion_salida = avion_salida -> next;
            printf("El vuelo con direccion: %s  Compania: %s Hora de salida: %2d:%2d Pasajeros: %d\t YA DESPEGO\n",despego->destino,despego->compania,despego->hora,despego->minutos,despego->pasajeros);
            free(despego->destino);
            free(despego->compania);
            lista->num--;
            free(despego);

            
        }else{
            avion_salida = avion_salida->next;
        }
    }

    return 0;
}

Airplane *alloc(Airplane * nuevo_avion){
    if((nuevo_avion = (Airplane *) malloc (sizeof(Airplane)))==NULL)
        return NULL;
    if((nuevo_avion->destino = (char *) malloc (50 * sizeof(char)))==NULL)
        return NULL;
    if((nuevo_avion->compania = (char *) malloc (50 * sizeof(char)))==NULL)
        return NULL;
    
    return nuevo_avion;
}

void display(Airport *lista){
    Airplane *mostrar;
    int i = 1;
    mostrar = lista->start;
    if(mostrar == NULL)
        printf("\nEl aeropuerto esta vacio.\n\n");
    else
        printf("\nLos vuelos que estan programados son:\n\n");
    while (mostrar!=NULL){
        printf("Vuelo: %d - Direccion: %s  Compania: %s Hora de salida: %2d:%2d Pasajeros: %d\n",i,mostrar->destino,mostrar->compania,mostrar->hora,mostrar->minutos,mostrar->pasajeros);
        mostrar = mostrar->next;
        i++;
    }
    
}


