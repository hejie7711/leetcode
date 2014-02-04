# 向循环有序链表插入节点

http://leetcode.com/2011/08/insert-into-a-cyclic-sorted-list.html

> 给一个循环有序链表中的某个节点，写一个函数，向该链表插入一个节点，依然保持循环有序。给的节点可以是链表中的任意单个节点。

## 循环有序链表定义
设想你有一个有序链表，但是它的尾指针指回到头指针。换言之，该链表必须有一个最小的节点，升序排列，最后指针指回到这个最小节点。访问该链表的唯一方法是通过节点，可以指向任意节点，但是没有必要一定指向最小节点。

首先，你明白什么是循环链表很重要。一个循环链表不同于普通的链表，循环链表的尾指针指回它的头指针，而普通的链表指向NULL指针。

该题出得有点狡猾，因为给的节点不一定是该链表的头指针（具有最小元素的节点）。你立马就能想出一个点子，但是注意。该题有陷阱，如果你不小心就会犯错。

![ScreenShot](https://raw.github.com/xiangzhai/leetcode/master/image/cyclic_list1.png)

一个循环有序链表。注意尾指针指回到头指针。该链表唯独可以参考的是给定一个节点，可以是该链表中的任意一个节点。假设你需要向该链表插入4。

![ScreenShot](https://raw.github.com/xiangzhai/leetcode/master/image/cyclic_list2.png)

This is how the cyclic list becomes after inserting 4. Note that the cyclic linked list remained in sorted order.

Hints:
It is best to list all kinds of cases first before you jump into coding. Then, it is much easier to reduce the number of cases your code need to handle by combining some of them into a more generic case. Try to also list down all possible edge cases if you have time. You might discover a bug before you even start coding!

Solution:
Basically, you would have a loop that traverse the cyclic sorted list and find the point where you insert the value (Let’s assume the value being inserted called x). You would only need to consider the following three cases:

prev→val ≤ x ≤ current→val:
Insert between prev and current.
x is the maximum or minimum value in the list:
Insert before the head. (ie, the head has the smallest value and its prev→val > head→val.
Traverses back to the starting point:
Insert before the starting point.
Most people have no problem getting case 1) working, while case 2) is easy to miss or being handled incorrectly. Case 3), on the other hand is more subtle and is not immediately clear what kind of test cases would hit this condition. It seemed that case 1) and 2) should take care of all kinds of cases and case 3) is not needed. Think again… How can you be sure of that? Could you come up with one case where it hits case 3)?

Q: What if the list has only one value?
A: Handled by case 1). Handled by case 3).
Q: What if the list is passed in as NULL?
A: Then handle this special case by creating a new node pointing back to itself and return.
Q: What if the list contains all duplicates?
A: Then it has been handled by case 3).
Below is the code. You could combine both negation of case 1) and case 2) in the while loop’s condition, but I prefer to use break statements here to illustrate the above idea clearer.

```
void insert(Node *& aNode, int x) {
  if (!aNode) {
    aNode = new Node(x);
    aNode->next = aNode;
    return;
  }
 
  Node *p = aNode;
  Node *prev = NULL;
  do {
    prev = p;
    p = p->next;
    if (x <= p->data && x >= prev->data) break;   // For case 1)
    if ((prev->data > p->data) && (x < p->data || x > prev->data)) break; // For case 2)
  } while (p != aNode);   // when back to starting point, then stop. For case 3)
 
  Node *newNode = new Node(x);
  newNode->next = p;
  prev->next = newNode;
}
```
