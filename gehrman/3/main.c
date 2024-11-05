#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>


int main(int argc, char **argv)
{

    if (argc != 2)
    {
        perror("No filepath provided");
        return 1;
    }


    char *filePath = argv[1];

    // 1. �������� �������� � ����������� �������������� ������������.
    printf("RID: %d\nEID: %d\n", getuid(), geteuid());

    // 2. ��������� ���� � ������� fopen(3)
    FILE *input = fopen(filePath, "r");
    if (input)
    {
        char *line = NULL;
        size_t len = 0;
        ssize_t read;

        while ((read = getline(&line, &len, input)) != -1)
        {
            printf("%s", line); 
        }

        free(line);
        fclose(input);
    }
    else
    {
        perror(filePath);
    }

    // 3. ��������, ����� �������� � ����������� �������������� ������������ ���������.
    if (setuid(getuid()) == -1)
    {
        perror("setuid failed");
    }


    // 4. ��������� ������ ��� ����.
    printf("RID: %d\nEID: %d\n", getuid(), geteuid());

    input = fopen(filePath, "r");
    if (input)
    {
        char *line = NULL;
        size_t len = 0;
        ssize_t read;

        while ((read = getline(&line, &len, input)) != -1)
        {
            printf("%s", line); 
        }

        free(line);
        fclose(input);
    }
    else
    {
        perror(filePath);
    }

    return 0;
}
