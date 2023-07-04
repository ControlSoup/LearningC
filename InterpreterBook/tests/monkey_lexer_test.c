#include <stdio.h>
#include "../monkey_lexer.h"



int main(){
    char* test_input = "let five = 5;let ten = 10;let add = fn(x, y) {x + y;};let result = add(five,ten);";

    Token TestCases[] = {
        {Token_LET, "let"},
        {Token_IDENT, "five"},
        {Token_ASSIGN, "="},
        {Token_INT, "5"},
        {Token_SEMICOLON, ";"},
        {Token_LET, "let"},
        {Token_IDENT, "ten"},
        {Token_ASSIGN, "="},
        {Token_INT, "10"},
        {Token_SEMICOLON, ";"},
        {Token_LET, "let"},
        {Token_IDENT, "add"},
        {Token_ASSIGN, "="},
        {Token_FUNCTION, "fn"},
        {Token_LPAREN, "("},
        {Token_IDENT, "x"},
        {Token_COMMA, ","},
        {Token_IDENT, "y"},
        {Token_RPAREN, ")"},
        {Token_LBRACE, "{"},
        {Token_IDENT, "x"},
        {Token_PLUS, "+"},
        {Token_IDENT, "y"},
        {Token_SEMICOLON, ";"},
        {Token_RBRACE, "}"},
        {Token_SEMICOLON, ";"},
        {Token_LET, "let"},
        {Token_IDENT, "result"},
        {Token_ASSIGN, "="},
        {Token_IDENT, "add"},
        {Token_LPAREN, "("},
        {Token_IDENT, "five"},
        {Token_COMMA, ","},
        {Token_IDENT, "ten"},
        {Token_RPAREN, ")"},
        {Token_SEMICOLON, ";"},
        {Token_EOF, ""},
};
    
    Lexer TestLexer = new_lexer(test_input);
    Token NewToken;

    printf("\n");
    for (int i =0; i<8; i++){
        NewToken = next_token(&TestLexer); 
        if (
            (NewToken.Type == TestCases[i].Type) &&
            (strcmp(NewToken.literal,TestCases[i].literal) == 0)
        ) printf("Test #%d Passed\n\n",i);

        else {
            printf("Test #%d FAILED!\n",i);
            printf(
                "Expected Token [%d], got Token [%d]\n", 
                (int)TestCases[i].Type,
                (int)NewToken.Type 
            );
            printf(
                "Expected literal [%s], got literal [%s]\n\n", 
                TestCases[i].literal,
                NewToken.literal 
            );
        }
    }
}