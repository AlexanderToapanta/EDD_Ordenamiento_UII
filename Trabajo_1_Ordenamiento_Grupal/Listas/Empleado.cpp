#ifndef EMPLEADO_CPP
#define EMPLEADO_CPP
#include "Empleado.h"
#include<string>
using namespace std;


string Empleado :: getID(void)
{
   return ID;
}


double Empleado :: getSueldo() 
{
   return Sueldo;
}

void Empleado :: setSueldo(double newSueldo)
{
   Sueldo = newSueldo;
}


Empleado::Empleado(const std::string& id, double sueldo)
    : ID(id), Sueldo(sueldo) {
}


Empleado :: Empleado()
{
    
}
Empleado::~Empleado()
{
   // TODO : implement
}
#endif 