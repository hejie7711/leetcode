# 最长回文子字符串 第一部

http://leetcode.com/2011/11/longest-palindromic-substring-part-i.html

> 给定一个字符串S，找出S中最长的回文子字符串。

这道有趣的题目已经成为著名的Greplin http://baike.baidu.com/view/5302414.htm?fr=iciba 编程挑战的专题，而且多次在面试中被问起。为什么？因为该题有多少解法。我知道的解法就有5种。你准备接受挑战吗？

## 提示
首先，确保你明白回文的意思。回文是一个字符串，正着读反着读都一样。比如，aba是一个回文，abc就不是。

## 通病
试图想出快速解法的，都不幸的答错了（但是很容易被纠正）：

```
反转S变成S’。找出S和S’最长的公共子字符串 http://en.wikipedia.org/wiki/Longest_common_substring 就是最长回文子字符串。
```

看上去可以工作，让我们看下面的例子。

例如，
S = “caba” S’ = “abac”
S和S’最长的公共子字符串是“aba”。

让我们试试另一个例子：
S = “abacdfgdcaba” S’ = “abacdgfdcaba”
S和S’最长的公共子字符串是“abacd”。很明显这不是一个回文。

我们发现只要在S中存在一个反转的非回文子字符串，最长公共子字符串的解法就失败了。修正该解法，每次我们找到一个最长公共子字符串，我们检查一下该子字符串和反转子字符串之前的原始字符串是否一样。如果一样，我们更新当前找到的最长公共子字符串；如果不一样，我们跳过它寻找下一个。

该解法时间复杂度是O(N2)使用O(N2)空间（可以改进只使用O(N)空间）。请阅读最长公共子字符串 http://en.wikipedia.org/wiki/Longest_common_substring

## 暴力解法，时间复杂度O(N3)
暴力解法就是穷举所有可能的子字符串的起止位置，然后挨个检查是否是回文。总共C(N, 2)子字符串（单个字符除外，它不算回文）。

挨个检查每个子字符串的时间复杂度是O(N)，运行时复杂度是O(N3)。

## 动态编程解法 O(N2)时间复杂度 O(N2)空间复杂度
改进数据处理的暴力解法，首先考虑我们如何省去检查是否是回文的不必要的重复计算。考虑“ababa”。如果我们已经知道“bab”是回文，很明显“ababa”肯定是回文，因为左右两端的字母是一样的。

公式化如下所示：

```
定义P[ i, j ] ← true 如果子字符串Si … Sj是回文，否则false.
```

所以，

```
P[ i, j ] ← ( P[ i+1, j-1 ] && Si = Sj )
```

基本如下：

```
P[ i, i ] ← true
P[ i, i+1 ] ← ( Si = Si+1 )
```

这就产生了一个直接的数据处理解法，我们首先初始化一个和两个字母的回文，然后找出所有三个字母的回文，N个...

时间复杂度O(N2)，空间复杂度O(N2)

```
string longestPalindromeDP(string s) {
    int n = s.length();
    int longestBegin = 0;
    int maxLen = 1;
    bool table[1000][1000] = {false};
    for (int i = 0; i < n; i++) 
        table[i][i] = true;
    for (int i = 0; i < n-1; i++) {
        if (s[i] == s[i+1]) {
            table[i][i+1] = true;
            longestBegin = i;
            maxLen = 2;
        }
    }
    for (int len = 3; len <= n; len++) {
        for (int i = 0; i < n-len+1; i++) {
            int j = i + len - 1;
            if (s[i] == s[j] && table[i+1][j-1]) {
                table[i][j] = true;
                longestBegin = i;
                maxLen = len;
            }
        }
    }
    return s.substr(longestBegin, maxLen);
}
```

## 附加题
你能改进上面的解法，如何减少空间复杂度？

## 一个更加简单的解法O(N2)时间复杂度O(1)空间复杂度
实际上，我们可以在O(N2)时间复杂度，不使用额外空间的前提下解题。

我们发现一个回文是中心点对称的。所以，一个回文可以由中心点扩展，而且只有2N - 1个中心点。

你可能会问为什么有2N - 1个中心点，而不是N个？这是因为一个回文的中心点可能在两个字母之间。有偶数个字母的回文（比如“abba”）它的中心点在两个b之间。

由回文中心点扩展开来，时间复杂度变为O(N)，总复杂度是O(N2)。

```
string expandAroundCenter(string s, int c1, int c2) {
    int l = c1, r = c2;
    int n = s.length();
    while (l >= 0 && r <= n-1 && s[l] == s[r]) {
        l--;
        r++;
    }
    return s.substr(l+1, r-l-1);
}
 
string longestPalindromeSimple(string s) {
    int n = s.length();
    if (n == 0) return "";
    string longest = s.substr(0, 1);  // 单个字符本身是个回文
    for (int i = 0; i < n-1; i++) {
        string p1 = expandAroundCenter(s, i, i);
        if (p1.length() > longest.length())
            longest = p1;
 
        string p2 = expandAroundCenter(s, i, i+1);
        if (p2.length() > longest.length())
            longest = p2;
    }
    return longest;
}
```

## 进一步思考
是否存在O(N)的解法？你打赌！但是，它需要非常聪明的洞察力。第二部 https://github.com/xiangzhai/leetcode/blob/master/question/longest-palindromic-substring-part-ii.md 将讲解O(N)的解法。
