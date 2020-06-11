#include <stdio.h>
#include <stdlib.h>
#include "utn.h"
#include "LinkedList.h"
#include "Employee.h"
#include "parser.h"

static int idMaximo(LinkedList* pArrayListEmployee, int* idMaximo);

/** \brief Carga los datos de los empleados desde el archivo data.csv (modo texto).
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_loadFromText(char* path , LinkedList* pArrayListEmployee)
{
	int retorno = -1;
	FILE* pFile;
	int empleadosCargados = 0;

	    if(path != NULL && pArrayListEmployee != NULL)
	    {
	    	pFile = fopen(path,"r");  //abro archivo para lectura de texto.
	    		if(pFile != NULL && !parser_EmployeeFromText(pFile, pArrayListEmployee))
				{
	    			empleadosCargados = parser_EmployeeFromText(pFile, pArrayListEmployee);  // cuento cuantos empleados pude parsear y se lo doy a un auxiliar.
					printf("Empleados cargados: %d \n", empleadosCargados); //imprimo la cantidad de empleados caregados con mi auxiliar
					retorno = 0;
				}
				else
				{
					printf("El archivo no puede abrirse\n"); //en caso que no pueda abrirlo, informo
				}

	    fclose(pFile);
	    }

	    return retorno;
}

/** \brief Carga los datos de los empleados desde el archivo data.csv (modo binario).
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_loadFromBinary(char* path , LinkedList* pArrayListEmployee)
{
	int retorno = -1;
	FILE* pFile;
	int empleadosCargados = 0;

	    if(path != NULL && pArrayListEmployee != NULL)
	    {
	    	pFile = fopen(path,"rb");  //abro archivo para lectura binaria
	    	if(pFile != NULL)
	    	{
	    		if(pFile != NULL)   //parseo los datos
					{
	    				empleadosCargados = parser_EmployeeFromBinary(pFile, pArrayListEmployee);  // cuento cuantos empleados pude parsear.
						printf("Empleados cargados: %d \n", empleadosCargados); //imprimo la cantidad de empleados caregados
						retorno = 0;
					}
	    	}
	    	else
	    	{
	    		printf("El archivo no puede abrirse\n"); //en caso que no pueda abrirlo informo.
	    	}
	    fclose(pFile);
	    }

	    return retorno;
}

/** \brief Alta de empleados
 * \param pArrayListEmployee LinkedList*
 * \return int 0 en caso de exito, y 1 si fallo.
 *
 */
int controller_addEmployee(LinkedList* pArrayListEmployee)
{
	int retorno=-1;
	char bufferNombre[128];
	int bufferSueldo;
	int bufferHorasTrabajadas;
	int id;
	Employee* empleado;

	if(pArrayListEmployee != NULL)
	{
		if(	utn_getNombre(bufferNombre,128,"ingrese nombre: \n", "nombre incorrecto \n", 2) == 0 && 
				utn_getNumero(&bufferSueldo,"ingrese sueldo: \n", "sueldo incorrecto \n",1,100000,2) ==0 &&  
				utn_getNumero(&bufferHorasTrabajadas, "ingrese horas trabajadas:\n","formato horas incorrecto\n",1,500,2) == 0 &&
				idMaximo(pArrayListEmployee,&id) ==0) // hice funcion para encontrar el ID maximo.
			{
				id=id+1;  // al ID maximo que me dio la funcion le sumo uno y se lo asigno al proximo empleado.
				empleado=employee_newParametros(id,bufferNombre,bufferHorasTrabajadas,bufferSueldo);  // cargo un empleado en memoria.
				if(empleado!=NULL)
				{
					ll_add(pArrayListEmployee, empleado);  // añado su puntero a la lista,
					printf("alta OK \n");
				}
				retorno=0;
			}
	}
	else
	{
		printf("Error.");
	}
    return retorno;
}

/** \brief Modificar datos de empleado
 * \param pArrayListEmployee LinkedList*
 * \return int 0 en caso de exito y -1 si fallo.
 *
 */
int controller_editEmployee(LinkedList* pArrayListEmployee)
{
	int retorno=-1;
	int id;
	int i;
	Employee* empleado;
	char bufferNombre[128];
	int bufferSueldo;
	int bufferHorasTrabajadas;

if(pArrayListEmployee != NULL)
{
	if(utn_getNumero(&id,"ingrese ID del empleado a modificar:\n", "error\n", 0,100000,2) == 0) //ingreso id
	{
		for(i=0;i<ll_len(pArrayListEmployee);i++) //recorro listo
		{
			empleado= ll_get(pArrayListEmployee,i); //obtengo direccion de memoria

			if(empleado != NULL && empleado->id == id) //busco id
			{
				if(	utn_getNombre(bufferNombre,128,"ingrese nombre: \n", "nombre incorrecto \n", 2) == 0 &&
					utn_getNumero(&bufferSueldo,"ingrese sueldo: \n", "sueldo incorrecto \n",1,100000,2) ==0 &&
					utn_getNumero(&bufferHorasTrabajadas, "ingrese horas trabajadas:\n","formato horas incorrecto\n",1,1000,2) == 0)
					{ //si todo esta ok, modifico
							employee_setNombre(empleado,bufferNombre); // escribo los nuevos campos.
							employee_setSueldo(empleado,bufferSueldo);// escribo los nuevos campos.
							employee_setHorasTrabajadas(empleado,bufferHorasTrabajadas); // escribo los nuevos campos.
					    	printf("modificacion OK \n");
					    	break;
					    	retorno=0;
					}
			}

		}
	}
}
    return retorno;
}

/** \brief Baja de empleado
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_removeEmployee(LinkedList* pArrayListEmployee)
{
	int retorno=-1;
	int id;
	int i;
	Employee* empleado;

	if(pArrayListEmployee != NULL)
	{
		if(utn_getNumero(&id, "ingrese ID que quiere borrar: \n", "Formato ID incorrecto \n", 0,100000,2) ==0)   //pido ID
		{
			for(i=0;i<ll_len(pArrayListEmployee);i++) //recorro lista
			{
				empleado= ll_get(pArrayListEmployee,i); // leo en cada posicion de la lista
				if(empleado != NULL && empleado->id == id)  //busco el ID
				{
					employee_delete(empleado); //remuevo empleado de memoria (free)
					ll_remove(pArrayListEmployee,i); //lo borro de la lista
					retorno=0;
					printf("baja OK. \n");
					break;
				}
			}
		}
	}

return retorno;
}

/** \brief Listar empleados
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_ListEmployee(LinkedList* pArrayListEmployee)
{
	int retorno=-1;
	int i;
	Employee* empleado;

	char auxiliarId[128];
	char auxiliarNombre[128];
	char auxiliarHsTrabajadas[128];
	char auxiliarSueldo[128];

	if(pArrayListEmployee != NULL) //valida que la lista tenga algo
	{

		for(i=0;i<ll_len(pArrayListEmployee);i++) // recorre lista
		{
			empleado = ll_get(pArrayListEmployee,i); //lee un empleado en una posicion de la lista.
			if(empleado!=NULL) //si me da una posicion de la lista, imprimo
			{
				employee_getIdStr(empleado,auxiliarId);
				employee_getNombre(empleado,auxiliarNombre);
				employee_getHorasTrabajadasStr(empleado,auxiliarHsTrabajadas);
				employee_getSueldoStr(empleado,auxiliarSueldo);
				printf("%s,%s,%s,%s\n",auxiliarId,auxiliarNombre,auxiliarHsTrabajadas,auxiliarSueldo);
			}
		}
		retorno=0;
	}
	return retorno;

}

/** \brief Ordenar empleados
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_sortEmployee(LinkedList* pArrayListEmployee)
{
	int opcion;

	if(utn_getNumero(&opcion,"De que manera desea ordenar los sueldos? [0 creciente; 1 Decreciente]\n","Error \n",0,1,2)==0)  //pregunto de que forma ordenar
	{
		if(ll_sort(pArrayListEmployee,Employee_funcionCriterio,opcion)==0)
		{
			printf("ordena por sueldo OK. \n"); //ok ordenado
		}
	}
	return 1;
}

/** \brief Guarda los datos de los empleados en el archivo data.csv (modo texto).
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_saveAsText(char* path , LinkedList* pArrayListEmployee)
{
	int retorno=-1;
	FILE* pArchivo;
	Employee* pEmpleado;
	int i;
	int auxiliarId;
	char auxiliarNombre[2048];
	int auxiliarHorasTrabajadas;
	int auxiliarSueldo;
	pArchivo=fopen(path,"w");

	if(pArchivo != NULL)
	{

		for(i=0;i<ll_len(pArrayListEmployee);i++) // recorro la lista
		{
			pEmpleado=ll_get(pArrayListEmployee,i); // leo una posicion de un empleado
			if(pEmpleado != NULL)
			{
				employee_getId(pEmpleado,&auxiliarId); // leo sus campos y los guardo en un buffer
				employee_getNombre(pEmpleado,auxiliarNombre);// leo sus campos y los guardo en un buffer
				employee_getHorasTrabajadas(pEmpleado,&auxiliarHorasTrabajadas);// leo sus campos y los guardo en un buffer
				employee_getSueldo(pEmpleado,&auxiliarSueldo);// leo sus campos y los guardo en un buffer

			}
			fprintf(pArchivo,"%d,%s,%d,%d \n",auxiliarId,auxiliarNombre,auxiliarHorasTrabajadas,auxiliarSueldo); // escribo en el archivo los valores obtenidos del buffer
		}

		printf("guardado ok \n");
	}
	else
	{
		printf("El archivo no se puede guardar.\n"); // mensaje si no se puede abrir archivo.
	}
	fclose(pArchivo); // cierro archivo
    return retorno;
}

/** \brief Guarda los datos de los empleados en el archivo data.csv (modo binario).
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_saveAsBinary(char* path , LinkedList* pArrayListEmployee)
{

	int retorno=-1;
	FILE* pArchivo;
	Employee* pEmpleado;
	int i;

	pArchivo=fopen(path,"wb");  // abro para escribir en un archivo binario
	

	if(pArchivo != NULL)
	{

		for(i=0;i<ll_len(pArrayListEmployee);i++) // recorro la lista
		{
			pEmpleado=ll_get(pArrayListEmployee,i); // obtengo el puntero a un empleaado
			fwrite(pEmpleado,sizeof(Employee),1,pArchivo); // lo escribo en el archivo, de a 1 empelado leido y del tamaño de un empleado.
		}
		printf("guardado ok \n");
	}
	else
	{
		printf("El archivo no se puede guardar.\n");
	}

	fclose(pArchivo); // cierro archivo.

    return retorno;
}

static int idMaximo(LinkedList* pArrayListEmployee, int* idMaximo) // funcion para obtener el maximo ID
{
	int retorno=-1;
	Employee* auxEmpleado;
	int auxId=-1;
	int i;

	if(pArrayListEmployee != NULL && idMaximo != NULL)
	{
		retorno=0;
		for(i=0; i<ll_len(pArrayListEmployee);i++) // recorro la lista
		{
			auxEmpleado=ll_get(pArrayListEmployee,i); // leo los ID y almaceno
			if(auxEmpleado!=NULL && auxEmpleado->id>auxId) // los comparo con un maximo (que arranca en un -1). Hice esto suponiendo que siempre primero se carga la lista como habiamos mencionado en clase.
			{
				*idMaximo=auxEmpleado->id; // leo el ID del empleado y lo guardo en el maximo.
			}
		}
	}

	return retorno;
}
