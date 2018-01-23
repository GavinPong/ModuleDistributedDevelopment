#!/bin/bash
#遇到中文会进入死循环
readfile()
{
	for file in  `ls $1`
	do
		if [ -d $1"/"$file ]	#判断是否为文件夹
		then
			find $1"/"$file -name "*.o"  #输出所有*.o文件
			find $1"/"$file -name "*.d"  #输出所有*.d文件
			find $1"/"$file -name "*.o"  | xargs  rm -f    #强制删除所有*.o文件
			find $1"/"$file -name "*.d"  | xargs  rm -f    #强制删除所有*.d文件
			readfile   $1"/"$file
		else
			find $1 -name "*.o"  #输出所有*.o文件
			find $1 -name "*.d"  #输出所有*.d文件
			find $1 -name "*.o"  | xargs  rm -f    #强制删除所有*.o文件
			find $1 -name "*.d"  | xargs  rm -f    #强制删除所有*.d文件
		fi
	done
}

folder="./"
readfile $folder