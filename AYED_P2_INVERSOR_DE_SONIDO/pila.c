#include "pila.h"
#include "boolean.h"
#include "confirm.h"
#include <stdio.h>
#include <stdlib.h>

/*Crea una pila implementada con un arreglo dinamico, donde se inicializa con
 un tamanho inicial, pero se redimensSiona cuando se alcanza el limite de almacenamiento
 del arreglo. Esto es, crear un nuevo arreglo mas grande y referenciarlo a la pila.
 Retorna NULL si algun error ocurre durante el proceso creacion*/

APila apila_crear(int tamInicial) {
    /*Agregue su codigo de implementacion aqui*/
    APila p = (APila)malloc(sizeof(_APila)); //Se reserva memoria para la pila
    //Se reserva memoria para el arreglo que tendra los elementos
    p->arr = (void**)malloc(sizeof(void*) * tamInicial); 
    p->tam = tamInicial;//Se inicializa el tamano de la pila
    p->sp = -1; //Retorna la pila creada
    return p;
}

/* Agrega un elemento a la pila (utilizando el metodo LIFO), el parametro void* valor significa que pasamos la direccion
 * del dato a guardar.  FUNCIONAAAAAAA?
 * Retorna ok si no hubo errores. Si hubo algun error la pila no es modificada
 */
BOOLEAN apila_push(APila p, void* valor) {
    /*Agregue su codigo de implementacion aqui*/
    //Verifica que la pila y el arreglo no sea NULL
    if (p == NULL || p->arr == NULL) {
        return ERROR;
    }
    //Verifica si se ha alcanzado el limite de la pila
    if (p->sp >= p->tam) { 
        return ERROR;
    }
    p->sp++; //Se incremeta el indice del tope
    p->arr[p->sp] = valor; //Asgina el valor al tope
    return OK;
}
/* Saca un elemento de la pila (utilizando el metodo LIFO), el parametro void** retval significa que pasamos la direccion
 * del puntero del dato a guardar.(puntero a puntero).
 * Y asigna el dato sacado en el parametro retval (paso por referencia);
 * Retorna ok si no hubo errores. Si hubo algun error la pila no es modificada
 */
BOOLEAN apila_pop(APila p, void** retval) {
    /*Agregue su codigo de implementacion aqui*/
    //Verifica que la pila y el arreglo no sean NULL y que no este vacia
    if (p == NULL || p->arr == NULL || p->sp < 0) {
        return ERROR;
    }
    //Asigna el valor del tope a retval
    *retval = &p->arr[p->sp];
    //Decrementa el indice del tope
    p->sp = p->sp - 1;
    return OK;
}
/* Muestra el elemento que esta en la cima de la pila (utilizando el metodo LIFO), el parametro void** retval significa que pasamos la direccion
 * del puntero del dato a guardar.(puntero a puntero).
 * Y asigna el dato de la cima en el parametro retval (paso por referencia);
 * Retorna ok si no hubo errores. Si hubo algun error la pila no es modificada
 */
BOOLEAN apila_top(APila p, void** retval) {
    /*Agregue su codigo de implementacion aqui*/
    //Asigna el valor del tope de la pila a retval
    *retval = &p->arr[p->sp];
    return OK;
}

/* Devuelve TRUE si la pila esta vacia. sino devuelve false,
   Si hay error devuelve TRUE (para evitar portlemas de bucles infinitos en nuestro programa);
 */
BOOLEAN apila_isEmpty(APila p) {
    /*Agregue su codigo de implementacion aqui*/
    //Verifica si la pila es NULL o si no hay elementos
    if (p == NULL || p->sp == -1) {
        return TRUE;
    }
    return FALSE;
}
/* Elimina la pila.
    verificar que los datos sean eliminados correctamente.!
 */
BOOLEAN apila_destruir(APila p) {
    //Verifica que la pila y el arreglo no sean NULL
    if (p == NULL || p->arr == NULL) {
        return ERROR;
    }
    //Libera la memoria del arreglo
    free(p->arr);
    //Libera la memoria de la pila
    free(p);
    return OK;
}

/*Implementacion de Pila con lista ligada*/

/* Crea una pila implementada con listas ligadas.
 *
 *Tip, no hay requisito de saber el tamanho de la pila. se puede usar un flag de vacio|novacio
 *para mantener la funcion isEmpty mas sencillo.
 * Retorna NULL si hubo errores.
 */

LPila lpila_crear() {
    /*Agregue su codigo de implementacion aqui*/
    LPila p = (LPila)malloc(sizeof(LPila));//Reservamos memoria para una nueva pila
    CONFIRM_NOTNULL(p,FALSE);//Verifica si la memoria se asigno correctamente
    p->sig = NULL; //Se inicializa el puntero 
    return p; 
}
/* Agrega un elemento a la pila (utilizando el metodo LIFO), el parametro void* valor significa que pasamos la direccion
 * del dato a guardar.
 * Retorna ok si no hubo errores. Si hubo algun error la pila no es modificada
 * MEL TOCO
 */
BOOLEAN lpila_push(LPila p, void* valor) {
    /*Agregue su codigo de implementacion aqui*/
    //Se reserva memoria pra un nuevo nodo
    Nodo* nuevo = (Nodo*)malloc(sizeof(Nodo));
    CONFIRM_NOTNULL(nuevo, FALSE);//Verifica si la memoria se asigno correctamente
    nuevo->valor = valor; //Se asigna el nuevo valr
    //El nodo nuevo apunta al nodo actual en la cima 
    nuevo->sig = p->sig;
    p->sig = nuevo; // Actualiza la cima de la pila
    return OK;
}
/* Saca un elemento de la pila (utilizando el metodo LIFO), el parametro void** retval significa que pasamos la direccion
 * del puntero del dato a guardar.(puntero a puntero).
 * Y asigna el dato sacado en el parametro retval (paso por referencia);
 * Retorna ok si no hubo errores. Si hubo algun error la pila no es modificada
 */
BOOLEAN lpila_pop(LPila p, void** valor) {
    /*Agregue su codigo de implementacion aqui*/
    CONFIRM_NOTNULL(p, FALSE);//Verifica que la pila este vacia
    Nodo* temporal = p->sig; //Se guarda en una variable temporal el sig nodo 
    *valor = temporal->valor; //Se obtiene el valor del nodo a sacar
    p->sig = temporal->sig; //actualiza la cima de la pila y apunta al sig
    free(temporal);//Se libera el nodo
    return OK;
}
/* Muestra el elemento que esta en la cima de la pila (utilizando el metodo LIFO), el parametro void** retval significa que pasamos la direccion
 * del puntero del dato a guardar.(puntero a puntero).
 * Y asigna el dato de la cima en el parametro retval (paso por referencia);
 * Retorna ok si no hubo errores. Si hubo algun error la pila no es modificada
 * MEL TOCO
 */
BOOLEAN lpila_top(LPila p, void** valor) {
    /*Agregue su codigo de implementacion aqui*/
    CONFIRM_NOTNULL(p, FALSE); //Verifica que no este vacai
    *valor = p->valor; //Obtiene el valor del tope de la pila
    return OK;
}
/* Devuelve TRUE si la pila esta vacia. sino devuelve false,
   Si hay error devuelve TRUE (para evitar portlemas de bucles infinitos en nuestro programa);
   MEL TOCO
 */
BOOLEAN lpila_isEmpty(LPila p) {
    /*Agregue su codigo de implementacion aqui*/
    //Retorna true si esta vacio sino false 
    return (p->sig == NULL);
}
/* Elimina la pila.
 * Verificar que la lista sea borrada correctamente!
 */
BOOLEAN lpila_destruir(LPila p) {
    /*Agregue su codigo de implementacion aqui*/
    Nodo* actual = p; //Se guarda el nodo actual
    while (actual != NULL) { //Mientras que el nodo actual  no se igual a null
        Nodo* temporal = actual;//Se guarda el nodo actual en una variable temporal
        actual = actual->sig;//Avanza al sig nodo
        free(temporal);//Se lobera el nodo actual
       
    }
    return OK;
}