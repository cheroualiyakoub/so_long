NAME = so_long
CC = cc
CFLAGS = -Wall -Wextra -Werror -g
MLXFLAG = -framework Cocoa -framework OpenGL -framework IOKit
ODIR = ./odir/
SRCDIR = ./src/
LIBSFLD = ./Libs
MLXFLD = ./MLX42
LIBFTLFD = ./libft
LIBMLXH = ./Libs/MLX42/build/
LIBFT = ./Libs/libft/libft.a
GNLSRC = ./Libs/get_next_line/
SRCPATH = ./src/

SRC = 	${SRCPATH}main.c \
 		${SRCPATH}sl_parsing.c \
 		${SRCPATH}sl_init_config.c \
 		${SRCPATH}sl_check_map_utils.c \
 		${SRCPATH}sl_check_map_chars.c \
 		${SRCPATH}sl_check_collectibles.c \
 		${SRCPATH}sl_mlx_display_colls.c \
 		${SRCPATH}sl_clean_exit.c \
 		${SRCPATH}sl_mlx_game.c \
 		${SRCPATH}sl_mlx_put_imgs.c \
 		${SRCPATH}sl_mlx_movements.c \
 		${SRCPATH}sl_mlx_utilis.c \
 		${SRCPATH}sl_mlx_clean.c \
		${GNLSRC}get_next_line.c \
		${GNLSRC}get_next_line_utils.c

OBJ = $(SRC:$(SRCDIR)%.c=$(ODIR)%.o)

all : $(ODIR) $(NAME) 

$(NAME) : $(OBJ)
	@cd ${LIBSFLD}/${LIBFTLFD} && make && make bonus --silent
	@make -C ${LIBMLXH} --silent
	${CC} -Iinclude  $(CFLAGS) $(LIBFT) $(SRC)  -o $(NAME) ${LIBMLXH}libmlx42.a -lglfw 
	
$(ODIR)%.o: $(SRCDIR)%.c
	@mkdir -p $(ODIR)
	@$(CC) $(CFLAGS) -c $< -o $@ 

$(ODIR) :
	@mkdir -p $(ODIR)

clean :
	@cd ./${LIBSFLD}/${LIBFTLFD} && make clean -silent
	@rm -rf $(ODIR)
	@cd  ${LIBMLXH}  && make clean -silent

install :
	@cd ${LIBSFLD} && git clone https://github.com/codam-coding-college/MLX42.git ${MLXFLD}
	@cd ${LIBSFLD}/${MLXFLD} && cmake -B build && cmake --build build -j4

rebb : reb all

uninstall :
	@cd ${LIBSFLD} && rm -rf ${MLXFLD}

fclean : clean 
	@cd ./${LIBSFLD}/${LIBFTLFD} && make fclean -silent
	@rm -f $(NAME)
	@rm -rf ./so_long.dSYM
	@cd  ${LIBMLXH}  && make clean -silent

re : fclean all 

.PHONY: all clean fclean re leaks
