#ifndef employee_H_INCLUDED
#define employee_H_INCLUDED

typedef struct
{
    int id;
    char nombre[128];
    int horasTrabajadas;
    int sueldo;
}Employee;

Employee* employee_new(void);
Employee* employee_newParametrosTxt(char* idStr,char* nombreStr,char* horasTrabajadasStr, char* sueldoStr);
Employee* employee_newParametros(int id,char* nombreStr,int horasTrabajadas,int sueldo);
void employee_delete(Employee* this);

/*****************************************************/

//set y get (formato texto)

int employee_setNombre(Employee* this,char* nombre);
int employee_getNombre(Employee* this,char* nombre);

int employee_setIdStr(Employee* this,char* id);
int employee_getIdStr(Employee* this,char* id);

int employee_setHorasTrabajadasStr(Employee* this,char* horasTrabajadas);
int employee_getHorasTrabajadasStr(Employee* this,char* horasTrabajadas);

int employee_setSueldoStr(Employee* this,char* sueldo);
int employee_getSueldoStr(Employee* this,char* sueldo);

//get y set (NATIVOS)

int employee_setId(Employee* this,int id);
int employee_getId(Employee* this,int* id);

int employee_setSueldo(Employee* this,int sueldo);
int employee_getSueldo(Employee* this,int* sueldo);

int employee_setHorasTrabajadas(Employee* this,int horasTrabajadas);
int employee_getHorasTrabajadas(Employee* this,int* horasTrabajadas);

/****************************************************/
int Employee_funcionCriterio (void* item1, void* item2);

#endif // employee_H_INCLUDED
