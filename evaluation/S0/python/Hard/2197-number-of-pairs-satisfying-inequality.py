# Source: https://leetcode.com/problems/number-of-pairs-satisfying-inequality/   |   Difficulty: Hard
#
# Problem Description:
# You are given two 0-indexed integer arrays nums1 and nums2, each of size n, and an integer diff. Find the number of pairs (i, j) such that:
#
#
# 	0 <= i < j <= n - 1 and
# 	nums1[i] - nums1[j] <= nums2[i] - nums2[j] + diff.
#
#
# Return the number of pairs that satisfy the conditions.
#
# Example:
# Input: nums1 = [3,2,5], nums2 = [2,2,1], diff = 1
# Output: 3
# Explanation:
# There are 3 pairs that satisfy the conditions:
# 1. i = 0, j = 1: 3 - 2 <= 2 - 2 + 1. Since i < j and 1 <= 1, this pair satisfies the conditions.
# 2. i = 0, j = 2: 3 - 5 <= 2 - 1 + 1. Since i < j and -2 <= 2, this pair satisfies the conditions.
# 3. i = 1, j = 2: 2 - 5 <= 2 - 1 + 1. Since i < j and -3 <= 2, this pair satisfies the conditions.
# Therefore, we return 3.
#
# Constraints:
# n == nums1.length == nums2.length
# 	2 <= n <= 105
# 	-104 <= nums1[i], nums2[i] <= 104
# 	-104 <= diff <= 104
#

class Solution(object):
    def numberOfPairs(self, nums1, nums2, diff):
        """
        :type nums1: List[int]
        :type nums2: List[int]
        :type diff: int
        :rtype: int
        """
        n = len(nums1)
        arr = [nums1[i] - nums2[i] for i in range(n)]
        
        def merge_sort_and_count(arr, left, right):
            if left >= right:
                return 0
            
            mid = (left + right) // 2
            count = merge_sort_and_count(arr, left, mid) + merge_sort_and_count(arr, mid + 1, right)
            
            # Count pairs
            j = mid + 1
            for i in range(left, mid + 1):
                while j <= right and arr[i] > arr[j] + diff:
                    j += 1
                count += (right - j + 1)
            
            # Merge step
            temp = []
            i, j = left, mid + 1
            while i <= mid and j <= right:
                if arr[i] <= arr[j]:
                    temp.append(arr[i])
                    i += 1
                else:
                    temp.append(arr[j])
                    j += 1
            while i <= mid:
                temp.append(arr[i])
                i += 1
            while j <= right:
                temp.append(arr[j])
                j += 1
            
            for i in range(len(temp)):
                arr[left + i] = temp[i]
            
            return count
        
        return merge_sort_and_count(arr, 0, n - 1)