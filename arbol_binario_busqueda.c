		//=============================================================
		//		 David Barrios
		//		 davidbarrios@usal.es
		//		 Practica arbolbinario (GRUPO 2)
		//               Estructuras de datos
		//   gcc -o arbol_binario_busqueda arbol_binario_busqueda.c
		//=============================================================

// ------------------------------------------------------------------------------------------------------
// Librerias usadas
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// Struct de los leotardos
struct LEOTARDO
{
	int clave_color;					// Campo de tipo entero para la clave del color del producto
	int n_inve;							// Campo de tipo entero para numero de elementos en el inventario
	char color[15];						// Campo de tipo char para el color (Elijo un tamanio de 15 ya que no hay ningun color que lo supere)
};typedef struct LEOTARDO leotardo;


// Struct de NODO
struct NODO
{
	leotardo clave_color;
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
    printf("\n\t            Arbol binario (G2)");
    printf("\n\t  David Barrios Portales davidbarrios@usal.es");
	printf("\n\t-----------------------------------------------\n\n");

}
// ------------------------------------------------------------------------------------------------------

//funcion para insertar el hijo
int insertar_hijo(nodo **raiz, nodo *padre, leotardo clave_color, int derecha)
{
	
	// Vamos a crear un puntero aux
	nodo *puntero_aux;
	// Comprobamos que la posicion no este ocupada
	if (((padre != NULL) && (derecha == 1) && (padre->hijo_der != NULL))
		|| ((padre != NULL) && (padre->hijo_izq != NULL) && (derecha == 0))
		|| ((padre == NULL) && (*raiz != NULL)))
	{
		printf("\nERROR.\n Ya hay un nodo en la posicion indicada\n");
		return 5;		// Retornamos un 5 si esto ocurre
	}
	// Procedemos a reservar memoria
	puntero_aux = (nodo *)calloc(1, sizeof(nodo));
	
	// Si el puntero auxiliar apunta a una direccion nula entonces 
	if(puntero_aux == NULL)
	{
		return 1;			//Retornamos un 1
	}

	//Igualamos a null 
	puntero_aux->hijo_izq = NULL;
	puntero_aux->hijo_der = NULL;
	puntero_aux->clave_color = clave_color;

	//Vamos a compraobar el padre
	if(padre == NULL)
	{
		// Insertamos en la raiz
		*raiz = puntero_aux;
		puntero_aux->padre = NULL;
	}
	else	// Si el padre no es nulo
	{
		// Insertamos en la posicion correspondiente
		if(derecha == 1)	// Derecha
		{
			padre->hijo_der = puntero_aux;
		}
		else	// Si no en la izquierda
		{
			padre->hijo_izq = puntero_aux;
		}
		puntero_aux->padre = padre;
	}
	return 1;		// Devolvemos un 1
}

// ------------------------------------------------------------------------------------------------------

//Esta funcion realiza el trabajo de insertar en el arbol la clave.
int insertar(nodo **arbol, leotardo clave_color)
{
	
	// Vamos a tener 2 punteros y los inicializamos
	nodo *p,*q;
	int e_encontrados=0;
	q=NULL;
	p=*arbol;
	// Comenzamos a buscar la clave_color en el arbol.
	while((p!=NULL) && (e_encontrados == 0))
	{ 
		q=p;
		if(clave_color.clave_color==p->clave_color.clave_color)
		{
			e_encontrados = 1;
		}
		else
		{
			//Buscamos en la posicion de insertado
			if(clave_color.clave_color<p->clave_color.clave_color)
			{
				p=p->hijo_izq;
			}
			else	// Si no
			{
				p=p->hijo_der;
			}
		}
	}
	//insercion, si la busqueda no tuvo exito
	if(e_encontrados==0)		// Si el numero de elementos encontrados es 0
	{
		
		if(q==NULL)			// Si q es nulo
		{
			return insertar_hijo(arbol,q,clave_color,0);	// insertamos
		}
		else				// Si no
		{
			// Insertamos un hijo en la izq
			if(clave_color.clave_color<q->clave_color.clave_color)
			{
			 return insertar_hijo(arbol,q,clave_color,0);
			}
			// Insetamos un hijo en la drcha
			else
			{
			 return insertar_hijo(arbol,q,clave_color,1);
			}
		}
	}

	return 0;		// Retornamos 0
}

// ------------------------------------------------------------------------------------------------------
// Recorrido en orden
void recorrido_en_orden(nodo *raiz){
	
	if(raiz!=NULL)
    {
        recorrido_en_orden(raiz->hijo_izq);
        printf("%d\t|\t%d\t|\t%s \n",raiz->clave_color.clave_color, raiz->clave_color.n_inve, raiz->clave_color.color);
				//printf("\tLeotardo (Codigo color %d) -->  %d | %d | %s \n", b1->clave_color.clave_color, b1->clave_color.clave_color,b1->clave_color.n_inve, b1->clave_color.color);

        recorrido_en_orden(raiz->hijo_der);
    }
}

// ------------------------------------------------------------------------------------------------------
// Eliminamos el arbol
void eliminar_arbol(nodo **raiz)
{
	if(*raiz!=NULL)
	{
		eliminar_arbol(&(**raiz).hijo_izq);
		eliminar_arbol(&(**raiz).hijo_der);
		free(*raiz);
		*raiz=NULL;
	}
}



// ------------------------------------------------------------------------------------------------------
//Realiza una busquead de forma no recursiva

nodo *busca_forma_no_recursiva(nodo *arbol, int x)
{
	
	//puntero
	nodo *p;
	int e_encontrados;		// Numero de elementos encontrados

	//inicializamos
	p = arbol;
	e_encontrados = 0;

	// Recorremos el arbol
	while((p!=NULL)&&(e_encontrados == 0))
	{
		//se comprueba si la posicion actual es la buscada
		if(p->clave_color.clave_color == x)
		{
			e_encontrados = 1;
		}
		else
		{
			//se comprueba por que subarbol avanzar
			if(x<p->clave_color.clave_color)
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
// FUNCION MAIN
int main()
{
	int i;

	// Presentacion con mi nombre y correo electronico.
	presentacion();

	// Comienza el programa:
	nodo *arbol;
	arbol = NULL;

	//Vamos a introducir los datos en >> 
	leotardo datos;

	
	// CARGAMOS LOS DATOS:
	// COLOR ROJO -----------------------------
	datos.clave_color = 550;			// Clave del color del producto
	datos.n_inve = 27;					// Numero de productos en el inventario
	strcpy(datos.color,"ROJO") ;		// Color del producto
	insertar(&arbol,datos);				// Insertamos los datos

	// COLOR BLANCO -----------------------------
	datos.clave_color = 200;
	datos.n_inve = 27;
	strcpy(datos.color,"BLANCO") ;
	insertar(&arbol,datos);

	// COLOR AZUL FRANCIA -----------------------------
	datos.clave_color = 449;
	datos.n_inve = 105;
	strcpy(datos.color,"AZUL FRANCIA") ;
	insertar(&arbol,datos);

	// COLOR NEGRO -----------------------------
	datos.clave_color = 900;
	datos.n_inve = 92;
	strcpy(datos.color,"NEGRO") ;
	insertar(&arbol,datos);

	// COLOR CAVA -----------------------------
	datos.clave_color = 303;
	datos.n_inve = 50;
	strcpy(datos.color,"CAVA") ;
	insertar(&arbol,datos);

	// COLOR LINO -----------------------------
	datos.clave_color = 304;
	datos.n_inve = 50;
	strcpy(datos.color,"LINO") ;
	insertar(&arbol,datos);

	// COLOR ROSA PALO -----------------------------
	datos.clave_color = 526;
	datos.n_inve = 76;
	strcpy(datos.color,"ROSA PALO") ;
	insertar(&arbol,datos);

	// COLOR VERDE SECO -----------------------------
	datos.clave_color = 780;
	datos.n_inve = 88;
	strcpy(datos.color,"VERDE SECO") ;
	insertar(&arbol,datos);

	// COLOR AZUL MARINO -----------------------------
	datos.clave_color = 480;
	datos.n_inve = 90;
	strcpy(datos.color,"AZUL MARINO") ;
	insertar(&arbol,datos);

	// COLOR JADE -----------------------------
	datos.clave_color = 704;
	datos.n_inve = 26;
	strcpy(datos.color,"JADE") ;
	insertar(&arbol,datos);

	// COLOR GRANATE -----------------------------
	datos.clave_color = 575;
	datos.n_inve = 115;
	strcpy(datos.color,"GRANATE") ;
	insertar(&arbol,datos);

	// COLOR GRIS CLARO -----------------------------
	datos.clave_color = 230;
	datos.n_inve = 98;
	strcpy(datos.color,"GRIS CLARO") ;
	insertar(&arbol,datos);

	// COLOR BUGAMBILLA -----------------------------
	datos.clave_color = 590;
	datos.n_inve = 43;
	strcpy(datos.color,"BUGAMBILLA") ;
	insertar(&arbol,datos);

	// COLOR CURRY -----------------------------
	datos.clave_color = 645;
	datos.n_inve = 78;
	strcpy(datos.color,"CURRY") ;
	insertar(&arbol,datos);
	
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


	// Vamos a buscar dos leotardos que nos pide el enunciado (304 y 666):

	// El primero es buscar por campo color, con numero 304
	printf("\nBusqueda de clave_color 304 >> \n");
	nodo * b1 = busca_forma_no_recursiva(arbol,304);		// Realizamos la busqueda
	// Si tiene exito
	if(b1){
		// Si lo encontramos, mostramos los datos
		printf("\tLeotardo (Codigo color %d) -->  %d | %d | %s \n", b1->clave_color.clave_color, b1->clave_color.clave_color,b1->clave_color.n_inve, b1->clave_color.color);
	}else{
		// En el casod e que no, mostramos un mensaje de error.
		printf("\tNO EXISTE ESE ELEMENTO.\n");
	}
	
	// El segundo es buscar por campo de color con numero 666
	printf("\nBusqueda de clave_color 666 >> \n");
	nodo * b2 = busca_forma_no_recursiva(arbol,666);
	if(b2){
		// Si lo encontramos, mostramos los datos
		printf("\tLeotardo (Codigo color %d) -->  %d | %d | %s \n", b1->clave_color.clave_color, b1->clave_color.clave_color,b1->clave_color.n_inve, b1->clave_color.color);
	}else{
		printf("\tNO EXISTE ESE ELEMENTO.\n");
	}
	
	// Realizamos un recorrido del arbol, mostrando los campos de cada nodo
	printf("\n\n<< Realizamos el recorrido en orden >> \n");
	recorrido_en_orden(arbol);			// Llamamos a la funcion que recorre el arbol en orden y le pasamos el arbol como parametro

	// Eliminamos el arbol como se pide en el enunciado
	printf("\nProcedesmos a eliminar el arbol\n");
	eliminar_arbol(&arbol);			// Llamamos a la funcion que elimina el arbol y le pasamos el arbol por referencia

	// Fin del programa
	printf("\nFIN\n");
	printf("\n");
	return 0;
}

// ------------------------------------------------------------------------------------------------------
// ---------------------------------------  FIN  --------------------------------------------------------
// ------------------------------------------------------------------------------------------------------
