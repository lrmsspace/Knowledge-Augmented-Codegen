# Source: https://leetcode.com/problems/minimum-operations-to-make-a-special-number/   |   Difficulty: Medium
#
# Problem Description:
# You are given a 0-indexed string num representing a non-negative integer.
#
# In one operation, you can pick any digit of num and delete it. Note that if you delete all the digits of num, num becomes 0.
#
# Return the minimum number of operations required to make num special.
#
# An integer x is considered special if it is divisible by 25.
#
# Example:
# Input: num = "2245047"
# Output: 2
# Explanation: Delete digits num[5] and num[6]. The resulting number is "22450" which is special since it is divisible by 25.
# It can be shown that 2 is the minimum number of operations required to get a special number.
#
# Constraints:
# 1 <= num.length <= 100
# 	num only consists of digits '0' through '9'.
# 	num does not contain any leading zeros.
#

class Solution(object):
    def minimumOperations(self, num):
        """
        :type num: str
        :rtype: int
        """
        targets = ['00', '25', '50', '75']
        min_ops = float('inf')
        
        for target in targets:
            t1, t2 = target
            ops = 0
            found_t2 = False
            
            # Traverse from the end to find t2
            for digit in reversed(num):
                if not found_t2:
                    if digit == t2:
                        found_t2 = True
                    else:
                        ops += 1
                else:
                    if digit == t1:
                        break
                    else:
                        ops += 1
            
            if found_t2 and (t1 in num[:len(num) - ops - 1]):
                min_ops = min(min_ops, ops)
        
        return min_ops if min_ops != float('inf') else len(num)