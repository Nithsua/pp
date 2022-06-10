#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <ctype.h>
size_t len = 0;
size_t linelen;
char store1[10][1000];
char store2[10][1000];
int dtype[10], cnt = 0;
int count = 0;
char data_type[3][10] = {"int", "float", "double"};
void simple_table(char *ptr, char type[10])
{
    int declare = 0;
    int conditional = 0;
    if (ptr != NULL)
    {
        declare = 1;
        char *p = ptr;
        char str[10];
        int slen = 0;
        char *t = p;
        int jumplen = strlen(type);
        t = t + jumplen;
        while (*t != '\0')
        {
            char c = *t;
            str[slen++] = c;
            t = t + 1;
            if (*t == '=')
            {
                if (strcmp(type, "int ") == 0)
                    dtype[cnt++] = 0;
                else if (strcmp(type, "float ") == 0)
                    dtype[cnt++] = 1;
                else
                {
                    dtype[cnt++] = 2;
                }
                t = t + 1;
                str[slen] = '\0';
                strcpy(store1[count], str);
                slen = 0;
                str[0] = '\0';
                while (isdigit(*t) || *t == '.')
                {
                    char c = *t;
                    str[slen++] = c;
                    t = t + 1;
                }
                str[slen] = '\0';
                slen = 0;
                strcpy(store2[count], str);
            }
            if (*t == ',' | *t == ';')
            {
                count = count + 1;
                t = t + 1;
            }
        }
    }
}
int main()
{
    FILE *fp;
    char *line = NULL;
    fp = fopen("token.c", "r");
    while ((linelen = getline(&line, &len, fp)) != -1)
    {
        char *int1 = strstr(line, "int ");
        char *float1 = strstr(line, "float ");
        char *double1 = strstr(line, "double ");
        simple_table(int1, "int ");
        simple_table(float1, "float ");
        simple_table(double1, "double ");
    }
    fclose(fp);
    printf("\nSymbol Table:\n");
    int base = 1000;
    for (int i = 0; i < count; i++)
    {
        printf("%d \t %s \t %s \t %s \t %d\n", i + 1, store1[i],
               data_type[dtype[i]], store2[i], base);
        if (dtype[i] == 0)
        {
            base += 2;
        }
        else if (dtype[i] == 1)
        {
            base += 4;
        }
        else
        {
            base += 8;
        }
    }
    return 0;
}