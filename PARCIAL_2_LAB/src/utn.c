/*
 * Funciones.c
 *
 */


#include "utn.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<ctype.h>


int getFloat (float* pResultado);
static int getNumeroInt (int* pResultado);
static int getTexto (char* pResultado, int longitud);
 int getString (char* cadena, int longitud);
int esSoloLetras (char* cadena, int longitud);
int esNumerica (char* cadena, int longitud);
int esNumericaFlotante (char* cadena, int longitud);
static int esTarjeta (char* cadena, int longitud);
static int getTarjeta (char* pResultado, int longitud);
static int getDni (char* pResultado, int longitud);
static int esDni (char* cadena, int longitud);
static int esTelefono (char* cadena, int longitud);
static int getTelefono (char* pResultado, int longitud);
static int getCuit (char* pResultado, int longitud);
static int esCuit (char* cadena, int longitud);
static int getDireccion (char* pResultado, int longitud);
static int esAlfaNumerica (char* cadena, int longitud);
int getDescripcion (char* pResultado, int longitud);
int esAlfaNumericaCaracter (char* cadena, int longitud);
static int getSexo (char* pResultado, int longitud);
static int esSexo (char* cadena, int longitud);
static int getEmail (char* pResultado, int longitud);
static int esEmail (char* cadena, int longitud);
static int getFecha(char* pResultado, int longitud);
static int esFecha(char* cadena, int longitud);



int utn_getTextoNumerosCaracter(char* pResultado, int longitud, char* pMensaje, char* pMensajeError, int reintentos)
{
	int output = -1;
	if (pResultado != NULL && pMensaje != NULL && pMensajeError != NULL && longitud > 0 && reintentos > 0) {
		do {
			printf("%s", pMensaje);
			if (!(myGets2(pResultado, longitud))) {
				for(int i = 0; i<longitud; i++){
					pResultado[i] = toupper(pResultado[i]);
				}
				output = 0;
			} else {
				reintentos--;
				if (reintentos > 0) {
					printf("%s: %d\n", pMensajeError, reintentos);
				}
			}
		} while (output != 0 && reintentos > 0);
	}
	return output;
}
int myGets2(char *pCadena, int len) {
    int output = -1;
    char bufferString[4096];

    if (pCadena != NULL && len > 0 && fgets(bufferString, sizeof(bufferString), stdin) != NULL) {
        if (bufferString[0] == '\n') {
            printf("Error, solo ingreso un ENTER\n");
        } else {
            bufferString[strnlen(bufferString, sizeof(bufferString)) - 1] = '\0';
            if (strnlen(bufferString, sizeof(bufferString)) <= len) {
                strncpy(pCadena, bufferString, len);
                output = 0;
            }
        }
    }
    return output;
}
int utn_getStringWithOnlyNumbers(char *msg, char *msgError, char *pCadena, int limite, int reintentos) {
    int output = -1;
    if (msg != NULL && msgError != NULL && pCadena != NULL && limite > 0 && reintentos > 0) {
        do {
            printf("%s", msg);
            if (!(myGets2(pCadena, limite)) && utn_isNumeric(pCadena)) {
                for(int x = 0; x<limite; x++){
                    pCadena[x] = toupper(pCadena[x]);
                }
                output = 0;
            } else {
                reintentos--;
                if (reintentos > 0) {
                    printf("%s: %d\n", msgError, reintentos);
                }
            }
        } while (output != 0 && reintentos > 0);
    }
    return output;
}
int utn_isNumeric(char *pCadena){
    int output = 1;
    if(pCadena !=NULL){
        for(int x = 0; pCadena[x] !='\0'; x++){
            if(pCadena[x] < '0' || pCadena[x] > '9')
            {
                output = 0;
                break;
            }
        }
    }
    return output;
}
/*\brief Solicita Una fecha al usuario, luego de verificarlo devuelve el resultado
 * \param pResultado Puntero al espacio de memoria donde se dejara el resultado de la funcion
 * \param longitud Es la longitud del texto
 * \param pMensaje El mensaje a ser mostrado
 * \param pMensajeError Mensaje a ser mostrado en caso de no ser un texto valido
 * \param reintentos Es la cantidad de reintentos
 * \return retorna 0 si OK, -1 si hay ERROR.
 */
int utn_getFecha(char* pResultado, int longitud, char* pMensaje, char* pMensajeError, int reintentos)
{
	int retorno = -1;
	char buffer[EMAIL_LEN];

	if (pResultado!= NULL && pMensaje != NULL && pMensajeError != NULL && reintentos>= 0){
		do
		{
			printf ("%s", pMensaje);
			if (getFecha(buffer, sizeof (buffer))==0 && reintentos >= 0){
				strncpy(pResultado, buffer, longitud);
				retorno = 0;
				break;
			}
			reintentos--;
			printf ("%s", pMensajeError);
		}while(reintentos >=0);
	}
	return retorno;
}
/**
 * \brief Obtiene un string valido como fecha
 * \param pResultado Array donde se dejara el resultado de la funcion
 * \param longitud Longitud del array
 * \return Retorna 0 (EXITO) y -1 (ERROR)
 */
static int getFecha(char* pResultado, int longitud)
{
	int retorno = -1;
	char buffer [EMAIL_LEN];

	if (pResultado != NULL){
		if (getString (buffer, sizeof (buffer)) == 0 && esFecha(buffer, sizeof (buffer)) && strnlen (buffer, sizeof (buffer)) < longitud){
			strncpy (pResultado, buffer, longitud);
			retorno = 0;
		}
	}
	return retorno;
}
/**
 * \brief Verifica si la cadena ingresada es una fecha valida
 * \param cadena Array a ser analizado
 * \param longitud Longitud del array
 * \return Retorna 1 (verdadero) si la cadena es valida y 0 (falso) si no lo es
 */
static int esFecha(char* cadena, int longitud)
{
    int retorno = 0;
    int i;
    int contadorBarras = 0;
    int contadorGuiones = 0;

    if (cadena != NULL)
    {
        for (i= 0; cadena [i] != '\0'; i++){

            if ((cadena [i] < '0' || cadena [i]> '9') &&(cadena [i] != '/' || cadena [i] != '-'))
            {
                retorno = 0;
            }
            if (cadena[i]== '-')
            {
            	contadorGuiones++;
            }
            if (cadena[i]== '/')
			{
            	contadorBarras++;
			}
            if (contadorGuiones==2 || contadorBarras==2 )
            {
                retorno = 1;
            }
        }
    }
    return retorno;
}
/*
 * \brief Solicita un email al usuario, luego de verificarlo devuelve el resultado
 * \param pResultado Array del email
 * \param longitud Longitud del array
 * \param pMensaje Mensaje
 * \param pMensajeError Mensaje de error
 * \param reintentos Reintentos que tiene el usuario por si el ingreso fue erroneo
 * \return Retorna 0 (EXITO) y -1 (ERROR)
 */
int utn_getEmail (char* pResultado, int longitud, char* pMensaje, char* pMensajeError, int reintentos){
	int retorno = -1;
	char buffer[EMAIL_LEN];

	if (pResultado!= NULL && pMensaje != NULL && pMensajeError != NULL && reintentos>= 0){
		do
		{
			printf ("%s", pMensaje);
			if (getEmail(buffer, sizeof (buffer))==0 && reintentos >= 0){
				strncpy(pResultado, buffer, longitud);
				retorno = 0;
				break;
			}
			reintentos--;
			printf ("%s", pMensajeError);
		}while(reintentos >=0);
	}
	return retorno;
}
/**
 * \brief Obtiene un string valido como email
 * \param pResultado Array donde se dejara el resultado de la funcion
 * \return Retorna 0 (EXITO) y -1 (ERROR)
 */
static int getEmail (char* pResultado, int longitud){
	int retorno = -1;
	char buffer [EMAIL_LEN];

	if (pResultado != NULL){
		if (getString (buffer, sizeof (buffer)) == 0 && esEmail (buffer, sizeof (buffer)) && strnlen (buffer, sizeof (buffer)) < longitud){
			strncpy (pResultado, buffer, longitud);
			retorno = 0;
		}
	}
	return retorno;
}
/**
 * \brief Verifica si la cadena ingresada es un email valida
 * \param cadena Array a ser analizado
 * \param longitud Longitud del array
 * \return Retorna 1 (verdadero) si la cadena es valida y 0 (falso) si no lo es
 */
static int esEmail (char* cadena, int longitud){
	int retorno = 1;
	int i;
	int contadorArroba = 0;

	if (cadena != NULL){
		for (i= 0; cadena [i] != '\0'; i++){

			if ((cadena[i] != '@') && (cadena [i] < 'a' || cadena [i]> 'z') && (cadena [i]< 'A' || cadena [i]> 'Z') &&
				(cadena[i]< '0' || cadena[i]>'9') && (cadena [i] != '.')){
				retorno = 0;
			}
			if (cadena[i]== '@'){
				contadorArroba++;
			}
			if (contadorArroba>1)
				retorno =0;
		}
	}
	return retorno;
}
/*
 * \brief Solicita un sexo al usuario, luego de verificarlo devuelve el resultado
 * \param pResultado Array del sexo
 * \param longitud Longitud del array
 * \param pMensaje Mensaje
 * \param pMensajeError Mensaje de error
 * \param reintentos Reintentos que tiene el usuario por si el ingreso fue erroneo
 * \return Retorna 0 (EXITO) y -1 (ERROR)
 */
int utn_getSexo (char* pResultado, int longitud, char* pMensaje, char* pMensajeError, int reintentos){
	int retorno = -1;
	char buffer[SEX_LEN];

	if (pResultado!= NULL && pMensaje != NULL && pMensajeError != NULL && reintentos>= 0){
		do
		{
			printf ("%s", pMensaje);
			if (getSexo(buffer, sizeof (buffer))==0 && reintentos >= 0){
				strncpy(pResultado, buffer, longitud);
				retorno = 0;
				break;
			}
			reintentos--;
			printf ("%s", pMensajeError);
		}while(reintentos >=0);
	}
	return retorno;
}
/**
 * \brief Obtiene un string valido como sexo
 * \param pResultado Array donde se dejara el resultado de la funcion
 * \param longitud Longitud del array
 * \return Retorna 0 (EXITO) y -1 (ERROR)
 */
static int getSexo (char* pResultado, int longitud){
	int retorno = -1;
	char buffer [SEX_LEN];

	if (pResultado != NULL){
		if (getString (buffer, sizeof (buffer)) == 0 && esSexo (buffer, sizeof (buffer)) && strnlen (buffer, sizeof (buffer)) < longitud){
			strncpy (pResultado, buffer, longitud);
			retorno = 0;
		}
	}
	return retorno;
}
/**
 * \brief Verifica si la cadena ingresada es un sexo valido
 * \param cadena Array a ser analizado
 * \param longitud Longitud del array
 * \return Retorna 1 (verdadero) si la cadena es valida y 0 (falso) si no lo es
 *
 */
static int esSexo (char* cadena, int longitud){
	int retorno = 1;
	int i;
	if (cadena != NULL){
		for (i= 0; cadena [i] != '\0'; i++){
			if ((cadena[i] != 'f' && cadena [i] != 'm' && cadena [i]!= 'F' && cadena [i]!= 'M')){
				retorno = 0;
			}
		}
	}
	return retorno;
}
/*
 * \brief Solicita una descripcion al usuario, luego de verificarla devuelve el resultado
 * \param pResultado Array de la descripcion
 * \param longitud Longitud del array
 * \param pMensaje Mensaje
 * \param pMensajeError Mensaje de error
 * \param reintentos Reintentos que tiene el usuario por si el ingreso fue erroneo
 * \return Retorna 0 (EXITO) y -1 (ERROR)
 */
int utn_getDescripcion (char* pResultado, int longitud, char* pMensaje, char* pMensajeError, int reintentos){
	int retorno = -1;
	char buffer[10000];
	if (pResultado!= NULL && pMensaje != NULL && pMensajeError != NULL && reintentos>= 0){
		do
		{
			printf ("%s", pMensaje);
			if (getDescripcion(buffer, sizeof (buffer))==0 && reintentos >= 0){
				strncpy(pResultado, buffer, longitud);
				retorno = 0;
				break;
			}
			reintentos--;
			printf ("%s", pMensajeError);
		}while(reintentos >=0);
	}
	return retorno;
}
/**
 * \brief Obtiene un string valido como descripcion
 * \param pResultado Array donde se dejara el resultado de la funcion
 * \param longitud Longitud del array
 * \return Retorna 0 (EXITO) y -1 (ERROR)
 */
int getDescripcion (char* pResultado, int longitud){
	int retorno = -1;
	char buffer [100000];
	if (pResultado != NULL){
		if (getString (buffer, sizeof (buffer)) == 0 && esAlfaNumericaCaracter (buffer, sizeof (buffer)) && strnlen (buffer, sizeof (buffer)) < longitud){
			strncpy (pResultado, buffer, longitud);
			retorno = 0;
		}
	}
	return retorno;
}
/*
 * \brief Solicita una direccion al usuario, luego de verificarla devuelve el resultado
 * \param pResultado Array de la direccion
 * \param longitud Longitud del array
 * \param pMensaje Mensaje a ser mostrado
 * \param pMensajeError Mensaje de error a ser mostrado
 * \param reintentos Reintentos que tiene el usuario por si el ingreso fue erroneo
 * \return Retorna 0 (EXITO) y -1 (ERROR)
 */

int utn_getDireccion (char* pResultado, int longitud, char* pMensaje, char* pMensajeError, int reintentos){
	int retorno = -1;
	char buffer[DIREC_LEN];

	if (pResultado!= NULL && pMensaje != NULL && pMensajeError != NULL && reintentos>= 0){
		do
		{
			printf ("%s", pMensaje);
			if (getDireccion(buffer, sizeof (buffer))==0 && reintentos >= 0){
				strncpy(pResultado, buffer, longitud);
				retorno = 0;
				break;
			}
			reintentos--;
			printf ("%s", pMensajeError);
		}while(reintentos >=0);
	}
	return retorno;
}
/**
 * \brief Obtiene un string valido como direccion
 * \param pResultado Array donde se dejara el resultado de la funcion
 * \param longitud Longitud del array
 * \return Retorna 0 (EXITO) y -1 (ERROR)
 */
static int getDireccion (char* pResultado, int longitud){
	int retorno = -1;
	char buffer [DIREC_LEN];
	if (pResultado != NULL){
		if (getString (buffer, sizeof (buffer)) == 0 && esAlfaNumerica (buffer, sizeof (buffer)) && strnlen (buffer, sizeof (buffer)) < longitud){
			strncpy (pResultado, buffer, longitud);
			retorno = 0;
		}
	}
	return retorno;
}
/**
 * \brief Verifica si la cadena ingresada contiene solo numeros y letras.
 * \param cadena Array a ser analizado
 * \param longitud Longitud del array
 * \return Retorna 1 (verdadero) si la cadena es valida y 0 (falso) si no lo es
 */
static int esAlfaNumerica (char* cadena, int longitud){
	int retorno = 1;
	int i;
	if (cadena != NULL){
		for (i= 0; cadena [i] != '\0'; i++){
			if ((cadena[i] != ' ') && (cadena [i] < 'a' || cadena [i]> 'z') && (cadena [i]< 'A' || cadena [i]> 'Z') &&
				(cadena[i]< '0' || cadena[i]>'9')){
				retorno = 0;
				break;
			}
		}
	}
	return retorno;
}
/**
 * \brief Verifica si la cadena ingresada contiene letras en minusculas, mayusculas, numeros, espacios y puntos.
 * \param cadena Array a ser analizado
 * \param longitud Longitud del array
 * \return Retorna 1 (verdadero) si la cadena es valida y 0 (falso) si no lo es
 */
int esAlfaNumericaCaracter (char* cadena, int longitud){
	int retorno = 1;
	int i;
	if (cadena != NULL){
		for (i= 0; cadena [i] != '\0'; i++){
			if ((cadena[i] < '0' || cadena[i] > 'z')
				&& (cadena[i] > '9' || cadena[i] < 'A')
				&& (cadena[i] > 'Z' || cadena[i] < 'a') && (cadena[i] != ' '))
			{
				retorno = 0;
			}
		}
	}
	return retorno;
}
/*
 * \brief Solicita un cuit al usuario, luego de verificarlo devuelve el resultado
 * \param pResultado Array de la direccion
 * \param longitud Longitud del array
 * \param pMensaje Mensaje a ser mostrado
 * \param pMensajeError Mensaje de error a ser mostrado
 * \param reintentos Reintentos que tiene el usuario por si el ingreso fue erroneo
 * \return Retorna 0 (EXITO) y -1 (ERROR)
 */
int utn_getCuit (char* pResultado, int longitud, char* pMensaje, char* pMensajeError, int reintentos){
	int retorno = -1;
	char buffer[14];
	if (pResultado!= NULL && pMensaje != NULL && pMensajeError != NULL && reintentos>= 0){
		do
		{
			printf ("%s", pMensaje);
			if (getCuit(buffer, sizeof (buffer))==0 && reintentos >= 0){
				strncpy(pResultado, buffer, longitud);
				retorno = 0;
				break;
			}
			reintentos--;
			printf ("%s", pMensajeError);
		}while(reintentos >=0);
	}
	return retorno;
}
/**
 * \brief Obtiene un string valido como cuit
 * \param pResultado Array donde se dejara el resultado de la funcion
 * \param longitud Longitud del array
 * \return Retorna 0 (EXITO) y -1 (ERROR)
 */
static int getCuit (char* pResultado, int longitud){
	int retorno = -1;
	char buffer [14];
	if (pResultado != NULL){
		if (getString (buffer, sizeof (buffer)) == 0 && esCuit (buffer, sizeof (buffer)) && strnlen (buffer, sizeof (buffer)) < longitud){
			strncpy (pResultado, buffer, longitud);
			retorno = 0;
		}
	}
	return retorno;
}
/**
 * \brief Verifica si la cadena ingresada contiene numeros y guiones en la posicion del array: 2, 10 u 11.
 * \param cadena Array a ser analizado
 * \param longitud Longitud del array
 * \return Retorna 1 (verdadero) si la cadena es valida y 0 (falso) si no lo es
 */
static int esCuit (char* cadena, int longitud){
	int retorno = 0;
	int i;
	int contadorGuiones = 0;
	if (cadena != NULL){
		if (cadena [2] == '-' && (cadena [11] == '-' || cadena [10] == '-')){
			retorno = 1;
			for (i=0; cadena [i] != '\0'; i++){
				if ((cadena[i] >= '0' || cadena[i] <= '9') && (cadena [i]== '-')){
					retorno = 1;
					contadorGuiones++;
				}
			}
			if (contadorGuiones>2 || contadorGuiones<2)
			retorno = 0;
		}
	}
	return retorno;
}
/*
 * \brief Solicita un telefono al usuario, luego de verificarla devuelve el resultado
 * \param pResultado Array de la direccion
 * \param longitud Longitud del array
 * \param pMensaje Mensaje a ser mostrado
 * \param pMensajeError Mensaje de error a ser mostrado
 * \param reintentos Reintentos que tiene el usuario por si el ingreso fue erroneo
 * \return Retorna 0 (EXITO) y -1 (ERROR)
 */
int utn_getTelefono (char* pResultado, int longitud, char* pMensaje, char* pMensajeError, int reintentos){
	int retorno = -1;
	char buffer[4501];
	if (pResultado!= NULL && pMensaje != NULL && pMensajeError != NULL && reintentos>= 0){
		do
		{
			printf ("%s", pMensaje);
			if (getTelefono(buffer, sizeof (buffer))==0 && reintentos >= 0){
				strncpy(pResultado, buffer, longitud);
				retorno = 0;
				break;
			}
			reintentos--;
			printf ("%s", pMensajeError);
		}while(reintentos >=0);
	}
	return retorno;
}
/**
 * \brief Obtiene un string valido como telefono
 * \param pResultado Array donde se dejara el resultado de la funcion
 * \param longitud Longitud del array
 * \return Retorna 0 (EXITO) y -1 (ERROR)
 */
static int getTelefono (char* pResultado, int longitud){
	int retorno = -1;
	char buffer [4050];
	if (pResultado != NULL){
		if (getString (buffer, sizeof (buffer)) == 0 && esTelefono (buffer, sizeof (buffer)) && strnlen (buffer, sizeof (buffer)) < longitud){
			strncpy (pResultado, buffer, longitud);
			retorno = 0;
		}
	}
	return retorno;
}
/**
 * \brief Verifica si la cadena ingresada contiene numeros y un guion.
 * \param cadena Array a ser analizado
 * \param longitud Longitud del array
 * \return Retorna 1 (verdadero) si la cadena es valida y 0 (falso) si no lo es
 */
static int esTelefono (char* cadena, int longitud){
	int retorno = 0;
	int i;
	int contadorGuiones = 0;
	if (cadena != NULL){
		for (i=0 ; i<longitud && cadena[i] != '\0';i++)
		{
			if ((cadena[i] > '9' || cadena[i] < '0') &&(cadena [i] != '-')){
				retorno = 0;
				break;
			}
			if (cadena[i] == '-')
				contadorGuiones++;
		}
		if (contadorGuiones == 1)
			retorno =1;
	}
	return retorno;
}
/*
 * \brief Solicita un dni al usuario, luego de verificarla devuelve el resultado
 * \param pResultado Array de la direccion
 * \param longitud Longitud del array
 * \param pMensaje Mensaje a ser mostrado
 * \param pMensajeError Mensaje de error a ser mostrado
 * \param reintentos Reintentos que tiene el usuario por si el ingreso fue erroneo
 * \return Retorna 0 (EXITO) y -1 (ERROR)
 */
int utn_getDni (char* pResultado, int longitud, char* pMensaje, char* pMensajeError, int reintentos){
	int retorno = -1;
	char buffer[DNI_LEN];
	if (pResultado!= NULL && pMensaje != NULL && pMensajeError != NULL && reintentos>= 0){
		do
		{
			printf ("%s", pMensaje);
			if (getDni(buffer, sizeof (buffer))==0 && reintentos >= 0){
				strncpy(pResultado, buffer, longitud);
				retorno = 0;
				break;
			}
			reintentos--;
			printf ("%s", pMensajeError);
		}while(reintentos >=0);
	}
	return retorno;
}
/**
 * \brief Obtiene un string valido como dni
 * \param pResultado Array donde se dejara el resultado de la funcion
 * \param longitud Longitud del array
 * \return Retorna 0 (EXITO) y -1 (ERROR)
 */
static int getDni (char* pResultado, int longitud){
	int retorno = -1;
	char buffer [DNI_LEN];
	if (pResultado != NULL){
		if (getString (buffer, sizeof (buffer)) == 0 && esDni (buffer, sizeof (buffer)) && strnlen (buffer, sizeof (buffer)) < longitud){
			strncpy (pResultado, buffer, longitud);
			retorno = 0;
		}
	}
	return retorno;
}
/**
 * \brief Verifica si la cadena ingresada contiene numeros y 2 puntos
 * \param cadena Array a ser analizado
 * \param longitud Longitud del array
 * \return Retorna 1 (verdadero) si la cadena es valida y 0 (falso) si no lo es
 */
static int esDni (char* cadena, int longitud){
	int retorno = 1;
	int i;
	int contadorPuntos= 0;
	if (cadena != NULL){
		for (i=0; i<longitud && cadena[i] != '\0';i++){
			if ((cadena[i] > '9' || cadena[i] < '0') && (cadena[i] != '.' )){
				retorno = 0;
				break;
			}
			if(cadena[i] == '.'){
				contadorPuntos++;
			}
		}
		if (contadorPuntos>=3 || contadorPuntos<=1){
			retorno = 0;
		}
	}
	return retorno;
}
/*
 * \brief Solicita una tarjeta de credito al usuario, luego de verificarla devuelve el resultado
 * \param pResultado Array de la direccion
 * \param longitud Longitud del array
 * \param pMensaje Mensaje a ser mostrado
 * \param pMensajeError Mensaje de error a ser mostrado
 * \param reintentos Reintentos que tiene el usuario por si el ingreso fue erroneo
 * \return Retorna 0 (EXITO) y -1 (ERROR)
 */
int utn_getTarjeta (char* pResultado, int longitud, char* pMensaje, char* pMensajeError, int reintentos){
	int retorno = -1;
	char buffer[4501];
	if (pResultado!= NULL && pMensaje != NULL && pMensajeError != NULL && reintentos>= 0){
		do
		{
			printf ("%s", pMensaje);
			if (getTarjeta(buffer, sizeof (buffer))==0 && reintentos >= 0){
				strncpy(pResultado, buffer, longitud);
				retorno = 0;
				break;
			}
			reintentos--;
			printf ("%s", pMensajeError);
		}while(reintentos >=0);
	}

	return retorno;
}
/**
 * \brief Obtiene un string valido como tarjeta de credito
 * \param pResultado Array donde se dejara el resultado de la funcion
 * \param longitud Longitud del array
 * \return Retorna 0 (EXITO) y -1 (ERROR)
 */
static int getTarjeta (char* pResultado, int longitud){
	int retorno = -1;
	char buffer [4050];
	if (pResultado != NULL){
		if (getString (buffer, sizeof (buffer)) == 0 && esTarjeta (buffer, sizeof (buffer)) && strnlen (buffer, sizeof (buffer)) < longitud){
			strncpy (pResultado, buffer, longitud);
			retorno = 0;
		}
	}
	return retorno;
}
/**
 * \brief Verifica si la cadena ingresada contiene numeros y guiones en la posicion del array: 4, 9 y 14.
 * \param cadena Array a ser analizado
 * \param longitud Longitud del array
 * \return Retorna 1 (verdadero) si la cadena es valida y 0 (falso) si no lo es
 */
static int esTarjeta (char* cadena, int longitud){
	int retorno = 0;
	int i;
	int contadorGuiones = 0;
	if (cadena != NULL){
		if (cadena [4] == '-' && cadena [9]== '-' && cadena [14] == '-'){
			retorno = 1;
			for (i=0; cadena [i] != '\0'; i++){
				if ((cadena[i] >= '0' || cadena[i] <= '9') && (cadena [i]== '-')){
					retorno = 1;
					contadorGuiones++;
				}
			}
			if (contadorGuiones>4)
				retorno = 0;
		}

	}
	return retorno;
}
/*
 * \brief Solicita un numero entero al usuario, luego de verificarlo devuelve el resultado
 * \param pResultado Puntero al espacio de memoria donde se dejara el resultado de la funcion
 * \param pMensaje Mensaje a ser mostrado
 * \param pMensajeError Mensaje de error a ser mostrado
 * \param minimo Es el numero maximo a ser aceptado
 * \param maximo Es el minimo minimo a ser aceptado
 * \param reintentos Reintentos que tiene el usuario por si el ingreso fue erroneo
 * \return Retorna 0 (EXITO) y -1 (ERROR)
 */
int utn_getNumeroInt (int *pResultado,char* mensaje, char* mensajeError, int minimo, int maximo, int reintentos){
	int retorno = -1;
	int bufferInt;
	if (pResultado!= NULL && mensaje != NULL && mensajeError != NULL && minimo <= maximo && reintentos>= 0){
		do
		{
			printf ("%s", mensaje);
			if (getNumeroInt (&bufferInt)==0 && bufferInt >= minimo && bufferInt <= maximo){
				*pResultado = bufferInt;
				retorno = 0;
				break;
			}
			reintentos--;
			printf ("%s", mensajeError);
		}while(reintentos >=0);
	}
	return retorno;
}
/**
 * \brief Obtiene un numero entero valido
 * \param pResultado Puntero al espacio de memoria donde se dejara el resultado de la funcion
 * \return 0 (exito) si se obtiene un numero entero y -1 (error) si no se obtiene un  numero entero
 */
static int getNumeroInt (int* pResultado){
	int retorno = -1;
	char buffer [64];
	if (pResultado!= NULL){
		if (getString(buffer,sizeof(buffer)) == 0 && esNumerica(buffer, sizeof(buffer))){
			*pResultado = atoi (buffer);
			retorno = 0;
		}
	}
	return retorno;
}
/*
 * \brief Verifica si la cadena ingresada es numerica
 * \param cadena Cadena de caracteres que sera analizada
 * \return Retorna 1 (verdadero) si la cadena es numerica, 0 (falso) si no lo es y -1 si da error
 */
int esNumerica (char* cadena, int longitud){
	int retorno = 1;
	int i=0;
	if (cadena != NULL){
		if (cadena [0] == '-' || cadena [0] == '+')
			i = 1;
		for ( ; i<longitud && cadena[i] != '\0';i++){
			if (cadena[i] > '9' || cadena[i] < '0'){
				retorno = 0;
				break;
			}
		}
	}
	return retorno;
}
/*
 * \brief Solicita un numero flotante al usuario, luego de verificarlo devuelve el resultado
 * \param pResultado Puntero al espacio de memoria donde se dejara el resultado de la funcion
 * \param pMensaje Mensaje a ser mostrado
 * \param pMensajeError Mensaje de error a ser mostrado
 * \param minimo Es el numero maximo a ser aceptado
 * \param maximo Es el minimo minimo a ser aceptado
 * \param reintentos Reintentos que tiene el usuario por si el ingreso fue erroneo
 * \return Retorna 0 (EXITO) y -1 (ERROR)
 */
int utn_getNumeroFlotante (float* pResultado, char* mensaje, char* mensajeError, int minimo, int maximo, int reintentos){
	int retorno = -1;
	float bufferFloat;
	if (pResultado!= NULL && mensaje != NULL && mensajeError != NULL && minimo <= maximo && reintentos>= 0){
			do
			{
				printf ("%s", mensaje);
				if (getFloat (&bufferFloat)==0 && bufferFloat >= minimo && bufferFloat <= maximo){
					*pResultado = bufferFloat;
					retorno = 0;
					break;
				}
				reintentos--;
				printf ("%s", mensajeError);
			}while(reintentos >=0);
		}

		return retorno;
}
/**
 * \brief Obtiene un numero flotante valido
 * \param pResultado Puntero al espacio de memoria donde se dejara el resultado de la funcion
 * \return Retorna 0 (EXITO) y -1 (ERROR)
 */
int getFloat (float* pResultado){
	int retorno = -1;
	char buffer [64];
	if (pResultado != NULL){
		if (getString (buffer, sizeof (buffer)) == 0 && esNumericaFlotante(buffer, sizeof(buffer))){
			*pResultado = atof (buffer);
			retorno = 0;
		}
	}
	return retorno;
}
/**
 * \brief Verifica si la cadena ingresada contiene numeros flotantes (con coma)
 * \param cadena Array a ser analizado
 * \param longitud Longitud del array
 * \return Retorna 1 (verdadero) si la cadena es valida y 0 (falso) si no lo es
 */
int esNumericaFlotante (char* cadena, int longitud){
	int retorno = 1;
	int i;
	int contadorPuntos=0;
	if (cadena != NULL){
		for (i=0;i<longitud && cadena[i] != '\0';i++){
			if (cadena [i] == '.' && contadorPuntos ==0){
				contadorPuntos++;
				continue;
			}
			if (cadena[i] > '9' || cadena[i] < '0'){
				retorno = 0;
				break;
			}
		}
	}
	return retorno;
}
/*
 * \brief Solicita un texto al usuario, luego de verificarlo devuelve el resultado
 * \param pResultado Array de la direccion
 * \param longitud Longitud del array
 * \param pMensaje Mensaje a ser mostrado
 * \param pMensajeError Mensaje de error a ser mostrado
 * \param reintentos Reintentos que tiene el usuario por si el ingreso fue erroneo
 * \return Retorna 0 (EXITO) y -1 (ERROR)
 */
int utn_getTexto (char* pResultado, int longitud, char* pMensaje, char* pMensajeError, int reintentos){
	int retorno = -1;
	char buffer[4501];
	if (pResultado!= NULL && pMensaje != NULL && pMensajeError != NULL && reintentos>= 0){
		do
		{
			printf ("%s", pMensaje);
			if (getTexto(buffer, sizeof (buffer))==0 && reintentos >= 0){
				strncpy(pResultado, buffer, longitud);
				retorno = 0;
				break;
			}
			reintentos--;
			printf ("%s", pMensajeError);
		}while(reintentos >=0);
	}

	return retorno;
}
/**
 * \brief Obtiene un string valido como un texto
 * \param pResultado Array donde se dejara el resultado de la funcion
 * \param longitud Longitud del array
 * \return Retorna 0 (EXITO) y -1 (ERROR)
 */
static int getTexto (char* pResultado, int longitud){
	int retorno = -1;
	char buffer [4050];
	if (pResultado != NULL){
		if (getString (buffer, sizeof (buffer)) == 0 && esSoloLetras (buffer, sizeof (buffer)) && strnlen (buffer, sizeof (buffer)) < longitud){
			strncpy (pResultado, buffer, longitud);
			retorno = 0;
		}
	}
	return retorno;
}
/**
 * \brief Verifica si la cadena ingresada contiene solo letras
 * \param cadena Array a ser analizado
 * \param longitud Longitud del array
 * \return Retorna 1 (verdadero) si la cadena es valida y 0 (falso) si no lo es
 */
int esSoloLetras (char* cadena, int longitud){
	int retorno = 1;
	int i;
	if (cadena != NULL){
		for (i= 0; cadena [i] != '\0'; i++){
			if ((cadena[i] != ' ') && (cadena [i] < 'a' || cadena [i]> 'z') && (cadena [i]< 'A' || cadena [i]> 'Z'))
				retorno = 0;
			if(cadena[i]== '-')
				retorno = 1;
		}
	}
	return retorno;
}
/*
 * \brief Solicita una nombre al usuario, luego de verificarla devuelve el resultado
 * \param pResultado Array de la direccion
 * \param longitud Longitud del array
 * \param pMensaje Mensaje a ser mostrado
 * \param pMensajeError Mensaje de error a ser mostrado
 * \param reintentos Reintentos que tiene el usuario por si el ingreso fue erroneo
 * \return Retorna 0 (EXITO) y -1 (ERROR)
 */
int utn_getNombre (char* pResultado, int longitud, char* pMensaje, char* pMensajeError, int reintentos){
	int retorno = -1;
	char buffer[4501];
	if (pResultado!= NULL && pMensaje != NULL && pMensajeError != NULL && reintentos>= 0){
		do
		{
			printf ("%s", pMensaje);
			if (getTexto(buffer, sizeof (buffer))==0 && reintentos >= 0){
				strncpy(pResultado, buffer, longitud);
				retorno = 0;
				break;
			}
			reintentos--;
			printf ("%s", pMensajeError);
		}while(reintentos >=0);
	}
	return retorno;
}

/**
 * \brief 	Lee de stdin hasta que encuentra un '\n' o hasta que haya copiado en cadena
 * 			un maximo de 'longitud - 1' caracteres.
 * \param pResultado Array donde se copiara la cadena obtenida
 * \param longitud Longitud del array
 * \return Retorna 0 (EXITO) si se obtiene una cadena y -1 (ERROR)
 *
 */
int getString (char* cadena, int longitud){
	int retorno = -1;
	char bufferString [4050];
	if (cadena != NULL && longitud > 0){
		fflush(stdin);
		if (fgets (bufferString, sizeof (bufferString), stdin)){
			if (bufferString[strnlen(bufferString, sizeof(bufferString))-1] == '\n'){
				bufferString[strnlen(bufferString, sizeof(bufferString))-1] = '\0';
			}
			if (strnlen(bufferString, sizeof(bufferString)) <= longitud){
				strncpy (cadena, bufferString, longitud);
				retorno = 0;
			}
		}
	}
	return retorno;
}

/*void imprimir (NombreDeEstructura* pEstructura)
{
	printf (" %s, %s, %d", pEstructura->nombre, pEstructura->precio..)
}
*/
//-----------------------------------------------------------A- B- M-----------------------------------------------------------------------------

/*
int _imprimir (Prueba* pElemento)
{
	int retorno = -1;

	if (pElemento != NULL && pElemento->isEmpty == 0) //pregunto si ese lugar no esta vacio
	{
		retorno = 0;
		printf ("\n Id: %d - Nombre: %s -DNI: %s - Altura: %.2f", pElemento->id, pElemento->nombre, pElemento->dni, pElemento->altura);
	}
	return retorno;
}
int _imprimirArray (Prueba* array, int limite)
{
	int retorno = -1;
	int i;
	if (array != NULL && limite >0)
	{
		retorno = 0;
		for (i=0; i<limite; i++) //pasamos por todos los lugares del array
		{
			_imprimir(&array [i]);
		}
	}
	return retorno;
}
int _inicializarArray (Prueba* array, int limite)
{
	int retorno = -1;
	int i;
	if(array != NULL && limite>0)
	{
		retorno = 0;
		for (i=0; i<limite; i++) //recorremos todo el array poniendo el is empty en 1
		{
			array [i].isEmpty = 1; //lo ponemos en 1: es verdadero que esta vacio
		}
	}
	return retorno;
}

int _altaArray(Prueba* array, int limite, int indice, int* id)
{
	int retorno = -1;
	Prueba bufferCli;
	if (array != NULL && limite>0 && indice<limite && indice >= 0 && id != NULL)
	{
		if (utn_getNombre(bufferCli.nombre,NOMBRE_LEN, "\nIngrese nombre", "\nError", 3)==0 &&
			utn_getDni(bufferCli.dni, DNI_LEN, "\nDni?:", "\nError", 3) ==0 &&
			utn_getNumeroFlotante(&bufferCli.altura, "\nAltura?", "\nError", 0, 1.99, 3)==0)
		{
			bufferCli.id =*id;
			bufferCli.isEmpty = 0;
			array[indice] = bufferCli;
			(*id)++;
			retorno = 0;
		}
	}

	return retorno;
}
int _modificarArray (Prueba* array, int limite, int indice) //accede a una posicion y modifica los datos ahi
{
	int retorno = -1;
	Prueba bufferCli;
	if (array!=NULL && limite>0 && indice<limite && indice>=0 && array[indice].isEmpty ==0)
	{
			if (utn_getNombre(bufferCli.nombre,NOMBRE_LEN, "\nIngrese nombre", "\nError", 3)==0 &&
				utn_getDni(bufferCli.dni, DNI_LEN, "\nDni?:", "\nError", 3) ==0 &&
				utn_getNumeroFlotante(&bufferCli.altura, "\nAltura?", "\nError", 0, 1.99, 3)==0)
			{
				bufferCli.id = array[indice].id;
				bufferCli.isEmpty = 0;
				array[indice] = bufferCli;
				retorno = 0;
			}
	}
	return retorno;
}

int _bajarArray (Prueba* array, int limite, int indice)
{
	int retorno = -1;

	if (array != NULL && limite >0 && indice <limite && indice >= 0 && array[indice].isEmpty ==0)
	{
		array[indice].isEmpty = 1;
		retorno = 0;
	}
	return retorno;
}

int _buscarId (Prueba* array, int limite, int valorBuscado)
{
	int respuesta = -1;
	int i;
	if(array != NULL && limite>0 && valorBuscado>=0)
	{
		respuesta = 0;
		for (i=0; i<limite; i++)
		{
			if (array[i].id == valorBuscado)
			{
				respuesta = i;
				break;
			}
		}
	}
	return respuesta;
}

int _getEmptyIndex (Prueba* array, int limite)
{
	int respuesta = -1;
	int i;
	if(array != NULL && limite>0)
	{
		respuesta = 0;
		for (i=0; i<limite; i++)
		{
			if (array[i].isEmpty == 1) //busca el indice que esta vacio
			{
				respuesta = i; //devuelve la posicion vacia
				break;
			}
		}
	}
	return respuesta;
}
*/
/*
 * \brief Ordenar el array de ... por ... (comparacion de string)
 * \param array Array de ..
 * \param limite Limite del array de ..
 * \return Retorna el
 */
/*
int _ordenarPorNombre (Prueba* array, int limite)
{
	int respuesta = -1;
	int i;
	Prueba buffer;
	int flagSwap;
	if(array != NULL && limite>0)
	{
		do
		{
			flagSwap = 0;
			for (i=0; i<limite-1; i++)
			{
				if(array [i].isEmpty || array[i+1].isEmpty)
				{
					continue;
				}
				if (strncmp(array[i].nombre, array[i+1].nombre, NOMBRE_LEN) >0)
				{
					flagSwap = 1;
					buffer = array[i];
					array[i] = array[i+1];
					array[i+1] = buffer;
				}
			}
			limite--;
		}while (flagSwap);
	}
	return respuesta;
}
*//*
 * \brief Ordenar el array de ... por ... y por .. (2 comparaciones)
 * \param array Array de ..
 * \param limite Limite del array de ..
 * \return Retorna el
 */

/*
int _ordenarPorNombreAltura (Prueba* array, int limite)
{
	int respuesta = -1;
		int i;
		Prueba buffer;
		int flagSwap;
		if(array != NULL && limite>0)
		{
			do
			{
				flagSwap = 0;
				for (i=0; i<limite-1; i++)
				{
					if(array [i].isEmpty || array[i+1].isEmpty)
					{
						continue;
					}
					if (strncmp(array[i].nombre, array[i+1].nombre, NOMBRE_LEN) >0 ||
						(strncmp(array[i].nombre, array[i+1].nombre, NOMBRE_LEN) ==0 &&
						array[i].altura > array [i+1].altura))
					{
						flagSwap = 1;
						buffer = array[i];
						array[i] = array[i+1];
						array[i+1] = buffer;
					}
				}
				limite--;
			}while (flagSwap);
		}
		return respuesta;
}


*/
