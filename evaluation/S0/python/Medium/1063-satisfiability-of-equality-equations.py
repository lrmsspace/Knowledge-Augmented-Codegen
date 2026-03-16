# Source: https://leetcode.com/problems/satisfiability-of-equality-equations/   |   Difficulty: Medium
#
# Problem Description:
# You are given an array of strings equations that represent relationships between variables where each string equations[i] is of length 4 and takes one of two different forms: "xi==yi" or "xi!=yi".Here, xi and yi are lowercase letters (not necessarily different) that represent one-letter variable names.
#
# Return true if it is possible to assign integers to variable names so as to satisfy all the given equations, or false otherwise.
#
# Example:
# Input: equations = ["a==b","b!=a"]
# Output: false
# Explanation: If we assign say, a = 1 and b = 1, then the first equation is satisfied, but not the second.
# There is no way to assign the variables to satisfy both equations.
#
# Constraints:
# 1 <= equations.length <= 500
# 	equations[i].length == 4
# 	equations[i][0] is a lowercase letter.
# 	equations[i][1] is either '=' or '!'.
# 	equations[i][2] is '='.
# 	equations[i][3] is a lowercase letter.
#

class Solution(object):
    def equationsPossible(self, equations):
        """
        :type equations: List[str]
        :rtype: bool
        """
        parent = {}

        def find(x):
            if parent.setdefault(x, x) != x:
                parent[x] = find(parent[x])
            return parent[x]

        def union(x, y):
            parent[find(x)] = find(y)

        for eq in equations:
            if eq[1] == '=':
                union(eq[0], eq[3])

        for eq in equations:
            if eq[1] == '!':
                if find(eq[0]) == find(eq[3]):
                    return False

        return True