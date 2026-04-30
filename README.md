# minishell

A 42 school project implementing a minimal Unix shell in C.

## Features

- Interactive prompt with command history
- Command execution via `PATH` lookup
- Pipes (`|`) between commands
- Input/output redirections (`<`, `>`, `>>`, `<<` heredoc)
- Environment variable expansion (`$VAR`, `$?`)
- Single and double quote handling
- Signal handling (`Ctrl+C`, `Ctrl+D`, `Ctrl+\`)

## Built-in Commands

| Command | Description |
|---------|-------------|
| `echo [-n]` | Print text |
| `cd [path]` | Change directory |
| `pwd` | Print working directory |
| `export [name=value]` | Set environment variable |
| `unset [name]` | Remove environment variable |
| `env` | Print environment |
| `exit [status]` | Exit the shell |

## Usage

```bash
make
./minishell
```

## Requirements

- libreadline
- libft (included)
