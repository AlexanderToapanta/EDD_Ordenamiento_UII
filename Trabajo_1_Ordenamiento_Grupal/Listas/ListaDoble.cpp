#include "ListaDoble.h"
#include "Empleado.h"
#include <iostream>
#include <algorithm>
#include <cctype>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <filesystem>
#include <conio.h> 


using namespace std;
namespace fs = filesystem;


ListaDoble::ListaDoble() : cabeza(nullptr) {}

ListaDoble::~ListaDoble() {
    while (cabeza != nullptr) {
        Nodo* temp = cabeza;
        cabeza = cabeza->getSiguiente();
        delete temp;
    }
}

bool ListaDoble::cedulaExistente(const string& Ced) {
    // Verificar en la lista enlazada
    Nodo* actual = cabeza;
    while (actual != nullptr) {
        if (actual->getCedula() == Ced) {
            return true;
        }
        actual = actual->getSiguiente();
    }

    // Verificar en el archivo
    ifstream archivo("C:\\Users\\Usuario\\Pictures\\xd\\list.txt");
    if (archivo.is_open()) {
        string linea;
        while (getline(archivo, linea)) {
            if (linea.find("Cedula: " + Ced) != string::npos) {
                archivo.close();
                return true;
            }
        }
        archivo.close();
    }

    return false;
}

void ListaDoble::Insertar(string& N1, string& N2, string& Ape, string& Ced, int count) {
    while (cedulaExistente(Ced)) {
        cout << "La cédula ingresada ya existe. Por favor, ingrese otra cédula: ";
        cin >> Ced;
    }

    string dominio = "espe.edu.ec";
    Nodo* nuevoNodo = new Nodo(N1, N2, Ape, Ced);
    if (cabeza == nullptr) {
        cabeza = nuevoNodo;
        cola = nuevoNodo;
    }
    else {
        cola->setSiguiente(nuevoNodo);
        nuevoNodo->setAnterior(cola);
        cola = nuevoNodo;
    }
    Comprobar_existencia(N1, N2, Ape, count, nuevoNodo);

    string password = generarContrasenia(nuevoNodo);
    cout << "Contraseña generada: " << password << endl;

    string correo = crearCorreo(N1, N2, Ape, count, dominio);
    cout << "Correo generado: " << correo << endl;

    string id = crearID();
    cout << "ID generado: " << id << endl;
    nuevoNodo->setID(id);
    Empleado* emp = new Empleado(id, 0.0);
    nuevoNodo->setEmpleado(emp);

}

void ListaDoble::Comprobar_existencia(string& N1, string& N2, string& Ape, int count, Nodo* nodo) {
    count = -1;
    Nodo* actual = cabeza;

    while (actual != nullptr) {
        if (actual->getNombre1() == N1 && actual->getNombre2() == N2 && actual->getApellido() == Ape) {
            count++;
        }
        actual = actual->getSiguiente();
    }

    string correo = crearCorreo(N1, N2, Ape, count, "espe.edu.ec");
    nodo->setCorreo(correo);
}

string ListaDoble::crearCorreo(string& N1, string& N2, string& Ape, int count, string dominio) {
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

void ListaDoble::Eliminar(string& N1, string& N2, string& Ape) {
    Nodo* actual = cabeza;
    while (actual != nullptr) {
        if (actual->getNombre1() == N1 && actual->getNombre2() == N2 && actual->getApellido() == Ape) {
            if (actual->getAnterior() != nullptr) {
                actual->getAnterior()->setSiguiente(actual->getSiguiente());
            }
            else {
                cabeza = actual->getSiguiente();
            }
            if (actual->getSiguiente() != nullptr) {
                actual->getSiguiente()->setAnterior(actual->getAnterior());
            }
            else {
                cola = actual->getAnterior();
            }
            delete actual;
            cout << "Nodo eliminado" << endl;
            cout << "Correo del nodo eliminado: " << endl;
            return;
        }
        actual = actual->getSiguiente();
    }
    cout << "Nodo no encontrado para eliminar" << endl;
}

void ListaDoble::Buscar(string& N1, string& N2, string& Ape, string& Ced) {
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

void ListaDoble::guardarArchivo(const string& nombreArchivo) const {
    ofstream archivo(nombreArchivo, ios::app);
    if (!archivo) {
        cerr << "Error al abrir el archivo: " << nombreArchivo << endl;
        return;
    }

    Nodo* actual = cabeza;
    while (actual != nullptr) {
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
    }

    archivo.close();
    cout << "Datos guardados en el archivo: " << nombreArchivo << endl;
}


string ListaDoble::crearID() {
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
void ListaDoble::Mostrar() {
    Nodo* actual = cabeza;
    while (actual != nullptr) {
        cout << "Nombre1: " << actual->getNombre1()
            << ", Nombre2: " << actual->getNombre2()
            << ", Apellido: " << actual->getApellido()
            << ", Correo: " << actual->getCorreo()
            << ", Cedula: " << actual->getCedula() << endl;

        Empleado* emp = actual->getEmpleado();
        if (emp != nullptr) {
            cout << "ID Empleado: " << emp->getID()
                << ", Sueldo: " << emp->getSueldo() << endl;
        }
        else {
            cout << "Empleado no asignado" << endl;
        }
        actual = actual->getSiguiente();
    }
}

bool ListaDoble::validarCedula(string& Ced) {
    if (Ced.length() != 10) {
        return false;
    }
    int sum = 0;
    for (int i = 0; i < 9; ++i) {
        int num = Ced[i] - '0';
        if (i % 2 == 0) {
            num *= 2;
            if (num > 9) num -= 9;
        }
        sum += num;
    }
    int last_digit = Ced[9] - '0';
    int verifier = (10 - (sum % 10)) % 10;
    return last_digit == verifier;
}

bool ListaDoble::validarNombre(string& nombre) {
    for (char c : nombre) {
        if (!isalpha(c) && c != ' ') {
            return false;
        }
    }
    return true;
}

string ListaDoble::generarContrasenia(Nodo* cabeza) {
    const string caracteres = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
    string contrasenia;
    srand(time(0));
    for (int i = 0; i < 8; ++i) {
        contrasenia += caracteres[rand() % caracteres.length()];
    }
    return contrasenia;
}

string ListaDoble::encriptar(string& contrasenia) {
    string encriptada;
    for (char c : contrasenia) {
        encriptada += c + 3;
    }
    return encriptada;
}

void ListaDoble::ingresarSueldo(string& Ced, double sueldo) {
    Nodo* actual = cabeza;
    while (actual != nullptr) {
        if (actual->getCedula() == Ced) {
            Empleado* emp = actual->getEmpleado();
            if (emp != nullptr) {
                emp->setSueldo(sueldo);
                cout << "Sueldo actualizado para la cédula: " << Ced << endl;
                return;
            }
            else {
                cout << "Empleado no encontrado para la cédula: " << Ced << endl;
                return;
            }
        }
        actual = actual->getSiguiente();
    }
    cout << "Cédula no encontrada: " << Ced << endl;
}
double ingresarSueldos(const char* msj) {
    char dato[10];
    char c;
    int i = 0;
    bool puntoIngresado = false;

    cout << msj << ": ";
    while ((c = _getch()) != 13) {
        if ((isdigit(c) || c == '.') && i < 9) {
            // Si es un dígito o un punto y no se ha ingresado el punto o no se han ingresado más de dos decimales
            if (c == '.') {
                if (!puntoIngresado) {
                    puntoIngresado = true;
                    dato[i++] = c;
                    cout << c;
                }
            }
            else {
                dato[i++] = c;
                cout << c;
            }
        }
        else if (c == 8 || c == 127) {
            // Si se presiona retroceso para borrar
            if (i > 0) {
                cout << "\b \b";
                if (dato[i - 1] == '.') {
                    puntoIngresado = false;
                }
                i--;
            }
        }
    }

    dato[i] = '\0';  // Agregar el carácter nulo al final de la cadena

    double sueldo = atof(dato);  // Convertir la cadena a double

    cout << endl;

    return sueldo;
}


void ListaDoble::ordenarPorCedula() {
    if (cabeza == nullptr) {
        cout << "La lista está vacía." << endl;
        return;
    }
    ordenarListaDoble(cabeza, [](const Nodo& a, const Nodo& b) {
        return a.getCedula() > b.getCedula();
        });
}

void ListaDoble::ordenarPorNombre1() {
    ordenarListaDoble(cabeza, [](const Nodo& a, const Nodo& b) {
        return a.getNombre1() > b.getNombre1();
        });
}

void ListaDoble::ordenarPorApellido() {
    ordenarListaDoble(cabeza, [](const Nodo& a, const Nodo& b) {
        return a.getApellido() > b.getApellido();
        });
}

template <typename Compare>
void ListaDoble::ordenarListaDoble(Nodo* cabeza, Compare comp) {
    if (!cabeza) return;

    bool intercambiado;
    Nodo* actual;

    do {
        intercambiado = false;
        actual = cabeza;

        while (actual->getSiguiente() != nullptr) {
            Nodo* siguiente = actual->getSiguiente();
            if (comp(*actual, *siguiente)) {
                // Intercambiar los valores de los nodos
                std::string temp;

                temp = actual->getCedula();
                actual->setCedula(siguiente->getCedula());
                siguiente->setCedula(temp);

                temp = actual->getNombre1();
                actual->setNombre1(siguiente->getNombre1());
                siguiente->setNombre1(temp);

                temp = actual->getNombre2();
                actual->setNombre2(siguiente->getNombre2());
                siguiente->setNombre2(temp);

                temp = actual->getApellido();
                actual->setApellido(siguiente->getApellido());
                siguiente->setApellido(temp);

                temp = actual->getCorreo();
                actual->setCorreo(siguiente->getCorreo());
                siguiente->setCorreo(temp);

                intercambiado = true;
            }
            actual = siguiente;
        }
    } while (intercambiado);
}

auto compCedulaDoble = [](const Nodo& a, const Nodo& b) {
    return a.getCedula() > b.getCedula();
    };

auto compNombre1Doble = [](const Nodo& a, const Nodo& b) {
    return a.getNombre1() > b.getNombre1();
    };

auto compApellidoDoble = [](const Nodo& a, const Nodo& b) {
    return a.getApellido() > b.getApellido();
    };

void ListaDoble::mostrarLista() {
    if (!cabeza) return;

    Nodo* actual = cabeza;
    do {
        cout << "Cedula: " << actual->getCedula() <<
            ",\nNombre1: " << actual->getNombre1() <<
            ",\nNombre2: " << actual->getNombre2() <<
            ",\nApellido: " << actual->getApellido() << endl;
        actual = actual->getSiguiente();
    } while (actual != cabeza);
}