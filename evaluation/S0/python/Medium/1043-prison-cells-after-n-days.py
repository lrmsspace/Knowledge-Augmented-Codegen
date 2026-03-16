# Source: https://leetcode.com/problems/prison-cells-after-n-days/   |   Difficulty: Medium
#
# Problem Description:
# There are 8 prison cells in a row and each cell is either occupied or vacant.
#
# Each day, whether the cell is occupied or vacant changes according to the following rules:
#
#
# 	If a cell has two adjacent neighbors that are both occupied or both vacant, then the cell becomes occupied.
# 	Otherwise, it becomes vacant.
#
#
# Note that because the prison is a row, the first and the last cells in the row can't have two adjacent neighbors.
#
# You are given an integer array cells where cells[i] == 1 if the ith cell is occupied and cells[i] == 0 if the ith cell is vacant, and you are given an integer n.
#
# Return the state of the prison after n days (i.e., n such changes described above).
#
# Example:
# Input: cells = [0,1,0,1,1,0,0,1], n = 7
# Output: [0,0,1,1,0,0,0,0]
# Explanation: The following table summarizes the state of the prison on each day:
# Day 0: [0, 1, 0, 1, 1, 0, 0, 1]
# Day 1: [0, 1, 1, 0, 0, 0, 0, 0]
# Day 2: [0, 0, 0, 0, 1, 1, 1, 0]
# Day 3: [0, 1, 1, 0, 0, 1, 0, 0]
# Day 4: [0, 0, 0, 0, 0, 1, 0, 0]
# Day 5: [0, 1, 1, 1, 0, 1, 0, 0]
# Day 6: [0, 0, 1, 0, 1, 1, 0, 0]
# Day 7: [0, 0, 1, 1, 0, 0, 0, 0]
#
# Constraints:
# cells.length == 8
# 	cells[i] is either 0 or 1.
# 	1 <= n <= 109
#

class Solution(object):
    def prisonAfterNDays(self, cells, n):
        """
        :type cells: List[int]
        :type n: int
        :rtype: List[int]
        """
        seen = {}
        is_cycle = False
        cycle_length = 0

        for day in range(n):
            next_cells = [0] * 8
            for i in range(1, 7):
                if cells[i - 1] == cells[i + 1]:
                    next_cells[i] = 1
                else:
                    next_cells[i] = 0

            cells_tuple = tuple(next_cells)
            if cells_tuple in seen:
                is_cycle = True
                cycle_length = day - seen[cells_tuple]
                break
            else:
                seen[cells_tuple] = day

            cells = next_cells

        if is_cycle:
            remaining_days = (n - day - 1) % cycle_length
            for _ in range(remaining_days):
                next_cells = [0] * 8
                for i in range(1, 7):
                    if cells[i - 1] == cells[i + 1]:
                        next_cells[i] = 1
                    else:
                        next_cells[i] = 0
                cells = next_cells

        return cells