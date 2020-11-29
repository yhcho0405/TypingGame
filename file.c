#include "typing.h"

void	delete_user(t_usr **usr, char *myname)
{
	t_usr	*tmp = *usr;
	int		i = 0;
	int		cnt;
	char	buf[1000];
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
	if (!(ft_strncmp(myname, buf, 10000)))
		printf("\ncan't delete myself\n"), sleep(2);
	else
	{
		while (tmp)
		{
			if (!(ft_strncmp(tmp->name, buf, 10000)))
			{
				tmp->score = -99999;
				flag = 1;
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

	if (!(fd = open("idtable", O_WRONLY | O_TRUNC)))
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
		if (!(ft_strncmp(tmp->name, name, 100000)))
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
		if (!(ft_strncmp(tmp->name, name, 100000)))
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
		cnt = 6;
		cnt += ft_strlen(tmp->name);
		char *fre;
		cnt += ft_strlen((fre = ft_itoa(tmp->score))); free(fre);
		printf("║%d. %s [%d]", ++i, tmp->name, tmp->score);
		for (int i = cnt; i < 30; i++)
			printf(" ");
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
	char	buffer[10000];
	char	**user;
	size_t	users;
	char	*buf;

	if (flag)
		buf = *myname;
	else
	{
		buf = malloc(1000);
		printf("Username : ");
		scanf("%s", buf);
	}
	if ((fd = open("idtable", O_RDWR | O_CREAT)) < 0)
	{
		printf("file open error");
		exit(0);
	}
	int cnt = read(fd, buffer, 10000); close(fd);
	if (cnt >= 3)
	{
		user = split(buffer, '/');
		users = count_words(buffer, '/');
		char **tmp;
		for (int i = 0 ; i < users; i++)
		{
			tmp = split(user[i], '@');
			ft_lstadd_back(usr, ft_lstnew(ft_strtrim(tmp[0], " "), ft_atoi(tmp[1])));
			// tmp[0]:공백기준 이름, tmp[1]:점수, 이 ft_lstnew를 usr에 추가한다
			allocate_fail(tmp, 2); //free
		}
		ft_lstsort(usr);
		allocate_fail(user, users);
	}
	*myname = check_dup_and_add(usr, ft_strtrim(buf, " "));
	if (!flag) free(buf);
	return *myname;
}
