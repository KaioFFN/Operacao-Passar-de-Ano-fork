TARGET = grafo

all:
	make compilar

compilar: main.c grafos.c impressao.c OperacaoPassarDeAno.h
	gcc -o $(TARGET) main.c grafos.c impressao.c OperacaoPassarDeAno.h -g
run:
	./$(TARGET)

clean:
	$(RM) $(TARGET)
