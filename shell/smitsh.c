/*
Copyright (c) 2015, MrUNIXMan
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

* Redistributions of source code must retain the above copyright notice, this
  list of conditions and the following disclaimer.

* Redistributions in binary form must reproduce the above copyright notice,
  this list of conditions and the following disclaimer in the documentation
  and/or other materials provided with the distribution.

* Neither the name of FreeBSD-SMIT nor the names of its
  contributors may be used to endorse or promote products derived from
  this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
---------------------------------------------------------------------------------------
* 
* SMIT Shell Interpreter - This is the Internal Shell for Smit
* 
* This shell is based on the LSH which actually became a Toy Shell
* it does contain functions from the Toy Shell.
* 
* This is the main file for it.
* 
*/


#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include "includes/protos.h"
#include "includes/common.h"




/* Built in Stuff - Commands are found in seperate modules 
 * 
 * The commands in this section and one below must be in the same order
 * 
 * */



char *smitshell_builtin_cmd[] = {
	"dir",  		// DOS Style		1
	"directory", 	// VMS Style		2
	"set",			// Set Commands		3
	"show",			// Show Commands	4
	"help",			// Help				5
	"chdir",		// CD				6
	"cd",			// CD				7
	"ver",			// version			8
	"about", 		// About			9
	"exit"			// Exit				10
};


/* Must be in same order as smitshell_builtin_cmd */
int (*builtin_func[]) (char **) = {
	&SMITsh_directory,				//	1
	&SMITsh_directory,				//	2
	&SMITsh_set,					//	3
	&SMITsh_show,					//	4
	&SMITsh_help,					//	5
	&SMITsh_cd,						//	6
	&SMITsh_cd,						//	7
	&SMITsh_ver, 					//	8
	&SMITsh_about,					//  9
	&SMITsh_exit					//	10
};



	int smitshell_num_builtins() {
	return sizeof(smitshell_builtin_cmd) / sizeof(char *);
};


/* Builtin Implentations for Basic will be in 
 * basiccmds.c
 * 
 *  Help & Exit is only one that is in this module
 */
 
 /**
   @brief Builtin command: print help.
   @param args List of args.  Not examined.
   @return Always returns 1, to continue executing.
 */
int SMITsh_help(char **args)
 {
  int i;
  printf("SMIT's Own Shell\n");
  printf("Type program names and arguments, and hit enter.\n");
  printf("The following are internal commands:\n");

  for (i = 0; i < smitshell_num_builtins(); i++) {
    printf(" %s\n", smitshell_builtin_cmd[i]);
  }

  printf("\n");	
  return 1;
}

 
 
int SMITsh_exit(char **args)
{
	return 0;
}
 
 /* This will launch a program and wait for it to terminate.
  * Arguments will be supplied including program name.
  * All must send return 1 to keep the shell going.
  */
 
 
int SMITsh_launch(char **args)
{
		pid_t pid;
		
		int status;
		
		pid = fork();
		
		if(pid == 0)
		{
			/* Child Process */
			
			if(execvp(args[0], args) == -1)
			{
				/* Error Message comes out of Windows */
				fprintf(stderr, "%s: Not recongnized as an internal or external command,\n\t    operatable program or shell script\n\n", SHELL_NAME);
			}
			exit(EXIT_FAILURE);
		 } else if(pid <0)  {
			/* Error Forking */
			fprintf(stderr, "%s: Unable to Fork\n", SHELL_NAME);
		}else {
			// Parent Process
			do {
				waitpid(pid, &status,  WUNTRACED);
				} while (!WIFEXITED(status) && !WIFSIGNALED(status));
			}
		return 1;
	}
 

/* Shell Execute, this determines the Internal Commands then will
 * attempt to run any external commands if they exist by using the 
 * launch function. */
 
 
 int SMITsh_execute(char **args)
 {
	 int i;
	 
	 if(args[0] == NULL)
	 {
		 /* Empty Command returned */
		 return 1;
	 }
	 
	 /* Searches inside Internal command list above functions */
	 
	 for(i = 0 ; i < smitshell_num_builtins(); i++)
	 {
		 if(strcmp(args[0], smitshell_builtin_cmd[i]) == 0 )
		 {
			return(*builtin_func[i])(args);
		 }  // fi
	 } // for
 
	/* Execute External Command */
 
	return SMITsh_launch(args);
 }


#define SMIT_SHELL_RL_BUFFER_SIZE 1024


char *SMITShell_Read_Line(void)
{
	int BufSize = SMIT_SHELL_RL_BUFFER_SIZE;
	int Position = 0;
	int c;
	
	char *buffer = malloc(sizeof(char) * BufSize);

	if(!buffer) {
		fprintf(stderr, "%s: Unable to allocate\n", SHELL_NAME);
		exit(EXIT_FAILURE);
	}
	
	while(1)  // Read Charactors from Keyboard 
	{
		c = getchar();
		
		if(c == EOF)
		{
			exit(EXIT_SUCCESS);
		} 
		
		if(c == '\n')
		{
			buffer[Position] = '\0';
			return buffer;
		} else {
			buffer[Position] = c;
			
		} // Else
		Position++;
	
			
			
	/* If you exceed the sizes then this will need to be seen to
	 * by reallocating. */
	
	if(Position >= BufSize)
	{
		BufSize += SMIT_SHELL_RL_BUFFER_SIZE;
		buffer = realloc(buffer, BufSize);
		if(!buffer) {
			fprintf(stderr, "%s: Unable to allocate\n", SHELL_NAME);
			exit(EXIT_FAILURE);
		} //If !Buffer
	}  // If Position >= BufSize
	
  }  // While		
 	
	
}

#define SMIT_SHELL_TOKEN_BUFSIZE  64
#define SMIT_SHELL_TOKEN_DELIM " \t\r\n\a"

/* This one splits lines believed to be quite nieave with it */


char **SMITShell_Split_line(char *line)
{
	int BufSize = SMIT_SHELL_TOKEN_BUFSIZE, Position = 0;
	char **tokens = malloc(BufSize * sizeof(char*));
	char *token, **tokenbackup;
	
	if(!tokens) 
	{
		fprintf(stderr, "%s: Unable to allocate\n", SHELL_NAME);
		exit(EXIT_FAILURE);
	}
	
	
	token = strtok(line, SMIT_SHELL_TOKEN_DELIM);
	while(token != NULL)
	{
		tokens[Position] = token;
		Position++;
		
		if(Position >= BufSize)
		{
			BufSize +=  SMIT_SHELL_TOKEN_BUFSIZE;
			tokenbackup = tokens;
			tokens = realloc(tokens, BufSize * sizeof(char*));
			if(!tokens)
			{
				fprintf(stderr, "%s: Unable to allocate\n", SHELL_NAME);
				exit(EXIT_FAILURE);
			}
		}
	
		token = strtok(NULL, SMIT_SHELL_TOKEN_DELIM);
	}
	tokens[Position] = NULL;
	return tokens;
	
}


void SMITsh_loop(void)
{
	int status;
	char *line;
	char **args;
	
	do {
		printf("SMIT-Shell # ");
		line = SMITShell_Read_Line();
		args = SMITShell_Split_line(line);
		status = SMITsh_execute(args);
		
		
		free(args);
		free(line);
	} while (status);
	




}

int main()
{
	
	/* Run Own stuf here */
	printf("You are entering the SMIT's own shell\n Type  help for help. \n Type Exit to return to SMIT\n\n");
			
	
	
	SMITsh_loop();
	
	
	/* Clean Exir */
	return  EXIT_SUCCESS;
}
