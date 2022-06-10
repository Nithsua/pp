// lex tk.l
// gcc lex.yy.c
// ./a.out

FILE *yyin;
%{
    int keyword=0,operator=0,symbols=0,identifiers=0;
%}

%%
"while"|"if"|"for"|"else"|"int"|"float"|"char"|"string"|"double" {ECHO;printf("\nkeyword::\n");}

[a-zA-Z_]+[0-9]* {ECHO;printf("\nidentifiers::\n");}

"<="|"=="|"="|"++"|"-"|"*"|"+"|"<"|">"|"--"|">="|"/" {ECHO;printf("\noperators::\n");}

";"|","|"("|")" {ECHO;printf("\nsymbols:::\n"); }

. ;
%%

int yywrap(){};

void main(int argc,char *argv)
{
    yyin=fopen("test.c", "r");
    yylex();
    printf("hello");
    fclose(yyin);
}


