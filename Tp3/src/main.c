#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.h"
#include "utn.h"
#include "Controller.h"
#include "Employee.h"
#include "parser.h"
/****************************************************
    Menu:
     1. Cargar los datos de los empleados desde el archivo data.csv (modo texto).
     2. Cargar los datos de los empleados desde el archivo data.csv (modo binario).
     3. Alta de empleado
     4. Modificar datos de empleado
     5. Baja de empleado
     6. Listar empleados
     7. Ordenar empleados
     8. Guardar los datos de los empleados en el archivo data.csv (modo texto).
     9. Guardar los datos de los empleados en el archivo data.csv (modo binario).
    10. Salir
*****************************************************/


//DEJO CARGADAS LAS CARPETAS QUE USE DE PRUEBAS, EN EL MAIN DEJO LA LISTA ORIGINAL.

int main()
{
	setbuf (stdout,NULL);

	LinkedList* listaEmpleados = ll_newLinkedList();

	//FILE* punteroTexto;

    int option = 0;


    do{
    	if (utn_getNumero (&option, "1.CARGAR DATOS DE LOS EMPLEADOS DESDE EL ARCHIVO DATA.CSV (modo texto)\n"
    								"2.CARGAR DATOS DE LOS EMPLEADOS DESDE EL ARCHIVO DATA.CSV (modo binario)\n"
    								"3.ALTA DE EMPLEADO\n"
    								"4.MODIFICAR DATOS DEL EMPLEADO \n"
    								"5.BAJA DE UN EMPLEADO \n"
    								"6.LISTAR EMPLEADOS \n"
    								"7.ORDENAR EMPLEADOS \n"
    								"8.GUARDAR DATOS DE LOS EMPLEADOS EN EL ARCHIVO DATA.CSV (modo texto) \n"
    								"9.GUARDAR DATOS DE LOS EMPLEADOS EN EL ARCHIVO DATA.CSV (modo binario)\n"
    								"10.SALIR \n"
    								,"Error no es una opcion\n",1,10,2) ==0)
    	{

    		switch(option)
    		{
    			case 1:
                controller_loadFromText("data.csv",listaEmpleados);
                break;
                /********************************************************************************************************************/
    			case 2:
    			controller_loadFromBinary("data.bin",listaEmpleados);
    			break;
                /********************************************************************************************************************/
    			case 3:
    			controller_addEmployee(listaEmpleados);
    		    break;
                /********************************************************************************************************************/
    			case 4:
    			controller_editEmployee(listaEmpleados);
    		    break;
                /********************************************************************************************************************/
    			case 5:
    			controller_removeEmployee(listaEmpleados);
    		    break;
                /********************************************************************************************************************/
    			case 6:
    			controller_ListEmployee(listaEmpleados);
    		    break;
                /********************************************************************************************************************/
    			case 7:
    			controller_sortEmployee(listaEmpleados);
    		    break;
                /********************************************************************************************************************/
    			case 8:
    			controller_saveAsText("data.csv",listaEmpleados);
    		    break;
                /********************************************************************************************************************/
    			case 9:
    			controller_saveAsBinary("data.bin",listaEmpleados);
    		    break;
                /********************************************************************************************************************/
    		}

    	}
    }while(option != 10);
    return 0;
}
