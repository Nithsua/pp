%{
    #include"y.tab.h"
    extern yylval;
%}

%%
[0-9]+ {yylval=atoi(yytext);return num;}
[a-zA-Z]+ {return id;}
[\t]+;
\n {return 0;}
. {return yytext[0];}
%%

int yywrap(){
    return 1;
}
