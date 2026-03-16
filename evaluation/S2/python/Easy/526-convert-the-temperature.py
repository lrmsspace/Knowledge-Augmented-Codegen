# Source: https://leetcode.com/problems/convert-the-temperature/   |   Difficulty: Easy
#
# Problem Description:
# You are given a non-negative floating point number rounded to two decimal places celsius, that denotes the temperature in Celsius.
#
# You should convert Celsius into Kelvin and Fahrenheit and return it as an array ans = [kelvin, fahrenheit].
#
# Return the array ans. Answers within 10-5 of the actual answer will be accepted.
#
# Note that:
#
#
# 	Kelvin = Celsius + 273.15
# 	Fahrenheit = Celsius * 1.80 + 32.00
#
# Example:
# Input: celsius = 36.50
# Output: [309.65000,97.70000]
# Explanation: Temperature at 36.50 Celsius converted in Kelvin is 309.65 and converted in Fahrenheit is 97.70.
#
# Constraints:
# 0 <= celsius <= 1000
#
# Helpful references (internal KB):
# - bucket-sort (array, linked-list, bucket-sort)
#   • When to use: Use when sorting elements, especially floating-point numbers, that are uniformly distributed over a range. It offers linear time complexity on average for such distributions.
#   • Idea: Bucket sort distributes elements into a fixed number of buckets, sorts each bucket individually using another sorting algorithm, and then concatenates the sorted buckets. It achieves an average time complexity of O(N+K), where N is the number of elements and K is the number of buckets.
#   • Invariants: Before sorting any bucket, all elements are correctly placed in their respective buckets based on their range.; After sorting each individual bucket, all elements within that bucket are in sorted order.
#   • Tips: Use a stable sorting algorithm like Insertion Sort for individual buckets to maintain overall stability.; The number of buckets should be chosen carefully, often proportional to N, to optimize performance.
#   • Pitfalls: Performance degrades significantly with non-uniform data distributions, potentially becoming O(N^2).; Requires extra space for the buckets, which can be substantial for many buckets or large elements.
# - Fibonacci Numbers (array, dp-1d)
#   • When to use: Use this when calculating the n-th Fibonacci number or similar sequences where each term depends on a fixed number of preceding terms. It efficiently avoids redundant computations for moderate 'n' values.
#   • Idea: This algorithm calculates Fibonacci numbers iteratively by storing previously computed values in an array, building up to the desired n-th term. This approach achieves O(N) time complexity and O(N) space complexity.
#   • Invariants: dp[i] correctly stores the i-th Fibonacci number.; For i >= 2, dp[i] is computed as the sum of dp[i-1] and dp[i-2].
#   • Tips: Initialize base cases (F0, F1) correctly to start the sequence.; Use an array or two variables to store only the necessary previous terms.
#   • Pitfalls: Incorrectly initializing the base cases can lead to wrong results.; A naive recursive solution without memoization will lead to exponential time complexity.
# - Search the subarray with the maximum/minimum sum (array, prefix-sum, max-window)
#   • When to use: When needing to find the maximum or minimum sum of any contiguous subarray within a given array efficiently. It is particularly useful for problems requiring an O(N) solution.
#   • Idea: This algorithm finds the maximum (or minimum) sum of a contiguous subarray by iterating through the array, maintaining a running prefix sum, and tracking the minimum (or maximum) prefix sum encountered so far. It achieves an optimal O(N) time complexity with O(1) auxiliary space.
#   • Invariants: max_global_sum stores the maximum subarray sum found among all subarrays ending at or before the current element.; min_prefix_sum_value correctly tracks the minimum prefix sum encountered up to the previous element's prefix sum.
#   • Tips: Use a running sum variable instead of explicitly storing the entire prefix sum array.; Keep track of the minimum prefix sum encountered up to the current point.
#   • Pitfalls: Incorrectly initializing the minimum prefix sum (e.g., to INT_MAX instead of 0 or s[0]).; Off-by-one errors when calculating subarray sums using prefix sums (s[r] - s[l-1]).
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def convertTemperature(self, celsius):
        """
        :type celsius: float
        :rtype: List[float]
        """
        kelvin = celsius + 273.15
        fahrenheit = celsius * 1.80 + 32.00
        return [kelvin, fahrenheit]