#ifndef CALCULO_DE_SIMILITUD_H
#define CALCULO_DE_SIMILITUD_H
#include "Lector_Archivo.h"
#include <fstream>
#include <string>
#include <iostream>
#include <cfloat>
#include <cmath>
#include <vector>

class Calculo_de_Similitud {
public:
	Calculo_de_Similitud(int tipo_similitud, vector<int> indices_similares, vector<float> similitudes, vector<vector<float>> promedio_por_columna_tipo, vector<int> tipos_finales_unicos, vector<vector<float>> suma_por_tipo, vector<int> conteo_por_tipo, vector<vector<float>> desviacion_por_tipo_columna, int cant_tipos_finales, int regresar_menu, vector<float> mayores_probabilidades, vector<float> tipo_mas_similar);
	~Calculo_de_Similitud();
	void Menu(Lector_Archivo &arch_base, Lector_Archivo &arch_base2);
	int getTipo_Similitud();
	void setTipo_Similitud(int tipo_similitud);
	void Similitud_Absoluta(Lector_Archivo &arch_base, Lector_Archivo &arch_base2);
	void Similitud_Bayesiana(Lector_Archivo &arch_base, Lector_Archivo &arch_base2);
	vector<int> getIndices_Similares();
	vector<float> getSimilitudes();
	bool Validez_Columnas(Lector_Archivo &arch_base, Lector_Archivo &arch_base2);
	void Calcular_Promedio(Lector_Archivo &arch_base2);
	void Calcular_Desviacion(Lector_Archivo &arch_base2);
	int getRegresar_Menu();
	vector <float> getMayores_Probabilidades();
	vector <float> getTipo_Mas_Similar();

private:
	int tipo_similitud;//guarda el tipo de similitud que se va a calcular
	vector<int> indices_similares;//guarda los indices de las filas mas similares
    vector<float> similitudes;//guarda las similitudes de las filas mas similares
	vector<float> mayores_probabilidades;//guarda las mayores probabilidades de las filas mas similares
	vector<float> tipo_mas_similar;//guarda los tipos mas similares de las filas mas similares

	vector<vector<float>> promedio_por_columna_tipo;//guarda los promedios de las columnas por tipo
	vector<int> tipos_finales_unicos;//guarda los tipos finales sin repetir
    vector<vector<float>> suma_por_tipo;//guarda la suma de los valores por tipo
    vector<int> conteo_por_tipo;//guarda el conteo de los valores por tipo
    vector<vector<float>> desviacion_por_tipo_columna;//guarda la desviacion por tipo y columna
	int regresar_menu;//guarda la opcion de regresar al menu
    int cant_tipos_finales = 0;//guarda la cantidad de tipos finales diferentes

};

#endif

