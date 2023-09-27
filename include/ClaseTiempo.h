/***************************************************************************/
/***************************************************************************/
//
// Autor: Juan Manuel Segura Duarte
//
// Fichero: ClaseTiempo.h
//
/***************************************************************************/
/***************************************************************************/

#ifndef CLASE_TIEMPO
#define CLASE_TIEMPO

using namespace std;


// Tipo para seleccionar el tipo de presentación de los datos "Tiempo" 
// Si "segundos": nos interesa segundos:milesimas
// Si "minutos": nos interesa minutos:segundos:milesimas
// Si "horas": nos interesa horas:minutos:segundos:milesimas
enum class CategoriaTiempo {segundos, minutos, horas};


const int SEGS_MIN = 60; 
const int MINS_HORA = 60; 
const int MILISEGS_SEG = 1000; 
const int MILISEGS_MIN = MILISEGS_SEG*SEGS_MIN;
const int MILISEGS_HORA = MILISEGS_MIN*MINS_HORA;

/////////////////////////////////////////////////////////////////////////////
// Registro de tiempo

class Tiempo {

private: 

	int horas;		// 0 <= horas <= 24 
	int minutos; 	// 0 <= minutos < 60
	int segundos; 	// 0 <= segundos < 60	
	int milesimas; 	// 0 <= milesimas < 1000	

public: 

	/***********************************************************************/
	// Constructor sin argumentos.
	// Inicializa el objeto con todos sus campos a 0.

	Tiempo (void); 

	/***********************************************************************/
	// Constructor directo. 
	// Parámetros: trivial. 
	// PRE: 0 <= la_hora <= 24 
	// PRE: 0 <= los_minutos <= 60
	// PRE: 0 <= los_segundos <= 60
	// PRE: 0 <= las_milesimas <= 1000

	Tiempo (int la_hora, int los_minutos, int los_segundos, int las_milesimas);

	/***********************************************************************/
	// Constructor desde un string.
	// Parámetros: cad, string con el tiempo. 
	// PRE: cad contiene un tiempo CORRECTO en formato hh:mm:ss:mmm 
	// PRE: cad.length() == 12	

	Tiempo (string cad);

	/***********************************************************************/
	// Métodos Get

	int GetHoras     (void) const;
	int GetMinutos   (void) const;
	int GetSegundos  (void) const;
	int GetMilesimas (void) const;

	long GetTiempoMilisegundos (void) const;

	/***********************************************************************/
	// Serializa un dato "Tiempo"

	string  ToString (CategoriaTiempo tipo_tiempo) const;
	
	/***********************************************************************/
	// Operadores relacionales
	// Devuelve: un valor bool
	
	bool operator == (const Tiempo & otro) const;
	
	bool operator != (const Tiempo & otro) const;
	
	bool operator  > (const Tiempo & otro) const;
	
	bool operator <= (const Tiempo & otro) const;
	
	bool operator  < (const Tiempo & otro) const;
	
	bool operator >= (const Tiempo & otro) const;
	
	/***********************************************************************/
	// Sobrecarga de los operadores >> y <<
	
	friend istream & operator >> (istream & entrada, Tiempo & el_tiempo);
	
	friend ostream & operator << (ostream & salida, const Tiempo & el_tiempo);
	
	
	
	private:
	
	/***********************************************************************/
	// Establece el tiempo desde un string.
	// Parámetros: cad, string con el tiempo. 
	// PRE: cad contiene un tiempo CORRECTO en formato hh:mm:ss:mmm 
	// PRE: cad.length() == 12	
	
	void PonerTiempo (const string & cad);
	
};

#endif
