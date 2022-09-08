#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "heap.h"
#include "testing.h"
#define TAM_VOLUMEN 100

int comparador_aux (const void* valor1, const void* valor2) {
	return *(int*)valor1 - *(int*)valor2;
}

void pruebas_heap_inicial() {
	printf("\n ### PRUEBAS INICIALES EN HEAP ###\n");
	heap_t* heap = heap_crear(comparador_aux);
	print_test("El heap se creo con exito", heap);
	print_test("La cantidad inicial del heap es 0", !heap_cantidad(heap));
	print_test("Desencolar del heap inicial es invalido", !heap_desencolar(heap));
	print_test("El heap inicialmente esta vacio", heap_esta_vacio(heap));
	print_test("Ver el maximo del heap inicial es invalido", !heap_ver_max(heap));
	heap_destruir(heap, NULL);
}

void pruebas_heap_encolar_y_desencolar() {
	int valor12 = 12;
	int valor5  = 5;
	int valor18 = 18;
	printf("\n ### PRUEBAS ENCOLAR Y DESENCOLAR EN HEAP ###\n");
	heap_t* heap = heap_crear(comparador_aux);
	print_test("El heap se creo con exito", heap);
	print_test("El heap esta vacio", heap_esta_vacio(heap));
	print_test("Encolo el valor 12", heap_encolar(heap, &valor12));
	print_test("La cantidad del heap es 1", heap_cantidad(heap) == 1);
	print_test("El maximo del heap ahora es 12", heap_ver_max(heap) == &valor12);
	print_test("Encolo el valor 5", heap_encolar(heap, &valor5));
	print_test("La cantidad del heap es 2", heap_cantidad(heap) == 2);
	print_test("El maximo del heap sigue siendo 12", heap_ver_max(heap) == &valor12);
	print_test("Encolo el valor 18", heap_encolar(heap, &valor18));
	print_test("La cantidad del heap es 3", heap_cantidad(heap) == 3);
	print_test("El maximo del heap ahora es 18", heap_ver_max(heap) == &valor18);
	print_test("Desencolo tiene que ser el valor 18", heap_desencolar(heap) == &valor18);
	print_test("El maximo del heap ahora es 12", heap_ver_max(heap) == &valor12);
	print_test("La cantidad del heap es 2", heap_cantidad(heap) == 2);
	print_test("Desencolo tiene que ser el valor 12", heap_desencolar(heap) == &valor12);
	print_test("El maximo del heap ahora es 5", heap_ver_max(heap) == &valor5);
	print_test("La cantidad del heap es 1", heap_cantidad(heap) == 1);
	print_test("Desencolo tiene que ser el valor 5", heap_desencolar(heap) == &valor5);
	print_test("El heap esta vacio", heap_esta_vacio(heap));
	heap_destruir(heap, NULL);	
}

void pruebas_heap_con_free() {
	printf("\n ### PRUEBAS DEL HEAP CON DATOS DINAMICOS ###\n");
	heap_t* heap = heap_crear(comparador_aux);
	int* valor3 = malloc(sizeof(int));
	if (!valor3) return;
	int* valor7 = malloc(sizeof(int));
	if(!valor7) {
		free(valor3);
		return;
	}
	*valor3 = 3;
	*valor7 = 7;
	print_test("El heap se creo con exito", heap);
	print_test("El heap inicialmente esta vacio", heap_esta_vacio(heap));
	print_test("Encolo el valor 3", heap_encolar(heap, valor3));
	print_test("La cantidad del heap es 1", heap_cantidad(heap) == 1);
	print_test("El maximo del heap ahora es 3", heap_ver_max(heap) == valor3);
	print_test("Encolo el valor 7", heap_encolar(heap, valor7));
	print_test("La cantidad del heap es 2", heap_cantidad(heap) == 2);
	print_test("El maximo del heap ahora es 7", heap_ver_max(heap) == valor7);
	print_test("Desencolo el 7 y libero el dato", heap_desencolar(heap) == valor7);
	free(valor7);
	heap_destruir(heap, free);	
}

void pruebas_heap_con_arreglo() {
	printf("\n ### PRUEBAS HEAP CON ARREGLO PREVIO ###\n");
	size_t largo_arr = 5;
	int valor3 = 3;
	int valor4 = 4;
	int valor6 = 6;
	int valor7 = 7;
	int valor9 = 9;
	void* arr[] = {&valor3, &valor9, &valor7, &valor6, &valor4};
	heap_t* heap = heap_crear_arr(arr, largo_arr, comparador_aux);
	print_test("El heap se creo con exito", heap);
	print_test("El heap inicialmente no esta vacio", !heap_esta_vacio(heap));
	print_test("La cantidad del heap es 5", heap_cantidad(heap) == largo_arr);
	print_test("El maximo del heap es 9", heap_ver_max(heap) == &valor9);
	heap_destruir(heap, NULL);	
}

void pruebas_heapsort() {
	printf("\n ### PRUEBAS HEAPSORT ###\n");
	size_t largo_arr = 5;
	int valor1 = 1;
	int valor2 = 2;
	int valor3 = 3;
	int valor4 = 4;
	int valor5 = 5;
	void* arr[] = {&valor4, &valor3, &valor5, &valor2, &valor1};
	printf(" ~ Arreglo sin ordenar ~\n");
	for(int i = 0; i < (int)largo_arr; i ++) {
		printf(" %d ·", *(int*)arr[i]);
	}
	heap_sort(arr, largo_arr, comparador_aux);
	int errores = 0;
	printf("\n ~ Arreglo tras aplicar heapsort ~\n");
	for(int j = 0; j < (int)largo_arr; j++) {
		if(j+1 != *(int*)arr[j]) errores += 1;
		printf(" %d ·", *(int*)arr[j]);
	}
	printf("\n");
	print_test("El arreglo esta ordenado", !errores);
}

void pruebas_heap_volumen() {
	printf("\n ### PRUEBAS DE VOLUMEN EN HEAP ###\n");
	
	heap_t* heap = heap_crear(comparador_aux);
	print_test("El heap se creo con exito", heap);
	int* vector = malloc(TAM_VOLUMEN * sizeof(int));
    bool encolar_volumen = true;
    bool desencolar_volumen = true;

    for (int i = 0; i < TAM_VOLUMEN && encolar_volumen; i++) {
        vector[i] = i+1;
        encolar_volumen = heap_encolar(heap, &vector[i]);
    }
    print_test("Encolar varios elementos", encolar_volumen);
    print_test("El maximo del heap es el TAM_VOLUMEN", heap_ver_max(heap) == &vector[TAM_VOLUMEN - 1]);
    print_test("El heap no esta vacio", !heap_esta_vacio(heap));
    for (int i = TAM_VOLUMEN - 1; i >= 0; i--) {
        int* desencolado = heap_desencolar(heap);
        if (desencolado != &vector[i]) desencolar_volumen = false;
    }
    print_test("Todos los elementos fueron desencolados correctamente", desencolar_volumen);
    print_test("El heap esta vacio", heap_esta_vacio(heap));

    heap_destruir(heap, NULL);
    print_test("Heap destruido", true);
    free(vector);
}

int comparador_maximos (const void* heap1, const void* heap2) {
	int maximo_heap1 = *(int*)heap_ver_max((heap_t*)heap1);
	int maximo_heap2 = *(int*)heap_ver_max((heap_t*)heap2);
	return maximo_heap1 - maximo_heap2;
}

void destruir_heap_aux(void* heap) {
	heap_destruir(heap, NULL);
}

void pruebas_heap_con_heaps() {
	printf("\n ### PRUEBAS DE HEAP CON HEAPS Y COMPARACION DE MAXIMOS ###\n");
	heap_t* heap = heap_crear(comparador_maximos);
	print_test("El heap se creo con exito", heap);
	print_test("El heap esta vacio", heap_esta_vacio(heap)); 
	heap_t* heap_aux1 = heap_crear(comparador_aux);
	heap_t* heap_aux2 = heap_crear(comparador_aux);
	print_test("Los heaps auxiliares se crearon con exito", heap_aux1 && heap_aux2);
	print_test("Ambos estan vacios", heap_esta_vacio(heap_aux1) && heap_esta_vacio(heap_aux2));
	int valor4  = 4;
	int valor14 = 14;

	print_test("Encolo el valor 4 a un heap", heap_encolar(heap_aux1, &valor4));
	print_test("Encolo el valor 14 a otro heap", heap_encolar(heap_aux2, &valor14));
	
	print_test("Encolo el heap con 4 como maximo al heap principal", heap_encolar(heap, heap_aux1));
	print_test("La cantidad del heap es 1", heap_cantidad(heap) == 1);
	print_test("El maximo del heap es el heap con maximo 4", heap_ver_max(heap) == heap_aux1);
	print_test("Encolo el heap con 14 como maximo al heap principal", heap_encolar(heap, heap_aux2));	
	print_test("La cantidad del heap es 2", heap_cantidad(heap) == 2);
	print_test("El maximo del heap es el heap con maximo 14", heap_ver_max(heap) == heap_aux2);

	heap_destruir(heap, destruir_heap_aux);
}

void pruebas_heap_alumno() {
	pruebas_heap_inicial();
	pruebas_heap_encolar_y_desencolar();
	pruebas_heap_con_free();
	pruebas_heap_con_arreglo();
	pruebas_heapsort();
	pruebas_heap_volumen();
	pruebas_heap_con_heaps();
}