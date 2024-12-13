#ifndef LECTOR_ARCHIVO_H
#define LECTOR_ARCHIVO_H

#include "Convertir_Datos.h"

#include <string>

using namespace std;

class Lector_Archivo
{

public:
    Lector_Archivo(string nombre_archivo = "", string *ptr = NULL, int N = 0, bool Datos_Convertidos = false, double **datos_flotantes = NULL, int *columnas = NULL, int *filas_errores = NULL, int *columnas_errores = NULL, int errores = 0, int med = 0, string nombre_archivo_corregido = "");
    Lector_Archivo &operator=(Lector_Archivo &other);
    ~Lector_Archivo();
    void Crea_Arreglo_Dinamico();
    void Imprimir_Lineas();
    void Abrir_Archivo();
    int getN();
    string *getptr();
    string getnombre_archivo();
    bool getDatos_Convertidos();
    void setN(int N);
    void setPtr(string *ptr);
    void setnombre_archivo(string nombre_archivo);
    void setDatos_Convertidos(bool Datos_Convertidos);
    void setDatos_Flotantes(double **datos_flotantes, int *columnas);
    double **getDatos_Flotantes();
    int *getColumnas_Flotantes();
    void setColumas_Flotantes(int *);
    int *getFila_Error();
    int *getColumna_Error();
    void setFila_Error(int *);
    void setColumna_Error(int *);
    int getErrores();
    void setErrores(int);
    void setMed(int);
    int getMed();
    void setNombre_Archivo_Corregido(string);
    string getNombre_Archivo_Corregido();

private:
    int N;//numero de filas
    string *ptr;//arreglo de strings
    string nombre_archivo;//nombre del archivo
    bool Datos_Convertidos;//bandera para saber si los datos ya fueron convertidos
    double **datos_flotantes;//arreglo de flotantes
    int *columnas;//arreglo que contiene el numero de columnas de cada fila
    int *filas_errores;//arreglo que contiene las filas con errores
    int *columnas_errores;//arreglo que contiene las columnas con errores
    int errores;//numero de errores
    int med;//bandera para saber por que metodo se corrigieron los errores
    string nombre_archivo_corregido;//nombre del archivo corregido
};

#endif
