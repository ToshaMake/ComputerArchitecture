#include "readkey.h"

int rk_readkey(int* key)
{
	struct termios orig_options;
	char buff[32];

	if (!tcgetattr(STDIN_FILENO, &orig_options))
		return -1;
	if (!rk_mytermregime(0, 0, 1, 0, 1))
		return -1;
	int count = read(1, buff, 31);
	if (!count)
		return -1;
	buff[count] = '\0';
	printf("%s", buff);
	printf("%d", count);
	if (!strcmp(buff, "l"))
		*key = KEY_l;
	else if (!strcmp(buff, "s"))
		*key = KEY_s;
	else if (!strcmp(buff, "r"))
		*key = KEY_r;
	else if (!strcmp(buff, "t"))
		*key = KEY_t;
	else if (!strcmp(buff, "i"))
		*key = KEY_i;
	else if (!strcmp(buff, "\n"))
		*key = KEY_enter;
	else if (!strcmp(buff, "\033[15~"))
		*key = KEY_f5;
	else if (!strcmp(buff, "\033[17~"))
		*key = KEY_f6;
	else if (!strcmp(buff, "\033[A"))
		*key = KEY_up;
	else if (!strcmp(buff, "\033[B"))
		*key = KEY_down;
	else if (!strcmp(buff, "\033[C"))
		*key = KEY_right;
	else if (!strcmp(buff, "\033[D"))
		*key = KEY_left;
	else 
		*key = KEY_other;
	if (!tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_options))
		return -1;

	return 0;
}

int rk_mytermsave()
{
	struct termios options;

	int fd = open("settings.bin", O_CREAT | O_RDWR | O_TRUNC);

	if (tcgetattr(STDIN_FILENO, &options) != 0)
		return -1;
	if (!write(fd, &options, sizeof(options)))
		return -1;
	return 0;
}

int rk_mytermrestore()
{
	struct termios options;
	int fd = open("settings.bin", O_RDONLY);

	if (!read(fd, &options, sizeof(options)))
		return -1;
	if (!tcsetattr(STDIN_FILENO, TCSAFLUSH, &options))
		return -1;

	return 0;
}

int rk_mytermregime(int regime, int vtime, int vmin, int echo, int sigint)
{
	struct termios options;

	if (tcgetattr(STDIN_FILENO, &options) != 0)
		return -1;
	if (regime == 1)
		options.c_lflag |= ICANON;
	else if (regime == 0)
		options.c_lflag &= ~ICANON;
	else return -1;

	if (regime == 0)
	{
		options.c_cc[VTIME] = vtime;
		options.c_cc[VMIN] = vmin;
		if (echo == 1)
			options.c_lflag |= ECHO;
		else if (echo == 0)
			options.c_lflag &= ~ECHO;
		else return -1;
		if (sigint == 1)
			options.c_lflag |= ISIG;
		else if (sigint == 0)
			options.c_lflag &= ~ISIG;
		else return -1;
	}
	if (!tcsetattr(STDIN_FILENO, TCSANOW, &options))
		return -1;

	return 0;
}
