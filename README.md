Long before the famous bash, there was shell, and since it was hard to communicate with such a blasphemy `sorry Ken Thompson`, it was nicer to create another user-friendly interface with more and more implementations (i just care about the colors), anyway it our time to mimic a simpler version of bash. 

Minishell, nah, m calling it `mi/sh` is a simple UNIX command interpreter written in C as part of the 42 school curriculum. Imagine it as a language to make discussion with the shell more easier.


## Installation

Clone the repository and build using make:

```bash
https://github.com/iliassovic2003/simple-minishell.git
cd simple-minishell
```

To make the executable 
```bash
make                        (creates the executable)
make clean                 (clean the temporary files)
make fclean                 (cleans the whole process)
make re                    (recreating the executable)
```

# Usage
Run the executable to start the shell:

```bash
./minishell
```
### Example commands:

```bash

# Execute commands
mi/sh> ls -la
mi/sh> /bin/pwd

# Pipes and redirections
mi/sh> cat file.txt | grep "search" > output.txt
mi/sh> < input.txt wc -l

# Environment variables
mi/sh> echo $PATH
mi/sh> export MY_VAR=hello
mi/sh> echo $MY_VAR
mi/sh> unset $MY_VAR

# Built-in commands
mi/sh> cd ~/Documents
mi/sh> pwd
mi/sh> env
mi/sh> exit 42

```

# Features
- Basic command execution (absolute/relative paths and PATH lookup)

- Pipes (|) and redirections (>, >>, <, <<)

- Environment variables ($VAR) and special variables ($?)

- Signal handling (Ctrl-C, Ctrl-D, Ctrl-)

- Built-in commands: echo, cd, pwd, export, unset, env, exit

## Known Limitations
* 
* * * Here document (<<) doesn't ```expand``` variables
* * * * * Environment variable management is ```basic```
* * * Some edge cases in parsing may not be handled
*
###### (the editor is such a baby)
## Contributing
This is a school project with specific requirements, but suggestions and bug reports are welcome. Please open an issue to discuss any changes.

###### This project is part of the 42 school curriculum and follows their guidelines
