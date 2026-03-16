# Source: https://leetcode.com/problems/count-good-triplets-in-an-array/   |   Difficulty: Hard
#
# Problem Description:
# You are given two 0-indexed arrays nums1 and nums2 of length n, both of which are permutations of [0, 1, ..., n - 1].
#
# A good triplet is a set of 3 distinct values which are present in increasing order by position both in nums1 and nums2. In other words, if we consider pos1v as the index of the value v in nums1 and pos2v as the index of the value v in nums2, then a good triplet will be a set (x, y, z) where 0 <= x, y, z <= n - 1, such that pos1x < pos1y < pos1z and pos2x < pos2y < pos2z.
#
# Return the total number of good triplets.
#
# Example:
# Input: nums1 = [2,0,1,3], nums2 = [0,1,2,3]
# Output: 1
# Explanation: 
# There are 4 triplets (x,y,z) such that pos1x < pos1y < pos1z. They are (2,0,1), (2,0,3), (2,1,3), and (0,1,3). 
# Out of those triplets, only the triplet (0,1,3) satisfies pos2x < pos2y < pos2z. Hence, there is only 1 good triplet.
#
# Constraints:
# n == nums1.length == nums2.length
# 	3 <= n <= 105
# 	0 <= nums1[i], nums2[i] <= n - 1
# 	nums1 and nums2 are permutations of [0, 1, ..., n - 1].
#

class Solution(object):
    def goodTriplets(self, nums1, nums2):
        """
        :type nums1: List[int]
        :type nums2: List[int]
        :rtype: int
        """
        n = len(nums1)
        pos_in_nums2 = [0] * n
        for i in range(n):
            pos_in_nums2[nums2[i]] = i

        bit = [0] * (n + 1)

        def update(index, value):
            index += 1
            while index <= n:
                bit[index] += value
                index += index & -index

        def query(index):
            index += 1
            result = 0
            while index > 0:
                result += bit[index]
                index -= index & -index
            return result

        left_smaller = [0] * n
        for i in range(n):
            pos = pos_in_nums2[nums1[i]]
            left_smaller[i] = query(pos - 1)
            update(pos, 1)

        bit = [0] * (n + 1)
        right_larger = [0] * n
        for i in range(n - 1, -1, -1):
            pos = pos_in_nums2[nums1[i]]
            right_larger[i] = query(n - 1) - query(pos)
            update(pos, 1)

        result = 0
        for i in range(n):
            result += left_smaller[i] * right_larger[i]

        return result