#include "ListaCircular.h"
#include "Empleado.h"
#include <iostream>
#include <algorithm>
#include <cctype>
#include <fstream>
#include <iomanip>
#include <filesystem>

using namespace std;

namespace fs = filesystem;

ListaCircular::ListaCircular() : cabeza(nullptr) {}

ListaCircular::~ListaCircular() {
    if (cabeza != nullptr) {
        Nodo* actual = cabeza;
        do {
            Nodo* nextNode = actual->getSiguiente();
            delete actual;
            actual = nextNode;
        } while (actual != cabeza);
    }
}

void ListaCircular::insertarNodo(Nodo* nuevoNodo) {
    if (cabeza == nullptr) {
        cabeza = nuevoNodo;
        cabeza->setSiguiente(cabeza);
    }
    else {
        Nodo* cola = cabeza;
        while (cola->getSiguiente() != cabeza) {
            cola = cola->getSiguiente();
        }
        cola->setSiguiente(nuevoNodo);
        nuevoNodo->setSiguiente(cabeza);
    }
    cout << "Nodo insertado correctamente." << endl;
}

void ListaCircular::Insertar(string& N1, string& N2, string& Ape, string& Ced, int count) {
    string dominio = "espe.edu.ec";
    Nodo* nuevoNodo = new Nodo(N1, N2, Ape, Ced);
    cout << "Insertando nodo: " << N1 << " " << N2 << " " << Ape << " " << Ced << endl;
    insertarNodo(nuevoNodo);
    Comprobar_existencia(N1, N2, Ape, count, nuevoNodo);

    string password = generarContrasenia(nuevoNodo);
    cout << "Contraseña generada: " << password << endl;

    string desencriptada = desencriptar(password);
    cout << "Contraseña desencriptada: " << desencriptada << endl;

    string correo = crearCorreo(N1, N2, Ape, count, dominio);
    cout << "Correo generado: " << correo << endl;

    string id = crearID();
    cout << "ID generado: " << id << endl;
    nuevoNodo->setID(id);
    Empleado* emp = new Empleado(id, 0.0);
    nuevoNodo->setEmpleado(emp);
    guardarArchivo("C:\\Users\\DELL\\Desktop\\Estructura_de_Datos\\TALLER_ED_1P\\list.txt");
}

void ListaCircular::Comprobar_existencia(string& N1, string& N2, string& Ape, int count, Nodo* nodo) {
    count = -1;
    Nodo* actual = cabeza;

    if (actual == nullptr) {
        return;
    }

    do {
        if (actual->getNombre1() == N1 && actual->getNombre2() == N2 && actual->getApellido() == Ape) {
            count++;
        }
        actual = actual->getSiguiente();
    } while (actual != cabeza);

    string correo = crearCorreo(N1, N2, Ape, count, "espe.edu.ec");
    nodo->setCorreo(correo);
}

string ListaCircular::crearCorreo(string& N1, string& N2, string& Ape, int count, string dominio) {
    if (N1.empty() || N2.empty() || Ape.empty()) {
        cerr << "Error: Los nombres y el apellido no deben estar vacíos" << endl;
    }

    char inicialN1 = tolower(N1[0]);
    char inicialN2 = tolower(N2[0]);

    string apellidoMinusculas = Ape;
    transform(apellidoMinusculas.begin(), apellidoMinusculas.end(), apellidoMinusculas.begin(), ::tolower);
    string correo;
    if (count <= 0) {
        correo = string(1, inicialN1) + string(1, inicialN2) + apellidoMinusculas + "@" + dominio;
    }
    else {
        correo = string(1, inicialN1) + string(1, inicialN2) + apellidoMinusculas + to_string(count) + "@" + dominio;
    }

    return correo;
}

void ListaCircular::Eliminar(string& N1, string& N2, string& Ape) {
    if (cabeza == nullptr) return;

    Nodo* actual = cabeza;
    do {
        if (actual->getNombre1() == N1 && actual->getNombre2() == N2 && actual->getApellido() == Ape) {
            if (actual->getSiguiente() == actual) {
                delete actual;
                cabeza = nullptr;
            }
            else {
                Nodo* prevNode = actual->getAnterior();
                Nodo* nextNode = actual->getSiguiente();
                prevNode->setSiguiente(nextNode);
                nextNode->setAnterior(prevNode);
                if (actual == cabeza) {
                    cabeza = nextNode;
                }
                delete actual;
            }
            return;
        }
        actual = actual->getSiguiente();
        cout << "Nodo Eliminado" << endl;
    } while (actual != cabeza);
}

void ListaCircular::Buscar(string& N1, string& N2, string& Ape, string& Ced) {
    if (cabeza == nullptr) return;

    Nodo* actual = cabeza;

    while (actual != nullptr) {
        if (actual->getNombre1() == N1 && actual->getNombre2() == N2 && actual->getApellido() == Ape) {
            cout << "Nodo encontrado:\n" << "N1 = " << actual->getNombre1()
                << ", \nNombre2 = " << actual->getNombre2()
                << ", \nApellido = " << actual->getApellido()
                << ", Correo = " << actual->getCorreo()
                << ", Cedula = " << actual->getCedula()
                << endl;
            return;
        }
        actual = actual->getSiguiente();
    }
    cout << "Nodo no encontrado" << endl;
}


void ListaCircular::guardarArchivo(const string& nombreArchivo) const {
    ofstream archivo(nombreArchivo);
    if (!archivo) {
        cerr << "Error al abrir el archivo: " << nombreArchivo << endl;
        return;
    }

    Nodo* actual = cabeza;
    if (actual == nullptr) {
        archivo << "La lista está vacía." << endl;
        archivo.close();
        cout << "Archivo vacío: " << nombreArchivo << endl;
        return;
    }

    do {
        archivo << "Nombre1: " << actual->getNombre1()
            << ", Nombre2: " << actual->getNombre2()
            << ", Apellido: " << actual->getApellido()
            << ", Correo: " << actual->getCorreo()
            << ", Cedula: " << actual->getCedula();

        Empleado* emp = actual->getEmpleado();
        if (emp != nullptr) {
            archivo << ", ID Empleado: " << emp->getID()
                << ", Sueldo: " << emp->getSueldo();
        }
        else {
            archivo << ", Empleado no asignado";
        }
        archivo << endl;

        actual = actual->getSiguiente();
    } while (actual != cabeza);

    archivo.close();
    cout << "Datos guardados en el archivo: " << nombreArchivo << endl;
}





bool ListaCircular::validarCedula(string& cedula) {
    if (cedula.length() != 10) {
        return false;
    }

    for (char c : cedula) {
        if (!isdigit(c)) {
            cout << "Ingrese solo numeros";
            return false;
        }
    }

    int suma = 0;
    for (int i = 0; i < 9; i++) {
        int digito = cedula[i] - '0';
        if (i % 2 == 0) {
            digito *= 2;
            if (digito > 9) {
                digito -= 9;
            }
        }
        suma += digito;
    }

    int digitoVerificador = cedula[9] - '0';
    int resultado = 10 - (suma % 10);
    if (resultado == 10) {
        resultado = 0;
    }

    return digitoVerificador == resultado;
}

bool ListaCircular::validarNombre(string& nombre) {
    for (char c : nombre) {
        if (isdigit(c)) {
            return false;
        }
    }
    return true;
}

string ListaCircular::generarContrasenia(Nodo* cabeza) {
    string N1 = cabeza->getNombre1();
    string N2 = cabeza->getNombre2();
    string Ape = cabeza->getApellido();

    char letraApe = tolower(Ape.back());
    char letraN1 = tolower(N1.front());
    char letraN2 = tolower(N2.back());

    string apellidoInvertido = Ape.substr(0, Ape.length() - 1);
    reverse(apellidoInvertido.begin(), apellidoInvertido.end());
    string contrasenia = string(1, letraApe) + letraN1 + letraN2 + apellidoInvertido;

    string clave = N1 + N2 + Ape;
    int& contador = contadorContrasenias[clave];
    contador++;
    string contraseniaNumero = contrasenia + to_string(contador);


    contrasenia = encriptar(contraseniaNumero);

    return contrasenia;
}


string ListaCircular::encriptar(string& contrasenia) {
    string contraseniaEncriptada = contrasenia;
    int desplazamiento = 2;
    for (char& c : contraseniaEncriptada) {
        if (isalpha(c)) {
            char base = isupper(c) ? 'A' : 'a';
            c = ((c - base + desplazamiento) % 26) + base;
        }
    }
    return contraseniaEncriptada;
}

string ListaCircular::desencriptar(string& contrasenia) {
    string contraseniaDesencriptada = contrasenia;
    int desplazamiento = 2;
    for (char& c : contraseniaDesencriptada) {
        if (isalpha(c)) {
            char base = isupper(c) ? 'A' : 'a';
            c = ((c - base - desplazamiento + 26) % 26) + base;
        }
    }
    return contraseniaDesencriptada;
}

void ListaCircular::ingresarSueldo(string& Ced, double Sueldo) {
    Nodo* actual = cabeza;
    while (actual != nullptr) {
        if (actual->getCedula() == Ced) {
            Empleado* empleado = actual->getEmpleado();
            if (empleado == nullptr) {
                empleado = new Empleado(actual->getID(), Sueldo);
                actual->setEmpleado(empleado); // Asignar el empleado al nodo
            }
            else {
                empleado->setSueldo(Sueldo);
            }
            cout << "Sueldo asignado a " << actual->getNombre1() << " " << actual->getApellido() << ": " << Sueldo << endl;
            guardarArchivo("C:\\Users\\DELL\\Desktop\\Estructura_de_Datos\\TALLER_ED_1P\\list.txt");
            return;
        }
        actual = actual->getSiguiente();
    }
    cout << "Empleado con cedula " << Ced << " no encontrado." << endl;

}



string ListaCircular::crearID() {
    int count = 0;
    string idPrefix = "ESPE-";

    ifstream archivo_contador("contador.txt");
    if (archivo_contador.is_open()) {
        archivo_contador >> count;
        archivo_contador.close();
    }
    else {
        cerr << "No se encontró el archivo contador.txt. Inicializando contador." << endl;
    }

    count++;

    ostringstream oss;
    oss << idPrefix << setfill('0') << setw(3) << count;
    string id = oss.str();

    ofstream archivo_guardar("contador.txt");
    if (archivo_guardar.is_open()) {
        archivo_guardar << count;
        archivo_guardar.close();
    }
    else {
        cerr << "Error al abrir el archivo para guardar el contador." << endl;
    }

    return id;

}

void ListaCircular::ordenarPorCedula() {
    if (cabeza == nullptr) {
        cout << "La lista está vacía." << endl;
        return;
    }

    ordenarListaDoble(cabeza, [](const Nodo& a, const Nodo& b) {
        return a.getCedula() > b.getCedula();
        });

    // Mostrar la lista ordenada por cédula
    cout << "\nLista ordenada por cédula.\n";
    Mostrar(); // Suponiendo que tienes una función Mostrar() para mostrar la lista
}

void ListaCircular::ordenarPorNombre1() {
    ordenarListaDoble(cabeza, [](const Nodo& a, const Nodo& b) {
        return a.getNombre1() > b.getNombre1();
        });
}

void ListaCircular::ordenarPorApellido() {
    ordenarListaDoble(cabeza, [](const Nodo& a, const Nodo& b) {
        return a.getApellido() > b.getApellido();
        });
}

template <typename Compare>
void ListaCircular::ordenarListaDoble(Nodo* cabeza, Compare comp) {
    if (!cabeza || !cabeza->getSiguiente() || cabeza->getSiguiente() == cabeza) {
        // Si la lista está vacía, solo tiene un elemento o es un solo nodo circular
        return;
    }

    bool intercambiado;
    Nodo* actual;
    Nodo* siguiente;

    do {
        intercambiado = false;
        actual = cabeza;

        do {
            siguiente = actual->getSiguiente();
            if (comp(*actual, *siguiente)) {
                // Almacenar temporalmente los valores del nodo actual
                std::string tempCedula = actual->getCedula();
                std::string tempNombre1 = actual->getNombre1();
                std::string tempNombre2 = actual->getNombre2();
                std::string tempApellido = actual->getApellido();
                std::string tempCorreo = actual->getCorreo();

                // Asignar los valores del siguiente nodo al nodo actual
                actual->setCedula(siguiente->getCedula());
                actual->setNombre1(siguiente->getNombre1());
                actual->setNombre2(siguiente->getNombre2());
                actual->setApellido(siguiente->getApellido());
                actual->setCorreo(siguiente->getCorreo());

                // Asignar los valores temporales al siguiente nodo
                siguiente->setCedula(tempCedula);
                siguiente->setNombre1(tempNombre1);
                siguiente->setNombre2(tempNombre2);
                siguiente->setApellido(tempApellido);
                siguiente->setCorreo(tempCorreo);

                intercambiado = true;
            }
            actual = siguiente;
        } while (actual->getSiguiente() != cabeza); // Asegurarse de no comparar con el nodo cabeza

    } while (intercambiado);
}




void ListaCircular::Mostrar() {
    if (!cabeza) {
        cout << "La lista está vacía." << endl;
        return;
    }

    Nodo* actual = cabeza;
    do {
        // Mostrar los datos del nodo actual
        cout << "Cedula: " << actual->getCedula() << endl;
        cout << "Nombre1: " << actual->getNombre1() << endl;
        cout << "Nombre2: " << actual->getNombre2() << endl;
        cout << "Apellido: " << actual->getApellido() << endl;
        cout << "Correo: " << actual->getCorreo() << endl;

        // Mover al siguiente nodo en la lista circular
        actual = actual->getSiguiente();
    } while (actual != cabeza); // Salir del bucle al regresar al inicio de la lista
}