#my_shell

A minimal custom shell built in C for linux systems. Supports built-in commands (`cd`,`exit`),
arrow key history navigation, and launching external programs - with a custom `.desktop` launcher
to run it like a desktop terminal app.

---

##Features

-Built-in commands : `cd`,`exit`
-External command execution using `fork()` and `execvp()`
-Arrow key navigation (up/down to access command history)
-Line editing support via GNU Readline
-Launchable from the desktop via `.desktop` shortcut
-Simple shell prompt(`>`)

---

##Requirements

-Linux system(tested on XFCE,Linux Mint)
-GCC compiler
-GNU Readline library

Install Readline if missing:

```bash
sudo apt install libreadline-dev
