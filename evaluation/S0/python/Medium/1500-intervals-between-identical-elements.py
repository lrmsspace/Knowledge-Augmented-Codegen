# Source: https://leetcode.com/problems/intervals-between-identical-elements/   |   Difficulty: Medium
#
# Problem Description:
# You are given a 0-indexed array of n integers arr.
#
# The interval between two elements in arr is defined as the absolute difference between their indices. More formally, the interval between arr[i] and arr[j] is |i - j|.
#
# Return an array intervals of length n where intervals[i] is the sum of intervals between arr[i] and each element in arr with the same value as arr[i].
#
# Note: |x| is the absolute value of x.
#
# Example:
# Input: arr = [2,1,3,1,2,3,3]
# Output: [4,2,7,2,4,4,5]
# Explanation:
# - Index 0: Another 2 is found at index 4. |0 - 4| = 4
# - Index 1: Another 1 is found at index 3. |1 - 3| = 2
# - Index 2: Two more 3s are found at indices 5 and 6. |2 - 5| + |2 - 6| = 7
# - Index 3: Another 1 is found at index 1. |3 - 1| = 2
# - Index 4: Another 2 is found at index 0. |4 - 0| = 4
# - Index 5: Two more 3s are found at indices 2 and 6. |5 - 2| + |5 - 6| = 4
# - Index 6: Two more 3s are found at indices 2 and 5. |6 - 2| + |6 - 5| = 5
#
# Constraints:
# n == arr.length
# 	1 <= n <= 105
# 	1 <= arr[i] <= 105
#
#
#  
# Note: This question is the same as  2615: Sum of Distances.
#

class Solution(object):
    def getDistances(self, arr):
        """
        :type arr: List[int]
        :rtype: List[int]
        """
        from collections import defaultdict

        index_map = defaultdict(list)
        n = len(arr)
        result = [0] * n

        # Step 1: Collect indices for each value
        for i, value in enumerate(arr):
            index_map[value].append(i)

        # Step 2: Calculate distances for each group of identical elements
        for indices in index_map.values():
            m = len(indices)
            if m == 1:
                continue

            prefix_sum = [0] * (m + 1)
            for i in range(m):
                prefix_sum[i + 1] = prefix_sum[i] + indices[i]

            for i in range(m):
                left_count = i
                right_count = m - i - 1
                left_sum = prefix_sum[i]
                right_sum = prefix_sum[m] - prefix_sum[i + 1]

                result[indices[i]] = (indices[i] * left_count - left_sum) + (right_sum - indices[i] * right_count)

        return result