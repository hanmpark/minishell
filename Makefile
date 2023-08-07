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
SRC_EXPANDER = ${addprefix ${EXPANDER_PATH}, treat_env.c \
												expand_tools.c \
												expand_arg.c \
												compare_file.c \
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
												ft_export_utils.c}

EXIT_PATH = ${SRC_PATH}exit/
SRC_EXIT = ${addprefix ${EXIT_PATH}, free_structure.c \
										error.c}

SRC = ${SRC_PARSER} ${SRC_LEXER} ${SRC_EXPANDER} ${SRC_EXIT} ${SRC_EXEC} \
	${SRC_BUILTINS} ${SRC_DEBUG} ${SRC_REDIR} ${SRC_PATH}main.c ${SRC_PATH}handle_line.c

OBJ = ${SRC:.c=.o}

# --------------------------------- COMPILER --------------------------------- #
CC = gcc
CFLAGS = -Wall -Werror -Wextra

ifdef DEBUG
	CFLAGS += -fsanitize=address -g
endif

HEADER_PATH = ./inc/
SRC_COUNT = 0
SRC_TOT = ${shell find ${SRC_PATH} -type f -name '*.c' | wc -l}
SRC_PRCT = ${shell expr 100 \* ${SRC_COUNT} / ${SRC_TOT}}
BAR = ${shell expr 23 \* ${SRC_COUNT} / ${SRC_TOT}}

${SRC_PATH}%.o: ${SRC_PATH}%.c ${HEADER_PATH}
	@${eval SRC_COUNT = ${shell expr ${SRC_COUNT} + 1}}
	@${CC} ${CFLAGS} -I ${HEADER_PATH} -c $< -o ${<:.c=.o}
	@echo "\n ${BOLD}${CUR}${LPURPLE}-> Compiling ${DEF}${BOLD}${LYELLOW}[MINISHELL]${DEF}"
	@printf " ${LPURPLE}   [${LGREEN}%-23.${BAR}s${LPURPLE}] [%d/%d (%d%%)]${DEF}" "***********************" ${SRC_COUNT} ${SRC_TOT} ${SRC_PRCT}
	@echo "${UP}${UP}${UP}"

# ---------------------------------- RULES ----------------------------------- #
# pour la fonction readline, il faut inclure la librairie qu'on installe en utilisant
# la commmande: 'brew install readline'
# -l specifie la bibliotheque,
# -L le chemin d'accès (du coup dans le repertoire brew)


NAME = minishell

### Must MODIFY Makefile for the PC that doesn't have the library for readline function();
READ_LINE_PATH = ~/.brew/opt/readline/lib

LIBFT_PATH = ./lib/libft/

all: ${NAME}

${NAME}: ${OBJ}
	@echo "\n\n\n"
	@${MAKE} -C ${LIBFT_PATH}
	@${CC} ${CFLAGS} ${LIBFT_PATH}libft.a ${OBJ} -o ${NAME} -lreadline -L ${READ_LINE_PATH}
	@echo "\n\n\n\n   ${BOLD}${CUR}${LYELLOW}${NAME} COMPILED ✨${DEF}\n"

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

.PHONY: all clean fclean re debug