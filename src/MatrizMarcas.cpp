/***************************************************************************/
/***************************************************************************/
//
// Autor: Juan Manuel Segura Duarte
//
// Definición de las funciones declaradas en el fichero MatrizMarcas.h
//
// Fichero: MatrizMarcas.cpp
//
/***************************************************************************/
/***************************************************************************/

#include "MatrizMarcas.h"

#include <iostream>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <cstring>

////////////////////////////////////////////////////////////
// Constructores y destructor

/***********************************************************************/
// Constructor sin argumentos.
// Por defecto matriz vacía.

MatrizMarcas :: MatrizMarcas (void)
{
	num_pruebas = 0;
	pruebas = nullptr;
}

/***********************************************************************/
// Constructor con un argumento.
// Parámetros: capacidad, número de filas que tendrá la matriz
// PRE: 0 < capacidad

MatrizMarcas :: MatrizMarcas (int capacidad)
{
	if (capacidad > 0) // Solo si se cumplen las precondiciones se actua
		ReservaMemoria (capacidad);
	
}

/***********************************************************************/
// Construye un objeto de MatrizMarcas a partir de un fichero de marcas.
// Parámetros: nombre, nombre del fichero de marcas

MatrizMarcas :: MatrizMarcas (const string & nombre)
{
	pruebas = nullptr;
	
	ifstream fi (nombre, ios::binary);
	
	// Comprobar la cadena mágica
	
	string cadena;
	
	getline (fi, cadena);
	
	bool txt = (cadena == "MARCAS");
	
	LeerMatrizMarcas (nombre, txt);
}

/***********************************************************************/
// Constructor de copia.

MatrizMarcas :: MatrizMarcas (const MatrizMarcas & otra)
{
	ReservaMemoria (otra.num_pruebas);
	CopiaDatos (otra);
}

/***********************************************************************/
// Destructor.

MatrizMarcas :: ~MatrizMarcas (void)
{
	LiberaMemoria ();
}



////////////////////////////////////////////////////////////
// Método Get

int MatrizMarcas :: NumPruebas (void)
{
	return num_pruebas;
}



/***********************************************************************/
// Ajusta una matriz MatrizMarcas para que ocupe el mínimo 
// número de casillas posible.

void MatrizMarcas :: Ajusta (void)
{
	for (int i = 0 ; i < num_pruebas ; i++)
		pruebas[i].Ajusta ();
}

/***********************************************************************/
// Ordena una matriz MatrizMarcas.

void MatrizMarcas :: Ordena (void)
{
	for (int i = 0 ; i < num_pruebas ; i++)
		pruebas[i].Ordena ();
}

/***********************************************************************/
// Convierte a string información útil sobre una matriz MatrizMarcas.

string MatrizMarcas :: ToStringInfo (void)
{
	stringstream cad_stream;
	
	int lineas = 0;
	
	cad_stream << endl << "Número de pruebas = " << num_pruebas << endl;
	
	cad_stream << endl << setw(7) << "Pruebas" << setw(10) << "Marcas" << endl;
	
	for (int i = 0 ; i < num_pruebas ; i++){
		cad_stream << setw(7) << pruebas[i].Etiqueta() << setw(10) 
				   << pruebas[i].NumMarcas() << endl;
		
		lineas += pruebas[i].NumMarcas();
	}
	
	cad_stream << endl << setw(13) << "Total marcas =" << setw(3) << lineas 
			   << endl;
	
	return cad_stream.str();
}

/***********************************************************************/
// Convierte a string una matriz MatrizMarcas.
// Parámetros:  mensaje, mensaje que mostrará como título

string MatrizMarcas :: ToString (const string mensaje)
{
	string cad;
	
	cad += "\n..................................\n";
	
	cad += mensaje + "\n\n";
	
	for (int i = 0 ; i < num_pruebas ; i++){
		cad += pruebas[i].Etiqueta() + "\n";
		
		cad += pruebas[i].ToString ();
	}
	
	cad += "..................................\n";
	
	return cad;
}

/***********************************************************************/
// Guarda un dato MatrizMarcas en un fichero llamado nombre . El
// fichero será un fichero de marcas.
// Parámetros: nombre, nombre del fichero en el que se guarda la matriz
//			   txt, variable booleana que determina si el fichero es
//					de texto o binario

void MatrizMarcas :: EscribirMatrizMarcas (const string & nombre, 
										   bool txt) const
{
	if (txt)
		EscribirMatrizMarcasTxt (nombre);
	else
		EscribirMatrizMarcasBin (nombre);
}

/***********************************************************************/
// Lee un dato MatrizMarcas de un fichero llamado nombre . El 
// fichero será un fichero de marcas.
// Parámetros: nombre, nombre del fichero de marcas
//			   txt, variable booleana que determina si el fichero es
//					de texto o binario

void MatrizMarcas :: LeerMatrizMarcas (const string & nombre, bool txt)
{
	if (txt)
		LeerMatrizMarcasTxt (nombre);
	else
		LeerMatrizMarcasBin (nombre);
}

/***********************************************************************/
// Operador de asignación (Copia profunda)
// Devuelve: un objeto de la misma clase

MatrizMarcas & MatrizMarcas :: operator = (const MatrizMarcas & otra)
{
	if (this != &otra) { // Evitar autoasignación
		
		// Se libera la memoria que estaban ocupando los datos actuales
		
		LiberaMemoria ();
		
		// Se reserva memoria para alojar los nuevos datos
		
		ReservaMemoria (otra.num_pruebas);
		
		// Se copian los datos desde otra al objeto implícito
		
		CopiaDatos (otra);
	}
	
	return (*this);
}

/***********************************************************************/
// Sobrecarga del operador ()
// Accede a un vector de la matriz dado su índice.
// Parámetros: indice, posición del vector al que se accede
// Devuelve: el vector en la posición (indice)
//
// PRE: 1 <= indice <= num_marcas

VectorMarcas & MatrizMarcas :: operator () (int indice)
{
	return la_fila (indice);
}

VectorMarcas & MatrizMarcas :: operator () (int indice) const
{
	return la_fila (indice);
}

/***********************************************************************/
// Sobrecarga del operador ()
// Accede a un elemento de la matriz dado sus índices.
// Parámetros: fila, fila en la que está el elemento
//			   columna, columna en la que está el elemento
// Devuelve: el elemento en la posición (fila, columna)
//
// PRE: 1 <= fila <= num_marcas
// PRE: 1 <= columna <= la_fila (fila).num_marcas

RegistroDeMarca & MatrizMarcas :: operator () (int fila, int columna)
{
	return el_elemento (fila, columna);
}

RegistroDeMarca & MatrizMarcas :: operator () (int fila, int columna) const
{
	return el_elemento (fila, columna);
}

/***********************************************************************/
// Sobrecarga del operador []
// Accede a un elemento del vector dado su índice.
// Parámetros: indice, posición del elemento al que se accede
// Devuelve: el elemento en la posición (indice)
//
// PRE: 1 <= indice <= num_marcas

VectorMarcas & MatrizMarcas :: operator [] (int indice)
{
	return la_fila (indice);
}

VectorMarcas & MatrizMarcas :: operator [] (int indice) const
{
	return la_fila (indice);
}

/***********************************************************************/
// Operadores binarios + y -

// Operador +

// IMPORTANTE:		CONCATENAR
// Versión 1: [MatrizMarcas] + [MatrizMarcas]
/*
MatrizMarcas operator + (const MatrizMarcas & matriz1,
						 const MatrizMarcas & matriz2)
{
	// Se crea una matriz con capacidad para almacenar los
	// contenidos de las dos matrices
	
	MatrizMarcas suma (matriz1.num_pruebas + matriz2.num_pruebas);
	
	// Se copian los datos de matriz1 en suma
	
	suma.CopiaDatos (matriz1);
	
	// Se copian los datos de matriz2 en suma
	
	for (int i = 1 ; i <= matriz2.num_pruebas ; i++)
		suma[i + matriz1.num_pruebas] = matriz2[i];
	
	// Se establecen los campos de suma
	
	suma.num_pruebas = matriz1.num_pruebas + matriz2.num_pruebas;
	
	return suma;
}
*/

// Versión 1: [MatrizMarcas] + [MatrizMarcas]

MatrizMarcas operator + (const MatrizMarcas & matriz1,
						 const MatrizMarcas & matriz2)
{
	// Se crea una matriz con capacidad para almacenar los
	// contenidos de las dos matrices
	
	MatrizMarcas suma (matriz1.num_pruebas + matriz2.num_pruebas);
	
	if (matriz1.num_pruebas == 0)
		suma = matriz2;
	else if (matriz2.num_pruebas == 0)
		suma = matriz1;
	else {
		
		// Se copian los datos de matriz1 en suma

		suma.CopiaDatos (matriz1);

		// Se copian los datos de matriz2 en suma

		for (int i = 1 ; i <= matriz2.num_pruebas ; i++)
			suma[i + matriz1.num_pruebas] = matriz2[i];

		// Se establecen los campos de suma

		suma.num_pruebas = matriz1.num_pruebas + matriz2.num_pruebas;
		
		suma.AjustaPruebas();
	}
	
	return suma;
}

// Versión 2: [MatrizMarcas] + [VectorMarcas]

MatrizMarcas operator + (const MatrizMarcas & matriz,
						 const VectorMarcas & vector)
{
	// Se crea una matriz que solo contiene el vector
	
	MatrizMarcas matriz_vector (1);
	
	matriz_vector[1] = vector;
	
	// Se suman dos matrices
	
	return matriz + matriz_vector;
}

// Versión 3: [VectorMarcas] + [MatrizMarcas]

MatrizMarcas operator + (const VectorMarcas & vector,
						 const MatrizMarcas & matriz)
{
	// Se crea una matriz que solo contiene el vector
	
	MatrizMarcas matriz_vector (1);
	
	matriz_vector[1] = vector;
	
	// Se suman dos matrices
	
	return matriz_vector + matriz;
}

// Operador -

// Versión única: [MatrizMarcas] - [string]

MatrizMarcas operator - (const MatrizMarcas & matriz,
						 const string una_licencia)
{
	// Se crea una copia de matriz
	
	MatrizMarcas copia_matriz (matriz);
	
	// Elimina todas los registros con una_licencia fila por fila
	
	for (int i = 1 ; i < copia_matriz.num_pruebas ; i++)
		copia_matriz.pruebas[i] -= una_licencia;
	
	return copia_matriz;
}

/***********************************************************************/
// Sobrecarga de los operadores combinados += y -=

// Operador +=

// Versión 1: [MatrizMarcas] += [MatrizMarcas]

MatrizMarcas & MatrizMarcas :: operator += (const MatrizMarcas & matriz)
{
	(*this) = (*this) + matriz;
	
	return (*this);
}

// Versión 2: [MatrizMarcas] += [VectorMarcas]

MatrizMarcas & MatrizMarcas :: operator += (const VectorMarcas & vector)
{
	(*this) = (*this) + vector;
	
	return (*this);
}

// Operador -=

//Versión única: [MatrizMarcas] -= [string]

MatrizMarcas & MatrizMarcas :: operator -= (const string & una_licencia)
{
	(*this) = (*this) - una_licencia;
	
	return (*this);
}

/***********************************************************************/
// Sobrecarga de los operadores >> y <<

istream & operator >> (istream & entrada, MatrizMarcas & matriz)
{
	matriz.LiberaMemoria();
	
	entrada >> matriz.num_pruebas;
	
	matriz.ReservaMemoria (matriz.num_pruebas);
	
	string cadena;
	string fecha_str;
	string licencia_str;
	string tiempo_str;
	
	for (int i = 0 ; i < matriz.num_pruebas ; i++) {
		entrada >> cadena;
		
		matriz.pruebas[i].SetEtiqueta (cadena);
	}
	
	// Lectura adelantada
	
	entrada >> cadena;
	
	while (!entrada.eof()) {
		
		entrada >> fecha_str;
		entrada >> licencia_str;
		entrada >> tiempo_str;
		
		// Se convierten los datos de strings a sus correspondientes clases
		
		Fecha fecha_registro (fecha_str);
		Tiempo tiempo_registro (tiempo_str);
		
		// Se crea un registro con los datos introducidos
		
		RegistroDeMarca registro (fecha_registro, licencia_str, 
								  tiempo_registro);
		
		// Se busca la fila que conteien su categoría y se introduce en esta
		
		bool prueba_encontrada = false;
		
		for (int i = 0 ; i < matriz.num_pruebas && !prueba_encontrada ; i++)
			if (cadena == matriz.pruebas[i].Etiqueta()) {
				matriz.pruebas[i] += registro;
				prueba_encontrada = true;
			}
		
		// Se vuelve a leer
		
		entrada >> cadena;
	}
	
	matriz.Ajusta();
	
	return entrada;
}

ostream & operator << (ostream & salida, const MatrizMarcas & matriz)
{
	if (matriz.num_pruebas > 0) {
		
		salida << matriz.num_pruebas;
		
		for (int i = 0 ; i < matriz.num_pruebas ; i++)
			salida << setfill(' ') << setw(10) << matriz.pruebas[i].Etiqueta();
		
		salida << "\n\n";
		
		for (int i = 0 ; i < matriz.num_pruebas ; i++)
			for (int j = 1 ; j <= matriz.pruebas[i].NumMarcas() ; j++)
				salida << setw(8) << matriz.pruebas[i].Etiqueta() << "  " 
					   << matriz.pruebas[i][j] << "\n";
	}
	
	return salida;
}






///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
//
//	MÉTODOS PRIVADOS DE LA CLASE MatrizMarcas
//
///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////


/***********************************************************************/
// Reserva memoria para los datos de una matriz de marcas con "tamanio"
// número de filas.
// Parámetros: tamanio, número de filas de la matriz.
// PRE: 0 < tamanio

void MatrizMarcas :: ReservaMemoria (int tamanio)
{
	// Por defecto matriz vacía
	
	num_pruebas = 0;
	pruebas = nullptr;
	
	if (tamanio > 0) { // Solo si se cumplen las precondiciones se actua
		pruebas = new VectorMarcas [tamanio];
		
		num_pruebas = tamanio;
	}
}

/***********************************************************************/
// Libera la memoria ocupada por una matriz de marcas.
// POST: La matriz queda vacía (todos sus campos a cero).

void MatrizMarcas :: LiberaMemoria (void)
{
	if (pruebas) // Solo se libera memoria si el puntero apunta a "algo"
		delete [] pruebas;
	
	// Establece los campos a 0
	
	num_pruebas = 0;
	pruebas = nullptr;
}

/***********************************************************************/
// Copia datos desde otro objeto de la misma clase. (Copia profunda).
// PRE: Se ha reservado memoria para los datos.

void MatrizMarcas :: CopiaDatos (const MatrizMarcas & otra)
{
	// Copia profunda de los datos utilizando el operador de asignación
	
	for (int i = 0 ; i < otra.num_pruebas ; i++)
		pruebas[i] = otra.pruebas[i];
	
	// Se establecen el número de pruebas
	
	num_pruebas = otra.num_pruebas;
}

/***********************************************************************/
// Elimina las pruebas repetidas fusionándolas en un único VectorMarcas.

void MatrizMarcas :: AjustaPruebas (void)
{
	if (num_pruebas > 0) {	// Solo si la matriz no está vacía
		
		int contador = 0;
		
		while (contador < num_pruebas - 1) {
			
			int a_comprobar = contador + 1;
			
			while (a_comprobar < num_pruebas) {
			
				if (pruebas[contador].Etiqueta() == 
					pruebas[a_comprobar].Etiqueta())
					UnePruebas (contador, a_comprobar);
				else
					a_comprobar++;
			}
			
			contador++;
		}
	}
}

/***********************************************************************/
// Une dos pruebas dados sus índices.
// Parámetros: intacta, índice de la prueba que contendrá al resultado
//			   a_eliminar, índice de la prueba a unir

void MatrizMarcas :: UnePruebas (const int intacta, const int a_eliminar)
{
	// Vector que contendrá las pruebas de los otros vectores
	
	VectorMarcas prueba_nueva;
	
	prueba_nueva = pruebas[intacta] + pruebas[a_eliminar];
	
	// Eliminar los vectores antiguos
	
	pruebas[intacta].Elimina();
	pruebas[a_eliminar].Elimina();
	
	// Crea un nuevo puntero a VectorMarcas
	
	VectorMarcas * nuevo = new VectorMarcas[num_pruebas - 1];
	
	// Copia las direcciones de pruebas a nuevo
	
	int contador = 0;
	for (int i = 0 ; i < num_pruebas ; i++)
		if (i != a_eliminar) {
			nuevo[contador] = pruebas[i];
			contador++;
		}
	
	nuevo[intacta] = prueba_nueva;
	
	delete [] pruebas;
	
	num_pruebas -= 1;
	
	pruebas = nuevo;
}

/***********************************************************************/
// Ordena las pruebas de una matriz de marcas.

void MatrizMarcas :: OrdenaPruebas (void)
{
	for (int izda = 1 ; izda < num_pruebas ; izda++) {

		VectorMarcas a_insertar = pruebas[izda];

		// Se busca la posición en la zona ordenada

		int i = izda;
		while ((i > 0) && (a_insertar < pruebas[i - 1])) {

			pruebas[i] = pruebas[i - 1]; // Desplazar a la derecha los valores
										 // mayores que "a_insertar"
			i--;
		}

		pruebas[i] = a_insertar;	// Copiar a_insertar en el hueco
	}
}

/***********************************************************************/
// Método PRIVADO compartido por: 
//      VectorMarcas & operator () (int indice);
//		VectorMarcas & operator () (int indice) const;
//      VectorMarcas & operator [] (int indice);
//		VectorMarcas & operator [] (int indice) const;
// para evitar la duplicidad de código.
//
// Devuelve una referencia a una fila de la matriz dada su posición.
// PRE: 1 <= indice < num_pruebas

VectorMarcas & MatrizMarcas :: la_fila (int indice) const
{
	return pruebas[indice - 1];
}

/***********************************************************************/
// Método PRIVADO compartido por: 
//      RegistroDemarca & operator () (int columna);
//		RegistroDeMarca & operator () (int fila) const;
// para evitar la duplicidad de código.
// Devuelve una referencia a un elemento de la matriz dada su posición.
//
// PRE: 1 <= fila <= num_marcas
// PRE: 1 <= columna <= la_fila (fila).num_marcas

RegistroDeMarca & MatrizMarcas :: el_elemento (int fila, int columna) const
{
	return pruebas[fila - 1][columna - 1];
}

/***********************************************************************/
// Guarda un dato MatrizMarcas en un fichero de texto llamado nombre . El
// fichero será un fichero de marcas.
// Parámetros: nombre, nombre del fichero en el que se guarda la matriz

void MatrizMarcas :: EscribirMatrizMarcasTxt (const string & nombre) const
{
	if (num_pruebas > 0) {
		ofstream fo (nombre);
		
		fo << "MARCAS" << endl;
		
		fo << (*this);
		
		fo.close();
	}
}

/***********************************************************************/
// Guarda un dato MatrizMarcas en un fichero binario llamado nombre . El
// fichero será un fichero de marcas.
// Parámetros: nombre, nombre del fichero en el que se guarda la matriz

void MatrizMarcas :: EscribirMatrizMarcasBin (const string & nombre) const
{
	if (num_pruebas > 0) {
		
		ofstream fo (nombre, ios::binary);
		
		const int TAM = 100;
		char buffer[TAM];
		int longitud;
		Fecha la_fecha;
		Tiempo el_tiempo;
		
		fo << "MARCAS_BIN\n";
		
		// Número de pruebas
		
		fo.write (reinterpret_cast<const char*>(&num_pruebas), sizeof(int));
		
		// Escribir las pruebas
		
		for (int i = 0 ; i < num_pruebas ; i++) {
			longitud = pruebas[i].Etiqueta().length();
			
			fo.write (reinterpret_cast<const char*>(&longitud), sizeof(int));
			
			strcpy (buffer, pruebas[i].Etiqueta().c_str());
			
			fo.write (reinterpret_cast<const char*>(buffer), longitud);
		}
		
		// Registros de marca
		
		for (int i = 0 ; i < num_pruebas ; i++) {
			for (int j = 1 ; j <= pruebas[i].NumMarcas() ; j++) {
				
				longitud = pruebas[i].Etiqueta().length();
				
				fo.write (reinterpret_cast<const char*>(&longitud), 
						  sizeof(int));
				
				strcpy (buffer, pruebas[i].Etiqueta().c_str());
				
				fo.write (reinterpret_cast<const char*>(buffer), longitud);
				
				la_fecha = pruebas[i][j].GetFecha();
				
				fo.write (reinterpret_cast<const char*>(&la_fecha),
						  sizeof(Fecha));
				
				longitud = pruebas[i][j].GetLicencia().length();
				
				fo.write (reinterpret_cast<const char*>(&longitud),
						  sizeof(int));
				
				strcpy (buffer, pruebas[i][j].GetLicencia().c_str());
				
				fo.write (reinterpret_cast<const char*>(buffer), longitud);
				
				el_tiempo = pruebas[i][j].GetTiempo();
				
				fo.write (reinterpret_cast<const char*>(&el_tiempo),
						  sizeof(Tiempo));
			}
		}
		
		fo.close();
	}
}

/***********************************************************************/
// Lee un dato MatrizMarcas de un fichero de texto llamado nombre . El 
// fichero será un fichero de marcas.
// Parámetros: nombre, nombre del fichero de marcas

void MatrizMarcas :: LeerMatrizMarcasTxt (const string & nombre)
{
	LiberaMemoria();
	
	ifstream fi (nombre);
	
	string cadena;
	
	getline (fi, cadena);	// Coger la cadena mágica
	
	if (cadena == "MARCAS") {
		
		// Saltar comentarios
		
		while (fi.peek() == '#')
			getline (fi, cadena);
		
		fi >> (*this);
	}
	
	fi.close();
}

/***********************************************************************/
// Lee un dato MatrizMarcas de un fichero binario llamado nombre . El 
// fichero será un fichero de marcas.
// Parámetros: nombre, nombre del fichero de marcas

void MatrizMarcas :: LeerMatrizMarcasBin (const string & nombre)
{
	LiberaMemoria();
	
	ifstream fi (nombre, ios::binary);
	
	// Coger la primera línea que debería contener la cadena mágica
	
	string cadena;
	
	getline (fi, cadena);
	
	if (cadena == "MARCAS_BIN") {
		
		const int TAM = 100;
		char buffer[TAM];
		int numero;
		Fecha la_fecha;
		Tiempo el_tiempo;
		string la_licencia;
		
		// Saltar comentarios
		
		while (fi.peek() == '#')
			getline (fi, cadena);
		
		// Leer pruebas
		
		fi.read (reinterpret_cast<char*>(&num_pruebas), sizeof(int));
		
		ReservaMemoria (num_pruebas);
		
		for (int i = 0 ; i < num_pruebas ; i++) {
			
			fi.read (reinterpret_cast<char*>(&numero), sizeof(int));
			
			fi.read (reinterpret_cast<char*>(buffer), numero);
			
			buffer[numero] = '\0';
			
			pruebas[i].SetEtiqueta ((string)buffer);
		}
		
		fi.read (reinterpret_cast<char*>(&numero), sizeof(int));
		
		while (!fi.eof()) {
			
			fi.read (reinterpret_cast<char*>(buffer), numero);
			buffer[numero] = '\0';
			
			string prueba(buffer);
			
			fi.read (reinterpret_cast<char*>(&la_fecha), sizeof(Fecha));
			
			fi.read (reinterpret_cast<char*>(&numero), sizeof(int));
			
			fi.read (reinterpret_cast<char*>(buffer), numero);
			buffer[numero] = '\0';
			
			la_licencia = buffer;
			
			fi.read (reinterpret_cast<char*>(&el_tiempo), sizeof(Tiempo));
			
			RegistroDeMarca registro (la_fecha, la_licencia, el_tiempo);
			
			for (int i = 0 ; i < num_pruebas ; i++)
				if (pruebas[i].Etiqueta() == prueba)
					pruebas[i] += registro;
			
			fi.read (reinterpret_cast<char*>(&numero), sizeof(int));
		}
		
	}
	
	fi.close();
}


/***********************************************************************/
