#include <stdio.h>
#include <string.h>
#include <stdlib.h> /* for exit() */
#include "tennis.h"

extern union _lexVal lexicalValue;
extern enum token yylex (void);

void match(int expectedToken)
{
    if (lookahead == expectedToken)
        lookahead = yylex();
    else
    {
        char e[100];
        sprintf(e, "error: expected token %s, found token %s",
                token_name(expectedToken), token_name(lookahead));
        errorMsg(e);
        exit(1);
    }
}

void parse()
{
    lookahead = yylex();
    start();
    if (lookahead != 0) {  // 0 means EOF
        errorMsg("EOF expected");
        exit(1);
    }
}

void start()
{
	match(TITLE);
    struct player p = playerList();
    if (p.typeGen == -1)
    {
        printf("There is no woman that win in Wimbledon\n");
    }else{
        printf("Woman with greatest number of wins at Wimbledon: %s (%d wins)\n",
               p.playerName, p.numOfWinsInWimbledon);
    }
}

struct player playerList()
{
	struct player playerWithMaxWins = {"", -1, -1};
    while (lookahead == NAME)
    {
        struct player p = player();
        if (p.typeGen == WOMAN)
            playerWithMaxWins = calcMaxWins(playerWithMaxWins, p);
    }
    return playerWithMaxWins;
}

struct player player()
{
	struct player p = {"", -1, -1};
	match(NAME);
	char name[MAX_SIZE];
	strcpy(p.playerName, lexicalValue.name);
	match(PLAYER_NAME);
	match(GENDER);
	p.typeGen = lexicalValue.gender;
	p.numOfWinsInWimbledon = wimbledon();
	open_australian();
	open_french();
	return p;
}	

int wimbledon()
{
    int numOfWins = 0;
    if (lookahead == WIMBLEDON)
    {
        match(WIMBLEDON);
        numOfWins = yearList();
    }
    return numOfWins;
}

int open_australian()
{
    int numOfWins = 0;
    if (lookahead == OPEN_AUSTRALIAN)
    {
        match(OPEN_AUSTRALIAN);
        numOfWins = yearList();
    }
    return numOfWins;
}

int open_french()
{
    int numOfWins = 0;
    if (lookahead == OPEN_FRENCH)
    {
        match(OPEN_FRENCH);
        numOfWins = yearList();
    }
    return numOfWins;
}

int yearList()
{
    int numOfYears = 0;
    numOfYears += years_range();
    while (lookahead == COMMA)
    {
		match(COMMA);
        numOfYears += years_range();
    }
    return numOfYears;
}

int years_range()
{
    int year1, year2;
    match(YEAR_NUM);
    year1 = lexicalValue.year;
    if (lookahead == THROUGH)
    {
        match(THROUGH);
        match(YEAR_NUM);
        year2 = lexicalValue.year;
        return calcYears(year1, year2);
    }
    return 1;
}

int main(int argc, char **argv)
{
    extern FILE *yyin;
    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s <input-file-name>\n", argv[0]);
        return 1;
    }
    yyin = fopen(argv[1], "r");
    if (yyin == NULL)
    {
        fprintf(stderr, "failed to open %s\n", argv[1]);
        return 2;
    }

    parse();

    fclose(yyin);
    return 0;
}

void errorMsg(const char *s)
{
    extern int yylineno;
    fprintf(stderr, "line %d: %s\n", yylineno, s);
}

int calcYears(int start, int end)
{
   return (end-start)+1;
}

struct player calcMaxWins(struct player p1, struct player p2)
{
	if(p1.numOfWinsInWimbledon >= p2.numOfWinsInWimbledon)
		return p1;
	else
		return p2;
}