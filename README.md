# minishell
Implementation of simple shell (bash).

- Search and launch the right executable (based on the PATH variable or by using
relative or absolute path)
- Implemented builtins: 
    - `echo` (with option `-n`) 
    - `cd` (with only a relative or absolute path)
    - `pwd` (with no options)
    - `export` (with no options)
    - `unset` (with no options)
    - `env` (with no options or arguments)
    - `exit` (with no options)
- Redirections `<` `>` `<<` `>>`
- Pipes `|` The output of each command in the pipeline is connected via a pipe to the
input of the next command.
- Environment variables (`$` followed by characters)
- `ctrl-C` `ctrl-D` `ctrl-\` work like in bash.
- Working history
