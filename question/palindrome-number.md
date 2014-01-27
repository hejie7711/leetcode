# 回文数

http://leetcode.com/2012/01/palindrome-number.html

> 确定一个整型是否是回文。不能使用额外的空间。

在之前的题目中（最长回文子字符串 第一部 第）
In previous posts (Longest Palindromic Substring Part I, Part II) we have discussed multiple approaches on finding the longest palindrome in a string. In this post we discuss ways to determine whether an integer is a palindrome. Sounds easy?

Hint:
Don’t be deceived by this problem which seemed easy to solve. Also note the restriction of doing it without extra space. Think of a generic solution that is not language/platform specific. Also, consider cases where your solution might go wrong.

Solution:
First, the problem statement did not specify if negative integers qualify as palindromes. Does negative integer such as -1 qualify as a palindrome? Finding out the full requirements of a problem before coding is what every programmer must do. For the purpose of discussion here, we define negative integers as non-palindromes.

The most intuitive approach is to first represent the integer as a string, since it is more convenient to manipulate. Although this certainly does work, it violates the restriction of not using extra space. (ie, you have to allocate n characters to store the reversed integer as string, where n is the maximum number of digits). I know, this sound like an unreasonable requirement (since it uses so little space), but don’t most interview problems have such requirements?

Another approach is to first reverse the number. If the number is the same as its reversed, then it must be a palindrome. You could reverse a number by doing the following:

```
int reverse(int num) {
  assert(num >= 0);   // for non-negative integers only.
  int rev = 0;
  while (num != 0) {
    rev = rev * 10 + num % 10;
    num /= 10;
  }
  return rev;
}
```
This seemed to work too, but did you consider the possibility that the reversed number might overflow? If it overflows, the behavior is language specific (For Java the number wraps around on overflow, but in C/C++ its behavior is undefined). Yuck.

Of course, we could avoid overflow by storing and returning a type that has larger size than int (ie, long long). However, do note that this is language specific, and the larger type might not always be available on all languages.

We could construct a better and more generic solution. One pointer is that, we must start comparing the digits somewhere. And you know there could only be two ways, either expand from the middle or compare from the two ends.

It turns out that comparing from the two ends is easier. First, compare the first and last digit. If they are not the same, it must not be a palindrome. If they are the same, chop off one digit from both ends and continue until you have no digits left, which you conclude that it must be a palindrome.

Now, getting and chopping the last digit is easy. However, getting and chopping the first digit in a generic way requires some thought. I will leave this to you as an exercise. Please think your solution out before you peek on the solution below.

```
bool isPalindrome(int x) {
  if (x < 0) return false;
  int div = 1;
  while (x / div >= 10) {
    div *= 10;
  }        
  while (x != 0) {
    int l = x / div;
    int r = x % 10;
    if (l != r) return false;
    x = (x % div) / 10;
    div /= 100;
  }
  return true;
}
```

Alternative Solution:
Credits go to Dev who suggested a recursive solution (if extra stack space does not count as extra space), which is pretty neat too.

```
bool isPalindrome(int x, int &y) {
  if (x < 0) return false;
  if (x == 0) return true;
  if (isPalindrome(x/10, y) && (x%10 == y%10)) {
    y /= 10;
    return true;
  } else {
    return false;
  }
}
bool isPalindrome(int x) {
  return isPalindrome(x, x);
}
```
