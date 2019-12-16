# Shell
# by Amanda Zheng and Joseph Lee

### Features

#### Basic Features:

######  -Reads and parses multiple commands separated by ;
######  -executes basic commands of execvp
######  -exiting shell (type in exit)
######  -cd into different directories
######  -simple redirection of > and <
######  -simple pipes (use of one pipe)

#### Additional Features we successfully implemented:

######  -Added Color (USE BLACK BACKGROUND TO SEE THE COLORS) to shell
######  -Can put additional spaces before, after and even in the middle of flagged commands (e.g. "ls   -a")
######  -Error handling/Simulating Bash Behavior (Handling Ctrl+c, Enter Key)
######  - >> redirection works
######  -Two simple redirection together works :  xxx > yyy < zzz and xxx< yyy >zzz
######  -infinite piping works

#### Additional Features we tried to implement:
- Up/Down Arrow
- Moving Cursor sideways
- "cd;"
- ~
- alias
- Doing piping and redirect (e.g. ls | wc > inputfile)
#### Persisting Bugs in our program:

#### Files and headers for all functions:

##### shell.c Has functions dealing with directory, cd, and executing commands
	/*======== void executing(char ** command, int * keepRunning) ==========
	Inputs:  char ** command, int * keepRunning
	Returns: N/A
	Executes command given by command and prints command not found if invalid command
	If command is to exit, turn keeprunning to 0 (false)
	====================*/
	
		 /*======== void set_color(unsigned char color) ==========
	Inputs:  char * args, char * sign
	Returns: N/A
	changes color of text to the one dictated by unsigned char color
	====================*/

	/*======== int isChangeDirectory(char ** command) ==========
	Inputs:  char ** command
	Returns: 1 if the command is cd, 0 otherwise
	Checks if the first element of the command list is "cd"
	====================*/

	/*======== void changeDirectory(char ** command) ==========
	Inputs:  char ** command
	Returns: N/A
	Uses chdir to change change directory
	Uses lengthArgs(command) and chdir's return value to return appropriate error messages
	====================*/
##### parse.c Has functions dealing with parsing arguments/inputs
	/*======== int lengthArgs(char ** command) ==========
	Inputs:  char ** command
	Returns: Number of Char * in command
	Counts number of elements in command
	While the element in command is not null
	add one to the length
	Once it exits loop return the length
	====================*/
	
	/*======== char ** parseMulti(char * args,char * sign) ==========
	Inputs:  char * args, char * sign
	Returns: returns a list of strings that are split from args based on sign
	Keep on strseping untill the token is null and also strip each element of trailing white spaces. If the length of the element is 0, set the slot to Null, and don't advance the loop.
	====================*/
	
	  /*======== char * strip(char * args, char sign) ==========
	Inputs:  char * args, char * sign
	Returns: returns a string without leading leading character sign
	Moves down the characters of the array until the first character is not sign
	====================*/

  	  /*======== char * truncs(char * args, char sign) ==========
	Inputs:  char * args, char * sign
	Returns: returns a string without trailing character sign
	Adds terminating string character while looping from the back of the string if the character equals sign
	====================*/
	
##### pipe.c Has functions dealing with piping

	/*======== int isPipe(char * command) ==========
	Inputs:  char * command
	Returns: 1 if the command is an only | command, 0 otherwise
	Loops through the command in search of a |
	If an | exists, parse the string by | using parseMulti
	If the command has multiple |s, parse all commands except the last one into one command
	Pass the commands into performPipe
	====================*/

	/*======== void performPipe(char * command1, char * command2); ==========
	Inputs:  char * command1, char * command2
	Returns: N/A
	Uses popen() to open the first command in reading mode
	Use popen to open the second command in writing mode
	Use fgets to read the first command's file output and write it in as the second command's input 
	====================*/

##### redirect.c Has functions dealing with redirect
	 /*======== void simpleRedirect(char * args,char sign) ==========
	Inputs:  char * args, char * sign
	Returns: N/A
	Create a file to write, truncate, and create and write to stdout if sign is > and then execute the command in args
	Create a file to read into stdin if the sign is < and execute the command in args
	====================*/

	 /*======== void complexRedirect(char * args,char sign) ==========
	Inputs:  char * args, char * sign
	Returns: N/A
	Create a file to write, append, and create and write to stdout if sign is > and then execute the command in args
	====================*/

  	 /*======== void transitiveRedirect(char * args, char sign) ==========
	Inputs:  char * args, char * sign
	Returns: N/A
	Create a file to write, truncate, and creat and write to stdout and read from stdin if firstsign is > and then execute the command in args
	Create a file to write, truncate, and creat and write to stdout and read from stdin and to determine which one to read from and which one to read to depends on firstsign and then execute the command in args
	====================*/

  	 /*======== hybridRedirect(char * args, char sign) ==========
	Inputs:  char * args, char * sign
	Returns: N/A
	Create a file to write, truncate, and creat and write to stdout if sign is > and then perform the piping in args
	====================*/

	   /*======== int isRedirect(char * args) ==========
	Inputs:  char * args
	Returns: 1 if there was sometype of redirection in the command or 0 if there was none
	Depending on what signs are in args (e.g. >, <, >>...), it calls on the appropriate function to execute the correct redirection
	====================*/
	
	 /*======== int isRedirect(char * args) ==========
	Inputs:  char * args
	Returns: 1 if there was sometype of redirection in the command or 0 if there was none
	Depending on what signs are in args (e.g. >, <, >>...), it calls on the appropriate function to execute the correct redirection
	====================*/
	
	 /*======== void saveRedirect(int* redirects) ==========
	Inputs: int* redirects
	Returns: N/A
	Saves STDIN_FILENO,STDOUT_FILENO,STDERR_FILENO to restore file stream later
	====================*/
	
	 /*======== void restoreRedirect(int* redirects) ==========
	Inputs: int* redirects
	Returns: N/A
	restore STDIN_FILENO,STDOUT_FILENO,STDERR_FILENO file stream
	====================*/
