# 最长回文子字符串 第二部

http://leetcode.com/2011/11/longest-palindromic-substring-part-ii.html

> 给定一个字符串S，找出S中最长的回文子字符串。

## 注意
这是最长回文子字符串 https://github.com/xiangzhai/leetcode/blob/master/question/longest-palindromic-substring-part-i.md 的第二部。这里，我们要描述Manacher算法，可以在线性时间内找出最长回文子字符串。请阅读第一部 https://github.com/xiangzhai/leetcode/blob/master/question/longest-palindromic-substring-part-i.md 了解更多内幕。

Manacher http://en.wikipedia.org/wiki/Longest_palindromic_substring#CITEREFManacher1975

![ScreenShot](https://raw.github.com/xiangzhai/leetcode/master/image/ManG490.jpg)

## 提示
思考如何改进O(N^2)时间复杂度的算法。考虑最坏的情况。最坏的情况是输入了多个重复的回文。举个例子，输入："aaaaaaaaa" 和 “cabcbabcbabcba”。事实上，我们应该利用回文的对称属性，减少一些不必要的计算量。

## 一个O(N)时间复杂度解法（Manacher算法）
首先，我们在输入的字符串S的每个字符之间添加一个特殊字符#，转换成另一个字符串T。这样做的原因马上揭晓。

举个例子 S = “abaaba” T = “#a#b#a#a#b#a#”

为了寻找最长回文子字符串，我们需要扩展Ti，比如Ti - d...Ti + d，以Ti为中心，d为半径的圆，构成一个回文。d就是以Ti为中心的回文长度。

我们把中间结果存到数组P中，那么P[i]就等于以Ti为中心的回文长度。最长回文子字符串就是P中最大的元素。

使用上面的例子，我们填充P如下所示（从左向右）：

```
T = # a # b # a # a # b # a #
P = 0 1 0 3 0 1 6 1 0 3 0 1 0
```

看P我们立马找到最长回文"abaaba"，如P6 = 6所示。

在字母之间插入特殊字符#，可以优雅地处理奇数、偶数长度的回文。（请注意：这是为了更方便地论证解题思路，不需要码代码。）

现在，想像在回文"abaaba"的中间画一条竖线。数组P中的数字是中心轴对称的。再测试另一个回文"aba"，数组中的数字依旧具有相似的轴对称属性。这是巧合吗？在某一特定条件下是这样的，但是，我们至少没有重复计算P[i]，这就是个优化。

让我们看一个稍微有点复杂的例子，有很多重复的回文，比如S = "babcbabcbaccba"

![ScreenShot](https://raw.github.com/xiangzhai/leetcode/master/image/palindrome_table10.png) 

上面图片的T由S = "babcbabcbaccba"转换而来。假设你单步调试到数组P暂停在（比如P[i] < P[N]）。竖实线是回文"babcbabcbaccba"的中心C。两个竖虚线是左L右R边界。你单步调试到索引i轴对称的i’。怎样才能高效地计算出P[i]呢？

假设我们已经单步跟踪到索引i = 13，我们需要计算出P[13]（如蓝色问号所示的位置）。我们首先查看在回文中心旁边，它的镜像索引i’，即索引i’ = 9

![ScreenShot](https://raw.github.com/xiangzhai/leetcode/master/image/palindrome_table11.png) 

上面的两条绿实线表示中心点i和i’的两个回文的重叠区域。我们看中心点C附近的索引i的镜像i’。P[i'] = P[9] = 1。因为回文中心轴对称属性，P[i]也应该等于1。综上所述，很明显P[i] = P[i'] = 1。事实上，中心C之后的P[12] = P[10] = 0, P[13] = P[9] = 1, P[14] = P[8] = 0都满足该特性。

![ScreenShot](https://raw.github.com/xiangzhai/leetcode/master/image/palindrome_table4.png)

现在我们单步跟踪到索引i = 15。P[i]的值是多少呢？如果我们遵循对称属性，P[i] = P[i'] = 7。但是这就错了。如果我们以T15为中心，构成回文“a#b#c#b#a”，实际上比中心T11的短。为什么？

![ScreenShot](https://raw.github.com/xiangzhai/leetcode/master/image/palindrome_table5.png)

彩色线段重叠在以索引i和i’中心周围。绿实线所表示的区域是以中心C轴对称必须匹配的两条边。红实线所表示的两条边就不一定匹配了。绿虚线所表示的穿越中心的区域。

在两个绿实线区域内的两个子字符串必须完全匹配。穿越中心的区域（绿虚线所示）也必须相对称。注意P[i'] = 7而且所有穿越左边L的回文（红实线所示），就不再遵循回文的对称属性。我们知道的是P[i] ≥ 5，为了找到P[i]的实际值，我们需要扩展右边R来做字符匹配。当P[21] ≠ P[1]这种情况下，我们得出结论P[i] = 5。

让我们概括该算法的精髓如下：

```
if P[ i' ] ≤ R – i,
then P[ i ] ← P[ i' ]
else P[ i ] ≥ P[ i' ] 这里我们需要扩展右边R来找到P[i]
```

该算法是如此的简洁。如果可以抓到上述要害，就完全领悟了该算法的精髓，也是最难理解的部分。

最后我们就要决定何时同时向右移动C和R的坐标：

```
如果回文的中心i越过了R，我们就将C更新成i，（该回文的新中心），然后把R扩展到新回文的右边。
```

论时间复杂度，有两种可能性。如果P[i] ≤ R – i，只需一步，我们设P[i]为P[i']。否则，我们从右边R扩展，改变回文的中心变为i。扩展R（线性while循环）需要花费N步，而且确定坐标也需要花费N步。所以，该算法确保在2*N步内，提供了线性时间复杂度的解法。

```
// 将S转换成T
// 比如，S = "abba", T = "^#a#b#b#a#$"
// ^和$符号用来表示开始和结束。 
string preProcess(string s) 
{
    int n = s.length();
    if (n == 0) return "^$";
    string ret = "^";
    for (int i = 0; i < n; i++)
        ret += "#" + s.substr(i, 1);
 
    ret += "#$";
    return ret;
}
 
string longestPalindrome(string s) 
{
    string T = preProcess(s);
    int n = T.length();
    int* P = new int[n];
    int C = 0, R = 0;
    for (int i = 1; i < n - 1; i++) {
        int i_mirror = 2 * C - i; // 等于i' = C - (i-C)
    
    P[i] = (R > i) ? min(R-i, P[i_mirror]) : 0;
    
    // 扩展回文中心变为i
    while (T[i + 1 + P[i]] == T[i - 1 - P[i]])
        P[i]++;
 
    // 如果回文中心i超越了R，调整回文的中心
    if (i + P[i] > R) {
        C = i;
        R = i + P[i];
        }
    }
 
    // 找出P中的最大值
    int maxLen = 0;
    int centerIndex = 0;
    for (int i = 1; i < n-1; i++) {
        if (P[i] > maxLen) {
            maxLen = P[i];
            centerIndex = i;
        }
    }
    delete[] P;
  
    return s.substr((centerIndex - 1 - maxLen)/2, maxLen);
}
```

## 注意
该算法是不凡的，在面试过程中，你可能想不起来该算法。但是，我希望你喜欢阅读这篇文章，有助于理解这个有趣的算法。

## 进一步思考
事实上，针对该题还有第六种解法——使用后缀树。但是，它并不高效O(N log N)，而且构造后缀树的开销也很大，实践起来也更加复杂。如果你感兴趣，可以阅读维基百科有关最长回文子字符串的文章。
如果让你找出最长回文序列？（你知道子字符串和序列的区别吗？）

## 有用的链接
* Manacher算法O(N)求字符串的最长回文子串 http://www.felix021.com/blog/read.php?2040
* [需要翻墙]一个简单的找最长回文子字符串的线性时间复杂度算法 http://zhuhongcheng.wordpress.com/2009/08/02/a-simple-linear-time-algorithm-for-finding-longest-palindrome-sub-string/
* [需要翻墙]寻找回文 http://johanjeuring.blogspot.com/2007/08/finding-palindromes.html
* 在线性时间内寻找最长回文子字符串 http://www.akalin.cx/longest-palindrome-linear-time
* 维基百科：最长回文子字符串 http://en.wikipedia.org/wiki/Longest_palindromic_substring
