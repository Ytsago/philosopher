# -----------RULES-----------#

CFLAGS = -Wall -Wextra -Werror -MMD -MP -g3
CC = cc
AR = ar
ARFLAG = -rcs

# -----------PATHS-----------#

SRCDIR = src/

UTIDIR = $(SRCDIR)utils/
ROUTDIR = $(SRCDIR)routine/

# UTILS SUBDIRECTORIES #
UPARSDIR = $(UTIDIR)parsing/
UALLOCDIR = $(UTIDIR)alloc/
UTHDIR = $(UTIDIR)thread/

INCDIR = inc/
LIBDIR =
OBJDIR = .Obj/

# -----------FILES-----------#

MAIN =		main.c

UTILS =

PUTIL =		parsing_utils.c	

ALUTIL =	bt_malloc.c			bt_free.c

THUTIL =	thread_helpers.c	param_init.c	check_philo.c

ROUT =		routine.c			action.c 		fork.c			monitoring.c

INC =		bt_malloc.h 		philo_funct.h	philo_struc.h	philosopher.h	color.h

# -----------SRCS-----------#



SRCS =	$(addprefix $(SRCDIR), $(MAIN)) \
		$(addprefix $(UTIDIR), $(UTILS)) \
		$(addprefix $(UPARSDIR), $(PUTIL)) \
		$(addprefix $(ROUTDIR), $(ROUT)) \
		$(addprefix $(UALLOCDIR), $(ALUTIL)) \
		$(addprefix $(UTHDIR), $(THUTIL)) \


# -----------OTHER-----------#

OBJS =	$(patsubst $(SRCDIR)%.c, $(OBJDIR)%.o, $(SRCS))

DEPS =	$(OBJS:.o=.d)

HEADER = $(addprefix $(INCDIR), $(INC))

LIBS =	

NAME =	philo

# -----------RULES-----------#

all: $(NAME) Makefile

$(NAME): $(LIBS) $(OBJS)
	$(CC) $(CFLAG) $(OBJS) -o $(NAME) $(LIBS)

$(OBJDIR)%.o: $(SRCDIR)%.c | $(OBJDIR)
	$(CC) $(CFLAGS) -I $(INCDIR) $(if $(LIBS),-I $(LIBDIR)$(INCDIR)) -c $< -o $@ 

$(OBJDIR):
	mkdir -p $(OBJDIR) $(dir $(OBJS))

$(LIBS): FORCE
	@$(MAKE) -C $(LIBDIR) --no-print-directory

# -----------UTILS-----------#

clean:
	rm -rf $(OBJDIR)
ifneq ($(LIBS),)
	@$(MAKE) $@ -C $(LIBDIR) 
endif

fclean: clean
	rm -f $(NAME)
ifneq ($(LIBS),)
	@$(MAKE) $@ -C $(LIBDIR) 
endif

re: fclean all

FORCE:

-include $(DEPS)

.PHONY: clean fclean re all bonus