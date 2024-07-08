#pragma once
#include "Nodo.cpp"
#include "Empleado.cpp"
#include <string>
#include <algorithm>
#include <cctype>

class ListaDoble {
public:
    ListaDoble();
    ~ListaDoble();

    void Insertar(string& N1, string& N2, string& Ape, string& Ced, int count);
    void Eliminar(string& N1, string& N2, string& Ape);
    void Buscar(string& N1, string& N2, string& Ape, string& Ced);
    void Comprobar_existencia(string& N1, string& N2, string& Ape, int count, Nodo* nodo);
    string crearCorreo(string& N1, string& N2, string& Ape, int count, string dominio = "espe.edu.ec");
    void guardarArchivo(const string& nombreArchivo)const;
    void Mostrar();
    bool validarCedula(string& Ced);
    bool validarNombre(string& nombre);
    string generarContrasenia(Nodo* cabeza);
    string encriptar(string& contrasenia);
    string crearID();
    void ingresarSueldo(string& Ced, double sueldo);
    bool cedulaExistente(const string& Ced);

    void mostrarLista();
    void ordenarPorCedula();
    void ordenarPorNombre1();
    void ordenarPorApellido();


private:

    template <typename Compare>
    void ordenarListaDoble(Nodo* cabeza, Compare comp);
    Nodo* cabeza;
    Nodo* cola;
    Empleado emp;
};



