#ifndef ESCRIBIR_ARCHIVO_H
#define ESCRIBIR_ARCHIVO_H

#include "Lector_Archivo.h"
#include "Calculo_de_Similitud.h"

#include <string>
#include <vector>

using namespace std;

class Escribir_Archivo
{

public:
	bool Escribir_Archivo_Corregido(Lector_Archivo &arch_base);
	bool Escribir_Archivo_Errores(Lector_Archivo &arch_base);
	bool Escribir_Archivo_Similitud_Absoluto(vector<int> indices_similares, vector<float> similitudes, Lector_Archivo &arch_base, Lector_Archivo &arch_base2);
	bool Escribir_Archivo_Similitud_Bayesiana(vector<float> mayores_probabilidades, vector<float> tipo_mas_similar, Lector_Archivo &arch_base, Lector_Archivo &arch_base2);
	string Cambiar_Extension(string nombre_archivo);
};

#endif
