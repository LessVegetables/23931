#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <signal.h>
#include <ctype.h>

void timer(int var)
{
    int fd = open("test.txt", O_RDONLY);
    char buf;
    printf("\n");
    printf("Haha, too late! You can restart the program and try again. Meanwhile, here is strings from file, enjoy it:\n");
    while(read(fd, &buf, 1)) //������ ���� �����������, ���� ������ �������� ������
    {
        printf("%c", buf);
    }
    close(fd);
    //printf("Haha\n");
    exit(0);
}

int main()
{
    int fd = open("test.txt", O_RDONLY); //��������� ���� �� ������
    if (fd == -1)
    {
        close(fd);
        printf("Your file was open incorrectly. Pls, stop breaking my programm...\n");
        exit(0);
    }
    int lines[200]; //��� ������ ������ �����
    int lenght[200]; //� ��� ����� ����� �� �������
    lines[1] = 0L; //���������� ������ ������ ������
    int counter = 1; //��� �ޣ����, ������������� ����� ������
    int len = 0; //����� ������ ����� ������ �ģ� ����
    char buf, text[1024]; //buf ������ ������� �� �����, � text ����� ������������ �������� ������
    while(read(fd, &buf, 1)) //������ ���� �����������, ���� ������ �������� ������
    {
        //printf("%c", buf);
        if(buf == '\n') //����� ������ ��������
        {
            len++;
            int test = lseek(fd, 0L, 1); //�������, ������� ��� �� ������ �����
            lenght[counter] = len; //���� ������ ����� ������
            counter++; //��� �����, �.�. lines ����� ������ �� ��������� ������ ������������ lenght
            lines[counter] = test; //� ��� ���������� �� ������
            //printf("%d %d\n", test, lines[counter]); 
            len = 0; //�������� ������� �����
            continue; //��������� ����� ��������
        }
        len++; //��� �������
    }

    //printf("\n");

    int temp; //���� ����� ������������ ����� ������, ������� ����� ������� ������������
    signal(SIGALRM, timer);
    
    while(1)
    {
        alarm(5);
        printf("Give me some line numbers: "); 
        int number = scanf("%d", &temp);
        if(number == 0) //���� ����� ����, �� ����� �����������
        {
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
        counter = lenght[number];
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
