# Source: https://leetcode.com/problems/find-the-grid-of-region-average/   |   Difficulty: Medium
#
# Problem Description:
# You are given m x n grid image which represents a grayscale image, where image[i][j] represents a pixel with intensity in the range [0..255]. You are also given a non-negative integer threshold.
#
# Two pixels are adjacent if they share an edge.
#
# A region is a 3 x 3 subgrid where the absolute difference in intensity between any two adjacent pixels is less than or equal to threshold.
#
# All pixels in a region belong to that region, note that a pixel can belong to multiple regions.
#
# You need to calculate a m x n grid result, where result[i][j] is the average intensity of the regions to which image[i][j] belongs, rounded down to the nearest integer. If image[i][j] belongs to multiple regions, result[i][j] is the average of the rounded-down average intensities of these regions, rounded down to the nearest integer. If image[i][j] does not belong to any region, result[i][j] is equal to image[i][j].
#
# Return the grid result.
#
# Example:
# Input: image = [[5,6,7,10],[8,9,10,10],[11,12,13,10]], threshold = 3
#
# Output: [[9,9,9,9],[9,9,9,9],[9,9,9,9]]
#
# Explanation:
#
#
#
# There are two regions as illustrated above. The average intensity of the first region is 9, while the average intensity of the second region is 9.67 which is rounded down to 9. The average intensity of both of the regions is (9 + 9) / 2 = 9. As all the pixels belong to either region 1, region 2, or both of them, the intensity of every pixel in the result is 9.
#
# Please note that the rounded-down values are used when calculating the average of multiple regions, hence the calculation is done using 9 as the average intensity of region 2, not 9.67.
#
# Constraints:
# 3 <= n, m <= 500
# 	0 <= image[i][j] <= 255
# 	0 <= threshold <= 255
#

class Solution(object):
    def resultGrid(self, image, threshold):
        """
        :type image: List[List[int]]
        :type threshold: int
        :rtype: List[List[int]]
        """
        m, n = len(image), len(image[0])
        region_sums = [[0] * n for _ in range(m)]
        region_counts = [[0] * n for _ in range(m)]

        for i in range(m - 2):
            for j in range(n - 2):
                if self.is_region(image, i, j, threshold):
                    region_avg = self.calculate_region_average(image, i, j)
                    for x in range(i, i + 3):
                        for y in range(j, j + 3):
                            region_sums[x][y] += region_avg
                            region_counts[x][y] += 1

        result = [[0] * n for _ in range(m)]
        for i in range(m):
            for j in range(n):
                if region_counts[i][j] > 0:
                    result[i][j] = region_sums[i][j] // region_counts[i][j]
                else:
                    result[i][j] = image[i][j]

        return result