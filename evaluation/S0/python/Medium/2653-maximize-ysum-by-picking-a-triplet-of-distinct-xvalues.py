# Source: https://leetcode.com/problems/maximize-ysum-by-picking-a-triplet-of-distinct-xvalues/   |   Difficulty: Medium
#
# Problem Description:
# You are given two integer arrays x and y, each of length n. You must choose three distinct indices i, j, and k such that:
#
#
# 	x[i] != x[j]
# 	x[j] != x[k]
# 	x[k] != x[i]
#
#
# Your goal is to maximize the value of y[i] + y[j] + y[k] under these conditions. Return the maximum possible sum that can be obtained by choosing such a triplet of indices.
#
# If no such triplet exists, return -1.
#
# Example:
# Input: x = [1,2,1,3,2], y = [5,3,4,6,2]
#
# Output: 14
#
# Explanation:
#
#
# 	Choose i = 0 (x[i] = 1, y[i] = 5), j = 1 (x[j] = 2, y[j] = 3), k = 3 (x[k] = 3, y[k] = 6).
# 	All three values chosen from x are distinct. 5 + 3 + 6 = 14 is the maximum we can obtain. Hence, the output is 14.
#
# Constraints:
# n == x.length == y.length
# 	3 <= n <= 105
# 	1 <= x[i], y[i] <= 106
#

class Solution(object):
    def maxSumDistinctTriplet(self, x, y):
        """
        :type x: List[int]
        :type y: List[int]
        :rtype: int
        """
        from collections import defaultdict
        value_map = defaultdict(list)
        
        for xi, yi in zip(x, y):
            value_map[xi].append(yi)
        
        # For each distinct x value, keep only the top 3 y values
        filtered_values = []
        for yi_list in value_map.values():
            yi_list.sort(reverse=True)
            filtered_values.append(yi_list[:3])
        
        # Flatten the list and sort to get the top y values
        all_y_values = []
        for sublist in filtered_values:
            all_y_values.extend(sublist)
        
        all_y_values.sort(reverse=True)
        
        # Try to pick the top 3 distinct x values
        max_sum = -1
        n = len(all_y_values)
        
        for i in range(n):
            for j in range(i + 1, n):
                for k in range(j + 1, n):
                    if (all_y_values[i] != all_y_values[j] and 
                        all_y_values[j] != all_y_values[k] and 
                        all_y_values[i] != all_y_values[k]):
                        current_sum = all_y_values[i] + all_y_values[j] + all_y_values[k]
                        max_sum = max(max_sum, current_sum)
                        break  # No need to check further k's for this i, j
        
        return max_sum