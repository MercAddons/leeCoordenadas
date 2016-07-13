SRC = src
INC = include
OBJ = obj
BIN = bin
CXX = g++
LIB = lib
CPPFLAGS = -c -g -I$(INC) -I/home/mer/kinect/NiTE-Linux-x64-2.2/Include -std=c++11 `pkg-config --cflags opencv libopenni2`
LDFLAGS = `pkg-config --libs opencv libopenni2` -lViewer -lglut -lGL

all: $(BIN)/main
# ************ Compilación de módulos ************
$
$(BIN)/main: $(OBJ)/main.o $(LIB)/libViewer.a
	$(CXX) -ggdb -o $(BIN)/main $(OBJ)/main.o -L$(LIB) $(LDFLAGS)

#Bibliotecas
$(LIB)/libViewer.a: $(OBJ)/Viewer.o
	ar rvs $(LIB)/libViewer.a $(OBJ)/Viewer.o

#Objetos
$(OBJ)/main.o: $(SRC)/main.cpp $(INC)/Viewer.h
	$(CXX) $(CPPFLAGS) $(SRC)/main.cpp -o $(OBJ)/main.o

$(OBJ)/Viewer.o: $(SRC)/Viewer.cpp $(INC)/Viewer.h
	$(CXX) $(CPPFLAGS) $(SRC)/Viewer.cpp -o $(OBJ)/Viewer.o


# ************ Generación de documentación ******************
documentacion:
	doxygen doc/doxys/Doxyfile

# ************ Limpieza ************
clean :
	-rm $(OBJ)/* $(SRC)/*~ $(INC)/*~ ./*~

mrproper : clean
	-rm $(BIN)/* doc/html/*
