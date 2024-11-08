# Minishell

<img src="https://raw.githubusercontent.com/mbraga-s/42-project-badges/main/covers/cover-minishell.png" alt="Minishell">

The minishell project requires students to build their own simple shell (using bash as reference) following the established guidelines and requirements. It is the first project of the 42 cursus that is developed with another student. To make this project happen, Manuel and I paired up and put our skills to the test.

The bulk of the work was divided as follows:
>[Miguel](https://github.com/mbraga-s):
>
>Parsing, Expansions, Redirections, Execution and Signal Handling
>
>[Manuel](https://github.com/manuelm-git):
>
>Built-ins, Environment Variables and Signal Handling


**This Readme is still in development - everything here is subject to change so take what you see here '*with a grain of salt*'.**
  
## Intro

I.	Usage
```
> make
> ./minishell
```
  

II.	Features

 - Working here-doc
 - Infile / outfile redirections + appending
 - Built-in functions (echo, cd, export, unset, env, exit, pwd)
 - Command execution with several pipes
 - Basic signal handling
 - Expandible arguments

## Structure

<div  align="center">  <strong>

INPUT → LEXER → SYNTAX CHECKER → PARSER → EXPANDER → REDIRECTIONS → EXECUTOR

</strong>  </div>

In this *README*, we'll look into the following example to illustrate how the input is handled throughout our minishell.

<div  align="center">

`<infile cat|grep "else if" | wc -l >>$USER$NOEXIST.txt`

</div>

### Lexer

The lexer's function is to tokenize the received input. It does this by separating the operators from any words — adding a *space* before and after each operator ( | , < , >, <<, >>) . Afterwards, it procceds to split each word into tokens, respecting single ( ' ) and double ( " ) quotes.

<div  align="center">

`<infile cat|grep "else if" | wc -l >>$USER$NOEXIST.txt` → ` < infile cat | grep "else if"  |  wc -l  >> $USER$NOEXIST.txt` → `<` `infile` `cat` `|` `grep` `"else if"` `|` `wc` `-l` `>>` `$USER$NOEXIST.txt`

</div>

For easier understanding in the following segments, we'll classify these tokens as **pipe**, **redirection** and **word tokens** depending on their content.

### Syntax Checker

After the input has been tokenized,  it needs to be checked in order to validate that it can be interpreted by minishell. In order for an input to be considered valid, it must follow these rules:

 - The input cannot start with a **pipe token**;
 - After any **redirection token**, there must be a **word token**;
 - **Pipe tokens** in a row are not allowed;
 - The input cannot end with a **pipe** or **redirection token**;

If these rules are followed, the tokens are sent to the parser. Otherwise, an appropriate error message is displayed, and the program exits.

### Parser

The parser assigns the tokens provided by the lexer (and checked by the syntax checker) to their respective place in a struct called **data** so, later on, it can be interpreted by the executor. These structs form a linked list, with each node of the list representing a command.

```
    struct data
    {
    	char		**args;		// array of strings for the command and arguments
    	int		fd[2];		// file descriptors of a pipe (assigned later)
    	char		**infile;	// array of strings for each file to be read from, stored in order
    	char		**inflag;	// array using "0" and "1" as flags depending of the type of infile
    	char		**outfile;	// same as infile but for files to write to
    	char		**outflag;	// same as inflag but for the outfiles
    	int		fd_in;		// for the fd of an infile to be stored
    	int		fd_out;		// for the fd of an outfile to be stored
    	int		pid;		// for the pid of the fork to be stored
    	struct s_data	*next;		// pointer to the next node of the list
    	struct s_data	*prev;		// pointer to the previous node of the list
    }	
```

Tokens are assigned following these rules:
 1. if an **operator token** is found and it is a redirection (<, >, << or >>), the following token is added to the corresponding *infile* or *outfile* array and a "flag string" is added to the *inflag* or *outflag* array — 0 if it's a simple redirection, 1 if it's n here-doc or append.
 2. if a **word token** is found, it is added to the *args* array — where the first string of that array will be the command name and all others will be the command arguments.
 3. if an **operator token** is found and it is a pipe ( | ) a new node is created, and the *next* and *prev* pointers are set accordingly.

```
data1							data2							data3
{							{							{
	char		**args = [cat]				char		**args = [grep, "else if"]		char		**args = [wc, -l]
	int		fd[2] = [0 , 1]				int		fd[2] = [0 , 1]				int		fd[2] = [0 , 1]
	char		**infile = [infile]			char		**infile = NULL				char		**infile = NULL
	char		**inflag = [0]				char		**inflag = NULL				char		**inflag = NULL
	char		**outfile = NULL			char		**outfile = NULL			char		**outfile = [$USER$NOEXIST.txt]
	char		**outflag = NULL			char		**outflag = [1]				char		**outflag = [1]
	int		fd_in = 0				int		fd_in = 0				int		fd_in = 0
	int		fd_out = 1				int		fd_out = 1				int		fd_out = 1
	int		pid = 0					int		pid = 0					int		pid = 0
	struct s_data	*next = &data2				struct s_data	*next = &data3				struct s_data	*next = NULL
	struct s_data	*prev = NULL				struct s_data	*prev = &data1				struct s_data	*prev = &data2
}							}							}
```

### Expander

After the linked list is constructed, each string in the *args* array of each node, as well as in the *infile* and *outfile* arrays,  is checked for single or double quotations and for expandable arguments — arguments starting with a *$* that are not in between single quotes.

Any quoted string has its quotes removed, and if an expandable argument is found, it's checked against the environment variables. If it's found, the expandable argument is replaced with the value of the variable. If it isn't found, then it's removed (from the string if it's in one, or from the array if the expandable argument is the string).

```
data1							data2							data3
{							{							{
	char		**args = [cat]				char		**args = [grep, "else if"]		char		**args = [wc, -l]
	int		fd[2] = [0 , 1]				int		fd[2] = [0 , 1]				int		fd[2] = [0 , 1]
	char		**infile = [infile]			char		**infile = NULL				char		**infile = NULL
	char		**inflag = [0]				char		**inflag = NULL				char		**inflag = NULL
	char		**outfile = NULL			char		**outfile = NULL			char		**outfile = [mbraga-s.txt]
	char		**outflag = NULL			char		**outflag = [1]				char		**outflag = [1]
	int		fd_in = 0				int		fd_in = 0				int		fd_in = 0
	int		fd_out = 1				int		fd_out = 1				int		fd_out = 1
	int		pid = 0					int		pid = 0					int		pid = 0
	struct s_data	*next = &data2				struct s_data	*next = &data3				struct s_data	*next = NULL
	struct s_data	*prev = NULL				struct s_data	*prev = &data1				struct s_data	*prev = &data2
}							}							}
```
### Redirections
>In development
### Executor
The executor starts by seeing if the *data* list has more than one node. If it has, it opens a pipe (saving the corresponding file descriptors in *fd[2]* and runs the rest of the executor - which is explained further. If not, no pipes need to be opened, and the first string of the *args* array is checked for a built-in command. 
In case a built-in command is found, the corresponding built-in function is called and the executor ends. Otherwise, or if there is a pipe, the executor calls the **execute_forks** function:

```
void	execute_forks(t_data *data)
{
	data->pid = fork(); //Creates the first fork and runs the corresponding command
	if (data->pid == 0)
		first_fork(data, msdata()->envp);
	data = data->next; //Moves to the next node of the list
	while (data && data->next) //Runs a loop creating forks, and pipes as long as there is a next node.
	{
		pipe_protect(data);
		data->pid = fork();
		if (data->pid == 0)
			mid_fork(data, msdata()->envp);
		close_fd(data->prev->fd);
		data = data->next;
	}
	if (data) //Creates the last fork of the list
	{
		data->pid = fork();
		if (data->pid == 0)
			last_fork(data, msdata()->envp);
		close_fd(data->prev->fd);
	}
}
```
This simple function allows all pipes/forks to be handled correctly, making sure that there are never more than 2 pipes open in our main process - which allows for a clean handling of file descriptors. 
It also makes sure that all forks are running simultaneously and that no nasty things (such as waiting for a process/fork to end before running the next one) happen.

Each fork creation saves its process id (*pid*) on the corresponding node, allowing us to wait for all processes and to catch their exit codes.
