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

#include "ClaseFecha.h"
#include "ClaseTiempo.h"

using namespace std;

/***************************************************************************/
// Constructor sin argumentos. 
// Inicializa el objeto con todos sus campos a 0.

Tiempo :: Tiempo (void)
{
	horas = minutos = segundos = milesimas = 0 ;
}

/***************************************************************************/
// Constructor directo. 
// Parámetros: trivial. 
// PRE: 0 <= la_hora <= 24 
// PRE: 0 <= los_minutos <= 60
// PRE: 0 <= los_segundos <= 60
// PRE: 0 <= las_milesimas <= 1000

Tiempo :: Tiempo (int la_hora, int los_minutos, 
				  int los_segundos, int las_milesimas) 
		          : horas (la_hora), minutos (los_minutos), 
		            segundos (los_segundos), milesimas (las_milesimas) 
{} 

/***************************************************************************/
// Constructor desde un string.
// Parámetros: cad, string con la fecha. 
// PRE: cad contiene un tiempo CORRECTO en formato hh:mm:ss:mmm 
// PRE: cad.length() == 12	

Tiempo :: Tiempo (string cad)
{
	PonerTiempo (cad);
}

/***********************************************************************/
// Métodos Get

int Tiempo :: GetHoras (void) const
{
	return horas; 
}

int Tiempo :: GetMinutos (void) const
{
	return minutos; 
}

int Tiempo :: GetSegundos (void) const
{
	return segundos; 
}

int Tiempo :: GetMilesimas (void) const
{
	return milesimas; 
}

long Tiempo :: GetTiempoMilisegundos (void) const
{
	return (horas*MILISEGS_HORA + minutos*MILISEGS_MIN + 
			segundos*MILISEGS_SEG + milesimas);	
}

/***************************************************************************/
// Serializa un dato Tiempo.

string Tiempo :: ToString (CategoriaTiempo tipo_tiempo) const
{
	string cad; 
	
	switch (tipo_tiempo) {
		
		case (CategoriaTiempo::horas) : {
			cad = cad + ::ToString(GetHoras(), 2, '0') + ":"; 
		}
		case (CategoriaTiempo::minutos) : {
			cad = cad + ::ToString(GetMinutos(), 2, '0') + ":"; 
		}		
		default: {
			cad = cad + ::ToString(GetSegundos(), 2, '0') + ":" + 
		  		        ::ToString(GetMilesimas(), 3, '0');
			break;
		} 
	}

	return cad; 
}

/***********************************************************************/
// Operadores relacionales
// Devuelve: un valor bool

/***************************************************************************/
// Operador ==

bool Tiempo :: operator == (const Tiempo & otro) const
{
	long int milisegs_1, milisegs_2;
	
	milisegs_1 = GetTiempoMilisegundos();
	milisegs_2 = otro.GetTiempoMilisegundos();
	
	return (milisegs_1 == milisegs_2);
}

/***************************************************************************/
// Operador !=

bool Tiempo :: operator != (const Tiempo & otro) const
{
	return (!((*this) == otro));
}

/***************************************************************************/
// Operador >

bool Tiempo :: operator  > (const Tiempo & otro) const
{
	
	long int milisegs_1, milisegs_2;

	milisegs_1 = GetTiempoMilisegundos(); 
	milisegs_2 = otro.GetTiempoMilisegundos(); 
				 
	return (milisegs_1 > milisegs_2);
	
}

/***************************************************************************/
// Operador <=

bool Tiempo :: operator <= (const Tiempo & otro) const
{
	return (!((*this) > otro));
}

/***************************************************************************/
// Operador <

bool Tiempo :: operator  < (const Tiempo & otro) const
{
	return (!((*this) > otro) && !((*this) == otro));
}

/***************************************************************************/
// Operador >=

bool Tiempo :: operator >= (const Tiempo & otro) const
{
	return (((*this) > otro) || ((*this) == otro));
}

/***********************************************************************/
// Sobrecarga de los operadores >> y <<

istream & operator >> (istream & entrada, Tiempo & el_tiempo)
{
	string cadena;
	
	entrada >> cadena;
	
	el_tiempo.PonerTiempo (cadena);
	
	return entrada;
}

ostream & operator << (ostream & salida, const Tiempo & el_tiempo)
{
	salida << el_tiempo.ToString (CategoriaTiempo :: horas);
	
	return salida;
}


///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
//
//	MÉTODOS PRIVADOS DE LA CLASE Tiempo
//
///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////

/***********************************************************************/
// Establece el tiempo desde un string.
// Parámetros: cad, string con el tiempo. 
// PRE: cad contiene un tiempo CORRECTO en formato hh:mm:ss:mmm 
// PRE: cad.length() == 12	

void Tiempo :: PonerTiempo (const string & cad)
{
	horas     = stoi(cad.substr(0,2));
	minutos   = stoi(cad.substr(3,2));
	segundos  = stoi(cad.substr(6,2));
	milesimas = stoi(cad.substr(9,3));
}


