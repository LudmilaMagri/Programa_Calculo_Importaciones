/*
 * Aereo.h
 *
 *  Created on: 16 jun. 2021
 *      Author: ludmi
 */
#include "Articulos.h"
#include "PosArancelaria.h"
#ifndef AEREO_H_
#define AEREO_H_

typedef struct
{
	float constVolumetrica;
	float precioPorKg;
}Aereo;

int aer_newParam(Aereo* pAereo, float constVolumetrica, float precioPorKg);
int aer_delete(Aereo* this);

float aer_setConstVolumen(Aereo* this, float constVolumetrica);
float aer_getConstVolumen(Aereo* this,int* flagError);
int isValidConstVolumen(float);

float aer_setPrecioPorKg(Aereo* this, float precioPorKg);
float aer_getPrecioPorKg(Aereo* this,int* flagError);
int isValidPrecioPorKg(float);

int aer_setIdAereo(Aereo* this,int idAereo);
int aer_getIdAereo(Aereo* this,int* flagError);
int isValidIdAereo(int idAereo);



float calcularTranspAereoValorVolumetrico(Articulos* pArticulos, Aereo* pAereo);
float calcularMetroCubico(Articulos* pArticulos);
float calcularVolumenAereoEnCm (Articulos* pArticulos);
float calcularTranspAereoPesoReal(Articulos* pArticulos, Aereo* pAereo);
float calcularTotalTransporteAereo(Articulos* pArticulos, Aereo* pAereo);

float calcularBaseImponibleAereo(PosArancelaria* pPosAranc,Articulos* pArt, Aereo* pAereo);
float calcularPorcentajeSeguro (PosArancelaria* pPosAranc, Articulos* pArt);
float calcularPorcentajeTransporteAereo(Articulos* pArt, Aereo* pAereo);

float calcularCostoArgentinoAereo(PosArancelaria* pPosAranc, Articulos* pArt, Aereo* pAereo);
float calcularPorcImportacionAereo (PosArancelaria* pPosAranc, Articulos* pArt, Aereo* pAereo);
float calcularPorcTasaEstadisticaAereo(PosArancelaria* pPosAranc, Articulos* pArt, Aereo* pAereo);


#endif /* AEREO_H_ */
