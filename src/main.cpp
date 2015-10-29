#include <iostream>
#include <string>
#include <cstdlib>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <errno.h>
#include <stdio.h>
#include <unistd.h>


using namespace std;

#define delimiter " \r\t\n\""

int main()
{
	char line[100];
	char temp[100];
	char user_name[256];
	char host_name[256];
	char *cmd = NULL;

	while(1)
	{
		getlogin_r(user_name, sizeof(user_name)-1);
		gethostname(host_name, sizeof(host_name)-1);
		
		cout << "[" << user_name << "@" << host_name << " ~]$ ";
        
		//Get user inputs
		cin.getline(line,100);	
		
		for(unsigned x = 0; x < 100; x++)
		{
			if(line[x] == '#')
			{
				line[x] = NULL;
			}
		}

		//Check line if exit
		cmd = strtok(line, delimiter);
		if(line[0] == '\0')
		{
			continue;
		}

		if(strcmp(cmd, "exit") == 0)
		{
			exit(1);
		}

		//Execute command if not exit
		else
		{
			int num = fork();
			if(num == 0)
			{
				char* arg_1[100];
				arg_1[0] = new char[50];
				strcpy(arg_1[0],ccmd = strtok(NULL,delimiter);
				cmd = strtok(NULL,delimiter);
				unsigned int i = 0;

				while(cmd != NULL)
				{
					arg_1[i+1] = new char[50];
					strcpy(arg_1[i+1],cmd);
					cmd = strtok(NULL,delimiter);
					i++;
				}

				arg_1[i+1] = NULL;
				int pid = execvp(arg_1[0],arg_1);

				if(pid == -1)
				{
					perror("execvp failed");
				}

				exit(1);
			}

			else if(num == -1)
			{
				perror("fork failed");
				exit(1);
			}

			else
			{
				wait(NULL);
			}
		}
	}

	return 0;
}
