/*
 * Maritimo.c
 *
 *  Created on: 16 jun. 2021
 *      Author: ludmi
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Maritimo.h"
#include "utn.h"
#include "Dictionary.h"
#include "Articulos.h"
#include "Controller.h"

int mar_newParam(Maritimo* pMar, float volumen, float precio)
{
	int ret = -1;
	if(pMar != NULL)
	{
		if (	mar_setVolumen(pMar, volumen) < 0 ||
				mar_setPrecio(pMar, precio) <0)
		{
			mar_delete(pMar);
			pMar = NULL;
		}
		ret =0;
	}
	return ret;
}

int mar_delete(Maritimo* this)
{
	int retorno = -1;
	if(this != NULL)
	{
		free(this);
		retorno = 0;
	}
	return retorno;
}

float mar_setVolumen(Maritimo* this, float volumen)
{
	float retorno = -1;
	if(this != NULL)
	{
		this->volumen = volumen;
		retorno = 0;
	}
	return retorno;
}

float mar_getVolumen(Maritimo* this,int* flagError)
{
	*flagError = -1;
	float aux = -1;
	if(this != NULL && flagError != NULL )
	{
		aux=this->volumen;
		*flagError = 0;
	}
	return aux;
}
int isValidVolumen(float volumen)
{
	int retorno = 1;
	if (volumen >'9' || volumen <'0')
	{
		retorno = 0;
	}
	return retorno;
}
float mar_setPrecio(Maritimo* this, float precio)
{
	float retorno = -1;
	if(this != NULL )
	{
		this->precio = precio;
		retorno = 0;
	}
	return retorno;
}
float mar_getPrecio(Maritimo* this,int* flagError)
{
	*flagError = -1;
	float aux = -1;
	if(this != NULL && flagError != NULL )
	{
		aux=this->precio;
		*flagError = 0;
	}
	return aux;
}

float mar_setVolumen2(Maritimo this, float volumen)
{
	float retorno = -1;
	if( isValidVolumen(volumen) )
	{
		this.volumen = volumen;
		retorno = 0;
	}
	return retorno;
}

float mar_getVolumen2(Maritimo this,int* flagError)
{
	*flagError = -1;
	float aux = -1;
	if(flagError != NULL )
	{
		aux=this.volumen;
		*flagError = 0;
	}
	return aux;
}
int isValidVolumen2(float volumen)
{
	return 1;
}
float mar_setPrecio2(Maritimo this, float precio)
{
	float retorno = -1;

		this.precio = precio;
		retorno = 0;

	return retorno;
}
float mar_getPrecio2(Maritimo this,int* flagError)
{
	*flagError = -1;
	float aux = -1;
	if(flagError != NULL )
	{
		aux=this.precio;
		*flagError = 0;
	}
	return aux;
}

int isValidPrecio2(float precio)
{
	int retorno = 1;
	if (precio >'9' || precio <'0')
	{
		retorno = 0;
	}
	return retorno;
}

/*float calcularCostoMaritimo (Articulo* pArt, Posicion* pPosicion, Transporte* pT)
{
	getMtCubicos ();
	return pArt-> valor
}*/



//-----------------------------------------------------------------------------------------

/** \brief Calcula el volumen en metro cubico (m3)
 *
 * \param pArticulos Articulos* Puntero a la lista de Articulos
 * \return float ret (-1) si el puntero es NULL o el volumen obtenido
 *
 */
float calcularMetroCubico(Articulos* pArticulos)
{
	float ret =-1;
	float ancho, alto, prof;
	int flag;
	float volumen;

	if (pArticulos!=NULL)
	{
		ancho = art_getAncho(pArticulos, &flag);
		alto = art_getAlto(pArticulos, &flag);
		prof = art_getProfundidad(pArticulos, &flag);
		volumen = (ancho/100) * (alto/100) * (prof/100);
		ret = volumen;
	}
	return ret;
}

/** \brief Calcula el total del transporte maritimo
 *
 * \param pArticulos Articulos* Puntero a la lista de Articulos
 *  \param pMar Maritimo* Puntero al tipo de dato Maritimo
 *
 * \return float ret (-1) si el puntero es NULL o el precio final obtenido
 *
 */
float calcularTotalTransporteMar(Articulos* pArticulos, Maritimo* pMar)
{
	float ret =-1;
	float volumenCalculado, volumenContenedor, precioFinal, precio;
	int flag;
	if(pArticulos!=NULL && pMar != NULL)
	{
		volumenCalculado = calcularMetroCubico(pArticulos);
		precio = mar_getPrecio(pMar, &flag);
		volumenContenedor = mar_getVolumen(pMar, &flag);
		precioFinal = (volumenCalculado * precio)/volumenContenedor;
		ret = precioFinal;

	}
	return ret;
}

/** \brief Calcula la base imponible maritima
 *
 * \param pArt Articulos* Puntero a la lista de Articulos
 *  \param pMar Maritimo* Puntero al tipo de dato Maritimo
 *  \param pPosAranc PosArancelaria* Puntero a la lista de Posiciones Arancelarias
 *
 * \return float ret (-1) si el puntero es NULL o la base imponible maritima
 *
 */
float calcularBaseImponibleMaritimo(Articulos* pArt, Maritimo* pMar, PosArancelaria* pPosAranc)
{
	float ret =-1;
	float seguroPorcTotal, transporteTotal, precioFob, totalBI;
	int flag;
	//BI = FOB+seguro+trans
	if (pArt!=NULL && pMar!=NULL && pPosAranc!=NULL)
	{
		precioFob = art_getValorFob(pArt, &flag);
		seguroPorcTotal = calcularPorcentajeSeguro(pPosAranc, pArt);
		transporteTotal = calcularTotalTransporteMar(pArt, pMar);
		totalBI = precioFob+ seguroPorcTotal + transporteTotal;
		ret = totalBI;
	}
	return ret;
}
/** \brief Calcula el porcentaje del seguro
 *
 * \param pArticulos Articulos* Puntero a la lista de Articulos
 *  \param pPosAranc PosArancelaria* Puntero a la lista de Posicion Arancelaria
 *
 * \return float ret (-1) si el puntero es NULL o el porcentaje del seguro calculado
 *
 */
float calcularPorcentajeSeguro (PosArancelaria* pPosAranc, Articulos* pArt)
{
	float ret = -1;
	float precioFob, porcentajeSeguro, seguroTotal;
	int flag;
	if (pPosAranc!=NULL && pArt!=NULL)
	{
		precioFob = art_getValorFob(pArt, &flag);
		porcentajeSeguro = pos_getSeguro(pPosAranc, &flag);
		seguroTotal = (porcentajeSeguro * precioFob)/100;
		ret = seguroTotal;
	}
	return ret;
}
/** \brief Calcula el porcentaje del transporte maritimo
 *
 * \param pArticulos Articulos* Puntero a la lista de Articulos
 *  \param pMar Maritimo* Puntero al tipo de dato Maritimo
 *
 * \return float ret (-1) si el puntero es NULL o el porcentaje del transporte maritimo calculado
 *
 */
float calcularPorcentajeTransporteMaritimo(Articulos* pArt, Maritimo* pMar)
{
	float ret = -1;
	float precioFob, porcentajeTransp, transporteTotal;
	int flag;
	if (pMar!=NULL && pArt!=NULL)
	{
		precioFob = art_getValorFob(pArt, &flag);
		porcentajeTransp = calcularTotalTransporteMar(pArt, pMar);
		transporteTotal = (porcentajeTransp * precioFob)/100;
		ret = transporteTotal;
	}
	return ret;
}

/** \brief Calcula el costo Argentino Maritimo
 *
 * \param pArticulos Articulos* Puntero a la lista de Articulos
 *  \param pPosAranc PosArancelaria* Puntero a la lista de Posicion Arancelaria
 *  \param pMar Maritimo* Puntero al tipo de dato Maritimo
 *
 * \return float ret (-1) si el puntero es NULL o el costo argentino maritimo calculado
 *
 */
float calcularCostoArgentinoMaritimo(PosArancelaria* pPosAranc, Articulos* pArt, Maritimo* pMar)
{
	float ret = -1;
	float baseImponible, porcImportacion, porcTasaEst, costoArgMaritimo;

	if (pPosAranc!=NULL && pArt!= NULL && pMar!=NULL)
	{
		baseImponible = calcularBaseImponibleMaritimo(pArt, pMar, pPosAranc);
		porcImportacion = calcularPorcImportacion(pPosAranc, pArt, pMar);
		porcTasaEst = calcularPorcTasaEstadistica(pPosAranc, pArt, pMar);
		costoArgMaritimo = baseImponible+porcImportacion+porcTasaEst;
		ret = costoArgMaritimo;
	}
	return ret;

}
/** \brief Calcula el porcentaje de importacion maritimo
 *
 * \param pArticulos Articulos* Puntero a la lista de Articulos
 * \param pPosAranc PosArancelaria* Puntero a la lista de Posicion Arancelaria
 * \param pMar Maritimo* Puntero al tipo de dato Maritimo
 *
 * \return float ret (-1) si el puntero es NULL o el porcentaje de importacion maritimo calculado
 *
 */
float calcularPorcImportacion (PosArancelaria* pPosAranc, Articulos* pArt, Maritimo* pMar)
{
	float ret = -1;
	float baseImponible, importacion, porcImporTotal;
	int flag;

	if (pArt!= NULL && pMar != NULL && pPosAranc!=NULL)
	{
		baseImponible = calcularBaseImponibleMaritimo(pArt, pMar, pPosAranc);
		importacion = pos_getImportacion(pPosAranc, &flag);
		porcImporTotal = (importacion* baseImponible)/100;
		ret = porcImporTotal;
	}
	return ret;
}
/** \brief Calcula el porcentaje de la tasa estadistica Maritima
 *
 * \param pArticulos Articulos* Puntero a la lista de Articulos
 * \param pPosAranc PosArancelaria* Puntero a la lista de Posicion Arancelaria
 * \param pMar Maritimo* Puntero al tipo de dato Maritimo
 *
 * \return float ret (-1) si el puntero es NULL o el porcentaje de la tasa estadistica maritima calculada
 *
 */
float calcularPorcTasaEstadistica (PosArancelaria* pPosAranc, Articulos* pArt, Maritimo* pMar)
{
	float baseImponible, tasaEstadistica, porcTasaEstTotal;
	int flag;
	if (pArt!= NULL && pMar != NULL && pPosAranc!=NULL)
	{
		baseImponible = calcularBaseImponibleMaritimo(pArt, pMar, pPosAranc);
		tasaEstadistica = pos_getTasaEstadistica(pPosAranc, &flag);
		porcTasaEstTotal = (tasaEstadistica * baseImponible)/100;
	}
	return porcTasaEstTotal;
}



