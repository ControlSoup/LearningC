#include "monkey_lexer.h"

#define MAX_LINE_LEN 100

const char* EXIT_TAG = ":wq";

const char* TITLE_CARD = "\n=========================   MonkeyType   =============================\n"; 
const char* EXIT_CARD = "=========================    Exiting     =============================\n"; 
const char* LINE_TAG = ">> ";
int s1 = 0;

int main(){

    char input_str[MAX_LINE_LEN];

    Lexer MonkeyLexer;
    Token CurrentToken;

    printf("%s", TITLE_CARD);
    printf("Begin by typing a line and pressing ENTER:\n");

    while (1){
        printf("%s",LINE_TAG);
        scanf("%[^\n]%*c",input_str);

        if (strcmp(input_str,EXIT_TAG) == 0){
            printf("%s", EXIT_CARD);
            exit(1);
        };

        MonkeyLexer = new_lexer(input_str);
        CurrentToken = next_token(&MonkeyLexer);

        while (CurrentToken.Type != Token_EOF){
            CurrentToken = next_token(&MonkeyLexer);
            print_token(CurrentToken);
        }

    }
}