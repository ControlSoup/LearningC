#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
Notes:
    - Max identifier length is 25 characters long
*/

#define MAX_STR_LEN 25
#define NUM_IDENT 14 


// ===================================
// ====== Variables and Structs ======
// ===================================
 
typedef enum{
    Token_ILLEGAL,
    Token_EOF,
    Token_IDENT,
    Token_INT,
    Token_ASSIGN,
    Token_PLUS,
    Token_COMMA,
    Token_SEMICOLON,
    Token_LPAREN,
    Token_RPAREN,
    Token_LBRACE,
    Token_RBRACE,
    Token_FUNCTION,
    Token_LET
} TokenType;

typedef  struct{
    char* input;
    int input_length;
    char current_char; // current char under examination
    int position; // location of current_char inside input 
    int read_position; // location after current char
} Lexer;


typedef struct{
    TokenType Type;
    char* literal;
} Token;


// ===============================
// ====== Private Functions ======
// ===============================



int _is_letter(char character){
    return (('a' <= character && character <= 'z') || ('A' < character && character <= 'Z') || (character == '_'));
}

int _is_digit(char character){
    return ('0' <= character && character <= '9');
}

void lexer_read_char(Lexer* ptr_Lexer){
    // Ensure we are not at the end of the input
    if (ptr_Lexer->read_position >= ptr_Lexer->input_length){
        ptr_Lexer->current_char = 0;
    }

    // Get the next character in the input
    else ptr_Lexer->current_char = ptr_Lexer->input[ptr_Lexer->read_position];

    ptr_Lexer->position = ptr_Lexer->read_position;
    ptr_Lexer->read_position += 1;
}

char* _lexer_read_digit(Lexer* ptr_Lexer){
    /*
        :returns: a string contiaing the current digits 
    */

    int start = ptr_Lexer->position;

    while (_is_digit(ptr_Lexer->current_char)){
        lexer_read_char(ptr_Lexer);
    };

    int end =  ptr_Lexer->position;

    if(end > MAX_STR_LEN){
        printf("  ERROR| MAX digit or identifier length exeeded\n");
        exit(0);
    };

    static char identifier[MAX_STR_LEN];

    // Populate the output with the relavent chars
    int i = 0;
    while (i < end-start){
        identifier[i] = ptr_Lexer->input[start + i];
        i++;
    };

    // Ensure last char is an end of string
    identifier[i] = '\0';

    return identifier;
}


char* _lexer_read_identifier(Lexer* ptr_Lexer){
    /*
        :returns: a string contianing the current identifier
    */

    int start = ptr_Lexer->position;

    while (_is_letter(ptr_Lexer->current_char)){
        lexer_read_char(ptr_Lexer);
    };

    int end =  ptr_Lexer->position;

    if(end > MAX_STR_LEN){
        printf("  ERROR| MAX digit or identifier length exeeded\n");
        exit(0);
    };

    static char identifier[MAX_STR_LEN];

    // Populate the output with the relavent chars
    int i = 0;
    while (i < end-start){
        identifier[i] = ptr_Lexer->input[start + i];
        i++;
    };

    // Ensure last char is an end of string
    identifier[i] = '\0';

    return identifier;
}

void _skip_whitespace(Lexer* ptr_Lexter){
    while((ptr_Lexter->current_char == ' ') || 
          (ptr_Lexter->current_char == '\t') || 
          (ptr_Lexter->current_char == '\n') || 
          (ptr_Lexter->current_char == '\r')
    ){
        lexer_read_char(ptr_Lexter);
    };
}

TokenType _ident_token(char* identifier){
    /*
        :returns: TokenType that matches known IDENT strings
    */
    if (strcmp("fn", identifier) == 0)return Token_FUNCTION;
    else if (strcmp("let", identifier) == 0) return Token_LET;
    else{
        printf("     ERROR| _ident_token() FAILED with IDENT: %s\n", identifier);
    }
}

// ==============================
// ====== Public Functions ======
// ==============================


Lexer new_lexer(char* input){
    /*
        :returns: Lexer with properly intialized value 
    */
    Lexer NewLexer = {
        .input = input,
        .input_length = strlen(input),
        .current_char = 0,
        .position = 0,
        .read_position = 0 
    };

    // Update read position
    lexer_read_char(&NewLexer);
    return NewLexer;
}


Token next_token(Lexer* ptr_Lexer){
    /*
        :returns: the next Token in the Lexer 
    */

    Token CurrentToken;

    _skip_whitespace(ptr_Lexer);

    static char char_to_string[2] = {'\0','\0'};    
    char_to_string[0] = ptr_Lexer->current_char;

    CurrentToken.literal = char_to_string;

    // Evaluate what kind of token this is
    switch (ptr_Lexer->current_char){
        case '=':
            CurrentToken.Type = Token_ASSIGN;
            break;
        case ';':
            CurrentToken.Type = Token_SEMICOLON;
            break;
        case '(':
            CurrentToken.Type = Token_LPAREN;
            break;
        case ')':
            CurrentToken.Type = Token_RPAREN;
            break;
        case ',':
            CurrentToken.Type = Token_COMMA;
            break;
        case '+':
            CurrentToken.Type = Token_PLUS;
            break;
        case '{':
            CurrentToken.Type = Token_LBRACE;
            break;
        case '}':
            CurrentToken.Type = Token_RBRACE;
            break;
        case 0:
            CurrentToken.Type = Token_EOF;
            break;
        default:
            if (_is_letter(ptr_Lexer->current_char)){
                CurrentToken.literal = _lexer_read_identifier(ptr_Lexer);
                CurrentToken.Type = _ident_token(CurrentToken.literal); 
            }
            else if (_is_digit(ptr_Lexer->current_char)){
                CurrentToken.literal = _lexer_read_digit(ptr_Lexer);
                CurrentToken.Type = Token_INT;
            }
            else {
                CurrentToken.Type = Token_ILLEGAL;
                printf("    ERROR| Illegal symbol [%c]\n", ptr_Lexer->current_char);
                exit(0);
            };
    }

    
    lexer_read_char(ptr_Lexer);

    return CurrentToken;
}
