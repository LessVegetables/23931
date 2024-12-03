#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <ctype.h>

int main()
{
    int fd = open("test.txt", O_RDONLY); //��������� ���� �� ������
    if (fd == -1)
    {
        printf("Your file was open incorrectly. Pls, stop breaking my programm...\n");
        exit(0);
    }
    int lines[200] = {0}; //��� ������ ������ �����
    int lenght[200] = {0}; //� ��� ����� ����� �� �������
    lines[1] = 0L; //���������� ������ ������ ������
    int counter = 1; //��� �ޣ����, ������������� ����� ������
    int len = 0; //����� ������ ����� ������ �ģ� ����
    char buf, text[1024]; //buf ������ ������� �� �����, � text ����� ������������ �������� ������
    int test;
    while(read(fd, &buf, 1) != 0) //������ ���� �����������, ���� ������ �������� ������
    {
        //printf("%c", buf);
        if(buf == '\n') //����� ������ ��������
        {
            len++;
            test = lseek(fd, 0L, 1); //�������, ������� ��� �� ������ �����
            lenght[counter] = len; //���� ������ ����� ������
            counter++; //��� �����, �.�. lines ����� ������ �� ��������� ������ ������������ lenght
            lines[counter] = test; //� ��� ���������� �� ������
            //printf("%d %d %d %d\n", counter, test, lines[counter], lenght[counter-1]); 
            len = 0; //�������� ������� �����
            continue; //��������� ����� ��������
        }
        len++; //��� �������
    }

    //printf("\n");

    int temp; //���� ����� ������������ ����� ������, ������� ����� ������� ������������
    while(1)
    {
        printf("Give me some line numbers: "); 
        int number = scanf("%d", &temp);

        if(number == 0 && (int)number > 199) //���� ����� ����, �� ����� �����������
        {
            printf("Error\n");
            close(fd);
            return -1;
        }
        if(lenght[number] == 0)
        {
            printf("There is no such string\n");
            close(fd);
            return -1;
        }
        
        lseek(fd, lines[number], 0); //���� ���������� ������ ������ �� ������ �����
        //printf("%d\n", test2);
        if(read(fd, text, lenght[number]))
        {
            write(1, text, lenght[number]);
        }
        else
        {
            printf("Error\n");
            close(fd);
            return -1;
        }
    }
    close(fd);
    return 0;


}
