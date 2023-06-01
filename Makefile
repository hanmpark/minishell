# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hanmpark <hanmpark@student.42nice.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/01 14:08:12 by hanmpark          #+#    #+#              #
#    Updated: 2023/06/01 14:14:06 by hanmpark         ###   ########.fr        #
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

SRC_MAN_PATH = ${SRC_PATH}mandatory/
SRC_MAN = ${addprefix ${SRC_MAN_PATH}, ...} #TO BE COMPLETED

SRC_BONUS_PATH = ${SRC_PATH}bonus/
SRC_BONUS = ${addprefix ${SRC_BONUS_PATH}, ...} #TO BE COMPLETED

OBJ_MAN = ${SRC_MAN:.c=.o}

OBJ_BONUS = ${SRC_BONUS:.c=.o}

# --------------------------------- COMPILER --------------------------------- #
CC = gcc
CFLAGS = -Wall -Werror -Wextra

ifdef DEBUG
	CFLAGS += -fsanitize=address -g
endif

HEADER_MAN_PATH = ./inc/
SRC_MAN_COUNT = 0
SRC_MAN_TOT = ${shell find ${SRC_MAN_PATH} -type f -name '*.c' | wc -l}
SRC_MAN_PRCT = ${shell expr 100 \* ${SRC_MAN_COUNT} / ${SRC_MAN_TOT}}
BAR_MAN = ${shell expr 23 \* ${SRC_MAN_COUNT} / ${SRC_MAN_TOT}}

${SRC_MAN_PATH}%.o: ${SRC_MAN_PATH}%.c ${HEADER_MAN_PATH}
	@${eval SRC_MAN_COUNT = ${shell expr ${SRC_MAN_COUNT} + 1}}
	@${CC} ${CFLAGS} -I ${HEADER_MAN_PATH} -c $< -o ${<:.c=.o}
	@echo "\n ${BOLD}${CUR}${LPURPLE}-> Compiling ${DEF}${BOLD}${LYELLOW}[MINISHELL]${DEF}"
	@printf " ${LPURPLE}   [${LGREEN}%-23.${BAR_MAN}s${LPURPLE}] [%d/%d (%d%%)]${DEF}" "***********************" ${SRC_COUNT} ${SRC_MAN_TOT} ${SRC_MAN_PRCT}
	@echo "${UP}${UP}${UP}"

HEADER_BONUS_PATH = ./inc/
SRC_BONUS_COUNT = 0
SRC_BONUS_TOT = ${shell find ${SRC_BONUS_PATH} -type f -name '*.c' | wc -l}
SRC_BONUS_PRCT = ${shell expr 100 \* ${SRC_BONUS_COUNT} / ${SRC_BONUS_TOT}}
BAR_BONUS = ${shell expr 23 \* ${SRC_BONUS_COUNT} / ${SRC_BONUS_TOT}}

${SRC_BONUS_PATH}%.o: ${SRC_BONUS_PATH}%.c ${HEADER_BONUS_PATH}
	@${eval SRC_COUNT = ${shell expr ${SRC_COUNT} + 1}}
	@${CC} ${CFLAGS} -I ${HEADER_BONUS_PATH} -c $< -o ${<:.c=.o}
	@echo "\n ${BOLD}${CUR}${LPURPLE}-> Compiling ${DEF}${BOLD}${LYELLOW}[MINISHELL (BONUS)]${DEF}"
	@printf " ${LPURPLE}   [${LGREEN}%-23.${BAR_BONUS}s${LPURPLE}] [%d/%d (%d%%)]${DEF}" "***********************" ${SRC_BONUS_COUNT} ${SRC_BONUS_TOT} ${SRC_BONUS_PRCT}
	@echo "${UP}${UP}${UP}"

# ---------------------------------- RULES ----------------------------------- #
NAME = #TO BE COMPLETED

all: ${NAME}

${NAME}: ${OBJ}
	@${CC} ${CFLAGS} ${OBJ} -o ${NAME}
	@echo "\n\n\n\n   ${BOLD}${CUR}${LYELLOW}${NAME} COMPILED ✨${DEF}\n"

bonus:
	${MAKE} BONUS_OK=1

debug:
	@${MAKE} DEBUG=1

clean:
	@rm -f ${OBJ_MAN} ${OBJ_BONUS}
	@echo "${ORANGE}${BOLD}\tCLEANING${DEF}"
	@echo "${LBLUE}${BOLD}${CUR} - Deleted object files${DEF}"

fclean: clean
	@rm -f ${NAME}
	@echo "${LBLUE}${BOLD}${CUR} - Deleted ${NAME}${DEF}"

re: fclean
	@${MAKE} all

.PHONY: all clean fclean re debug