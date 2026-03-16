# Source: https://leetcode.com/problems/couples-holding-hands/   |   Difficulty: Hard
#
# Problem Description:
# There are n couples sitting in 2n seats arranged in a row and want to hold hands.
#
# The people and seats are represented by an integer array row where row[i] is the ID of the person sitting in the ith seat. The couples are numbered in order, the first couple being (0, 1), the second couple being (2, 3), and so on with the last couple being (2n - 2, 2n - 1).
#
# Return the minimum number of swaps so that every couple is sitting side by side. A swap consists of choosing any two people, then they stand up and switch seats.
#
# Example:
# Input: row = [0,2,1,3]
# Output: 1
# Explanation: We only need to swap the second (row[1]) and third (row[2]) person.
#
# Constraints:
# 2n == row.length
# 	2 <= n <= 30
# 	n is even.
# 	0 <= row[i] < 2n
# 	All the elements of row are unique.
#

class Solution(object):
    def minSwapsCouples(self, row):
        """
        :type row: List[int]
        :rtype: int
        """
        n = len(row)
        pos = {v: i for i, v in enumerate(row)}
        swaps = 0
        
        for i in range(0, n, 2):
            first_person = row[i]
            second_person = first_person ^ 1  # Partner's ID
            
            if row[i + 1] != second_person:
                partner_index = pos[second_person]
                
                # Swap the second person with the partner
                row[i + 1], row[partner_index] = row[partner_index], row[i + 1]
                
                # Update positions
                pos[row[partner_index]] = partner_index
                pos[row[i + 1]] = i + 1
                
                swaps += 1
        
        return swaps