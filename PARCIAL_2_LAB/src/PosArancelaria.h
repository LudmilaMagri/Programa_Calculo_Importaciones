/*
 * PosArancelaria.h
 *
 *  Created on: 16 jun. 2021
 *      Author: ludmi
 */
#include "Dictionary.h"
#include "Maritimo.h"
#include "Articulos.h"
#ifndef POSARANCELARIA_H_
#define POSARANCELARIA_H_

static const char ESTADO [2][20] ={"NO_AUTOMATICA","AUTOMATICA"};
typedef struct
{
	char nomenclaturaAranc[200];
	float seguro;
	float importacion;
	float tasaEstadistica;
	int tipoLicencia;
	int idPosArancelaria;
}PosArancelaria;


PosArancelaria* pos_new(void);
PosArancelaria* pos_newParam(char* nomenclaturaAranc, float seguro, float importacion, float tasaEstadistica, int tipoLicencia, int idPosArancelaria);

int pos_delete(PosArancelaria* this);

int pos_setNomenclatura(PosArancelaria* this,char* nomenclaturaAranc);
char* pos_getNomenclatura(PosArancelaria* this,int* flagError);
int isValidNomenclatura(char*);

int pos_setSeguro(PosArancelaria* this, float seguro);
float pos_getSeguro(PosArancelaria* this,int* flagError);
int isValidSeguro(float);

int pos_setImportacion(PosArancelaria* this, float importacion);
float pos_getImportacion(PosArancelaria* this,int* flagError);
int isValidImportacion(float);

int pos_setTasaEstadistica(PosArancelaria* this, float tasaEstadistica);
float pos_getTasaEstadistica(PosArancelaria* this,int* flagError);
int isValidTasaEstadistica(float);

int pos_setTipoLicencia(PosArancelaria* this,int tipoLicencia);
int pos_getTipoLicencia(PosArancelaria* this,int* flagError);
int isValidTipoLicencia(int);

int pos_setIdPosArancelaria(PosArancelaria* this,int idPosArancelaria);
int pos_getIdPosArancelaria(PosArancelaria* this,int* flagError);
int isValidIdPosArancelaria(int);

void pos_setearValorInicialDeId(int id);
int pos_generarId(void);
int pos_generarId2(void);



int pos_addPosicionArancelaria(Dictionary* pArrayPosAra, char* pFile);
int pos_editPosicionArancelaria(Dictionary* pArrayPosAra, char* pFile);
int pos_deletePosicionArancelaria(Dictionary* pArrayPosAra, char* pFile);

#endif /* POSARANCELARIA_H_ */
