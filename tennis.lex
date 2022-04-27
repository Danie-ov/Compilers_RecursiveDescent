%{
#include "tennis.h"
extern int atoi (const char *);
extern void exit(int);

union _lexVal lexicalValue;
%}

%option noyywrap
%option yylineno

%%

"** Winners **" {return TITLE;}

\<name\> {return NAME;}

\<Wimbledon\> { return WIMBLEDON; }

\<Australian" "Open\> { return OPEN_AUSTRALIAN; }

\<French" "Open\>  { return OPEN_FRENCH; }

18[5-9][0-9]|19[0-9]{2}|[2-9][0-9]{3,} { lexicalValue.year = atoi(yytext); return YEAR_NUM;}

["`'][a-zA-Z]+(" "[a-zA-Z]+)*["`'] {strcpy(lexicalValue.name,yytext+1); lexicalValue.name[strlen(lexicalValue.name)-1]='\0';return PLAYER_NAME;}

\<Woman\> {lexicalValue.gender = WOMAN; return GENDER; }

\<Man\> {lexicalValue.gender = MAN; return GENDER; }

","  {return ',';}

"-" {return '-';}

[\t\n\r ]+

.          { char e[100];
            sprintf(e, "unrecognized token %c", yytext[0]);  
            errorMsg(e);  
             exit(1);
           }

%%

char *token_name(enum token token)
{
    static char *names[] = {
         "EOF", "TITLE", "NAME", "WIMBLEDON", "OPEN_AUSTRALIAN",
         "OPEN_FRENCH", "YEAR_NUM", "GENDER", "PLAYER_NAME" };
    
    return token <= PLAYER_NAME ? names[token] : "unknown token";
}