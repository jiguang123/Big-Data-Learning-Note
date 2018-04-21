```
1、题目描述：

Given an array of integers, return indices of the two numbers such that they add up to a specific target.
You may assume that each input would have exactly one solution, and you may not use the same element twice.

Example :

	Given nums = [2, 7, 11, 15], target = 9,
	Because nums[0] + nums[1] = 2 + 7 = 9,
	return [0, 1].

2、题目翻译

给定一个整数数组，返回两个数字的索引下标，使它们相加和为target指定的值。
每个输入都只有一个解，不存在使用相同元素两次的情况。

示例：

	给定nums = [2，7，11，15]，target = 9，
	因为nums [ 0 ] + nums [ 1 ] = 2 + 7 = 9，
	返回[ 0，1 ]。

3、解题方案

标签： Hash Table、Array
思路：
	方法一：最简单的思路是遍历数组，看数组中剩下的数里是否存在nums[j]=target-nums[i];
	方法二：将数组中的数插入HashMap中，再遍历数组，看（target-nums[i]）是否在HashMap中。
			其时间复杂度和空间复杂度都是O(n)，因为Hash Table的查找时间复杂度是O(1)。

```

class Solution(object):
    def twoSum(self, nums, target):
        """
        :type nums: List[int]
        :type target: int
        :rtype: List[int]
        """
        hash_map = {}
        for index, value in enumerate(nums):
            hash_map[value] = index
        for index1, value in enumerate(nums):
            if target - value in hash_map:
                index2 = hash_map[target - value]
                if index1 != index2:
                    return [index1 + 1, index2 + 1]


if __name__ == "__main__":
    print(Solution().twoSum([2, 7, 11, 15], 9));