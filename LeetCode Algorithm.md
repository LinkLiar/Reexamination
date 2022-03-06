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

--------------------------------------------------------------------------------------------------------------------------------------------
## Algorithm
217.Contains Duplicate
Given an integer array nums, return true if any value appears at least twice in the array, and return false if every element is distinct.

1.对数组排序后，判断数组第i与第i+1个元素是否相等； 
  时间复杂度：O(N*logN)，其中 N 为数组的长度。对数组进行排序。 
  空间复杂度：O(logN)，其中 N 为数组的长度。应当考虑递归调用栈的深度。
2.利用哈希表无法存储相同元素的性质
  时间复杂度：O(N)，其中 N 为数组的长度。
  空间复杂度：O(N)，其中 N 为数组的长度。

53.Maximum Subarray
Given an integer array nums, find the contiguous subarray (containing at least one number) which has the largest sum and return its sum.  

若sum小于0，就说明当前元素加上sum只会更小，所以此时sum=nums[i]，否则max+=nums[i]。（动态规划Kadane’s Algorithm）

1.Two Sum
Given an array of integers nums and an integer target, return indices of the two numbers such that they add up to target.

----------------------------------------------------------------------------------------------------------------------------------------
## Programming Skills
1523. Count Odd Numbers in an Interval Range(计算区间内的奇数个数)
Given two non-negative integers low and high. Return the count of odd numbers between low and high (inclusive).

计算方法：(low + high)/2 如果两端任一一个为奇数，则需+1