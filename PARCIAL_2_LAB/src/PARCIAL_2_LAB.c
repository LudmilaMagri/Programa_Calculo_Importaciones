/*
 ============================================================================
 Name        : PARCIAL_2_LAB.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include "Articulos.h"
#include "LinkedList.h"
#include "Controller.h"
#include "PosArancelaria.h"
#include "Maritimo.h"
#include "Aereo.h"
#include "utn.h"

int main(void) {

	setbuf(stdout, NULL);

	int option = 0;
	Dictionary* articulos = dict_new(0);
	Dictionary* posicionAranc = dict_new(0);
	Maritimo transMar;
	Aereo transAereo;
	int idMaxPosAra;
	int idMaxArt;

	controller_art_loadFromText("articulos.csv", articulos, &idMaxArt);
	controller_posAranc_loadFromText("posicionAranc.csv", posicionAranc, &idMaxPosAra);
	controller_MAR_loadFromText("TransporteMar.csv", &transMar);
	controller_AEREO_loadFromText("TransporteAereo.csv", &transAereo);



	do{
		if (!utn_getNumeroInt(&option,
							"\n\n"
							"\n\t---------------------------------------------------------------------------------"
							"\n\t\t		***** MENU *****							\n"
							"\n\t*	1. Menu posiciones arancelarias\t*"
							"\n\t*	2. Menu articulos\t*"
							"\n\t*	3. Listar Posiciones Arancelarias\t\t\t\t\t\t\t*"
							"\n\t*	4. Listar Articulos\t\t\t\t\t\t*"
							"\n\t*	5. Modificar datos del transporte Maritimo\t\t\t\t\t\t\t*"
							"\n\t*	6. Modificar datos del transporte Aereo\t\t\t\t\t\t\t*"
							"\n\t*	7. Listar costo argentino de ambos transportes\t\t\t\t\t\t\t*"
							"\n\t*	8. Guardar los datos de los empleados en el archivo (modo texto).\t*"
							"\n\t*	9. Guardar los datos de los empleados en el archivo (modo binario).\t*"
							"\n\t*	10. Salir\t\t\t\t\t\t\t\t*"
							"\n\t--------------------------------------------------------------------------------\n\nIngrese Opcion: ",
							"\nError opcion invalida", 0, 11, 2))
		{
			switch(option)
			{
				case 1:
					controller_ABM_PosicionArancelaria(posicionAranc, "posicionAranc.csv");
					break;
				case 2:
					controller_ABM_Articulos(articulos, posicionAranc, "posicionesAranc.csv", "articulos.csv");
					break;
				case 3:
					controller_imprimirListaPosAranc(posicionAranc);
					break;
				case 4:
					controller_imprimirListaArticulos(articulos);
					break;
				case 5:
					controller_mar_editTransporteMar(&transMar, "TransporteMar.csv");
					break;
				case 6:
					controller_aer_editTransporteAereo(&transAereo, "TransporteAereo.csv");
					break;
				case 7:
					controller_printCostoArgMaritimoAereo(articulos, posicionAranc, &transMar, &transAereo);
					break;
				case 8:
					break;
				case 9:
					break;
			}
		}
	}while(option != 10);


	return EXIT_SUCCESS;
}
