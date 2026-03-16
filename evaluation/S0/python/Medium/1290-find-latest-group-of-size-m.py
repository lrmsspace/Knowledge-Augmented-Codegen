# Source: https://leetcode.com/problems/find-latest-group-of-size-m/   |   Difficulty: Medium
#
# Problem Description:
# Given an array arr that represents a permutation of numbers from 1 to n.
#
# You have a binary string of size n that initially has all its bits set to zero. At each step i (assuming both the binary string and arr are 1-indexed) from 1 to n, the bit at position arr[i] is set to 1.
#
# You are also given an integer m. Find the latest step at which there exists a group of ones of length m. A group of ones is a contiguous substring of 1's such that it cannot be extended in either direction.
#
# Return the latest step at which there exists a group of ones of length exactly m. If no such group exists, return -1.
#
# Example:
# Input: arr = [3,5,1,2,4], m = 1
# Output: 4
# Explanation: 
# Step 1: "00100", groups: ["1"]
# Step 2: "00101", groups: ["1", "1"]
# Step 3: "10101", groups: ["1", "1", "1"]
# Step 4: "11101", groups: ["111", "1"]
# Step 5: "11111", groups: ["11111"]
# The latest step at which there exists a group of size 1 is step 4.
#
# Constraints:
# n == arr.length
# 	1 <= m <= n <= 105
# 	1 <= arr[i] <= n
# 	All integers in arr are distinct.
#

class Solution(object):
    def findLatestStep(self, arr, m):
        """
        :type arr: List[int]
        :type m: int
        :rtype: int
        """
        n = len(arr)
        if m == n:
            return n
        
        length = [0] * (n + 2)
        count = [0] * (n + 1)
        res = -1
        
        for step in range(n):
            pos = arr[step]
            left = length[pos - 1]
            right = length[pos + 1]
            total = left + right + 1
            
            length[pos - left] = total
            length[pos + right] = total
            
            count[left] -= 1
            count[right] -= 1
            count[total] += 1
            
            if count[m] > 0:
                res = step + 1
                
        return res