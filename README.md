---
layout : life
title: 基于Qt和VLC的音乐播放器
wangyiyun: true
date : 2016-03-24
---

******

    作者:鹅卵石
    时间:2016年03月24日20:38:09
    版本:V 0.0.0
    邮箱:kevinlq@yeah.net

<!-- more -->


# 基于Qt和VLC的音乐播放器

## 环境
	* windows 10 64位
	* ubuntu 14.04 32位
	* Qt4.8.6(mingw32)

## 效果展示

![效果](/image/project.png)

## 功能

1. 自定义标题栏
2. 自定义底部工具栏
3. 自定义鼠标右键菜单
4. 封装第三方库VLC，可以方便进行控制音乐播放、暂停、下一首、上一首
5. windows、ubuntu 14.04上测试通过。

## 注意


程序编译后，将file文件夹中所有的文件拷贝到可执行程序bin/目录下