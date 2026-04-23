#ifndef REPOSITORIO_H
#define REPOSITORIO_H

#include <string>

using namespace std;

class Repositorio {
public:
    Repositorio();
    void cargarBase();

    bool leercsvequipos(string ruta);
    int getfilascsv() const;
    int getcolumnascsv() const;

private:
    int filascsv;
    int columnascsv;
    string rutacsv;
};

#endif // REPOSITORIO_H
