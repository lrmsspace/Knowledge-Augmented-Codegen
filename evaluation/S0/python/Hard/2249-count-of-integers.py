# Source: https://leetcode.com/problems/count-of-integers/   |   Difficulty: Hard
#
# Problem Description:
# You are given two numeric strings num1 and num2 and two integers max_sum and min_sum. We denote an integer x to be good if:
#
#
# 	num1 <= x <= num2
# 	min_sum <= digit_sum(x) <= max_sum.
#
#
# Return the number of good integers. Since the answer may be large, return it modulo 109 + 7.
#
# Note that digit_sum(x) denotes the sum of the digits of x.
#
# Example:
# Input: num1 = "1", num2 = "12", min_sum = 1, max_sum = 8
# Output: 11
# Explanation: There are 11 integers whose sum of digits lies between 1 and 8 are 1,2,3,4,5,6,7,8,10,11, and 12. Thus, we return 11.
#
# Constraints:
# 1 <= num1 <= num2 <= 1022
# 	1 <= min_sum <= max_sum <= 400
#

class Solution(object):
    def count(self, num1, num2, min_sum, max_sum):
        """
        :type num1: str
        :type num2: str
        :type min_sum: int
        :type max_sum: int
        :rtype: int
        """
        MOD = 10**9 + 7

        def digit_dp(num, limit):
            n = len(num)
            dp = [[[0] * (limit + 1) for _ in range(2)] for _ in range(n + 1)]
            dp[0][1][0] = 1

            for i in range(n):
                for is_tight in range(2):
                    for curr_sum in range(limit + 1):
                        max_digit = int(num[i]) if is_tight else 9
                        for digit in range(max_digit + 1):
                            new_sum = curr_sum + digit
                            if new_sum <= limit:
                                new_tight = is_tight and (digit == max_digit)
                                dp[i + 1][new_tight][new_sum] = (dp[i + 1][new_tight][new_sum] + dp[i][is_tight][curr_sum]) % MOD

            total_count = 0
            for is_tight in range(2):
                for s in range(min_sum, limit + 1):
                    total_count = (total_count + dp[n][is_tight][s]) % MOD
            return total_count

        def decrement(num):
            num_list = list(num)
            i = len(num_list) - 1
            while i >= 0:
                if num_list[i] == '0':
                    num_list[i] = '9'
                    i -= 1
                else:
                    num_list[i] = str(int(num_list[i]) - 1)
                    break
            if num_list[0] == '0':
                num_list = num_list[1:]
            return ''.join(num_list) if num_list else '0'

        count_up_to_num2 = digit_dp(num2, max_sum)
        num1_minus_1 = decrement(num1)
        count_up_to_num1_minus_1 = digit_dp(num1_minus_1, max_sum) if num1_minus_1 != '0' else 0

        result = (count_up_to_num2 - count_up_to_num1_minus_1) % MOD
        return result