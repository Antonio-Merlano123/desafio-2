#ifndef MATRIZDINAMICA_H
#define MATRIZDINAMICA_H

class matrizdinamica {
public:
    // matriz int con bloque lineal interno
    matrizdinamica();
    matrizdinamica(int filasbase, int columnasbase);
    ~matrizdinamica();

    bool redimensionar(int nuevasfilas, int nuevascolumnas);
    void limpiar();

    int getfilas() const;
    int getcolumnas() const;

    bool setvalor(int fila, int columna, int valor);
    int getvalor(int fila, int columna) const;

private:
    int* datos;
    int filas;
    int columnas;

    int calcularindice(int fila, int columna) const;
    bool posicionvalida(int fila, int columna) const;
};

#endif // MATRIZDINAMICA_H
