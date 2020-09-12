# InferenceEngine

[![License: MIT](https://img.shields.io/badge/License-MIT-blue.svg)](https://github.com/RabbitWhite1/USTC-Health-Report/blob/master/LICENSE)

数理方程推理机(效率比较低, 稍微复杂一点的推理就很久都出不来) 有诸多不完善的地方

一些示例公式[见此处](https://github.com/RabbitWhite1/InferenceEngine/blob/master/InputData.md)

## 使用方法

以练习3中3.5°为例

首先运行程序
```shell script
python main.c
```

根据提示输入目标公式及前提集
```shell script
Please input the target formula: q->(p->r)
Please input the premise set one by one(enter to ignore): p->(q->r)
Please input the premise set one by one(enter to ignore): 
Your target is: q->(p->r)
Your given premise set: {p->(q->r)}
Computing Begin!
(  1°)	q->(p->q)	[l1]
(  2°)	p->(q->r)	[known]
(  3°)	(p->(q->r))->((p->q)->(p->r))	[l2]
(  4°)	(p->q)->(p->r)	[MP 2°, 3°]
(  5°)	((p->q)->(p->r))->(q->((p->q)->(p->r)))	[l1]
(  6°)	q->((p->q)->(p->r))	[MP 4°, 5°]
(  7°)	(q->((p->q)->(p->r)))->((q->(p->q))->(q->(p->r)))	[l2]
(  8°)	(q->(p->q))->(q->(p->r))	[MP 6°, 7°]
(  9°)	q->(p->r)	[MP 1°, 8°]

Time Spent: 107.91982746124268 s
```

即可得到结果.

如果输入的公式有问题, 比如{!p} |- p, 就会直接报错
```shell script
The Truth Value isn't True!
```