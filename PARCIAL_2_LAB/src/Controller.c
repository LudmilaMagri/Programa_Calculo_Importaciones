/*
 * Controller.c
 *
 *  Created on: 17 jun. 2021
 *      Author: ludmi
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Articulos.h"
#include "utn.h"
#include "Controller.h"
#include "Dictionary.h"
#include "LinkedList.h"
#include "PosArancelaria.h"
#include "Maritimo.h"
#include "Aereo.h"
#include "parser.h"
#define PORC_DESC 50

int controller_art_loadFromText(char* pFile, Dictionary* articulos,int* pIdMaxEncontrado)
{
	int retorno = -1;
	FILE* fpArchivo;

	if(pFile != NULL &&  articulos!=NULL)
	{
		fpArchivo = fopen(pFile, "r");
		if(fpArchivo!=NULL)
		{
			*pIdMaxEncontrado = parser_ArticulosFromText(fpArchivo, articulos);
			art_valorInicialId(*pIdMaxEncontrado);
			retorno = 0;
			printf("\nArticulos cargados correctamente en modo texto");
		}
		fclose(fpArchivo);
	}
	return retorno;
}
int controller_posAranc_loadFromText(char* pFile, Dictionary* posAranc,int* pIdMaxEncontrado)
{
	int retorno = -1;
	FILE* fpArchivo;

	if(pFile != NULL &&  posAranc!=NULL)
	{
		fpArchivo = fopen(pFile, "r");
		if(fpArchivo!=NULL)
		{
			*pIdMaxEncontrado = parser_PosArancFromText(fpArchivo, posAranc);
			pos_setearValorInicialDeId(*pIdMaxEncontrado);
			retorno = 0;
			printf("\nPosicion arancelaria cargada correctamente en modo texto");
		}
		fclose(fpArchivo);
	}
	return retorno;
}

int controller_MAR_loadFromText(char* pFile, Maritimo* transpMar)
{
	int retorno = -1;
	FILE* fpArchivo;

	if(pFile != NULL &&  transpMar!=NULL)
	{
		fpArchivo = fopen(pFile, "r");
		if(fpArchivo!=NULL)
		{
			if (parser_TranspMarFromText(fpArchivo, transpMar)==0)
			{
				printf("\nTransporte maritimo cargado correctamente");
			}
		}
		fclose(fpArchivo);
	}
	return retorno;
}
int controller_AEREO_loadFromText(char* pFile, Aereo* transpAereo)
{
	int retorno = -1;
	FILE* fpArchivo;

	if(pFile != NULL &&  transpAereo!=NULL)
	{
		fpArchivo = fopen(pFile, "r");
		if(fpArchivo!=NULL)
		{
			if (parser_TranspAereoFromText(fpArchivo, transpAereo)==0)
			{
				printf("\nTransporte aereo cargado correctamente\n");
			}
		}
		fclose(fpArchivo);
	}
	return retorno;
}

int controller_ABM_Articulos(Dictionary* pArt, Dictionary* pPosAranc,char* pFilePosAra, char* pFileArt)
{
	int retorno = -1;
	int opcion;
	if (pArt != NULL)
	{
		do
		{
			if(!utn_getNumeroInt(&opcion,
					"\n\t-------------------------------------------------"
					"\n\t\t***** MENU ARTICULOS *****							\n"
					"\n\t*	1. Alta de un articulo.\t\t\t*"
					"\n\t*	2. Modificar un articulo.\t\t*"
					"\n\t*	3. Baja de un articulo.\t\t\t*"
					"\n\t*	0. Salir.\t\t\t\t*"
					"\n\t-------------------------------------------------\n\nIngrese opcion: ",
							"Opcion incorrecta", 0, 6, 3))
			{
				switch(opcion)
				{
					case 1:
						if(pFilePosAra!=NULL)
						{
							art_addArticulo(pArt, pPosAranc, pFilePosAra, pFileArt);
						}
						else
						{
							printf("\nNo se han encontrado posiciones arancelarias disponibles. Cargue una antes de continuar\n");
							pos_addPosicionArancelaria(pPosAranc, pFilePosAra);
						}
						break;
					case 2:
							art_editArticulo(pArt, pFileArt);
						break;
					case 3:
							art_deleteArticulo(pArt, pFileArt);
						break;
				}
			}
		}while(opcion!=0);
		retorno = 0;
	}
	return retorno;
}



int controller_ABM_PosicionArancelaria(Dictionary* pPosAranc, Dictionary* pArt,char* pFilePosAranc, char* pFileArticulos)
{
	int retorno = -1;
	int opcion;
	if (pPosAranc != NULL)
	{
		do
		{
			if(!utn_getNumeroInt(&opcion,
					"\n\t---------------------------------------------------------------"
					"\n\t\t***** MENU POSICIONES ARANCELARIAS*****							\n"
					"\n\t*	1. Alta de una posicion arancelaria.\t\t\t*"
					"\n\t*	2. Modificar una posicion arancelaria.\t\t\t*"
					"\n\t*	3. Eliminar una posicion arancelaria.\t\t\t*"
					"\n\t*	0. Salir.\t\t\t\t\t\t*"
					"\n\t---------------------------------------------------------------\n\nIngrese opcion: ",
							"Opcion incorrecta", 0, 6, 3))
			{
				switch(opcion)
				{
					case 1:
						pos_addPosicionArancelaria(pPosAranc, pFilePosAranc);
						break;
					case 2:
						pos_editPosicionArancelaria(pPosAranc, pFilePosAranc);
						break;
					case 3:
						pos_deletePosicionArancelaria(pPosAranc, pArt, pFilePosAranc, pFileArticulos);
						break;
				}
			}
		}while(opcion!=0);
		retorno = 0;
	}
	return retorno;
}

void funcionImprimirProlijoArticulos()
{
	char id[10] = "ID ART";
	char codigo[10] = "CODIGO";
	char nombre[10] = "NOMBRE";
	char desc [20] = "DESCRIP";
	char pais[10] = "PAIS";
	char fob [10] = "FOB";
	char peso[10] = "PESO";
	char ancho[10] = "ANCHO";
	char alto [10] = "ALTO";
	char prof [10] = "PROFUN.";
	char idPA[10] = "ID P.A";
	char aereo [20] = "COSTO AEREO";
	char mar [20] = "COSTO MARITIMO";

	printf("\n|%-10s|	%-10s|	%-10s|	%-10s\t|	%-10s|	%-10s|	%-10s|	%-10s|	%-10s|	%-10s|	%-10s	%-10s	%-10s\n", id, codigo, nombre, desc, pais, fob, peso, ancho, alto, prof, idPA, mar, aereo);
	printf("|-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|\n");

}
int controller_imprimirListaArticulos(Dictionary* articulos)
{
	int ret=-1;
	int i;
	int flagError;
	LinkedList* pL;
	Articulos* pA;

	// Obtengo empleados del diccionario e imprimo sus datos
	if (articulos != NULL)
	{
		pL = dict_getValues(articulos); //obtengo la dir de memo de la ll
		if(pL!=NULL)
		{

			funcionImprimirProlijoArticulos();
			//printf("\n|ID ART\t|    CODIGO\t|  NOMBRE\t|  DESCRIPCION\t|  PAIS\t|  FOB\t| PESO\t| ANCHO\t|  ALTO\t|  PROFUN.\t|  ID P.A|\n");
			for (i=0; i<ll_len(pL); i++)
			{
				pA =(Articulos*)ll_get(pL, i); //elementos que estan en el ll que estaban en el diccionario
				if(pA!=NULL)
				{
					printf("|%-10d|	%-10s|	%-10s|%10s\t|\t%-10s|	%-10.4f|%-10.3f|	%-10.3f|	%-10.3f|	%-10.3f|	%-10d |		%f	| %f\n", art_getIdArticulo(pA, &flagError), art_getCodigo(pA, &flagError),
																											art_getNombre(pA, &flagError), art_getDescripcion(pA, &flagError),
																											art_getPaisFabricacion(pA, &flagError), art_getValorFob(pA, &flagError),
																											art_getPeso(pA, &flagError), art_getAncho(pA, &flagError),
																											art_getAlto(pA, &flagError), art_getProfundidad(pA, &flagError),
																											art_getIdPosicionArancelaria(pA, &flagError),art_getValorMaritimo(pA, &flagError) ,art_getValorAereo(pA, &flagError));
				}
			}
		}
		ll_deleteLinkedList(pL);
	}
	return ret;
}
int controller_imprimirListaArticulosSort(LinkedList* articulos)
{
	int ret=-1;
	int i;
	int flagError;
	Articulos* pA;

	// Obtengo empleados del diccionario e imprimo sus datos
	if (articulos != NULL)
	{
		funcionImprimirProlijoArticulos();
		//printf("\n|ID ART\t|    CODIGO\t|  NOMBRE\t|  DESCRIPCION\t|  PAIS\t|  FOB\t| PESO\t| ANCHO\t|  ALTO\t|  PROFUN.\t|  ID P.A|\n");
		for (i=0; i<ll_len(articulos); i++)
		{
			pA =(Articulos*)ll_get(articulos, i); //elementos que estan en el ll que estaban en el diccionario
			if(pA!=NULL)
			{
				printf("|%-10d|	%-10s|	%-10s|	%-10s|	%-10s|	%-10.2f|	%-10.2f|	%-10.2f|	%-10.2f|	%-10.2f|	%-10d\n", art_getIdArticulo(pA, &flagError), art_getCodigo(pA, &flagError),
																										art_getNombre(pA, &flagError), art_getDescripcion(pA, &flagError),
																										art_getPaisFabricacion(pA, &flagError), art_getValorFob(pA, &flagError),
																										art_getPeso(pA, &flagError), art_getAncho(pA, &flagError),
																										art_getAlto(pA, &flagError), art_getProfundidad(pA, &flagError),
																										art_getIdPosicionArancelaria(pA, &flagError));
			}
		}
	}
	return ret;
}
void funcionImprimirProlijoPosAranc()
{
	char idPosAranc[20] = "ID P.A";
	char nomenclador[20] = "NOMENCLADOR";
	char seguro[20] = "SEGURO (%)";
	char import[20] = "IMPORT (%)";
	char tasaEst[20] = "TASA ESTAD (%)";
	char tipoLic[20] = "TIPO LIC";
	printf("\n|%5s\t|	%-10s	|%-10s|\t%-5s\t|%-5s\t|%-10s\t|\n", idPosAranc, nomenclador, seguro, import, tasaEst, tipoLic);
	printf("|-----------------------------------------------------------------------------------------------|\n");

}
int controller_imprimirListaPosAranc(Dictionary* posicionAranc)
{
	int ret=-1;
	int i;
	int flagError;
	LinkedList* pL;
	PosArancelaria* pPA;

	// Obtengo empleados del diccionario e imprimo sus datos
	if (posicionAranc != NULL)
	{
		pL = dict_getValues(posicionAranc); //obtengo la dir de memo de la ll
		if(pL!=NULL)
		{
			funcionImprimirProlijoPosAranc();
			for (i=0; i<ll_len(pL); i++)
			{
				pPA =(PosArancelaria*)ll_get(pL, i); //elementos que estan en el ll que estaban en el diccionario
				if(pPA!=NULL)
				{
					printf("|%5d\t|\t%s\t|%-10.3f|\t%-5.3f\t\t|%5.3f\t\t| %s  \n", pos_getIdPosArancelaria(pPA, &flagError), pos_getNomenclatura(pPA, &flagError),
																				pos_getSeguro(pPA, &flagError), pos_getImportacion(pPA, &flagError),
																				pos_getTasaEstadistica(pPA, &flagError), ESTADO[pos_getTipoLicencia(pPA, &flagError)]);
				}
			}
		}
		ll_deleteLinkedList(pL);
	}
	return ret;
}

int controller_savePosAraText(char* pFile, Dictionary* posicionAranc)
{
	int ret= -1;
	int i;
	int flag;
	FILE* fpArchivo;
	LinkedList* pL;
	PosArancelaria* pPA;

	fpArchivo = fopen(pFile, "w");
	if(fpArchivo!=NULL)
	{
		fprintf(fpArchivo,"idPosAranc,nomenclatura,seguro,importacion,tasaEstad,tipoLic\n");
		pL = dict_getValues(posicionAranc);
		if(pL!=NULL)
		{
			for(i=0; i<ll_len(pL); i++)
			{
				pPA = (PosArancelaria*)ll_get(pL, i);
				if(pPA!=NULL)
				{
					fprintf(fpArchivo, "%d,%s,%.2f,%.2f,%.2f,%d\n", pos_getIdPosArancelaria(pPA, &flag), pos_getNomenclatura(pPA, &flag),
														pos_getSeguro(pPA, &flag), pos_getImportacion(pPA, &flag),
														pos_getTasaEstadistica(pPA, &flag), pos_getTipoLicencia(pPA, &flag));
					ret = 0;
				}
			}
		}
		ll_deleteLinkedList(pL);
		fclose(fpArchivo);
	}
	return ret;
}

int controller_saveArticulosText(char* pFile, Dictionary* articulos)
{
	int ret = -1;
	int i;
	int flag;
	FILE* fpArchivo;
	LinkedList* pL;
	Articulos* pA;
	fpArchivo = fopen(pFile, "w");

	if(fpArchivo!=NULL)
	{
		fprintf(fpArchivo,"id,codigo,nombre,descripcion,pais,valorFob,peso,ancho,alto,profundidad,idPA,costoArgAereo,costoMaritimo\n");
		pL = dict_getValues(articulos);
		if(pL!=NULL)
		{
			for(i=0; i<ll_len(pL); i++)
			{
				pA = (Articulos*) ll_get(pL, i);
				if(pA!=NULL)
				{
					fprintf(fpArchivo, "%d,%s,%s,%s,%s,%.4f,%.4f,%.4f,%.4f,%.4f,%d,%f,%f\n",art_getIdArticulo(pA, &flag), art_getCodigo(pA, &flag),
																					art_getNombre(pA, &flag), art_getDescripcion(pA, &flag),
																					art_getPaisFabricacion(pA, &flag), art_getValorFob(pA, &flag),
																					art_getPeso(pA, &flag), art_getAncho(pA, &flag),
																					art_getAlto(pA, &flag), art_getProfundidad(pA, &flag),
																					art_getIdPosicionArancelaria(pA, &flag), art_getValorAereo(pA, &flag),
																					art_getValorMaritimo(pA, &flag));
					ret =0;
				}
			}
		}
		ll_deleteLinkedList(pL);
		fclose(fpArchivo);
	}
	return ret;
}


int controller_saveTransporteMaritimoText(char* pFile, Maritimo* pTransMar)
{
	int ret =-1;
	FILE* fpArchivo;
	int flag;
	float volumen,precio;

	if(pFile!= NULL && pTransMar!=NULL)
	{
		fpArchivo =fopen(pFile, "w");
		if(fpArchivo!=NULL)
		{
			fprintf(fpArchivo,"volumen, precio\n");
			volumen = mar_getVolumen(pTransMar, &flag);
			precio = mar_getPrecio(pTransMar, &flag);
			fprintf(fpArchivo, "%.3f, %.3f\n", volumen, precio);
			ret = 0;
		}
		fclose(fpArchivo);
	}
	return ret;
}


int controller_saveTransporteAereoText(char* pFile, Aereo* pAereo)
{
	int ret = -1;
	int flag;
	float constVol, precio;
	FILE* fpArchivo;
	if(pFile!=NULL && pAereo!=NULL)
	{
		fpArchivo = fopen(pFile, "w");
		if(fpArchivo!=NULL)
		{
			fprintf(fpArchivo,"constVol,precio\n");
			constVol = aer_getConstVolumen(pAereo, &flag);
			precio = aer_getPrecioPorKg(pAereo, &flag);
			fprintf(fpArchivo, "%.3f, %.3f\n", constVol,precio);
			ret = 0;
		}
		fclose(fpArchivo);
	}
	return ret;
}

int controller_mar_editTransporteMar(Maritimo* pMaritimo, char* pFile)
{
	int ret = -1;
	float precio, volumen;
	if (pMaritimo!=NULL && pFile!=NULL)
	{
		if(!utn_getNumeroFlotante(&volumen, "\nIngrese el volumen del contenedor\n", "\nError\n", 0, 1000000, 3) &&
			!utn_getNumeroFlotante(&precio, "\nIngrese precio por m3\n", "\nError\n", 0, 10000000, 3))
		{
			if(!mar_setPrecio(pMaritimo, precio) && !mar_setVolumen(pMaritimo, volumen))
			{
				printf("\nDatos cargados: Volumen: %.3f - Precio: %.3f", volumen, precio);
				if (!controller_saveTransporteMaritimoText(pFile, pMaritimo))
				{
					printf("\nDatos guardados exitosamente\n");
					ret =0;
				}
			}
		}
	}
	return ret;
}
int controller_aer_editTransporteAereo(Aereo* pAereo, char* pFile)
{
	int ret = -1;
	float constVol, precio;
	if (pAereo!=NULL && pFile!=NULL)
	{
		if(!utn_getNumeroFlotante(&constVol, "\nIngrese la constante volumetrica\n", "\nError\n", 0, 10000000, 3) &&
				!utn_getNumeroFlotante(&precio, "\nIngrese el precio\n", "\nError\n", 0, 1000000, 3))
		{
			if(!aer_setConstVolumen(pAereo, constVol) && !aer_setPrecioPorKg(pAereo, precio))
			{
				printf("\nDatos cargados\n: Const: %.3f - Precio: %.3f", constVol, precio);
				if(!controller_saveTransporteAereoText(pFile, pAereo))
				{
					printf("\nDatos guardados exitosamente\n");
					ret =0;
				}
			}
		}
	}
	return ret;
}


void funcionImprimirProlijoCostoArgentino()
{
	char id[10] = "ID ART";
	char codigo[10] = "CODIGO";
	char nombre[10] = "NOMBRE";
	char desc [20] = "DESCRIP";
	char pais[10] = "PAIS";
	char fob [10] = "FOB";
	char peso[10] = "PESO";
	char ancho[10] = "ANCHO";
	char alto [10] = "ALTO";
	char prof [10] = "PROFUN.";
	char idPA[10] = "ID P.A";
	char costoArgMar[25] = "COSTO ARG MARITIMO";
	char costoArgAereo[25] = "COSTO ARG AEREO";
	//char codigo[COD_LEN], nombre[NOM_LEN], desc[DESCRIP_LEN], pais[PAIS_LEN];
	//float fob, peso, ancho, alto, prof;
	printf("|------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|");
	printf("\n|%-10s|	%-10s|	%-10s|	%-10s|	%-10s|	%-10s|	%-10s|	%-10s|	%-10s|	%-10s|	%-10s|%-3s	|%-3s\n", id, codigo, nombre, desc, pais, fob, peso, ancho,alto, prof,idPA, costoArgMar, costoArgAereo);
	printf("|------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|\n");

}


int controller_printCostoArgMaritimoAereo(Dictionary* pArt, Dictionary* pPosAranc, Maritimo* pMar, Aereo* pAereo, char* pFileArt)
{
	int ret = -1;
	LinkedList* pL;
	Articulos* pA;
	int i;
	PosArancelaria* pPA;
	int idPA;
	char keyPA [32];
	int flag;
	float costoArgMaritimoTotal, costoArgAereoTotal;
	if (pArt!=NULL && pPosAranc!=NULL && pMar!=NULL)
	{
		pL = dict_getValues(pArt);
		if(pL!=NULL)
		{
			funcionImprimirProlijoCostoArgentino();
			for (i=0; i<ll_len(pL); i++)
			{
				pA =(Articulos*)ll_get(pL, i); //elementos que estan en el ll que estaban en el diccionario
				idPA = pA->idPosicionArancelaria;
				sprintf(keyPA, "%d", idPA);
				pPA = dict_get(pPosAranc, keyPA);
				if(pA!=NULL)
				{
					 costoArgMaritimoTotal=calcularCostoArgentinoMaritimo(pPA, pA, pMar);
					 costoArgAereoTotal = calcularCostoArgentinoAereo(pPA, pA, pAereo);
					 art_setValorAereo(pA, costoArgAereoTotal);
					 art_setValorMaritimo(pA, costoArgMaritimoTotal);

					 printf("|%-10d|	%-10s|	%-10s|	%-10s|	%-10s|	%-10.2f|	%-10.2f|	%-10.2f|	%-10.2f|	%-10.2f|	%-10d|	%-10f USD	|	%-10f USD\n", art_getIdArticulo(pA, &flag), art_getCodigo(pA, &flag),
																																art_getNombre(pA, &flag), art_getDescripcion(pA, &flag),
																																art_getPaisFabricacion(pA, &flag), art_getValorFob(pA, &flag),
																																art_getPeso(pA, &flag), art_getAncho(pA, &flag),
																																art_getAlto(pA, &flag), art_getProfundidad(pA, &flag),
																																art_getIdPosicionArancelaria(pA, &flag), art_getValorMaritimo(pA, &flag), art_getValorAereo(pA, &flag));


				}
			}
		}
		ll_deleteLinkedList(pL);
		controller_saveArticulosText(pFileArt, pArt);
	}
	return ret;
}


int controller_sort (Dictionary* pArt, char* pFile)
{
	int ret = -1;
	int opcion;
	LinkedList* pL;
	if(pArt!= NULL)
	{
		pL = dict_getValues(pArt);
		do
		{
			if(!utn_getNumeroInt(&opcion,
					"\n\t---------------------------------------------------------------"
					"\n\t\t***** MENU DE ORDENAMIENTO*****							\n"
					"\n\t*	1. Ordenar por nombre.\t\t\t*"
					"\n\t*	2. Ordenar por precio FOB.\t\t\t*"
					"\n\t*	10. Salir.\t\t\t\t*"
					"\n\t---------------------------------------------------------------\n\n",
							"Opcion incorrecta", 0, 11, 3))
			{
				switch (opcion)
				{
					case 1:
						if(ll_sort(pL, art_funcionCriterioSortNombre, 1)==0)
						{
							printf("\nDatos ordenados exitosamente");
							controller_imprimirListaArticulosSort(pL);
						}
						break;
					case 2:
						if (ll_sort(pL, art_funcionCriterioSortFob, 1)==0)
						{
							controller_imprimirListaArticulosSort(pL);
							printf("\nDatos ordenados FOB");
						}
						break;
					case 3:
						break;
				}

			}
		}while(opcion!=10);
		ret = 0;
	}
	ll_deleteLinkedList(pL);
	return ret;
}


int controller_imprimirListaFiltradaPosAran(Dictionary* posicionAranc)
{
	int ret=-1;
	int i;
	int flagError;
	LinkedList* pL;
	PosArancelaria* pPA;
	LinkedList* listaFiltrada;

	// Obtengo empleados del diccionario e imprimo sus datos
	if (posicionAranc != NULL)
	{
		pL = dict_getValues(posicionAranc); //obtengo la dir de memo de la ll con sus valores
		if(pL!=NULL)
		{
			listaFiltrada = ll_filtrar4(pL, funcionCriterioFiltrarLic);
			funcionImprimirProlijoPosAranc();

			for (i=0; i<ll_len(listaFiltrada); i++)
			{
				pPA =(PosArancelaria*)ll_get(listaFiltrada, i); //elementos que estan en el ll que estaban en el diccionario
				if(pPA!=NULL)
				{
					printf("|%5d\t|\t%s\t|%-10.3f|\t%-5.3f\t\t|%5.3f\t\t| %s  \n", pos_getIdPosArancelaria(pPA, &flagError), pos_getNomenclatura(pPA, &flagError),
																				pos_getSeguro(pPA, &flagError), pos_getImportacion(pPA, &flagError),
																				pos_getTasaEstadistica(pPA, &flagError), ESTADO[pos_getTipoLicencia(pPA, &flagError)]);
				}
			}
		}
		ll_deleteLinkedList(pL);
		ll_deleteLinkedList(listaFiltrada);
	}
	return ret;
}

int controller_imprimirListaFiltradaArticulos(Dictionary* pArticulos)
{
	int ret=-1;
	int i;
	int flagError;
	LinkedList* pL;
	Articulos* pA;
	LinkedList* listaFiltrada;

	// Obtengo empleados del diccionario e imprimo sus datos
	if (pArticulos != NULL)
	{
		pL = dict_getValues(pArticulos); //obtengo la dir de memo de la ll
		if(pL!=NULL)
		{
			listaFiltrada = ll_filtrar4(pL, funcionCriterioValorFob);
			if(!aplicarDescuentoEnValorFob(listaFiltrada))
			funcionImprimirProlijoArticulos();
			for (i=0; i<ll_len(listaFiltrada); i++)
			{
				pA =(Articulos*)ll_get(listaFiltrada, i); //elementos que estan en el ll que estaban en el diccionario
				if(pA!=NULL)
				{
					printf("|%-10d|	%-10s|	%-10s|	%-10s|	%-10s|	%-10.2f|	%-10.2f|	%-10.2f|	%-10.2f|	%-10.2f|	%-10d\n", art_getIdArticulo(pA, &flagError), art_getCodigo(pA, &flagError),
																																art_getNombre(pA, &flagError), art_getDescripcion(pA, &flagError),
																																art_getPaisFabricacion(pA, &flagError), art_getValorFob(pA, &flagError),
																																art_getPeso(pA, &flagError), art_getAncho(pA, &flagError),
																																art_getAlto(pA, &flagError), art_getProfundidad(pA, &flagError),
																																art_getIdPosicionArancelaria(pA, &flagError));
				}
			}
		}
		ll_deleteLinkedList(pL);
		ll_deleteLinkedList(listaFiltrada);
	}
	return ret;
}

int funcionCriterioValorFob(void* pGenerico)
{
	Articulos* pA;
	pA = (Articulos*) pGenerico;
	int fob, flag;

	fob = art_getValorFob(pA, &flag);
	if (fob>=10)
	{
		return 1;
	}
	return 0;
}
int aplicarDescuentoEnValorFob (LinkedList* listaFiltrada)
{
	int ret = -1;
	Articulos* pA;
	int flag;
	int i;
	float valorFob, descuento;

	for(i=0; i<ll_len(listaFiltrada); i++)
	{
		pA = (Articulos*) ll_get(listaFiltrada, i);
		valorFob = art_getValorFob(pA, &flag);
		descuento = (PORC_DESC*valorFob)/100;
		valorFob = valorFob - descuento;
		printf("\n\nVALOR FOB: %f", valorFob);
		art_setValorFob(pA, valorFob);
		ret = 0;
	}
	return ret;
}

int funcionCriterioFiltrarLic(void* pGenerico)
{
	PosArancelaria* pPA;
	pPA = (PosArancelaria*) pGenerico;
	int lic, flag;

	lic = pos_getTipoLicencia(pPA, &flag);
	if (lic==0)
	{
		return 1;
	}
	return 0;
}

float controller_buscarMayor (Dictionary* pArt)
{
	Articulos* pA;
	LinkedList* pL;
	float fob,max;
	int flag;
	float ret=-1;

	if (pArt!= NULL)
	{
		pL = dict_getValues(pArt);
		if (pL!=NULL)
		{
			for (int i=0; i<ll_len(pL); i++)
			{
				pA =(Articulos*)ll_get(pL, i);
				fob = art_getValorFob(pA, &flag);
				if (i ==0 || fob > max)
					max = fob;
			}
		}
	}
	ll_deleteLinkedList(pL);
	printf("\nEl mayor valor fob es: %.3f", max);
	return ret;
}

float controller_buscarMayorCostoArgAereo(Dictionary* pArt, Dictionary* pPosAranc, Aereo* pAereo)
{
	Articulos* pA;
	LinkedList* pL;
	LinkedList* pPOS;
	PosArancelaria* pPA;
	float max= 0;
	float ret=-1;
	char* descripcion;
	float valorFob;
	int flag, posAranc;

	if (pArt!= NULL && pPosAranc!=NULL && pAereo!=NULL)
	{
		pL = dict_getValues(pArt);
		pPOS = dict_getValues(pPosAranc);
		if (pL!=NULL && pPOS !=NULL)
		{
			for (int i=0; i<ll_len(pPOS); i++)
			{
				pPA = (PosArancelaria*) ll_get(pPOS, i);
				max = 0; //se reinicia el max para cada pos Aranc
				for (int j=0; j<ll_len(pL); j++)
				{
					pA = (Articulos*)ll_get(pL, j);

					if(pA->idPosicionArancelaria == pPA->idPosArancelaria)
					{
						if (pA->valorAereo > max)
						{
							max = pA->valorAereo;
							descripcion=art_getDescripcion(pA, &flag);
							valorFob =art_getValorFob(pA, &flag);
							posAranc = art_getIdPosicionArancelaria(pA, &flag);
							ret = 0;
						}
					}
				}
				printf("\nID POS ARANC: %d - DESCRIPCION: %s - VALOR FOB: %.3f - COSTO ARG AEREO: %f\n", posAranc,descripcion, valorFob, max);
			}
		}
		ll_deleteLinkedList(pL);
		ll_deleteLinkedList(pPOS);
	}
	return ret;
}

// ****************************************************
float controller_ordenarPorNombreCadaPosAranc(Dictionary* pArt, Dictionary* pPosAranc, Aereo* pAereo)
{
	Articulos* pA;
	LinkedList* pL;
	LinkedList* pPOS;
	float ret=-1;
	int flag;

	if (pArt!= NULL && pPosAranc!=NULL && pAereo!=NULL)
	{
		pL = dict_getValues(pArt);
		pPOS = dict_getValues(pPosAranc);
		if (pL!=NULL && pPOS !=NULL)
		{
			for (int i=1; i<=ll_len(pPOS); i++)
			{
				for (int j=0; j<ll_len(pL); j++)
				{
					pA = (Articulos*)ll_get(pL, j);

					if(pA->idPosicionArancelaria == i)
					{
						if (ll_sort(pL, art_funcionCriterioSortNombre, 1) ==0)
						{
							printf("\nPOS ARA: %d - NOMBRE: %s", art_getIdPosicionArancelaria(pA, &flag),art_getNombre(pA, &flag));
							ret =0;
						}
					}
				}

				//printf("\nDESCRIPCION: %s - VALOR FOB: %.3f - COSTO ARG AEREO: %f\n", descripcion, valorFob, max);
			}
		}
		controller_imprimirListaArticulosSort(pL);

		ll_deleteLinkedList(pL);
		ll_deleteLinkedList(pPOS);
	}
	return ret;
}



int controller_buscarNomenclatura(Dictionary* pPosAranc, Dictionary* pArt)
{
	int ret = -1;
	PosArancelaria* pPA;
	LinkedList* pL;
	LinkedList* pLArt;
	Articulos* pA;
	char nomenclatura[2000];
	int flagError;
	//int idPA;

	if (pPosAranc!=NULL)
	{
		pL = dict_getValues(pPosAranc);
		if(utn_getTextoNumerosCaracter(nomenclatura, 2000, "\nIngrese nomenclatura", "\nError\n", 3)==0)
		{
			for (int i=0; i<ll_len(pL); i++)
			{
				pPA = ll_get(pL, i);
				if (strcmp (pPA->nomenclaturaAranc,nomenclatura)==0)
				{
					funcionImprimirProlijoPosAranc();
					printf("|%5d\t|\t%s\t|%-10.3f|\t%-5.3f\t\t|%5.3f\t\t| %s  \n", pos_getIdPosArancelaria(pPA, &flagError), pos_getNomenclatura(pPA, &flagError),
																					pos_getSeguro(pPA, &flagError), pos_getImportacion(pPA, &flagError),
																					pos_getTasaEstadistica(pPA, &flagError), ESTADO[pos_getTipoLicencia(pPA, &flagError)]);
					//idPA = pPA->idPosArancelaria;
					pLArt = dict_getValues(pArt);
					printf("\n\nARTICULOS ASOCIADOS A LA NOMENCLATURA SOLICITADA: \n\n");
					funcionImprimirProlijoArticulos();
					for (int j=0; j<ll_len(pLArt); j++)
					{
						pA = (Articulos*) ll_get(pLArt, j);
						if (pA->idPosicionArancelaria == pPA->idPosArancelaria)
						{
							printf("|%-10d|	%-10s|	%-10s|	%-10s|	%-10s|	%-10f|	%-10.3f|	%-10.3f|	%-10.3f|	%-10.3f|	%-10d\n", art_getIdArticulo(pA, &flagError), art_getCodigo(pA, &flagError),
																																		art_getNombre(pA, &flagError), art_getDescripcion(pA, &flagError),
																																		art_getPaisFabricacion(pA, &flagError), art_getValorFob(pA, &flagError),
																																		art_getPeso(pA, &flagError), art_getAncho(pA, &flagError),
																																		art_getAlto(pA, &flagError), art_getProfundidad(pA, &flagError),
																																		art_getIdPosicionArancelaria(pA, &flagError));
						}
					}
				}
			}
		}
	}
	ll_deleteLinkedList(pL);
	ll_deleteLinkedList(pLArt);
	return ret;
}

/*
float aplicarDescuento (LinkedList* listaFiltrada, Dictionary* pArt)
{
	int ret = -1;
	LinkedList* pLarticulos;
	Articulos* pArticulos;
	int flag, i, j;
	float descuento, precioFob;
	PosArancelaria* pPA;
	int idABuscar;
	if (listaFiltrada != NULL)
	{
		pLarticulos = dict_getValues(pArt);
		for (i=0 ; i<ll_len(listaFiltrada); i++)
		{
			pPA = (PosArancelaria*) ll_get(listaFiltrada, i);
			idABuscar = pPA->idPosArancelaria; //de la lista filtrada obtengo el id de cada pos Aran con lic auto

			printf("\nID %d\n",idABuscar);

				pArticulos = (Articulos*) ll_get(pLarticulos, i);
				if (pArticulos->idPosicionArancelaria == idABuscar)
				{
					precioFob = art_getValorFob(pArticulos, &flag);
					printf("PRECIO OBTENIDO: %f", precioFob);
					descuento = (PORC_DESC*precioFob)/100;
					precioFob = precioFob - descuento;
					printf("\n\nVALOR FOB: %f", precioFob);
					art_setValorFob(pArticulos, precioFob);
					ret = 0;
				}
		}
	}
	return ret;
}
*/

/*
int controller_saveArticulosTextLL(char* pFile, LinkedList* articulos)
{
	int ret = -1;
	int i;
	int flag;
	FILE* fpArchivo;
	Articulos* pA;
	fpArchivo = fopen(pFile, "w");

	if(fpArchivo!=NULL)
	{
		fprintf(fpArchivo,"id,codigo,nombre,descripcion,pais,valorFob,peso,ancho,alto,profundidad,idPA\n");
		for(i=0; i<ll_len(articulos); i++)
		{
			pA = (Articulos*) ll_get(articulos, i);
			if(pA!=NULL)
			{
				fprintf(fpArchivo, "%d,%s,%s,%s,%s,%.2f,%.2f,%.2f,%.2f,%.2f,%d\n",art_getIdArticulo(pA, &flag), art_getCodigo(pA, &flag),
																				art_getNombre(pA, &flag), art_getDescripcion(pA, &flag),
																				art_getPaisFabricacion(pA, &flag), art_getValorFob(pA, &flag),
																				art_getPeso(pA, &flag), art_getAncho(pA, &flag),
																				art_getAlto(pA, &flag), art_getProfundidad(pA, &flag),
																				art_getIdPosicionArancelaria(pA, &flag));
				ret =0;
			}
		}
		fclose(fpArchivo);
	}
	return ret;
}
*/

