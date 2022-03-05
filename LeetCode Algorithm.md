## Data Structure
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

283. Move Zeroes
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

167. Two Sum II - Input Array Is Sorted
Given a 1-indexed array of integers numbers that is already sorted in non-decreasing order, find two numbers such that they add up to a specific target number. Let these two numbers be numbers[index1] and numbers[index2] where 1 <= index1 < index2 <= numbers.length.
Return the indices of the two numbers, index1 and index2, added by one as an integer array [index1, index2] of length 2.

双指针法：最左最右，往中间夹，小，左指针右移，大，右指针左移，交叉则寻找失败。TimeC: O(N) SpaceC: O(1)

344. Reverse String
Write a function that reverses a string. The input string is given as an array of characters s.

1.双指针法：退出条件：l==r
2.迭代器法：return { s.rbegin(), s.rend() };reverse(s.begin(),s.end());

557. Reverse Words in a String III
Given a string s, reverse the order of characters in each word within a sentence while still preserving whitespace and initial word order.

外部增加断词逻辑：
1.双指针法：退出条件l==r
2.迭代器法：return { s.rbegin(), s.rend() };reverse(s.begin(),s.end());

876. Middle of the Linked List
Given the head of a singly linked list, return the middle node of the linked list.
If there are two middle nodes, return the second middle node.

双指针：快慢指针
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