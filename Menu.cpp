#include "Lector_Archivo.h"
#include "Convertir_Datos.h"
#include "Escribir_Archivo.h"
#include "Dinamico_objetos_archivo.h"
#include "Menu.h"
#include "Calculo_de_similitud.h"

#include <iostream>
#include <string>
#include <cstdlib>
#include <cmath>

using namespace std;

void Menu::Mostrar_Menu()
{
    string opcion;
    int op = 0;
    Lector_Archivo arch_base("", NULL, 0, 0, NULL, NULL, NULL, NULL, 0, 0, "");
    Lector_Archivo arch_base2("", NULL, 0, 0, NULL, NULL, NULL, NULL, 0, 0, "");                                                                                                                                 // instancias de la clase Lector_Archivo, son dos ya que una la usaremos como base mientras que la otra nos ayudara como copia para la comparacion de similitud
    Convertir_Datos D1(NULL, 0, NULL, NULL, NULL, 0, 0);                                                                                                                                                         // instancia de la clase Convertir_Datos, ayuda a convertir los datos del archivo y a restaurar los datos erroneos
    Dinamico_objetos_archivo archivos_base(NULL, 0);                                                                                                                                                             // instancia de la clase Dinamico_objetos_archivo, nos ayuda a cargar los archivos y a actualizarlos
    Escribir_Archivo E1;                                                                                                                                                                                         // instancia de la clase Escribir_Archivo, nos ayuda a escribir los archivos corregidos, los errores y la similitud
    Calculo_de_Similitud S1(0, vector<int>(), vector<float>(), vector<vector<float>>(), vector<int>(), vector<vector<float>>(), vector<int>(), vector<vector<float>>(), 0, 0, vector<float>(), vector<float>()); // instancia de la clase Calculo_de_Similitud, nos ayuda a calcular la similitud entre dos archivos

    while (op != 8)
    {
        cout << "Menu" << endl;
        cout << "1. Leer archivo" << endl;
        cout << "2. Ver todos los archivos" << endl;
        cout << "3. Imprimir archivo" << endl;
        cout << "4. Convertir datos (Se guarda en un archivo txt los datos corregidos y en otro los errores)" << endl;
        cout << "5. Ver errores" << endl;
        cout << "6. Imprimir datos" << endl;
        cout << "7. Calculo de similitud" << endl;
        cout << "8. Salir" << endl;
        cout << "Opcion: ";
        cin >> opcion;

        // manejamos por medio de un try-catch la excepcion de que el usuario ingrese un caracter que no sea un numero
        try
        {
            op = stoi(opcion);
        }
        catch (const invalid_argument &e)
        {
            system("cls");
            cout << "Un caracter no es un numero tonoto." << endl;
            continue;
        }

        switch (op)
        {
        case 1:
        {
            // para limpiar la pantalla usamos system("cls") la usaremos repetidamente en el codigo para limpiar la ejecucion
            system("cls");
            string nombre;
            cout << "Digite el nombre del archivo: " << endl;
            cin >> nombre;

            // manejamos la excepcion de que el archivo no se pueda abrir
            try
            {
                arch_base.setnombre_archivo(nombre);
                arch_base.Abrir_Archivo(); // se llama al metodo Abrir_Archivo de la clase Lector_Archivo para verificar si el archivo existe
                // a pesar de que usamos arch_base para leer el archivo y abrirlo tambien lo usamos para cargar los datos en la clase archivos_base
                archivos_base.Cargar_Archivo(nombre);
                cout << "Datos leidos correctamente." << endl;
            }
            catch (const runtime_error &e)
            {
                cout << "Error al abrir el archivo: " << e.what() << endl;
            }
            system("pause");
            system("cls");

            break;
        }

        case 2:
        {
            // verificamos si hay archivos cargados
            if (archivos_base.getN() == 0)
            {
                cout << "primero debes ingresar un archivo." << endl;
                Regresar_Menu();
                break;
            }
            archivos_base.Imprimir_Nombres(); // imprimimos los nombres de los archivos
            Regresar_Menu();                  // aunque es regresar al menu solo consta de un pause y un cls para que aparezca el menu inmediatamente al borrar la pantalla
            break;
        }

        case 3:
        {
            // llama a validar_seleccion_archivo para verificar si hay archivos cargados o si el indice que se ingresa existe
            if (!Validar_Seleccion_Archivo(archivos_base, arch_base))
            {
                Regresar_Menu();

                break;
            }

            arch_base.Imprimir_Lineas(); // tras haber usado y seleccionado el archivo a usar se realiza una escritura sobre el archivo base y se llama al metodo imprimir lineas de la clase Lector_Archivo
            Regresar_Menu();
            break;
        }

        case 4:
        {
            if (!Validar_Seleccion_Archivo(archivos_base, arch_base))
            {
                Regresar_Menu();

                break;
            }
            // despues de validar el archivo y sobre escribirlo en el base se llama a la funcion flotantes de la clase Convertir_Datos donde pasamos como parametros un arrglo dinamico de strings y el numero de filass
            D1.Flotantes(arch_base.getptr(), arch_base.getN());

            if (D1.getRegresar_Menu() == 1)
            {
                Regresar_Menu();
                break;
            } // si es que dentro de la funcion flotantes se regresa al menu principal se llama a la funcion regresar menu

            // se actualizan los datos correspondientes sobre el archivo del cual se calcularon los flotantes
            arch_base.setDatos_Convertidos(true);
            arch_base.setDatos_Flotantes(D1.getMatriz(), D1.getColumnas());
            arch_base.setFila_Error(D1.getFilas_Errores());
            arch_base.setColumna_Error(D1.getColumnas_Errores());
            arch_base.setErrores(D1.getErrores());
            arch_base.setMed(D1.getOp_Restaurar());
            arch_base.setColumas_Flotantes(D1.getColumnas());

            archivos_base.Actualizar_Archivo(arch_base, ind); // se actualiza el archivo en la clase archivos_base, donde se actualiza el que se manipula con los datos convertidos
            // se realiza una escritura en un .txt del archivo corregido y de los errores segun sus posiciones en el archivo original
            if (arch_base.getErrores() != 0)
            {
                cout << "Los datos han sido convertidos." << endl;
                if (!E1.Escribir_Archivo_Corregido(arch_base))
                {
                    cout << "Error al escribir el archivo corregido." << endl;
                }

                if (!E1.Escribir_Archivo_Errores(arch_base))
                {
                    cout << "Error al escribir el archivo de errores." << endl;
                }
            }

            Regresar_Menu();
            break;
        }
        case 5:
        {
            if (!Validar_Seleccion_Archivo(archivos_base, arch_base))
            {
                Regresar_Menu();

                break;
            }
            // se valida si los datos del archivo seleccionado han sido convertidos
            if (!arch_base.getDatos_Convertidos())
            {
                cout << "Primero debes convertir los datos." << endl;
                Regresar_Menu();
                break;
            }

            if (arch_base.getErrores() == 0)
            {
                cout << "No hay errores en el archivo." << endl;
                Regresar_Menu();
                break;
            }

            cout << "Digite la columna que desea ver los errores: " << endl;

            try
            {
                string columna;
                int col;
                cin >> columna;
                col = stoi(columna);
                col = col - 1;
                bool columna_sin_errores = true;

                cout << "Los errores en la columna " << col + 1 << " son: " << endl;

                vector<int> tipos_finales_unicos;
                int cant_tipos_finales = 0;
                vector<int> conteo_por_tipo;
                for (int i = 0; i < arch_base.getErrores(); i++)
                {
                    if (arch_base.getColumna_Error()[i] == col)
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

                        conteo_por_tipo[existencia_tipo_final]++;
                    }
                }

                int total_errores_columnas = 0;
                for (int i = 0; i < cant_tipos_finales; i++)
                {
                    total_errores_columnas += conteo_por_tipo[i];
                }

                cout << "Total de errores en la columna: " << total_errores_columnas << endl;

                for (int i = 0; i < cant_tipos_finales; i++)
                {
                    cout << "Tipo: " << tipos_finales_unicos[i] << " Cantidad: " << conteo_por_tipo[i] << endl;
                }

                cout << "Filas\t\tTipo\t\tValor" << endl;
                for (int i = 0; i < arch_base.getErrores(); i++)
                {
                    if (arch_base.getColumna_Error()[i] == col)
                    {
                        cout << arch_base.getFila_Error()[i] - 2 << "\t\t" << arch_base.getDatos_Flotantes()[arch_base.getFila_Error()[i]][arch_base.getColumnas_Flotantes()[arch_base.getFila_Error()[i]] - 1] << "\t\t" << arch_base.getDatos_Flotantes()[arch_base.getFila_Error()[i]][col] << endl;
                        columna_sin_errores = false;
                    }
                }

                if (columna_sin_errores)
                {
                    cout << "No hay errores en la columna " << columna << endl;
                }
            }
            catch (const invalid_argument &e)
            {
                cout << "Un caracter no es un numero tonoto." << endl;
                Regresar_Menu();
                break;
            }

            Regresar_Menu();
            break;
        }

        case 6:
        {
            if (!Validar_Seleccion_Archivo(archivos_base, arch_base))
            {
                Regresar_Menu();

                break;
            }
            // se valida si los datos del archivo seleccionado han sido convertidos
            if (!arch_base.getDatos_Convertidos())
            {
                cout << "Primero debes convertir los datos." << endl;
                Regresar_Menu();
                break;
            }

            // se imprime los datos convertidos
            cout << "Los datos convertidos son: " << endl;
            D1.Imprime(arch_base.getDatos_Flotantes(), arch_base.getN(), arch_base.getColumnas_Flotantes());
            Regresar_Menu();
            break;
        }

        case 7:
        {
            // se usa una doble validacion de los archivos registrados, una validacion sobreescribe sobre el archivo base y la otra sobre el archivo base2
            if (!Validar_Seleccion_Archivo(archivos_base, arch_base))
            {
                Regresar_Menu();
                break;
            }
            if (!Validar_Seleccion_Archivo(archivos_base, arch_base2))
            {
                Regresar_Menu();

                break;
            }
            // valida si ambos archivos han sido convertidos a flotantes
            if (!arch_base.getDatos_Convertidos() || !arch_base2.getDatos_Convertidos())
            {
                cout << "Primero debes convertir los datos." << endl;
                Regresar_Menu();
                break;
            }

            // valida si ambos archivos tienen la misma cantidad de columnas
            if (!S1.Validez_Columnas(arch_base, arch_base2))
            {
                Regresar_Menu();
                break;
            }
            system("cls");
            // llamamos al metodo menu de la clase Calculo_de_Similitud donde se nos pedira digitar el tipo de similutud que queremos calcular
            S1.Menu(arch_base, arch_base2);

            // si se regresa al menu principal se llama a la funcion regresar menu
            if (S1.getRegresar_Menu() == 1)
            {
                Regresar_Menu();
                break;
            }

            // si la similitud escogida es la absoluta se llama al metodo Escribir_Archivo_Similitud_Absoluto de la clase Escribir_Archivo
            if (S1.getTipo_Similitud() == 1)
            {
                if (!E1.Escribir_Archivo_Similitud_Absoluto(S1.getIndices_Similares(), S1.getSimilitudes(), arch_base, arch_base2))
                {
                    cout << "Error al escribir el archivo de similitud." << endl;
                }
            }
            else // si la similitud escogida es la bayesiana se llama al metodo Escribir_Archivo_Similitud_Bayesiana de la clase Escribir_Archivo
            {
                if (!E1.Escribir_Archivo_Similitud_Bayesiana(S1.getMayores_Probabilidades(), S1.getTipo_Mas_Similar(), arch_base, arch_base2))
                {
                    cout << "Error al escribir el archivo de similitud." << endl;
                }
            }
            Regresar_Menu();
            break;
        }

        case 8:
        {
            cout << "Gracias por usar el programa <3" << endl; // termina la ejecucion del programa
            exit(0);
            break;
        }

        default:
        {
            cout << "Opcion no valida, por favor elige una opcion del menu." << endl;
            break;
        }
        }
    }
}

void Menu::Seleccionar_Archivo(int N, Lector_Archivo &arch_base, Dinamico_objetos_archivo &archivos_base)
{
    bool archivo_seleccionado = false;
    string indice;
    ind = 0;
    while (!archivo_seleccionado)
    {
        try
        {
            cout << "Digite el indice de archivo que desea usar: " << endl; // se valida si el indice es un numero y si el archivo existe
            cin >> indice;
            ind = stoi(indice);
        }
        catch (invalid_argument &e)
        {
            cout << "Indice invalido. UN caracter no es un numero tonoto " << endl;
        }
        if (ind <= N && ind > 0) // se valida si el indice es menor o igual a la cantidad de archivos cargados
        {
            archivo_seleccionado = true;
        }
        else
        {
            cout << "Indice invalido. El archivo en ese indice no existe." << endl;
        }
    }

    for (int i = 0; i < N; i++)
    {
        if ((i == ind - 1))
        {
            arch_base = archivos_base.getArchivos()[i]; // se asigna el archivo seleccionado a la variable arch_base
        }
    }
}

void Menu::Regresar_Menu() // ayuda a la limpieza de la pantalla despues de cada case
{
    system("pause");
    system("cls");
}

bool Menu::Validar_Seleccion_Archivo(Dinamico_objetos_archivo &archivos_base, Lector_Archivo &arch_base)
{

    if (archivos_base.getN() == 0) // se valida si hay archivos cargados, de lo contrario no se puede seleccionar un archivo
    {
        cout << "Primero leer un archivo." << endl;
        return false;
        Regresar_Menu();
    }

    archivos_base.Imprimir_Nombres(); // se imprimen los nombres de los archivos cargados

    // aqui se llama al metodo Seleccionar_Archivo de la clase Menu para seleccionar el archivo que se desea usar
    Seleccionar_Archivo(archivos_base.getN(), arch_base, archivos_base);
    return true;
}
