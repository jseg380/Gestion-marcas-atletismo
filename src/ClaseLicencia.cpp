/***************************************************************************/
/***************************************************************************/
//
// Autor: Juan Manuel Segura Duarte
//
// Fichero: ClaseTiempo.cpp
//
/***************************************************************************/
/***************************************************************************/

#include <iomanip>

#include "ClaseLicencia.h"

using namespace std;

/***********************************************************************/
// Constructor sin argumentos.
// Inicializa la licencia vacía

Licencia :: Licencia (void)
		: la_licencia ("")
{}

/***********************************************************************/
// Constructor directo. 
// Parámetros: trivial.

Licencia :: Licencia (string cad)
		: la_licencia (cad)
{
}

/***********************************************************************/
// Métodos Set y Get

void Licencia :: SetLicencia (string cad)
{
	la_licencia = cad;
}

/***********************************************************************/
// Método ToString

string Licencia :: ToString (void) const
{
	return la_licencia;
}

/***********************************************************************/
// Operadores relacionales
// Devuelve: un valor bool

bool Licencia :: operator == (const Licencia & otra) const
{
	return ((*this) == otra);
}

bool Licencia :: operator != (const Licencia & otra) const
{
	return (!((*this) == otra));
}

/***********************************************************************/
// Sobrecarga de los operadores >> y <<

istream & operator >> (istream & entrada, Licencia & una_licencia)
{
	entrada >> una_licencia.la_licencia;
	
	return entrada;
}

ostream & operator << (ostream & salida, const Licencia & una_licencia)
{
	salida << una_licencia.la_licencia;
	
	return salida;
}



