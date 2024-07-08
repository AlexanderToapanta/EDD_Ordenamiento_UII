/***********************************************************************
 * Module:  Nodo.h
 * Author:  Usuario
 * Modified: mi�rcoles, 29 de mayo de 2024 18:58:15
 * Purpose: Declaration of the class Nodo
 ***********************************************************************/
#ifndef NODO_H
#define NODO_H

#include <iostream>
#include <string>
#include "Empleado.h"

using namespace std;

class Nodo {
private:
    string Nombre1;
    string Nombre2;
    string Apellido;
    string Correo;
    string Cedula;
    Nodo* Siguiente;
    Nodo* Anterior;
    Empleado* empleado;
    string ID;
    
public:
    string getNombre2(void) const;
    void setNombre2(string newNombre2);
    Nodo(string N1,  string N2, string Ape,string Ced ,Nodo* S = nullptr, Nodo* A = nullptr);
    ~Nodo();
    string getNombre1(void)const;
    string getCorreo(void);
    void setNombre1(const string& newNombre1);
    void setCorreo(string newCorreo);
    string getApellido(void) const;
    void setApellido(const string& newApellido);
    Nodo* getSiguiente(void);
    void setSiguiente(Nodo* newSiguiente);
    Nodo* getAnterior(void);
    void setAnterior(Nodo* newAnterior);
    string getCedula(void) const;
    void setCedula(const string& newCedula);
    Empleado* getEmpleado(void);
    void setEmpleado(Empleado* emp);
    string getID(void);
    void setID(string newID);

};
#endif // NODO_H