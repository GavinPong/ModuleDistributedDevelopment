#!/bin/bash
#遇到中文会进入死循环

readfile()
{
	for file in  `ls $1`
	do
		if [ -d $1"/"$file ]	#判断是否为文件夹
		then
			cd $1"/"$file && make
			cd -		#回到上次回到cd前的目录，避免下次跳转时路径异常
			readfile   $1"/"$file
		fi
	done
}
shellPath=$(cd "$(dirname "$0")"; pwd)
folder="./"
readfile $folder