#include "typing.h"

void parsing(t_set *set, char *file)
{
	char buf[BUFF_MAX];
	int fd;
	if ((fd = open(file, O_RDONLY)) < 0)
	{
		printf("file open error");
		exit(0);
	}
	read(fd, buf, BUFF_MAX);
	set->words = split(buf, ' ');
	set->count = count_words(buf, ' ');
	close(fd);
}


int main_init(t_usr **usr, char **name, char **myname, int flag)
{
	int		mode;

	system("clear");
	*myname = user_id_init(usr, name, flag);
	system("clear");
	printf(SELECT_MODE_STR);
	scanf("%d", &mode);
	if (!(mode == 1 || mode == 2 || mode == 3 || mode == 4))
	{
		printf("wrong mode");
		exit(0);
	}
	return mode;
}

int main(int argc, char **argv)
{
	int		mode;
	t_set	set;
	t_usr	*usr;
	char	*myname;

	parsing(&set, "db/wordset");
	if (argc == 2)
		mode = main_init(&usr, &argv[1], &myname, 1);
	else
		mode = main_init(&usr, &myname, &myname, 0);
	system("clear");
	if (mode == 1) game(&set, &usr, myname);
	else if (mode == 2) show_score(&usr);
	else if (mode == 3) delete_user(&usr, myname);
	free_all(&usr); //free
	allocate_fail(set.words, set.count); //free
	// close & free
	if (mode != 4)
		system(ft_strjoin("./start ", myname));
	/* TEST
	printf("%d\n", set.count);
	for(int i = 0; i < set.count; i++)
		printf("%s\n", set.words[i]);
	*/
}

/*
------------------------------
[1. game mode]
wordset1에서 나온 랜덤 단어를 일정 시간 안에 타이핑 한다

1) 타이핑 성공?
-> 다음 단어로 똑같은 방식으로 시작

1-1) 언제까지 타이핑 하는가?
->  유저가 정한 개수만큼 or 무한 모드(틀릴 때 까지 반복)

2) 타이핑 실패?
->  게임 오버

3) 게임이 끝나면?
->  점수 출력

------------------------------

[2. practice mode]
wordset1 에서 나온 랜덤 단어를 타이핑한 시간을 알려주기

1) 몇번까지?
->  유저가 정한 만큼?

1-1) 맞으면?
->  다음 단어로 똑같은 방식으로 시작

2) 만약 틀리면?
->  게임오버 (난이도?)

2) 게임 오버 되면?
->  점수 출력
------------------------------

7장 Process Control

*/


		// 모드 (게임, 타자 속도 측정)
		// 난이도 (시간초, 틀린걸 몇번 봐주는지)
		// 라운드 ()
/*
	char buf[10000];
	int fd = open(argv[1], O_RDONLY);
	read(fd, buf, 10000);
	char **words = split(buf, ' ');
	int count = count_words(buf, ' ');

	printf("%d\n", count);
	for(int i = 0; i < count; i++)
		printf("%s\n", words[i]);
*/
