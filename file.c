#include "typing.h"

void	delete_user(t_usr **usr, char *myname)
{
	t_usr	*tmp = *usr;
	int		i = 0;
	int		cnt;
	char	buf[BUFF_MAX];
	int		flag = 0;

	printf("╔═════════ User List ══════════╗\n");
	while (tmp)
	{
		cnt = 3;
		cnt += ft_strlen(tmp->name);
		printf("║%d. %s", ++i, tmp->name);
		for (int i = cnt; i < 30; i++)
			printf(" ");
		printf("║\n");
		tmp = tmp->next;
	}
	printf("╚══════════════════════════════╝\nDelete user name : ");
	scanf("%s", buf);
	tmp = *usr;
	if (!(ft_strncmp(myname, buf, BUFF_MAX)))
		printf("\ncan't delete myself\n"), sleep(2);
	else
	{
		while (tmp)
		{
			if (!(ft_strncmp(tmp->name, buf, BUFF_MAX)))
			{
				tmp->score = -999;
				flag = 1;
				break;
			}
			tmp = tmp->next;
		}
		if (flag)
		{
			ft_lstsort(usr);
			tmp = ft_lstlast(*usr, 1);
			free(tmp->name); free(tmp);
			write_idtable(usr);
		}
	}
}

void    write_idtable(t_usr **usr)
{
	t_usr	*tmp = *usr;
	int		fd;

	if (!(fd = open("db/idtable", O_WRONLY | O_TRUNC)))
	{
		printf("file open error");
		exit(0);
	}
	while (tmp)
	{
		char *fre1, *fre2;
		write(fd, tmp->name, ft_strlen(tmp->name));
		write(fd, "@", 1);
		write(fd, (fre1 = ft_itoa(tmp->score)), ft_strlen((fre2 = ft_itoa(tmp->score)))); free(fre1); free(fre2);
		if (tmp->next)
			write(fd, "/", 1);
		tmp = tmp->next;
	}
	close(fd);
}

char    *check_dup_and_add(t_usr **usr, char *name)
{
	t_usr	*tmp = *usr;

	while (tmp)
	{
		if (!(ft_strncmp(tmp->name, name, BUFF_MAX)))
			return name;
		tmp = tmp->next;
	}
	ft_lstadd_back(usr, ft_lstnew(name, 0));
	write_idtable(usr);
	return name;
}

void	update_score(char *name, t_usr **usr, int score)
{
	t_usr	*tmp = *usr;

	while (tmp)
	{
		if (!(ft_strncmp(tmp->name, name, BUFF_MAX)))
			tmp->score = score;
		tmp = tmp->next;
	}
	write_idtable(usr);
}

void    show_score(t_usr **usr)
{
	t_usr	*tmp = *usr;
	int		i = 0;
	int		cnt;

	ft_lstsort(usr);
	printf("╔════════ Ranking page ════════╗\n");
	printf("║                              ║\n");
	while (tmp)
	{
		cnt = 0;
		cnt += ft_strlen(tmp->name);
		char *fre;
		cnt += ft_strlen((fre = ft_itoa(tmp->score))); free(fre);
		printf("║%d. %s ", ++i, tmp->name);
		int i; for (i = cnt; i < 23; i++) printf("-");
		printf(" %d ", tmp->score);
		while (++i < 25) printf(" ");
		printf("║\n");
		tmp = tmp->next;
	}
	printf("║                              ║\n");
	printf("╚══════════════════════════════╝\n");
	printf("Enter \"y\" key : ");
	char buf[100]; scanf("%s", buf);
}


char    *user_id_init(t_usr **usr, char **myname, int flag)
{
	int		fd;
	char	buffer[BUFF_MAX];
	char	**user;
	size_t	users;
	char	*buf;

	if (flag)
		buf = *myname;
	else
	{
		buf = malloc(BUFF_MAX);
		printf("Username : ");
		scanf("%s", buf);
	}
	if ((fd = open("db/idtable", O_RDWR | O_CREAT)) < 0)
	{
		printf("file open error");
		exit(0);
	}
	int cnt = read(fd, buffer, BUFF_MAX); close(fd);
	if (cnt >= 3)
	{
		user = split(buffer, '/');
		users = count_words(buffer, '/');
		char **tmp;
		for (int i = 0 ; i < users; i++)
		{
			tmp = split(user[i], '@');
			ft_lstadd_back(usr, ft_lstnew(ft_strtrim(tmp[0], " "), ft_atoi(tmp[1])));
			allocate_fail(tmp, 2); //free
		}
		ft_lstsort(usr);
		allocate_fail(user, users);
	}
	*myname = check_dup_and_add(usr, ft_strtrim(buf, " "));
	if (!flag) free(buf);
	return *myname;
}
