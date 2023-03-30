#include <stdio.h>
#include <stdlib.h>

typedef int TipoDato;

#define MaxTamaPila 2

typedef struct pila{
    TipoDato A[MaxTamaPila];
    int cima;
}Pila;

void vaciaP(Pila *P);

void BorrarP(Pila *P);
TipoDato PrimeroP(Pila P);
int EsVaciaP(Pila P);
int EstallenaP(Pila P);
void Push(Pila *P, TipoDato elemento);
TipoDato Pop(Pila *p);

void vaciaP(Pila *P){
    P->cima=-1;
}

void Push(Pila *P, TipoDato elemento){
    //Comprobamos antes de agregar si esta llena la Pila o no
    if(EstallenaP(*P)){
    //Se manda lo que contiene Pila ya que no podemos mandalor como EstallenaP()
    //ya que nuestra función no lo recibe como apuntador sino como copia.
        printf("Stack Overflow");
        return;
    }
    
}

int EstallenaP(Pila P){
    //Checamos si la cima es igual al Max de la Pila
    //De ser así retorna un True y se ejecuta el if donde se invocó
    return (P.cima)+1 == MaxTamaPila; 
}


int main(){
    Pila *s;
    

}