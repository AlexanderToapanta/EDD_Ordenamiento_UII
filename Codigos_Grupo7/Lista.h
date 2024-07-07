/**********************************************************/
/*       UNIVERSIDAD DE LAS FUEZAS ARMADAS-ESPE           */
/*                 PRUEBA 1 -PARCIAL II                   */
/*         AUTORES: REISHEL TIPAN, JORDY VISCAINO         */
/*            FECHA DE CREACIÓN: 05/07/2024               */
/*            FECHA DE MODIFICACIÓN: 05/07/2024           */
/**********************************************************/

#ifndef LISTA_H
#define LISTA_H

#include <iostream>
#include <unordered_set>
#include <algorithm>
#include "Nodo.h"
#include "Persona.h"

template <typename T>
class Lista {
private:
    Nodo<T>* cabeza;
    Nodo<T>* cola;
    bool esCircular;
    std::unordered_set<std::string> cedulasRegistradas;  // Agregar conjunto para cédulas registradas

    std::string generarCorreo(T& persona) {
        Nodo<T>* auxiliar = cabeza;
        std::string inicialesNombre = "";
        inicialesNombre.push_back(tolower(persona.nombre[0]));
        inicialesNombre.push_back(tolower(persona.segundoNombre[0]));
        std::string correo = inicialesNombre + persona.apellido;
        std::string correoBase = correo;
        int contador = 0;

        while (auxiliar != nullptr) {
            if (auxiliar->dato.getCorreo() == correo) {
                contador++;
                correo = correoBase + std::to_string(contador);
            }
            auxiliar = auxiliar->siguiente;
            if (esCircular && auxiliar == cabeza) break;
        }

        return correo;
    }

    std::string generarContrasena(T& persona) {
        static bool primerUsuario = true;
        static int contador = 1;

        std::string apellido = persona.apellido;
        std::string primerNombre = persona.nombre;
        std::string segundoNombre = persona.segundoNombre;

        char ultimaLetraApellido = tolower(apellido.back());
        char primeraLetraPrimerNombre = tolower(primerNombre.front());
        char ultimaLetraSegundoNombre = tolower(segundoNombre.back());

        std::string restoApellido = apellido.substr(0, apellido.size() - 1);
        std::reverse(restoApellido.begin(), restoApellido.end());
        std::transform(restoApellido.begin(), restoApellido.end(), restoApellido.begin(), ::tolower);

        std::string contrasenaBase = std::string(1, ultimaLetraApellido) + primeraLetraPrimerNombre + ultimaLetraSegundoNombre + restoApellido;
        std::string contrasenaEncriptada = "";

        int shift = 2;
        for (char c : contrasenaBase) {
            if (isalnum(c)) {
                char base = (isdigit(c) ? '0' : (isupper(c) ? 'A' : 'a'));
                char encryptedChar = (c - base + shift) % 26 + base;
                contrasenaEncriptada += encryptedChar;
            } else {
                contrasenaEncriptada += c;
            }
        }

        if (!primerUsuario) {
            contrasenaBase += std::to_string(contador);
            contador++;
        }

        primerUsuario = false;

        persona.setContrasena(contrasenaEncriptada);
        persona.setContrasenaInicial(contrasenaBase);
        return contrasenaEncriptada;
    }

    std::string desencriptarContrasena(T& persona) {
        std::string contrasenaBase = persona.getContrasenaInicial(); 
        std::string contrasenaDesencriptada = "";

        int shift = 2;
        for (char c : persona.getContrasena()) {
            if (isalpha(c)) {
                char base = isupper(c) ? 'A' : 'a';
                char decryptedChar = (c - base - shift + 26) % 26 + base; 
                contrasenaDesencriptada += decryptedChar;
            } else {
                contrasenaDesencriptada += c;
            }
        }

        return contrasenaDesencriptada;
    }
    
    void shellSortPersonas(int criterio) {
    if (!cabeza || cabeza == cola) return;

    int n = 0;
    Nodo<T>* actual = cabeza;
    do {
        n++;
        actual = actual->siguiente;
    } while (actual != (esCircular ? cabeza : nullptr));

    for (int gap = n / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < n; i++) {
            Nodo<T>* temp = cabeza;
            for (int k = 0; k < i; k++) temp = temp->siguiente;

            T tempDato = temp->dato;
            Nodo<T>* jNodo = temp;
            for (int j = i; j >= gap; j -= gap) {
                Nodo<T>* jGapNodo = cabeza;
                for (int k = 0; k < j - gap; k++) jGapNodo = jGapNodo->siguiente;
                
                bool debeIntercambiar = false;
                switch (criterio) {
                    case 1:
                        debeIntercambiar = jGapNodo->dato.nombre > tempDato.nombre;
                        break;
                    case 2:
                        debeIntercambiar = jGapNodo->dato.apellido > tempDato.apellido;
                        break;
                    case 3:
                        debeIntercambiar = jGapNodo->dato.cedula > tempDato.cedula;
                        break;
                }

                if (!debeIntercambiar) break;

                jNodo->dato = jGapNodo->dato;
                jNodo = jGapNodo;
                }
                jNodo->dato = tempDato;
            }
        }
    }

    void shellSort(std::string &str) {
       
        std::transform(str.begin(), str.end(), str.begin(), ::tolower);
        
        int n = str.length();
        
        for (int gap = n / 2; gap > 0; gap /= 2) {
            for (int i = gap; i < n; i++) {
                char temp = str[i];
                int j;
                for (j = i; j >= gap && str[j - gap] > temp; j -= gap) {
                    str[j] = str[j - gap];
                }
                str[j] = temp;
            }
        }
    }

public:
    Lista(bool circular = false) : cabeza(nullptr), cola(nullptr), esCircular(circular) {}

    ~Lista() {
        if (!esCircular) {
            Nodo<T>* actual = cabeza;
            while (actual != nullptr) {
                Nodo<T>* temp = actual;
                actual = actual->siguiente;
                delete temp;
            }
        } else {
            Nodo<T>* actual = cabeza;
            if (actual) {
                do {
                    Nodo<T>* temp = actual;
                    actual = actual->siguiente;
                    delete temp;
                } while (actual != cabeza);
            }
        }
    }

    bool verificarCedula(const string& cedula) {
        return cedulasRegistradas.find(cedula) != cedulasRegistradas.end();
    }

    void insertar(T dato) {
        if (verificarCedula(dato.cedula)) {
            cout << "La cadula ya esta registrada" << endl;
            return;
        }

        dato.setCorreo(generarCorreo(dato));
        generarContrasena(dato);
        Nodo<T>* nuevo = new Nodo<T>(dato);
        if (!cabeza) {
            cabeza = nuevo;
            cola = nuevo;
            if (esCircular) {
                cabeza->siguiente = cabeza;
                cabeza->anterior = cabeza;
            }
        } else {
            if (esCircular) {
                nuevo->siguiente = cabeza;
                nuevo->anterior = cola;
                cola->siguiente = nuevo;
                cabeza->anterior = nuevo;
                cola = nuevo;
            } else {
                cola->siguiente = nuevo;
                nuevo->anterior = cola;
                cola = nuevo;
            }
        }

        cedulasRegistradas.insert(dato.cedula);  
    }

    void ordenar(int criterio) {
        if (criterio >= 1 && criterio <= 3) {
            shellSortPersonas(criterio);
        } else if (criterio == 4) {
            ordenarCaracteres();
        }
    }


    void ordenarCaracteres() {
        Nodo<T>* actual = cabeza;
        while (actual != nullptr) {
            shellSort(actual->dato.nombre);
            shellSort(actual->dato.apellido);
            actual = actual->siguiente;
            if (esCircular && actual == cabeza) break;
        }
    }

    void imprimir() const {
        if (!cabeza) return;

        Nodo<T>* actual = cabeza;
        do {
            std::cout << "Nombre: " << actual->dato.nombre << " " << actual->dato.segundoNombre
                      << ", Apellido: " << actual->dato.apellido
                      << ", Cedula: " << actual->dato.cedula << std::endl;

            std::cout << "Correo: " << actual->dato.getCorreo() << "@espe.edu.ec"
                      << ", Contrasenia E: " << actual->dato.getContrasenaInicial()
                      << ", Contrasenia : " << actual->dato.getContrasena()
                      << std::endl;
            actual = actual->siguiente;
        } while (actual != (esCircular ? cabeza : nullptr));
    }
};

#endif
