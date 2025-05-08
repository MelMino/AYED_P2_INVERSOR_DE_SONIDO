#ifndef DEFINE_PILA_H
#define DEFINE_PILA_H
#include "boolean.h"
/*
 Copyright (c) 2008. Universidad Nacional de Itapua.

 En general no deberias tener que modificar este archivo a menos que el
 profesor se haya equivocado!

*/
/*Implementacion de pila con arreglo dinamico*/

typedef struct __APila {
	void** arr; /*arreglo de void*  */
	int tam;
	int sp;
}_APila;

typedef _APila* APila;

/*Crea una pila implementada con un arreglo dinamico, donde se inicializa con
un tamanho inicial, pero se redimensiona cuando se alcanza el limite de almacenamiento
del arreglo. Esto es, crear un nuevo arreglo mas grande y referenciarlo a la pila.
Retorna NULL si algun error ocurre durante el proceso creacion*/

APila apila_crear(int tamInicial);


/* Agrega un elemento a la pila (utilizando el metodo LIFO), el parametro void* valor significa que pasamos la direccion
* del dato a guardar.
* Retorna ok si no hubo errores. Si hubo algun error la pila no es modificada
*/
BOOLEAN apila_push(APila p, void* valor);
/* Saca un elemento de la pila (utilizando el metodo LIFO), el parametro void** retval significa que pasamos la direccion
* del puntero del dato a guardar.(puntero a puntero).
* Y asigna el dato sacado en el parametro retval (paso por referencia);
* Retorna ok si no hubo errores. Si hubo algun error la pila no es modificada
*/
BOOLEAN apila_pop(APila p, void** retval);
/* Muestra el elemento que esta en la cima de la pila (utilizando el metodo LIFO), el parametro void** retval significa que pasamos la direccion
* del puntero del dato a guardar.(puntero a puntero).
* Y asigna el dato de la cima en el parametro retval (paso por referencia);
* Retorna ok si no hubo errores. Si hubo algun error la pila no es modificada
*/
BOOLEAN apila_top(APila p, void** retval);

/* Devuelve TRUE si la pila esta vacia. sino devuelve false,
Si hay error devuelve TRUE (para evitar portlemas de bucles infinitos en nuestro programa);
*/
BOOLEAN apila_isEmpty(APila p);
/* Elimina la pila.
verificar que los datos sean eliminados correctamente.!
*/
BOOLEAN apila_destruir(APila p);
/*Implementacion de Pila con lista ligada*/
typedef struct _Nodo {
	struct _Nodo* sig;
	void* valor;
}Nodo;

typedef Nodo* LPila;

/* Crea una pila implementada con listas ligadas.
*
*Tip, no hay requisito de saber el tamanho de la pila. se puede usar un flag de vacio|novacio
*para mantener la funcion isEmpty mas sencillo.
* Retorna NULL si hubo errores.
*/

LPila lpila_crear();
/* Agrega un elemento a la pila (utilizando el metodo LIFO), el parametro void* valor significa que pasamos la direccion
* del dato a guardar.
* Retorna ok si no hubo errores. Si hubo algun error la pila no es modificada
*/
BOOLEAN lpila_push(LPila* p, void* valor);
/* Saca un elemento de la pila (utilizando el metodo LIFO), el parametro void** retval significa que pasamos la direccion
* del puntero del dato a guardar.(puntero a puntero).
* Y asigna el dato sacado en el parametro retval (paso por referencia);
* Retorna ok si no hubo errores. Si hubo algun error la pila no es modificada
*/
BOOLEAN lpila_pop(LPila* p, void** valor);
/* Muestra el elemento que esta en la cima de la pila (utilizando el metodo LIFO), el parametro void** retval significa que pasamos la direccion
* del puntero del dato a guardar.(puntero a puntero).
* Y asigna el dato de la cima en el parametro retval (paso por referencia);
* Retorna ok si no hubo errores. Si hubo algun error la pila no es modificada
*/
BOOLEAN lpila_top(LPila p, void** valor);
/* Devuelve TRUE si la pila esta vacia. sino devuelve false,
Si hay error devuelve TRUE (para evitar portlemas de bucles infinitos en nuestro programa);
*/
BOOLEAN lpila_isEmpty(LPila p);
/* Elimina la pila.
* Verificar que la lista sea borrada correctamente!
*/
BOOLEAN lpila_destruir(LPila* p);

#endif

