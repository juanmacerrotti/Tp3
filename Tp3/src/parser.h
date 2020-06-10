/*
 * parser.h
 *
 *  Created on: 5 jun. 2020
 *      Author: Juan
 */
#ifndef PARSER_H_
#define PARSER_H_
#include "Linkedlist.h"

int parser_EmployeeFromText(FILE* pFile , LinkedList* pArrayListEmployee);
int parser_EmployeeFromBinary(FILE* pFile , LinkedList* pArrayListEmployee);

#endif /* PARSER_H_ */
