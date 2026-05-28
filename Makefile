# ============================================================================
# MAKEFILE - PROJET C-TRANSIT (INF 132)
# ============================================================================

CC = gcc
CFLAGS = -Wall -Wextra -std=c99
TARGET = c_transit.exe

# Liste des objets mis à jour avec persistence.o
OBJ = main.o edition.o stats.o affichage.o persistence.o

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ)
	@echo "=========================================================="
	@echo "✅ Compilation reussie ! Executez avec : .\\c_transit.exe"
	@echo "=========================================================="

main.o: main.c transport.h edition.h stats.h affichage.h persistence.h
	$(CC) $(CFLAGS) -c main.c

edition.o: edition.c edition.h transport.h
	$(CC) $(CFLAGS) -c edition.c

stats.o: stats.c stats.h transport.h
	$(CC) $(CFLAGS) -c stats.c

affichage.o: affichage.c affichage.h transport.h
	$(CC) $(CFLAGS) -c affichage.c

persistence.o: persistence.c persistence.h transport.h
	$(CC) $(CFLAGS) -c persistence.c

clean:
	del /f /q $(OBJ) $(TARGET) 2>nul