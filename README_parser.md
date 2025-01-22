**High-Level Overview**
This code is implementing a recursive descent parser for a shell-like command language. It takes a linked list of tokens as input and constructs an Abstract Syntax Tree (AST) representing the parsed command line. The AST nodes indicate commands, sub-expressions, pipes, redirections, and logical operators.

**Key Idea**:
Each function represents a “rule” in the language grammar. They call each other based on what they expect next. The input moves forward through the token list, and depending on what’s found, the parser builds a corresponding AST node. The code checks token types and creates nodes like `NODE_COMMAND`, `NODE_REDIRECTION`, `NODE_PIPE`, `NODE_AND`, `NODE_OR`, etc.

**Data Structures Involved**:
- **`t_token`**: Holds the type and value of a single token. Example token types:
  - `TKN_WORD` (e.g., command names, filenames)
  - `TKN_PIPE` (`|`)
  - `TKN_RDIR_IN` (`<`), `TKN_RDIR_OUT` (`>`), `TKN_APPEND` (`>>`), `TKN_HEREDOC` (`<<`)
  - `TKN_AND` (`&&`), `TKN_OR` (`||`), `TKN_SEMCOL` (`;`)
  - `TKN_PAREN_OP` (`(`), `TKN_PAREN_CL` (`)`)
- **`t_ast`**: Represents a node in the Abstract Syntax Tree. Each node corresponds to a grammatical construct (a command, a pipe, a redirection, a parenthesized expression, etc.).

**Step-by-Step Through Each Function**:

1. **`parse()`**
   - Entry point for parsing.
   - Starts from the top-level rule: `parse_expression()`.
   - Returns the fully built AST representing the entire input line.

2. **`parse_expression(t_token **current)`**
   - Parses logical and sequence operators like `&&`, `||`, and `;`.
   - First, it calls `parse_pipe()` to get a node representing either a simple command or something connected by pipes.
   - Then, if it finds `&&`, `||`, or `;`, it creates an operator node (`NODE_AND`, `NODE_OR`, or `NODE_SEQUENCE`), sets its left child to the previously parsed node, and calls `parse_pipe()` again to get the right child.
   - Continues this until no more logical operators are found.

   **Example**:
   For input: `ls -l && echo done; pwd`
   - `parse_expression()` first parses `ls -l` as a command node.
   - Sees `&&` next, so it creates an `AND` node whose left child is `ls -l`.
   - It then parses `echo done` for the right child.
   - Sees `;`, so it creates a `SEQUENCE` node whose left child is the `AND` node and then parses `pwd` as the new right child.

3. **`parse_pipe(t_token **current)`**
   - Handles the `|` operator.
   - First calls `parse_term()` to get a command or sub-expression with potential redirections.
   - If it sees a `|`, it creates a `PIPE` node, sets its left child to what was parsed, then calls `parse_term()` again for the right child.
   - Keeps chaining if multiple `|` operators appear.

   **Example**:
   For input: `cat file | grep foo | wc -l`
   - `parse_pipe()` calls `parse_term()` to get the `cat file` node.
   - Sees `|`, creates a `PIPE` node, then calls `parse_term()` to get `grep foo`.
   - Sees another `|`, creates another `PIPE` node, left child is the first pipe node, and then gets `wc -l` as the right child.

4. **`parse_term(t_token **current)`**
   - Parses a “term” which is either a factor plus optional redirections.
   - Calls `parse_factor()` first.
   - If it sees redirection operators like `<`, `>`, `>>`, `<<`, it creates a `REDIRECTION` node, sets it as a parent of the previously parsed node, and moves on to parse the filename after the redirection.

   **Example**:
   For input: `ls > out.txt`
   - `parse_term()` calls `parse_factor()` and gets the `ls` command node.
   - Sees `>`, creates a `REDIRECTION` node, sets its left child to `ls`, and reads `out.txt` as the filename.

5. **`parse_factor(t_token **current)`**
   - Deals with the most basic units of the grammar: either a command or a parenthesized sub-expression.
   - If it sees `(`, it calls `parse_expression()` to parse what’s inside, then expects `)` at the end.
   - Otherwise, if it sees a `TKN_WORD`, it calls `parse_command()`.

   **Example**:
   For input: `(echo hello && echo world)`
   - `parse_factor()` sees `(`, calls `parse_expression()` on `echo hello && echo world`, and then checks for `)`.

6. **`parse_command(t_token **current)`**
   - Collects consecutive `TKN_WORD` tokens and builds a command node, adding each word as an argument.
   - Stops when it hits an operator or the end of tokens.

   **Example**:
   For input: `echo hello world`
   - `parse_command()` sees `echo`, then `hello`, then `world` as `TKN_WORD` tokens. It builds a command node with args: `["echo", "hello", "world"]`.

**How the Functions Call Each Other**:
- The parsing starts at the highest level (`parse()` -> `parse_expression()`).
- `parse_expression()` uses `parse_pipe()` internally to parse pipe segments.
- `parse_pipe()` uses `parse_term()` to handle commands and redirections.
- `parse_term()` uses `parse_factor()` to get either a command or a grouped expression.
- `parse_factor()` uses `parse_command()` to get the most basic command form.
- For parenthesized expressions, `parse_factor()` calls back up to `parse_expression()`. This creates a recursive structure allowing nested expressions.

**In Short**:
- `parse()` → `parse_expression()`
- `parse_expression()` → `parse_pipe()`
- `parse_pipe()` → `parse_term()`
- `parse_term()` → `parse_factor()`
- `parse_factor()` → `parse_command()` or `parse_expression()` again for parentheses.

This chain of function calls breaks the input down from the highest-level (logical operators) down to the lowest-level (commands and arguments), building a structured tree along the way. Each step refines and structures the input tokens until a well-formed AST is produced.
