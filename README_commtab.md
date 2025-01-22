# Command Table Module

## Overview
The Command Table module is responsible for converting an Abstract Syntax Tree (AST) into a flat, executable command table structure. This transformation makes it easier to execute shell commands, handle pipes, redirections, and command sequences.

## Core Data Structures

### Command Table (`t_cmdtable`)
```c
typedef struct s_cmdtable
{
    t_command   *commands;      // Linked list of commands
    int         cmd_count;      // Total number of commands
    int         pipe_count;     // Number of pipes
}   t_cmdtable;
```
The command table is the top-level structure that holds all commands to be executed.

### Command (`t_command`)
```c
typedef struct s_command
{
    char            **args;          // Command and its arguments
    t_redirection   *redirections;   // List of redirections
    t_cmd_type      type;           // Type of command (simple, pipe, subshell)
    int             pipe_read;       // Read end of pipe (-1 if none)
    int             pipe_write;      // Write end of pipe (-1 if none)
    struct s_command *next;         // Next command in sequence
}   t_command;
```

### Redirection (`t_redirection`)
```c
typedef struct s_redirection
{
    t_tkntype               type;       // Type of redirection
    char                    *file;      // Target file
    struct s_redirection    *next;      // Next redirection
}   t_redirection;
```

## How It Works

### 1. AST to Command Table Conversion
The module takes an AST and converts it into a command table through these steps:

1. **Initial Processing**:
   ```c
   t_cmdtable *table = ast_to_command_table(ast);
   ```
   This function creates an empty command table and starts recursive processing.

2. **Node Type Processing**:
   Each AST node is processed according to its type:
   - `NODE_COMMAND`: Creates a simple command
   - `NODE_PIPE`: Creates piped commands
   - `NODE_REDIRECTION`: Adds redirections to commands
   - `NODE_SEQUENCE`: Processes multiple commands in sequence
   - `NODE_SUBSHELL`: Creates a subshell command

### 2. Examples

#### Simple Command
```bash
ls -l
```
AST:
```
NODE_COMMAND
├── args: ["ls", "-l"]
└── args_count: 2
```
Command Table:
```
commands[0]:
  ├── args: ["ls", "-l"]
  ├── type: CMD_SIMPLE
  └── redirections: NULL
```

#### Pipeline
```bash
cat file.txt | grep pattern
```
AST:
```
NODE_PIPE
├── left: NODE_COMMAND (args: ["cat", "file.txt"])
└── right: NODE_COMMAND (args: ["grep", "pattern"])
```
Command Table:
```
commands[0]:
  ├── args: ["cat", "file.txt"]
  ├── type: CMD_PIPE
  └── pipe_write: fd[1]
commands[1]:
  ├── args: ["grep", "pattern"]
  ├── type: CMD_PIPE
  └── pipe_read: fd[0]
```

#### Redirections
```bash
echo hello > output.txt
```
AST:
```
NODE_REDIRECTION
├── type: TKN_RDIR_OUT
├── filename: "output.txt"
└── left: NODE_COMMAND (args: ["echo", "hello"])
```
Command Table:
```
commands[0]:
  ├── args: ["echo", "hello"]
  ├── type: CMD_SIMPLE
  └── redirections:
      └── type: TKN_RDIR_OUT
      └── file: "output.txt"
```

### 3. Memory Management

The module handles memory in three main areas:

1. **Command Creation**:
   - Allocates space for command structure
   - Deep copies command arguments
   - Initializes pipe descriptors to -1

2. **Redirection Creation**:
   - Allocates redirection structure
   - Deep copies filenames
   - Links redirections in a list

3. **Cleanup**:
   - `free_command_table`: Frees entire table
   - `free_command`: Frees command and its resources
   - `free_redirection`: Frees redirection chain

### 4. Error Handling

The module includes robust error handling:

1. **Memory Allocation**:
   - Checks all malloc calls
   - Cleans up on allocation failure
   - Returns NULL for failed operations

2. **Pipe Creation**:
   - Checks pipe system call success
   - Handles pipe creation failures gracefully

3. **Invalid Input**:
   - Validates AST structure
   - Handles NULL or invalid arguments
   - Skips invalid nodes

## Usage Example

```c
// Parse input into AST
t_token *tokens = lexer(input);
t_ast *ast = parse(tokens);

// Convert AST to command table
t_cmdtable *table = ast_to_command_table(ast);
if (!table)
{
    // Handle error
    return ;
}

// Use command table
// ... execute commands ...

// Cleanup
free_command_table(table);
free_ast(ast);
free_tokens(tokens);
```

## Testing

The module includes comprehensive tests covering:
- Simple commands
- Pipelines
- Redirections
- Command sequences
- Subshells
- Complex combinations

Run tests using:
```bash
make test
```

## Error Codes

The module uses NULL returns to indicate errors:
- NULL from `ast_to_command_table`: AST conversion failed
- NULL from `create_command`: Command creation failed
- NULL from `create_redirection`: Redirection creation failed

## Best Practices

1. Always check return values for NULL
2. Free resources in reverse order of creation
3. Handle pipe file descriptors carefully
4. Validate AST structure before conversion
5. Use proper error handling in the executor

## Integration Points

The Command Table module interfaces with:
1. Parser (input): Receives AST
2. Executor (output): Provides command table
3. Memory manager: Handles allocation/deallocation
4. Error handler: Reports conversion failures
