#ifndef EMPLEADO_H
#define EMPLEADO_H
#include <iostream>
#include <string>

using namespace std;

class Empleado {
private:
    double Sueldo;
    string ID;

public:
    Empleado(const string& id, double sueldo);
    Empleado();
    ~Empleado();
    string getID(void);
    double getSueldo();
    void setSueldo(double newSueldo);

};
#endif // EMPLEADO_H