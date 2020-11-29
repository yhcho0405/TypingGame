#include "typing.h"


void free_all(t_usr **usr)
{
	t_usr *tmp;

	if (usr)
	{
		while (*usr)
		{
			tmp = (*usr)->next;
			free((*usr)->name);
			free(*usr);
			*usr = tmp;
		}
		*usr = 0;
	}
}

t_usr	*ft_lstlast(t_usr *lst, int flag)
{
	t_usr *tmp;

	if (!lst)
		return (0);
	while (lst->next)
	{
		tmp = lst;
		lst = lst->next;
	}
	if (flag)
		tmp->next = NULL;
	return (lst);
}

int		ft_lstsize(t_usr *lst)
{
	int ret;

	ret = 0;
	while (lst)
	{
		lst = lst->next;
		ret++;
	}
	return (ret);
}

void	ft_lstsort(t_usr **lst)
{
	t_usr 	*tmp = *lst;
	t_usr	*ttmp;
	t_usr	*tttmp;
	char	*maxc;
	int 	maxi;
	int		itmp;
	char	*ctmp;

	while (tmp)
	{
		ttmp = tmp;
		maxi = -1;
		while (ttmp)
		{
			if (maxi < ttmp->score)
			{
				maxi = ttmp->score;
				maxc = ttmp->name;
				tttmp = ttmp;
			}
			ttmp = ttmp->next;
		}
		itmp = tmp->score;
		ctmp = tmp->name;
		tmp->score = maxi;
		tmp->name = maxc;
		tttmp->score = itmp;
		tttmp->name = ctmp;
		tmp = tmp->next;
	}
}

t_usr	*ft_lstnew(char *name, int score)
{
	t_usr	*ret;

	if (!(ret = (t_usr *)malloc(sizeof(t_usr))))
		return (0);
	ret->name = name;
	ret->score = score;
	ret->next = 0;
	return (ret);
}


void	ft_lstadd_back(t_usr **lst, t_usr *new)
{
	t_usr	*tmp;

	if (!*lst)
		*lst = new;
	else
	{
		tmp = *lst;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}
