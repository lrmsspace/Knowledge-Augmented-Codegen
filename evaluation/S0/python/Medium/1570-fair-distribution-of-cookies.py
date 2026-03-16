# Source: https://leetcode.com/problems/fair-distribution-of-cookies/   |   Difficulty: Medium
#
# Problem Description:
# You are given an integer array cookies, where cookies[i] denotes the number of cookies in the ith bag. You are also given an integer k that denotes the number of children to distribute all the bags of cookies to. All the cookies in the same bag must go to the same child and cannot be split up.
#
# The unfairness of a distribution is defined as the maximum total cookies obtained by a single child in the distribution.
#
# Return the minimum unfairness of all distributions.
#
# Example:
# Input: cookies = [8,15,10,20,8], k = 2
# Output: 31
# Explanation: One optimal distribution is [8,15,8] and [10,20]
# - The 1st child receives [8,15,8] which has a total of 8 + 15 + 8 = 31 cookies.
# - The 2nd child receives [10,20] which has a total of 10 + 20 = 30 cookies.
# The unfairness of the distribution is max(31,30) = 31.
# It can be shown that there is no distribution with an unfairness less than 31.
#
# Constraints:
# 2 <= cookies.length <= 8
# 	1 <= cookies[i] <= 105
# 	2 <= k <= cookies.length
#

class Solution(object):
    def distributeCookies(self, cookies, k):
        """
        :type cookies: List[int]
        :type k: int
        :rtype: int
        """
        n = len(cookies)
        res = float('inf')
        distribution = [0] * k

        def backtrack(i):
            nonlocal res
            if i == n:
                res = min(res, max(distribution))
                return

            for j in range(k):
                distribution[j] += cookies[i]
                if max(distribution) < res:
                    backtrack(i + 1)
                distribution[j] -= cookies[i]

        backtrack(0)
        return res