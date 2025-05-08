#include "pila.h"
#include "boolean.h"
#include "confirm.h"
#include <stdio.h>
#include <stdlib.h>
//ARREGLO JUANCAAAAAAAAAAAAAAAAA
/*Crea una pila implementada con un arreglo dinamico, donde se inicializa con
 un tamanho inicial, pero se redimensSiona cuando se alcanza el limite de almacenamiento
 del arreglo. Esto es, crear un nuevo arreglo mas grande y referenciarlo a la pila.
 Retorna NULL si algun error ocurre durante el proceso creacion*/

APila apila_crear(int tamInicial) {
    /*Agregue su codigo de implementacion aqui*/
    APila p = (APila)malloc(sizeof(_APila));
    p->arr = (void**)malloc(sizeof(void*) * tamInicial);
    p->tam = tamInicial;
    p->sp = -1;
    return p;
}

/* Agrega un elemento a la pila (utilizando el metodo LIFO), el parametro void* valor significa que pasamos la direccion
 * del dato a guardar.  FUNCIONAAAAAAA?
 * Retorna ok si no hubo errores. Si hubo algun error la pila no es modificada
 */
BOOLEAN apila_push(APila p, void* valor) {
    /*Agregue su codigo de implementacion aqui*/
    if (p == NULL || p->arr == NULL) {
        return ERROR;
    }if (p->sp >= p->tam) { 
        return ERROR;
    }
    p->sp = p->sp++;
    p->arr[p->sp] = valor;
    return OK;
}
/* Saca un elemento de la pila (utilizando el metodo LIFO), el parametro void** retval significa que pasamos la direccion
 * del puntero del dato a guardar.(puntero a puntero).
 * Y asigna el dato sacado en el parametro retval (paso por referencia);
 * Retorna ok si no hubo errores. Si hubo algun error la pila no es modificada
 */
BOOLEAN apila_pop(APila p, void** retval) {
    /*Agregue su codigo de implementacion aqui*/
    if (p == NULL || p->arr == NULL || p->sp < 0) {
        return ERROR;
    }
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
    int* x = &p->sp;
    *retval = x;
    return OK;
}

/* Devuelve TRUE si la pila esta vacia. sino devuelve false,
   Si hay error devuelve TRUE (para evitar portlemas de bucles infinitos en nuestro programa);
 */
BOOLEAN apila_isEmpty(APila p) {
    /*Agregue su codigo de implementacion aqui*/
    if (p == NULL || p->sp == -1) {
        return TRUE;
    }
    return FALSE;
}
/* Elimina la pila.
    verificar que los datos sean eliminados correctamente.!
 */
BOOLEAN apila_destruir(APila p) {
    if (p == NULL || p->arr == NULL) {
        return ERROR;
    }
    free(p->arr);
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
    LPila p = NULL;
    return p;
}
/* Agrega un elemento a la pila (utilizando el metodo LIFO), el parametro void* valor significa que pasamos la direccion
 * del dato a guardar.
 * Retorna ok si no hubo errores. Si hubo algun error la pila no es modificada
 * MEL TOCO
 */
BOOLEAN lpila_push(LPila* p, void* valor) {
    /*Agregue su codigo de implementacion aqui*/
    //Se reserva memoria pra un nuevo nodo
    Nodo* nuevo = (Nodo*)malloc(sizeof(Nodo));
    CONFIRM_NOTNULL(nuevo, FALSE);
    nuevo->valor = valor; //Se asigna el nuevo valr
    nuevo->sig = *p;
    *p = nuevo;
    return OK;
}
/* Saca un elemento de la pila (utilizando el metodo LIFO), el parametro void** retval significa que pasamos la direccion
 * del puntero del dato a guardar.(puntero a puntero).
 * Y asigna el dato sacado en el parametro retval (paso por referencia);
 * Retorna ok si no hubo errores. Si hubo algun error la pila no es modificada
 */
BOOLEAN lpila_pop(LPila* p, void** valor) {
    /*Agregue su codigo de implementacion aqui*/
    CONFIRM_NOTNULL(*p, FALSE);
    Nodo* temporal = *p; //Se guarda en una variable temporal el sig nodo
    *valor = temporal->valor; //Se obtiene el valor del nodo
    *p = temporal->sig;
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
    CONFIRM_NOTNULL(p, FALSE);
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
    return (p == NULL);
}
/* Elimina la pila.
 * Verificar que la lista sea borrada correctamente!
 * MEL TOCO
 * CORREGIR
 */
BOOLEAN lpila_destruir(LPila* p) {
    /*Agregue su codigo de implementacion aqui*/
    Nodo* actual = *p; //Se guarda el nodo actual
    while (actual != NULL) {
        Nodo* temporal = actual;
        actual = actual->sig;
        free(temporal);//Se lobera el nodo actual
       
    }
    *p = NULL;
    return OK;
}