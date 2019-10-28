TARGET=test
C_SRCFILES=main.cpp expr_parser.c expr_lexer.c
OBJ_FILES=${C_SRCFILES:.c=.o}
.PHONY:	clean

$(TARGET):	$(OBJ_FILES)
	gcc -g -o $@ $(OBJ_FILES)

expr_lexer.c:	gramatica.l
	flex -o $@ $^

expr_parser.c: ejemplobison.y
	bison --defines=tokens.h -o $@ $<

%.o: %.c tokens.h
	gcc -c -g -o $@ $<

run: $(TARGET)
	./$(TARGET) < input.txt

clean:
	rm -f expr_parser.c expr_lexer.c
	rm -f *.o
	rm -f tokens.h
	rm -f $(TARGET)