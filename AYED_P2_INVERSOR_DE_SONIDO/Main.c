/*
* File:   Main.c
*
*  Inversor de sonido
* Version original en http://www.cs.washington.edu/education/courses/cse326/08sp/projects/proj1/
* Created on 26 de agosto de 2008, 12:35
*/
#pragma warning(disable:4996)

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "confirm.h"
#include "pila.h"
/*
int main() {
	void* val = NULL;
	int y = 3;
	int* x= &y;
	APila p = apila_crear(2);
	apila_push(p, x);
	apila_push(p, x);
	apila_pop(p, val);
	apila_pop(p, val);
	apila_isEmpty(p);
	

}

*/
void GlobalReportarError(char* pszFile, int iLine) {
	fprintf(stderr, "Error detectado en %s, línea %d\n", pszFile, iLine);
}


/*programa de prueba*/
int main(int argc, char** argv) {
	LPila p = lpila_crear();
	char* data = (char*)malloc(sizeof(char) * 10);
	if (NULL == p) printf("pila nula! \n");
	{
		char* test = (char*)malloc(sizeof(char) * 10);
		char* test1 = (char*)malloc(sizeof(char) * 10);

		test = "10.000";
		test1 = "15.000";
		lpila_push(p, test);
		lpila_push(p, test1);
	}
	lpila_pop(p, (void**)&data);
	printf("data=%s ", data);
	printf("isempty=%d", lpila_isEmpty(p));
	lpila_pop(p, (void**)&data);
	printf("isempty=%d", lpila_isEmpty(p));
	return (EXIT_SUCCESS);
}

void printFormaDeUso() {
	printf("Forma de uso: \n");
	printf(">proyecto2.exe -input entrada.dat -output salida.dat -type array|list \n");
}
void procesarParametros(char** input_file, char** output_file, BOOLEAN* tipo_lpila, int argc, char** argv) {

}

int main2(int argc, char** argv) {

	/*manejar argumentos*/
	char* input_file = NULL;
	char* output_file = NULL;
	BOOLEAN tipo_lpila = TRUE;
	FILE* fd = NULL;
	long sampleRate = 0;
	int count = 0;
	LPila lp = NULL;
	APila ap = NULL;
	/* proceso de parametros */
	{
		/*declaracion de variables al inicio del bloque */
		int i = 1;
		char* tipo_pila = NULL;
		for (i = 1; i < argc; i++) {
			if (!strcmp(argv[i], "-input")) {
				i++; assert(i < argc);
				input_file = argv[i];
			}
			else if (!strcmp(argv[i], "-output")) {
				i++; assert(i < argc);
				output_file = argv[i];
			}
			else if (!strcmp(argv[i], "-type")) {
				i++; assert(i < argc);
				tipo_pila = argv[i];
				if (strcmp(argv[i], "array") && strcmp(argv[i], "list")) {
					printf("tipo_pila = %s == %d \n ", tipo_pila, (tipo_pila == "array"));
					printf("error con la linea de comando, argumento %d: '%s', el tipo de pila es incorrecto.\n", i, argv[i]);
					printFormaDeUso();
				}
				if (!strcmp(argv[i], "array")) {
					tipo_lpila = FALSE;
				}
			}
			else {
				printf("error con la linea de comando, argumento %d: '%s'\n", i, argv[i]);
				printFormaDeUso();
				assert(0);
			}
		}
	}
	assert(NULL != input_file);
	assert(NULL != output_file);
	if (NULL == input_file || NULL == output_file)return EXIT_SUCCESS;

	/* abrir archivo de entrada */
	fd = fopen(input_file, "r");
	if (tipo_lpila == FALSE)ap = apila_crear(100);
	else lp = lpila_crear();
	if (NULL == lp && NULL == ap) {
		printf("error al crear la pila \n ");
		assert(0);
		return EXIT_SUCCESS;
	}
	if (fd != NULL) {
		/*leer cabecera del archivo*/
		char str[100];
		char str1[500];
		int cont = 1;
		char strTimeStep[100];
		fscanf(fd, "%s%s%s%d", str, str, str, &sampleRate);
		printf("; sample Rate %d \n", sampleRate);
		/*leer comentarios dejados por el programa de conversion*/
		fgets(str1, 500, fd);
		/*ignorar comentarios
		printf("fgets:%s\n",str1);*/
		while (!feof(fd) && cont == 1) {
			char c = fgetc(fd);
			if (c == ';') {
				fgets(str1, 500, fd);
			}
			else { cont = 0; }

		}


		while (!feof(fd)) {
			/*usamos malloc para reservar esta memoria y no perder el dato como en una variable local
			notese que si se usa una variable local el dato se perderia al salir del bloque while*/
			char* strData = (char*)malloc(sizeof(char) * 100);/*tamanho 100, para evitar complejidad al proyecto*/
			fscanf(fd, "%s%s", strTimeStep, strData);
			if (feof(fd)) continue;
			if (strlen(strData) > 0) {
				if (tipo_lpila == FALSE) {
					if (ERROR == apila_push(ap, strData)) {
						printf("error al cargar la pila");
						assert(0);
					}
				}
				else {
					if (ERROR == lpila_push(lp, strData)) {
						printf("error al cargar la pila");
						assert(0);
					}
				}
			}
			count++;
		}
	}
	fclose(fd);
	printf("%d samples in file\n", count);

	{
		FILE* fd2 = fopen(output_file, "w");
		if (NULL != fd2) {
			int numSteps = 0;
			char* strData; /*aqui el dato va a ser referenciado a esta direccion (puntero a char) */
			fprintf(fd2, "; Sample Rate %d\n", sampleRate);
			if (tipo_lpila == FALSE) {
				while (!apila_isEmpty(ap)) {
					if (ERROR == apila_pop(ap, (void**)&strData)) {
						printf("error al sacar de la pila");
						assert(0);
					}
					else {
						fprintf(fd2, "%f\t%s\n", (double)numSteps / sampleRate, strData);
						numSteps++;
						free(strData); /* liberamos ese malloc hecho dentro del while*/
					}
				}
			}
			else {
				while (!lpila_isEmpty(lp)) {
					if (ERROR == lpila_pop(lp, (void**)&strData)) {
						printf("error al sacar de la pila");
						assert(0);
					}
					else {
						fprintf(fd2, "%f\t%s\n", (double)numSteps / sampleRate, strData);
						numSteps++;
						free(strData); /* liberamos ese malloc hecho dentro del while*/
					}
				}
			}

			fclose(fd2);
		}
		if (tipo_lpila == FALSE) {
			if (apila_destruir(ap) == ERROR) {
				printf("error al sacar de la pila");
				assert(0);
			}
		}
		else {
			if (lpila_destruir(lp) == ERROR) {
				printf("error al sacar de la pila");
				assert(0);
			}
		}
	}

	return (EXIT_SUCCESS);
}


