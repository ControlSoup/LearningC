#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Defines the maximum string length for all static sub string operations
#define MAX_STR_LEN 25

// ===================================
// ====== Variables and Structs ======
// ===================================
 
typedef enum{
    // Symbols
    Token_ASSIGN,
    Token_PLUS,
    Token_MINUS,
    Token_BANG,
    Token_ASTERISK,
    Token_FSLASH,
    Token_COMMA,
    Token_SEMICOLON,
    Token_LPAREN,
    Token_RPAREN,
    Token_LBRACE,
    Token_RBRACE,

    // Types 
    Token_INT,

    // Evaluation 
    Token_ISEQUAL,
    Token_NOTEQUAL,
    Token_LT,
    Token_GT,


    // Identifiers
    Token_IDENT,
    Token_FUNCTION,
    Token_LET,
    Token_IF,
    Token_ELSE,
    Token_RETURN,
    Token_TRUE,
    Token_FALSE,

    // Terminations
    Token_EOF,
    Token_ILLEGAL

} TokenType;


char* token_strings[] = {
    "Token_ASSIGN",
    "Token_PLUS",
    "Token_MINUS",
    "Token_BANG",
    "Token_ASTERISK",
    "Token_FSLASH",
    "Token_COMMA",
    "Token_SEMICOLON",
    "Token_LPAREN",
    "Token_RPAREN",
    "Token_LBRACE",
    "Token_RBRACE",
    "Token_INT",
    "Token_ISEQUAL",
    "Token_NOTEQUAL",
    "Token_LT",
    "Token_GT",
    "Token_IDENT",
    "Token_FUNCTION",
    "Token_LET",
    "Token_IF",
    "Token_ELSE",
    "Token_RETURN",
    "Token_TRUE",
    "Token_FALSE",
    "Token_EOF",
    "Token_ILLEGAL"
};


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
    return (('a' <= character && character <= 'z') || ('A' <= character && character <= 'Z') || (character == '_'));
}


int _is_digit(char character){
    return ('0' <= character && character <= '9');
}

char * _static_char_to_string(char character){
    /* Returns a string contianing the input character
    */
    static char char_to_string[2] = {'$','\0'};    
    char_to_string[0] = character;

    if (character != '$' && char_to_string[0] == '$'){
        printf("    ERRROR| _static_char_to_string failed with character [%c]", character);
        exit(1);
    };

    return char_to_string;
}


char * _static_substring(char* string, int start_index, int end_index){

    static char identifier[MAX_STR_LEN];

    if(end_index - start_index > MAX_STR_LEN){
        printf("  ERROR| MAX digit or identifier length exeeded with [%s]\n",string);
        printf("         start_index = [%d] end_index = [%d]",start_index,end_index);
        exit(0);
    };

    int i = 0;
    while (i < end_index - start_index){
        identifier[i++] = string[start_index + i];
    };
    identifier[i] = '\0';

    return identifier;
}

char _lexer_peek_char(Lexer* ptr_Lexer){
    return ptr_Lexer->input[ptr_Lexer->read_position];
}


void _lexer_read_char(Lexer* ptr_Lexer){
    // Ensure we are not at the end_index of the input
    if (ptr_Lexer->read_position >= ptr_Lexer->input_length){
        ptr_Lexer->current_char = 0;
    }
    else {
        ptr_Lexer->current_char = ptr_Lexer->input[ptr_Lexer->read_position];
    };

    ptr_Lexer->position = ptr_Lexer->read_position;
    ptr_Lexer->read_position += 1;

}


Token _lexer_read_char_pair(
    Lexer* ptr_Lexer, 
    char second_char,
    TokenType DefaultTokenType,
    TokenType IfTrueTokenType
){
    /* Returns a Token with the correct Token Type 
       and literal to make new char pairs easier to implment
    */
    char current_char = ptr_Lexer->current_char;
    char peek_char = _lexer_peek_char(ptr_Lexer);

    Token UpdatedToken = {
        DefaultTokenType,
        _static_char_to_string(current_char)
    };

    if (peek_char == second_char){
        static char char_pair[3];
        char_pair[0] = current_char;
        char_pair[1] = peek_char;
        char_pair[2] = '\0';

        UpdatedToken.Type = IfTrueTokenType;
        UpdatedToken.literal = char_pair;
        _lexer_read_char(ptr_Lexer);
    };

    return UpdatedToken;
}


char* _lexer_read_digit(Lexer* ptr_Lexer){
    /*
        :returns: a string contiaing the current digits 
    */

    int start_index = ptr_Lexer->position;

    while (_is_digit(ptr_Lexer->current_char)){
        _lexer_read_char(ptr_Lexer);
    };

    int end_index =  ptr_Lexer->position;


    return _static_substring(ptr_Lexer->input, start_index, end_index);
}


char* _lexer_read_identifier(Lexer* ptr_Lexer){
    /*
        :returns: a string contianing the current identifier
    */

    int start_index = ptr_Lexer->position;

    while (_is_letter(ptr_Lexer->current_char)){
        _lexer_read_char(ptr_Lexer);
    };

    int end_index =  ptr_Lexer->position;

    return _static_substring(ptr_Lexer->input, start_index, end_index);
}


void _skip_whitespace(Lexer* ptr_Lexter){
    while((ptr_Lexter->current_char == ' ') || 
          (ptr_Lexter->current_char == '\t') || 
          (ptr_Lexter->current_char == '\n') || 
          (ptr_Lexter->current_char == '\r')
    ){
        _lexer_read_char(ptr_Lexter);
    };
}


TokenType _ident_token(char* identifier){
    /*
        :returns: TokenType that matches known identifier strings
    */
    if (strcmp("fn", identifier) == 0) return Token_FUNCTION;
    else if (strcmp("let", identifier) == 0) return Token_LET;
    else if (strcmp("if", identifier) == 0) return Token_IF;
    else if (strcmp("else", identifier) == 0) return Token_ELSE;
    else if (strcmp("return", identifier) == 0) return Token_RETURN;
    else if (strcmp("true", identifier) == 0) return Token_TRUE;
    else if (strcmp("false", identifier) == 0) return Token_FALSE;
    else return Token_IDENT;
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
    _lexer_read_char(&NewLexer);
    return NewLexer;
}


Token next_token(Lexer* ptr_Lexer){
    /*
        :returns: the next Token in the Lexer 
    */

    Token CurrentToken;

    _skip_whitespace(ptr_Lexer);


    CurrentToken.literal = _static_char_to_string(ptr_Lexer->current_char);

    // Evaluate what kind of token this is
    switch (ptr_Lexer->current_char){
        case '=':
            CurrentToken = _lexer_read_char_pair(
                ptr_Lexer,
                '=',
                Token_ASSIGN,
                Token_ISEQUAL
            );
            break;
        case '+':
            CurrentToken.Type = Token_PLUS;
            break;
        case '-':
            CurrentToken.Type = Token_MINUS;
            break;
        case '!':
            CurrentToken = _lexer_read_char_pair(
                ptr_Lexer,
                '=',
                Token_BANG,
                Token_NOTEQUAL
            );
            break;
        case '*':
            CurrentToken.Type = Token_ASTERISK;
            break;
        case '/':
            CurrentToken.Type = Token_FSLASH;
            break;
        case ',':
            CurrentToken.Type = Token_COMMA;
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
        case '{':
            CurrentToken.Type = Token_LBRACE;
            break;
        case '}':
            CurrentToken.Type = Token_RBRACE;
            break;
        case '<':
            CurrentToken.Type = Token_LT;
            break;
        case '>':
            CurrentToken.Type = Token_GT;
            break;
        case '\0':
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
            return CurrentToken;
            break;
    }


    _lexer_read_char(ptr_Lexer);

    return CurrentToken;
}

void print_token(Token PrintToken){
    printf("Type: [%s], Literal: [%s]\n",token_strings[(int)PrintToken.Type], PrintToken.literal);
}
