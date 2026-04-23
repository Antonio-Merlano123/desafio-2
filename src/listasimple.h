#ifndef LISTASIMPLE_H
#define LISTASIMPLE_H

#include <string>

using namespace std;

// lista enlazada simple, cada nodo guarda un string
class listasimple {
public:
    listasimple();
    ~listasimple();

    void agregar(string valor);
    string obtener(int pos) const;
    void eliminar(int pos);
    bool estavacia() const;
    int getcantidad() const;

private:
    // nodo interno, no necesito archivo aparte para esto
    class nodo {
    public:
        string dato;
        nodo* siguiente;

        nodo(string val) {
            dato = val;
            siguiente = 0;
        }
    };

    nodo* cabeza;
    int cantidad;
};

#endif // LISTASIMPLE_H
