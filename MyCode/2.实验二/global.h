#ifndef GLOBAL_H_INCLUDED
#define GLOBAL_H_INCLUDED

#include <stdio.h>
#include <string.h>

#define BSIZE   1024
#define FSIZE   50
#define TSIZE   1024
#define VTSIZE 1024
#define CTSIZE  1024
#define LIMIT_NOTATION 10

/**define keyword**/
#define INCLUDE         256
#define AUTO                 257
#define BREAK                258
#define CASE                259
#define CHAR                260
#define CONST               261
#define CONTINUE        262
#define DEFAULT             263
#define DO                      264
#define DOUBLE                  265
#define ELSE                    266
#define ENUM                267
#define EXTERN                      268
#define FLOAT               269
#define FOR                     270
#define GOTO                271
#define IF                      272
#define  INT                 273
#define  LONG                 274
#define REGISTER            275
#define RETURN             276
#define SHORT              277
#define SIGNED             278
#define SIZEOF           279
#define STATIC         280
#define STRUCT          281
#define SWITCH       282
#define TYPEDEF     283
#define UNION           284
#define UNSIGNED    285
#define VOLATILE     286
#define WHILE          287

/**define variables and consts**/
#define IDN                 300
#define INUM               301
#define FNUM                302
#define CCHAR               303
#define CSTR                 304

/**define border**/
#define PLUS                  400
#define MINUS                   401
#define MUL                     402
#define DIV                   403
#define REM                     404
#define SEMI                   405
#define  COM                    406
#define  BLP                    407
#define  BRP                        408
#define  SRP 409
#define  SLP 410
#define  BIG 411
#define  SML 412
#define  EQU 413
#define  MLP 414
#define  MRP 415
#define  COL 416
#define  QUE 417
#define  SIG 418
#define  NOT 419
#define  AND 420
#define  OR  421
#define  PP 422
#define  MM 423
#define  EQEQ 424
#define  NOTL 425
#define  NOTR 426
#define  DECL 427
#define  BIGE 428
#define  SMLE 429
#define  NOTE 430
#define  AA 431
#define  OO 432
#define  ANDE 433
#define  MINUE 434
#define  MULE 435
#define  DIVE 436
#define  XOR 437
#define  RIGHT 438
#define  LEFT 439
#define  TURN 440

/**define change char**/
#define CA 500
#define CB 501
#define CF 502
#define CN 503
#define CR 504
#define CT 505
#define CV 506
#define CBSL 507
#define CQUE 508
#define CDQM 509
#define  CQM 510
#define ZERO 511

/**structs**/
typedef struct varTable
{
    int id;
    char name[100];
} VarTable;

typedef struct conTable
{
    int id;
    char name[100];
} ConTable;

typedef struct token
{
    char name[100];
    int symbol;
    char attr[100];
} Token;

/**variables**/
FILE* error;
FILE* out;
FILE* in;

int line = 1;
int tokenNum = 0;
int varTableNum = 0;
int conTableNum = 0;
int start = 0;
int forward = 0;
int flag = 0;
int isNotation = 0;
char buf[BSIZE];
Token tokenArray[TSIZE];
VarTable varTableArray[VTSIZE];
ConTable conTableArray[CTSIZE];
char headCh;
char head;
char* borderList[] = { "+","-","*","/","%",";",",","{","}",")","(",">","<","=","[","]",":","?","!","&","|",
                       "++","--","==","/*","*/",":=",">=","<=","!=","&&","||","+=","-=","*=","/=","^",">>","<<","~"
};//by order unnecessary notation
char* keywordList[] = { "include","auto","break","case","char","const","continue","default","do","double",
                       "else","enum","extern","float","for","goto","if","int","long","register",
                       "return","short","signed","sizeof","static","struct","switch","typedef",
                       "union","unsigned","volatile","while",""
};//by order
char changeList[12] = { 'a', 'b', 'f','n','r','t','v','\\','?','"','\'','0' };

/**Functions**/
char goBlank(FILE* in);
char predeal(FILE* in);
void dealInclude(char* in);
void dealAlpha();
void dealDigit();
void dealBorder();
int dealNotation();
void dealChar(char ch);
int isKeyword(char* word);
void writeToken();
void writeVarTable();
void writeConTable();
int isBorder(char ch);
int isInVarTable(char* name);
int isInConTable(char* name);



#endif // GLOBAL_H_INCLUDED