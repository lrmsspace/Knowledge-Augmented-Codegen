# Source: https://leetcode.com/problems/minimum-reverse-operations/   |   Difficulty: Hard
#
# Problem Description:
# You are given an integer n and an integer p representing an array arr of length n where all elements are set to 0's, except position p which is set to 1. You are also given an integer array banned containing restricted positions. Perform the following operation on arr:
#
#
# 	Reverse a subarray with size k if the single 1 is not set to a position in banned.
#
#
# Return an integer array answer with n results where the ith result is the minimum number of operations needed to bring the single 1 to position i in arr, or -1 if it is impossible.
#
# Example:
# Input: n = 4, p = 0, banned = [1,2], k = 4
#
# Output: [0,-1,-1,1]
#
# Explanation:
#
#
# 	Initially 1 is placed at position 0 so the number of operations we need for position 0 is 0.
# 	We can never place 1 on the banned positions, so the answer for positions 1 and 2 is -1.
# 	Perform the operation of size 4 to reverse the whole array.
# 	After a single operation 1 is at position 3 so the answer for position 3 is 1.
#
# Constraints:
# 1 <= n <= 105
# 	0 <= p <= n - 1
# 	0 <= banned.length <= n - 1
# 	0 <= banned[i] <= n - 1
# 	1 <= k <= n 
# 	banned[i] != p
# 	all values in banned are unique
#

class Solution(object):
    def minReverseOperations(self, n, p, banned, k):
        """
        :type n: int
        :type p: int
        :type banned: List[int]
        :type k: int
        :rtype: List[int]
        """
        from collections import deque
        banned = set(banned)
        res = [-1] * n
        res[p] = 0
        even = set(i for i in range(n) if i % 2 == 0 and i != p and i not in banned)
        odd = set(i for i in range(n) if i % 2 == 1 and i != p and i not in banned)
        queue = deque([p])
        step = 0
        
        while queue:
            step += 1
            for _ in range(len(queue)):
                curr = queue.popleft()
                left = max(0, curr - k + 1)
                right = min(n - k, curr)
                start = left + (k - 1 - (curr - left))
                end = right + (curr - right)
                
                if start % 2 == 0:
                    candidates = even
                else:
                    candidates = odd
                
                to_remove = []
                for pos in candidates:
                    if start <= pos <= end and (pos - start) % 2 == 0:
                        res[pos] = step
                        queue.append(pos)
                        to_remove.append(pos)
                
                for pos in to_remove:
                    candidates.remove(pos)
        
        return res