## Data Structure
704. Binary Search(随机查找值)
Given an array of integers nums which is sorted in ascending order, and an integer target, write a function to search target in nums. If target exists, then return its index. Otherwise, return -1.

278. First Bad Version(随机查找值)
You are a product manager and currently leading a team to develop a new product. Unfortunately, the latest version of your product fails the quality check. Since each version is developed based on the previous version, all the versions after a bad version are also bad.

35. Search Insert Position(随机查找值)
Given a sorted array of distinct integers and a target value, return the index if the target is found. If not, return the index where it would be if it were inserted in order.

二分查找：
1.递归形式：函数输入参数有left、right。递归退出条件：交叉false；
2.循环形式：函数输入参数无需left、right。循环条件：left <= right，交叉时退出循环false；

977. Squares of a Sorted Array(有序序列的平方)
Given an integer array nums sorted in non-decreasing order, return an array of the squares of each number sorted in non-decreasing order.

双指针法：
比较非降序数组两端绝对值的大小，双指针往最小负数/正数滑动。

189. Rotate Array(将数组右移k位)
Given an array, rotate the array to the right by k steps, where k is non-negative.

方法：
1.拷贝数据，答案的第(i + k)%n个格子 放入 源数据第i个数据TimeC: O(n). SpaceC: O(n).
2.双指针法：
https://leetcode.com/problems/rotate-array/discuss/54263/3-lines-of-C%2B%2B-in-one-pass-using-swap
https://leetcode.com/problems/rotate-array/discuss/54277/Summary-of-C%2B%2B-solutions
3.三次旋转法：reverse(nums.begin(),nums.end());reverse(nums.begin(),nums.begin()+k);reverse(nums.begin()+k,nums.end()); 

283. Move Zeroes(将0全部往后移动至数组末尾)
Given an integer array nums, move all 0's to the end of it while maintaining the relative order of the non-zero elements.

方法：
1.双指针法
	for(int i=0,next=0;i<nums.size();++i)
		if(nums[i])
			swap(nums[i],nums[next++]);
  next指向0元素位置    
2.STL算法
  stable_partition(begin(nums),end(nums),[](int i){return i;});
  stable_partition(rbegin(nums),rend(nums),logical_not<int>());

167. Two Sum II - Input Array Is Sorted(有序数组寻找两个数的和为指定数值的组合)
Given a 1-indexed array of integers numbers that is already sorted in non-decreasing order, find two numbers such that they add up to a specific target number. Let these two numbers be numbers[index1] and numbers[index2] where 1 <= index1 < index2 <= numbers.length.
Return the indices of the two numbers, index1 and index2, added by one as an integer array [index1, index2] of length 2.

双指针法：最左最右，往中间夹，小，左指针右移，大，右指针左移，交叉则寻找失败。TimeC: O(N) SpaceC: O(1)

344. Reverse String(旋转字符串)
Write a function that reverses a string. The input string is given as an array of characters s.

1.双指针法：退出条件：l==r
2.迭代器法：return { s.rbegin(), s.rend() };reverse(s.begin(),s.end());

557. Reverse Words in a String III(旋转句子中的每个词)
Given a string s, reverse the order of characters in each word within a sentence while still preserving whitespace and initial word order.

外部增加断词逻辑：
1.双指针法：退出条件l==r
2.迭代器法：return { s.rbegin(), s.rend() };reverse(s.begin(),s.end());

876. Middle of the Linked List(返回链表最中间的元素，偶数的话返回n/2个元素，数组下标0开始)
Given the head of a singly linked list, return the middle node of the linked list.
If there are two middle nodes, return the second middle node.

双指针：快慢指针，快步长比慢步长快一倍。

19. Remove Nth Node From End of List(删除倒数第n个元素)
Given the head of a linked list, remove the nth node from the end of the list and return its head.

双指针：偏移指针先抢跑，为避免内存泄漏，要delete节点。

3. Longest Substring Without Repeating Characters(寻找最长不重复字符字串)
Given a string s, find the length of the longest substring without repeating characters.

滑动窗口法：用哈希表unordered_set来有指针字符是否已出现在子串内

567. Permutation in String(给定字符串排列组合是否存在于主字符串中)
Given two strings s1 and s2, return true if s2 contains a permutation of s1, or false otherwise.
In other words, return true if one of s1's permutations is the substring of s2.

滑动窗口法：cur vector 和 goal vector，从第cur.size()==goal.size()开始比较，保持cur.size()，进行滑动比较。

733. Flood Fill(洪水染色)
An image is represented by an m x n integer grid image where image[i][j] represents the pixel value of the image.
You are also given three integers sr, sc, and newColor. You should perform a flood fill on the image starting from the pixel image[sr][sc].
To perform a flood fill, consider the starting pixel, plus any pixels connected 4-directionally to the starting pixel of the same color as the starting pixel, plus any pixels connected 4-directionally to those pixels (also with the same color), and so on. Replace the color of all of the aforementioned pixels with newColor.
Return the modified image after performing the flood fill.

DFS：当4/8领域时，递归终止条件为：点的坐标位于图外，点坐标的颜色已经为目标颜色，点坐标的颜色不为源颜色。

695. Max Area of Island(找最大的连通域)
You are given an m x n binary matrix grid. An island is a group of 1's (representing land) connected 4-directionally (horizontal or vertical.) You may assume all four edges of the grid are surrounded by water.
The area of an island is the number of cells with a value 1 in the island.
Return the maximum area of an island in grid. If there is no island, return 0.

DFS：当遍历到一个前景色块时，进行连通域的的DFS，递归：将该点的值置为背景色，递归其4/8连通域，返回1 + AreaOfIsland(grid, i+1, j) + AreaOfIsland(grid, i-1, j) + AreaOfIsland(grid, i, j-1) + AreaOfIsland(grid, i, j+1);

617. Merge Two Binary Trees(将两棵树合并，重叠位置的数值求和)
You are given two binary trees root1 and root2.
Imagine that when you put one of them to cover the other, some nodes of the two trees are overlapped while the others are not. You need to merge the two trees into a new binary tree. The merge rule is that if two nodes overlap, then sum node values up as the new value of the merged node. Otherwise, the NOT null node will be used as the node of the new tree.
Return the merged tree.

深度优先遍历：用递归：若两结点位置重叠，则两节点的值相加，若位置不重叠，则返回存在的结点值。值相加；递归左子树位置，递归右子树位置.

116. Populating Next Right Pointers in Each Node(将每个结点的next指针指向它右边的兄弟结点)
You are given a perfect binary tree where all leaves are on the same level, and every parent has two children. The binary tree has the following
Populate each next pointer to point to its next right node. If there is no next right node, the next pointer should be set to NULL.

广度优先遍历：用循环+队列，先把右孩子压入队列，再把左孩子压入队列，每次弹出一个结点，修改它的next后，将它作为下一个等着被指向的结点。

542. 01 Matrix(知道矩阵到0元素的距离)
Given an m x n binary matrix mat, return the distance of the nearest 0 for each cell.

方法1：用广度优先算法，将0元素的坐标收集起来，将0元素上下左右位置中未标记的位置用该元素的值+1作为替代，并压出队列中。

36. Valid Sudoku(判断是否是一个有效数独)
Determine if a 9 x 9 Sudoku board is valid. Only the filled cells need to be validated according to the following rules:
Each row must contain the digits 1-9 without repetition.
Each column must contain the digits 1-9 without repetition.
Each of the nine 3 x 3 sub-boxes of the grid must contain the digits 1-9 without repetition.

三个判断条件：每行，每列，每块。used1 used2 used3 都为九行九列。
至于每行和每列，则是用数组判断，有则置为1。
至于每块，则用k = i / 3 * 3 + j / 3去计算每个位置的索引。

74. Search a 2D Matrix(有序矩阵效率查找数)
Write an efficient algorithm that searches for a value target in an m x n integer matrix matrix. This matrix has the following properties:
Integers in each row are sorted from left to right.
The first integer of each row is greater than the last integer of the previous row.

把矩阵看作为一维数组，用二分查找法。行号为取余，列号为取模。

387. First Unique Character in a String(寻找字符串第一个不重复出现的字符位置)
Given a string s, find the first non-repeating character in it and return its index. If it does not exist, return -1.

第一遍统计，第二遍找只出现一次的字符。

383. Ransom Note(看一个字符串是否被包含于另一字符串)
Given two strings ransomNote and magazine, return true if ransomNote can be constructed from magazine and false otherwise.
Each letter in magazine can only be used once in ransomNote.

哈希表magazine用来 +1，ransomNote用来 -1.

242. Valid Anagram(给定两个字符串，判断是否互为排序组合字符串)
Given two strings s and t, return true if t is an anagram of s, and false otherwise.
An Anagram is a word or phrase formed by rearranging the letters of a different word or phrase, typically using all the original letters exactly once.

哈希表：加减，最终为0
<Algorithm>:排序，判相等

141. Linked List Cycle(判断链表是否有环)
Given head, the head of a linked list, determine if the linked list has a cycle in it.
There is a cycle in a linked list if there is some node in the list that can be reached again by continuously following the next pointer. Internally, pos is used to denote the index of the node that tail's next pointer is connected to.

快慢指针

21. Merge Two Sorted Lists(合并两个有序链表)
You are given the heads of two sorted linked lists list1 and list2.
Merge the two lists in a one sorted list. The list should be made by splicing together the nodes of the first two lists.
Return the head of the merged linked list.

谁小，谁next，剩下的全接入。

203. Remove Linked List Elements(删除链表上值为固定的结点)
Given the head of a linked list and an integer val, remove all the nodes of the linked list that has Node.val == val, and return the new head.

遍历删除结点，记得防止内存泄露。

206. Reverse Linked List(翻转链表)
Given the head of a singly linked list, reverse the list, and return the reversed list.

头插法或双指针遍历

83. Remove Duplicates from Sorted List(删除有序链表重复出现元素)
Given the head of a sorted linked list, delete all duplicates such that each element appears only once. Return the linked list sorted as well.

遍历删除结点，记得防止内存泄露。

20. Valid Parentheses
Given a string s containing just the characters '(', ')', '{', '}', '[' and ']', determine if the input string is valid.
An input string is valid if:
Open brackets must be closed by the same type of brackets.
Open brackets must be closed in the correct order.

栈入栈出。

232. Implement Queue using Stacks(用栈来实施队列)
Implement a first in first out (FIFO) queue using only two stacks. The implemented queue should support all the functions of a normal queue (push, peek, pop, and empty).
Implement the MyQueue class:
void push(int x) Pushes element x to the back of the queue.
int pop() Removes the element from the front of the queue and returns it.
int peek() Returns the element at the front of the queue.
boolean empty() Returns true if the queue is empty, false otherwise.

两个栈：input栈和output栈，
队列出队是，判断output栈是否为空，如果为空，则将input栈全部出栈后立刻压入output栈，反之则直接取output栈顶。

144. Binary Tree Preorder Traversal(求树的先序序列)
Given the root of a binary tree, return the preorder traversal of its nodes' values.

1.Iterative solution using stack --- O(n) time and O(n) space;
2.Recursive solution --- O(n) time and O(n) space (function call stack);
3.Morris traversal --- O(n) time and O(1) space.
https://leetcode.com/problems/binary-tree-preorder-traversal/discuss/45466/C%2B%2B-Iterative-Recursive-and-Morris-Traversal

94. Binary Tree Inorder Traversal(求树的中序序列)
Given the root of a binary tree, return the inorder traversal of its nodes' values.+

Iterative solution using stack: O(n) time and O(n) space;
Recursive solution: O(n) time and O(n) space (function call stack);
Morris traversal: O(n) time and O(1) space.
https://leetcode.com/problems/binary-tree-inorder-traversal/discuss/31231/C%2B%2B-Iterative-Recursive-and-Morris

145. Binary Tree Postorder Traversal(求树的后序序列)
Given the root of a binary tree, return the postorder traversal of its nodes' values.

Iterative solution using stack --- O(n) time and O(n) space;
Recursive solution --- O(n) time and O(n) space (function call stack);
Morris traversal --- O(n) time and O(1) space.
https://leetcode.com/problems/binary-tree-postorder-traversal/discuss/45550/C%2B%2B-Iterative-Recursive-and-Morris-Traversal

102. Binary Tree Level Order Traversal(求树的层序序列)
Given the root of a binary tree, return the level order traversal of its nodes' values. (i.e., from left to right, level by level).

辅助队列，while循环内for循环当前队列内的元素。

104. Maximum Depth of Binary Tree(求树的最大深度)
Given the root of a binary tree, return its maximum depth.
A binary tree's maximum depth is the number of nodes along the longest path from the root node down to the farthest leaf node.

DFS：递归，递归左，递归右，然后返回左右最大深度 + 1

101. Symmetric Tree(判断树是否对称)
Given the root of a binary tree, check whether it is a mirror of itself (i.e., symmetric around its center).

701. Insert into a Binary Search Tree
You are given the root node of a binary search tree (BST) and a value to insert into the tree. Return the root node of the BST after the insertion. It is guaranteed that the new value does not exist in the original BST.

700. Search in a Binary Search Tree
You are given the root of a binary search tree (BST) and an integer val.
Find the node in the BST that the node's value equals val and return the subtree rooted with that node. If such a node does not exist, return null.

112. Path Sum
Given the root of a binary tree and an integer targetSum, return true if the tree has a root-to-leaf path such that adding up all the values along the path equals targetSum.

226. Invert Binary Tree
Given the root of a binary tree, invert the tree, and return its root.


235. Lowest Common Ancestor of a Binary Search Tree
Given a binary search tree (BST), find the lowest common ancestor (LCA) of two given nodes in the BST.
According to the definition of LCA on Wikipedia: “The lowest common ancestor is defined between two nodes p and q as the lowest node in T that has both p and q as descendants (where we allow a node to be a descendant of itself).”



--------------------------------------------------------------------------------------------------------------------------------------------
## Algorithm
217.Contains Duplicate(找重复的数)
Given an integer array nums, return true if any value appears at least twice in the array, and return false if every element is distinct.

1.对数组排序后，判断数组第i与第i+1个元素是否相等； 
  时间复杂度：O(N*logN)，其中 N 为数组的长度。对数组进行排序。 
  空间复杂度：O(logN)，其中 N 为数组的长度。应当考虑递归调用栈的深度。
2.利用哈希表无法存储相同元素的性质
  时间复杂度：O(N)，其中 N 为数组的长度。
  空间复杂度：O(N)，其中 N 为数组的长度。

53.Maximum Subarray(找和最大的子数组)
Given an integer array nums, find the contiguous subarray (containing at least one number) which has the largest sum and return its sum.  

若sum小于0，就说明当前元素加上sum只会更小，所以此时sum=nums[i]，否则max+=nums[i]。（动态规划Kadane’s Algorithm）

1.Two Sum(无序数组寻找两个数的和为指定数值的组合)
Given an array of integers nums and an integer target, return indices of the two numbers such that they add up to target.

用哈希表，对数组每个元素做差，看差值是否已经存在表内。

1.  Merge Sorted Array(合并两个有序数组)
You are given two integer arrays nums1 and nums2, sorted in non-decreasing order, and two integers m and n, representing the number of elements in nums1 and nums2 respectively.
Merge nums1 and nums2 into a single array sorted in non-decreasing order.
The final sorted array should not be returned by the function, but instead be stored inside the array nums1. To accommodate this, nums1 has a length of m + n, where the first m elements denote the elements that should be merged, and the last n elements are set to 0 and should be ignored. nums2 has a length of n.

简洁写法：a[m + n - 1] = (m > 0 && a[m - 1] > b[n - 1])? a[--m] : b[--n];

350. Intersection of Two Arrays II(找两数组重叠的部分)
Given two integer arrays nums1 and nums2, return an array of their intersection. Each element in the result must appear as many times as it shows in both arrays and you may return the result in any order.

哈希表：数组一加入哈希表，重复则自增，数组二查找哈希表，查找成功则自减；
排序和双指针。

121. Best Time to Buy and Sell Stock(低买高抛)
You are given an array prices where prices[i] is the price of a given stock on the ith day.
You want to maximize your profit by choosing a single day to buy one stock and choosing a different day in the future to sell that stock.
Return the maximum profit you can achieve from this transaction. If you cannot achieve any profit, return 0.

遍历：记录最低买入价格，记录当前卖出的利益，不断更新最大卖出利益。

566. Reshape the Matrix(重整矩形)
In MATLAB, there is a handy function called reshape which can reshape an m x n matrix into a new one with a different size r x c keeping its original data.
You are given an m x n matrix mat and two integers r and c representing the number of rows and the number of columns of the wanted reshaped matrix.
The reshaped matrix should be filled with all the elements of the original matrix in the same row-traversing order as they were.
If the reshape operation with given parameters is possible and legal, output the new reshaped matrix; Otherwise, output the original matrix.

遍历至总数：取余，取模！result[i / c][i % c] = mat[i / n][i % n];

118. Pascal's Triangle
Given an integer numRows, return the first numRows of Pascal's triangle.

杨辉三角：初始化i+1个全1，从下标为1至下标i-1，开始赋值，上一行[i] + 上一行[i-1]。


994. Rotting Oranges(多少次腐烂扩散全部橙子腐烂)
You are given an m x n grid where each cell can have one of three values:
0 representing an empty cell,
1 representing a fresh orange, or
2 representing a rotten orange.
Every minute, any fresh orange that is 4-directionally adjacent to a rotten orange becomes rotten.
Return the minimum number of minutes that must elapse until no cell has a fresh orange. If this is impossible, return -1.

77. Combinations(找出区间内所有的k个元素的组合)
Given two integers n and k, return all possible combinations of k numbers out of the range [1, n].

https://leetcode.com/problems/combinations/discuss/26992/Short-Iterative-C%2B%2B-Answer-8ms

----------------------------------------------------------------------------------------------------------------------------------------
## Programming Skills
1523. Count Odd Numbers in an Interval Range(计算区间内的奇数个数)
Given two non-negative integers low and high. Return the count of odd numbers between low and high (inclusive).

计算方法：(low + high)/2 如果两端任一一个为奇数，则需+1

1491. Average Salary Excluding the Minimum and Maximum Salary(去掉一个最高分和一个最低分算平均)
You are given an array of unique integers salary where salary[i] is the salary of the ith employee.
Return the average salary of employees excluding the minimum and maximum salary. Answers within 10-5 of the actual answer will be accepted.

技巧：
accumulate(begin(s), end(s), 0.)
conversion to double (0. - with a dot - as the initial value for accumulate).
min_element 和 max_element 头文件:#include<algorithm> 作用:返回容器中最小值和最大值的指针。max_element(first,end,cmp);其中cmp为可选择参数