#include "typing.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	unsigned int	cnt;

	cnt = 0;
	while (*(dest + cnt) && cnt < size)
		cnt++;
	while (*src && cnt + 1 < size)
	{
		*(dest + cnt) = *src;
		src++;
		cnt++;
	}
	if (cnt < size)
		*(dest + cnt) = 0;
	while (*src)
	{
		src++;
		cnt++;
	}
	return (cnt);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*ret;
	size_t	len;

	if (!s1 || !s2)
		return (0);
	len = ft_strlen(s1) + ft_strlen(s2) + 1;
	if (!(ret = malloc(len)))
		return (0);
	ft_strlcpy(ret, s1, len);
	ft_strlcat(ret, s2, len);
	return (ret);
}

size_t	ft_strlen(const char *str)
{
	size_t len;

	len = 0;
	while (str[len])
		len++;
	return (len);
}

int		get_len(long long n)
{
	if (n < 10)
		return (1);
	return (get_len(n / 10) + 1);
}

char	*ft_itoa(int n)
{
	char			*ret;
	int				len;
	long long		tmp;

	len = 0;
	tmp = n;
	if (n < 0)
	{
		len++;
		tmp = -tmp;
	}
	len += get_len(tmp);
	if (!(ret = malloc(len + 1)))
		return (0);
	ret[len] = 0;
	ret[--len] = tmp % 10 + '0';
	while (tmp /= 10)
		ret[--len] = tmp % 10 + '0';
	if (n < 0)
		ret[0] = '-';
	return (ret);
}

void	*ft_memset(void *ptr, int val, size_t n)
{
	size_t i;

	i = 0;
	while (i < n)
		((char *)ptr)[i++] = val;
	return (ptr);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t idx;

	idx = -1;
	while (++idx < n && (s1[idx] || s2[idx]))
	{
		if (s1[idx] != s2[idx])
			return ((unsigned char)s1[idx] - (unsigned char)s2[idx]);
	}
	return (0);
}

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	unsigned int i;

	if (!dest || !src)
		return (0);
	i = 0;
	while (src[i] && size != 0 && i < size - 1)
	{
		dest[i] = src[i];
		i++;
	}
	if (size != 0)
		dest[i] = 0;
	while (src[i])
		i++;
	return (i);
}

size_t	count_words(char const *s, char c)
{
	size_t	ret;
	int		chk;

	ret = 0;
	chk = 0;
	while (*s)
	{
		if (*s != c && !chk)
		{
			chk = 1;
			ret++;
		}
		else if (*s == c && chk)
			chk = 0;
		s++;
	}
	return (ret);
}

char	**allocate_fail(char **tmp, size_t idx)
{
	size_t	i;

	i = 0;
	while (i < idx)
		free(tmp[i++]);
	free(tmp);
	return (0);
}

char	**split(char const *s, char c)
{
	char	**ret;
	char	*tmp;
	size_t	idx;

	if (!s)
		return (0);
	idx = 0;
	if (!(ret = (char **)malloc(sizeof(char *) * (count_words(s, c) + 1) + 1)))
		return (0);
	while (*s)
	{
		if (*s == c)
		{
			s++;
			continue;
		}
		tmp = (char *)s;
		while (*s && *s != c)
			s++;
		if (!(ret[idx] = (char *)malloc(s - tmp + 1)))
			return (allocate_fail(ret, idx));
		ft_strlcpy(ret[idx++], tmp, s - tmp + 1);
	}
	ret[idx] = 0;
	return (ret);
}

int		find_set(char c, char const *set)
{
	while (*set)
	{
		if (*set == c)
			return (1);
		set++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*ret;
	char	*head;
	char	*tail;
	size_t	len;

	if (!s1 || !set)
		return ((char *)s1);
	head = (char *)s1;
	tail = (char *)s1 + ft_strlen(s1);
	while (*head && find_set(*head, set))
		head++;
	while (*(tail - 1) && head < tail && find_set(*(tail - 1), set))
		tail--;
	len = tail - head + 1;
	if (!(ret = malloc(len)))
		return (0);
	ft_strlcpy(ret, head, len);
	return (ret);
}


int	ft_atoi(const char *str)
{
	unsigned long long	ans;

	ans = 0;
	while ((9 <= *str && *str <= 13) || *str == ' ')
		str++;
	while ('0' <= *str && *str <= '9')
	{
		ans *= 10;
		ans += *str - '0';
		str++;
	}
	return (ans);
}
