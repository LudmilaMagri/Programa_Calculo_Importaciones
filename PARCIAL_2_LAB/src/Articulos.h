/*
 * Articulos.h
 *
 *  Created on: 15 jun. 2021
 *      Author: ludmi
 */

#ifndef ARTICULOS_H_
#define ARTICULOS_H_
#define COD_LEN 200
#define DESC_LEN 100
#define PAIS_LEN 100
#define NOM_LEN 100
typedef struct
{
	char codigo[COD_LEN];
	char descripcion[DESC_LEN];
	char paisFabricacion[PAIS_LEN];
	char nombre[NOM_LEN];
	float valorFob;
	float peso;
	float ancho;
	float alto;
	float profundidad;
	int idArticulo;
	int idPosicionArancelaria;
	float valorAereo;
	float valorMaritimo;
}Articulos;

Articulos* art_new(void);
Articulos* art_newParam(char* codigo,char* descripcion,char* paisFabricacion, char* nombre, float valorFob, float peso, float ancho,
						float alto, float profundidad, int idArticulo, int idPosicionArancelaria, float valorAereo, float valorMaritimo);

int art_delete(Articulos* this);

int art_setCodigo(Articulos* this,char* codigo);
char* art_getCodigo(Articulos* this,int* flagError);
int isValidCodigo(char*);

int art_setDescripcion(Articulos* this,char* descripcion);
char* art_getDescripcion(Articulos* this,int* flagError);
int isValidDescripcion(char*);

int art_setPaisFabricacion(Articulos* this,char* paisFabricacion);
char* art_getPaisFabricacion(Articulos* this,int* flagError);
int isValidPaisFabricacion(char*);

int art_setNombre(Articulos* this, char* nombre);
char* art_getNombre(Articulos* this,int* flagError);
int art_getNombre2(Articulos* this, char* nombre);
int isValidNombre(char*);

float art_setValorFob(Articulos* this, float valorFob);
float art_getValorFob(Articulos* this,int* flagError);
int isValidValorFob(float);

float art_setPeso(Articulos* this, float peso);
float art_getPeso(Articulos* this,int* flagError);
int isValidPeso(float);

float art_setAncho(Articulos* this, float ancho);
float art_getAncho(Articulos* this,int* flagError);
int isValidAncho(float);

float art_setAlto(Articulos* this, float alto);
float art_getAlto(Articulos* this,int* flagError);
int isValidAlto(float);

float art_setProfundidad(Articulos* this, float profundidad);
float art_getProfundidad(Articulos* this,int* flagError);
int isValidProfundidad(float);

int art_setIdArticulo(Articulos* this,int idArticulo);
int art_getIdArticulo(Articulos* this,int* flagError);
int isValidIdArticulo(int);

int art_setIdPosicionArancelaria(Articulos* this,int idPosicionArancelaria);
int art_getIdPosicionArancelaria(Articulos* this,int* flagError);
int isValidIdPosicionArancelaria(int);

float art_setValorAereo(Articulos* this, float valorAereo);
float art_getValorAereo(Articulos* this,int* flagError);
float art_setValorMaritimo(Articulos* this, float valorMaritimo);
float art_getValorMaritimo(Articulos* this,int* flagError);


int art_generarId(void);
void art_setearValorInicialDeId(int id);
int funcionCriterioFiltrarHoras(void* pGenerico);

void art_valorInicialId(int id);

#include "Dictionary.h"
int art_addArticulo(Dictionary* pArrayArticulos, Dictionary* pArrayPosAranc, char* pFilePosAra, char* pFileArt);
int art_editArticulo(Dictionary* pArrayArticulos, char* pFileArt);
int art_deleteArticulo(Dictionary* pArrayArticulos, char* pFileArt);



int art_funcionCriterioSortNombre (void* a, void* b);
int art_funcionCriterioSortFob(void*a, void* b);


#endif /* ARTICULOS_H_ */
