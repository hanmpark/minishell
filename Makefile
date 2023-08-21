# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hanmpark <hanmpark@student.42nice.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/15 20:04:15 by hanmpark          #+#    #+#              #
#    Updated: 2023/08/19 23:48:58 by hanmpark         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ---------------------------------- COLORS ---------------------------------- #
DEF = \033[0m
BOLD = \033[1m
CUR = \033[3m
UL = \033[4m
UP = \033[A

ORANGE = \033[38;5;216m
LBLUE = \033[38;5;153m
LYELLOW = \033[38;5;228m
LPURPLE = \033[38;5;189m
LGREEN = \033[38;5;155m

# ---------------------------- SOURCES / OBJECTS ----------------------------- #
SRC_PATH = ./src/

SRC_MAIN = ${addprefix ${SRC_PATH}, init_data.c \
									parsing.c \
									minishell.c}

DEBUG_PATH = ${SRC_PATH}debug/
SRC_DEBUG = ${addprefix ${DEBUG_PATH}, print_tokens.c \
										print_tree.c}

LEXER_PATH = ${SRC_PATH}lexer/
SRC_LEXER = ${addprefix ${LEXER_PATH}, tokenize.c \
										tokenize_string.c \
										is_type.c}

PARSER_PATH = ${SRC_PATH}parser/
SRC_PARSER = ${addprefix ${PARSER_PATH}, checker.c \
											get_table.c \
											get_cmd.c}

REDIR_PATH = ${SRC_PATH}redirection/
SRC_REDIR = ${addprefix ${REDIR_PATH}, file_descriptors.c \
										set_iostream.c \
										format_limiter.c \
										here_doc.c}

EXPANDER_PATH = ${SRC_PATH}expander/

ENV_PATH = ${EXPANDER_PATH}environment/
SRC_ENV = ${addprefix ${ENV_PATH}, expand_arg.c \
									expand_tools.c \
									treat_env.c}

WILDCARD_PATH = ${EXPANDER_PATH}wildcard/
SRC_WILDCARD = ${addprefix ${WILDCARD_PATH}, compare_file.c \
												match_files.c \
												asterix_globbing.c \
												init_entry_files.c}

EXEC_PATH = ${SRC_PATH}execution/
SRC_EXEC = ${addprefix ${EXEC_PATH}, execute.c \
										define_path.c \
										exec_cmd.c}

BUILTINS_PATH = ${SRC_PATH}builtins/
SRC_BUILTINS = ${addprefix ${BUILTINS_PATH}, builtin_checker.c \
												ft_cd.c \
												ft_echo.c \
												ft_pwd.c \
												ft_export.c \
												ft_export_utils.c \
												ft_env.c \
												ft_unset.c \
												ft_exit.c}

SIGNALS_PATH = ${SRC_PATH}signals/
SRC_SIGNALS = ${addprefix ${SIGNALS_PATH}, set_signals.c \
											basic_signals.c \
											command_signals.c \
											heredoc_signals.c \
											ignore_signals.c}

EXIT_PATH = ${SRC_PATH}exit/
SRC_EXIT = ${addprefix ${EXIT_PATH}, free_structure.c \
										error.c}

SRC = ${SRC_PARSER} ${SRC_LEXER} ${SRC_ENV} ${SRC_WILDCARD} ${SRC_EXIT} ${SRC_EXEC} \
	${SRC_BUILTINS} ${SRC_SIGNALS} ${SRC_DEBUG} ${SRC_REDIR} ${SRC_MAIN}

OBJ = ${SRC:.c=.o}

# --------------------------------- COMPILER --------------------------------- #
CC = clang
CFLAGS = -Wall -Werror -Wextra

ifdef DEBUG
	CFLAGS += -fsanitize=address -g
endif

# --------------------------------- CHECK OPERATING SYSTEM --------------------------------- #
OS := ${shell uname}

ifeq (${OS}, Linux)
	READLINE_LIB_PATH = /usr/lib/x86_64-linux-gnu
	READLINE_INC_PATH = /usr/include/readline/
else
	READLINE_LIB_PATH = ./vendor/readline/
	READLINE_INC_PATH = ./vendor/readline/include/
endif

CUR_INC = ./inc/
LIBFT_PATH = ./lib/libft/
READLINE_PATH = ./vendor/readline/
SRC_COUNT = 0
SRC_TOT = ${shell find ${SRC_PATH} -type f -name '*.c' | wc -l}
SRC_PRCT = ${shell expr 100 \* ${SRC_COUNT} / ${SRC_TOT}}
BAR = ${shell expr 23 \* ${SRC_COUNT} / ${SRC_TOT}}

${SRC_PATH}%.o: ${SRC_PATH}%.c
	@${eval SRC_COUNT = ${shell expr ${SRC_COUNT} + 1}}
	@${CC} ${CFLAGS} -I${CUR_INC} -I${LIBFT_PATH}inc/ -I${READLINE_INC_PATH} -c $< -o ${<:.c=.o}
	@echo "\n ${BOLD}${CUR}${LPURPLE}-> Compiling ${DEF}${BOLD}${LYELLOW}[MINISHELL]${DEF}"
	@printf " ${LPURPLE}   [${LGREEN}%-23.${BAR}s${LPURPLE}] [%d/%d (%d%%)]${DEF}" "***********************" ${SRC_COUNT} ${SRC_TOT} ${SRC_PRCT}
	@echo "${UP}${UP}${UP}"

# ---------------------------------- RULES ----------------------------------- #
NAME = minishell
LIBS = -L${READLINE_LIB_PATH}lib/ -lreadline -lhistory -L${LIBFT_PATH} -lft

all: os_check readline ${NAME}

os_check:
	@printf "\n\n    Compiling on: ${OS}\n\n"

${NAME}: ${OBJ}
	@echo "\n\n\n"
	@${MAKE} -C ${LIBFT_PATH}
	@${CC} ${CFLAGS} ${OBJ} ${LIBS} -o ${NAME}
	@echo "\n\n\n\n   ${BOLD}${CUR}${LYELLOW}${NAME} COMPILED ✨${DEF}\n"

readline: ${READLINE_PATH}

${READLINE_PATH}:
	sh ./install_readline.sh

bonus:
	${MAKE}

debug:
	@${MAKE} DEBUG=1

clean:
	@${MAKE} -C ${LIBFT_PATH} clean
	@rm -f ${OBJ}
	@echo "${ORANGE}${BOLD}\tCLEANING${DEF}"
	@echo "${LBLUE}${BOLD}${CUR} - Deleted object files${DEF}"

fclean: clean
	@rm -f ${NAME} ${LIBFT_PATH}libft.a
	@echo "${LBLUE}${BOLD}${CUR} - Deleted ${NAME}${DEF}"

re: fclean
	@${MAKE} all

.PHONY: all readline bonus debug clean fclean re os_check