## 2.21.1
由于须作图量较大，故使用电子档方便复制粘贴。

> **此处的调用后指的是: 调用了函数, 并执行了代码, 直到返回前或下一次调用前.**

### a.

由于a程序未使用到静态数据段, 故不作其图.

#### 栈内容

从`main`函数调用, 到`leaf_function(int f)`内部的递归调用, 总共执行了6次调用. 

##### 第1次(从`main`函数的调用)

|指针位置|内容|地址|说明|
|:-|:-|:-|:-|
|\$fp$\rightarrow$|0x0000 0001|0x7FFF FFFC|传入参数为1|
||第1次函数调用的返回地址\$ra值|0x7FFF FFFB||
||0x0000 0002|0x7FFF FFFA|下一次调用前, result值为2|

##### 第2次(从`leaf_function(int f)`函数的调用)

|指针位置|内容|地址|说明|
|:-|:-|:-|:-|
||0x0000 0001|0x7FFF FFFC|传入参数为1|
||第1次函数调用的返回地址\$ra值|0x7FFF FFFB||
||0x0000 0002|0x7FFF FFFA|下一次调用前, result值为2|
|\$fp$\rightarrow$|0x0000 0002|0x7FFF FFF9|传入参数为2|
||第2次函数调用的返回地址\$ra值|0x7FFF FFF8||
||0x0000 0003|0x7FFF FFF7|下一次调用前, result值为3|

##### 第3次(从`leaf_function(int f)`函数的调用)

|指针位置|内容|地址|说明|
|:-|:-|:-|:-|
||0x0000 0001|0x7FFF FFFC|传入参数为1|
||第1次函数调用的返回地址\$ra值|0x7FFF FFFB||
||0x0000 0002|0x7FFF FFFA|下一次调用前, result值为2|
||0x0000 0002|0x7FFF FFF9|传入参数为2|
||第2次函数调用的返回地址\$ra值|0x7FFF FFF8||
||0x0000 0003|0x7FFF FFF7|下一次调用前, result值为3|
|\$fp$\rightarrow$|0x0000 0003|0x7FFF FFF6|传入参数为3|
||第3次函数调用的返回地址\$ra值|0x7FFF FFF5||
||0x0000 0004|0x7FFF FFF4|下一次调用前, result值为4|

##### 第4次(从`leaf_function(int f)`函数的调用)

|指针位置|内容|地址|说明|
|:-|:-|:-|:-|
||0x0000 0001|0x7FFF FFFC|传入参数为1|
||第1次函数调用的返回地址\$ra值|0x7FFF FFFB||
||0x0000 0002|0x7FFF FFFA|下一次调用前, result值为2|
||0x0000 0002|0x7FFF FFF9|传入参数为2|
||第2次函数调用的返回地址\$ra值|0x7FFF FFF8||
||0x0000 0003|0x7FFF FFF7|下一次调用前, result值为3|
||0x0000 0003|0x7FFF FFF6|传入参数为3|
||第3次函数调用的返回地址\$ra值|0x7FFF FFF5||
||0x0000 0004|0x7FFF FFF4|下一次调用前, result值为4|
|\$fp$\rightarrow$|0x0000 0004|0x7FFF FFF3|传入参数为4|
||第4次函数调用的返回地址\$ra值|0x7FFF FFF2||
||0x0000 0005|0x7FFF FFF1|下一次调用前, result值为5|

##### 第5次(从`leaf_function(int f)`函数的调用)

|指针位置|内容|地址|说明|
|:-|:-|:-|:-|
||0x0000 0001|0x7FFF FFFC|传入参数为1|
||第1次函数调用的返回地址\$ra值|0x7FFF FFFB||
||0x0000 0002|0x7FFF FFFA|下一次调用前, result值为2|
||0x0000 0002|0x7FFF FFF9|传入参数为2|
||第2次函数调用的返回地址\$ra值|0x7FFF FFF8||
||0x0000 0003|0x7FFF FFF7|下一次调用前, result值为3|
||0x0000 0003|0x7FFF FFF6|传入参数为3|
||第3次函数调用的返回地址\$ra值|0x7FFF FFF5||
||0x0000 0004|0x7FFF FFF4|下一次调用前, result值为4|
||0x0000 0004|0x7FFF FFF3|传入参数为4|
||第4次函数调用的返回地址\$ra值|0x7FFF FFF2||
||0x0000 0005|0x7FFF FFF1|下一次调用前, result值为5|
|\$fp$\rightarrow$|0x0000 0005|0x7FFF FFF0|传入参数为5|
||第5次函数调用的返回地址\$ra值|0x7FFF FFEF||
||0x0000 0006|0x7FFF FFEE|下一次调用前, result值为6|

##### 第6次(从`leaf_function(int f)`函数的调用)

|指针位置|内容|地址|说明|
|:-|:-|:-|:-|
||0x0000 0001|0x7FFF FFFC|传入参数为1|
||第1次函数调用的返回地址\$ra值|0x7FFF FFFB||
||0x0000 0002|0x7FFF FFFA|下一次调用前, result值为2|
||0x0000 0002|0x7FFF FFF9|传入参数为2|
||第2次函数调用的返回地址\$ra值|0x7FFF FFF8||
||0x0000 0003|0x7FFF FFF7|下一次调用前, result值为3|
||0x0000 0003|0x7FFF FFF6|传入参数为3|
||第3次函数调用的返回地址\$ra值|0x7FFF FFF5||
||0x0000 0004|0x7FFF FFF4|下一次调用前, result值为4|
||0x0000 0004|0x7FFF FFF3|传入参数为4|
||第4次函数调用的返回地址\$ra值|0x7FFF FFF2||
||0x0000 0005|0x7FFF FFF1|下一次调用前, result值为5|
||0x0000 0005|0x7FFF FFF0|传入参数为5|
||第5次函数调用的返回地址\$ra值|0x7FFF FFEF||
||0x0000 0006|0x7FFF FFEE|下一次调用前, result值为6|
|\$fp$\rightarrow$|0x0000 0006|0x7FFF FFED|传入参数为6|
||第6次函数调用的返回地址\$ra值|0x7FFF FFEC||
||0x0000 0007|0x7FFF FFEB|下一次调用前, result值为7|


### b.

总共执行了1次函数`my_function`的调用

#### 栈数据段内容

调用后有

|指针位置|内容|地址|说明|
|:-|:-|:-|:-|
||0x0000 000A|0x7FFF FFFC|main函数中的x|
||0x0000 0014|0x7FFF FFFB|main函数中的y|
||main中z的值(未初始化, 不确定值)|0x7FFF FFFA|main函数中的z|
|\$fp$\rightarrow$|0x0000 000A|0x7FFF FFF9|传入参数x|
||0x0000 0014|0x7FFF FFF8|传入参数y|
||第1次函数调用的返回地址\$ra值|0x7FFF FFF7||

#### 静态数据段内容

|指针位置|内容|地址|说明|
|:-|:-|:-|:-|
|\$gp$\rightarrow$|0x0000 0064|0x1000 8000|my_global的值|

