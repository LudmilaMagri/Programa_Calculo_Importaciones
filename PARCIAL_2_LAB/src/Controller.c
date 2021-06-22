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

	printf("\n|%-10s|	%-10s|	%-10s|	%-10s|	%-10s|	%-10s|	%-10s|	%-10s|	%-10s|	%-10s|	%-10s\n", id, codigo, nombre, desc, pais, fob, peso, ancho,alto, prof,idPA);
	printf("|-----------------------------------------------------------------------------------------------------------------------------------------------------------------------|\n");

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
		fprintf(fpArchivo,"id,codigo,nombre,descripcion,pais,valorFob,peso,ancho,alto,profundidad,idPA\n");
		pL = dict_getValues(articulos);
		if(pL!=NULL)
		{
			for(i=0; i<ll_len(pL); i++)
			{
				pA = (Articulos*) ll_get(pL, i);
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


int controller_printCostoArgMaritimoAereo(Dictionary* pArt, Dictionary* pPosAranc, Maritimo* pMar, Aereo* pAereo)
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
					 printf("|%-10d|	%-10s|	%-10s|	%-10s|	%-10s|	%-10.2f|	%-10.2f|	%-10.2f|	%-10.2f|	%-10.2f|	%-10d|	%-10f USD	|	%-10f USD\n", art_getIdArticulo(pA, &flag), art_getCodigo(pA, &flag),
																																art_getNombre(pA, &flag), art_getDescripcion(pA, &flag),
																																art_getPaisFabricacion(pA, &flag), art_getValorFob(pA, &flag),
																																art_getPeso(pA, &flag), art_getAncho(pA, &flag),
																																art_getAlto(pA, &flag), art_getProfundidad(pA, &flag),
																																art_getIdPosicionArancelaria(pA, &flag), costoArgMaritimoTotal, costoArgAereoTotal);
				}
			}
		}
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
					"\n\t*	2. Ordenar por ID.\t\t\t*"
					"\n\t*	3. Ordenar por codigo.\t\t\t*"
					"\n\t*	4. Ordenar por valor FOB.\t*"
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
	return ret;
	ll_deleteLinkedList(pL);
}


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
		pL = dict_getValues(posicionAranc); //obtengo la dir de memo de la ll
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
/*
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
			//listaFiltrada = ll_filtrar4(pL, funcionCriterioElMayor);
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
*/
int controller_aplicarListaFiltrada(Dictionary* pArrayListPosAranc)
{
	int ret;
	LinkedList* listaFiltrada;
	LinkedList* pPA;
	pPA = dict_getValues(pArrayListPosAranc);
	if (pArrayListPosAranc!=NULL && pPA!=NULL)
	{
		listaFiltrada = ll_filtrar4(pPA, funcionCriterioFiltrarLic);
		//aplico lo que sea (listaFiltrada);
		ll_deleteLinkedList(listaFiltrada);
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
	if (lic==1)
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
				if (i ==0)
					max = fob;
				else if (fob>max)
				{
					max = fob;
					ret= max;
				}
			}
		}
	}
	printf("\nEl mayor valor fob es: %.3f", max);
	return ret;
}

float controller_buscarMayorCostoArgMaritimo(Dictionary* pArt, Dictionary* pPosAranc, Maritimo* pTransMar)
{
	Articulos* pA;
	LinkedList* pL;
	PosArancelaria* pPA;
	float max;
	float ret=-1;
	float totalCostArgMar;
	int idPA, flag;
	char keyPA[32];

	if (pArt!= NULL && pPosAranc!=NULL && pTransMar!=NULL)
	{
		pL = dict_getValues(pArt);
		if (pL!=NULL)
		{
			funcionImprimirProlijoCostoArgentino();
			for (int i=0; i<ll_len(pL); i++)
			{
				pA =(Articulos*)ll_get(pL, i);
				idPA = pA->idPosicionArancelaria;
				sprintf (keyPA, "%d", idPA);
				pPA = dict_get(pPosAranc, keyPA);
				if (pPA!=NULL)
				{
					totalCostArgMar = calcularCostoArgentinoMaritimo(pPA,pA, pTransMar);
				}
				if (i ==0)
					max = totalCostArgMar;
				else if (totalCostArgMar>max)
				{
					max = totalCostArgMar;
					ret= max;
				}
			}
		}
	}
	printf("|%-10d|	%-10s|	%-10s|	%-10s|	%-10s|	%-10.2f|	%-10.2f|	%-10.2f|	%-10.2f|	%-10.2f|	%-10d|	%-10f USD\n", art_getIdArticulo(pA, &flag), art_getCodigo(pA, &flag),
																																				art_getNombre(pA, &flag), art_getDescripcion(pA, &flag),
																																				art_getPaisFabricacion(pA, &flag), art_getValorFob(pA, &flag),
																																				art_getPeso(pA, &flag), art_getAncho(pA, &flag),
																																				art_getAlto(pA, &flag), art_getProfundidad(pA, &flag),
																																				art_getIdPosicionArancelaria(pA, &flag), max);
	printf("\nEl mayor costo arg maritimo es: %f USD", max);
	return ret;
}
/*
 * if(bufferInt<min)
	{
		min=bufferInt;
	}
 * */

