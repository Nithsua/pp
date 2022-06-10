%{
    #include<stdio.h>
    #include<stdlib.h>
%}

%token num id;
%left '+''-';
%left '*''/';
%%
expr: expr '+' expr                                        
|expr '-' expr
|expr '*' expr
|expr '/' expr
|'-'num
|'-'id
|'('expr')'
|num
|id
;
%%

int main(int argc,char *argv)
{
    printf("enter the expression:::");
    yyparse();
    printf("valid expression");
    exit(0);
}
int yyerror(char *s)
{
printf("\nExpression is invalid");
exit(0);
}
