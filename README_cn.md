# AltCmd

这是一个可以让你在任何地方优雅地运行shell的小工具。

![](imgs/001.png#gh-light-mode-only)

![](imgs/002.png#gh-dark-mode-only)

## 如何使用

启动可执行文件，软件将在后台运行。

在任何地方按下<kbd>Alt + Space</kbd>激活命令窗口，输入命令，按下<kbd>Enter</kbd>即可。

注意，命令默认的运行目录为用户主目录。

如果想要以管理员身份运行命令，可以使用<kbd>Shift + Enter</kbd>。

如果想显示运行窗口，使用<kbd>Ctrl + Enter</kbd>。

上面两个特殊的运行方式可以一起使用，及<kbd>Ctrl + Shift + Enter</kbd>。

## 构建

使用Qt5.15版本构建。

通过`AltCmd.pro`配置构建目标即可。

