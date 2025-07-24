# AltCmd

- [中文](README_cn.md)

This is a tool, make you run shell anywhere gracefully.

![](imgs/001.png#gh-light-mode-only)

![](imgs/002.png#gh-dark-mode-olny)

## How to use

Start the executable file, and the software will run in the background.

Press <kbd>Alt + Space</kbd> anywhere to activate the command window, enter the command, and press <kbd>Enter</kbd>.

Note that the default working directory for commands is the user's home directory.

If you want to run the command as an administrator, you can use <kbd>Shift + Enter</kbd>.

If you want to display the running window, use <kbd>Ctrl + Enter</kbd>.

The above two special running methods can be used together, that is <kbd>Ctrl + Shift + Enter</kbd>.

## Build

Built using Qt version 5.15.

Configure the build target through `AltCmd.pro`.
