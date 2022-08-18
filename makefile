TARGET = grafo

all:
	make compilar

compilar: grafos.c
	gcc -o $(TARGET) grafos.c

run:
	./$(TARGET)

clean:
	$(RM) $(TARGET)
