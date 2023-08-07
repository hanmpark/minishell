#ifndef BUILTIN_H
# define BUILTIN_H

# define EXPORTED "declare -x "
# define INVALID_ID "not a valid identifier"
# define NO_EQUAL_SIGN -1

/* IDENTIFIER FOR BUILTINS */

int		builtin_checker(char **cmd);
int		builtin_cmds(char **cmd, char ***envp);

/* BUILTINS */

int		ft_echo(char **av);
int		ft_cd(char **av);
int		ft_pwd(void);
int		ft_export(char **av, char ***envp);
void	put_export(char **envp);
bool	check_env_var(char *var_name);

#endif