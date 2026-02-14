/* front.c - a lexical analyzer system for simple
             arithmetic expressions */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <string.h>

/* Global declarations */
/* Variables */
int  charClass;
char  lexeme [100];
char  nextChar;
int  lexLen;
int  token;
int  nextToken;
FILE *in_fp;

/* Function declarations */
void addChar();
void getChar();
void getNonBlank();
int lex();

/* Character classes */
#define LETTER 0
#define DIGIT 1
#define QUOTE 2
#define UNKNOWN 99
#define QUOTE 2

/* Token codes */
#define STR_LIT 8
#define INT_LIT 10
#define FLOAT_LIT 9
#define IDENT 11
#define LT_OP 18
#define RT_OP 19
#define EQUALS_OP 20
#define ADD_OP 21
#define SUB_OP 22
#define MULT_OP 23
#define DIV_OP 24
#define LEFT_PAREN 25
#define RIGHT_PAREN 26
#define COMMA 27
#define SEMICOLON 28
#define CR 30
#define RELOP 31       /* <, >, <=, >=, <> */
#define STRING_LIT 32  /* "String Content" */
#define KEYWORD 33     /* PRINT, IF, etc. */
#define VAR 34         /* Single letter variable */
#define ERROR_TOKEN 99

/******************************************************/
/* main driver */
int main()
{
  /* Open the input data file and process its contents */
  if ((in_fp = fopen("front.in", "r")) == NULL)
    printf("ERROR - cannot open front.in \n");
  else
  {
    getChar();
    do
    {
      lex();
    } while (nextToken != EOF);
  }
  return 0;
}

/*****************************************************/
/* isKeyword - checks if the current lexeme is a known keyword */
int isKeyword(char *str) {
    const char *keywords[] = {
        "PRINT", "IF", "THEN", "GOTO", "INPUT", "LET", "GOSUB", 
        "RETURN", "CLEAR", "LIST", "RUN", "END"
    };
    int numKeywords = 12;
    for (int i = 0; i < numKeywords; i++) {
        if (strcmp(str, keywords[i]) == 0) {
            return 1;
        }
    }
    return 0;
}

/*****************************************************/
/* lookup - a function to lookup operators and parentheses
            and return the token */

int lookup(char ch)
{
  switch (ch)
  {
  case '(':
    addChar();
    nextToken = LEFT_PAREN;
    break;

  case ')':
    addChar();
    nextToken = RIGHT_PAREN;
    break;

  case '+':
    addChar();
    nextToken = ADD_OP;
    break;

  case '-':
    addChar();
    nextToken = SUB_OP;
    break;

  case '*':
    addChar();
    nextToken = MULT_OP;
    break;

    case  '/':
      addChar();
      nextToken = DIV_OP;
      break;

    case ',':
        addChar();
        nextToken = COMMA;
        break;

    case ';':
        addChar();
        nextToken = SEMICOLON;
        break;
        
    case '=':
        addChar();
        nextToken = ASSIGN_OP; 
        break;
        
    case '<':
        addChar();
        getChar();
        if (nextChar == '>' || nextChar == '=') {
            addChar(); // Add the second char (> or =)
            nextToken = RELOP;
        } else {
            nextToken = RELOP; 
            return nextToken;
        }
        break;

    case '>':
        addChar();
        getChar(); // Look ahead
        if (nextChar == '=' || nextChar == '<') { /* Handling >< if grammar implies it, grammar says > (<|=|e) */
            addChar();
            nextToken = RELOP;
        } else {
            nextToken = RELOP;
            return nextToken;
        }
        break;

    default:
      addChar();
      nextToken = EOF;
      break;
  }
  return nextToken;
}

/*****************************************************/
/* addChar - a function to add nextChar to lexeme */
void addChar()
{
  if (lexLen <= 98)
  {
    lexeme[lexLen++] = nextChar;
    lexeme[lexLen] = 0;
  }
  else
    printf("Error - lexeme is too long \n");
}
/*****************************************************/
/* getChar - a function to get the next character of
             input and determine its character class */
void getChar()
{
  int c = getc(in_fp);
  if (c == EOF)
  {
    charClass = EOF;
    nextChar = 0;
  }
  else
  {
    nextChar = (char)c;
    if (isalpha((unsigned char)nextChar))
      charClass = LETTER;
    else if (isdigit((unsigned char)nextChar))
      charClass = DIGIT;
    else if (nextChar == '"')
      charClass = QUOTE;
    else if (nextChar == '"')
      charClass = QUOTE;
    else
      charClass = UNKNOWN;
  }
}

/*****************************************************/
/* getNonBlank - a function to call getChar until it
                 returns a non-whitespace character */
void getNonBlank() {
  while  (isspace(nextChar) && nextChar != '\n')
    getChar();
}

/* examines current lexeme and returns specific token or IDENT if it's not a keyword */
int keywordLookup() {
  if (strcmp(lexeme,"PRINT")==0 || strcmp(lexeme,"PR")==0)
    return PRINT;
  else if (strcmp(lexeme,"INPUT")==0)
    return INPUT;
  else if (strcmp(lexeme,"GOSUB")==0)
    return GOSUB;
  else if (strcmp(lexeme,"LET")==0)
    return LET;
  //else if ... finish all the keywords!
  else
    return IDENT;
  
}

/*****************************************************/
/* lex - a simple lexical analyzer for arithmetic
         expressions 
   // depends on charClass and nextChar already being set by the caller
         */
int lex()
{
  lexLen = 0;
  getNonBlank();
  switch  (charClass) {
/* Parse identifiers */
    case  LETTER:
      addChar();
      getChar();
      while  (charClass == LETTER || charClass == DIGIT) {
        addChar();
        getChar();
      }
    /* Check if it's a keyword */
      if (isKeyword(lexeme)) {
        nextToken = KEYWORD;
      } 
      /* Grammar says var is single letter A-Z */
      else if (strlen(lexeme) == 1 && isupper(lexeme[0])) {
        nextToken = VAR;
      } 
      else {
        nextToken = IDENT;
      }
      break;

    /* Parse integer literals */
  case DIGIT:
    addChar();
    getChar();
    while (charClass == DIGIT)
    {
      addChar();
      getChar();
    }
    nextToken = INT_LIT;
    break;

/* Parse Strings */
  case QUOTE:
     addChar(); // Add opening "
     getChar();
     while (nextChar != '"' && nextChar != '\n' && nextChar != EOF) {
       addChar();
       getChar();
       }
       if (nextChar == '"') {
         addChar(); // Add closing "
         getChar(); // Setup next char
         nextToken = STRING_LIT;
        } else {
          nextToken = ERROR_TOKEN; // Unterminated string
          printf("Error: Unterminated string literal\n");
        }
        break;

/* Parentheses and operators */
  case UNKNOWN:
    if (nextChar == '\n') {
      nextToken = CR;
      lexeme[0] = 'C'; lexeme[1] = 'R'; lexeme[2] = '\0';
      getChar(); // Consume the newline
    } else {
      lookup(nextChar);
      if (nextToken != RELOP) {
      getChar();
      }
    }
        break;

/* EOF */
    case  EOF:
      nextToken = EOF;
      lexeme[0] = 'E';
      lexeme[1] = 'O';
      lexeme[2] = 'F';
      lexeme[3] = 0;
      break;

 } /* End of switch */
 printf("Next token is: %d, Next lexeme is %s\n", nextToken, lexeme);
  return  nextToken;
} /* End of function lex */
