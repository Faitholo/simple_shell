#include "log.h"
/**
 * add_log - add input from the user to log
 * @sev: ptr to shell env var link list
 * Return: 1 in success, 0 in fail
 */
int add_log(sev_t *sev)
{
	if (add_node(&sev->log, NULL, _strdup(sev->input, &sev->mem)))
	{
		sev->log_cnt++;
		sev->cmd_cnt++;
		return (1);
	}
	return (0);
}
/**
 * write_log - write the current sessions' log to a file
 * @sev: ptr to the shell env var
 * Return: 1 in success, 0 in fail
 */
int write_log(sev_t *sev)
{
	char *fullpath = NULL, *entry = NULL;

	list_t *walker = NULL;
	int fds = 0, len = 0;

	fullpath = _strcat(_getenvironment("HOME", sev), "/", &sev->mem);
	fullpath = _strcat(fullpath, LOGFILE, &sev->mem);
	fds = open(fullpath, O_WRONLY | O_CREAT | O_TRUNC, 0600);
	if (fds == -1)
	{
		return (0);
	}
	reverse_list(&(sev->log));
	walker = sev->log;
	while (walker)
	{
		entry = walker->value;
		entry = _strcat(entry, "\n", &sev->mem);
		len = _strlen(entry);
		if (write(fds, entry, len) < len)
		{
			close(fds);
			return (0);
		}
		walker = walker->next;
	}
	close(fds);
	return (1);
}
/**
 * get_log_count - read and get log file count
 * @sev: ptr to shell env var struct
 * Return: num of entries in log file, 0 in empty or fail
 */
int get_log_count(sev_t *sev)
{
	char *fullpath = NULL, buffer[MAXBUFREAD];
	int fds = 0;
	size_t size = MAXBUFREAD, lines = 0;
	ssize_t numread = 1, index = 0;

	fullpath = _strcat(_getenvironment("HOME", sev), "/", &sev->mem);
	fullpath = _strcat(fullpath, LOGFILE, &sev->mem);
	fds = open(fullpath, O_RDONLY);
	if (fds == -1)
	{
		return (0);
	}
	while (numread)
	{
		numread = read(fds, &buffer, size);
		if (numread == -1)
		{
			close(fds);
			return (0);
		}
		for (index = 0; index < numread; index++)
		{
			if (buffer[index] == '\n')
				lines++;
		}
	}
	return (lines % MAXLOGSIZE);
}
