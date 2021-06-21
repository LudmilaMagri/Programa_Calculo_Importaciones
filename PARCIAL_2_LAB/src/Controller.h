/*
 * Controller.h
 *
 *  Created on: 17 jun. 2021
 *      Author: ludmi
 */

#ifndef CONTROLLER_H_
#define CONTROLLER_H_

#include "LinkedList.h"


#include "Dictionary.h"
int controller_imprimirListaArticulos(Dictionary* articulos);
int controller_imprimirListaPosAranc(Dictionary* posicionAranc);
int controller_ABM_Articulos(Dictionary* pArt, Dictionary* pPosAranc,char* pFilePosAra, char* pFileArt);
int controller_art_loadFromText(char* pFile, Dictionary* articulos,int* pIdMaxEncontrado);
int controller_posAranc_loadFromText(char* pFile, Dictionary* posAranc,int* pIdMaxEncontrado);

int controller_ABM_PosicionArancelaria(Dictionary* pPosAranc, char* pFile);

int controller_savePosAraText(char* pFile, Dictionary* posicionAranc);
int controller_saveArticulosText(char* pFile, Dictionary* articulos);

void funcionImprimirProlijoArticulos();
void funcionImprimirProlijoPosAranc();
void funcionImprimirProlijoCostoArgentino();

#include "Maritimo.h"
int controller_imprimirListaTransporteMar(Dictionary* posicionAranc, Dictionary* articulos, Maritimo* transMar);
int controller_MAR_loadFromText(char* pFile, Maritimo* transpMar);
int controller_saveTransporteMaritimoText(char* pFile,Maritimo* pTransMar);
int controller_mar_editTransporteMar(Maritimo* pMaritimo, char* pFile);



#include "Aereo.h"
int controller_AEREO_loadFromText(char* pFile, Aereo* transpAereo);
int controller_saveTransporteAereoText(char* pFile, Aereo* pAereo);
int imprimirCostoArgAereo(Dictionary* pArt, Dictionary* pPosAranc, Aereo* pAereo);
int controller_printCostoArgMaritimoAereo(Dictionary* pArt, Dictionary* pPosAranc, Maritimo* pMar, Aereo* pAereo);
int controller_aer_editTransporteAereo(Aereo* pAereo, char* pFile);

#endif /* CONTROLLER_H_ */
