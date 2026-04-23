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
    int getcantidadequipos() const;
    string getequipo(int indice) const;
    string getconfederacion(int indice) const;
    int getranking(int indice) const;

private:
    static const int maxequipos = 64;

    int filascsv;
    int columnascsv;
    int cantidadequipos;

    string rutacsv;
    string equiposcsv[maxequipos];
    string confederacionescsv[maxequipos];
    int rankingscsv[maxequipos];
};

#endif // REPOSITORIO_H
