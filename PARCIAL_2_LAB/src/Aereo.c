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

float aer_setConstVolumen(Aereo* this, float constVolumetrica)
{
	float retorno = -1;
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
	float aux = -1;
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
float aer_setPrecioPorKg(Aereo* this, float precioPorKg)
{
	float retorno = -1;
	if(this != NULL && isValidPrecioPorKg(precioPorKg)==1)
	{
		this->precioPorKg = precioPorKg;
		retorno = 0;
	}
	return retorno;
}
float aer_getPrecioPorKg(Aereo* this,int* flagError)
{
	*flagError = -1;
	float aux = -1;
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




//-------------------------------------------------------------------------


/** \brief Calcula el valor volumetrico del transporte aereo
 *
 * \param pArticulos Articulos* Puntero a la lista de Articulos
 * \param pAereo Aereo* Puntero al tipo de dato Aereo
 *
 * \return float ret (-1) si el puntero es NULL o el precio del valor volumetrico calculado
 */
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

/** \brief Calcula el volumen en centimetro cubico (c3)
 *
 * \param pArticulos Articulos* Puntero a la lista de Articulos
 *
 * \return float ret (-1) si el puntero es NULL o el volumen obtenido
 *
 */
float calcularVolumenAereoEnCm (Articulos* pArticulos)
{
	float ret = -1;
	float ancho, alto, prof, volumen;
	int flag;

	if (pArticulos!=NULL)
	{
		ancho = art_getAncho(pArticulos, &flag);
		alto = art_getAlto(pArticulos, &flag);
		prof = art_getProfundidad(pArticulos, &flag);
		volumen = ancho * alto * prof;
		ret = volumen;
	}
	return ret;
}
/** \brief Calcula el peso real del transporte aereo
 *
 * \param pArticulos Articulos* Puntero a la lista de Articulos
 * \param pAereo Aereo* Puntero al tipo de dato Aereo
 *
 * \return float ret (-1) si el puntero es NULL o el precio real
 */

float calcularTranspAereoPesoReal(Articulos* pArticulos, Aereo* pAereo)
{
	float ret = -1;
	float precioPesoReal, pesoArticulo, precio;
	int flag;
	if (pArticulos!= NULL && pAereo !=NULL)
	{
		pesoArticulo = art_getPeso(pArticulos, &flag);
		precio = aer_getPrecioPorKg(pAereo, &flag);
		precioPesoReal = (pesoArticulo) * precio;
		ret = precioPesoReal;
	}
	return ret;
}
/** \brief Calcula el mayor del transporte aereo
 *
 * \param pArticulos Articulos* Puntero a la lista de Articulos
 * \param pAereo Aereo* Puntero al tipo de dato Aereo
 *
 * \return float ret (-1) si el puntero es NULL o el precio mayor del transporte aereo
 */
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

/** \brief Calcula la base imponible aerea
 *
 * \param pPosAranc PosArancelaria* Puntero a la lista de Posiciones Arancelarias
 * \param pArt Articulos* Puntero a la lista de Articulos
 * \param pMar Maritimo* Puntero al tipo de dato Maritimo
 *
 * \return float ret (-1) si el puntero es NULL o la base imponible aerea
 *
 */
float calcularBaseImponibleAereo(PosArancelaria* pPosAranc,Articulos* pArt, Aereo* pAereo)
{
	float ret = -1;
	float seguroPorcTotal, transportePorcTotal, precioFob, baseImponibleTotal;
	int flag;
	if(pArt!=NULL && pAereo!=NULL && pPosAranc!=NULL)
	{
		precioFob = art_getValorFob(pArt, &flag);
		seguroPorcTotal = calcularPorcentajeSeguro(pPosAranc, pArt);
		transportePorcTotal = calcularTotalTransporteAereo(pArt, pAereo);
		baseImponibleTotal = precioFob + seguroPorcTotal + transportePorcTotal;
		ret = baseImponibleTotal;
	}
	return ret;
}
/** \brief Calcula el porcentaje del transporte aereo
 *
 * \param pArticulos Articulos* Puntero a la lista de Articulos
 *  \param pAereo Aereo* Puntero al tipo de dato Aereo
 *
 * \return float ret (-1) si el puntero es NULL o el porcentaje del transporte aereo calculado
 *
 */
float calcularPorcentajeTransporteAereo(Articulos* pArt, Aereo* pAereo)
{
	float ret = -1;
	float precioFob, porcentajeTransp, transporteTotal;
	int flag;
	if (pAereo!=NULL && pArt!=NULL)
	{
		precioFob = art_getValorFob(pArt, &flag);
		porcentajeTransp = calcularTotalTransporteAereo(pArt, pAereo);
		transporteTotal = (porcentajeTransp*precioFob)/100;
		ret = transporteTotal;
	}
	return ret;
}

/** \brief Calcula el costo Argentino Aereo
 *
 * \param pArt Articulos* Puntero a la lista de Articulos
 * \param pPosAranc PosArancelaria* Puntero a la lista de Posicion Arancelaria
 * \param pAereo Aereo* Puntero al tipo de dato Aereo
 *
 * \return float ret (-1) si el puntero es NULL o el costo argentino aereo calculado
 *
 */
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
/** \brief Calcula el porcentaje de importacion aereo
 *
 * \param pArticulos Articulos* Puntero a la lista de Articulos
 * \param pPosAranc PosArancelaria* Puntero a la lista de Posicion Arancelaria
 * \param pAereo Aereo* Puntero al tipo de dato Aereo
 *
 * \return float ret (-1) si el puntero es NULL o el porcentaje de importacion aereo calculado
 *
 */
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
/** \brief Calcula el porcentaje de la tasa estadistica aerea
 *
 * \param pArticulos Articulos* Puntero a la lista de Articulos
 * \param pPosAranc PosArancelaria* Puntero a la lista de Posicion Arancelaria
 * \param pAereo Aereo* Puntero al tipo de dato Aereo
 *
 * \return float ret (-1) si el puntero es NULL o el porcentaje de la tasa estadistica aerea calculada
 *
 */
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










