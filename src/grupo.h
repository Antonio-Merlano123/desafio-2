#ifndef GRUPO_H
#define GRUPO_H

#include <string>

using namespace std;

class grupo {
public:
    grupo();
    grupo(string nombregrupo);

    void setnombre(string nuevonombre);
    string getnombre() const;

    bool agregarequipo(string nombreequipo);
    string getequipo(int pos) const;
    int getcantidad() const;
    bool estalleno() const;

private:
    string nombre;
    string equipos[4];
    int cantidad;
};

#endif // GRUPO_H
