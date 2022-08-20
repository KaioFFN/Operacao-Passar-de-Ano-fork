TARGET = grafo

all:
	make compilar

compilar: main.c grafos.c grafos.h
	gcc -o $(TARGET) main.c grafos.c grafos.h
run:
	./$(TARGET)

clean:
	$(RM) $(TARGET)
