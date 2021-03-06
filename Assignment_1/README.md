# 硬币面值问题
## 算法思想：
根据题目要求，首先会想到使用贪心法或回溯法（DFS深度优先搜索）解决问题。
1.贪心法：为了减少硬币的使用量，自然想到尽可能多地使用面值大的硬币。但经过仔细思考过后可以想到，当大面值硬币为较小面值硬币的整数倍时这个结论显然成立，但若有这种情况：若硬币面值有3、5、9、10四种，目标金额为18，若使用贪心算法，则会找出10+5+3这种组合方式，需要3枚硬币，但显然2枚9元硬币的组合方案更优。由此可见贪心法无法解决本题。

2.回溯法：既然贪心法难以解决问题，我们可以考虑找出满足目标面额的所有组合方案，再在其中找出需要最少硬币数的方案。而找出所有组合方案的过程正好可以使用我们最初想到的回溯法，即从面值最大的硬币开始逐步搜索至面值最小的硬币，若组合出目标面值则存储该方案所需目标数（若已存储，则取较小值）。这种思路固然可以得到本题的正确答案，但可想而知，这样的时间复杂度会很大，在搜索过程中有很多不必要的步骤。因此再对问题进行深入思考，可以联想到楼梯问题和0/1背包问题，我们可以对目标金额的组合方案进行拆分：①现有组合方案对应的硬币数；②目标金额减去某一硬币面值后的对应金额组合方案+1。以此法搜索，每次在这二者中取较小值即可得到最终答案。

为了进一步降低复杂度，我们最终使用动态规划方法解决问题，算法步骤可分为如下6步：

### ①变量定义：
假设用户输入的硬币面值有num种，目标金额为amount元，用数组coins记录这m种硬币面值，数组count记录每个金额对应方案的最少硬币数。因为这两种数组大小都不固定（分别与m、n有关），故使用动态整型数组的形式，其中count数组在第④步之后再进行定义（理由见④）。

### ②用户输入：
循环读入用户输入的硬币面值，直到用户输入-1为止（考虑到其他错误输入，故判断当用户输入非正数时即跳出循环），记录用户输入的面值种数，记为num；其后读入用户输入的目标金额，记为amount。

### ③面值排序：
动态规划时最好从面值最小的硬币数开始循环判断至面值最大的硬币数，因此事先对用户输入的num种进行升序排序，这里我们采用库函数sort直接对coins数组进行排序处理。

### ④特殊判断：
首先考虑一系列特殊输入，如目标金额amount为0时，所求最少硬币数为0；目标金额amount小于最小的硬币面值（即coins[0]）时，不存在合法的组合方案。若出现这两类情况，直接输出对应信息后结束程序即可，不需要使用count数组记录不同金额对应的硬币数，因此可以在此处尽可能地剩下部分空间。若不出现这两类情况，则定义大小为amount的动态数组count，并初始化其中元素值为0。

### ⑤动态规划：
使用两重循环，外层循环为j = 0 →(j++)  j = num，遍历num种硬币面值，此处需要进行判断，若coins[j]>amount（大于目标金额的硬币面值显然不会被使用到，又因为coins为排好序的升序数组，故循环即可就此结束）则以break结束动态规划，否则将count[coins[j]]赋值为1（硬币面值所对应的金额显然只需要其1个硬币）；内层循环为i = coins[j] →(i++)  i <= amount（小于硬币面值的金额不需要考虑），然后判断使用1枚当前面值的硬币是否为较优方案，判断语句：Ⅰ.count[i - coins[j]] > 0（即使用1枚该面值的硬币前对应的金额可以被组合出来）；Ⅱ.count[i] == 0（该金额此前还未被组合出来过）或count[i - coins[j]] + 1 < count[i]（该金额此前被组合过，且此前的组合方案对应的硬币数较多）。若以上2个条件同时成立，则将count[i - coins[j]]赋值给count[i]。以上为循环体的所有内容。

### ⑥输出结果：
判断，若count[amount]仍为0，表示该金额不存在合法的组合方案，输出-1；否则输出count[amount]即可。至此程序结束。

*注：所需库函数有：iostream、vector、algorithm*

## 算法复杂度分析：
假设用户输入的硬币面值有m种，目标金额为n元：

### 1.空间复杂度：
在较优条件下（即用户输入的目标金额显然不可组合时），除3个输入及记录用的int型变量外，只需开辟大小为m的int型数组coins用于记录用户输入的硬币面值，此时空间复杂度为O(m)；正常情况下，还需要开辟大小为n的int型数组count，此时空间复杂度为O(m+n)。

### 2.时间复杂度：
同上，在较优条件下，只需要对coins数组进行排序，此时程序的时间复杂度取决于库函数sort，即O(mlogm)；正常情况下，还需要执行动态规划部分的循环体，循环语句执行次数小于m*(n-coins[0])次，因此该循环体时间复杂度可以记为O(m*n)。综上所述，正常情况下该算法时间复杂度可以认为是O(m*n)。
