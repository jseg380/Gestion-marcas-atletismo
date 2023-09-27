/***************************************************************************/
/***************************************************************************/
//
// Autor: Juan Manuel Segura Duarte
//
// Fichero: ClaseRegistroDeMarca.cpp
//
/***************************************************************************/
/***************************************************************************/

#include <iomanip>

#include "ClaseRegistroDeMarca.h"

using namespace std;

/***********************************************************************/
// Constructor sin argumentos.
// Necesario para crear arrays o matrices.

RegistroDeMarca :: RegistroDeMarca (void) {};

/***********************************************************************/
// Constructor con argumentos. 
// Parámetros: triviales. 

RegistroDeMarca :: RegistroDeMarca (Fecha la_fecha_marca, 
	                                string la_licencia, 
	             				    Tiempo el_tiempo_marca) 
				: fecha_marca (la_fecha_marca), 
	              licencia (la_licencia), 
	       		  tiempo_marca (el_tiempo_marca)
{}

/***********************************************************************/
// Constructor de copia. 
// Parámetros: trivial.

RegistroDeMarca :: RegistroDeMarca (const RegistroDeMarca & otro)
{
	fecha_marca = otro.fecha_marca;
	licencia = otro.licencia;
	tiempo_marca = otro.tiempo_marca;
}

/***********************************************************************/
// Métodos Get

Fecha  RegistroDeMarca :: GetFecha (void) const
{
	return fecha_marca;
}

string RegistroDeMarca :: GetLicencia (void) const
{
	return licencia.ToString();
}

Tiempo RegistroDeMarca :: GetTiempo (void) const
{
	return tiempo_marca;
}

/***************************************************************************/
// Serializa un dato RegistroDeMarca.

string RegistroDeMarca :: ToString (void) const
{
	string cad = ::ToString(GetLicencia(),12) + "   " + 
	               GetFecha().ToString() + "  " + 
	               GetTiempo().ToString(CategoriaTiempo::minutos);
	return cad;
}

/***********************************************************************/
// Operadores relacionales
// Devuelve: un valor bool

/***************************************************************************/
// Operador ==

// Dejar activo solo un criterio. Tiene que coincidir con >.

/***********************************************************************/
// Compara dos datos RegistroDeMarca en función del TIEMPO.

bool RegistroDeMarca :: operator == (const RegistroDeMarca & otro) const
{
	return (tiempo_marca == otro.GetTiempo());
}

/***********************************************************************/
// Compara dos datos RegistroDeMarca en función de la FECHA.

/*
bool RegistroDeMarca :: operator == (const RegistroDeMarca & otro) const
{
	return (fecha_marca == otro.GetFecha());
}
*/

/***************************************************************************/
// Operador !=

bool RegistroDeMarca :: operator != (const RegistroDeMarca & otro) const
{
	return (!((*this) == otro));
}

/***************************************************************************/
// Operador >

// Dejar activo solo un criterio. Tiene que coincidir con >.

/***********************************************************************/
// Compara dos datos RegistroDeMarca en función del TIEMPO.

bool RegistroDeMarca :: operator  > (const RegistroDeMarca & otro) const
{
	return (tiempo_marca > otro.GetTiempo());
}

/***********************************************************************/
// Compara dos datos RegistroDeMarca en función de la FECHA.

/*
bool RegistroDeMarca :: operator  > (const RegistroDeMarca & otro) const
{
	return (fecha_marca > otro.GetFecha());
}
*/

/***************************************************************************/
// Operador <=

bool RegistroDeMarca :: operator <= (const RegistroDeMarca & otro) const
{
	return (!((*this) > otro));
}

/***************************************************************************/
// Operador <

bool RegistroDeMarca :: operator  < (const RegistroDeMarca & otro) const
{
	return (!((*this) > otro) && !((*this) == otro));
}

/***************************************************************************/
// Operador >=

bool RegistroDeMarca :: operator >= (const RegistroDeMarca & otro) const
{
	return (((*this) > otro) || ((*this) == otro));
}

/***********************************************************************/
// Sobrecarga de los operadores >> y <<

istream & operator >> (istream & entrada, RegistroDeMarca & registro)
{
	entrada >> registro.fecha_marca;
	entrada >> registro.licencia;
	entrada >> registro.tiempo_marca;
	
	return (entrada);
}

ostream & operator << (ostream & salida, const RegistroDeMarca & registro)
{
	salida << setfill(' ') << setw(14) << registro.fecha_marca;
	salida << setfill(' ') << setw(11) << registro.licencia;
	salida << setfill(' ') << setw(16) << registro.tiempo_marca;
	
	return salida;
}


