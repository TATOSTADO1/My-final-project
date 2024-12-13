#include "Lector_Archivo.h"
#include "Convertir_Datos.h"

#include <fstream>
#include <stdexcept>
#include <iostream>

using namespace std;
// constructor de la clase Lector_Archivo
Lector_Archivo::Lector_Archivo(string nombre_archivo, string *ptr, int N, bool Datos_Convertidos, double **datos_flotantes, int *columnas, int *filas_errores, int *columnas_errores, int errores, int med, string nombre_archivo_corregido)
{
    this->nombre_archivo = nombre_archivo;
    this->ptr = ptr;
    this->N = N;
    this->Datos_Convertidos = Datos_Convertidos;
    this->datos_flotantes = datos_flotantes;
    this->columnas = columnas;
    this->filas_errores = filas_errores;
    this->columnas_errores = columnas_errores;
    this->errores = errores;
    this->med = med;
    this->nombre_archivo_corregido = nombre_archivo_corregido;
}

// sobrecarga del operador de asignacion para evitar errores de asignacion en el caso de los punteros
Lector_Archivo &Lector_Archivo::operator=(Lector_Archivo &copia)
{
    if (this != &copia)
    {
        // se asignan los valores de la clase copia a la clase original
        this->nombre_archivo = copia.nombre_archivo;
        this->N = copia.N;

        if (copia.ptr != NULL)
        {
            this->ptr = new string[N];
            for (int i = 0; i < N; i++) // se copia cada posicion del arreglo de strings ciclando hasta N que son las filas del archivo
            {
                this->ptr[i] = copia.ptr[i];
            }
        }
        else
        {
            this->ptr = NULL;
        }

        this->Datos_Convertidos = copia.Datos_Convertidos;

        if (copia.datos_flotantes != NULL)
        {
            this->datos_flotantes = new double *[N];
            this->columnas = new int[N];
            for (int i = 0; i < N; ++i)
            {
                this->datos_flotantes[i] = new double[copia.columnas[i]];
                for (int j = 0; j < copia.columnas[i]; ++j)
                {
                    this->datos_flotantes[i][j] = copia.datos_flotantes[i][j];
                }
                this->columnas[i] = copia.columnas[i];
            }
        }
        else
        {
            this->datos_flotantes = NULL;
            this->columnas = NULL;
        }

        this->errores = copia.errores;
        if (copia.filas_errores != NULL && copia.columnas_errores != NULL)
        {
            this->filas_errores = new int[errores];
            this->columnas_errores = new int[errores];

            for (int i = 0; i < errores; i++)
            {
                this->filas_errores[i] = copia.filas_errores[i];
                this->columnas_errores[i] = copia.columnas_errores[i];
            }
        }
        else
        {
            this->filas_errores = NULL;
            this->columnas_errores = NULL;
        }

        this->med = copia.med;
        this->nombre_archivo_corregido = copia.nombre_archivo_corregido;
    }
    return *this;
}

Lector_Archivo::~Lector_Archivo() // destructor de la clase Lector_Archivo
{
    if (ptr != NULL)
    {
        delete[] ptr;
        ptr = NULL;
    }

    if (datos_flotantes != NULL)
    {
        for (int i = 0; i < N; ++i)
        {
            if (datos_flotantes[i] != NULL)
            {
                delete[] datos_flotantes[i];
            }
        }
        delete[] datos_flotantes;
        datos_flotantes = NULL;
    }

    if (columnas != NULL)
    {
        delete[] columnas;
        columnas = NULL;
    }

    if (filas_errores != NULL)
    {
        delete[] filas_errores;
        filas_errores = NULL;
    }

    if (columnas_errores != NULL)
    {
        delete[] columnas_errores;
        columnas_errores = NULL;
    }
}

// metodo que crea un arreglo dinamico de strings
void Lector_Archivo::Crea_Arreglo_Dinamico()
{
    N = 0;
    ifstream arch;
    arch.open(nombre_archivo, ios::in);

    string linea;
    while (getline(arch, linea))
    {
        N++; // se cuenta la cantidad de lineas en el archivo a leer
    }

    arch.clear();  // se limpia el archivo del error eof
    arch.seekg(0); // se regresa al inicio del archivo

    ptr = new string[N];

    int i = 0;
    while (getline(arch, linea) && i < N)
    { // se llena el arreglo de strings con las lineas del archivo
        ptr[i] = linea;
        i++;
    }
    arch.close();
}

void Lector_Archivo::Imprimir_Lineas()
{
    for (int i = 0; i < N; i++) // se imprimen las lineas del archivo
    {
        cout << ptr[i] << endl;
    }
}

void Lector_Archivo::Abrir_Archivo()
{
    ifstream arch(nombre_archivo);

    if (!arch.is_open()) // se intenta abrir el archivo en caso de que no exista se lanza una excepcion
    {
        throw runtime_error("El archivo " + nombre_archivo + " no existe o no se puede abrir.");
    }

    cout << "Archivo " << nombre_archivo << " abierto correctamente." << endl;

    arch.close();
}

int Lector_Archivo::getN()
{
    return N;
}

string *Lector_Archivo::getptr()
{
    return ptr;
}

string Lector_Archivo::getnombre_archivo()
{
    return nombre_archivo;
}

bool Lector_Archivo::getDatos_Convertidos()
{
    return Datos_Convertidos;
}

void Lector_Archivo::setN(int N)
{
    this->N = N;
}

void Lector_Archivo::setPtr(string *ptr)
{
    if (this->ptr != NULL)
    {
        delete[] this->ptr;
    }
    this->ptr = ptr;
}

void Lector_Archivo::setnombre_archivo(string nombre_archivo)
{
    this->nombre_archivo = nombre_archivo;
}

void Lector_Archivo::setDatos_Convertidos(bool Datos_Convertidos)
{
    this->Datos_Convertidos = Datos_Convertidos;
}

void Lector_Archivo::setDatos_Flotantes(double **datos, int *columnas)
{
    this->datos_flotantes = datos;
    this->columnas = columnas;
}

double **Lector_Archivo::getDatos_Flotantes()
{
    return datos_flotantes;
}

int *Lector_Archivo::getColumnas_Flotantes()
{
    return columnas;
}

void Lector_Archivo::setColumas_Flotantes(int *)
{
    this->columnas = columnas;
}

int *Lector_Archivo::getFila_Error()
{
    return filas_errores;
}

int *Lector_Archivo::getColumna_Error()
{
    return columnas_errores;
}

void Lector_Archivo::setFila_Error(int *filas)
{
    filas_errores = filas;
}

void Lector_Archivo::setColumna_Error(int *columnas)
{
    columnas_errores = columnas;
}

int Lector_Archivo::getErrores()
{
    return errores;
}

void Lector_Archivo::setErrores(int errores)
{
    this->errores = errores;
}

void Lector_Archivo::setMed(int med)
{
    this->med = med;
}

int Lector_Archivo::getMed()
{
    return med;
}

void Lector_Archivo::setNombre_Archivo_Corregido(string nombre_archivo_corregido)
{
    this->nombre_archivo_corregido = nombre_archivo_corregido;
}

string Lector_Archivo::getNombre_Archivo_Corregido()
{
    return nombre_archivo_corregido;
}
