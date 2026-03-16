# Source: https://leetcode.com/problems/sum-of-distances/   |   Difficulty: Medium
#
# Problem Description:
# You are given a 0-indexed integer array nums. There exists an array arr of length nums.length, where arr[i] is the sum of |i - j| over all j such that nums[j] == nums[i] and j != i. If there is no such j, set arr[i] to be 0.
#
# Return the array arr.
#
# Example:
# Input: nums = [1,3,1,1,2]
# Output: [5,0,3,4,0]
# Explanation: 
# When i = 0, nums[0] == nums[2] and nums[0] == nums[3]. Therefore, arr[0] = |0 - 2| + |0 - 3| = 5. 
# When i = 1, arr[1] = 0 because there is no other index with value 3.
# When i = 2, nums[2] == nums[0] and nums[2] == nums[3]. Therefore, arr[2] = |2 - 0| + |2 - 3| = 3. 
# When i = 3, nums[3] == nums[0] and nums[3] == nums[2]. Therefore, arr[3] = |3 - 0| + |3 - 2| = 4. 
# When i = 4, arr[4] = 0 because there is no other index with value 2.
#
# Constraints:
# 1 <= nums.length <= 105
# 	0 <= nums[i] <= 109
#
#
#  
# Note: This question is the same as  2121: Intervals Between Identical Elements.
#

class Solution(object):
    def distance(self, nums):
        """
        :type nums: List[int]
        :rtype: List[int]
        """
        from collections import defaultdict

        index_map = defaultdict(list)
        n = len(nums)
        result = [0] * n

        # Step 1: Collect indices for each unique number
        for i, num in enumerate(nums):
            index_map[num].append(i)

        # Step 2: Calculate distances for each group of indices
        for indices in index_map.values():
            m = len(indices)
            if m == 1:
                continue  # No other identical elements

            # Precompute prefix sums of indices
            prefix_sum = [0] * (m + 1)
            for i in range(m):
                prefix_sum[i + 1] = prefix_sum[i] + indices[i]

            # Calculate distances using the prefix sums
            for i in range(m):
                idx = indices[i]
                left_count = i
                right_count = m - i - 1

                left_sum = prefix_sum[i]
                right_sum = prefix_sum[m] - prefix_sum[i + 1]

                result[idx] = (idx * left_count - left_sum) + (right_sum - idx * right_count)

        return result