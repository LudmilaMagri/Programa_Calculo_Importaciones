/*
 * Maritimo.h
 *
 *  Created on: 16 jun. 2021
 *      Author: ludmi
 */

#ifndef MARITIMO_H_
#define MARITIMO_H_

#include "Articulos.h"
#include "PosArancelaria.h"
#include "Dictionary.h"
#include "LinkedList.h"
typedef struct
{
	float volumen;
	float precio;
}Maritimo;

Maritimo* mar_new(void);
int mar_newParam(Maritimo* pMar, float volumen, float precio);

int mar_delete(Maritimo* this);

float mar_setVolumen(Maritimo* this, float volumen);
float mar_getVolumen(Maritimo* this,int* flagError);
int isValidVolumen(float);

float mar_setPrecio(Maritimo* this, float precio);
float mar_getPrecio(Maritimo* this,int* flagError);
int isValidPrecio(float);

float mar_setVolumen2(Maritimo this, float volumen);
float mar_getVolumen2(Maritimo this,int* flagError);
int isValidVolumen2(float);

float mar_setPrecio2(Maritimo this, float precio);
float mar_getPrecio2(Maritimo this,int* flagError);
int isValidPrecio2(float);

int mar_setIdMaritimo(Maritimo* this,int idMaritimo);
int mar_getIdMaritimo(Maritimo* this,int* flagError);
int isValidIdMaritimo(int);


float calcularMetroCubico(Articulos* pArticulos);
float calcularTotalTransporteMar(Articulos* pArticulos, Maritimo* pMar);

float calcularBaseImponibleMaritimo(Articulos* pArt, Maritimo* pMar, PosArancelaria* pPosAranc);
float calcularPorcentajeSeguro (PosArancelaria* pPosAranc, Articulos* pArt);
float calcularPorcentajeTransporteMaritimo(Articulos* pArt, Maritimo* pMar);

float calcularCostoArgentinoMaritimo(PosArancelaria* pPosAranc, Articulos* pArt, Maritimo* pMar);
float calcularPorcImportacion (PosArancelaria* pPosAranc, Articulos* pArt, Maritimo* pMar);
float calcularPorcTasaEstadistica (PosArancelaria* pPosAranc, Articulos* pArt, Maritimo* pMar);

#endif /* MARITIMO_H_ */
