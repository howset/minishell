#ifndef COMMAND_TABLE_H
# define COMMAND_TABLE_H

# include "../minishell.h"
# include "../structs.h"

/*
 * Command type enumeration to identify different types of commands
 * in the command table
 */
typedef enum e_cmd_type
{
    CMD_SIMPLE,      // Simple command (e.g., ls -l)
    CMD_PIPE,        // Command part of a pipeline
    CMD_SUBSHELL     // Command in subshell
}   t_cmd_type;

/*
 * Redirection structure to store input/output redirections
 */
typedef struct s_redirection
{
    t_tkntype               type;       // Type of redirection
    char                    *file;      // File for redirection
    struct s_redirection    *next;      // Next redirection in list
}   t_redirection;

/*
 * Command structure to store a single command with its arguments
 * and redirections
 */
typedef struct s_command
{
    char            **args;          // Command and its arguments
    t_redirection   *redirections;   // List of redirections
    t_cmd_type      type;           // Type of command
    int             pipe_read;       // Read end of pipe (-1 if none)
    int             pipe_write;      // Write end of pipe (-1 if none)
    struct s_command *next;         // Next command in sequence
}   t_command;

/*
 * Command table structure to store all commands to be executed
 */
typedef struct s_cmdtable
{
    t_command   *commands;      // List of commands
    int         cmd_count;      // Number of commands
    int         pipe_count;     // Number of pipes
}   t_cmdtable;

// Function prototypes
t_cmdtable      *create_command_table(void);
void            free_command_table(t_cmdtable *table);
t_cmdtable      *ast_to_command_table(t_ast *ast);
t_command       *create_command(char **args, t_cmd_type type);
t_redirection   *create_redirection(t_tkntype type, char *file);
void            add_command(t_cmdtable *table, t_command *cmd);
void            add_redirection(t_command *cmd, t_redirection *redir);

#endif
