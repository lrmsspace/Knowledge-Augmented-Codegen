# Source: https://leetcode.com/problems/digit-operations-to-make-two-integers-equal/   |   Difficulty: Medium
#
# Problem Description:
# You are given two integers n and m that consist of the same number of digits.
#
# You can perform the following operations any number of times:
#
#
# 	Choose any digit from n that is not 9 and increase it by 1.
# 	Choose any digit from n that is not 0 and decrease it by 1.
#
#
# The integer n must not be a prime number at any point, including its original value and after each operation.
#
# The cost of a transformation is the sum of all values that n takes throughout the operations performed.
#
# Return the minimum cost to transform n into m. If it is impossible, return -1.
#
# Example:
# Input: n = 10, m = 12
#
# Output: 85
#
# Explanation:
#
# We perform the following operations:
#
#
# 	Increase the first digit, now n = 20.
# 	Increase the second digit, now n = 21.
# 	Increase the second digit, now n = 22.
# 	Decrease the first digit, now n = 12.
#
# Constraints:
# 1 <= n, m < 104
# 	n and m consist of the same number of digits.
#

class Solution(object):
    def minOperations(self, n, m):
        """
        :type n: int
        :type m: int
        :rtype: int
        """
        def is_prime(num):
            if num < 2:
                return False
            for i in range(2, int(num**0.5) + 1):
                if num % i == 0:
                    return False
            return True

        from collections import deque

        queue = deque([(n, n)])  # (current number, cumulative cost)
        visited = set()
        min_cost = float('inf')

        while queue:
            current, cost = queue.popleft()

            if current == m:
                min_cost = min(min_cost, cost)
                continue

            for i in range(len(str(current))):
                digit = (current // (10 ** i)) % 10

                # Increase digit
                if digit < 9:
                    new_num = current + (10 ** i)
                    if not is_prime(new_num) and new_num not in visited:
                        visited.add(new_num)
                        queue.append((new_num, cost + new_num))

                # Decrease digit
                if digit > 0:
                    new_num = current - (10 ** i)
                    if not is_prime(new_num) and new_num not in visited:
                        visited.add(new_num)
                        queue.append((new_num, cost + new_num))

        return min_cost if min_cost != float('inf') else -1