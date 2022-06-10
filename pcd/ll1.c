#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int i=0,top=0;
char stack[20], ip[20];

void push(char c)
{
    if(top > 20)
        printf("Stack Overflow");
    else
        stack[top++] = c;
}

void pop()
{
    if(top < 0)
        printf("Stack Underflow");
    else
        top--;
}

void error()
{
    printf("Error");
    exit(0);
}

int main()
{
    int n;
    printf("Given Grammar\n");
    printf("E -> TE'\n");
    printf("E' -> +TE' | e\n");
    printf("T -> FT' | e\n");
    printf("T' -> *FT' | e\n");
    printf("F -> (E) | i'\n\n");
    printf("Enter string to be parsed: ");
    scanf(" %s",ip);
    n = strlen(ip);
    ip[n] = '$';
    ip[n+1] = '\0';
    push('$');
    push('E');
    /*3 conditions
    1. top = terminal = $
    2. top = terminal != $
    3. top != terminal*/
    while(ip[i] != '\0')
    {
        if(ip[i] == '$' && stack[top-1] == '$')
            printf("Parsing successful");
        else if(ip[i] == stack[top-1])
        {
            printf("\nMatch of %c ",ip[i]);
            i++;
            pop();
        }
        else
        {
            if(stack[top-1] == 'E' && (ip[i] == 'i' || ip[i] == '('))
            {
                printf("\nE -> TE' ");
                pop();
                push('A'); // E' = A
                push('T');
            }
            else if(stack[top-1] == 'A' && (ip[i] == '+'))
            {
                printf("\nE' -> +TE' ");
                pop();
                push('A');
                push('T');
                push('+');
            }
            else if(stack[top-1] == 'A' && (ip[i] == ')') || (ip[i] == '$'))
            {
                printf("\nE' -> e");
                pop();
            }
            else if(stack[top-1] == 'T' && (ip[i] == '(' || ip[i] == 'i'
                pop();
            }
            else if(stack[top-1] == 'F' && (ip[i] == 'i'))
            {
                printf("\nF -> i");
                pop();
                push('i');
            }
            else if(stack[top-1] == 'F' && (ip[i] == '('))
            {
                printf("\nF -> (E)");
                pop();
                push(')');
                push('E');
                push('(');
            }
            else
                error();
        }
    }
    return 0;
}
