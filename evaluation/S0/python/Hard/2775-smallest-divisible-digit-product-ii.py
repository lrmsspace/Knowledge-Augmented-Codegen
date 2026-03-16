# Source: https://leetcode.com/problems/smallest-divisible-digit-product-ii/   |   Difficulty: Hard
#
# Problem Description:
# You are given a string num which represents a positive integer, and an integer t.
#
# A number is called zero-free if none of its digits are 0.
#
# Return a string representing the smallest zero-free number greater than or equal to num such that the product of its digits is divisible by t. If no such number exists, return "-1".
#
# Example:
# Input: num = "1234", t = 256
#
# Output: "1488"
#
# Explanation:
#
# The smallest zero-free number that is greater than 1234 and has the product of its digits divisible by 256 is 1488, with the product of its digits equal to 256.
#
# Constraints:
# 2 <= num.length <= 2 * 105
# 	num consists only of digits in the range ['0', '9'].
# 	num does not contain leading zeros.
# 	1 <= t <= 1014
#

class Solution(object):
    def smallestNumber(self, num, t):
        """
        :type num: str
        :type t: int
        :rtype: str
        """
        from math import gcd
        from functools import reduce

        def prime_factors(n):
            i = 2
            factors = {}
            while i * i <= n:
                while (n % i) == 0:
                    if i in factors:
                        factors[i] += 1
                    else:
                        factors[i] = 1
                    n //= i
                i += 1
            if n > 1:
                factors[n] = 1
            return factors

        t_factors = prime_factors(t)
        digit_factors = {i: prime_factors(i) for i in range(1, 10)}

        def can_form_product(digit_count):
            product_factors = {}
            for digit, count in digit_count.items():
                for prime, exp in digit_factors[digit].items():
                    if prime in product_factors:
                        product_factors[prime] += exp * count
                    else:
                        product_factors[prime] = exp * count
            for prime, exp in t_factors.items():
                if product_factors.get(prime, 0) < exp:
                    return False
            return True

        n = len(num)
        num_list = list(map(int, num))

        for i in range(n - 1, -1, -1):
            for d in range(num_list[i] + 1, 10):
                candidate_digits = num_list[:i] + [d] + [1] * (n - i - 1)
                digit_count = {}
                for digit in candidate_digits:
                    if digit in digit_count:
                        digit_count[digit] += 1
                    else:
                        digit_count[digit] = 1
                if can_form_product(digit_count):
                    result = ''.join(map(str, candidate_digits))
                    return result

        for length in range(n + 1, n + 20):  
            candidate_digits = [1] * length
            digit_count = {1: length}
            if can_form_product(digit_count):
                result = ''.join(map(str, candidate_digits))
                return result

        return "-1"