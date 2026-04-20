#ifndef EQUIPO_H
#define EQUIPO_H

#include <string>

using namespace std;

class equipo {
public:
    equipo();
    equipo(string nombreinicial, string grupoinicial);

    void sumarpuntos(int valor);
    void registrargoles(int afavor, int encontra);

    string getnombre() const;
    string getgrupo() const;
    int getpuntos() const;
    int getgolesfavor() const;
    int getgolescontra() const;
    int getpartidosjugados() const;

    void setnombre(string nuevonombre);
    void setgrupo(string nuevogrupo);

private:
    string nombre;
    string grupo;
    int puntos;
    int golesfavor;
    int golescontra;
    int partidosjugados;
};

#endif // EQUIPO_H
