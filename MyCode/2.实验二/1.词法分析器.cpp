#define  _CRT_SECURE_NO_WARNINGS
#include "global.h"
#include <ctype.h>
int main28()
{
    char fname[FSIZE];

    error = fopen("error.txt", "w+");
    if (error == NULL)
    {
        printf("cannot create error.txt!\n");
    }
    out = fopen("out.txt", "w+");
    if (out == NULL)
    {
        printf("cannot create out.txt!\n");
    }
    printf("please input filename: \n");
    scanf("%s", fname);
    in = fopen(fname, "r");
    if (in == NULL)
    {
        printf("error: cannot open file %s\n", fname);
        return -1;
    }
    headCh = predeal(in);

    while (fgets(buf, BSIZE, in) != NULL)
    {
        head = headCh;
        int len = strlen(buf);
        buf[len - 1] = '\0';
        //  printf("buf:$%s$\tline:%d\n", buf, line);
        start = 0;
        while (headCh != '\0')
        {
            while (buf[start] == ' ' && headCh == ' ')
            {
                start++;
            }
            if (headCh == ' ')
            {
                if (buf[start] == '\0')break;
                headCh = buf[start++];
            }
            //      printf("start = %d\n", start);
                  // printf("headCH=%c\n",headCh);
            if (isalpha(headCh))
            {
                //       printf("ooooooo: DEAL ALPHA\n");
                dealAlpha();
            }
            else if (isdigit(headCh))
            {
                //        printf("ooooooo: DEAL DIGIT\n");
                dealDigit();
            }
            else if (headCh == '/')
            {
                //      printf("ooooooo: DEAL NOTATION\n");
                if (dealNotation() == -1)
                {
                    printf("notation too long to analyze, skip this line...\n");
                    fputc('\n', out);
                    break;
                }
            }
            else if (isBorder(headCh))
            {
                //           printf("ooooooo: DEAL BORDER\n");
                dealBorder();
            }
            else if (headCh == '\'' || headCh == '"')
            {
                //      printf("ooooooo: DEAL CHAR\n");
                dealChar(headCh);
            }
            else // not available start
            {
                fprintf(error, "L%d\tcannot analyse %c\n", line, headCh);
                headCh = buf[start];

            }
            start++;
            //    flag = 1;
        }
        line++;
        flag = 0;
        headCh = goBlank(in);
        if (isNotation == 0)
        {
            fprintf(out, "%c%s\n", head, buf);
        }
        isNotation = 0;
    }


    puts("Everything has done...");
    writeToken();
    writeVarTable();
    writeConTable();
    fclose(in);
    fclose(out);
    fclose(error);
    printf("错误日志\t\t\terror.txt\n");
    printf("Token文件\t\t\ttoken.txt\n");
    printf("无注释头文件的源文件日志\tout.txt\n");
    printf("常量符号表\t\t\tconTable.txt\n");
    printf("变量符号表\t\t\tvarTable.txt\n");
    return 0;
}
/**预处理**/
char predeal(FILE* in)
{
    char ch;
    ch = goBlank(in);
    while (ch == '#')
    {
        fgets(buf, BSIZE, in);
        dealInclude(buf);
        line++;
        fputc('\n', out);
        ch = goBlank(in);
    }
    printf("headers done...\n");
    return ch;
}

/** deal headers, like #include <...>**/
void dealInclude(char* buf)
{
    char include[15];
    char ch;
    int i = 9;
    strncpy(include, buf, 9);
    include[9] = '\0';
    //printf("%s%d",include,strlen(include));
    if (strcmp(include, "include <") == 0)
    {
        while ((ch = buf[i]) != '>')
        {
            i++;
            if (ch == '\n')
            {
                fprintf(error, "L%d\theaders end without '>'\n", line);
                break;
            }
        }
    }
    else
    {
        fprintf(error, "L%d\theaders format error\n", line);
    }

}

/**step blanks and count line number**/
char goBlank(FILE* in)
{
    char ch;
    do
    {
        ch = fgetc(in);
        if (ch == '\n')
        {
            line++;
            //  printf("goblank\n");
            fputc('\n', out);
        }
    } while (ch == ' ' || ch == '\n' || ch == '\t');
    return ch;
}

/**deal begin with alpha**/
void dealAlpha()
{
    int symbol;
    int id;
    char word[100];
    Token token;
    VarTable varTable;
    int i;
    word[0] = headCh;
    for (i = start; isdigit(buf[i]) || isalpha(buf[i]); i++)
    {
        word[i - start + 1] = buf[i];
    }
    word[i - start + 1] = '\0';
    // forward = i;
    start = i;
    headCh = buf[start];


    symbol = isKeyword(word);
    /**not keyword**/
    if (symbol == -1)
    {
        /*  id = isInVarTable(word);
          if(id ==-1) //not in the varTable
          {
              varTable.id = varTableNum;
              strcpy(varTable.name, word);
              varTableArray[varTableNum] = varTable;
              varTableNum++;
              id = varTable.id;
          }*/

        varTable.id = varTableNum;
        strcpy(varTable.name, word);
        varTableArray[varTableNum] = varTable;
        varTableNum++;

        token.symbol = IDN;
        sprintf(token.attr, "%d", varTable.id);//change int to string
        strcpy(token.name, word);
        tokenArray[tokenNum] = token;
        tokenNum++;
    }
    /** is keyword**/
    else
    {
        token.symbol = symbol;
        strcpy(token.name, word);
        strcpy(token.attr, "--");
        tokenArray[tokenNum] = token;
        tokenNum++;
    }
}

/**判断是否是关键字**/
int isKeyword(char* word)
{
    int i;
    for (i = 0; keywordList[i][0]; i++)
    {
        if (strcmp(word, keywordList[i]) == 0)
        {
            return i + 256;
        }
    }
    return -1;
}

/**将token数组写入文件**/
void writeToken()
{
    FILE* ftoken;
    int i = 0;
    ftoken = fopen("token.txt", "w+");
    if (ftoken == NULL)
    {
        printf("cannot create file token.txt!\n");
    }

    for (i = 0; i < tokenNum; i++)
    {
        fprintf(ftoken, "%s\t\t(%d, %s)\n", tokenArray[i].name, tokenArray[i].symbol, tokenArray[i].attr);
    }
    fclose(ftoken);
}

/**将变量符号表写入文件**/
void writeVarTable()
{
    FILE* fvarTable;
    int i = 0;
    fvarTable = fopen("varTable.txt", "w+");
    if (fvarTable == NULL)
    {
        printf("cannot create file varTable.txt!\n");
    }

    for (i = 0; i < varTableNum; i++)
    {
        fprintf(fvarTable, "%s\t\t%d\n", varTableArray[i].name, varTableArray[i].id);
    }
    fclose(fvarTable);
}

/**将常量符号表写入文件**/
void writeConTable()
{
    FILE* fconTable;
    int i = 0;
    fconTable = fopen("conTable.txt", "w+");
    if (fconTable == NULL)
    {
        printf("cannot create file conTable.txt!\n");
    }

    for (i = 0; i < conTableNum; i++)
    {
        fprintf(fconTable, "%s\t\t%d\n", conTableArray[i].name, conTableArray[i].id);
    }
    fclose(fconTable);
}

/**deal with digit**/
void dealDigit()
{
    int symbol;
    int id;
    char word[100];
    Token token;
    ConTable conTable;
    int i;
    word[0] = headCh;
    for (i = start; isdigit(buf[i]); i++)
    {
        word[i - start + 1] = buf[i];
    }
    if (buf[i] == '.')
    {
        if (!isdigit(buf[++i]))
        {
            start = i;
            headCh = buf[start];
            fprintf(error, "L%d\tunavailabe float\n", line);
            return;
        }
        word[i - start] = '.';
        for (; isdigit(buf[i]); i++)
        {
            word[i - start + 1] = buf[i];
        }
        word[i - start + 1] = '\0';
        // forward = i;
        start = i;
        headCh = buf[start];

        id = isInConTable(word);
        /**不在常量表里，新加项**/
        if (id == -1)
        {
            conTable.id = conTableNum;
            strcpy(conTable.name, word);
            conTableArray[conTableNum] = conTable;
            conTableNum++;
            id = conTable.id;
        }

        token.symbol = FNUM;
        sprintf(token.attr, "%d", id);//change int to string
        strcpy(token.name, word);
        tokenArray[tokenNum] = token;
        tokenNum++;
    }
    else
    {
        word[i - start + 1] = '\0';
        // forward = i;
        start = i;
        headCh = buf[start];

        id = isInConTable(word);
        /**不在常量表里，新加项**/
        if (id == -1)
        {
            conTable.id = conTableNum;
            strcpy(conTable.name, word);
            conTableArray[conTableNum] = conTable;
            conTableNum++;
            id = conTable.id;
        }

        token.symbol = INUM;
        sprintf(token.attr, "%d", id);//change int to string
        strcpy(token.name, word);
        tokenArray[tokenNum] = token;
        tokenNum++;
    }

}

/**处理界符**/
void dealBorder()
{
    Token token;
    char s[3];
    int i;
    s[0] = headCh;
    s[1] = buf[start];
    s[2] = '\0';
    if (s[1] != '\0')
    {
        //deal two border
        for (i = 0; borderList[i][0]; i++)
        {
            if (strcmp(s, borderList[i]) == 0)
            {
                strcpy(token.name, s);
                token.symbol = i + 400;
                strcpy(token.attr, "--");
                tokenArray[tokenNum++] = token;
                start++;
                headCh = buf[start];
                return;
            }
        }
    }
    /**处理单界符**/
    s[1] = '\0';
    for (i = 0; borderList[i][0]; i++)
    {
        if (strcmp(s, borderList[i]) == 0)
        {

            strcpy(token.name, s);
            token.symbol = i + 400;
            strcpy(token.attr, "--");
            tokenArray[tokenNum++] = token;

            //  start++;
            headCh = buf[start];
            return;
        }
    }
}

int isBorder(char ch)
{
    int i;
    for (i = 0; borderList[i][0]; i++)
    {
        if (ch == borderList[i][0])
        {
            return 1;
        }
    }
    return 0;
}

/**处理注释**/
int dealNotation()
{
    char ch = buf[start];
    int i;
    int notationLen = 0;
    Token token;
    //printf("dealNotation: ch = %c\n", ch);
    /**除号处理**/
    if (ch != '/' && ch != '*')
    {
        strcpy(token.name, "/");
        strcpy(token.attr, "--");
        token.symbol = DIV;
        tokenArray[tokenNum++] = token;
        start++;
        headCh = buf[start];
        return 0;
    }
    if (ch == '/')
    {
        fputc('\n', out);
        isNotation = 1;
        headCh = '\0';
        return 0;
    }
    else if (ch == '*')
    {
        for (i = start + 1;; i++)
        {
            if (buf[i] == '\0')
            {
                fgets(buf, BSIZE, in);
                line++;
                fputc('\n', out);
                start = 0;
                headCh = '\0';
                i = -1;
            }
            else
            {
                while (!(buf[i] == '*' && buf[i + 1] == '/'))
                {
                    i++;
                    if (++notationLen == LIMIT_NOTATION)
                    {
                        fprintf(error, "L%d\tnotation too long\n", line);
                        isNotation = 1;
                        return -1;
                    }
                    //   printf("notationLen = %d\n", notationLen);
                    if (buf[i + 1] == '\0')
                    {
                        fgets(buf, BSIZE, in);
                        line++;
                        fputc('\n', out);
                        i = 0;
                    }
                }
                fputc('\n', out);
                isNotation = 1;
                start = i + 2;
                headCh = buf[start];
                return 0;
            }
        }

    }
}

/**处理字符常量**/
void dealChar(char ch)
{
    Token token;
    ConTable conTable;
    int i = start;
    int id;
    int j;
    char word[100];
    word[0] = ch;
    if (ch == '\'')//const char
    {
        if (buf[i] == '\\')//change char
        {
            for (j = 0; j < 12; j++)
            {
                if (buf[i + 1] == changeList[j])
                {
                    word[1] = '\\';
                    word[2] = buf[i + 1];
                    word[3] = '\'';
                    word[4] = '\0';
                    strcpy(token.name, word);
                    strcpy(token.attr, "--");
                    token.symbol = j + 500;

                    tokenArray[tokenNum++] = token;
                    start = i + 3;
                    headCh = buf[start];
                    return;
                }
            }
            /**error: 转义字符不合法**/
            if (j == 12)
            {
                fprintf(error, "L%d\tunavailable change char\n", line);
            }
        }
        else if (buf[i + 1] != '\'')
        {
            fprintf(error, "L%d\tthe length of const char is unavailabe\n", line);
            for (i = i + 2; buf[i] != '\''; i++);
            start = i + 1;
            headCh = buf[start];
            return;
        }
        else
        {
            word[1] = buf[i];
            word[2] = '\'';
            word[3] = '\0';
            id = isInConTable(word);
            /**不在常量表里，新加项**/
            if (id == -1)
            {
                conTable.id = conTableNum;
                strcpy(conTable.name, word);
                conTableArray[conTableNum++] = conTable;
                id = conTable.id;
            }

            token.symbol = CCHAR;
            sprintf(token.attr, "%d", id);//change int to string
            strcpy(token.name, word);
            tokenArray[tokenNum++] = token;
            start = i + 2;
            headCh = buf[start];
            return;
        }
    }
    else if (ch == '"')//字符串常量
    {
        for (; buf[i] != '"'; i++)
        {
            word[i - start + 1] = buf[i];
            //  printf("buf%d:%s\n", i, buf);

        }
        word[i - start + 1] = '"';
        word[i - start + 2] = '\0';

        id = isInConTable(word);
        /**不在常量表里**/
        if (id == -1)
        {
            conTable.id = conTableNum;
            strcpy(conTable.name, word);
            conTableArray[conTableNum++] = conTable;
            id = conTable.id;
        }

        token.symbol = CSTR;
        sprintf(token.attr, "%d", id);//change int to string
        strcpy(token.name, word);
        tokenArray[tokenNum++] = token;
        start = i + 1;
        headCh = buf[start];
    }
}

/**判断是否在变量符号表中，返回位置，不在返回-1**/
int isInVarTable(char* name)
{
    int i;
    for (i = 0; i < varTableNum; i++)
    {
        if (strcmp(name, varTableArray[i].name) == 0)
        {
            return varTableArray[i].id;
        }
    }
    return -1;
}

/**判断是否在常量符号表中，返回位置，不在返回-1**/
int isInConTable(char* name)
{
    int i;
    for (i = 0; i < conTableNum; i++)
    {
        if (strcmp(name, conTableArray[i].name) == 0)
        {
            return conTableArray[i].id;
        }
    }
    return -1;
}