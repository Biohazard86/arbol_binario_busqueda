		//===========================================
		//			 David Barrios Portales
		//			 davidbarrios@usal.es
		//			 Practica arbolbinario
		//           Estructuras de datos
		//===========================================

// ------------------------------------------------------------------------------------------------------
// Librerias usadas
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// Struct de pintura
struct PINTURA
{
	int clave;							// Campo de tipo entero para la clave
	int n_inve;							// Campo de tipo entero para n_invee
	char color[15];							// Campo de tipo char para el color
};typedef struct PINTURA pintura;


// Struct de NODO
struct NODO
{
	pintura clave;
	struct NODO *hijo_izq;
	struct NODO *hijo_der;
	struct NODO *padre;
};typedef struct NODO nodo;

//Struct de NODO_COLA
struct NODO_COLA
{
	int dato;
	struct NODO_COLA *enlace;
	nodo *aux;
};typedef struct NODO_COLA nodo_cola;


// ------------------------------------------------------------------------------------------------------
void presentacion (){
    // Funcion para presentar el programa.
    printf("\n\n\t-----------------------------------------------");
    printf("\n\t              Arbol binario");
    printf("\n\t  David Barrios Portales davidbarrios@usal.es");
	printf("\n\t-----------------------------------------------\n\n");

}
// ------------------------------------------------------------------------------------------------------

//funcion para insertar el hijo
int insertar_hijo(nodo **raiz, nodo *padre, pintura clave, int derecha)
{
	
	// Vamos a crear un puntero aux
	nodo *puntero_aux;
	//comprueba que la posicion no este ocupada
	if (((padre != NULL) && (derecha == 1) && (padre->hijo_der != NULL))
		|| ((padre != NULL) && (padre->hijo_izq != NULL) && (derecha == 0))
		|| ((padre == NULL) && (*raiz != NULL)))
	{
		printf("ya existe un nodo en la posicion indicada\n");
		return 0;
	}
	//se reserva memoria
	puntero_aux = (nodo *)calloc(1, sizeof(nodo));
	
	if(puntero_aux == NULL)
	{
		return 0;
	}

	//igualamos
	puntero_aux->hijo_izq = NULL;
	puntero_aux->hijo_der = NULL;
	puntero_aux->clave = clave;

	//comprobamos el padre
	if(padre == NULL)
	{
		//se inseerta en la raiz
		*raiz = puntero_aux;
		puntero_aux->padre = NULL;
	}
	else
	{
		//se inserta en la posicion correspondiente
		if(derecha == 1)
		{
			padre->hijo_der = puntero_aux;
		}
		else
		{
			padre->hijo_izq = puntero_aux;
		}
		puntero_aux->padre = padre;
	}
	return 1;
}

// ------------------------------------------------------------------------------------------------------

//Esta funcion realiza el trabajo de insertar
int insertar(nodo **arbol, pintura clave)
{
	
	// Vamos a tener 2 punteros y los inicializamos
	nodo *p,*q;
	int e_encontrados=0;
	q=NULL;
	p=*arbol;
	// Comenzamos a buscar la clave en el arbol.
	while((p!=NULL) && (e_encontrados == 0))
	{ 
		q=p;
		if(clave.clave==p->clave.clave)
		{
			e_encontrados = 1;
		}
		else
		{
			//se busca la posicion de insertado
			if(clave.clave<p->clave.clave)
			{
				p=p->hijo_izq;
			}
			else
			{
				p=p->hijo_der;
			}
		}
	}
	//insercion, si la busqueda no tuvo exito
	if(e_encontrados==0)
	{
		
		if(q==NULL)
		{
			return insertar_hijo(arbol,q,clave,0);
		}
		else
		{
			//se inserta un hijo izquierdo
			if(clave.clave<q->clave.clave)
			{
			 return insertar_hijo(arbol,q,clave,0);
			}
			//se inserta un hijo derecho
			else
			{
			 return insertar_hijo(arbol,q,clave,1);
			}
		}
	}

	return 0;
}

// ------------------------------------------------------------------------------------------------------

void recorridoOrden(nodo *raiz){
	
	if(raiz!=NULL)
    {
        recorridoOrden(raiz->hijo_izq);
        printf("%d ",raiz->clave.clave);
        recorridoOrden(raiz->hijo_der);
    }
}
void eliminarArbol(nodo **raiz)
{
	if(*raiz!=NULL)
	{
		eliminarArbol(&(**raiz).hijo_izq);
		eliminarArbol(&(**raiz).hijo_der);
		free(*raiz);
		*raiz=NULL;
	}
}



// ------------------------------------------------------------------------------------------------------
//Realiza una busquead de forma no recursiva

nodo *buscar_no_recursivo(nodo *arbol, int x)
{
	
	//puntero
	nodo *p;
	int e_encontrados;

	//inicializamos
	p = arbol;
	e_encontrados = 0;

	//se recorre el arbol
	while((p!=NULL)&&(e_encontrados == 0))
	{
		//se comprueba si la posicion actual es la buscada
		if(p->clave.clave == x)
		{
			e_encontrados = 1;
		}
		else
		{
			//se comprueba por que subarbol avanzar
			if(x<p->clave.clave)
			{
				p=p->hijo_izq;
			}
			else
			{
				p = p->hijo_der;
			}
		}
	}
	return p;
}



// ------------------------------------------------------------------------------------------------------

int main()
{
	int i;
	// Presentacion con mi nombre y correo electronico.
	presentacion();

	// Comienza el programa:
	nodo *arbol;
	arbol = NULL;

	//Datos: 
	pintura datos;
	datos.clave = 550;
	datos.n_inve = 27;
	strcpy(datos.color,"Negro") ;

	insertar(&arbol,datos);
	datos.clave = 200;
	datos.n_inve = 27;
	insertar(&arbol,datos);
	datos.clave = 449;
	datos.n_inve = 105;
	insertar(&arbol,datos);
	datos.clave = 550;
	datos.n_inve = 92;
	insertar(&arbol,datos);
	datos.clave = 303;
	datos.n_inve = 50;
	insertar(&arbol,datos);
	datos.clave = 304;
	datos.n_inve = 50;
	insertar(&arbol,datos);
	datos.clave = 526;
	datos.n_inve = 76;
	insertar(&arbol,datos);
	datos.clave = 780;
	datos.n_inve = 88;
	insertar(&arbol,datos);
	datos.clave = 480;
	datos.n_inve = 90;
	insertar(&arbol,datos);
	datos.clave = 704;
	datos.n_inve = 26;
	insertar(&arbol,datos);
	datos.clave = 480;
	datos.n_inve = 115;
	insertar(&arbol,datos);
	datos.clave = 230;
	datos.n_inve = 98;
	insertar(&arbol,datos);
	datos.clave = 509;
	datos.n_inve = 43;
	insertar(&arbol,datos);
	datos.clave = 645;
	datos.n_inve = 78;
	insertar(&arbol,datos);
	nodo * b1 = buscar_no_recursivo(arbol,304);
	if(b1){
		printf("-> Pintura: %d %d %s",b1->clave.clave,b1->clave.n_inve, b1->clave.color);
		printf("\n");
	}
	
	nodo * b2 = buscar_no_recursivo(arbol,666);
	if(b2){
		printf("-> Pintura: %d %d %s",b1->clave.clave,b1->clave.n_inve, b1->clave.color);
		printf("\n");
	}else{
		printf("NO EXISTE.\n");
	}
	
	
	recorridoOrden(arbol);
	eliminarArbol(&arbol);
	printf("\n");
	return 0;
}

// ------------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------------