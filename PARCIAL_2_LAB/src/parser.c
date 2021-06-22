/*
 * parser.c
 *
 *  Created on: 18 jun. 2021
 *      Author: ludmi
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Articulos.h"
#include "utn.h"
#include "Dictionary.h"
#include "LinkedList.h"
#include "PosArancelaria.h"
#include "Maritimo.h"
#include "Aereo.h"
#define COD_LEN 200
#define DESC_LEN 100
#define PAIS_LEN 100
#define NOM_LEN 100

int parser_ArticulosFromText (FILE* pFile, Dictionary* articulos)
{
	char codigo[COD_LEN];
	char descripcion[DESC_LEN];
	char paisFabricacion[PAIS_LEN];
	char nombre[NOM_LEN];
	char idPosAranc[200];
	char idAux[100];
	char valorFob[2000], peso[2000], ancho[3000], alto[2000], profundidad[2000];
	int idArt;
	Articulos* pA=NULL;
	int indice = -1;
	int idMaxAux;
	if(pFile!=NULL && articulos!=NULL)
	{
		indice =0;
		do
		{
			if (fscanf(pFile, "%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^\n]\n", idAux, codigo, nombre, descripcion, paisFabricacion, valorFob,peso, ancho, alto ,profundidad, idPosAranc )==11)
			{
				if(esNumerica(idAux, 5000)==1)
				{
					pA= art_newParam(codigo, descripcion, paisFabricacion, nombre, atof(valorFob), atof(peso), atof(ancho), atof(alto), atof(profundidad), atoi(idAux), atoi(idPosAranc));
					if(pA != NULL)
					{
						dict_insert(articulos, idAux, pA);
					}
					idArt = atoi(idAux);
					if(indice==0)
						idMaxAux= idArt;
					else if(idArt > idMaxAux)
						idMaxAux = idArt;

					indice++;
				}
			}
		}while(!feof(pFile));
	}
	return idMaxAux;
}
int parser_PosArancFromText(FILE* pFile, Dictionary* posAranc)
{
	char nomenclaturaAranc[200];
	char seguro[200], importacion[200],tasaEstadistica[200], tipoLicencia[200], idPosArancelaria[200];
	PosArancelaria* pPosAra= NULL;
	int indice=-1;
	int idMaxAux;

	if(pFile!=NULL && posAranc!=NULL)
	{
		do
		{
			indice =0;
			if (fscanf(pFile, "%[^,],%[^,],%[^,],%[^,],%[^,],%[^\n]\n", idPosArancelaria, nomenclaturaAranc, seguro, importacion, tasaEstadistica, tipoLicencia)==6)
			{
				if(esNumerica(idPosArancelaria, 5000)==1)
				{
					pPosAra= pos_newParam(nomenclaturaAranc, atof(seguro), atof(importacion), atof(tasaEstadistica), atoi(tipoLicencia), atoi(idPosArancelaria));
					if(pPosAra != NULL)
					{
						dict_insert(posAranc, idPosArancelaria, pPosAra);
					}
					if(indice==0)
						idMaxAux= atoi(idPosArancelaria);
					else if(atoi(idPosArancelaria) > idMaxAux)
						idMaxAux = atoi(idPosArancelaria);
					indice++;
				}
			}
		}while(!feof(pFile));
	}
	return idMaxAux;
}

int parser_TranspMarFromText(FILE* pFile, Maritimo* transpMar)
{
	int ret =-1;
	char precio[200];
	char volumen[200];
	int indice=-1;

	if(pFile!=NULL && transpMar!=NULL)
	{
		do
		{
			indice =0;
			if (fscanf(pFile, "%[^,],%[^\n]\n", precio, volumen)==2)
			{
				mar_newParam(transpMar,atof(volumen),atof(precio));
				ret = 0;
				indice++;

			}
		}while(!feof(pFile));
	}
	return ret;
}
int parser_TranspAereoFromText(FILE* pFile, Aereo* transpAereo)
{
	int ret =-1;
	char constante[200];
	char precio[200];

	if(pFile!=NULL && transpAereo!=NULL)
	{
		do
		{
			if (fscanf(pFile, "%[^,],%[^\n]\n", constante, precio)==2)
			{
				aer_newParam(transpAereo,atof(constante),atof(precio));
				ret = 0;
			}
		}while(!feof(pFile));
	}
	return ret;
}









