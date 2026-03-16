# Source: https://leetcode.com/problems/odd-even-jump/   |   Difficulty: Hard
#
# Problem Description:
# You are given an integer array arr. From some starting index, you can make a series of jumps. The (1st, 3rd, 5th, ...) jumps in the series are called odd-numbered jumps, and the (2nd, 4th, 6th, ...) jumps in the series are called even-numbered jumps. Note that the jumps are numbered, not the indices.
#
# You may jump forward from index i to index j (with i < j) in the following way:
#
#
# 	During odd-numbered jumps (i.e., jumps 1, 3, 5, ...), you jump to the index j such that arr[i] <= arr[j] and arr[j] is the smallest possible value. If there are multiple such indices j, you can only jump to the smallest such index j.
# 	During even-numbered jumps (i.e., jumps 2, 4, 6, ...), you jump to the index j such that arr[i] >= arr[j] and arr[j] is the largest possible value. If there are multiple such indices j, you can only jump to the smallest such index j.
# 	It may be the case that for some index i, there are no legal jumps.
#
#
# A starting index is good if, starting from that index, you can reach the end of the array (index arr.length - 1) by jumping some number of times (possibly 0 or more than once).
#
# Return the number of good starting indices.
#
# Example:
# Input: arr = [10,13,12,14,15]
# Output: 2
# Explanation: 
# From starting index i = 0, we can make our 1st jump to i = 2 (since arr[2] is the smallest among arr[1], arr[2], arr[3], arr[4] that is greater or equal to arr[0]), then we cannot jump any more.
# From starting index i = 1 and i = 2, we can make our 1st jump to i = 3, then we cannot jump any more.
# From starting index i = 3, we can make our 1st jump to i = 4, so we have reached the end.
# From starting index i = 4, we have reached the end already.
# In total, there are 2 different starting indices i = 3 and i = 4, where we can reach the end with some number of
# jumps.
#
# Constraints:
# 1 <= arr.length <= 2 * 104
# 	0 <= arr[i] < 105
#

class Solution(object):
    def oddEvenJumps(self, arr):
        """
        :type arr: List[int]
        :rtype: int
        """
        n = len(arr)
        odd_next = [0] * n
        even_next = [0] * n

        sorted_indices = sorted(range(n), key=lambda i: (arr[i], i))
        stack = []
        for i in sorted_indices:
            while stack and stack[-1] < i:
                odd_next[stack.pop()] = i
            stack.append(i)

        sorted_indices = sorted(range(n), key=lambda i: (-arr[i], i))
        stack = []
        for i in sorted_indices:
            while stack and stack[-1] < i:
                even_next[stack.pop()] = i
            stack.append(i)

        odd_reachable = [False] * n
        even_reachable = [False] * n
        odd_reachable[-1] = True
        even_reachable[-1] = True

        for i in range(n - 2, -1, -1):
            if odd_next[i]:
                odd_reachable[i] = even_reachable[odd_next[i]]
            if even_next[i]:
                even_reachable[i] = odd_reachable[even_next[i]]

        return sum(odd_reachable)