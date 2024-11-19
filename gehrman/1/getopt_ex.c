#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ulimit.h>
#include <sys/resource.h>
#include <string.h>

/*
-i �������� �������� � ����������� �������������� ������������ � ������.
-s ������� ���������� ������� ������. ���������: ������ setpgid(2)
-p �������� �������������� ��������, ��������-�������� � ������ ���������
-u �������� �������� ulimit
-Unew_ulimit �������� �������� ulimit. ���������: ������ atol(3C) �� �������� ����������� strtol(3C)
-c �������� ������ � ������ core-�����, ������� ����� ���� ������.
-Csize �������� ������ core-�����
-d �������� ������� ������� ����������
-v ������������� ���������� ����� � �� ��������
-Vname=value ������ ����� ���������� � ����� ��� �������� �������� ������������ ����������
*/

int main(int argc, char **argv, char **envp)
{
  int aflag = 0;
  int bflag = 0;
  char *cvalue = NULL;
  int index;
  int c;

  opterr = 0;

  while ((c = getopt(argc, argv, "ispucdvU:C:V:")) != -1)
  {
    switch (c)
    {
    case 'i':
    {
      // -i �������� �������� � ����������� �������������� ������������ � ������.
      printf("Real UID: %d\nEffective UID: %d\nReal GID: %d\nEffective GID: %d\n", getuid(), geteuid(), getgid(), getegid());
      break;
    }
    case 's':
    {
      // -s ������� ���������� ������� ������. ���������: ������ setpgid(2)
      setpgid(0, 0);
      // The first argument is the PID of the calling process (0 can be passed to refer to the calling process itself).
      // The second argument is also the PID of the calling process, which will make the process the leader of a new process group.
      break;
    }
    case 'p':
    {
      // -p �������� �������������� ��������, ��������-�������� � ������ ���������
      // getpid - get the process ID
      // getppid - get the parent process ID
      // getpgrp -- get the process group ID of the calling process
      printf("Process ID: %d\nParent PID: %d\nGroup PID: %d\n", getpid(), getppid(), getpgrp());
      break;
    }
    case 'u':
    {
      // -u �������� �������� ulimit. ulimit - get and set process limits
      printf("ulimit: %ld\n", ulimit(UL_GETFSIZE));
      break;
    }
    case 'U':
    {
      // -Unew_ulimit �������� �������� ulimit. ���������: ������ atol(3C) �� �������� ����������� strtol(3C)
      // atol(optarg)
      // rlim_t --�Unsigned integer type used for limit values
      // rlim_t limit;
      printf("new ulimit: %ld\n", ulimit(UL_SETFSIZE, atol(optarg)));
      // printf("Ulimit: %ld\n", ulimit(UL_GETFSIZE));
      break;
    }
    case 'c':
    {
      // -c �������� ������ � ������ core-�����, ������� ����� ���� ������.
      struct rlimit rlim;
      getrlimit(RLIMIT_CORE, &rlim);
      printf("Core file size: %llu\n", rlim.rlim_cur);
      break;
    }
    case 'C':
    {
      // -Csize �������� ������ core - �����
      struct rlimit rlim;
      rlim.rlim_cur = atol(optarg);
      setrlimit(RLIMIT_CORE, &rlim);
      printf("Core file size changed to: %llu\n", rlim.rlim_cur);
      break;
    }
    case 'd':
    {
      // -d �������� ������� ������� ����������
      char dir[2000];
      getcwd(dir, 2000);
      printf("%s\n", dir);
      break;
    }
    case 'v':
    {
      // -v ������������� ���������� ����� � �� ��������
      for (char **env = envp; *env != 0; env++)
      {
        char *thisEnv = *env;
        printf("%s\n", thisEnv);
      }
      // printf("%s\n", getenv("HOME"));
      break;
    }
    case 'V':
    {
      // -Vname=value ������ ����� ���������� � ����� ��� �������� �������� ������������ ����������
      setenv(optarg, strchr(optarg, '=') + 1, 1); // doesn't work
      break;
    }
    case '?':
    {
      if (isprint(optopt))
        fprintf(stderr, "Unknown option `-%c'.\n", optopt);
      return 1;
    }
    default:
      abort();
    }
  }

  for (index = optind; index < argc; index++)
    printf("Non-option argument %s\n", argv[index]);
  return 0;
}
