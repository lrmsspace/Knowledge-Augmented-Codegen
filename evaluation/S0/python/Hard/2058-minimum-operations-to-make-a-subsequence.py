# Source: https://leetcode.com/problems/minimum-operations-to-make-a-subsequence/   |   Difficulty: Hard
#
# Problem Description:
# You are given an array target that consists of distinct integers and another integer array arr that can have duplicates.
#
# In one operation, you can insert any integer at any position in arr. For example, if arr = [1,4,1,2], you can add 3 in the middle and make it [1,4,3,1,2]. Note that you can insert the integer at the very beginning or end of the array.
#
# Return the minimum number of operations needed to make target a subsequence of arr.
#
# A subsequence of an array is a new array generated from the original array by deleting some elements (possibly none) without changing the remaining elements' relative order. For example, [2,7,4] is a subsequence of [4,2,3,7,2,1,4] (the underlined elements), while [2,4,2] is not.
#
# Example:
# Input: target = [5,1,3], arr = [9,4,2,3,4]
# Output: 2
# Explanation: You can add 5 and 1 in such a way that makes arr = [5,9,4,1,2,3,4], then target will be a subsequence of arr.
#
# Constraints:
# 1 <= target.length, arr.length <= 105
# 	1 <= target[i], arr[i] <= 109
# 	target contains no duplicates.
#

class Solution(object):
    def minOperations(self, target, arr):
        """
        :type target: List[int]
        :type arr: List[int]
        :rtype: int
        """
        import bisect

        pos = {num: i for i, num in enumerate(target)}
        lis = []

        for num in arr:
            if num in pos:
                index = pos[num]
                insert_pos = bisect.bisect_left(lis, index)
                if insert_pos == len(lis):
                    lis.append(index)
                else:
                    lis[insert_pos] = index

        return len(target) - len(lis)