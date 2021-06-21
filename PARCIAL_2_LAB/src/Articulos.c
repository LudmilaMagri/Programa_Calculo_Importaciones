/*
 * Articulos.c
 *
 *  Created on: 15 jun. 2021
 *      Author: ludmi
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Articulos.h"
#include "utn.h"
#include "Dictionary.h"
#include "PosArancelaria.h"
#include "Controller.h"
#define COD_LEN 200
#define DESC_LEN 100
#define PAIS_LEN 100
#define NOM_LEN 100
//#include "LinkedList.h"

Articulos* art_new(void)
{
	return (Articulos*) malloc(sizeof(Articulos));
}

Articulos* art_newParam(char* codigo,char* descripcion,char* paisFabricacion, char* nombre, float valorFob, float peso, float ancho,
						float alto, float profundidad, int idArticulo, int idPosicionArancelaria)
{
	Articulos* auxArt = art_new();
	if(auxArt != NULL)
	{
		if  ( 	art_setCodigo(auxArt, codigo) < 0 ||
				art_setDescripcion(auxArt, descripcion) < 0 ||
				art_setPaisFabricacion(auxArt, paisFabricacion) < 0 ||
				art_setNombre(auxArt, nombre) < 0 ||
				art_setValorFob(auxArt, valorFob) <0 ||
				art_setPeso(auxArt, peso) <0 ||
				art_setAncho(auxArt, ancho) <0 ||
				art_setAlto(auxArt, alto) <0 ||
				art_setProfundidad(auxArt, profundidad) <0 ||
				art_setIdArticulo(auxArt, idArticulo) <0 ||
				art_setIdPosicionArancelaria(auxArt, idPosicionArancelaria) <0 )
		{
			art_delete(auxArt);
			auxArt = NULL;
		}
	}
	return auxArt;;
}

int art_delete(Articulos* this)
{
	int retorno = -1;
	if(this != NULL)
	{
		free(this);
		retorno = 0;
	}
	return retorno;
}

int art_setCodigo(Articulos* this,char* codigo)
{
	int retorno = -1;
	if(this != NULL && codigo != NULL && isValidCodigo(codigo) )
	{
		strcpy(this->codigo,codigo);
		retorno = 0;
	}
	return retorno;
}
char* art_getCodigo(Articulos* this,int* flagError)
{
	*flagError = -1;
	char* auxCodigo= NULL;
	if(this != NULL && flagError != NULL )
	{
		auxCodigo = this->codigo;
		*flagError = 0;
	}
	return auxCodigo;
}
int isValidCodigo(char* codigo)
{
	return 1;
}
int art_setDescripcion(Articulos* this,char* descripcion)
{
	int retorno = -1;
	if(this != NULL && descripcion != NULL && isValidDescripcion(descripcion) )
	{
		strcpy(this->descripcion,descripcion);
		retorno = 0;
	}
	return retorno;
}
char* art_getDescripcion(Articulos* this,int* flagError)
{
	*flagError = -1;
	char* auxDescripcion= NULL;
	if(this != NULL && flagError != NULL )
	{
		auxDescripcion = this->descripcion;
		*flagError = 0;
	}
	return auxDescripcion;
}
int isValidDescripcion(char* descripcion)
{
	return 1;
}
int art_setPaisFabricacion(Articulos* this,char* paisFabricacion)
{
	int retorno = -1;
	if(this != NULL && paisFabricacion != NULL && isValidPaisFabricacion(paisFabricacion) )
	{
		strcpy(this->paisFabricacion,paisFabricacion);
		retorno = 0;
	}
	return retorno;
}

char* art_getPaisFabricacion(Articulos* this,int* flagError)
{
	*flagError = -1;
	char* auxPaisFab= NULL;
	if(this != NULL && flagError != NULL )
	{
		auxPaisFab = this->paisFabricacion;
		*flagError = 0;
	}
	return auxPaisFab;
}
int isValidPaisFabricacion(char* paisFabricacion)
{
	return 1;
}
int art_setNombre(Articulos* this, char* nombre)
{
	int retorno = -1;
	if(this != NULL && nombre != NULL && isValidNombre(nombre) )
	{
		strcpy(this->nombre,nombre);
		retorno = 0;
	}
	return retorno;
}

char* art_getNombre(Articulos* this,int* flagError)
{
	*flagError = -1;
	char* auxNombre= NULL;
	if(this != NULL && flagError != NULL )
	{
		auxNombre = this->nombre;
		*flagError = 0;
	}
	return auxNombre;
}
int isValidNombre(char* nombre)
{
	return 1;
}

int art_setValorFob(Articulos* this, float valorFob)
{
	int retorno = -1;
	if(this != NULL && isValidValorFob(valorFob) )
	{
		this->valorFob = valorFob;
		retorno = 0;
	}
	return retorno;
}

float art_getValorFob(Articulos* this,int* flagError)
{
	*flagError = -1;
	int auxValorFob = -1;
	if(this != NULL && flagError != NULL )
	{
		auxValorFob=this->valorFob;
		*flagError = 0;
	}
	return auxValorFob;
}
int isValidValorFob(float valorFob)
{
	return 1;
}
int art_setPeso(Articulos* this, float peso)
{
	int retorno = -1;
	if(this != NULL && isValidPeso(peso) )
	{
		this->peso = peso;
		retorno = 0;
	}
	return retorno;
}
float art_getPeso(Articulos* this,int* flagError)
{
	*flagError = -1;
	int auxPeso = -1;
	if(this != NULL && flagError != NULL )
	{
		auxPeso=this->peso;
		*flagError = 0;
	}
	return auxPeso;
}
int isValidPeso(float peso)
{
	return 1;
}
int art_setAncho(Articulos* this, float ancho)
{
	int retorno = -1;
	if(this != NULL && isValidAncho(ancho) )
	{
		this->ancho = ancho;
		retorno = 0;
	}
	return retorno;
}
float art_getAncho(Articulos* this,int* flagError)
{
	*flagError = -1;
	int auxAncho = -1;
	if(this != NULL && flagError != NULL )
	{
		auxAncho=this->ancho;
		*flagError = 0;
	}
	return auxAncho;
}
int isValidAncho(float ancho)
{
	return 1;
}
int art_setAlto(Articulos* this, float alto)
{
	int retorno = -1;
	if(this != NULL && isValidAlto(alto) )
	{
		this->alto = alto;
		retorno = 0;
	}
	return retorno;
}
float art_getAlto(Articulos* this,int* flagError)
{
	*flagError = -1;
	int auxAlto = -1;
	if(this != NULL && flagError != NULL )
	{
		auxAlto=this->alto;
		*flagError = 0;
	}
	return auxAlto;
}
int isValidAlto(float alto)
{
	return 1;
}
int art_setProfundidad(Articulos* this, float profundidad)
{
	int retorno = -1;
	if(this != NULL && isValidProfundidad(profundidad) )
	{
		this->profundidad = profundidad;
		retorno = 0;
	}
	return retorno;
}
float art_getProfundidad(Articulos* this,int* flagError)
{
	*flagError = -1;
	int auxProfundidad = -1;
	if(this != NULL && flagError != NULL )
	{
		auxProfundidad=this->profundidad;
		*flagError = 0;
	}
	return auxProfundidad;
}
int isValidProfundidad(float profundidad)
{
	return 1;
}
int art_setIdArticulo(Articulos* this,int idArticulo)
{
	int retorno = -1;
	if(this != NULL && isValidIdArticulo(idArticulo) )
	{
		this->idArticulo = idArticulo;
		retorno = 0;
	}
	return retorno;
}
int art_getIdArticulo(Articulos* this,int* flagError)
{
	*flagError = -1;
	int auxId = -1;
	if(this != NULL && flagError != NULL )
	{
		auxId=this->idArticulo;
		*flagError = 0;
	}
	return auxId;
}
int isValidIdArticulo(int idArticulo)
{
	return 1;
}
int art_setIdPosicionArancelaria(Articulos* this,int idPosicionArancelaria)
{
	int retorno = -1;
	if(this != NULL && isValidIdPosicionArancelaria(idPosicionArancelaria) )
	{
		this->idPosicionArancelaria = idPosicionArancelaria;
		retorno = 0;
	}
	return retorno;
}
int art_getIdPosicionArancelaria(Articulos* this,int* flagError)
{
	*flagError = -1;
	int auxId = -1;
	if(this != NULL && flagError != NULL )
	{
		auxId=this->idPosicionArancelaria;
		*flagError = 0;
	}
	return auxId;
}
int isValidIdPosicionArancelaria(int idPosicionArancelaria)
{
	return 1;
}


static int contador = 0;
void art_valorInicialId(int id)
{
	 contador= id;
}
int art_generarId(void)
{
	//mantiene su valor. no se comporta como localç
	contador++;
	return contador;
}



/*

Transporte t:;

for (...)
{
	pA = ll_get(listaArt);
	pPosicion = dict_get (dicPosiciones, pA->idPosicion);

	calcularCostoMaritimo(pArt, pPosicion, &t);
}

//para el calculo necesito todos los valores
float calcularCostoMaritimo (Articulo* pArt, Posicion* pPosicion, Transporte* pT)
{
	getMtCubicos ();
	return pArt-> valor
}
*/


int art_addArticulo(Dictionary* pArrayArticulos, Dictionary* pArrayPosAranc, char* pFilePosAra, char* pFileArt)
{
	int ret = -1;
	Articulos* pA;
	PosArancelaria* pPA;
	int newId;
	char codigo[COD_LEN];
	char descripcion[DESCRIP_LEN];
	char paisFabricacion[PAIS_LEN];
	char nombre[NOM_LEN];
	char idArt [32];
	float valorFob, peso, ancho, alto, profundidad;
	char idPosAranc[32];

	if(pArrayArticulos!= NULL && pArrayPosAranc!=NULL)
	{
		controller_imprimirListaPosAranc(pArrayPosAranc);
		if (!utn_getStringWithOnlyNumbers("\nIngrese el id de la posicion arancelaria\n", "\nError\n", idPosAranc, 32, 3))
		{
			pPA=dict_get(pArrayPosAranc, idPosAranc);
			if(pPA!=NULL)
			{
				if (utn_getDescripcion(codigo, COD_LEN, "\nIngrese el codigo\n", "\nError\n", 3)==0 &&
					utn_getNombre(nombre, NOM_LEN, "\nIngrese el nombre del articulo\n", "\nError\n", 3)==0 &&
					utn_getDescripcion(descripcion, DESCRIP_LEN, "\nIngrese la descripcion\n", "\nError\n", 3)==0 &&
					utn_getTexto(paisFabricacion, PAIS_LEN, "\nIngrese el pais de fabricacion\n", "\nError\n", 3)==0 &&
					utn_getNumeroFlotante(&valorFob, "\nIngrese el precio FOB\n", "\nError\n", 0, 3000000, 3)==0 &&
					utn_getNumeroFlotante(&peso, "\nIngrese el peso\n", "\nError\n", 0, 300000, 3)==0 &&
					utn_getNumeroFlotante(&ancho, "\nIngrese el ancho\n", "\nError\n", 0, 300000, 3)==0 &&
					utn_getNumeroFlotante(&alto, "\nIngrese el alto\n", "\nError\n", 0, 300000, 3)==0 &&
					utn_getNumeroFlotante(&profundidad, "\nIngrese la profundidad\n", "\nError\n", 0, 300000, 3)==0)
				{
					newId = art_generarId();
					printf("\nID NUEVO: %d\n", newId);
					sprintf(idArt, "%d", newId);
					pA= art_newParam(codigo, descripcion, paisFabricacion, nombre, valorFob, peso, ancho, alto, profundidad, newId, atoi(idPosAranc));
					if (pA!=NULL)
					{
						dict_insert(pArrayArticulos, idArt, pA);
						controller_saveArticulosText(pFileArt, pArrayArticulos);
						ret = 0;
					}
				}
			}
			else
			{
				printf("\nPosicion arancelaria inexistente\n");
			}
		}
	}
	printf("RETORNO : %d", ret);
	return ret;
}

int art_editArticulo(Dictionary* pArrayArticulos, char* pFileArt)
{
	int ret = -1;
	Articulos* pA;
	char idFindArt[100];
	char codigo[10000];
	char descripcion[DESC_LEN];
	char paisFabricacion[PAIS_LEN];
	char nombre[NOM_LEN];
	float valorFob, peso, ancho, alto, profundidad;
	int flag;

	if (pArrayArticulos!=NULL)
	{
		if(!utn_getStringWithOnlyNumbers("\nIngrese el id que desea modificar\n", "\nError\n", idFindArt, 100, 3))
		{
			pA = dict_get(pArrayArticulos, idFindArt);

			if(pA!=NULL)
			{
				if (utn_getDescripcion(codigo, 10000, "\nIngrese el codigo\n", "\nError\n", 3)==0 &&
					utn_getNombre(nombre, NOM_LEN, "\nIngrese el nombre del articulo\n", "\nError\n", 3)==0 &&
					utn_getDescripcion(descripcion, DESCRIP_LEN, "\nIngrese la descripcion\n", "\nError\n", 3)==0 &&
					utn_getTexto(paisFabricacion, PAIS_LEN, "\nIngrese el pais de fabricacion\n", "\nError\n", 3)==0 &&
					utn_getNumeroFlotante(&valorFob, "\nIngrese el precio FOB\n", "\nError\n", 0, 3000000, 3)==0 &&
					utn_getNumeroFlotante(&peso, "\nIngrese el peso\n", "\nError\n", 0, 300000, 3)==0 &&
					utn_getNumeroFlotante(&ancho, "\nIngrese el ancho\n", "\nError\n", 0, 300000, 3)==0 &&
					utn_getNumeroFlotante(&alto, "\nIngrese el alto\n", "\nError\n", 0, 300000, 3)==0 &&
					utn_getNumeroFlotante(&profundidad, "\nIngrese la profundidad\n", "\nError\n", 0, 300000, 3)==0)
				{
					if(!art_setCodigo(pA, codigo) && !art_setNombre(pA, nombre) && !art_setDescripcion(pA, descripcion) &&
							!art_setPaisFabricacion(pA, paisFabricacion)&& !art_setValorFob(pA, valorFob)&& !art_setPeso(pA, peso)&&
							!art_setAncho(pA, ancho)&& !art_setAlto(pA, alto) && !art_setProfundidad(pA, profundidad))
					{
						printf("ENTRE AL FIN LOCO");
						printf("\nCODIGO: %s\n", art_getCodigo(pA, &flag));
						printf("\nNOMBRE: %s", art_getNombre(pA, &flag));
					}
				}
			}
			else
			printf("\nId inexistente");
		}
	}
	return ret;
}

int art_deleteArticulo(Dictionary* pArrayArticulos, char* pFileArt)
{
	char idFindArt[32];
	int ret= -1;
	Articulos* pA;
	if(!utn_getStringWithOnlyNumbers("\nIngrese el id que desea eliminar\n", "\nError\n", idFindArt, 32, 3))
	{
		pA = dict_get(pArrayArticulos, idFindArt);
		if (pA!=NULL)
		{
			art_delete(pA);
			if(!dict_remove(pArrayArticulos, idFindArt))
			{
				controller_saveArticulosText(pFileArt, pArrayArticulos);
				printf("\nEliminado exitosamente\n");
				ret = 0;
			}
		}
		else
			printf("\nId inexistente");
	}
	return ret;
}






