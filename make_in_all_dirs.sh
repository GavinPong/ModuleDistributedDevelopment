#!/bin/bash
#遇到中文会进入死循环

readfile()
{
	for file in  `ls $1`
	do
		if [ -d $1"/"$file ]	#判断是否为文件夹
		then
			#不需要编译的目录全部在这里添加
			if [[ $1"/"$file =~ "config" ]] || [[ $1"/"$file =~ "doc" ]] \
			|| [[ $1"/"$file =~ "util_tools" ]]
			then
				echo $1"/"$file was not compile......
			else
				cd $1"/"$file && make || exit "$$?"
				cd -		#回到上次回到cd前的目录，避免下次跳转时路径异常
				readfile   $1"/"$file
			fi
		fi
	done
}


shellPath=$(cd "$(dirname "$0")"; pwd)
folder="./"
readfile $folder