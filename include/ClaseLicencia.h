/***************************************************************************/
/***************************************************************************/
//
// Autor: Juan Manuel Segura Duarte
//
// Fichero: ClaseLicencia.h
//
/***************************************************************************/
/***************************************************************************/

#ifndef CLASE_LICENCIA
#define CLASE_LICENCIA

using namespace std;

/***************************************************************************/
/***************************************************************************/

/////////////////////////////////////////////////////////////////////////////
// Registro de licencia

class Licencia {

private: 

	string la_licencia;

public: 

	/***********************************************************************/
	// Constructor sin argumentos.
	// Inicializa la licencia vacía

	Licencia (void);

	/***********************************************************************/
	// Constructor directo. 
	// Parámetros: trivial.
	
	Licencia (string cad);

	/***********************************************************************/
	// Método Set
	
	void SetLicencia (string cad);
	
	/***********************************************************************/
	// Método ToString
	
	string ToString (void) const;
	
	/***********************************************************************/
	// Operadores relacionales
	// Devuelve: un valor bool
	
	bool operator == (const Licencia & otra) const;
	
	bool operator != (const Licencia & otra) const;
	
	/***********************************************************************/
	// Sobrecarga de los operadores >> y <<
	
	friend istream & operator >> (istream & entrada, Licencia & una_licencia);
	
	friend ostream & operator << (ostream & salida,
								  const Licencia & una_licencia);
	
};

#endif
