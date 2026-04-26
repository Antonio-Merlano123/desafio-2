#ifndef GRUPO_H
#define GRUPO_H

#include <string>

using namespace std;

class grupo {
public:
    // grupo de 4 con regla de confederaciones
    grupo();
    grupo(string nombregrupo);

    void setnombre(string nuevonombre);
    string getnombre() const;

    bool agregarequipo(string nombreequipo);
    bool agregarequipo(string nombreequipo, string confederacion);
    bool puedeagregarconfederacion(string confederacion) const;
    string getequipo(int pos) const;
    string getconfederacion(int pos) const;
    int getcantidad() const;
    bool estalleno() const;
    void limpiar();

private:
    // almacenamiento fijo para evitar estructuras externas
    string nombre;
    string equipos[4];
    string confederaciones[4];
    int cantidad;
};

#endif // GRUPO_H
