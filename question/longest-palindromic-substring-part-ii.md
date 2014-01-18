# 最长回文子字符串 第二部

> 给定一个字符串S，找出S中最长的回文子字符串。

## 注意
这是[最长回文子字符串]: http://leetcode.com/2011/11/longest-palindromic-substring-part-i.html 的第二部。这里，我们要描述Manacher算法，可以在线性时间内找出最长回文子字符串。请阅读[第一部]: http://leetcode.com/2011/11/longest-palindromic-substring-part-i.html 了解更多的内幕。

[Manacher]: http://en.wikipedia.org/wiki/Longest_palindromic_substring#CITEREFManacher1975

![ScreenShot](https://raw.github.com/xiangzhai/leetcode/master/image/ManG490.jpg)

## 提示
思考如何改进比O(N^2)复杂度更简单的算法。考虑最坏情况。最坏的情况是输入了多个盘根错节的回文。举个例子，输入："aaaaaaaaa" 和 “cabcbabcbabcba”。事实上，我们应该利用回文的对称属性，减少一些不必要的计算量。

## 一个O(N)复杂度答案（Manacher算法）
首先，我们在输入的字符串S的每个字符之间添加一个特殊字符'#'，转换成另一个字符串T。这样做的原因马上揭晓。

举个例子 S = “abaaba” T = “#a#b#a#a#b#a#”

为了寻找最长回文子字符串，我们需要扩展Ti，比如Ti - d...Ti + d，以Ti为圆心，d为半径的圆，构成一个回文。d就是以Ti为圆心的回文长度。

我们把中间结果存到数组P中，那么P[i]就等于以Ti为圆心的回文长度。最长回文子字符串就是P中最大的元素。

使用上面的例子，我们填充P如下所示（从左向右）：

```
T = # a # b # a # a # b # a #
P = 0 1 0 3 0 1 6 1 0 3 0 1 0
```

看P我们立马找到最长回文是"abaaba"，如P6 = 6所示。

在字母之间插入特殊字符#，可以优雅地处理奇数、偶数长度的回文。（请注意：这是为了更方便地论证解题思路，不需要码代码。）

现在，想像一下在回文"abaaba"的中间画一条竖线。数组P中的数字是中心轴对称的。再试另一个回文"aba"，数组中的数字依旧具有相似的轴对称属性。这是巧合吗？在某一特定条件下是这样的，但是，无论如何，我们没有重复计算P[i]，这就是个进步。

让我们看一个稍微有点复杂的例子，有很多盘根错节的回文，比如S = "babcbabcbaccba"。

![ScreenShot](https://raw.github.com/xiangzhai/leetcode/master/image/palindrome_table10.png) 

上面图片的T由S = "babcbabcbaccba"转换而来。假设你单步调试到数组P部分形成的状态（比如P[i] < P[N]）。竖实线是回文"babcbabcbaccba"的圆心C。两个竖虚线是左L右R边界。你单步调试到索引i轴对称的i’。怎样才能高效地计算P[i]呢？

Assume that we have arrived at index i = 13, and we need to calculate P[ 13 ] (indicated by the question mark ?). We first look at its mirrored index i’ around the palindrome’s center C, which is index i’ = 9.


The two green solid lines above indicate the covered region by the two palindromes centered at i and i’. We look at the mirrored index of i around C, which is index i’. P[ i' ] = P[ 9 ] = 1. It is clear that P[ i ] must also be 1, due to the symmetric property of a palindrome around its center.
As you can see above, it is very obvious that P[ i ] = P[ i' ] = 1, which must be true due to the symmetric property around a palindrome’s center. In fact, all three elements after C follow the symmetric property (that is, P[ 12 ] = P[ 10 ] = 0, P[ 13 ] = P[ 9 ] = 1, P[ 14 ] = P[ 8 ] = 0).


Now we are at index i = 15, and its mirrored index around C is i’ = 7. Is P[ 15 ] = P[ 7 ] = 7?
Now we are at index i = 15. What’s the value of P[ i ]? If we follow the symmetric property, the value of P[ i ] should be the same as P[ i' ] = 7. But this is wrong. If we expand around the center at T15, it forms the palindrome “a#b#c#b#a”, which is actually shorter than what is indicated by its symmetric counterpart. Why?


Colored lines are overlaid around the center at index i and i’. Solid green lines show the region that must match for both sides due to symmetric property around C. Solid red lines show the region that might not match for both sides. Dotted green lines show the region that crosses over the center.
It is clear that the two substrings in the region indicated by the two solid green lines must match exactly. Areas across the center (indicated by dotted green lines) must also be symmetric. Notice carefully that P[ i ' ] is 7 and it expands all the way across the left edge (L) of the palindrome (indicated by the solid red lines), which does not fall under the symmetric property of the palindrome anymore. All we know is P[ i ] ≥ 5, and to find the real value of P[ i ] we have to do character matching by expanding past the right edge (R). In this case, since P[ 21 ] ≠ P[ 1 ], we conclude that P[ i ] = 5.

Let’s summarize the key part of this algorithm as below:

if P[ i' ] ≤ R – i,
then P[ i ] ← P[ i' ]
else P[ i ] ≥ P[ i' ]. (Which we have to expand past the right edge (R) to find P[ i ].
See how elegant it is? If you are able to grasp the above summary fully, you already obtained the essence of this algorithm, which is also the hardest part.

The final part is to determine when should we move the position of C together with R to the right, which is easy:

If the palindrome centered at i does expand past R, we update C to i, (the center of this new palindrome), and extend R to the new palindrome’s right edge.
In each step, there are two possibilities. If P[ i ] ≤ R – i, we set P[ i ] to P[ i' ] which takes exactly one step. Otherwise we attempt to change the palindrome’s center to i by expanding it starting at the right edge, R. Extending R (the inner while loop) takes at most a total of N steps, and positioning and testing each centers take a total of N steps too. Therefore, this algorithm guarantees to finish in at most 2*N steps, giving a linear time solution.

```
// Transform S into T.
// For example, S = "abba", T = "^#a#b#b#a#$".
// ^ and $ signs are sentinels appended to each end to avoid bounds checking
string preProcess(string s) {
  int n = s.length();
  if (n == 0) return "^$";
  string ret = "^";
  for (int i = 0; i < n; i++)
    ret += "#" + s.substr(i, 1);
 
  ret += "#$";
  return ret;
}
 
string longestPalindrome(string s) {
  string T = preProcess(s);
  int n = T.length();
  int *P = new int[n];
  int C = 0, R = 0;
  for (int i = 1; i < n-1; i++) {
    int i_mirror = 2*C-i; // equals to i' = C - (i-C)
    
    P[i] = (R > i) ? min(R-i, P[i_mirror]) : 0;
    
    // Attempt to expand palindrome centered at i
    while (T[i + 1 + P[i]] == T[i - 1 - P[i]])
      P[i]++;
 
    // If palindrome centered at i expand past R,
    // adjust center based on expanded palindrome.
    if (i + P[i] > R) {
      C = i;
      R = i + P[i];
    }
  }
 
  // Find the maximum element in P.
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

Note:
This algorithm is definitely non-trivial and you won’t be expected to come up with such algorithm during an interview setting. However, I do hope that you enjoy reading this article and hopefully it helps you in understanding this interesting algorithm. You deserve a pat if you have gone this far! :)

Further Thoughts:

In fact, there exists a sixth solution to this problem — Using suffix trees. However, it is not as efficient as this one (run time O(N log N) and more overhead for building suffix trees) and is more complicated to implement. If you are interested, read Wikipedia’s article about Longest Palindromic Substring.
What if you are required to find the longest palindromic subsequence? (Do you know the difference between substring and subsequence?)
Useful Links:
» Manacher’s Algorithm O(N) 时间求字符串的最长回文子串 (Best explanation if you can read Chinese)
» A simple linear time algorithm for finding longest palindrome sub-string
» Finding Palindromes
» Finding the Longest Palindromic Substring in Linear Time
» Wikipedia: Longest Palindromic Substring
