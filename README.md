# snowshell

Simple shell for CS class.

You may ask, what does it do? It's a REPL that can run subprocesses and it handles a few "edge case" scenarios (SIGINT/Ctrl + C, etc).

## Examples

### Running a subprocess

```bash
⛄️ whoami
rei
⛄️ echo hello
hello
```

### Gracefully handling commands not found

```bash
⛄️ a
🌲⛷  a: command not found
⛄️ b
🌲⛷  b: command not found
```

### Builtins

It currently implements `cd` and `exit`.

```bash
⛄️ pwd
/home/rei/snowshell
⛄️ cd ..
⛄️ pwd
/home/rei
⛄️ exit 1
```

### Signals

Ctrl + C does nothing on the parent process (shell).

```bash
⛄️ ^C
```

Ctrl + D stops the shell altogether.

```bash
⛄️ ^D
❄❅❄❅ Goodbye and stay warm! ❄❅❄❅
```

Ctrl + C terminates child process.

```bash
⛄️ sleep 10
^C
⛄️
```
