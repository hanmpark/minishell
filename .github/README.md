<div align="center">
    <img src="https://github.com/hanmpark/42-project-badges/blob/main/badges/minishellm.png"/>
</div>

<h1 align="center">minishell</h1>

<p align="center">
    <b><i>A small shell implementation in C, recreating key features of Bash 3.2.</i></b>
</p></br>

<div align="center">
    <img alt="Repository created at" src="https://img.shields.io/github/created-at/hanmpark/minishell"/>
    <img alt="Repository code size" src="https://img.shields.io/github/languages/code-size/hanmpark/minishell"/>
    <img alt="Mostly used language" src="https://img.shields.io/github/languages/top/hanmpark/minishell"/>
</div>

## 📖 Description
> The **minishell** project recreates a simplified version of Bash.</br>
> It allows executing commands, handling redirections and pipes, managing environment variables, and implementing built-in commands.</br>
> This project strengthens understanding of:
> - "**Parsing and Abstract Syntax Trees (AST)**"
> - "**Process creation (`fork`, `execve`)**"
> - "**Signals (`ctrl-C`, `ctrl-D`, `ctrl-\`)**"
> - "**Redirections, heredocs, and pipes**"

## 🛠️ Features
### ✅ Mandatory
- Display a prompt and wait for commands
- History functionality
- Locate and launch executables (builtins, `$PATH`, relative/absolute paths)
- Manage single/double quotes
- Implement redirections (`<`, `>`, `<<`, `>>`)
- Implement pipes (`|`)
- Manage environment variables (`$`) and `$?`
- Proper signal handling (`ctrl-C`, `ctrl-D`, `ctrl-\`)

### 🔥 Bonus
- Logical operators: `&&` and `||`
- Parentheses for priorities (no subshells)
- Wildcard `*` (current directory only)

### Builtins Implemented
- `echo` with `-n`
- `cd` (relative/absolute paths)
- `pwd`
- `export`
- `unset`
- `env`
- `exit`

### ❌ Limitations
> "**No unclosed quotation marks**"
> "**No unsupported characters (e.g., `\` backslash, `;` semicolon)**"
> "**No features outside the subject specification**"

## 🧩 Global Structure (Abstract Syntax Tree)
<div align="center">
    <img src="https://github.com/hanmpark/minishell/blob/main/minishell_glob_struct.png" alt="minishell global structure"/>
</div>

## 📦 Installation
Clone the repository and compile:
```bash
git clone https://github.com/hanmpark/minishell.git
cd minishell
make
```

## 🚀 Usage
Run the shell:
```bash
./minishell
```

To debug tokenization and AST generation:
```bash
./minishell debug
```

### Example
```bash
minishell$ echo 1 | cat -e || (echo 2 && echo 3) || echo 4
```

## 👤 Authors
- [hanmpark](https://github.com/hanmpark)
- [Kariyu42](https://github.com/Kariyu42)
