#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.h"
#include "Employee.h"

/** \brief Parsea los datos los datos de los empleados desde el archivo data.csv (modo texto).
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return cantidad de empleados
 */
int parser_EmployeeFromText(FILE* pFile , LinkedList* pArrayListEmployee)
{
        int retorno = -1;
		Employee* auxiliarEmpleado;
		char auxiliarId[2048];
		char auxiliarNombre[2048];
		char auxiliarHsTrabajadas[2048];
		char auxiliarSueldo[2048];
		int cantidadEmpleados = 0;


		if(pFile != NULL && pArrayListEmployee != NULL)
		{
			do
			 {
				if(fscanf(pFile,"%[^,],%[^,],%[^,],%[^\n]\n",auxiliarId,auxiliarNombre,auxiliarHsTrabajadas,auxiliarSueldo)== 4)
					{
				       auxiliarEmpleado = employee_newParametrosTxt(auxiliarId,auxiliarNombre,auxiliarHsTrabajadas,auxiliarSueldo);
					    if(auxiliarEmpleado != NULL)
					    {
							if(!ll_add(pArrayListEmployee,auxiliarEmpleado))
							{
								cantidadEmpleados++;
							}
		                 }
						else
						{
							break;
						}

					}
			  }while(!feof(pFile));
              retorno = cantidadEmpleados;
		  }
				return retorno;
}

/** \brief Parsea los datos los datos de los empleados desde el archivo data.csv (modo binario).
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int parser_EmployeeFromBinary(FILE* pFile , LinkedList* pArrayListEmployee)
{
    int retorno = -1;
	Employee* auxiliarEmpleado=NULL;
	Employee* empleado;
	int cantidadEmpleados = 0;
	char auxiliarId[2048];
	char auxiliarNombre[2048];
	char auxiliarHsTrabajadas[2048];
	char auxiliarSueldo[2048];


	if(pFile != NULL && pArrayListEmployee != NULL)
	{
		do
		 {
			auxiliarEmpleado=employee_new();
			if(fread(auxiliarEmpleado,sizeof(Employee),1,pFile)==1)
				{
				    if(auxiliarEmpleado != NULL)
				    {
				    	if(employee_getNombre(auxiliarEmpleado,auxiliarNombre) == 0 &&
				    		employee_getSueldoStr(auxiliarEmpleado,auxiliarSueldo) == 0 &&
							employee_getHorasTrabajadasStr(auxiliarEmpleado,auxiliarHsTrabajadas) == 0 &&
							employee_getIdStr(auxiliarEmpleado,auxiliarId) == 0)
						{
				    		empleado = employee_newParametrosTxt(auxiliarId,auxiliarNombre,auxiliarHsTrabajadas,auxiliarSueldo);
				    		 if(empleado != NULL)
				    		 {
				    			if(!ll_add(pArrayListEmployee,empleado))
				    			{
				    				cantidadEmpleados++;
				    			}
				    		 }
					}
	                }
					else
					{
						break;
					}

				}
		  }while(!feof(pFile));
          retorno = cantidadEmpleados;
	  }
			return retorno;
}
