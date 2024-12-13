#include "Convertir_Datos.h"

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>

Convertir_Datos::Convertir_Datos(double **num, int filas, int *columnas, int *filas_errores, int *columnas_errores, int errores, int col)
{
    this->filas = filas;
    this->errores = errores;
    this->col = col;

    if (num != nullptr)
    {
        this->num = new double *[filas];
        for (int i = 0; i < filas; ++i)
        {
            this->num[i] = new double[columnas[i]];
            for (int j = 0; j < columnas[i]; ++j)
            {
                this->num[i][j] = num[i][j];
            }
        }
    }
    else
    {
        this->num = nullptr;
    }

    if (columnas != nullptr)
    {
        this->columnas = new int[filas];
        for (int i = 0; i < filas; ++i)
        {
            this->columnas[i] = columnas[i];
        }
    }
    else
    {
        this->columnas = nullptr;
    }

    if (errores > 0)
    {
        this->filas_errores = new int[errores];
        this->columnas_errores = new int[errores];
        for (int i = 0; i < errores; ++i)
        {
            this->filas_errores[i] = filas_errores[i];
            this->columnas_errores[i] = columnas_errores[i];
        }
    }
    else
    {
        this->filas_errores = nullptr;
        this->columnas_errores = nullptr;
    }
}

Convertir_Datos::~Convertir_Datos()
{
    if (num != nullptr)
    {
        for (int i = 0; i < filas; ++i)
        {
            delete[] num[i];
        }
        delete[] num;
    }

    delete[] columnas;

    delete[] filas_errores;
    delete[] columnas_errores;
}

void Convertir_Datos::Flotantes(string *ptr, int N)
{
    filas = N; // numero de filas que se pasa por parametro desde la clase Lector_Archivo

    num = new double *[filas];  // se crea un arreglo dinamico de flotantes con el numero de filas
    columnas = new int[filas]; // se crea un arreglo dinamico de enteros con el numero de filas
    errores = 0;

    for (int i = 0; i < filas; i++)
    {
        stringstream linea(ptr[i]);
        string seccion;
        col = 0;

        while (getline(linea, seccion, ','))
        {
            col++; // se cuenta el numero de columnas en cada fila segun la iteracion
        }

        columnas[i] = col;       // se asigna el numero de columnas en cada fila al arreglo de columnas
        num[i] = new double[col]; // se crea un arreglo dinamico de flotantes con el numero de columnas en cada fila, es decir en cada fila el arreglo dinamico tendra la extension de columnas[i]

        linea.clear();     // se limpia la linea para poder volver a usarla
        linea.str(ptr[i]); // se asigna la linea a la cadena de texto que se pasa por parametro, ya que durante el proceso de contar las columnas se movio el puntero de la cadena de texto

        int j = 0;

        while (getline(linea, seccion, ','))
        {
            try
            {
                num[i][j] = stod(seccion); // se convierte la cadena de texto a flotante y se asigna a la matriz de flotantes
            }
            catch (invalid_argument &e) // se maneja la excepcion de que la cadena de texto no sea un flotante
            {
                // se crean nuevos arreglos dinamicos de enteros para las filas y columnas con errores
                int *new_filas_errores = new int[errores + 1];
                int *new_columnas_errores = new int[errores + 1];

                for (int k = 0; k < errores; k++) // se copian los valores de los arreglos anteriores a los nuevos arreglos, esto cada vez que se encuentre un error
                {
                    new_filas_errores[k] = filas_errores[k];
                    new_columnas_errores[k] = columnas_errores[k];
                }

                delete[] filas_errores; // se eliminan los arreglos anteriores
                delete[] columnas_errores;

                filas_errores = new_filas_errores; // se reasigna el puntero de los arreglos a los nuevos arreglos
                columnas_errores = new_columnas_errores;

                // se asignan las posicion de la fila y columna con error y se incrementa el numero de errores
                filas_errores[errores] = i;
                columnas_errores[errores] = j;
                errores += 1;
            }
            j++;
        }
    }

    if (errores == 0)
    {
        cout << "No hay errores en los datos" << endl;
    }
    else
    {
        cout << "Se encontraron errores en los datos" << endl;
        Menu_2();
    }
}

void Convertir_Datos::Restaurar_Datos_Media()
{
    double acumulador = 0;
    double promedio = 0;
    int cont_num_filas_terminacion_igual = 0;

    for (int i = 0; i < errores; i++)
    {
        acumulador = 0;
        cont_num_filas_terminacion_igual = 0;
        int fila_error = filas_errores[i];
        int columna_error = columnas_errores[i];
        double ultimo_valor_error = num[fila_error][columnas[fila_error] - 1];

        for (int j = 0; j < filas; j++)
        {
            bool es_error = false;
            for (int k = 0; k < errores; k++)
            {
                if (filas_errores[k] == j && columnas_errores[k] == columna_error)
                {
                    es_error = true;
                    break;
                }
            }

            if (!es_error)
            {
                double ultimo_valor_actual = num[j][columnas[j] - 1];

                if (ultimo_valor_actual == ultimo_valor_error)
                {
                    acumulador += num[j][columna_error];
                    cont_num_filas_terminacion_igual += 1;
                }
            }

            if (cont_num_filas_terminacion_igual > 0)
            {
                promedio = acumulador / cont_num_filas_terminacion_igual;
                for (int k = 0; k < errores; k++)
                {
                    if (columnas_errores[k] == columna_error && ultimo_valor_error == num[filas_errores[k]][columnas[filas_errores[k]] - 1])
                    {
                        num[filas_errores[k]][columna_error] = promedio;
                    }
                }
            }
        }
    }
}

void Convertir_Datos::Restaurar_Datos_Mediana()
{
    // Se recorren las filas con errores y se calcula el promedio de los valores de las columnas con errores
    for (int i = 0; i < errores; i++)
    {
        double promedio = 0;
        int fila_error = filas_errores[i];
        int columna_error = columnas_errores[i];
        double ultimo_valor_error = num[fila_error][columnas[fila_error] - 1]; // Se obtiene el ultimo valor de la fila con error

        double *valores_columna = new double[filas];
        int n = 0; // Se inicializa el contador de valores de la columna con errores

        // Recorremos las filas para obtener los valores de la columna con errores
        for (int j = 0; j < filas; j++)
        {
            bool es_error = false;
            for (int k = 0; k < errores; k++)
            {
                if (filas_errores[k] == j && columnas_errores[k] == columna_error)
                {
                    es_error = true;
                    break;
                }
            }

            if (!es_error)
            { // Solo agregar valores que no son error
                double ultimo_valor_actual = num[j][columnas[j] - 1];

                // Comparamos si el valor de la fila actual coincide con el ultimo valor de la fila con error
                if (ultimo_valor_actual == ultimo_valor_error)
                {
                    valores_columna[n++] = num[j][columna_error]; // Se almacenan los valores de las columnas con errores
                }
            }
        }

        for (int i = 0; i < n; i++)
        {
            int indice = i;
            for (int j = i + 1; j < n; j++)
            {
                if (valores_columna[j] < valores_columna[indice])
                {
                    indice = j;
                }
            }
            if (indice != i)
            {
                double temp = valores_columna[i];
                valores_columna[i] = valores_columna[indice];
                valores_columna[indice] = temp;
            }
        }

        if (n % 2 == 0)
        {
            promedio = (valores_columna[n / 2 - 1] + valores_columna[n / 2]) / 2;
        }
        else
        {
            promedio = valores_columna[n / 2];
        }
        num[fila_error][columna_error] = promedio;
    }
}

// funcion que imprime los datos corregidos
void Convertir_Datos::Imprime(double **num, int filas, int *columnas)
{
    for (int i = 0; i < filas; ++i)
    {
        for (int j = 0; j < columnas[i]; ++j)
        {
            cout << num[i][j] << " ";
        }
        cout << endl;
    }
}

double **Convertir_Datos::getMatriz()
{
    return num;
}

int Convertir_Datos::getFilas()
{
    return filas;
}

int *Convertir_Datos::getColumnas()
{
    return columnas;
}

void Convertir_Datos::Menu_2()
{
    int op;
    string opcion;
    while (op != 3)
    {
        cout << "Selecciona una opcion" << endl;
        cout << "Reparar datos extraviados: " << endl;
        cout << "1. Media de los datos: " << endl;
        cout << "2. Mediana de los datos: " << endl;
        cout << "3. Regresar: " << endl;
        cin >> opcion;
        try
        {
            op = stoi(opcion);
        }
        catch (exception e)
        {
            cout << "Un caracter no es un numero tonoto" << endl;
        }

        switch (op)
        {
        case 1:
            cout << "Calculando la media de los datos..." << endl;
            op_restaurar = 0;
            Restaurar_Datos_Media();
            op = 3;
            break;
        case 2:
            cout << "Calculando la mediana de los datos..." << endl;
            op_restaurar = 1;
            Restaurar_Datos_Mediana();
            op = 3;
            break;

        case 3:
            cout << "Regresando al menu principal..." << endl;
            regresar_menu = 1;
            break;
        default:
            cout << "Opcion no valida" << endl;
            break;
        }
    }
}

int *Convertir_Datos::getFilas_Errores()
{
    return filas_errores;
}

int *Convertir_Datos::getColumnas_Errores()
{
    return columnas_errores;
}

int Convertir_Datos::getErrores()
{
    return errores;
}

int Convertir_Datos::getOp_Restaurar()
{
    return op_restaurar;
}

int Convertir_Datos::getRegresar_Menu()
{
    return regresar_menu;
}
