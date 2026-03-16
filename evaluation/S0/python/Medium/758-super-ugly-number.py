# Source: https://leetcode.com/problems/super-ugly-number/   |   Difficulty: Medium
#
# Problem Description:
# A super ugly number is a positive integer whose prime factors are in the array primes.
#
# Given an integer n and an array of integers primes, return the nth super ugly number.
#
# The nth super ugly number is guaranteed to fit in a 32-bit signed integer.
#
# Example:
# Input: n = 12, primes = [2,7,13,19]
# Output: 32
# Explanation: [1,2,4,7,8,13,14,16,19,26,28,32] is the sequence of the first 12 super ugly numbers given primes = [2,7,13,19].
#
# Constraints:
# 1 <= n <= 105
# 	1 <= primes.length <= 100
# 	2 <= primes[i] <= 1000
# 	primes[i] is guaranteed to be a prime number.
# 	All the values of primes are unique and sorted in ascending order.
#

class Solution(object):
    def nthSuperUglyNumber(self, n, primes):
        """
        :type n: int
        :type primes: List[int]
        :rtype: int
        """
        import heapq

        ugly_numbers = [1]
        indices = [0] * len(primes)
        heap = [(primes[i], i) for i in range(len(primes))]
        heapq.heapify(heap)

        while len(ugly_numbers) < n:
            next_ugly, prime_index = heapq.heappop(heap)
            if next_ugly != ugly_numbers[-1]:
                ugly_numbers.append(next_ugly)

            indices[prime_index] += 1
            new_ugly = ugly_numbers[indices[prime_index]] * primes[prime_index]
            heapq.heappush(heap, (new_ugly, prime_index))

        return ugly_numbers[-1]