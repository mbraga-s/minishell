# Minishell

The minishell project requires students to build their own smaller version of shell following the established guidelines and requirements. It is the first project of the 42 cursus that is developed with another student. To make this project happen, I and Manuel ([manumart](https://github.com/manuelm-git) - check out his github as well) paired up and put our skills to the test.

**This project and Readme are still in development - everything here is subject to change so take what you see here '*with a grain of salt*'.**

## Index
I. [Usage](#usage)

II.[Features](#features)

III. [Structure](#structure)

## Usage
>In development
## Features
>In development
### Built-in Functions
>In development
## Structure
<div  align="center"> <strong>
INPUT → LEXER → PARSER → EXPANDER → REDIRECTIONS →  EXECUTOR
</strong>

### Lexer
The lexer's function is to tokenize the received input. It does this by separating the operators from any words — adding a *space* before and after each operator. Afterwards, it procceds to split each word into tokens, respecting inverted commas.

`ls -l|"grep a">outfile` → `ls -l | "grep a" > outfile` →`ls` `-l` `|` `"grep a"` `>` `outfile`

### Parser
>In development
### Expander
>In development
### Redirections
>In development
### Executor
>In development
