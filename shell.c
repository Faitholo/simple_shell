#include "shell.h"
/**
 * main - the shell program start point
 * @ac: int num of command line args
 * @av: null term'd arr of strs contain args
 * @ev: null term'd arr of strs contain env vars
 * Return: int result. 0 in success, everything else is an error
 */
int main(int ac, char **av, char **ev)
{
	sev_t sev;
	int exitcode = 0;
	(void)ac;
	init_shell_env(&sev, av, ev);

	while (sev.skywalker)
	{
		dis_prompt(sev);
		getcom(&sev);
		checker_alias(&sev);
		if (!check_builtin(&sev))
			actions(&sev);
		dis_error(&sev);
	}
	write_log(&sev);
	exitcode = sev.error;
	cl_sev(&sev);
	return (exitcode);
}
