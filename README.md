# minishell
> A command-line interpreter that can execute basic shell commands and provide a shell-like environment.

> [!NOTE]
> Reference to bash 3.2 version

The goal of *minishell* is to create a program that allows users to interact with the operating system by executing commands and managing processes. It provides functionalities such as executing external commands, handling shell built-in commands, managing environment variables, and handling input/output redirection.

The *minishell* program reads commands from the user, parses them, and executes them using various system calls and functions. It handles basic shell features such as command execution, argument parsing, handling signals, and managing the environment.

## Implementation

### What our shell has to do
#### Mandatory part
- display a prompt waiting for commands
- have a functional history
- find and launch the correct executable (builtin, PATH, relative path, absolute path...)
- manage single/double quotes
- implement redirections (<. >, <<, >>)
- implement pipes
- manage environment variables ($)
- manage '$?'
- manage `ctrl-C`, `ctrl-D`, `ctrl-\`
#### Bonus part
- manage `&&` and `||`
- manage parentheses for priorities purpose only (no subshells)
- the asterix wildcard `*` (only has to work in the current repository)

#### implement builtins
- `echo` and its option `-n`
- `cd` only with relative or absolute path
- `pwd` without any option
- `export` without any option
- `unset` without any option
- `env` without any option/argument
- `exit` without any option

### What our shell does not manage
> [!WARNING]
> - unclosed quotation marks or special characters that are not requested in the subject line, such as `\` (backslash) or `;` (semicolon)
> - anything else that was not mentioned above

## Global structure (Abstract Syntax Tree)
> "Binary trees sounds cool" - me

![code_struct](https://github.com/hanmpark/minishell/blob/main/minishell_glob_struct.png)

## Usage

First compile the program
```bash
$> make
```
Execute the minishell
```bash
$> ./minishell
```
To see how the minishell is tokenizing the command line and see what the tree looks like you can execute it like so:
```bash
$> ./minishell debug
```
#### usage example:
```bash
minishell$ echo 1 | cat -e || (echo 2 && echo 3) || echo 4 

TOKENS:
[0] token = [echo] type = WORD
[1] token = [1] type = WORD
[2] token = [|] type = PIPE
[3] token = [cat] type = WORD
[4] token = [-e] type = WORD
[5] token = [||] type = OR_IF
[6] token = [(] type = LPAR
[7] token = [echo] type = WORD
[8] token = [2] type = WORD
[9] token = [&&] type = AND_IF
[10] token = [echo] type = WORD
[11] token = [3] type = WORD
[12] token = [)] type = RPAR
[13] token = [||] type = OR_IF
[14] token = [echo] type = WORD
[15] token = [4] type = WORD

TREE:
command = [echo] [1] 
fdin = 0
fdout = 1
----- PIPE -----
command = [cat] [-e] 
fdin = 0
fdout = 1
left
        command = [echo] [2] 
        fdin = 0
        fdout = 1
        left
                command = [echo] [4] 
                fdin = 0
                fdout = 1
                left
                        ---<empty>---
                right
                        ---<empty>---
                done
        right
                command = [echo] [3] 
                fdin = 0
                fdout = 1
                left
                        command = [echo] [4] 
                        fdin = 0
                        fdout = 1
                        left
                                ---<empty>---
                        right
                                ---<empty>---
                        done
                right
                        ---<empty>---
                done
        done
right
        ---<empty>---
done

COMMAND OUTPUT:
1$
minishell$ 
```
