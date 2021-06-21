/*
 * parser.h
 *
 *  Created on: 18 jun. 2021
 *      Author: ludmi
 */

#ifndef PARSER_H_
#define PARSER_H_
#include "Dictionary.h"
#include "Maritimo.h"
#include "Aereo.h"

int parser_ArticulosFromText (FILE* pFile, Dictionary* articulos);
int parser_PosArancFromText(FILE* pFile, Dictionary* posAranc);
int parser_TranspMarFromText(FILE* pFile, Maritimo* transpMar);
int parser_TranspAereoFromText(FILE* pFile, Aereo* transpAereo);


#endif /* PARSER_H_ */
