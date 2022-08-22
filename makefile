TARGET = grafo

all:
	make compilar

compilar: main.c grafos.c grafos.h 
	gcc -o $(TARGET) main.c grafos.c grafos.h -g
run:
	./$(TARGET)

clean:
	$(RM) $(TARGET)
