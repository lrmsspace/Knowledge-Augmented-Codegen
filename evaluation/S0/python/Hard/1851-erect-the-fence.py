# Source: https://leetcode.com/problems/erect-the-fence/   |   Difficulty: Hard
#
# Problem Description:
# You are given an array trees where trees[i] = [xi, yi] represents the location of a tree in the garden.
#
# Fence the entire garden using the minimum length of rope, as it is expensive. The garden is well-fenced only if all the trees are enclosed.
#
# Return the coordinates of trees that are exactly located on the fence perimeter. You may return the answer in any order.
#
# Example:
# Input: trees = [[1,1],[2,2],[2,0],[2,4],[3,3],[4,2]]
# Output: [[1,1],[2,0],[4,2],[3,3],[2,4]]
# Explanation: All the trees will be on the perimeter of the fence except the tree at [2, 2], which will be inside the fence.
#
# Constraints:
# 1 <= trees.length <= 3000
# 	trees[i].length == 2
# 	0 <= xi, yi <= 100
# 	All the given positions are unique.
#

class Solution(object):
    def outerTrees(self, trees):
        """
        :type trees: List[List[int]]
        :rtype: List[List[int]]
        """
        def cross(o, a, b):
            return (a[0] - o[0]) * (b[1] - o[1]) - (a[1] - o[1]) * (b[0] - o[0])

        points = sorted(trees)
        lower = []
        for p in points:
            while len(lower) >= 2 and cross(lower[-2], lower[-1], p) < 0:
                lower.pop()
            lower.append(p)

        upper = []
        for p in reversed(points):
            while len(upper) >= 2 and cross(upper[-2], upper[-1], p) < 0:
                upper.pop()
            upper.append(p)

        return list(set(map(tuple, lower[:-1] + upper[:-1])))