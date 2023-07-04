#include <stdio.h>
#include "../monkey_lexer.h"

#define NUM_TESTS 74 

int main(){
    char* test_input = "let five = 510;\n\
    let ten = 10;\n\
    \n\
    let add = fn(x, y) {\n\
    x + y;\n\
    };\n\
    \n\
    let result = add(five,ten);\n\
    !-/*5;\n\
    5 < 10 > 5;\n\
    if (5 < 10) {\n\
        return true;\n\
    } else {\n\
        return false;\n\
    }\n\
    \n\
    10 == 10;\n\
    10 != 9;";

    Token TestCases[NUM_TESTS] = {
        {Token_LET, "let"},
        {Token_IDENT, "five"},
        {Token_ASSIGN, "="},
        {Token_INT, "510"},
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
        {Token_BANG, "!"},
        {Token_MINUS, "-"},
        {Token_FSLASH, "/"},
        {Token_ASTERISK, "*"},
        {Token_INT, "5"},
        {Token_SEMICOLON, ";"},
        {Token_INT, "5"},
        {Token_LT, "<"},
        {Token_INT, "10"},
        {Token_GT, ">"},
        {Token_INT, "5"},
        {Token_SEMICOLON, ";"},
        {Token_IF, "if"},
        {Token_LPAREN, "("},
        {Token_INT, "5"},
        {Token_LT, "<"},
        {Token_INT, "10"},
        {Token_RPAREN, ")"},
        {Token_LBRACE, "{"},
        {Token_RETURN, "return"},
        {Token_TRUE, "true"},
        {Token_SEMICOLON, ";"},
        {Token_RBRACE, "}"},
        {Token_ELSE, "else"},
        {Token_LBRACE, "{"},
        {Token_RETURN, "return"},
        {Token_FALSE, "false"},
        {Token_SEMICOLON, ";"},
        {Token_RBRACE, "}"},
        {Token_INT, "10"},
        {Token_ISEQUAL, "=="},
        {Token_INT, "10"},
        {Token_SEMICOLON, ";"},
        {Token_INT, "10"},
        {Token_NOTEQUAL, "!="},
        {Token_INT, "9"},
        {Token_SEMICOLON, ";"},
        {Token_EOF, ""},
};
    
    Lexer TestLexer = new_lexer(test_input);
    Token NewToken;

    printf("\n");
    for (int i = 0; i < NUM_TESTS; i++){
        NewToken = next_token(&TestLexer); 
        if (
            (NewToken.Type == TestCases[i].Type) &&
            (strcmp(NewToken.literal,TestCases[i].literal) == 0)
        ) printf("Test #%d Passed, with literal [%s]\n\n",i,NewToken.literal);

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