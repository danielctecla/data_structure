#include<stdio.h>
#include<stdlib.h>

struct node{
    int data;
    struct node *next;
};

struct queue{
    struct node *front;
    struct node *back;
};



struct queue *create_queue(struct queue *);
struct queue *insert_ascend(struct queue *, int);
struct queue *insert_descend(struct queue *, int);
struct queue *delete_front(struct queue *);
struct queue *display(struct queue *);
int peak (struct queue *);

struct queue * vaciarCola(struct queue *cola) {
    struct node *actual = cola->front;
    struct node *siguiente;

    while (actual != NULL) {
        siguiente = actual->next;
        free(actual); // liberar la memoria del nodo actual
        actual = siguiente;
    }

    cola->front = NULL;
    cola->back = NULL;
}


int main(){
    system("cls");
    int n,dat,peek,type;
    struct queue *q;
    q=create_queue(q);
    printf("\nBienvenido \n\nDe que forma vas a tener tu cola de prioridad.");
    printf("\n\n1.Ascendente\n2.Descendente");
    
    do{
        printf("\n\n\topcion: ");
        scanf("%d",&type);
    }while(type!=1 && type!=2);
    system("cls");
    while (n!=5)
    {   
        if(type==1)
            printf("\nCola de Prioridad Ascendente\n");
        else
            printf("\nCola de Prioridad Descendente\n");

        printf("\nMenu\n1.Ingresar\n2.Eliminar\n3.Peak\n4.Display\n5.Salir\n\n\topcion:");
        scanf("%d",&n);
        switch (n)
        {
        case 1:
            printf("\n\n\tDato:");
            scanf("%d",&dat);
            system("cls");
            if(type==1)
                q=insert_ascend(q,dat);
            else
                q=insert_descend(q,dat);
            printf("\n\nAgregado\n\n");
            break;
        case 2:
            system("cls");
            q=delete_front(q);
            break;
        case 3:
            /*Esto funciona para cola donde no ingresen valores negativos ya que si ingresan el -1
            y esta al inicio de la cola dira que esta vacía la cola*/
            system("cls");
            peek = peak(q);
            if(peek!=-1){
                printf("\n\nEl valor en frente de la cola es: %d\n\n",peek);
            }
            break;
        case 4:
            system("cls");
            q=display(q);
            break;
        case 5:
            printf("\n\n\n\tHas salido del programa. Adios");
            break;
        default:
            printf("\nEsta opcion no existe");
            break;
        }
    }
    q=vaciarCola(q);
    
    free(q);
}

struct queue * create_queue(struct queue *q){
    q=(struct queue *)malloc(sizeof(struct queue)*1);
    q->back=NULL;
    q->front=NULL;

    return q;
}

struct queue *insert_ascend(struct queue *q, int dato){
    struct node *ptr = (struct node*)malloc(sizeof(struct node));
    ptr->data=dato;
    //Si es el primer valor en agregarse entonces:
    if(q->front==NULL){
        q->front=ptr;
        q->back=ptr;
        q->front->next=NULL;

    }else if(dato<q->front->data){
    /*Ordenamiento ascedente
    si el dato es menor desde un inicio se agrega.
    */
        ptr->next=q->front;
        q->front=ptr;
    }else{
        /*Recorremos la cola para encontrar su posición ascedente 
        hacemos uso de un nodo que va recorrer la cola*/
        struct node *comparador = q->front;

        while (comparador->next != NULL && dato > comparador->next->data)
            comparador=comparador->next;

        ptr->next=comparador->next;
        comparador->next=ptr;

        if(q->back==comparador){
            q->back=ptr;
        }
        
    }

    return q;

}

struct queue *delete_front(struct queue *q){
    struct node *temp;
    temp=q->front;
    if(q->front==NULL){
        printf("\n\n\tUnderflow\n\n");
    }else{
        q->front=q->front->next;
        printf("\n\n\tEl valor eliminado es: %d\n\n",temp->data);
        free(temp);
    }

    return q;


}
struct queue *display(struct queue *q){
    struct node *ptr = q->front;

    if(ptr==NULL)
        printf("\n\nLa cola esta vacia.\n\n");
    else{
        printf("\nLos datos en la cola son: \n\n");
        while (ptr!=q->back){
            printf("%d\t",ptr->data);
            ptr = ptr->next;
        }
        printf("%d",ptr->data);
        
    }
    printf("\n\n");
    return q;
}
int peak (struct queue *q){
    if(q->front==NULL){
        printf("\n\nLa Cola esta vacia\n\n");
        return -1;
    }

    return q->front->data;
}

//En esta parte básicamente es el mismo codigo de insertar ascendentemente pero intercambiando los signos
struct queue *insert_descend(struct queue *q, int dato){
    struct node *ptr = (struct node*)malloc(sizeof(struct node));
    ptr->data=dato;
    //Si es el primer valor en agregarse entonces:
    if(q->front==NULL){
        q->front=ptr;
        q->back=ptr;
        q->front->next=NULL;

    }else if(dato>q->front->data){
    /*Ordenamiento ascedente
    si el dato es menor desde un inicio se agrega.
    */
        ptr->next=q->front;
        q->front=ptr;
    }else{
        /*Recorremos la cola para encontrar su posición ascedente 
        hacemos uso de un nodo que va recorrer la cola*/
        struct node *comparador = q->front;

        while (comparador->next != NULL && dato < comparador->next->data)
            comparador=comparador->next;

        ptr->next=comparador->next;
        comparador->next=ptr;

        if(q->back==comparador){
            q->back=ptr;
        }
        
    }

    return q;

}