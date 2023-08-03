#ifndef BUILTIN_H
# define BUILTIN_H

int	builtin_checker(char **cmd);
int	builtin_cmds(char **cmd, char **envp);

int	ft_echo(char **av);
int	ft_cd(char **av);
int	ft_pwd(void);

#endif