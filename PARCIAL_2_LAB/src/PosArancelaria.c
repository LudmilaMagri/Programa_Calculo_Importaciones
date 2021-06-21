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
int pos_setSeguro(PosArancelaria* this, float seguro)
{
	int retorno = -1;
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
	int aux = -1;
	if(this != NULL && flagError != NULL )
	{
		aux=this->seguro;
		*flagError = 0;
	}
	return aux;
}
int isValidSeguro(float seguro)
{
	return 1;
}
int pos_setImportacion(PosArancelaria* this, float importacion)
{
	int retorno = -1;
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
	int aux = -1;
	if(this != NULL && flagError != NULL )
	{
		aux=this->importacion;
		*flagError = 0;
	}
	return aux;
}
int isValidImportacion(float importacion)
{
	return 1;
}
int pos_setTasaEstadistica(PosArancelaria* this, float tasaEstadistica)
{
	int retorno = -1;
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
	int aux = -1;
	if(this != NULL && flagError != NULL )
	{
		aux=this->tasaEstadistica;
		*flagError = 0;
	}
	return aux;
}
int isValidTasaEstadistica(float tasaEstadistica)
{
	return 1;
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
	static int contador = 0; //mantiene su valor. no se comporta como localç
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

int pos_deletePosicionArancelaria(Dictionary* pArrayPosAra, char* pFile)
{
	char idFindPosAranc[32];
	int ret= -1;
	PosArancelaria* pPA;
	if(!utn_getStringWithOnlyNumbers("\nIngrese el id que desea eliminar\n", "\nError\n", idFindPosAranc, 32, 3))
	{
		pPA= dict_get(pArrayPosAra, idFindPosAranc);
		if (pPA!= NULL)
		{
			pos_delete(pPA);
			if(!dict_remove(pArrayPosAra, idFindPosAranc))
			{
				controller_savePosAraText(pFile, pArrayPosAra);
				printf("\nEliminado exitosamente");
				ret = 0;
			}
		}
		else
			printf("\nId inexistente");
	}
	return ret;
}





