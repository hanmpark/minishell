#ifndef BUILTIN_H
# define BUILTIN_H

# define EXPORTED "declare -x "
# define INVALID_ID "not a valid identifier"

// Identifier for built-ins
int	builtin_checker(char **cmd);
int	builtin_cmds(char **cmd, char ***envp);

// Built-ins
int	ft_echo(char **av);
int	ft_cd(char **av);
int	ft_pwd(void);
int	ft_export(char **av, char ***envp);

#endif