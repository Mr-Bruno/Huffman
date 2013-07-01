## Modulo:  Makefile
## Fecha:   02/02/12
## Asignatura: FT

.SUFFIXES: .o .c .cc


CCOMPILER = g++
CFLAGS   = -g  -Wall
CXXFLAGS = "-O3"
LIBS = -lm
SRCS = huffman.cc 
OBJECTS = huffman.o
EXEC = huffman


all: $(EXEC)

$(EXEC): $(OBJECTS)
	@echo [Creando ejecutable]
	$(CCOMPILER) $(CFLAGS) $(CXXFLAGS) -o $(EXEC) $(OBJECTS) $(LIBS)
	@chmod 755 $(EXEC)

.cc.o:
	@echo Compilando $<
	@$(CCOMPILER) $(CFLAGS) $(INCLUDE_PATH) -c $<
	@echo Hecho!!

clean:
	@echo [Haciendo limpieza]
	@rm -f *~ $(OBJECTS) core
	@rm -f $(EXEC) $(GENERADOS)



#end Makefile


             

