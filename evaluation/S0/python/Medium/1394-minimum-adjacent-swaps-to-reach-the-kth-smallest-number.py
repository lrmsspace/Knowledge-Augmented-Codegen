# Source: https://leetcode.com/problems/minimum-adjacent-swaps-to-reach-the-kth-smallest-number/   |   Difficulty: Medium
#
# Problem Description:
# You are given a string num, representing a large integer, and an integer k.
#
# We call some integer wonderful if it is a permutation of the digits in num and is greater in value than num. There can be many wonderful integers. However, we only care about the smallest-valued ones.
#
#
# 	For example, when num = "5489355142":
#
# 	
# 		The 1st smallest wonderful integer is "5489355214".
# 		The 2nd smallest wonderful integer is "5489355241".
# 		The 3rd smallest wonderful integer is "5489355412".
# 		The 4th smallest wonderful integer is "5489355421".
# 	
# 	
#
#
# Return the minimum number of adjacent digit swaps that needs to be applied to num to reach the kth smallest wonderful integer.
#
# The tests are generated in such a way that kth smallest wonderful integer exists.
#
# Example:
# Input: num = "5489355142", k = 4
# Output: 2
# Explanation: The 4th smallest wonderful number is "5489355421". To get this number:
# - Swap index 7 with index 8: "5489355142" -> "5489355412"
# - Swap index 8 with index 9: "5489355412" -> "5489355421"
#
# Constraints:
# 2 <= num.length <= 1000
# 	1 <= k <= 1000
# 	num only consists of digits.
#

class Solution(object):
    def getMinSwaps(self, num, k):
        """
        :type num: str
        :type k: int
        :rtype: int
        """
        from collections import deque

        def get_kth_permutation(s, k):
            s = list(s)
            for _ in range(k):
                i = len(s) - 2
                while i >= 0 and s[i] >= s[i + 1]:
                    i -= 1
                j = len(s) - 1
                while s[j] <= s[i]:
                    j -= 1
                s[i], s[j] = s[j], s[i]
                s[i + 1:] = reversed(s[i + 1:])
            return ''.join(s)

        target = get_kth_permutation(num, k)
        num_list = list(num)
        swaps = 0

        for i in range(len(num_list)):
            if num_list[i] != target[i]:
                j = i + 1
                while num_list[j] != target[i]:
                    j += 1
                while j > i:
                    num_list[j], num_list[j - 1] = num_list[j - 1], num_list[j]
                    swaps += 1
                    j -= 1

        return swaps