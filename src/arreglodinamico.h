#ifndef ARREGLODINAMICO_H
#define ARREGLODINAMICO_H

class arreglodinamico {
public:
    // arreglo int dinamico hecho a mano
    arreglodinamico();
    arreglodinamico(int capacidadinicial);
    ~arreglodinamico();

    bool reservar(int nuevacapacidad);
    bool agregar(int valor);
    int obtener(int indice) const;
    bool cambiar(int indice, int valor);

    int getcantidad() const;
    int getcapacidad() const;
    void limpiar();

private:
    int* datos;
    int cantidad;
    int capacidad;
};

#endif // ARREGLODINAMICO_H
