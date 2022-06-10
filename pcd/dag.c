#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    char op;
    char lc[5], rc[5];
    char labels[5][5];
    int p1, p2, count;
} node;

int main()
{
    char ar[10][5], str[20];
    int i = -1, j = 0, k, l, f1, f2, n;
    FILE *fp;
    fp = fopen("stmt.txt", "r");
    node stmt[10];
    while (fgets(str, 20, fp) != NULL)
    {
        i++;
        stmt[i].count = 0;
        stmt[i].p1 = -1;
        stmt[i].p2 = -1;
        stmt[i].op = '\0';
        if (strstr(str, "+"))
            stmt[i].op = '+';
        else if (strstr(str, "*"))
            stmt[i].op = '*';
        else if (strstr(str, "-"))
            stmt[i].op = '-';
        else if (strstr(str, "/"))
            stmt[i].op = '/';
        else if (strstr(str, "["))
            stmt[i].op = '[';
        strcpy(stmt[i].labels[0], strtok(str, "="));
        stmt[i].count++;
        strcpy(stmt[i].lc, strtok(NULL, "+*-/%[ \n\0"));
        if (stmt[i].op != '\0')
            strcpy(stmt[i].rc, strtok(NULL, "]\n\0"));
        else
            strcpy(stmt[i].rc, "\0");
        f1 = 0;
        if (strcmp(stmt[i].rc, "\0") == 0)
        {
            for (k = i - 1; k >= 0; k--)
            {
                for (l = 0; l < stmt[k].count; l++)
                {
                    if (strcmp(stmt[i].lc, stmt[k].labels[l]) == 0)
                    {
                        strcpy(stmt[k].labels[stmt[k].count], stmt[i].labels[0]);
                        stmt[k].count++;
                        i--;
                        f1 = 1;
                        break;
                    }
                }
                if (f1 == 1)
                    break;
            }
        }
        if (f1 == 1)
            continue;
        f2 = 0;
        for (k = i - 1; k >= 0; k--)
        {
            for (l = 0; l < stmt[k].count; l++)
            {
                if (strcmp(stmt[i].lc, stmt[k].labels[l]) == 0)
                {
                    stmt[i].p1 = k;
                    f2 = 1;
                    break;
                }
            }
            if (f2 == 0)
                if (strcmp(stmt[i].lc, stmt[k].lc) == 0 || strcmp(stmt[i].lc, stmt[k].rc) == 0)
                {
                    stmt[i].p1 = k;
                    break;
                }
        }
        f2 = 0;
        if (strcmp(stmt[i].rc, "\0") != 0)
            for (k = i - 1; k >= 0; k--)
            {
                for (l = 0; l < stmt[k].count; l++)
                {
                    if (strcmp(stmt[i].rc, stmt[k].labels[l]) == 0)
                    {
                        stmt[i].p2 = k;
                        f2 = 1;
                        break;
                    }
                }
                if (f2 == 0)
                    if (strcmp(stmt[i].rc, stmt[k].lc) == 0 || strcmp(stmt[i].rc, stmt[k].rc) == 0)
                    {
                        stmt[i].p2 = k;
                        break;
                    }
            }
        if (stmt[i].p1 == stmt[i].p2)
        {
            n = stmt[i].p1;
            if (stmt[i].op == stmt[n].op)
            {
                strcpy(stmt[n].labels[stmt[n].count], stmt[i].labels[0]);
                stmt[n].count++;
                i--;
            }
        }
    }
    for (k = 0; k <= i; k++)
    {
        if (stmt[k].op == '[')
            printf("\n\nAddress %d:: Node [] is created with %s", &stmt[k], stmt[k].lc);
        else
            printf("\n\nAddress %d:: Node %c is created with %s", &stmt[k], stmt[k].op, stmt[k].lc);
        if (stmt[k].p1 != -1)
            printf(" from address %d", &stmt[stmt[k].p1]);
        printf(" as left child and %s", stmt[k].rc);
        if (stmt[k].p2 != -1)
            printf(" from address %d", &stmt[stmt[k].p2]);
        printf(" as right child with labels");
        for (l = 0; l < stmt[k].count; l++)
            printf(" %s,", stmt[k].labels[l]);
    }
    printf("\n");
}

// dag 2
//  #include <stdio.h>
//  #include <stdlib.h>
//  #include <time.h>
//  #define MIN_PER_RANK 1
//  #define MAX_PER_RANK 5
//  #define MIN_RANKS 3
//  #define MAX_RANKS 5
//  #define PERCENT 30
//  void main()
//  {
//      int i, j, k, nodes = 0;
//      srand(time(NULL));
//      int ranks = MIN_RANKS + (rand() % (MAX_RANKS - MIN_RANKS + 1));
//      printf("DIRECTED ACYCLIC GRAPH\n");
//      for (i = 1; i < ranks; i++)
//      {
//          int new_nodes = MIN_PER_RANK + (rand() % (MAX_PER_RANK - MIN_PER_RANK + 1));
//          for (j = 0; j < nodes; j++)
//              for (k = 0; k < new_nodes; k++)
//                  if ((rand() % 100) < PERCENT)
//                      printf("%d->%d;\n", j, k + nodes);
//          nodes += new_nodes;
//      }
//  }
