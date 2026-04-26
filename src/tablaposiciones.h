#ifndef TABLAPOSICIONES_H
#define TABLAPOSICIONES_H

#include <string>

using namespace std;

class tablaposiciones {
public:
    // fila de tabla para fase de grupos
    tablaposiciones();

    void cargarequipo(string nombreequipo);
    string getnombre() const;

    void sumarganado();
    void sumarperdido();
    void sumarempate();
    void sumargoles(int afavor, int encontra);

    int getpuntos() const;
    int getgolesfavor() const;
    int getgolescontra() const;
    int getpartidos() const;
    int getdiferencia() const;

private:
    string nombre;
    int puntos;
    int golesfavor;
    int golescontra;
    int partidos;
};

#endif // TABLAPOSICIONES_H
