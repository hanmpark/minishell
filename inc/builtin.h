#ifndef BUILTIN_H
# define BUILTIN_H

# define EXPORTED "declare -x "
# define INVALID_ID "not a valid identifier"
# define NO_EQUAL_SIGN -1

# define NOT_VALID_ID "': not a valid identifier\n"
# define ERR_EXPORT "minishell: export: `"
# define ERR_UNSET "minishell: unset: `"

/* IDENTIFIER FOR BUILTINS */

int		builtin_checker(char **cmd);
int		builtin_cmds(char **cmd, char ***envp);

/* BUILTINS */

int		ft_echo(char **argv);
int		ft_cd(char **argv, char **envp);
int		ft_pwd(void);
int		ft_export(char **argv, char ***envp);
void	put_export(char **envp);
bool	check_env_var(char *var_name);
int		ft_env(char **envp);
int		ft_unset(char **argv, char ***envp);
int		ft_exit(char **argv);

#endif