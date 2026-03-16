# Source: https://leetcode.com/problems/longest-common-subpath/   |   Difficulty: Hard
#
# Problem Description:
# There is a country of n cities numbered from 0 to n - 1. In this country, there is a road connecting every pair of cities.
#
# There are m friends numbered from 0 to m - 1 who are traveling through the country. Each one of them will take a path consisting of some cities. Each path is represented by an integer array that contains the visited cities in order. The path may contain a city more than once, but the same city will not be listed consecutively.
#
# Given an integer n and a 2D integer array paths where paths[i] is an integer array representing the path of the ith friend, return the length of the longest common subpath that is shared by every friend's path, or 0 if there is no common subpath at all.
#
# A subpath of a path is a contiguous sequence of cities within that path.
#
# Example:
# Input: n = 5, paths = [[0,1,2,3,4],
#                        [2,3,4],
#                        [4,0,1,2,3]]
# Output: 2
# Explanation: The longest common subpath is [2,3].
#
# Constraints:
# 1 <= n <= 105
# 	m == paths.length
# 	2 <= m <= 105
# 	sum(paths[i].length) <= 105
# 	0 <= paths[i][j] < n
# 	The same city is not listed multiple times consecutively in paths[i].
#

class Solution(object):
    def longestCommonSubpath(self, n, paths):
        """
        :type n: int
        :type paths: List[List[int]]
        :rtype: int
        """
        def check(length):
            MOD = (1 << 61) - 1
            BASE = 113
            baseL = pow(BASE, length, MOD)

            common_hashes = None

            for path in paths:
                current_hashes = set()
                current_hash = 0

                for i in range(len(path)):
                    current_hash = (current_hash * BASE + path[i]) % MOD

                    if i >= length:
                        current_hash = (current_hash - path[i - length] * baseL) % MOD
                        if current_hash < 0:
                            current_hash += MOD

                    if i >= length - 1:
                        current_hashes.add(current_hash)

                if common_hashes is None:
                    common_hashes = current_hashes
                else:
                    common_hashes &= current_hashes

                if not common_hashes:
                    return False

            return True

        left, right = 0, min(len(path) for path in paths) + 1
        result = 0

        while left < right:
            mid = (left + right) // 2
            if check(mid):
                result = mid
                left = mid + 1
            else:
                right = mid

        return result