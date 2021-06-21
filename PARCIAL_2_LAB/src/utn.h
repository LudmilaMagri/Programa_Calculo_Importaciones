/*
 * Funciones.h
 *
 */

#ifndef UTN_H_
#define UTN_H_

#define CANT_TARJ 20
#define BARBIJOS_LEN 99
#define DNI_LEN 22
#define DIREC_LEN 60
#define CUIT_LEN 14
#define DESCRIP_LEN 300
#define SEX_LEN 3
#define EMAIL_LEN 1000
//#define DNI_LEN 18

/*typedef struct
{
	char tarjeta [CANT_TARJ];
	char numeros [500];
	char nombre [NOMBRE_LEN];
	char dni [DNI_LEN];
	int isEmpty;
	int id;
	float altura;

}Prueba;*/

int utn_getNumeroFlotante (float* pResultado, char* mensaje, char* mensajeError, int minimo, int maximo, int reintentos);
int utn_getTexto (char* pResultado, int longitud, char* pMensaje, char* pMensajeError, int reintentos);
int utn_getNombre (char* pResultado, int longitud, char* pMensaje, char* pMensajeError, int reintentos);
int utn_getTarjeta (char* pResultado, int longitud, char* pMensaje, char* pMensajeError, int reintentos);
int utn_getDni (char* pResultado, int longitud, char* pMensaje, char* pMensajeError, int reintentos);
int utn_getTelefono (char* pResultado, int longitud, char* pMensaje, char* pMensajeError, int reintentos);
int utn_getNumeroInt (int *pResultado,char* mensaje, char* mensajeError, int minimo, int maximo, int reintentos);
int utn_getCuit (char* pResultado, int longitud, char* pMensaje, char* pMensajeError, int reintentos);
int utn_getDireccion (char* pResultado, int longitud, char* pMensaje, char* pMensajeError, int reintentos);
int utn_getDescripcion (char* pResultado, int longitud, char* pMensaje, char* pMensajeError, int reintentos);
int utn_getSexo (char* pResultado, int longitud, char* pMensaje, char* pMensajeError, int reintentos);
int utn_getEmail (char* pResultado, int longitud, char* pMensaje, char* pMensajeError, int reintentos);
int utn_getFecha(char* pResultado, int longitud, char* pMensaje, char* pMensajeError, int reintentos);
int utn_getRespuesta (char* pResultado, int longitud, char* pMensaje, char* pMensajeError, int reintentos);
int esNumerica (char* cadena, int longitud);
int esNumericaFlotante (char* cadena, int longitud);
int esSoloLetras (char* cadena, int longitud);
int utn_getTextoNumerosCaracter(char* pResultado, int longitud, char* pMensaje, char* pMensajeError, int reintentos);
int myGets2(char *pCadena, int len);
int utn_getStringWithOnlyNumbers(char *msg, char *msgError, char *pCadena, int limite, int reintentos);
int utn_isNumeric(char *pCadena);




/*
int _imprimir (Prueba* pElemento);
int _imprimirArray (Prueba* array, int limite);
int _inicializarArray (Prueba* array, int limite);
int _altaArray(Prueba* array, int limite, int indice, int* id);
int _modificarArray (Prueba* array, int limite, int indice);
int _bajarArray (Prueba* array, int limite, int indice);
int _buscarId (Prueba* array, int limite, int valorBuscado);
int _getEmptyIndex (Prueba* array, int limite);
int _ordenarPorNombreAltura (Prueba* array, int limite);
int _ordenarPorNombre (Prueba* array, int limite);
*/



//void imprimir (NombreDeEstructura* estructura);

#endif /* UTN_H_ */
