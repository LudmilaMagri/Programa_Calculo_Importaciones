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

int mar_setVolumen(Maritimo* this, float volumen)
{
	int retorno = -1;
	if(this != NULL && isValidVolumen(volumen) )
	{
		this->volumen = volumen;
		retorno = 0;
	}
	return retorno;
}

float mar_getVolumen(Maritimo* this,int* flagError)
{
	*flagError = -1;
	int aux = -1;
	if(this != NULL && flagError != NULL )
	{
		aux=this->volumen;
		*flagError = 0;
	}
	return aux;
}
int isValidVolumen(float volumen)
{
	return 1;
}
int mar_setPrecio(Maritimo* this, float precio)
{
	int retorno = -1;
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
	int aux = -1;
	if(this != NULL && flagError != NULL )
	{
		aux=this->precio;
		*flagError = 0;
	}
	return aux;
}

int mar_setVolumen2(Maritimo this, float volumen)
{
	int retorno = -1;
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
	int aux = -1;
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
int mar_setPrecio2(Maritimo this, float precio)
{
	int retorno = -1;

		this.precio = precio;
		retorno = 0;

	return retorno;
}
float mar_getPrecio2(Maritimo this,int* flagError)
{
	*flagError = -1;
	int aux = -1;
	if(flagError != NULL )
	{
		aux=this.precio;
		*flagError = 0;
	}
	return aux;
}

int isValidPrecio2(float precio)
{
	return 1;
}

/*float calcularCostoMaritimo (Articulo* pArt, Posicion* pPosicion, Transporte* pT)
{
	getMtCubicos ();
	return pArt-> valor
}*/




 //---------------------------CALCULO M3 Y TOTAL TRANSPORTE----------------------------------


float calcularMetroCubico(Articulos* pArticulos)
{
	float ancho, alto, prof;
	int flag;
	float volumen;

	if (pArticulos!=NULL)
	{
		ancho = art_getAncho(pArticulos, &flag);
		alto = art_getAlto(pArticulos, &flag);
		prof = art_getProfundidad(pArticulos, &flag);
		volumen = (ancho/100) * (alto/100) * (prof/100);
	}
	return volumen;
}


float calcularTotalTransporteMar(Articulos* pArticulos, Maritimo* pMar)
{
	float volumenCalculado, volumenContenedor, precioFinal, precio;
	int flag;
	if(pArticulos!=NULL && pMar != NULL)
	{
		volumenCalculado = calcularMetroCubico(pArticulos);
		precio = mar_getPrecio(pMar, &flag);
		volumenContenedor = mar_getVolumen(pMar, &flag);
		precioFinal = (volumenCalculado * precio)/volumenContenedor;
	}
	return precioFinal;
}


/*
float calcularTransporteMaritimo (Dictionary* articulos, Maritimo* pTransMar)
{
	int ret = -1;
	float precio;
	Articulos* pA;
	LinkedList* pL;
	//int idPosAran;

	if (articulos!=NULL)
	{
		pL = dict_getValues(articulos);
		if(pL!=NULL)
		{
			for (int i=0; i<ll_len(pL); i++)
			{
				pA = (Articulos*) ll_get(pL, i);
				//idPosAran = pA->idPosicionArancelaria;

				if (pA!=NULL)
				{
					precio = calcularTotalTransporteMar(pA, pTransMar);
					//printf("\nPRECIO FINAL: %f\n POS ARAN: %d", precio, idPosAran);
					ret =0;
				}
			}
		}
	}
	return precio;
}
*/


// --------------------------------------BASE IMPONIBLE MARITIMO--------------------------------------------
float calcularBaseImponibleMaritimo(Articulos* pArt, Maritimo* pMar, PosArancelaria* pPosAranc, float* totalBI)
{
	int ret =-1;
	float seguroPorcTotal, transportePorcTotal, precioFob;
	int flag;
	//BI = FOB+seguro+trans
	if (pArt!=NULL && pMar!=NULL && pPosAranc!=NULL && totalBI!=NULL)
	{
		precioFob = art_getValorFob(pArt, &flag);
		seguroPorcTotal = calcularPorcentajeSeguro(pPosAranc, pArt);
		transportePorcTotal = calcularPorcentajeTransporteMaritimo(pPosAranc, pArt, pMar);
		*totalBI = precioFob+ seguroPorcTotal + transportePorcTotal;
	}
	return ret;
}

float calcularPorcentajeSeguro (PosArancelaria* pPosAranc, Articulos* pArt)
{
	float precioFob, porcentajeSeguro, seguroTotal;
	int flag;
	if (pPosAranc!=NULL && pArt!=NULL)
	{
		precioFob = art_getValorFob(pArt, &flag);
		porcentajeSeguro = pos_getSeguro(pPosAranc, &flag);
		seguroTotal = (porcentajeSeguro * precioFob)/100;
	}
	return seguroTotal;
}

float calcularPorcentajeTransporteMaritimo(PosArancelaria* pPosAranc, Articulos* pArt, Maritimo* pTransMar)
{
	float ret = -1;
	float precioFob, porcentajeTransp, transporteTotal;
	int flag;
	if (pPosAranc!=NULL && pArt!=NULL)
	{
		precioFob = art_getValorFob(pArt, &flag);
		porcentajeTransp = calcularTotalTransporteMar(pArt, pTransMar);
		transporteTotal = (porcentajeTransp * precioFob)/100;
		ret = transporteTotal;

	}
	return ret;
}

//----------------------------COSTO ARG MARITIMO---------------------------------------------
float calcularCostoArgentino(PosArancelaria* pPosAranc, Articulos* pArt, Maritimo* pTransMar)
{
	float baseImponible, porcImportacion, porcTasaEst, costoArgMaritimo;

	if (pPosAranc!=NULL && pArt!= NULL && pTransMar!=NULL)
	{
		calcularBaseImponibleMaritimo(pArt, pTransMar, pPosAranc, &baseImponible);
		porcImportacion = calcularPorcImportacion(pArt, pTransMar, pPosAranc);
		porcTasaEst = calcularPorcTasaEstadistica(pArt, pTransMar, pPosAranc);
		costoArgMaritimo = baseImponible+porcImportacion+porcTasaEst;
	}
	return costoArgMaritimo;

}

float calcularPorcImportacion (Articulos* pArt, Maritimo* pMar, PosArancelaria* pPosAranc)
{
	float baseImponible, importacion, porcImporTotal;
	int flag;

	if (pArt!= NULL && pMar != NULL && pPosAranc!=NULL)
	{
		calcularBaseImponibleMaritimo(pArt, pMar, pPosAranc, &baseImponible);
		importacion = pos_getImportacion(pPosAranc, &flag);
		porcImporTotal = (importacion* baseImponible)/100;
	}
	return porcImporTotal;
}

float calcularPorcTasaEstadistica (Articulos* pArt, Maritimo* pMar, PosArancelaria* pPosAranc)
{
	float baseImponible, tasaEstadistica, porcTasaEstTotal;
	int flag;
	if (pArt!= NULL && pMar != NULL && pPosAranc!=NULL)
	{
		calcularBaseImponibleMaritimo(pArt, pMar, pPosAranc, &baseImponible);
		tasaEstadistica = pos_getTasaEstadistica(pPosAranc, &flag);
		porcTasaEstTotal = (tasaEstadistica * baseImponible)/100;

	}
	return porcTasaEstTotal;
}



