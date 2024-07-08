#include "ListaSimple.h"
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


ListaSimple::ListaSimple() : cabeza(nullptr) {}

ListaSimple::~ListaSimple() {
    while (cabeza != nullptr) {
        Nodo* temp = cabeza;
        cabeza = cabeza->getSiguiente();
        delete temp;
    }
}

bool ListaSimple::cedulaExistente(const std::string& Ced) {
    // Verificar en la lista enlazada
    Nodo* actual = cabeza;
    while (actual != nullptr) {
        if (actual->getCedula() == Ced) {
            return true;
        }
        actual = actual->getSiguiente();
    }

    // Verificar en el archivo de empleados (ajustar según el formato real del archivo)
    ifstream archivo("list.txt");
    if (archivo.is_open()) {
        std::string linea;
        while (getline(archivo, linea)) {
            size_t pos = linea.find("Cedula: ");
            if (pos != std::string::npos) {
                std::string cedulaArchivo = linea.substr(pos + 8, 10); // Suponiendo cédula tiene 10 caracteres
                if (cedulaArchivo == Ced) {
                    archivo.close();
                    return true;
                }
            }
        }
        archivo.close();
    }
    else {
        cerr << "Error al abrir el archivo de empleados." << endl;
    }

    return false;
}

void ListaSimple::Insertar(std::string& N1, std::string& N2, std::string& Ape, std::string& Ced, int count) {
    while (cedulaExistente(Ced)) {
        std::cout << "La cédula ingresada ya existe. Por favor, ingrese otra cédula: ";
        std::cin >> Ced;
    }

    // Crear el nuevo nodo con la cédula válida y continuar con la inserción
    string dominio = "espe.edu.ec";
    Nodo* nuevoNodo = new Nodo(N1, N2, Ape, Ced);
    if (cabeza == nullptr) {
        cabeza = nuevoNodo;
    }
    else {
        Nodo* actual = cabeza;
        while (actual->getSiguiente() != nullptr) {
            actual = actual->getSiguiente();
        }
        actual->setSiguiente(nuevoNodo);
    }

    // Resto del código para generar contraseña, correo, ID, etc.
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


void ListaSimple::Comprobar_existencia(string& N1, string& N2, string& Ape, int count, Nodo* nodo) {
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

string ListaSimple::crearCorreo(string& N1, string& N2, string& Ape, int count, string dominio) {
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

void ListaSimple::Eliminar(string& N1, string& N2, string& Ape) {
    Nodo* actual = cabeza;
    Nodo* anterior = nullptr;

    while (actual != nullptr) {
        if (actual->getNombre1() == N1 && actual->getNombre2() == N2 && actual->getApellido() == Ape) {
            if (anterior == nullptr) {
                cabeza = actual->getSiguiente();
            }
            else {
                anterior->setSiguiente(actual->getSiguiente());
            }

            delete actual;
            cout << "Nodo eliminado" << endl;
            return;
        }

        anterior = actual;
        actual = actual->getSiguiente();
    }

    cout << "Nodo no encontrado para eliminar" << endl;
}

void ListaSimple::Buscar(string& N1, string& N2, string& Ape, string& Ced) {
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

void ListaSimple::guardarArchivo(const string& nombreArchivo) const {
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
            << ", Cedula: " << actual->getCedula() << endl;

        // Aquí podrías incluir más información según necesites (ID, sueldo, etc.)

        actual = actual->getSiguiente();
    }

    archivo.close();
    cout << "Datos guardados en el archivo: " << nombreArchivo << endl;
}


string ListaSimple::crearID() {
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
void ListaSimple::Mostrar() {
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

bool ListaSimple::validarCedula(string& Ced) {
    if (Ced.length() != 10) {
        cout << "La longitud de la cédula no es correcta." << endl;
        return false;
    }

    // Verificar que todos los caracteres sean dígitos
    for (char c : Ced) {
        if (!isdigit(c)) {
            cout << "La cédula debe contener solo dígitos." << endl;
            return false;
        }
    }

    int suma = 0;
    for (int i = 0; i < 9; i++) {
        int digito = Ced[i] - '0';  // Convertir char a int
        if (i % 2 == 0) {  // Posiciones pares (considerando que i inicia en 0)
            digito *= 2;
            if (digito > 9) {
                digito -= 9;
            }
        }
        suma += digito;
    }

    int digitoVerificador = Ced[9] - '0';  // Convertir char a int
    int resultado = 10 - (suma % 10);
    if (resultado == 10) {
        resultado = 0;
    }

    if (digitoVerificador != resultado) {
        cout << "La cédula ingresada no es válida." << endl;
        return false;
    }

    return true;
}

bool ListaSimple::validarNombre(string& nombre) {
    for (char c : nombre) {
        if (!isalpha(c) && c != ' ') {
            return false;
        }
    }
    return true;
}

string ListaSimple::generarContrasenia(Nodo* cabeza) {
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
    string contraseniaNumero = contrasenia;


    contrasenia = encriptar(contraseniaNumero);

    return contrasenia;
}


string ListaSimple::encriptar(string& contrasenia) {
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

string ListaSimple::desencriptar(string& contrasenia) {
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


void ListaSimple::ingresarSueldo(string& Ced, double sueldo) {
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
double ingresarSueldo(const char* msj) {
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
char* ingresarLetras(const char* msj) {
    static char dato[25];
    char c;
    int i = 0;
    std::cout << msj << ": ";

    while ((c = _getch()) != 13) {
        if (isalpha(c) || c == 8 || c == 127) {
            if (c == 8 || c == 127) {
                if (i > 0) {
                    std::cout << "\b \b";
                    i--;
                }
            }
            else {
                dato[i++] = c;
                std::cout << c;
            }
        }
    }

    dato[i] = '\0';
    std::cout << std::endl;
    return dato;
}

char* ingresarNumeros(const char* msj) {
    static char dato[25];
    char c;
    int i = 0;
    cout << msj << ": ";
    while ((c = _getch()) != 13) {
        if (c >= '0' && c <= '9') {
            dato[i++] = c;
            cout << c;
        }
    }
    dato[i] = '\0';
    cout << endl;
    return dato;
}

void ListaSimple::ordenarPorCedula() {
    if (cabeza == nullptr) {
        cout << "La lista está vacía." << endl;
        return;
    }
    ordenarLista(cabeza, [](const Nodo& a, const Nodo& b) {
        return a.getCedula() > b.getCedula();
        });
}

void ListaSimple::ordenarPorNombre1() {
    ordenarLista(cabeza, [](const Nodo& a, const Nodo& b) {
        return a.getNombre1() > b.getNombre1();
        });
}

void ListaSimple::ordenarPorApellido() {
    ordenarLista(cabeza, [](const Nodo& a, const Nodo& b) {
        return a.getApellido() > b.getApellido();
        });
}

template <typename T, typename Compare>
void ordenarLista(T* cabeza, Compare comp) {
    if (!cabeza) return;

    bool intercambiado;
    T* actual;

    do {
        intercambiado = false;
        actual = cabeza;

        while (actual->getSiguiente() != nullptr) {
            T* siguiente = actual->getSiguiente();
            if (comp(*actual, *siguiente)) {
                // Intercambiar los valores
                string tmpCedula = actual->getCedula();
                string tmpNombre1 = actual->getNombre1();
                string tmpNombre2 = actual->getNombre2();
                string tmpApellido = actual->getApellido();
                string tmpCorreo = actual->getCorreo();

                actual->setCedula(siguiente->getCedula());
                actual->setNombre1(siguiente->getNombre1());
                actual->setNombre2(siguiente->getNombre2());
                actual->setApellido(siguiente->getApellido());
                actual->setCorreo(siguiente->getCorreo());

                siguiente->setCedula(tmpCedula);
                siguiente->setNombre1(tmpNombre1);
                siguiente->setNombre2(tmpNombre2);
                siguiente->setApellido(tmpApellido);
                siguiente->setCorreo(tmpCorreo);

                intercambiado = true;
            }
            actual = siguiente;
        }
    } while (intercambiado);
}

void ListaSimple::ordenarPorNombre1Caracter() {
    ordenarCaracter(cabeza, &Nodo::getNombre1, &Nodo::setNombre1);
}

void ListaSimple::ordenarPorApellidoCaracter() {
    ordenarCaracter(cabeza, &Nodo::getApellido, &Nodo::setApellido);
}




template <typename T>
void ordenarCaracter(T* cabeza, std::string(T::* getter)() const, void (T::* setter)(const std::string&)) {
    if (!cabeza) return;

    auto convertirAMayusculas = [](std::string& str) {
        std::transform(str.begin(), str.end(), str.begin(), ::toupper);
        };

    auto ordenarString = [](std::string& str) {
        std::sort(str.begin(), str.end());
        };

    T* actual = cabeza;

    while (actual != nullptr) {
        std::string valor = (actual->*getter)();

        convertirAMayusculas(valor);
        ordenarString(valor);

        (actual->*setter)(valor);

        actual = actual->getSiguiente();
    }
}


void ListaSimple::mostrarLista() {
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