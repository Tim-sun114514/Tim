# Linux基本指令

## 1 . ls 指令

​	语法： ls [ 选项 ] [ ⽬录或文件 ]

​	功能：对于⽬录，该命令列出该⽬录下的所有⼦⽬录与⽂件。对于⽂件，将列出⽂件名以及其他信息。

	[root@VM-0-9-centos ~]# ls
	a.txt  tim

​	-a列出⽬录下的所有⽂件，包括以.开头的隐含⽂件。

	[root@VM-0-9-centos ~]# ls -a
	.   a.txt          .bash_logout   .bashrc  .config  .pip  .pydistutils.cfg  .tcshrc  .viminfo
	..  .bash_history  .bash_profile  .cache   .cshrc   .pki  .ssh              tim
​	-l列出⽂件的详细信息，也可以省略成 -ll

	[root@VM-0-9-centos tim]# ls -l
	total 12
	-rw-r--r-- 1 root root    6 Apr 15 13:25 1
	-rw-r--r-- 1 root root    0 Apr 14 21:17 a-copy.txt
	-rw-r--r-- 1 root root  125 Apr 14 21:43 a.txt
	drwxr-xr-x 2 root root 4096 Apr 14 21:17 dir
	[root@VM-0-9-centos tim]# ll
	total 12
	-rw-r--r-- 1 root root    6 Apr 15 13:25 1
	-rw-r--r-- 1 root root    0 Apr 14 21:17 a-copy.txt
	-rw-r--r-- 1 root root  125 Apr 14 21:43 a.txt
	drwxr-xr-x 2 root root 4096 Apr 14 21:17 dir
​	-r对⽬录反向排序

	[root@VM-0-9-centos tim]# ls -r
	dir  a.txt  a-copy.txt  1
	[root@VM-0-9-centos tim]# ls
	1  a-copy.txt  a.txt  dir
​	-t以时间排序

​	-s在l⽂件名后输出该⽂件的⼤⼩。（⼤⼩排序，如何找到⽬录下最⼤的⽂件）

​	-R列出所有⼦⽬录下的⽂件。(递归)

​	-1⼀⾏只输出⼀个⽂件。

## 2 . pwd指令

 	功能：显示用户当前所在的⽬录

```
[root@VM-0-9-centos tim]# pwd
/root/tim
```



## 3. cd 指令

​	Linux理论知识：路径的认识

![image-20260419211223220](C:\Users\1\AppData\Roaming\Typora\typora-user-images\image-20260419211223220.png)

![image-20260419211303855](C:\Users\1\AppData\Roaming\Typora\typora-user-images\image-20260419211303855.png)

​	语法: cd  ⽬录名 

​	功能：改变工作目录。将当前⼯作⽬录改变到指定的⽬录下

```
[root@VM-0-9-centos tim]# cd dir
[root@VM-0-9-centos dir]# 
```

可以看到工作目录由tim变为了dir

​	返回上级目录

```
[root@VM-0-9-centos dir]# pwd
/root/tim/dir
[root@VM-0-9-centos dir]# cd ..
[root@VM-0-9-centos tim]# pwd
/root/tim
```

​	每个文件中都有会初始化有两个文件   **.**   和   **.. ** 

```
[root@VM-0-9-centos tim]# ls -a
.  ..  1  a-copy.txt  a.txt  dir
```

​	. 文件代表当前文件

​	.. 文件代表上一个文件

​	因此cd .. 才能返回上级文件

​	绝对路径定位目录或文件

```
[root@VM-0-9-centos /]# pwd
/
[root@VM-0-9-centos /]# cd /root/tim
[root@VM-0-9-centos tim]# pwd
/root/tim
```

​	相对路径定位目录或文件

```
[root@VM-0-9-centos tim]# cd ./dir
[root@VM-0-9-centos dir]# pwd
/root/tim/dir
```

​	快速进入自己的家目录

```
[root@VM-0-9-centos dir]# whoami
root
[root@VM-0-9-centos dir]# cd ~
[root@VM-0-9-centos ~]# pwd
/root
```

​	返回到最近访问目录

```
[root@VM-0-9-centos tim]# pwd
/root/tim
[root@VM-0-9-centos tim]# cd /
[root@VM-0-9-centos /]# pwd
/
[root@VM-0-9-centos /]# cd -
/root/tim
[root@VM-0-9-centos tim]# pwd
/root/tim
```

## 	4 . touch 指令

​	语法: touch [ 选项 ]  ⽂件  

​	功能: touch命令参数可更改⽂档或⽬录的⽇期时间，包括存取时间和更改时间，或者新建⼀个不存在的⽂件。

​	创建普通文件

```
[root@VM-0-9-centos tim]# ll
total 12
-rw-r--r-- 1 root root    6 Apr 15 13:25 1
-rw-r--r-- 1 root root    0 Apr 14 21:17 a-copy.txt
-rw-r--r-- 1 root root  125 Apr 14 21:43 a.txt
drwxr-xr-x 2 root root 4096 Apr 14 21:17 dir
[root@VM-0-9-centos tim]# touch test.txt
[root@VM-0-9-centos tim]# ll
total 12
-rw-r--r-- 1 root root    6 Apr 15 13:25 1
-rw-r--r-- 1 root root    0 Apr 14 21:17 a-copy.txt
-rw-r--r-- 1 root root  125 Apr 14 21:43 a.txt
drwxr-xr-x 2 root root 4096 Apr 14 21:17 dir
-rw-r--r-- 1 root root    0 Apr 19 21:31 test.txt
```

​	成功新建了test.txt文件

​	-a: change only the access time

​	-c: change only the modification time

## 5 . mkdir指令

​	语法：mkdir  [ 选项 ]  dirname

​	功能：在当前⽬录下创建⼀个名为“dirname”的⽬录

```
[root@VM-0-9-centos ~]# mkdir newdir
[root@VM-0-9-centos ~]# ll
total 36
-rw-r--r-- 1 root root 9890 Apr 20 18:46 a.txt
drwxr-xr-x 2 root root 4096 Apr 20 22:02 newdir
-rwxr-xr-x 1 root root 8360 Apr 20 18:45 test
-rw-r--r-- 1 root root  106 Apr 20 18:45 test.c
drwxr-xr-x 3 root root 4096 Apr 20 18:35 tim
```

​	可以看到新建了一个newdir目录文件

​	-p  选项也可以递归建立多个目录，创建指定路径

```
[root@VM-0-9-centos ~]# mkdir -p a1/a2/a3/a4/a5
[root@VM-0-9-centos ~]# tree a1
a1
└── a2
    └── a3
        └── a4
            └── a5

4 directories, 0 files
```

​	![image-20260420220558162](C:\Users\1\AppData\Roaming\Typora\typora-user-images\image-20260420220558162.png)

## 6 . rmdir & rm 指令

​	rmdir是一个与mkdir相反的指令，mkdir是创建目录，rmdir是删除目录

​	语法：rmdir [ -p ] dirname

​	适用对象：具有当前目录操作权限的所有使用者

​	功能：删除空目录

```
[root@VM-0-9-centos ~]# ls
a1  a.txt  newdir  test  test.c  tim
[root@VM-0-9-centos ~]# rmdir newdir
[root@VM-0-9-centos ~]# ls
a1  a.txt  test  test.c  tim
```

​	-p选项：当子目录被删除后如果父目录变为空目录的话，连带父目录也一块删除

```
[root@VM-0-9-centos ~]# tree a1
a1
└── a2
    └── a3
        └── a4
            └── a5

4 directories, 0 files
[root@VM-0-9-centos ~]# rmdir -p a1/a2/a3/a4/a5
[root@VM-0-9-centos ~]# ls
a.txt  test  test.c  tim
```

​	**rm命令可以同时删除文件和目录**

​	语法： rm [选项] [dirname/dir]

​	使用对象： 所有使用者

​	功能： 删除文件或目录

```
[root@VM-0-9-centos ~]# touch newfile
[root@VM-0-9-centos ~]# ls
a.txt  newfile  test  test.c  tim
[root@VM-0-9-centos ~]# rm newfile
rm: remove regular empty file ‘newfile’? y    /// y 指的是 yes
[root@VM-0-9-centos ~]# ls
a.txt  test  test.c  tim
```

​	-r 选项 删除目录及其下所有文件( 递归删除 )

```
[root@VM-0-9-centos ~]# tree newdir
newdir
└── file.txt

0 directories, 1 file
[root@VM-0-9-centos ~]# rm -r newdir
rm: descend into directory ‘newdir’? y
rm: remove regular empty file ‘newdir/file.txt’? y
rm: remove directory ‘newdir’? y
[root@VM-0-9-centos ~]# ls
a.txt  file.txt  test  test.c  tim
```

​	-i 选项 删除普通文件前询问

```
[root@VM-0-9-centos ~]# ls
a.txt  file.txt  test  test.c  tim
[root@VM-0-9-centos ~]# rm -i file.txt 
rm: remove regular empty file ‘file.txt’? y
[root@VM-0-9-centos ~]# ls
a.txt  test  test.c  tim
```

​	-f选项 强制删除不询问

```
[root@VM-0-9-centos ~]# clear
[root@VM-0-9-centos ~]# ls
a.txt  test  test.c  tim
[root@VM-0-9-centos ~]# rm -f a.txt 
[root@VM-0-9-centos ~]# ls
test  test.c  tim
```

​	还可以组合使用

​	-rf 递归强制删除非空目录

​	-ri 询问删除目录

## 7 . man 指令

  	linux的命令有很多参数，我们不可能全记住，可以通过查看联机手册来获得帮助

​	语法：man [选项] 命令

![image-20260421205005418](C:\Users\1\AppData\Roaming\Typora\typora-user-images\image-20260421205005418.png)



## 8 . cp指令

​	语法：cp   [选项]  源文件或目录   目标文件或目录

​	功能：复制文件或目录

```
[root@VM-0-9-centos ~]# ls
test  test.c  tim
[root@VM-0-9-centos ~]# ls ./tim
1  a-copy.txt  a.txt  dir  test.txt
[root@VM-0-9-centos ~]# cp test.c ./tim
[root@VM-0-9-centos ~]# ls ./tim
1  a-copy.txt  a.txt  dir  test.c  test.txt
```

​	如果同时指定两个以上的文件或目录，且最后的目的地是已经存在的目录，则他会把前面的所有文件或目录复制到目的地中

​	-f或--force强行复制文件或目录，不论目的文件或目录是否已经存在

​	-i或--interactive 覆盖文件之前先询问用户

```
[root@VM-0-9-centos tim]# cat ../test.c
#include<stdio.h>
int main()
{
  int a = 1000;
  while(a--)
    printf("hello %d\n", a);
  return 0;
}
[root@VM-0-9-centos tim]# cp -i ../test.c test.c
cp: overwrite ‘test.c’? y
[root@VM-0-9-centos tim]# cat test.c 
#include<stdio.h>
int main()
{
  int a = 1000;
  while(a--)
    printf("hello %d\n", a);
  return 0;
}
```

​	-r递归处理，将指定目录下的文件与子目录⼀并处理。若源文件或目录的形态，不属于目录或符号链接，则⼀律视为普通⽂件处理

```
[root@VM-0-9-centos tim]# ls
1  dir  test.c
[root@VM-0-9-centos tim]# tree dir
dir
├── a-copy.txt
└── a.txt
[root@VM-0-9-centos tim]# cp -r dir ../dir
[root@VM-0-9-centos tim]# ls
1  dir  test.c
[root@VM-0-9-centos tim]# ls ../
dir  test  test.c  tim
[root@VM-0-9-centos tim]# tree ../dir
../dir
├── a-copy.txt
└── a.txt
```

