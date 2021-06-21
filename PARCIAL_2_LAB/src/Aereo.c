/*
 * Aereo.c
 *
 *  Created on: 16 jun. 2021
 *      Author: ludmi
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Aereo.h"
#include "utn.h"
#include "Dictionary.h"


int aer_newParam(Aereo* pAereo, float constVolumetrica, float precioPorKg)
{
	int ret = -1;
	if(pAereo != NULL)
	{
		if (aer_setConstVolumen(pAereo, constVolumetrica) <0 ||
			aer_setPrecioPorKg(pAereo, precioPorKg) < 0)
		{
			aer_delete(pAereo);
			pAereo = NULL;
		}
		ret =0;
	}
	return ret;
}

int aer_delete(Aereo* this)
{
	int retorno = -1;
	if(this != NULL)
	{
		free(this);
		retorno = 0;
	}
	return retorno;
}

int aer_setConstVolumen(Aereo* this, float constVolumetrica)
{
	int retorno = -1;
	if(this != NULL && isValidConstVolumen(constVolumetrica) )
	{
		this->constVolumetrica = constVolumetrica;
		retorno = 0;
	}
	return retorno;
}
float aer_getConstVolumen(Aereo* this,int* flagError)
{
	*flagError = -1;
	int aux = -1;
	if(this != NULL && flagError != NULL )
	{
		aux=this->constVolumetrica;
		*flagError = 0;
	}
	return aux;
}
int isValidConstVolumen(float constVolumen)
{
	return 1;
}
int aer_setPrecioPorKg(Aereo* this, float precioPorKg)
{
	int retorno = -1;
	if(this != NULL && isValidPrecioPorKg(precioPorKg) )
	{
		this->precioPorKg = precioPorKg;
		retorno = 0;
	}
	return retorno;
}
float aer_getPrecioPorKg(Aereo* this,int* flagError)
{
	*flagError = -1;
	int aux = -1;
	if(this != NULL && flagError != NULL )
	{
		aux=this->precioPorKg;
		*flagError = 0;
	}
	return aux;
}
int isValidPrecioPorKg(float precioPorKg)
{
	return 1;
}
/*
int aer_setIdAereo(Aereo* this,int idAereo)
{
	int retorno = -1;
	if(this != NULL && isValidIdAereo(idAereo) )
	{
		this->idAereo = idAereo;
		retorno = 0;
	}
	return retorno;
}
int aer_getIdAereo(Aereo* this,int* flagError)
{
	*flagError = -1;
	int aux = -1;
	if(this != NULL && flagError != NULL )
	{
		aux=this->idAereo;
		*flagError = 0;
	}
	return aux;
}
int isValidIdAereo(int idAereo)
{
	return 1;
}
*/




//------------------------CALCULO TRANSP VALOR VOL------------------
float calcularTranspAereoValorVolumetrico(Articulos* pArticulos, Aereo* pAereo)
{
	float ret = -1;
	float volumenCalculado, constanteVol, pesoTotal, precio, precioVol;
	int flag;
	if (pArticulos!= NULL && pAereo !=NULL)
	{
		volumenCalculado = calcularVolumenAereoEnCm(pArticulos);
		constanteVol = aer_getConstVolumen(pAereo, &flag);
		precio = aer_getPrecioPorKg(pAereo, &flag);

		pesoTotal = volumenCalculado/constanteVol;
		precioVol = pesoTotal * precio;
		ret = precioVol;
	}
	return ret;
}
float calcularVolumenAereoEnCm (Articulos* pArticulos)
{
	float ancho, alto, prof;
	int flag;
	float volumen;

	if (pArticulos!=NULL)
	{
		ancho = art_getAncho(pArticulos, &flag);
		alto = art_getAlto(pArticulos, &flag);
		prof = art_getProfundidad(pArticulos, &flag);
		volumen = ancho * alto * prof;
	}
	return volumen;
}
//------------------------CALCULO TRANSP PESO REAL------------------
float calcularTranspAereoPesoReal(Articulos* pArticulos, Aereo* pAereo)
{
	float ret = -1;
	float precioPesoReal, pesoArticulo, precio;
	int flag;
	if (pArticulos!= NULL && pAereo !=NULL)
	{
		pesoArticulo = art_getPeso(pArticulos, &flag);
		precio = aer_getPrecioPorKg(pAereo, &flag);
		precioPesoReal = (pesoArticulo/1000) * precio;
		ret = precioPesoReal;
	}
	return ret;
}
//------------------------CALCULO TOTAL TRANSP AEREO------------------
float calcularTotalTransporteAereo(Articulos* pArticulos, Aereo* pAereo)
{
	float ret = -1;
	float precioValorVolum, precioReal;

	if (pArticulos!= NULL && pAereo !=NULL)
	{
		precioValorVolum = calcularTranspAereoValorVolumetrico(pArticulos, pAereo);
		precioReal = calcularTranspAereoPesoReal(pArticulos, pAereo);
		if (precioValorVolum > precioReal)
		{
			ret = precioValorVolum;
		}
		else
		{
			ret = precioReal;
		}
	}
	return ret;
}

// --------------------------------------BASE IMPONIBLE AEREO--------------------------------------------
float calcularBaseImponibleAereo(PosArancelaria* pPosAranc,Articulos* pArt, Aereo* pAereo)
{
	int ret = -1;
	float seguroPorcTotal, transportePorcTotal, precioFob, baseImponibleTotal;
	int flag;
	if(pArt!=NULL && pAereo!=NULL && pPosAranc!=NULL)
	{
		precioFob = art_getValorFob(pArt, &flag);
		seguroPorcTotal = calcularPorcentajeSeguro(pPosAranc, pArt);
		transportePorcTotal = calcularPorcentajeTransporteAereo(pPosAranc, pArt, pAereo);
		baseImponibleTotal = precioFob + seguroPorcTotal + transportePorcTotal;
		ret = baseImponibleTotal;
	}
	return ret;
}

float calcularPorcentajeTransporteAereo(PosArancelaria* pPosAranc, Articulos* pArt, Aereo* pAereo)
{
	float ret = -1;
	float precioFob, porcentajeTransp, transporteTotal;
	int flag;
	if (pPosAranc!=NULL && pArt!=NULL)
	{
		precioFob = art_getValorFob(pArt, &flag);
		porcentajeTransp = calcularTotalTransporteAereo(pArt, pAereo);
		transporteTotal = (porcentajeTransp*precioFob)/100;
		ret = transporteTotal;
	}
	return ret;
}

// --------------------------------------COSTO ARG AEREO--------------------------------------------
float calcularCostoArgentinoAereo(PosArancelaria* pPosAranc, Articulos* pArt, Aereo* pAereo)
{
	float ret = -1;
	float baseImponible, porcImportacion, porcTasaEst, costoArgAereo;
	if (pPosAranc!=NULL && pArt!=NULL && pAereo!=NULL)
	{
		baseImponible = calcularBaseImponibleAereo(pPosAranc, pArt, pAereo);
		porcImportacion = calcularPorcImportacionAereo(pPosAranc, pArt, pAereo);
		porcTasaEst = calcularPorcTasaEstadisticaAereo(pPosAranc, pArt, pAereo);
		costoArgAereo = baseImponible+porcImportacion+porcTasaEst;
		ret = costoArgAereo;
	}
	return ret;
}

float calcularPorcImportacionAereo (PosArancelaria* pPosAranc, Articulos* pArt, Aereo* pAereo)
{
	float ret = -1;
	float baseImponible, importacion, porcImporTotal;
	int flag;
	if (pPosAranc!=NULL && pArt!=NULL && pAereo!=NULL)
	{
		baseImponible = calcularBaseImponibleAereo(pPosAranc, pArt, pAereo);
		importacion = pos_getImportacion(pPosAranc, &flag);
		porcImporTotal = (importacion*baseImponible)/100;
		ret = porcImporTotal;
	}
	return ret;
}
float calcularPorcTasaEstadisticaAereo(PosArancelaria* pPosAranc, Articulos* pArt, Aereo* pAereo)
{
	float ret = -1;
	float baseImponible, tasaEstadistica, porcTasaEstTotal;
	int flag;
	if (pPosAranc!=NULL && pArt!=NULL && pAereo!=NULL)
	{
		baseImponible = calcularBaseImponibleAereo(pPosAranc, pArt, pAereo);
		tasaEstadistica = pos_getTasaEstadistica(pPosAranc, &flag);
		porcTasaEstTotal = (tasaEstadistica*baseImponible)/100;
		ret = porcTasaEstTotal;
	}
	return ret;
}










