#include <stdio.h>

/**
 * this code should prompt a user to
 * enter a command
 * the prompt will repeat itself
 */

int main(int ac __attribute__((unused)), char **av __attribute__((unused)))
{
  while (int_mode)
  {
    int_mode = isatty(STDIN_FILENO);
    if (int_mode == 1)
    {
     write(STDOUT_FILENO, “~$ “, 13);
    }
  }
  
token = strtok(buffer, delimiter);
  while (token != NULL)
  {
   toks[counter] = strdup(token);
   token = strtok(NULL, delimiter);
   Counter++;
  }
  toks[counter] = token;
  
  if(!pid)
  {
   if (execve(args[0], args, NULL) == -1)
   {
      handle_errors();
   }
    else
    {
   wait();
    }
}
