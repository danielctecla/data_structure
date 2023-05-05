#include<stdio.h>
#include<stdlib.h>
#include<conio.h>

struct pila{
    int num;
    struct pila *next;
};

struct pila *iniciar(struct pila *iniciar){
    iniciar = NULL;
    return iniciar;
}

struct pila *push(struct pila *stack_top,int num);
struct pila *pop(struct pila *stack_top);
int peak(struct pila *_top);
int empty_Stack(struct pila *stack);
struct pila *delete(struct pila *stack);


void IniciarPila();
int main(){
    int n=0,data;
    system("cls");
    printf("Bienvenido a la Pila Dinamica");
    //Creamos nuestra pila y le asignamos Null ya que no la hemos inicializado.
    struct pila *top=iniciar(top);
    while (n!=5){
        printf("\n\nMenu\n1.Agregar a la Pila.\n2.Pop\n3.Peak\n4.Pila Vacia\n5.Eliminar Pila y Salir\n\nOpcion: ");
        scanf("%d",&n);
        
        switch (n){
        
        case 1:
            
            printf("\n\tIngrese el numero que quiere agregar: ");
            scanf("%d",&data);
            system("cls");
            top=push(top,data);
            break;
        case 2:
            system("cls");
            top = pop(top);
            break;
        case 3:
            system("cls");
            if (peak(top) != -1)
                printf("\nEl valor del tope es: %d\n", peak(top));

            break;
        case 4:
            system("cls");
            if(empty_Stack(top)!=-1)
                printf("\nFalse. La pila no esta vacia");
            else
                printf("\nTrue. La pila si esta vacia");
            break;
        case 5:
            system("cls");
            top=delete(top);
            break;
        default:
            if(top!=NULL)
                printf("Dirección a la que apunta es: %p\na lo que apunta es %p",top,top->next);
            break;
        }
    }

    free(top);
    getch();    

}

struct pila *push(struct pila *stack_top,int num){
    //new_nodo();
    struct pila *nodo = (struct pila *)malloc(sizeof(struct pila)*1);
    nodo->num = num;
    
    //indica que es el primer elemento de mi pila
    if(stack_top==NULL){
        nodo->next=NULL;
        stack_top = nodo;
        printf("\n%d agregado correctamente",num);
        return stack_top;
    }
    
    //al no ser el primer elemento, entonces anidamos el nuevo nodo
    //al nodo que esta en el tope
    // después stack_top se le asigna el nuevo nodo como top
    nodo->next=stack_top;
    stack_top=nodo;
    printf("\n%d agregado correctamente",num);
    return stack_top;
}

struct pila *pop(struct pila *stack_top){
    
    if(empty_Stack(stack_top)!=1){
        printf("\nstack underflow");
        return NULL;
    }

    struct pila *borrar=NULL;

    borrar=stack_top;
    printf("\nEl elemento eliminado es:%d\n",borrar->num);
    stack_top=stack_top->next;
    free(borrar);

    return stack_top;
}

int empty_Stack(struct pila *stack){
    if(stack==NULL){
        return -1; //retornamos -1 para decir que la Pila está vacía
    }
    return 1; //1 es falso en nuestro caso para deciru que la Pila no está vacía
}

int peak(struct pila *_top){
    //Comprobamos si la pila esta vacía, de ser así retornamos -1.
    if(empty_Stack(_top)!=1){
        printf("\nPila vacia");
        return -1;
    }
    
    return _top->num;
}

struct pila *delete(struct pila *stack){
    system("cls");
    if(empty_Stack(stack)==-1){
        printf("\n\nHas salido de la pila y no quedaron elementos en ella. Presiona Enter.\n");
        return NULL;
    }else{
        printf("\n\nHas salido de la pila y eliminamos todos los elementos de la pila. Presiona Enter.\n");
    }

    struct pila *temp= NULL;
    while (stack->next!=NULL){
        temp=stack;
        stack= stack->next;
        free(temp);
    }
    
    return NULL;
        
}
