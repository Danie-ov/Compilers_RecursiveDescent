#ifndef TENNIS

enum token {
     TITLE = 1,
	 NAME,
	 WIMBLEDON, 
	 OPEN_AUSTRALIAN, 
	 OPEN_FRENCH,
	 GENDER,
	 YEAR_NUM,
	 PLAYER_NAME,
};

enum delimiter {
	COMMA = 44,
	THROUGH
};

enum gender {
	MAN = 1,
	WOMAN,
	MAX_SIZE = 50
};

char *token_name(enum token token);

struct player {
	char playerName[MAX_SIZE];
	int numOfWinsInWimbledon;
	int typeGen;
};

union _lexVal{
   struct player _plyaer;
   char name[MAX_SIZE];
   int gender;
   int numOfWins;
   int year;
};

extern union _lexVal lexicalValue;

void errorMsg(const char *s);

int lookahead;
int calcYears(int start, int end);
struct player calcMaxWins(struct player p1, struct player p2);

void match();
void parse();
void start();
struct player playerList();
struct player player();
int wimbledon();
int open_australian();
int open_french();
int yearList();
int years_range();

#endif