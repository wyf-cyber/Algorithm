# Python的输入与输出
## 一、输入
### （一）输入函数input()
**函数用途：** 函数input()主要用于接收单个输入
**函数参数：** 函数括号中可以填写输入的提示语（非必要），提示语与输入内容位于同一行
**函数功能：** 接收一整行输入，直到检测到换行符
~~~py
a = input("Please enter your name")
~~~
运行结果：
> Please enter your name
### （二）输入数据的类型
input函数会将输入默认转换成字符串类型，如果需要接收整型或浮点型变量，则需要使用类型转换函数
~~~py
# 输入字符串
a = input()
# 输入整数
b = int(input())
# 输入浮点数
c = float(input())
~~~
注意如果输入是浮点数，字符串类型的浮点数（例如"23.4"）就不能直接转成整型，否则将会出现报错
需要先将其转换成浮点数，然后再转换成整数。但字符串类型的整型（例如"23"）可以直接转换成浮点型（23.0）
~~~py
# 输入浮点数并直接舍弃小数位转换成整型
d = float(input())
d = int(d)
# 输入浮点数并将其按照四舍五入的规则转成整型
e = float(input())
e = round(e)
~~~
### （三）输入数字的进制
如果输入的数字是2进制、8进制、16进制等其他进制表示的整数，则可以使用int(num, base = 10)函数进行进制转换，int函数默认转换成10进制。此外，还有以下函数可用于进制转换
- a = hex(a) :将10进制整数转成16进制整数
- a = oct(a) :将10进制整数转成8进制整数
- a = bin(a) :将10进制整数转成2进制整数
~~~py
# 接收2进制整数
a = int(input(), 2)
# 接收8进制整数
a = int(input(), 8)
# 接收16进制整数
a = int(input(), 16)
~~~
如果输入的数是浮点数，需要转换成10进制浮点数
则可使用fromhex()函数将字符串直接转换成浮点小数
~~~py
a = "0x1.47ae51bp+3"
# 转换成10进制浮点数
a = float.fromhex(a)
~~~
### （四）接收若干个元素（数量已知）
#### 情况一 若干个元素不在同一行，以换行符间隔
使用for循环多次读取
~~~py
# 输入格式：
# 3
# 4
# 1
# 5
# 接收输入元素总数
n = int(input())
# 初始化一个空列表存储多个元素
elements = []
for i in range(n):
    a = int(input())
    elements.append(a)
~~~
#### 情况二 若干个元素在同一行
使用map()、split()实现读取，其中split()函数有一个字符串类型的参数，表示以该字符分割输入，默认值为" "，表示以空格键分割
~~~py
# 输入样例：23 4 11 55
m, n = map(int, input().split())
# 输入样例：23,4,11,55
m, n = map(int, input().split(","))
~~~
### （五）接收若干个元素（数量未知）
#### 情况一 若干元素不在同一行，以换行符间隔
使用while循环多次读取，需要设定一个结束读取的标志
~~~py
# 输入格式：
# 3
# 4
# 1
# 5
# 创建空列表
elements = []
# 设定while循环
while True:
    temp = input()
    # 如果用户没有输入，直接按下换行键则停止循环
    if not temp:
        break
    elements.append(temp)
~~~
#### 情况二 若干元素在同一行
同一行的多个元素可以使用空格键、逗号等符号间隔，可以使用split()函数将其存入列表中
~~~py
# 将数据以一整个字符串的形式存入字符串变量
elements = input()
elements_list = []
elements_list = elements.split(", ")
# 将字符串列表转换成整型列表
elements_int = [int(i) for i in elements_list] 
~~~
## 二、输出
Python的输出主要使用print()和wirte()函数
### （一） print()函数用法
> print(value1, value2, ..., sep=' ', end='\n', file=sys.stdout, flush=False)

- value:将要输出的元素
- sep:决定同一个print()函数中的各个元素之间用什么方式间隔，默认为空格' '
- end:决定该print()函数与下一个print()函数的输出之间用什么方式间隔，默认为换行符'\n'
- file:决定输出到标准输出还是指定文件，默认为标准输出
- flush: 指定是否刷新输出缓冲，默认为 False。
1. 输出单个元素
~~~py
a = 24
print(a)
~~~
1. 输出列表
print()函数可以通过读取列表名直接在一行之内输出整个列表，列表元素之间以", "分割，列表两端有方括号标明列表范围
~~~py
elements = [12,4,2,3,55]
print(elements)
# 输出结果
# [12, 4, 2, 3, 55]
~~~
1. 插入值
~~~py
name = 'student'
age = 99
# 方法一
print(f'My name is {name},and I am {age} years old.')
# 方法二
print('My name is {},and I am {} years old.'.format(name, age))
~~~
### （二） write()函数用法
write()需要指定输出为标准输出流还是文件输出流
write()也在括号中填写需要输出的内容，不同的是，write函数中换行需要借助换行符\n显式换行。
1. 标准输出流
~~~py
import sys
name = 'student'
age = 99
# 方法一
sys.stdout.write(f'My name is {name},and I am {age} years old.')
# 方法二
sys.stdout.write('My name is {},and I am {} years old.'.format(name, age))
~~~
运行结果：
> My name is student,and I am 99 years old.My name is student,and I am 99 years old.
1. 文件输出流
write()结合open()函数可以实现对其他文件的读取与修改，open()函数主要有两个参数，第一个参数是目标文件的相对路径或绝对路径，第二个参数是操作的类型mode。
mode有多个值，默认为 'r'（只读）。其他常用的模式包括 'w'（写入）、'a'（追加）、'rb'（二进制读取）等。
~~~py
name = 'student'
age = 99
with open("output.txt", "w") as file:
    file.write('My name is {},and I am {} years old.'.format(name, age))
~~~