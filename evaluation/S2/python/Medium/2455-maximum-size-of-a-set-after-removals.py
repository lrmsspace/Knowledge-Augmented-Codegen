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
# Helpful references (internal KB):
# - N/A
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def maximumSetSize(self, nums1, nums2):
        """
        :type nums1: List[int]
        :type nums2: List[int]
        :rtype: int
        """
        from collections import Counter
        
        count1 = Counter(nums1)
        count2 = Counter(nums2)
        
        # Calculate the number of elements that can be removed from each array
        removals = len(nums1) // 2
        
        # Calculate the number of unique elements in both arrays
        unique_elements = set(count1.keys()) | set(count2.keys())
        
        # Calculate the maximum size of the set after removals
        max_set_size = 0
        
        for elem in unique_elements:
            # Calculate how many times this element can be removed from both arrays
            remove_from_nums1 = min(count1[elem], removals)
            remove_from_nums2 = min(count2[elem], removals)
            
            # Update the maximum set size based on the remaining occurrences of this element
            if count1[elem] - remove_from_nums1 > 0 or count2[elem] - remove_from_nums2 > 0:
                max_set_size += 1
        
        return max_set_size