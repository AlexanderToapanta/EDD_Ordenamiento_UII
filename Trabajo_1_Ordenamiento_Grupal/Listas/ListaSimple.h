#pragma once
#include "Nodo.cpp"
#include "Empleado.cpp"
#include <string>
#include <algorithm>
#include <cctype>




template <typename T, typename Compare>
void ordenarLista(T* cabeza, Compare comp);
template <typename T>
void ordenarCaracter(T* cabeza, std::string(T::* getter)() const, void (T::* setter)(const std::string&));

class ListaSimple {
public:
    ListaSimple();
    ~ListaSimple();

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
    string desencriptar(string& contrasenia);
    string crearID();
    void ingresarSueldo(string& Ced, double sueldo);
    bool cedulaExistente(const string& Ced);

    void mostrarLista();


    void ordenarPorCedula();
    void ordenarPorNombre1();
    void ordenarPorApellido();

    void ordenarPorNombre1Caracter();
    void ordenarPorApellidoCaracter();

private:
    Nodo* cabeza;
    Empleado emp;
};

