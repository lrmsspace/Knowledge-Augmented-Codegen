# Source: https://leetcode.com/problems/minimum-space-wasted-from-packaging/   |   Difficulty: Hard
#
# Problem Description:
# You have n packages that you are trying to place in boxes, one package in each box. There are m suppliers that each produce boxes of different sizes (with infinite supply). A package can be placed in a box if the size of the package is less than or equal to the size of the box.
#
# The package sizes are given as an integer array packages, where packages[i] is the size of the ith package. The suppliers are given as a 2D integer array boxes, where boxes[j] is an array of box sizes that the jth supplier produces.
#
# You want to choose a single supplier and use boxes from them such that the total wasted space is minimized. For each package in a box, we define the space wasted to be size of the box - size of the package. The total wasted space is the sum of the space wasted in all the boxes.
#
#
# 	For example, if you have to fit packages with sizes [2,3,5] and the supplier offers boxes of sizes [4,8], you can fit the packages of size-2 and size-3 into two boxes of size-4 and the package with size-5 into a box of size-8. This would result in a waste of (4-2) + (4-3) + (8-5) = 6.
#
#
# Return the minimum total wasted space by choosing the box supplier optimally, or -1 if it is impossible to fit all the packages inside boxes. Since the answer may be large, return it modulo 109 + 7.
#
# Example:
# Input: packages = [2,3,5], boxes = [[4,8],[2,8]]
# Output: 6
# Explanation: It is optimal to choose the first supplier, using two size-4 boxes and one size-8 box.
# The total waste is (4-2) + (4-3) + (8-5) = 6.
#
# Constraints:
# n == packages.length
# 	m == boxes.length
# 	1 <= n <= 105
# 	1 <= m <= 105
# 	1 <= packages[i] <= 105
# 	1 <= boxes[j].length <= 105
# 	1 <= boxes[j][k] <= 105
# 	sum(boxes[j].length) <= 105
# 	The elements in boxes[j] are distinct.
#

class Solution(object):
    def minWastedSpace(self, packages, boxes):
        """
        :type packages: List[int]
        :type boxes: List[List[int]]
        :rtype: int
        """
        MOD = 10**9 + 7
        packages.sort()
        n = len(packages)
        prefix_sum = [0] * (n + 1)
        for i in range(n):
            prefix_sum[i + 1] = prefix_sum[i] + packages[i]

        min_waste = float('inf')
        for box_sizes in boxes:
            box_sizes.sort()
            if box_sizes[-1] < packages[-1]:
                continue

            waste = 0
            prev_index = 0
            for box_size in box_sizes:
                index = self.upper_bound(packages, box_size)
                waste += box_size * (index - prev_index) - (prefix_sum[index] - prefix_sum[prev_index])
                prev_index = index
                if prev_index == n:
                    break

            min_waste = min(min_waste, waste)

        return min_waste % MOD if min_waste != float('inf') else -1