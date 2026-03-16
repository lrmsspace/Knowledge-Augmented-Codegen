# Source: https://leetcode.com/problems/maximum-size-of-a-set-after-removals/   |   Difficulty: Medium
#
# Problem Description:
# You are given two 0-indexed integer arrays nums1 and nums2 of even length n.
#
# You must remove n / 2 elements from nums1 and n / 2 elements from nums2. After the removals, you insert the remaining elements of nums1 and nums2 into a set s.
#
# Return the maximum possible size of the set s.
#
# Example:
# Input: nums1 = [1,2,1,2], nums2 = [1,1,1,1]
# Output: 2
# Explanation: We remove two occurences of 1 from nums1 and nums2. After the removals, the arrays become equal to nums1 = [2,2] and nums2 = [1,1]. Therefore, s = {1,2}.
# It can be shown that 2 is the maximum possible size of the set s after the removals.
#
# Constraints:
# n == nums1.length == nums2.length
# 	1 <= n <= 2 * 104
# 	n is even.
# 	1 <= nums1[i], nums2[i] <= 109
#

class Solution(object):
    def maximumSetSize(self, nums1, nums2):
        """
        :type nums1: List[int]
        :type nums2: List[int]
        :rtype: int
        """
        from collections import Counter

        n = len(nums1)
        remove_count = n // 2

        count1 = Counter(nums1)
        count2 = Counter(nums2)

        common_elements = set(count1.keys()) & set(count2.keys())
        common_count = sum(min(count1[num], count2[num]) for num in common_elements)

        max_common_removal = min(common_count, remove_count)

        unique_nums1 = len(count1) - len(common_elements)
        unique_nums2 = len(count2) - len(common_elements)

        remaining_removals = remove_count - max_common_removal

        additional_unique1 = min(unique_nums1, remaining_removals)
        remaining_removals -= additional_unique1

        additional_unique2 = min(unique_nums2, remaining_removals)

        total_unique = (len(common_elements) + 
                        (unique_nums1 - additional_unique1) + 
                        (unique_nums2 - additional_unique2))

        return total_unique