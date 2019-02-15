char *getInput();
char **arg_splitter(char *line, int x);
void list_contents(char **args);
int shellxecute(char **args, int flag, char f[],char home[]);
void disp_info(char **args, char home[]);
void disp_reminder(char **args);
void disp_clock(char **args);
void shsetenv(char **args);
void shunsetenv(char **args);
void jobs();
void kjob(char **args);
void fg(char **args);
void bg(char **args);
void overkill();

#define MAXPATHLEN 200
#define MAXSTATLEN 2000
