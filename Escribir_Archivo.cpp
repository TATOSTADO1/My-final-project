#include "Escribir_Archivo.h"
#include "Lector_Archivo.h"
#include "Convertir_Datos.h"

#include <fstream>
#include <string>
#include <iostream>
#include <cfloat>
#include <cmath>

using namespace std;

// se escribe el archivo tras haber convertido el archivo a flotantes y haberse corregido los errores
bool Escribir_Archivo::Escribir_Archivo_Corregido(Lector_Archivo &arch_base)
{
    ofstream arch_corregido;

    string nombre_archivo = Cambiar_Extension(arch_base.getnombre_archivo()); // se cambia la extension del archivo
    string terminos[2] = {"media", "mediana"};

    arch_corregido.open(nombre_archivo + "_corregido_" + terminos[arch_base.getMed()] + ".txt");

    // se hace una iteracion para recorrer las filas y columnas flotantes del archivo y se escribe en el archivo corregido
    for (int i = 0; i < arch_base.getN(); i++)
    {
        for (int j = 0; j < arch_base.getColumnas_Flotantes()[i]; ++j)
        {
            arch_corregido << arch_base.getDatos_Flotantes()[i][j];
            if (j < arch_base.getColumnas_Flotantes()[i] - 1)
            {
                arch_corregido << ",";
            }
        }
        arch_corregido << "\n";
    }
    arch_corregido.close();

    cout << "Archivo corregido creado correctamente." << endl;

    cout << "El archivo ha sido guardado con el nombre de: " << nombre_archivo + "_corregido_" + terminos[arch_base.getMed()] + ".txt" << endl;

    return true;
}

// se escriben los errores en un archivo con el nombre del archivo original y se le agrega "_errores.txt"
bool Escribir_Archivo::Escribir_Archivo_Errores(Lector_Archivo &arch_base)
{
    ofstream arch_errores;
    string terminos[2] = {"media", "mediana"};
    string nombre_archivo = Cambiar_Extension(arch_base.getnombre_archivo());

    arch_errores.open(nombre_archivo + "_errores_" + terminos[arch_base.getMed()] + ".txt");

    arch_errores << "El archivo: " << arch_base.getnombre_archivo() << " tiene errores en las posiciones: \n"
                 << endl;

    arch_errores << terminos[arch_base.getMed()] << endl;

    arch_errores << "Total de errores: " << arch_base.getErrores() << endl;

    vector<int> tipos_finales_unicos;
    int cant_tipos_finales = 0;
    vector<int> conteo_por_tipo;
    for (int i = 0; i < arch_base.getErrores(); i++)
    {
        int valor_final = arch_base.getDatos_Flotantes()[arch_base.getFila_Error()[i]][arch_base.getColumnas_Flotantes()[arch_base.getFila_Error()[i]] - 1]; // se guarda el valor final de la fila con error
        int existencia_tipo_final = 0;
        bool existe = false;
        for (int j = 0; j < cant_tipos_finales; j++)
        {
            if (tipos_finales_unicos[j] == valor_final) // se busca si el tipo final ya existe en el vector de tipos finales unicos
            {
                existencia_tipo_final = j; // si existe se guarda el indice
                existe = true;
                break;
            }
        }

        if (!existe) // si no existe se agrega al vector de tipos finales unicos
        {
            existencia_tipo_final = tipos_finales_unicos.size();
            tipos_finales_unicos.push_back(valor_final); // se agrega el tipo final al vector de tipos finales unicos
            conteo_por_tipo.push_back(0);                // se agrega un 0 al vector de conteo por tipo, esto para guardar la cantidad de valores por tipo
            cant_tipos_finales++;                        // se aumenta la cantidad de tipos finales diferentes
        }
        conteo_por_tipo[existencia_tipo_final]++; // se aumenta el conteo de los valores por tipo
    }

    for (int i = 0; i < cant_tipos_finales; i++)
    {
        arch_errores << "Tipo: " << tipos_finales_unicos[i] << " Cantidad: " << conteo_por_tipo[i] << endl;
    }

    arch_errores << "Filas\t\tColumnas\tTipo\t\tValor" << endl;
    // se recorren los arreglos de filas errores y columnas errores para mostrar la posiciones de los datos corregidos asi como el dato por el cual fueron corregidos
    for (int i = 0; i < arch_base.getErrores(); i++)
    {
        arch_errores << arch_base.getFila_Error()[i] - 2 << "\t\t" << arch_base.getColumna_Error()[i] + 1 << "\t\t" << arch_base.getDatos_Flotantes()[arch_base.getFila_Error()[i]][arch_base.getColumnas_Flotantes()[arch_base.getFila_Error()[i]] - 1] << "\t\t" << arch_base.getDatos_Flotantes()[arch_base.getFila_Error()[i]][arch_base.getColumna_Error()[i]] << endl;
    }
    arch_errores << endl;
    arch_errores.close();

    return true;
}

// se escribe el archivo de similitud absoluta con el nombre de los archivos originales y se le agrega "_similitud_absoluta.txt"
bool Escribir_Archivo::Escribir_Archivo_Similitud_Absoluto(vector<int> indices_similares, vector<float> similitudes, Lector_Archivo &arch_base, Lector_Archivo &arch_base2)
{
    ofstream arch_similitud;
    string nombre_archivo = Cambiar_Extension(arch_base.getnombre_archivo());

    string nombre_archivo2 = Cambiar_Extension(arch_base2.getnombre_archivo());

    arch_similitud.open(nombre_archivo + "_" + nombre_archivo2 + "_similitud_absoluta.txt");
    arch_similitud << "Similitud Absoluta" << endl;

    // se recorren los arreglos de indices similares y similitudes para mostrar la similitud entre las filas de los archivos, llamando al arreglo de similitudes y al arreglo de indices similares
    for (int i = 3; i < arch_base.getN(); i++)
    {
        arch_similitud << "La fila " << i - 2 << " del archivo 1 es mas similar a la fila " << indices_similares[i] - 2 << " del archivo 2 con una similitud de " << similitudes[i] << endl;
    }

    arch_similitud.close();
    cout << "Archivo de similitud creado correctamente." << endl;

    cout << "El archivo ha sido guardado con el nombre de: " << nombre_archivo + "_" + nombre_archivo2 + "_similitud_absoluta.txt" << endl;
    return true;
}

// se escribe el archivo de similitud bayesiana con el nombre de los archivos originales y se le agrega "_similitud_bayesiana.txt"
bool Escribir_Archivo::Escribir_Archivo_Similitud_Bayesiana(vector<float> mayores_probabilidades, vector<float> tipo_mas_similar, Lector_Archivo &arch_base, Lector_Archivo &arch_base2)
{
    ofstream arch_similitud;
    string nombre_archivo = Cambiar_Extension(arch_base.getnombre_archivo());
    string nombre_archivo2 = Cambiar_Extension(arch_base2.getnombre_archivo());
    arch_similitud.open(nombre_archivo + "_" + nombre_archivo2 + "_similitud_bayesiana.txt");
    arch_similitud << "Similitud Bayesiana" << endl;

    for (int k = 3; k < arch_base.getN(); k++)
    {
        arch_similitud << "  - Fila " << k - 2 << " del archivo 1, archivo 2: probabilidad = " << mayores_probabilidades[k] << " al tipo " << tipo_mas_similar[k] << endl;
    }

    arch_similitud.close();
    cout << "Archivo de similitud creado correctamente." << endl;
    cout << "El archivo ha sido guardado con el nombre de: " << nombre_archivo + "_" + nombre_archivo2 + "_similitud_bayesiana.txt" << endl;
    return true;
}

string Escribir_Archivo::Cambiar_Extension(string nombre_archivo)
{
    if (nombre_archivo.substr(nombre_archivo.length() - 4) == ".txt") // se verifica si la extension del archivo es .txt
    {
        nombre_archivo.erase(nombre_archivo.length() - 4); // se borra la extension .txt
    }
    return nombre_archivo;
}
