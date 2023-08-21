/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanmpark <hanmpark@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 18:42:16 by hanmpark          #+#    #+#             */
/*   Updated: 2023/08/19 22:23:09 by hanmpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# define EXPORTED "declare -x "
# define NO_EQUAL_SIGN -1

# define ERR_EXPORT "minishell: export: `"
# define ERR_UNSET "minishell: unset: `"
# define ERR_EXIT "minishell: exit: "

# define NOT_VALID_ID "': not a valid identifier\n"
# define EXIT_ARGS "minishell: exit: too many arguments\n"
# define NUM_ARGS_REQ ": numeric argument required\n"

# define ERR_CWD "minishell: pwd: Current working directory does not exist\n"

/* IDENTIFIER FOR BUILTINS */

int		builtin_checker(char **cmd);
int		builtin_cmds(char **cmd, char ***envp, pid_t pid);

/* BUILTINS */

int		ft_echo(char **argv);
int		ft_cd(char **argv, char **envp);
int		ft_pwd(void);
int		ft_export(char **argv, char ***envp);
void	put_export(char **envp);
bool	check_env_var(char *var_name);
int		ft_env(char **envp);
int		ft_unset(char **argv, char ***envp);
int		ft_exit(pid_t process_id, char **argv);

#endif