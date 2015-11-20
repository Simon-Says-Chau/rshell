#include <iostream>
#include <string>
#include <cstdlib>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <stdio.h>
#include <unistd.h>

using namespace std;

#define delimiter " \r\t\n\""

int main()
{
	struct stat temp;
	char line[100];
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
				line[x] = '\0';
			}
		}

		//Check line if exit
		cmd = strtok(line, delimiter);
		if(line[0] == '\0')
		{
			continue;
		}

		else if(strcmp(cmd, "exit") == 0)
		{
			exit(1);
		}

		//Checks for flags with key word test or []
		else if((strcmp(cmd, "test") == 0) || (strcmp(cmd, "[")) == 0)
		{
			cmd = strtok(NULL,delimiter);
			if(strcmp(cmd, "-d") == 0)
			{
				cmd = strtok(NULL,delimiter);
				if(stat(cmd,&temp) == 0 && S_ISDIR(temp.st_mode))
				{
					cout << "Directory exists and is a directory." << endl;
				}

				else
				{
					cout << "Directory does not exist or not a directory." << endl;
				}
			}

			else if(strcmp(cmd, "-f") == 0)
			{
				cmd = strtok(NULL,delimiter);
				if(stat(cmd,&temp) == 0 && S_ISREG(temp.st_mode))
				{
					cout << "File exists and is a file." << endl;
				}

				else
				{
					cout << "File does not exist or not a file." << endl;
				}
			}

			else if(strcmp(cmd, "-e") == 0)
			{
				cmd = strtok(NULL,delimiter);
				if((stat(cmd,&temp) == 0 && S_ISREG(temp.st_mode)) || (stat(cmd,&temp) == 0 && S_ISDIR(temp.st_mode)))
				{
					cout << "File/Directory exists." << endl;
				}

				else
				{
					cout << "File/Directory does not exist." << endl;
				}
			}
			
			else
			{
				if((stat(cmd,&temp) == 0 && S_ISREG(temp.st_mode)) || (stat(cmd,&temp) == 0 && S_ISDIR(temp.st_mode)))
				{
					cout << "File/Directory exists." << endl;
				}

				else
				{
					cout << "File/Directory does not exist." << endl;
				}
			}
		}


		//Execute command if not any of the other commands
		else
		{
			int num = fork();
			if(num == 0)
			{
				char* arg_1[100];
				arg_1[0] = new char[50];
				strcpy(arg_1[0],cmd);
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
