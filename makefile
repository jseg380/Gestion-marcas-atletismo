#############################################################################
#
#
#							     PROYECTO  C++
# 						Gestión de marcas de atletismo
#
# Autor: Juan Manuel Segura Duarte
#
#############################################################################

#··········································································
# MACROS

HOME = .
BIN = $(HOME)/bin
INCLUDE = $(HOME)/include
LIB = $(HOME)/lib
OBJ = $(HOME)/obj
SRC = $(HOME)/src

PROYECTO = Gestión de marcas de atletismo

#··········································································

all: \
		preambulo \
		$(BIN)/Demo \
		despedida

#··········································································

preambulo:
	@echo
	@echo ---------------------------------------------------------
	@echo
	@echo "   METODOLOGÍA DE LA PROGRAMACIÓN"
	@echo
	@echo "   Autor: Juan Manuel Segura Duarte"
	@echo
	@echo "   Proyecto: $(PROYECTO)"
	@echo
	@echo ---------------------------------------------------------
	@echo
	@echo
	@echo Creando ejecutables ...
	@echo
	@echo

despedida:
	@echo
	@echo ... ejecutables creados
	@echo

#··········································································
# EJECUTABLES


$(BIN)/Demo : $(OBJ)/Demo.o \
			  $(LIB)/libClasesRankingMarcas.a \
			  $(LIB)/libMatrizMarcas.a \
			  $(LIB)/libUtils.a
	@echo
	@echo Creando ejecutable Demo
	@echo
	g++ -o $(BIN)/Demo \
		   $(OBJ)/Demo.o \
		   -L$(LIB) -lMatrizMarcas -lClasesRankingMarcas -lUtils


#··········································································
# OBJETOS


$(OBJ)/Demo.o : $(SRC)/Demo.cpp
	@echo
	@echo Creando objeto Demo.o
	@echo
	g++ -c -o $(OBJ)/Demo.o \
			  $(SRC)/Demo.cpp -I$(INCLUDE) -std=c++14


#··········································································
# BIBLIOTECAS

# ClasesRankingMarcas ...........................................

$(LIB)/libClasesRankingMarcas.a : $(OBJ)/ClaseFecha.o \
								  $(OBJ)/ClaseTiempo.o \
								  $(OBJ)/ClaseLicencia.o \
								  $(OBJ)/ClaseRegistroDeMarca.o
	@echo
	@echo Creando biblioteca libClasesRankingMarcas.a
	@echo
	ar rvs $(LIB)/libClasesRankingMarcas.a \
		   $(OBJ)/ClaseFecha.o \
		   $(OBJ)/ClaseTiempo.o \
		   $(OBJ)/ClaseLicencia.o \
		   $(OBJ)/ClaseRegistroDeMarca.o

$(LIB)/libMatrizMarcas.a : $(OBJ)/VectorMarcas.o \
						   $(OBJ)/MatrizMarcas.o
	@echo
	@echo Creando biblioteca libMatrizMarcas.a
	@echo
	ar rvs $(LIB)/libMatrizMarcas.a \
		   $(OBJ)/VectorMarcas.o \
		   $(OBJ)/MatrizMarcas.o

$(LIB)/libUtils.a : $(OBJ)/Utils.o
	@echo
	@echo Creando biblioteca libUtils.a
	@echo
	ar rvs $(LIB)/libUtils.a \
		   $(OBJ)/Utils.o

# Objetos para las bibliotecas

$(OBJ)/ClaseFecha.o : $(SRC)/ClaseFecha.cpp \
					  $(INCLUDE)/ClaseFecha.h
	@echo
	@echo Creando objeto ClaseFecha.o
	@echo
	g++ -c -o $(OBJ)/ClaseFecha.o \
			  $(SRC)/ClaseFecha.cpp -I$(INCLUDE) -std=c++14

$(OBJ)/ClaseTiempo.o : $(SRC)/ClaseTiempo.cpp \
					   $(INCLUDE)/ClaseTiempo.h \
					   $(INCLUDE)/ClaseFecha.h
	@echo
	@echo Creando objeto ClaseTiempo.o
	@echo
	g++ -c -o $(OBJ)/ClaseTiempo.o \
			  $(SRC)/ClaseTiempo.cpp -I$(INCLUDE) -std=c++14

$(OBJ)/ClaseLicencia.o : $(SRC)/ClaseLicencia.cpp \
						 $(INCLUDE)/ClaseLicencia.h
	@echo
	@echo Creando objeto ClaseLicencia.o
	@echo
	g++ -c -o $(OBJ)/ClaseLicencia.o \
			  $(SRC)/ClaseLicencia.cpp -I$(INCLUDE) -std=c++14

$(OBJ)/ClaseRegistroDeMarca.o : $(SRC)/ClaseRegistroDeMarca.cpp \
								$(INCLUDE)/ClaseRegistroDeMarca.h \
								$(INCLUDE)/ClaseFecha.h \
								$(INCLUDE)/ClaseTiempo.h \
								$(INCLUDE)/ClaseLicencia.h
	@echo
	@echo Creando objeto ClaseRegistroDeMarca.o
	@echo
	g++ -c -o $(OBJ)/ClaseRegistroDeMarca.o \
			  $(SRC)/ClaseRegistroDeMarca.cpp -I$(INCLUDE) -std=c++14

$(OBJ)/VectorMarcas.o : $(SRC)/VectorMarcas.cpp \
						$(INCLUDE)/VectorMarcas.h \
						$(SRC)/ClaseRegistroDeMarca.cpp \
						$(INCLUDE)/ClaseRegistroDeMarca.h
	@echo
	@echo Creando objeto VectorMarcas.o
	@echo
	g++ -c -o $(OBJ)/VectorMarcas.o \
			  $(SRC)/VectorMarcas.cpp -I$(INCLUDE) -std=c++14

$(OBJ)/MatrizMarcas.o : $(SRC)/MatrizMarcas.cpp \
						$(INCLUDE)/MatrizMarcas.h \
						$(INCLUDE)/VectorMarcas.h
	@echo
	@echo Creando objeto MatrizMarcas.o
	@echo
	g++ -c -o $(OBJ)/MatrizMarcas.o \
			  $(SRC)/MatrizMarcas.cpp -I$(INCLUDE) -std=c++14

$(OBJ)/Utils.o : $(SRC)/Utils.cpp
	@echo
	@echo Creando objeto Utils.o
	@echo
	g++ -c -o $(OBJ)/Utils.o \
			  $(SRC)/Utils.cpp -I$(INCLUDE) -std=c++14


#··········································································
# LIMPIEZA

# (Error suppression)
# Redirecciona los errores para que no se muestren cuando no se haya podido
# borrar un archivo debido a que no existía
# 2> /dev/null "ignora" el error de rm
# || true "ignora" el error de make
ERROR_SUP = 2> /dev/null || true

clean : clean-objs

clean-objs:
	@echo
	@echo Borrando objetos ...
	@echo
	
	-rm $(OBJ)/Demo.o $(ERROR_SUP)
	-rm $(OBJ)/ClaseFecha.o $(ERROR_SUP)
	-rm $(OBJ)/ClaseTiempo.o $(ERROR_SUP)
	-rm $(OBJ)/ClaseLicencia.o $(ERROR_SUP)
	-rm $(OBJ)/ClaseRegistroDeMarca.o $(ERROR_SUP)
	-rm $(OBJ)/VectorMarcas.o $(ERROR_SUP)
	-rm $(OBJ)/MatrizMarcas.o $(ERROR_SUP)
	-rm $(OBJ)/Utils.o $(ERROR_SUP)
	
	@echo
	@echo ... objetos borrados
	@echo

clean-bins:
	@echo
	@echo Borrando ejecutables ...
	@echo
	
	-rm $(BIN)/Demo $(ERROR_SUP)
	
	@echo
	@echo ... ejecutables borrados
	@echo

clean-libs:
	@echo
	@echo Borrando bibliotecas ...
	@echo
	
	-rm $(LIB)/libClasesRankingMarcas.a $(ERROR_SUP)
	-rm $(LIB)/libMatrizMarcas.a $(ERROR_SUP)
	-rm $(LIB)/libUtils.a $(ERROR_SUP)
	
	@echo
	@echo ... bibliotecas borradas
	@echo

mr.proper : clean-objs clean-bins clean-libs
