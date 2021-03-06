/*
 * PosArancelaria.c
 *
 *  Created on: 16 jun. 2021
 *      Author: ludmi
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "PosArancelaria.h"
#include "utn.h"
#include "Dictionary.h"
#include "Controller.h"
#include "Maritimo.h"

PosArancelaria* pos_new(void)
{
	return (PosArancelaria*) malloc(sizeof(PosArancelaria));

}
PosArancelaria* pos_newParam(char* nomenclaturaAranc, float seguro, float importacion, float tasaEstadistica, int tipoLicencia, int idPosArancelaria)
{
	PosArancelaria* aux = pos_new();
	if(aux != NULL)
	{
		if (	pos_setNomenclatura(aux, nomenclaturaAranc) < 0 ||
				pos_setSeguro(aux, seguro) <0 ||
				pos_setImportacion(aux, importacion) <0 ||
				pos_setTasaEstadistica(aux, tasaEstadistica) < 0 ||
				pos_setTipoLicencia(aux, tipoLicencia) < 0 ||
				pos_setIdPosArancelaria(aux, idPosArancelaria) < 0)
		{
			pos_delete(aux);
			aux = NULL;
		}
	}
	return aux;
}

int pos_delete(PosArancelaria* this)
{
	int retorno = -1;
	if(this != NULL)
	{
		free(this);
		retorno = 0;
	}
	return retorno;
}

int pos_setNomenclatura(PosArancelaria* this,char* nomenclaturaAranc)
{
	int retorno = -1;
	if(this != NULL && nomenclaturaAranc != NULL && isValidNomenclatura(nomenclaturaAranc) )
	{
		strcpy(this->nomenclaturaAranc,nomenclaturaAranc);
		retorno = 0;
	}
	return retorno;
}
char* pos_getNomenclatura(PosArancelaria* this,int* flagError)
{
	*flagError = -1;
	char* aux= NULL;
	if(this != NULL && flagError != NULL )
	{
		aux = this->nomenclaturaAranc;
		*flagError = 0;
	}
	return aux;
}

int isValidNomenclatura(char* nomenclatura)
{
	return 1;
}
float pos_setSeguro(PosArancelaria* this, float seguro)
{
	float retorno = -1;
	if(this != NULL && isValidSeguro(seguro) )
	{
		this->seguro = seguro;
		retorno = 0;
	}
	return retorno;
}
float pos_getSeguro(PosArancelaria* this,int* flagError)
{
	*flagError = -1;
	float aux = -1;
	if(this != NULL && flagError != NULL )
	{
		aux=this->seguro;
		*flagError = 0;
	}
	return aux;
}
int isValidSeguro(float seguro)
{
	int ret = -1;
	if (seguro> 0 && seguro<=999999999999)
	{
		ret = 1;
	}
	return ret;
}
float pos_setImportacion(PosArancelaria* this, float importacion)
{
	float retorno = -1;
	if(this != NULL && isValidImportacion(importacion) )
	{
		this->importacion = importacion;
		retorno = 0;
	}
	return retorno;
}
float pos_getImportacion(PosArancelaria* this,int* flagError)
{
	*flagError = -1;
	float aux = -1;
	if(this != NULL && flagError != NULL )
	{
		aux=this->importacion;
		*flagError = 0;
	}
	return aux;
}
int isValidImportacion(float importacion)
{
	int ret = -1;
	if (importacion> 0 && importacion<=999999999999)
	{
		ret = 1;
	}
	return ret;
}
float pos_setTasaEstadistica(PosArancelaria* this, float tasaEstadistica)
{
	float retorno = -1;
	if(this != NULL && isValidTasaEstadistica(tasaEstadistica) )
	{
		this->tasaEstadistica = tasaEstadistica;
		retorno = 0;
	}
	return retorno;
}
float pos_getTasaEstadistica(PosArancelaria* this,int* flagError)
{
	*flagError = -1;
	float aux = -1;
	if(this != NULL && flagError != NULL )
	{
		aux=this->tasaEstadistica;
		*flagError = 0;
	}
	return aux;
}
int isValidTasaEstadistica(float tasaEstadistica)
{
	int ret = -1;
	if (tasaEstadistica> 0 && tasaEstadistica<=999999999999)
	{
		ret = 1;
	}
	return ret;
}
int pos_setTipoLicencia(PosArancelaria* this,int tipoLicencia)
{
	int retorno = -1;
	if(this != NULL && isValidTipoLicencia(tipoLicencia) )
	{
		this->tipoLicencia = tipoLicencia;
		retorno = 0;
	}
	return retorno;
}
int pos_getTipoLicencia(PosArancelaria* this,int* flagError)
{
	*flagError = -1;
	int aux = -1;
	if(this != NULL && flagError != NULL )
	{
		aux=this->tipoLicencia;
		*flagError = 0;
	}
	return aux;
}
int isValidTipoLicencia(int tipoLicencia)
{
	return 1;
}
int pos_setIdPosArancelaria(PosArancelaria* this,int idPosArancelaria)
{
	int retorno = -1;
	if(this != NULL && isValidIdPosArancelaria(idPosArancelaria) )
	{
		this->idPosArancelaria = idPosArancelaria;
		retorno = 0;
	}
	return retorno;
}
int pos_getIdPosArancelaria(PosArancelaria* this,int* flagError)
{
	*flagError = -1;
	int aux = -1;
	if(this != NULL && flagError != NULL )
	{
		aux=this->idPosArancelaria;
		*flagError = 0;
	}
	return aux;
}
int isValidIdPosArancelaria(int idPosArancelaria)
{
	return 1;
}

static int contador=0; // NO ES LOCAL DE LA FUNCION
void pos_setearValorInicialDeId(int id)
{
	contador = id;
}

int pos_generarId(void)
{
	contador++;
	return contador;
}

int pos_generarId2(void)
{
	static int contador = 0; //mantiene su valor. no se comporta como local?
	contador++;
	return contador;
}

int pos_addPosicionArancelaria(Dictionary* pArrayPosAra, char* pFile)
{
	int ret=-1;
	char nomenclaturaAranc[10000];
	float seguro;
	float importacion;
	float tasaEstadistica;
	int tipoLicencia;
	char idPosArancKey[3000];
	int newId;
	PosArancelaria* pPA;
	if(pArrayPosAra!=NULL)
	{
		if(utn_getTextoNumerosCaracter(nomenclaturaAranc, 10000, "\nIngrese nomenclatura arancelaria\n", "\nError\n", 3)==0 &&
			utn_getNumeroFlotante(&seguro, "\nIngrese el porcentaje de seguro\n", "\nError\n", 0, 100, 3)==0 &&
			utn_getNumeroFlotante(&importacion, "\nIngrese el porcentaje de importacion\n", "\nError\n", 0, 100, 3)==0 &&
			utn_getNumeroFlotante(&tasaEstadistica, "\nIngrese el porcentaje de la tasa estadistica\n", "\nError\n", 0, 100, 3)==0 &&
			utn_getNumeroInt(&tipoLicencia, "\nIngrese el tipo de licencia [0:No automatica/ 1: Automatica]", "\nError\n", 0, 100, 3)==0)
		{
			newId = pos_generarId();
			printf("\nID NUEVO: %d\n", newId);
			sprintf(idPosArancKey, "%d", newId);
			pPA = pos_newParam(nomenclaturaAranc, seguro, importacion, tasaEstadistica, tipoLicencia, newId);
			if (pPA!=NULL)
			{
				dict_insert(pArrayPosAra, idPosArancKey, pPA);
				controller_savePosAraText(pFile, pArrayPosAra);
				ret=0;
			}
		}

	}
	return ret;
}
int pos_editPosicionArancelaria(Dictionary* pArrayPosAra, char* pFile)
{
	char idFindPosAranc[32];
	int ret=-1;
	PosArancelaria* pPA;
	char nomenclaturaAranc[10000];
	float seguro;
	float importacion;
	float tasaEstadistica;
	int tipoLicencia;

	if(pArrayPosAra!=NULL)
	{
		if(!utn_getStringWithOnlyNumbers("\nIngrese el id que desea modificar\n", "\nError\n", idFindPosAranc, 32, 3))
		{
			pPA=dict_get(pArrayPosAra, idFindPosAranc);
			if (pPA!=NULL)
			{
				if(!utn_getTextoNumerosCaracter(nomenclaturaAranc, 10000, "\nIngrese nomenclatura arancelaria\n", "\nError\n", 3) &&
					!utn_getNumeroFlotante(&seguro, "\nIngrese el porcentaje de seguro\n", "\nError\n", 0, 100, 3) &&
					!utn_getNumeroFlotante(&importacion, "\nIngrese el porcentaje de importacion\n", "\nError\n", 0, 100, 3) &&
					!utn_getNumeroFlotante(&tasaEstadistica, "\nIngrese el porcentaje de la tasa estadistica\n", "\nError\n", 0, 100, 3) &&
					!utn_getNumeroInt(&tipoLicencia, "\nIngrese el tipo de licencia [0:No automatica/ 1: Automatica]", "\nError\n", 0, 100, 3))
				{
					if(!pos_setNomenclatura(pPA, nomenclaturaAranc) && !pos_setSeguro(pPA, seguro) &&
						!pos_setImportacion(pPA, importacion) && !pos_setTasaEstadistica(pPA, tasaEstadistica) &&
						!pos_setTipoLicencia(pPA, tipoLicencia))
					{
						controller_savePosAraText(pFile, pArrayPosAra);
						printf("\nModificacion exitosa\n");
						ret = 0;
					}
				}
			}
			else
				printf("\nId inexistente\n");
		}
	}
	return ret;
}

int pos_deletePosicionArancelaria(Dictionary* pArrayPosAra, Dictionary* pArrayArticulos,char* pFilePosAranc, char* pFileArticulos)
{
	char idFindPosAranc[32];
	int ret= -1;
	PosArancelaria* pPA;
	LinkedList* pL;
	LinkedList* listaFiltrada = ll_newLinkedList();
	Articulos* pA;
	Articulos* pA2;
	int respuesta, flagError;
	char idChar[32];
	controller_imprimirListaPosAranc(pArrayPosAra);
	if(!utn_getStringWithOnlyNumbers("\nIngrese el id de la posicion arancelaria que desea eliminar\n", "\nError\n", idFindPosAranc, 32, 3))
	{
		pPA= dict_get(pArrayPosAra, idFindPosAranc); //obtendo la pos arancel de ese ID que quiero eliminar
		pL = dict_getValues(pArrayArticulos); //devuelve LL
		if (pPA!= NULL && pL!= NULL)
		{
			funcionImprimirProlijoArticulos();
			for (int i =0; i<ll_len(pL); i++)
			{
				pA = (Articulos*) ll_get(pL, i);
				if (pA->idPosicionArancelaria == atoi(idFindPosAranc))
				{
					ll_add(listaFiltrada, pA);
					printf("|%-10d|	%-10s|	%-10s|	%-10s|	%-10s|	%-10.2f|	%-10.2f|	%-10.2f|	%-10.2f|	%-10.2f|	%-10d\n", art_getIdArticulo(pA, &flagError), art_getCodigo(pA, &flagError),
																																art_getNombre(pA, &flagError), art_getDescripcion(pA, &flagError),
																																art_getPaisFabricacion(pA, &flagError), art_getValorFob(pA, &flagError),
																																art_getPeso(pA, &flagError), art_getAncho(pA, &flagError),
																																art_getAlto(pA, &flagError), art_getProfundidad(pA, &flagError),
																																art_getIdPosicionArancelaria(pA, &flagError));

				}
			}
			if(!utn_getNumeroInt(&respuesta, "\nSi elimina esta posicion arancelaria tambien se eliminaran los articulos asociados a ella.\nDesea continuar?\nSI: 1\nNO: 0\n",
											"\nError\n", 0, 2, 3))
			{
				if(respuesta ==1)
				{
					pos_delete(pPA);
					if(!dict_remove(pArrayPosAra, idFindPosAranc))
					{
						printf("\nPosicion arancelaria eliminada exitosamente");
						controller_savePosAraText(pFilePosAranc, pArrayPosAra);
					}

				}
			}
			for(int j=0; j<ll_len(listaFiltrada); j++)
			{
				pA2 = (Articulos*) ll_get(listaFiltrada, j);
				sprintf(idChar, "%d", pA2->idArticulo);
				if(!art_delete(pA2) &&!dict_remove(pArrayArticulos, idChar))
				{
					controller_saveArticulosText(pFileArticulos, pArrayArticulos);
					printf("\n ARTICULO: %d eliminado exitosamente", pA2->idArticulo);
					ret = 0;
				}
			}
		}
	}
		else
			printf("\nId inexistente");

	ll_deleteLinkedList(pL);
	ll_deleteLinkedList(listaFiltrada);
	return ret;
}
