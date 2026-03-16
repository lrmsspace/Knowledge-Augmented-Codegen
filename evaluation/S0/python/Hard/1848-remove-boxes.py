# Source: https://leetcode.com/problems/remove-boxes/   |   Difficulty: Hard
#
# Problem Description:
# You are given several boxes with different colors represented by different positive numbers.
#
# You may experience several rounds to remove boxes until there is no box left. Each time you can choose some continuous boxes with the same color (i.e., composed of k boxes, k >= 1), remove them and get k * k points.
#
# Return the maximum points you can get.
#
# Example:
# Input: boxes = [1,3,2,2,2,3,4,3,1]
# Output: 23
# Explanation:
# [1, 3, 2, 2, 2, 3, 4, 3, 1] 
# ----> [1, 3, 3, 4, 3, 1] (3*3=9 points) 
# ----> [1, 3, 3, 3, 1] (1*1=1 points) 
# ----> [1, 1] (3*3=9 points) 
# ----> [] (2*2=4 points)
#
# Constraints:
# 1 <= boxes.length <= 100
# 	1 <= boxes[i] <= 100
#

class Solution(object):
    def removeBoxes(self, boxes):
        """
        :type boxes: List[int]
        :rtype: int
        """
        n = len(boxes)
        dp = [[[0] * n for _ in range(n)] for _ in range(n)]

        def calculatePoints(l, r, k):
            if l > r:
                return 0
            if dp[l][r][k] != 0:
                return dp[l][r][k]

            while l + 1 <= r and boxes[l] == boxes[l + 1]:
                l += 1
                k += 1

            res = (k + 1) * (k + 1) + calculatePoints(l + 1, r, 0)

            for m in range(l + 1, r + 1):
                if boxes[m] == boxes[l]:
                    res = max(res, calculatePoints(l + 1, m - 1, 0) + calculatePoints(m, r, k + 1))

            dp[l][r][k] = res
            return res

        return calculatePoints(0, n - 1, 0)