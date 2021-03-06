# WordCount-c++词频统计
本次任务
本次作业分为两部分:
一、基本需求：实现一个能够对文本文件中的单词的词频进行统计的控制台程序。
二、进阶需求：在基本需求实现的基础上，编码实现顶会热词统计器。

特别说明：只要实现基本功能就有个基本分数，但是实现进阶的得到更多的分数。

一、WordCount需求
（一）WordCount基本需求
实现一个命令行程序，不妨称之为wordCount。

第一步、实现基本功能
输入文件名以命令行参数传入。例如我们在命令行窗口(cmd)中输入：

//C语言类
wordCount.exe input.txt

//Java语言
java wordCount input.txt

则会统计input.txt中的以下几个指标

统计文件的字符数：
- 只需要统计Ascii码，汉字不需考虑
- 空格，水平制表符，换行符，均算字符
统计文件的单词总数，单词：至少以4个英文字母开头，跟上字母数字符号，单词以分隔符分割，不区分大小写。
英文字母： A-Z，a-z
字母数字符号：A-Z， a-z，0-9
分割符：空格，非字母数字符号
例：file123是一个单词，123file不是一个单词。file，File和FILE是同一个单词
统计文件的有效行数：任何包含非空白字符的行，都需要统计。
统计文件中各单词的出现次数，最终只输出频率最高的10个。频率相同的单词，优先输出字典序靠前的单词。
按照字典序输出到文件result.txt：例如，windows95，windows98和windows2000同时出现时，则先输出windows2000
输出的单词统一为小写格式
输出的格式为
characters: number
words: number
lines: number
<word1>: number
<word2>: number
...

第二步、接口封装
在写了一些代码开胃之后，大家都完成了一份满足wordCount基本功能的代码。
大家的代码都各有特色，如果现在我们要把这个功能放到不同的环境中去（例如，命令行，Windows图形界面程序，网页程序，手机App），就会碰到困难：代码散落在各个函数中，很难剥离出来作为一个独立的模块运行以满足不同的需求。

同时我们也看到，不同的代码解决不同层面的问题：

有些是计算数据的（例如统计单词）
有些是控制输入的（例如scanf，cin，图形界面的输入字段）
有些是数据可视化的（例如printf，cout，println，DrawText）
有些则更为特殊，是架构相关的（例如main函数，并不是所有的程序都需要某个特定格式的main）
这些代码的种类不同，混杂在一起对于后期的维护扩展很不友好，所以它们的组织结构就需要精心的整理和优化。
我们希望把基本功能里的：

统计字符数
统计单词数
统计最多的10个单词及其词频
这三个功能独立出来，成为一个独立的模块(class library, DLL, 或其它)，这样的话，命令行和GUI的程序都能使用同一份代码。为了方便起见，我们称之为计算核心"Core模块"，这个模块至少可以在几个地方使用：

命令行测试程序使用
在单元测试框架下使用
与数据可视化部分结合使用
把计算核心在单元测试框架中做过完备的测试后，我们就可以在算法层级保证了这个模块的正确性。
但我们知道软件并非只有计算核心，实际的软件是交付给最终用户的软件，除了计算核心外，还需要有一定的界面和必要的辅助功能。
这个Core模块和使用它的其他模块之间则要通过一定的API来交流。

API应该怎么设计呢？
为了方便起见，我们可以从下面的最简单的接口开始（仅举例，你的代码里可能没有这个函数）：

int countChar(File *file)

这个函数表示输出一个文件指针，返回这个文件的字符数。
假设我们用Core封装了这个接口，那么我们的测试程序可以是这样：

File *in = fopen("input.txt","r");
int count = 100;
Assert(countChar(in) == count);

当然，这样的测试程序并不充分，希望大家测试时不要像这样偷懒。

（二）WordCount进阶需求
新增功能，并在命令行程序中支持下述命令行参数。说明：字符总数统计、单词总数统计、有效行统计要求与个人项目相同

1. 使用工具爬取论文信息

从CVPR2018官网爬取今年的论文列表，输出到result.txt(一定叫这个名字)，内容包含论文题目、摘要，格式如下：

为爬取的论文从0开始编号，编号单独一行
两篇论文间以2个空行分隔
在每行开头插入“Title: ”、“Abstract: ”（英文冒号，后有一个空格）说明接下来的内容是论文题目，或者论文摘要
后续所有字符、单词、有效行、词频统计中，论文编号及其紧跟着的换行符、分隔论文的两个换行符、“Title: ”、“Abstract: ”（英文冒号，后有一个空格）均不纳入考虑范围
可参考样例如下：

请在博客中注明你所使用的爬虫工具，并说明如何使用
如果是使用C++或Java实现的，在博客中简单解释你的思路，会有额外加分
2.自定义输入输出文件

-i 参数设定读入文件的存储路径，-o 参数设定生成文件的存储路径
格式如下：
WordCount.exe -i [file] -o [file]

一个例子如：

WordCount.exe -i input.txt -o output.txt

/*

*从input.txt读取需要统计的文本，将统计结果输出到output.txt

*/

3. 加入权重的词频统计

属于Title的单词权重为10，属于Abstract 单词权重为1
在上文图片样例中，embodied 的频率为 1x10+2x1=12。（在题目中出现1次，在摘要中出现2次，其中1次由于图片大小未能显示）
进行单词统计时依旧正常累加
-w 参数设定是否采用不同权重计数
-w 参数与数字 0|1 搭配使用，用于表示是否采用不同权重：0 表示属于 Title、Abstract 的单词权重相同均为 1 ；1 表示属于 Title 的单词权重为10，属于Abstract 单词权重为1。格式如下：
WordCount.exe -w [0|1]

一个例子如：

WordCount.exe -w 1

/*

*程序会输出input.txt中采用不同权重统计出的词频前10的单词

*/

4. 新增词组词频统计功能

统计文件夹中指定长度的词组的词频

m 个由分隔符隔开的单词组成一个词组，词组只存在于同一个字段中，即不能跨越 Title、Abstract - 组成词组
使用词组词频统计功能时，不再统计单词词频，而是统计词组词频，但不影响单词总数统计
最终只输出频率最高的10个词组，频率相同的词组，优先输出字典序靠前的词组
-m 参数设定统计的词组长度

-m 参数与数字配套使用，用于设置词组长度，格式如下：
WordCount.exe -m [number]

一个例子如：

WordCount.exe -m 3

/*

*要求程序统计长度为3的词组

*/

例：输入文件中内容为：

0

Title: Monday Tuesday Wednesday Thursday

Abstract: Friday

则输出如下：

characters: 40

words: 5

lines: 2

<monday tuesday wednesday>: 1

<tuesday wednesday thursday>: 1

5. 自定义词频统计输出

用户指定输出前 n 多的单词(词组)与其频数

-n 参数设定输出的单词数量

-n 参数与数字搭配使用，用于限制最终输出的单词(词组)的个数，表示输出频数最多的前 [number] 个单词(词组)，0 ≤ [number] ≤ 100格式如下:

WordCount.exe -n [number]

一个例子如：

WordCount.exe -n 1

/*

*输出文件中出现次数最多的那个单词

*/

6. 多参数的混合使用
实际测试时，在一句命令行语句中

-i 、-o 、-w 参数一定会出现

-m、-n 参数可能都不出现，可能只出现一个，也可能都出现

未出现 -m 参数时，不启用词组词频统计功能，默认对单词进行词频统计

未出现 -n 参数时，不启用自定义词频统计输出功能，默认输出10个

参数之间的顺序并不固定

一个完整例子如下：
WordCount.exe -i input.txt -m 3 -n 3 -w 1 -o output.txt

/*

*统计input.txt文件中的字符数、单词数、有效行数、出现次数排在前3的3个单词长的词组，并采用权重累>计频数，最终统计结果输出到output.txt

*/

例：输入文件中内容为：

0

Title: Monday Tuesday Wednesday Thursday

Abstract: Monday Tuesday Wednesday Thursday Friday

则输出如下：

characters: 74

words: 9

lines: 2

<monday tuesday wednesday>: 11

<tuesday wednesday thursday>: 11

<wednesday thursday friday>: 1

7. 附加题（20'）
本部分不参与自动化测试，如有完成，需在博客中详细描述，并在博客中附件（.exe及.txt）为证。附加功能的加入不能影响上述基础功能的测试，分数取决于创意和所展示的完成度，创意没有天花板，这里不提出任何限制，尽你们所能去完成。

要求：结合结对原型设计，发挥个人的奇思妙想，对论文列表进行更多的挖掘并进行数据分析，为你们举几个例子：

从网站综合爬取论文的除题目、摘要外其他信息
如：论文类型、作者、作者单位等等
分析论文作者的所属地， 哪些国家、哪些高校发表的论文比较多

分析论文列表中各位作者之间的关系，论文A的第一作者可能同时是论文B的第二作者，不同论文多位作者之间可能存在着联系

对数据的图形可视化做出一些努力，比如对上一条功能可以形成关系图谱
