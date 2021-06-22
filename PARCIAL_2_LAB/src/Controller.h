/*
 * Controller.h
 *
 *  Created on: 17 jun. 2021
 *      Author: ludmi
 */
#include "Aereo.h"
#include "LinkedList.h"
#include "Dictionary.h"
#include "Maritimo.h"

#ifndef CONTROLLER_H_
#define CONTROLLER_H_

int controller_art_loadFromText(char* pFile, Dictionary* articulos,int* pIdMaxEncontrado);
int controller_posAranc_loadFromText(char* pFile, Dictionary* posAranc,int* pIdMaxEncontrado);
int controller_MAR_loadFromText(char* pFile, Maritimo* transpMar);
int controller_AEREO_loadFromText(char* pFile, Aereo* transpAereo);


int controller_savePosAraText(char* pFile, Dictionary* posicionAranc);
int controller_saveArticulosText(char* pFile, Dictionary* articulos);
int controller_saveTransporteMaritimoText(char* pFile,Maritimo* pTransMar);
int controller_saveTransporteAereoText(char* pFile, Aereo* pAereo);


void funcionImprimirProlijoArticulos();
void funcionImprimirProlijoPosAranc();
void funcionImprimirProlijoCostoArgentino();

int controller_imprimirListaArticulosSort(LinkedList* articulos);
int controller_saveArticulosTextLL(char* pFile, LinkedList* articulos);


int controller_imprimirListaArticulos(Dictionary* articulos);
int controller_imprimirListaPosAranc(Dictionary* posicionAranc);
int controller_printCostoArgMaritimoAereo(Dictionary* pArt, Dictionary* pPosAranc, Maritimo* pMar, Aereo* pAereo);


int controller_ABM_Articulos(Dictionary* pArt, Dictionary* pPosAranc,char* pFilePosAra, char* pFileArt);
int controller_ABM_PosicionArancelaria(Dictionary* pPosAranc, Dictionary* pArt,char* pFilePosAranc, char* pFileArticulos);


int controller_sort (Dictionary* pArt, char* pFile);


int controller_mar_editTransporteMar(Maritimo* pMaritimo, char* pFile);
int controller_aer_editTransporteAereo(Aereo* pAereo, char* pFile);


int controller_imprimirListaFiltradaPosAran(Dictionary* posicionAranc);
int controller_imprimirListaFiltradaArticulos(Dictionary* pArticulos);
int controller_aplicarListaFiltrada(Dictionary* pArrayListPosAranc, Dictionary* pArticulos);

int funcionCriterioFiltrarLic(void* pGenerico);
int funcionCriterioValorFob(void* pGenerico);


float controller_buscarMayor (Dictionary* pArt);
float controller_buscarMayorCostoArgMaritimo(Dictionary* pArt, Dictionary* pPosAranc, Maritimo* pTransMar);

float aplicarDescuento (LinkedList* listaFiltrada, Dictionary* pArt);
int aplicarDescuentoEnValorFob (LinkedList* listaFiltrada);


int controller_buscarNomenclatura(Dictionary* pPosAranc, Dictionary* pArt);


#endif /* CONTROLLER_H_ */
