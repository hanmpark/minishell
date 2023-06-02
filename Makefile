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
SRC_PATH = ./srcs/

SRC_MAN = ${addprefix ${SRC_PATH}, main.c} #TO BE COMPLETED

OBJ = ${SRC_MAN:.c=.o}

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
NAME = minishell #TO BE COMPLETED

all: ${NAME}

# pour la fonction readline, il faut inclure la librairie qu'on installe en utilisant la commmande 'brew install readline'
# -l specifie la bibliotheque, -L le chemin d'accès (du coup dans le repertoire brew)
${NAME}: ${OBJ}
	@${CC} ${CFLAGS} ${OBJ} -o ${NAME} -lreadline -L ~/.brew/opt/readline/lib
	@echo "\n\n\n\n   ${BOLD}${CUR}${LYELLOW}${NAME} COMPILED ✨${DEF}\n"

bonus:
	${MAKE}

debug:
	@${MAKE} DEBUG=1

clean:
	@rm -f ${OBJ}
	@echo "${ORANGE}${BOLD}\tCLEANING${DEF}"
	@echo "${LBLUE}${BOLD}${CUR} - Deleted object files${DEF}"

fclean: clean
	@rm -f ${NAME}
	@echo "${LBLUE}${BOLD}${CUR} - Deleted ${NAME}${DEF}"

re: fclean
	@${MAKE} all

.PHONY: all clean fclean re debug