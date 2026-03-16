# Source: https://leetcode.com/problems/reverse-pairs/   |   Difficulty: Hard
#
# Problem Description:
# Given an integer array nums, return the number of reverse pairs in the array.
#
# A reverse pair is a pair (i, j) where:
#
#
# 	0 <= i < j < nums.length and
# 	nums[i] > 2 * nums[j].
#
# Example:
# Input: nums = [1,3,2,3,1]
# Output: 2
# Explanation: The reverse pairs are:
# (1, 4) --> nums[1] = 3, nums[4] = 1, 3 > 2 * 1
# (3, 4) --> nums[3] = 3, nums[4] = 1, 3 > 2 * 1
#
# Constraints:
# 1 <= nums.length <= 5 * 104
# 	-231 <= nums[i] <= 231 - 1
#

class Solution(object):
    def reversePairs(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        if not nums:
            return 0

        def merge_sort_and_count(arr, left, right):
            if left >= right:
                return 0

            mid = (left + right) // 2
            count = merge_sort_and_count(arr, left, mid)
            count += merge_sort_and_count(arr, mid + 1, right)

            # Count reverse pairs
            j = mid + 1
            for i in range(left, mid + 1):
                while j <= right and arr[i] > 2 * arr[j]:
                    j += 1
                count += j - (mid + 1)

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

        return merge_sort_and_count(nums, 0, len(nums) - 1)