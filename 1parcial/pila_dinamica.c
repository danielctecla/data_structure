#include<stdio.h>
#include<stdlib.h>

struct pila{
    int num;
    struct pila *next;
};

struct pila *push(struct pila *stack_top,int num);
struct pila *pop(struct pila *stack_top);
int peak(struct pila *_top);
int empty_Stack(struct pila *stack);
struct pila *delete(struct pila *stack);


void IniciarPila();
int main(){
    int n=0,data;
    //Creamos nuestra pila y le asignamos Null ya que no la hemos inicializado.
    struct pila *top=NULL;
    while (n!=6){
        printf("\n\n1.Agregar a la Pila.\n2.Pop\n3.Peak\n4.Pila Vacia\n5.Eliminar Pila\n6.Salir\nOpcion: ");
        scanf("%d",&n);
        
        switch (n){
        case 1:
            printf("Ingrese el numero que quiere agregar: ");
            scanf("%d",&data);
            top=push(top,data);
            break;
        case 2:
            top = pop(top);
            break;
        case 3:
            if (peak(top) != -1)
                printf("El valor del tope es: %d\n", peak(top));
            else
                printf("La pila esta vacía\n");
            break;
        case 4:
            if(empty_Stack(top)!=-1)
                printf("La pila no esta vacia");
            else
                printf("La pila esta vacia");
            break;
        case 5:
            top=delete(top);
            break;
        default:
            if(top!=NULL)
                printf("Dirección a la que apunta es: %p\na lo que apunta es %p",top,top->next);
            break;
        }
    }

    free(top);
        

}

struct pila *push(struct pila *stack_top,int num){
    //new_nodo();
    struct pila *nodo = (struct pila *)malloc(sizeof(struct pila)*1);
    nodo->num = num;
    
    //indica que es el primer elemento de mi pila
    if(stack_top==NULL){
        nodo->next=NULL;
        stack_top = nodo;
        return stack_top;
    }

    //al no ser el primer elemento, entonces anidamos el nuevo nodo
    //al nodo que esta en el tope
    // después stack_top se le asigna el nuevo nodo como top
    nodo->next=stack_top;
    stack_top=nodo;
    return stack_top;
}

struct pila *pop(struct pila *stack_top){
    
    if(stack_top==NULL){
        printf("\nStack underflow");
        return NULL;
    }

    struct pila *borrar=NULL;

    borrar=stack_top;
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
    if(_top==NULL)
        return -1;
    
    return _top->num;
}

struct pila *delete(struct pila *stack){
    if(empty_Stack(stack)==-1){
        printf("\n\nLa pila esta vacia. Inicia la Pila");
        return NULL;
    }
    struct pila *temp= NULL;
    while (stack->next!=NULL){
        temp=stack;
        stack= stack->next;
        free(temp);
    }
    
    return NULL;
        
}