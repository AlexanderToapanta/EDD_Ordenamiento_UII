/**********************************************************/
/*       UNIVERSIDAD DE LAS FUEZAS ARMADAS-ESPE           */
/*                 PRUEBA 1 -PARCIAL II                   */
/*         AUTORES: REISHEL TIPAN, JORDY VISCAINO         */
/*            FECHA DE CREACIÓN: 05/07/2024               */
/*            FECHA DE MODIFICACIÓN: 05/07/2024           */
/**********************************************************/

#ifndef PERSONA_H
#define PERSONA_H

#include <string>
#include <iostream>
#include <algorithm>

using namespace std;

struct Persona {
    string nombre;
    string segundoNombre;
    string apellido;
    string cedula;
    string correo;
    string contrasena;
    string contrasenaInicial;

    // Constructor
    Persona(string n, string sn, string a, string c) : nombre(n), segundoNombre(sn), apellido(a), cedula(c), correo("") {}

    void setCorreo(string c) {
        correo = c;
    }

    string getCorreo() const {
        return correo;
    }

    void setContrasena(string c) {
        contrasena = c;
    }

    string getContrasena() const {
        return contrasena;
    }

    void setContrasenaInicial(string ci) {
        contrasenaInicial = ci;
    }

    string getContrasenaInicial() const {
        return contrasenaInicial;
    }
};

// Sobrecarga del operador << para imprimir datos de Persona
ostream& operator<<(ostream& os, const Persona& p) {
    os << "Nombre: " << p.nombre << " " << p.segundoNombre << ", Apellido: " << p.apellido << ", Cedula: " << p.cedula << ", Correo: " << p.correo << ", Contraseña: " << p.contrasena;
    return os;
}

#endif // PERSONA_H
