/***********************************************************************
 * Module:  Nodo.cpp
 * Author:  Usuario
 * Modified: mi�rcoles, 29 de mayo de 2024 18:58:15
 * Purpose: Implementation of the class Nodo
 ***********************************************************************/
#ifndef NODO_CPP
#define NODO_CPP
#include "Nodo.h"
#include "Empleado.h"
#include<string>
using namespace std;

////////////////////////////////////////////////////////////////////////
// Name:       Nodo::getEdad()
// Purpose:    Implementation of Nodo::getEdad()
// Return:     int
////////////////////////////////////////////////////////////////////////

string Nodo::getNombre1(void) const
{
   return Nombre1;
}

////////////////////////////////////////////////////////////////////////
// Name:       Nodo::setEdad(int newEdad)
// Purpose:    Implementation of Nodo::setEdad()
// Parameters:
// - newEdad
// Return:     void
////////////////////////////////////////////////////////////////////////

void Nodo::setNombre1(const string& newNombre1)
{
   Nombre1 = newNombre1;
}


string Nodo ::getApellido(void) const
{
   return Apellido;
}
string Nodo ::getCorreo(void)
{
   return Correo;
}
void Nodo::setCorreo(string newCorreo)
{
   Correo = newCorreo;
}

void Nodo :: setApellido(const string&newApellido)
{
   Apellido = newApellido;
}

string Nodo :: getCedula(void) const
{
   return Cedula;
}

void Nodo :: setCedula(const string& newCedula)
{
   Cedula = newCedula;
}


////////////////////////////////////////////////////////////////////////
// Name:       Nodo::Nodo(int E, int N, Nodo* S, Nodo* A)
// Purpose:    Implementation of Nodo::Nodo()
// Parameters:
// - E
// - N
// - S
// - A
// Return:     
////////////////////////////////////////////////////////////////////////

std::string Nodo::getNombre2(void) const
{
   return Nombre2;
}

////////////////////////////////////////////////////////////////////////
// Name:       Nodo::setNombre(std::string newNombre)
// Purpose:    Implementation of Nodo::setNombre()
// Parameters:
// - newNombre
// Return:     void
////////////////////////////////////////////////////////////////////////

void Nodo::setNombre2(string newNombre2)
{
   Nombre2 = newNombre2;
}
Nodo::Nodo(string N1, string N2, string Ape,string Ced, Nodo* S, Nodo* A)
{
   Nombre1=N1;
   Nombre2=N2;
   Apellido = Ape;
   Cedula = Ced;
   Siguiente=S;
   Anterior=A;

}

////////////////////////////////////////////////////////////////////////
// Name:       Nodo::~Nodo()
// Purpose:    Implementation of Nodo::~Nodo()
// Return:     
////////////////////////////////////////////////////////////////////////

Nodo::~Nodo()
{
   // TODO : implement
}

////////////////////////////////////////////////////////////////////////
// Name:       Nodo::getNombre()
// Purpose:    Implementation of Nodo::getNombre()
// Return:     std::string
////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////
// Name:       Nodo::getSiguiente()
// Purpose:    Implementation of Nodo::getSiguiente()
// Return:     Nodo*
////////////////////////////////////////////////////////////////////////

Nodo* Nodo::getSiguiente(void)
{
   return Siguiente;
}

////////////////////////////////////////////////////////////////////////
// Name:       Nodo::setSiguiente(Nodo* newSiguiente)
// Purpose:    Implementation of Nodo::setSiguiente()
// Parameters:
// - newSiguiente
// Return:     void
////////////////////////////////////////////////////////////////////////

void Nodo::setSiguiente(Nodo* newSiguiente)
{
   Siguiente = newSiguiente;
}

////////////////////////////////////////////////////////////////////////
// Name:       Nodo::getAnterior()
// Purpose:    Implementation of Nodo::getAnterior()
// Return:     Nodo*
////////////////////////////////////////////////////////////////////////

Nodo* Nodo::getAnterior(void)
{
   return Anterior;
}

////////////////////////////////////////////////////////////////////////
// Name:       Nodo::setAnterior(Nodo* newAnterior)
// Purpose:    Implementation of Nodo::setAnterior()
// Parameters:
// - newAnterior
// Return:     void
////////////////////////////////////////////////////////////////////////

void Nodo::setAnterior(Nodo* newAnterior)
{
   Anterior = newAnterior;
}

Empleado* Nodo :: getEmpleado(void)
{
   return empleado;
}

void Nodo :: setEmpleado(Empleado* emp)
{
   empleado = emp;
}

string Nodo :: getID(void)
{
   return ID;
}

void Nodo :: setID(string newID)
{
    ID = newID;
}
#endif 