# Definimos el compilador y las banderas de compilación
CXX = g++
CXXFLAGS = -Wall -g

# Definimos los archivos de origen y los archivos objeto
SRCS = src/Catacomb.cpp src/CellUI.cpp src/Chunk.cpp src/Controller.cpp src/Explorer.cpp src/Game.cpp src/main.cpp src/WindowSizeException.cpp
OBJS = $(SRCS:.cpp=.o)

# Definimos el nombre del ejecutable
EXEC = game

# Definimos las librerías de SFML
SFML_LIBS = -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

# Regla por defecto
all: $(EXEC)

# Regla para crear el ejecutable
$(EXEC): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(EXEC) $(OBJS) $(SFML_LIBS)

# Regla para compilar archivos .cpp a .o
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Regla para limpiar los archivos generados
clean:
	rm -f $(OBJS) $(EXEC)

# Regla para limpiar y recompilar
rebuild: clean all

# Para que el Makefile no intente usar los nombres de archivos como reglas
.PHONY: all clean rebuild
