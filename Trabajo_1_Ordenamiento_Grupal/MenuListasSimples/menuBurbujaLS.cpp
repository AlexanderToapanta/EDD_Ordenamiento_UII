#include <iostream>
#include <conio.h>
#include <windows.h>
#include "menuBurbujaLS.h"
#include"Listas/ListaSimple.cpp"
enum Opciones {
    POR_CEDULA,
    POR_NOMBRE,
    POR_APELLIDO,
    ORDENAR_CARACTERES_NOMBRE,
    ORDENAR_CARACTERES_APELLIDO,
    SALIR,
    NUM_OPCIONES

};

void setConsole3Color(WORD color) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}

void mostrarMenuLC(int opcion) {
    system("cls");
    const char* opciones[] = {
    "POR_CEDULA",
    "POR_NOMBRE",
    "POR_APELLIDO",
    "ORDENAR_CARACTERES_NOMBRE",
    "ORDENAR_CARACTERES_APELLIDO",
    "SALIR"
    };

    std::cout << "  Opciones de ordenamiento r\n\n";
    for (int i = 0; i < NUM_OPCIONES; ++i) {
        if (i == opcion) {
            setConsole3Color(FOREGROUND_GREEN | FOREGROUND_INTENSITY | BACKGROUND_BLUE); // Cambiar color
            std::cout << " --> " << opciones[i] << "\n";
            setConsole3Color(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE); // Restaurar color
        }
        else {
            std::cout << "     " << opciones[i] << "\n";
        }
    }
}

void menuBurbuja() {
    int opcion = 0;
    bool continuar = true;
    ListaSimple lista;

    while (continuar) {
        mostrarMenuLC(opcion);

        int tecla = _getch();
        switch (tecla) {
        case 72: // Flecha arriba
            opcion = (opcion - 1 + NUM_OPCIONES) % NUM_OPCIONES;
            break;
        case 80: // Flecha abajo
            opcion = (opcion + 1) % NUM_OPCIONES;
            break;
        case 13: // Enter
            switch (opcion) {
                case POR_CEDULA:
                    lista.ordenarPorCedula;
                    break;
                    case POR_NOMBRE:
                        lista.ordenarPorNombre1;
                        break;
                        case POR_APELLIDO:
                            lista.ordenarPorApellido;
                            break;
                            case  ORDENAR_CARACTERES_NOMBRE:
                                lista.ordenarPorNombre1Caracter;
                                break;
                                case  ORDENAR_CARACTERES_APELLIDO:
                                    lista.ordenarPorApellidoCaracter;
                                    break;
                                case REGRESAR:
                                    continuar = false;
                                    break;
            }

        }
    }
}