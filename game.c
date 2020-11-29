#include "typing.h"

int		timeset[3] = {30, 20, 10};

void game_timer(int sec, pid_t pid)
{
	time_t t;
	time_t tmp;
	int count = 0;

	t = time(NULL);
	while (time(NULL) - t < sec) {
	}
	kill(pid, SIGINT);
	exit(0);
}

void game_start(t_set *set, t_usr **usr, int mode, char *myname)
{
	char	str[1000];
	char	*ans;
	int		score = 0;

	srand((unsigned int)time(NULL));
	while (1)
	{
		system("clear");
		printf("╔═══════════════════╗\n");
		if (mode == 1) printf("║   < Easy Mode >   ║\n");
		else if (mode == 2) printf("║  < Normal Mode >  ║\n");
		else if (mode == 3) printf("║   < Hard Mode >   ║\n");
		if (score < 10) printf("║  your score : %d   ║\n", score);
		else printf("║  your score : %d  ║\n", score);
		printf("╚═══════════════════╝\n");
		ft_memset(str, 0, 1000);
		ans = set->words[rand() % set->count];
		printf("%s\n", ans);
		while (1)
		{
			scanf("%s", str);
			if (!(ft_strncmp(str, ans, 1000)))
				break;
			printf("==== wrong ====\n");
		}
		score++;
		update_score(myname, usr, score);
	}
	exit(0);
}

int game_init()
{
	int mode;

	printf(SELECT_GAME_MODE_STR);
	scanf("%d", &mode);
	if (!(mode == 1 || mode == 2 || mode == 3))
	{
		printf("wrong mode");
		exit(0);
	}
	return mode;
}

void game(t_set *set, t_usr **usr, char *myname)
{
	pid_t	pid;
	int		status;
	char	round = 0;
	int		mode;

	mode = game_init(); system("clear");
	printf("====== Ready ======\n"); sleep(1); system("clear");
	printf("======   3   ======\n"); sleep(1); system("clear");
	printf("======   2   ======\n"); sleep(1); system("clear");
	printf("======   1   ======\n"); sleep(1); system("clear");
	if (!(pid = fork()))
		game_start(set, usr, mode, myname);
	if (!(vfork())) /* child process */
		game_timer(timeset[mode - 1], pid);

	printf("\n==== Timeover ====\nPress Enter : ");
	getchar();
	sleep(1);
}
