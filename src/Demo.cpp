/***************************************************************************/
/***************************************************************************/
//
// Demostración
//
/***************************************************************************/
/***************************************************************************/

#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>

#include "Utils.h"
#include "MatrizMarcas.h"

using namespace std;

int main (int argc, char ** argv)
{
    cout.setf(ios::fixed);		// Notación de punto fijo para los reales
	cout.setf(ios::showpoint);	// Mostrar siempre decimales

	//.......................................................................
	// Procesar línea de órdenes

	if (argc != 3) {
		cerr << endl;
		cerr << "Error: Número incorrecto de argumentos." << endl; 
		cerr << "Uso: " << argv[0] << " <fichero_marcas> <fichero_marcas>" 
			 << endl;
		cerr << endl;
		exit (1);
	} 

	if (!ExisteFichero(argv[1])) {
		cerr << endl;
		cerr << "Error: El fichero "<< argv[1] << " no existe o "; 
		cerr << "los permisos no son correctos." << endl;
		cerr << endl;
		exit (2);	
	}

	if (!ExisteFichero(argv[2])) {
		cerr << endl;
		cerr << "Error: El fichero "<< argv[2] << " no existe o "; 
		cerr << "los permisos no son correctos." << endl;
		cerr << endl;
		exit (3);
	}
	
	MatrizMarcas ranking;
	MatrizMarcas marcas;
	ifstream fi (argv[1], ios::binary);
	string cadena;
	bool txt;

	getline (fi, cadena);

	txt = (cadena == "MARCAS");

	marcas.LeerMatrizMarcas (argv[1], txt);

	fi.close();

	ranking += marcas;

	fi.open (argv[2], ios::binary);

	getline (fi, cadena);

	txt = (cadena == "MARCAS");

	marcas.LeerMatrizMarcas (argv[2], txt);

	fi.close();

	ranking += marcas;
	
	// MOSTRAR RESULTADO
	
	cout << endl;
	
	if (ranking.NumPruebas() == 0)
		cout << "Matriz vacia." << endl;
	else {
		
		// Ordenar y mostar el resultado
		
		ranking.Ordena();
		
		cout << ranking.ToString ("Ranking - marcas ordenadas") << endl;
		
		if (ranking[1] < ranking[2])
			cout << ranking[1].Etiqueta() << " < " << ranking[2].Etiqueta() << endl;
		else
			cout << ranking[1].Etiqueta() << " >= " << ranking[2].Etiqueta() << endl;

		ranking.OrdenaPruebas();
		
		cout << ranking.ToString ("Ranking - pruebas ordenadas") << endl;
	}
	
	cout << endl;
	
	return 0;
}


