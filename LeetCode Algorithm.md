704. Binary Search
Given an array of integers nums which is sorted in ascending order, and an integer target, write a function to search target in nums. If target exists, then return its index. Otherwise, return -1.

278. First Bad Version
You are a product manager and currently leading a team to develop a new product. Unfortunately, the latest version of your product fails the quality check. Since each version is developed based on the previous version, all the versions after a bad version are also bad.

35. Search Insert Position
Given a sorted array of distinct integers and a target value, return the index if the target is found. If not, return the index where it would be if it were inserted in order.

二分查找：
1.递归形式：函数输入参数有left、right。递归退出条件：交叉false；
2.循环形式：函数输入参数无需left、right。循环条件：left <= right，交叉时退出循环false；

977. Squares of a Sorted Array
Given an integer array nums sorted in non-decreasing order, return an array of the squares of each number sorted in non-decreasing order.

双指针法：
比较非降序数组两端绝对值的大小，双指针往最小负数/正数滑动。

189. Rotate Array
Given an array, rotate the array to the right by k steps, where k is non-negative.

方法：
1.拷贝数据，答案的第(i + k)%n个格子 放入 源数据第i个数据TimeC: O(n). SpaceC: O(n).
2.双指针法：
https://leetcode.com/problems/rotate-array/discuss/54263/3-lines-of-C%2B%2B-in-one-pass-using-swap
https://leetcode.com/problems/rotate-array/discuss/54277/Summary-of-C%2B%2B-solutions
3.三次旋转法：reverse(nums.begin(),nums.end());reverse(nums.begin(),nums.begin()+k);reverse(nums.begin()+k,nums.end()); 

.Contains Duplicate
Given an integer array nums, return true if any value appears at least twice in the array, and return false if every element is distinct.

1.对数组排序后，判断数组第i与第i+1个元素是否相等； 
  时间复杂度：O(N*logN)，其中 N 为数组的长度。对数组进行排序。 
  空间复杂度：O(logN)，其中 N 为数组的长度。应当考虑递归调用栈的深度。
2.利用哈希表无法存储相同元素的性质
  时间复杂度：O(N)，其中 N 为数组的长度。
  空间复杂度：O(N)，其中 N 为数组的长度。

1. Maximum Subarray
Given an integer array nums, find the contiguous subarray (containing at least one number) which has the largest sum and return its sum.  

动态规划Kadane’s Algorithm