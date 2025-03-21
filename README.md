# 🦪 MiniShell

## ↕️Table of Contents
1.[Introduction](#-introduction)

2.[Features](#-features)

3.[Installation](#-installation)

4.[Usage](#-usage)

5.[Built-in Commands](#-built-in-commands)

6.[Contributors](#-contributors)

7.[License](#-license)

## 🏁 Introduction
MiniShell is a lightweight Unix shell implementation written in C by Tudor Ursescu and Christoph Könnecke. This project aims to recreate the essential functionalities of a traditional shell, providing a simple yet powerful command-line experience. Inspired by Bash, MiniShell supports process execution, input/output redirection, pipes, and built-in shell commands.

This project is part of the 42 School curriculum, focusing on process management, system calls, and terminal behavior in UNIX-based environments.
## ⚡ Features
✔️ Execute commands with arguments (e.g., ls -l, echo "Hello")

✔️ Handle multiple processes using pipes (|)

✔️ Input (<) and output (> & >>) redirection support

✔️ Implemented built-in commands (cd, echo, pwd, export, unset, env, exit)

✔️ Signal handling

✔️ Environment variable expansion

✔️ Basic error handling for invalid commands and syntax

## 🔧 Installation
To install and compile minishell, follow these steps:
```sh
#Clone the repository
git clone https://github.com/Tudor-Ursescu/Minishell.git
# Navigate into the project directory
cd Minishell
# Compile the project
make
```
This will generate an executable named `minishell`.
## 💡 Usage
Once compiled, run MiniShell with:
```sh
./minishell
```
You can now execute commands like:
```sh
minishell$ ls -l
minishell$ echo "Hello, world!"
minishell$ cat file.txt | grep "keyword"
minishell$ export VAR="value"
minishell$ echo $VAR
minishell$ exit
```
To exit the shell, use the `exit` command or press `Ctrl+D`.
## 🏗 Built-in Commands
MiniShell supports the following built-in commands:
| Command   | Description                                  | Example Usage                |
|-----------|----------------------------------------------|------------------------------|
| `cd`      | Changes the current directory               | `cd /home/user`               |
| `echo`    | Displays a message or variable              | `echo "Hello World"`          |
| `pwd`     | Prints the current working directory        | `pwd`                         |
| `export`  | Sets an environment variable                | `export PATH=$PATH:/new/path` |
| `unset`   | Removes an environment variable             | `unset VAR_NAME`              |
| `env`     | Displays environment variables              | `env`                         |
| `exit`    | Exits the shell                             | `exit`                        |
------------------------------------------------------------------------------------------
All other commands are executed using system binaries 
## 👥 Contributors
[**Tudor Ursescu**](https://github.com/Tudor-Ursescu)

[**Christoph Könnecke**](https://github.com/ckonneck-42)
## 📜 License
This is an open-source project, and you are free to use, modify, and distribute it as you see fit. Contributions and improvements are always welcome! 😊