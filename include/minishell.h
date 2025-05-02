/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: izahr <izahr@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 11:59:47 by eelkabia          #+#    #+#             */
/*   Updated: 2025/04/22 00:27:06 by izahr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <dirent.h>
# include <fcntl.h>
# include <limits.h>
# include <linux/limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/wait.h>
# include <unistd.h>

extern volatile sig_atomic_t	g_signal_global;

typedef enum e_stat
{
	LOOP = 0,
	NO_LOOP = 1
}								t_stat;

typedef struct s_env
{
	char						*var;
	char						*value;
	struct s_env				*next;
}								t_env;

typedef struct s_dir
{
	char						*oldir;
	char						*dir;
	char						*home;
	long						exit_status_;
}								t_dir;

typedef struct s_signal
{
	struct sigaction			sa_int;
	struct sigaction			sa_quit;
}								t_signal;

typedef struct s_utils
{
	char						**line;
	char						**split;
	t_env						**env;
	t_dir						*dir;
	t_stat						*status;
	int							nc;
	int							i;
}								t_utils;

typedef struct s_tmp
{
	size_t						i;
	size_t						j;
	char						*result;
}								t_tmp;

void							handle_cd(char **split, t_env *my_env,
									t_dir *dir);
void							handle_echo(char **args, t_dir *dir);
void							handle_exit(char **split, t_dir *directory,
									t_stat *STATUS);
int								is_builtin(char **args);
int								try_builtin(char **args, t_utils *u);
int								is_all_n(char *str);
void							executing(t_utils *u);
void							handle_cd_path(char **split, t_env *my_env,
									t_dir *dir);
void							update_directory(t_dir *dir, t_env *my_env);
void							update_env_vars(t_env *tmp, char *buf,
									char **smp);
void							handle_cd_no_arg(t_env *my_env, t_dir *dir);
void							handle_cd_oldpwd(t_env *my_env, t_dir *dir);
void							execve_input(t_utils *u, char **split);
void							ft_process(char *str, int *pipe_fd,
									int input_fd, t_utils *u);

t_env							*create_env(char **envp);
void							parse_env(t_env *lst, int k, t_dir *dir);
t_env							*clear_node(t_env *env, char *str);
char							*check_env(t_env *env, char *str);

t_env							*create_node(char *line);
void							ft_lstadd_back(t_env **lst, t_env *new);
char							**convert_env(t_env *env);
char							*expand_user(const char *user);
void							handle_dollar(const char *t, t_tmp *tmp,
									t_env *env, int st);

void							error_par(char **data, const char *msg);
void							ft_error(char *str, int n);
void							ft_perror(char *str, int n);
void							ft_cmd(char *str, char **cmd, int n);
int								check_meta_char(char *str);
void							ft_putstr_fd(char *s, int fd);
void							ft_putendl_fd(char *s, int fd);
int								try_execute(char **args, t_env **env,
									t_dir *dir);
void							parent_process(int *pipe_fd, int input_fd,
									t_utils *u, pid_t id);
void							handle_export(t_dir *directory, char **split,
									t_env *my_env);
char							**ft_split(char const *s, char c);
void							history_nd_process(char **line, t_dir *dir,
									t_env **my_env, t_stat *status);
char							*trim_whitespace(char *str);
void							process_input(char **line, t_dir *dir,
									t_env **env, t_stat *status);
void							free_array(char **arr);
void							lst_clean(t_env *head);
void							*ft_realloc(void *ptr, size_t old_size,
									size_t new_size);
void							free_argv(char **argv, int count);
int								is_num(char *str);
int								is_all_num(char *str);
unsigned long long				ft_atoi(const char *str);
void							int_to_str(int num, char *buffer);
int								count_args(const char *input);
int								adjust_exit_status(int status);
char							*get_next_arg(const char **input);
char							*get_path(char *cmd, t_env *env);
void							execute_pipes(char **s, t_utils *u, int nc,
									int *cp);
int								init_pipe_exec(int *nc, int **cp, char **split,
									t_dir *dir);
void							init_sigactions(struct sigaction sa[3]);
void							cleanup_pipe_exec(int *cp, char **split,
									struct sigaction sa[3]);
char							**parse_prompt_to_argv(const char *input);
int								check_unclosed(char *line);
char							*special_check(const char *token, t_env *env,
									int last_exit_status);
void							tilda_remod(char **line, t_dir dir);
int								nested_quotes(char *str);
void							handle_quotes(const char *t, size_t *i,
									int q[3]);
int								ft_handle_quotes(const char c, int *quote_flag);
int								ft_skip_whitespace(const char *str, int *i,
									int *quote_flag);
void							check_redirections(char *str);
char							*strip_redirections(char *command);
void							setup_child_signals(void);
void							setup_signals(t_signal *config);
int								handle_signals(int status, int fd,
									char **tokens);
char							*ft_strjoin(char const *s1, char const *s2);
char							*ft_strcat(char *dest, const char *src);
char							*ft_strnstr(const char *str,
									const char *to_find, size_t len);
char							*ft_strncpy(char *dest, const char *src,
									size_t n);
int								ft_strcmp(char *str1, const char *str2);
void							append_str(const char *src, char *dest,
									size_t *j);
char							*append_token(char *current_cmd,
									char *token_to_add);
char							*build_new_line(char **tokens, t_dir dir);
void							normal_cmd(char **tokens, int i, char **new_cmd,
									char **tmp);
int								ft_isspace(int c);
size_t							ft_strlcpy(char *dst, const char *src,
									size_t dstsize);
char							*ft_strchr(const char *s, int c);
void							*ft_memcpy(void *dst, const void *src,
									size_t n);
char							*ft_strcpy(char *dest, const char *src);
int								ft_strlen(const char *s);
char							*ft_strdup(const char *s1);
char							*ft_substr(char *s, int start, size_t len);
char							*ft_ft_strchr(const char *s, int c);
int								ft_strncmp(const char *s1, const char *s2,
									size_t n);
void							safe_exit(char **split, t_dir *directory);
char							*expand_tilde(const char *token, t_dir dir);
void							wait_children(int *cp, int nc, t_dir *d);
void							handle_child_process(char **s, t_utils *u,
									int pp[2], int np[2]);
void							close_pipes(int pp[2]);
void							handle_child(char **s, t_utils *u, int pp[2],
									int np[2]);
void							handle_parent(int pp[2], int np[2], int i,
									int nc);
char							*ft_strjoin_free(char *s1, char *s2);

#endif