#ifndef TYPING_H
# define TYPING_H

#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <signal.h>
#include <sys/time.h>
#include <fcntl.h>
#include <stdlib.h>
#include <time.h>

# define BUFF_MAX				10000

# define SELECT_MODE_STR		"╔════════ Select Mode ════════╗\n║        Game Mode : 1        ║\n║       Ranking Page : 2      ║\n║       Delete User : 3       ║\n║          Log Out : 4        ║\n╚═════════════════════════════╝\nMode : "
# define SELECT_GAME_MODE_STR	"╔════════ Select Mode ════════╗\n║           Easy : 1          ║\n║          Normal : 2         ║\n║           Hard : 3          ║\n╚═════════════════════════════╝\nMode : "

typedef struct		s_usr
{
    char			*name;
	int				score;
    struct s_usr	*next;
}					t_usr;

typedef struct		s_set
{
	size_t			count;
	char			**words;
}					t_set;

// main.c
int					main(int argc, char **argv);
void				parsing(t_set *set, char *file);
int					main_init(t_usr **usr, char **name, char **myname, int flag);

// game.c
void				game(t_set *set, t_usr **usr, char *myname);
void				game_timer(int sec, pid_t pid);
void				game_start(t_set *set, t_usr **usr, int mode, char *myname);
int					game_init();

// util.c
size_t				ft_strlcat(char *dest, const char *src, size_t size);
char				*ft_strjoin(char const *s1, char const *s2);
size_t				ft_strlen(const char *str);
int					get_len(long long n);
char				*ft_itoa(int n);
void				*ft_memset(void *ptr, int val, size_t n);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
size_t				ft_strlcpy(char *dest, const char *src, size_t size);
size_t				count_words(char const *s, char c);
char				**allocate_fail(char **tmp, size_t idx);
char				**split(char const *s, char c);
int					find_set(char c, char const *set);
char				*ft_strtrim(char const *s1, char const *set);
int					ft_atoi(const char *str);

// list.c
void				free_all(t_usr **usr);
t_usr				*ft_lstlast(t_usr *lst, int flag);
int					ft_lstsize(t_usr *lst);
void				ft_lstsort(t_usr **lst);
t_usr				*ft_lstnew(char *name, int score);
void				ft_lstadd_back(t_usr **lst, t_usr *new);

// file.c
void				delete_user(t_usr **usr, char *myname);
void				write_idtable(t_usr **usr);
char				*check_dup_and_add(t_usr **usr, char *name);
void				update_score(char *name, t_usr **usr, int score);
void				show_score(t_usr **usr);
char				*user_id_init(t_usr **usr, char **myname, int flag);

#endif
