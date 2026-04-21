#ifndef TORNEO_H
#define TORNEO_H

#include <string>

#include "grupo.h"
#include "tablaposiciones.h"

using namespace std;

class Torneo {
public:
    Torneo();
    ~Torneo();

    void preparar();
    void iniciargrupos(int cantidad);
    bool registrargrupobase(int indice, string nombregrupo);
    bool cargarequipotabla(int fila, string nombreequipo);
    int getcantidadgrupos() const;

private:
    string nombretorneo;
    grupo* grupos;
    int cantidadgrupos;
    tablaposiciones* tabla;
    int cantidadfilastabla;
};

#endif // TORNEO_H
