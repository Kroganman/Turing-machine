#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 255


void MTbegin(FILE *fl, int* mas, int i, char *command, int n1,int n2)
{
    n1 = ftell(fl);
    char comment[MAX_SIZE];
    fscanf (fl, "%s", command);
    while (strcmp (command, "end"))
    {
        if (!strcmp(command, "inc"))
        {
            mas[i]++;
            if (mas[i] == 256)
            {
                mas[i] = 0;
                printf ("\nThe cell was overfilled!Now it is zero!\n");
            }
        }
        else if (!strcmp(command, "movl"))
        {
            i--;
            if (i < 0)
                i = 254;
        }
        else if (!strcmp(command, "movr"))
        {
            i++;
            if (i > 254)
                i = 0;
        }
        else if (!strcmp(command, "dec"))
        {
            mas[i]--;
            if(mas[i] < 0)
            {
                mas[i] = 255;
                printf ("\nYou can not assign values less than zero!The value became 255!\n");
            }
        }
        else if (!strcmp(command, "print"))
        {
            printf ("%d\n", mas[i]);
        }
        else if (!strcmp(command, "get"))
        {
            scanf ("%d\n", &mas[i]);
        }
        else if (!strcmp(command, "printc"))
        {
            printf ("%c", mas[i]);
        }
        else if (!strcmp(command, "begin"))
        {
            while (mas[i] != 0)

                MTbegin(fl, mas, i, command, n1, n2);
        }
        else if (command[0] == '*')
        {
            fgets(comment, MAX_SIZE, fl);
        }
        fscanf (fl, "%s", command);
    }
    if (mas[i] != 0)
    {
        n2 = ftell(fl);
        n1 = n1 - n2;
        fseek (fl, n1, SEEK_CUR);
    }
}



int main(int argc, char *argv[])
{
    char command[MAX_SIZE];
    char comment[MAX_SIZE];
    int mas[MAX_SIZE] = {0};
    int i = 0;
    int n1 = 0;
    int n2 = 0;
    FILE *fl;


    if (argc < 2)
    {
        printf ("\nNeed arguments to run\n");
        return -1;
    }
    if ((fl = fopen(argv[1], "r")) == NULL)
    {
        printf ("\nError!Could not open file!\n");
        return -2;
    }


    while (!feof(fl))
    {
        fscanf (fl, "%s", command);
        if (!strcmp(command, "inc"))
        {
            mas[i]++;
            if (mas[i] == 256)
            {
                mas[i] = 0;
                printf ("\nThe cell was overfilled!Now it is zero\n");
            }
        }
        else if (!strcmp(command, "movl"))
        {
            i--;
            if (i < 0)
                i = 254;
        }
        else if (!strcmp(command, "movr"))
        {
            i++;
            if (i > 254)
                i = 0;
        }
        else if (!strcmp(command, "dec"))
        {
            mas[i]--;
            if (mas[i] < 0)
            {
                mas[i] = 255;
                printf ("\nYou can not assign values less than zero!The value became 255!\n");
            }
        }
        else if (!strcmp(command, "get"))
        {
            mas[i] = getchar();
        }
        else if (!strcmp(command, "print"))
        {
            printf ("%d\n", mas[i]);
        }
        else if (!strcmp(command, "printc"))
        {
            printf ("%c", mas[i]);
        }
        else if (!strcmp(command, "begin"))
        {
            while (mas[i] != 0)
            {
                MTbegin(fl, mas, i, command, n1, n2);
            }
        }
        else if (command[0] == '*')
        {
            fgets(comment, MAX_SIZE, fl);
        }
    }
    return 1;
}
