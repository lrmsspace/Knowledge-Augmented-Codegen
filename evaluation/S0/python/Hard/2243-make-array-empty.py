# Source: https://leetcode.com/problems/make-array-empty/   |   Difficulty: Hard
#
# Problem Description:
# You are given an integer array nums containing distinct numbers, and you can perform the following operations until the array is empty:
#
#
# 	If the first element has the smallest value, remove it
# 	Otherwise, put the first element at the end of the array.
#
#
# Return an integer denoting the number of operations it takes to make nums empty.
#
# Example:
# Input: nums = [3,4,-1]
# Output: 5
#
#
#
# 	
# 		
# 			Operation
# 			Array
# 		
# 	
# 	
# 		
# 			1
# 			[4, -1, 3]
# 		
# 		
# 			2
# 			[-1, 3, 4]
# 		
# 		
# 			3
# 			[3, 4]
# 		
# 		
# 			4
# 			[4]
# 		
# 		
# 			5
# 			[]
#
# Constraints:
# 1 <= nums.length <= 105
# 	-109 <= nums[i] <= 109
# 	All values in nums are distinct.
#

class Solution(object):
    def countOperationsToEmptyArray(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        n = len(nums)
        indexed_nums = [(num, i) for i, num in enumerate(nums)]
        indexed_nums.sort()
        
        pos = [0] * n
        for rank in range(n):
            pos[indexed_nums[rank][1]] = rank
        
        bit = [0] * (n + 1)
        
        def update(i):
            i += 1
            while i <= n:
                bit[i] += 1
                i += i & -i
        
        def query(i):
            i += 1
            s = 0
            while i > 0:
                s += bit[i]
                i -= i & -i
            return s
        
        operations = 0
        for i in range(n):
            rank = pos[i]
            operations += (rank - query(rank)) + 1
            update(rank)
        
        return operations