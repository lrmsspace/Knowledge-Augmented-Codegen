# Source: https://leetcode.com/problems/count-triplets-that-can-form-two-arrays-of-equal-xor/   |   Difficulty: Medium
#
# Problem Description:
# Given an array of integers arr.
#
# We want to select three indices i, j and k where (0 <= i < j <= k < arr.length).
#
# Let's define a and b as follows:
#
#
# 	a = arr[i] ^ arr[i + 1] ^ ... ^ arr[j - 1]
# 	b = arr[j] ^ arr[j + 1] ^ ... ^ arr[k]
#
#
# Note that ^ denotes the bitwise-xor operation.
#
# Return the number of triplets (i, j and k) Where a == b.
#
# Example:
# Input: arr = [2,3,1,6,7]
# Output: 4
# Explanation: The triplets are (0,1,2), (0,2,2), (2,3,4) and (2,4,4)
#
# Constraints:
# 1 <= arr.length <= 300
# 	1 <= arr[i] <= 108
#

class Solution(object):
    def countTriplets(self, arr):
        """
        :type arr: List[int]
        :rtype: int
        """
        n = len(arr)
        count = 0
        
        # Iterate through all possible pairs (i, k)
        for i in range(n):
            xor_sum = 0
            for k in range(i, n):
                xor_sum ^= arr[k]
                
                # If the cumulative XOR from i to k is 0,
                # then all j between i+1 and k will satisfy a == b
                if xor_sum == 0:
                    count += (k - i)
        
        return count