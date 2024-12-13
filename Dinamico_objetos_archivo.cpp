#include "Dinamico_objetos_archivo.h"
#include "Lector_Archivo.h"

#include <cstdlib>
#include <iostream>

using namespace std;

Dinamico_objetos_archivo::Dinamico_objetos_archivo(Lector_Archivo *archivos, int N)
{

    this->archivos = new Lector_Archivo[N]; // se crea un nuevo arreglo de objetos de la clase Lector_Archivo

    for (int i = 0; i < N; i++)
    {
        this->archivos[i] = archivos[i]; // se copian los objetos de la clase Lector_Archivo
    }

    this->N = N;
}

Dinamico_objetos_archivo::~Dinamico_objetos_archivo()
{
    if (archivos != NULL)
    {
        delete[] archivos;
        archivos = NULL;
    }
}

void Dinamico_objetos_archivo::Cargar_Archivo(string nombre_archivo)
{
    N++; // cada vez que se carga un archivo se incrementa el numero de archivos
    Lector_Archivo *nuevo_archivos = new Lector_Archivo[N];

    for (int i = 0; i < N - 1; i++)
    {
        nuevo_archivos[i] = archivos[i]; // se copian los objetos guardados en el arreglo original en una copia para despues liberar la memoria y reasignarla
    }

    nuevo_archivos[N - 1].setnombre_archivo(nombre_archivo); // se asigna el nombre del archivo al objeto de la clase Lector_Archivo
    nuevo_archivos[N - 1].Crea_Arreglo_Dinamico();           // se llama al metodo Crea_Arreglo_Dinamico de la clase Lector_Archivo de cada objeto para cargar el archivo

    delete[] archivos;         // se libera la memoria del arreglo original
    archivos = nuevo_archivos; // se reasigna el apuntador al nuevo arreglo de objetos de la clase Lector_Archivo
}

// metodo que imprime los nombres de los archivos cargados
void Dinamico_objetos_archivo::Imprimir_Nombres()
{
    system("cls");
    cout << "Los archivos almacenados son: " << endl;
    for (int i = 0; i < N; i++)
    {
        cout << archivos[i].getnombre_archivo() << endl;
    }
}

int Dinamico_objetos_archivo::getN()
{
    return N;
}

Lector_Archivo *Dinamico_objetos_archivo::getArchivos()
{
    return archivos;
}

void Dinamico_objetos_archivo::setN(int N)
{
    this->N = N;
}

void Dinamico_objetos_archivo::setArchivos(Lector_Archivo *archivos, int N)
{
    this->archivos = archivos;
    this->N = N;
}

// cada vez que se modifica un archivo se actualiza el arreglo de objetos de la clase Lector_Archivo
void Dinamico_objetos_archivo::Actualizar_Archivo(Lector_Archivo &archivo_modificado, int indice)
{
    for (int i = 0; i < N; i++)
    {
        if (i == indice - 1)
        {
            archivos[i] = archivo_modificado; // se reemplaza el objeto de la clase Lector_Archivo en el arreglo de objetos de la clase Lector_Archivo
            break;
        }
    }
}
