# Nom de l'exécutable
TARGET = run

# Compilateur
CXX = g++

# Options de compilation
CXXFLAGS = -Wall -Wextra -std=c++17

# Fichiers source
SRCS = main.cpp

# Fichiers objets
OBJS = $(SRCS:.cpp=.o)

# Règle principale
all: $(TARGET)

# Compilation de l'exécutable
$(TARGET): $(OBJS)
	$(CXX) -o $(TARGET) $(OBJS)

# Compilation des fichiers objets
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Nettoyage des fichiers compilés
clean:
	rm -f $(OBJS) $(TARGET)

# Nettoyage complet
distclean: clean
	rm -f *~

# Règle par défaut
.PHONY: all clean distclean

