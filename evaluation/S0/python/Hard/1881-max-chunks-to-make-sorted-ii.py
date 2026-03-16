# Source: https://leetcode.com/problems/max-chunks-to-make-sorted-ii/   |   Difficulty: Hard
#
# Problem Description:
# You are given an integer array arr.
#
# We split arr into some number of chunks (i.e., partitions), and individually sort each chunk. After concatenating them, the result should equal the sorted array.
#
# Return the largest number of chunks we can make to sort the array.
#
# Example:
# Input: arr = [5,4,3,2,1]
# Output: 1
# Explanation:
# Splitting into two or more chunks will not return the required result.
# For example, splitting into [5, 4], [3, 2, 1] will result in [4, 5, 1, 2, 3], which isn't sorted.
#
# Constraints:
# 1 <= arr.length <= 2000
# 	0 <= arr[i] <= 108
#

class Solution(object):
    def maxChunksToSorted(self, arr):
        """
        :type arr: List[int]
        :rtype: int
        """
        sorted_arr = sorted(arr)
        count = 0
        current_sum = 0
        sorted_sum = 0
        
        for i in range(len(arr)):
            current_sum += arr[i]
            sorted_sum += sorted_arr[i]
            
            if current_sum == sorted_sum:
                count += 1
                
        return count