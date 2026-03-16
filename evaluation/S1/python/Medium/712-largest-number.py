# Source: https://leetcode.com/problems/largest-number/   |   Difficulty: Medium
#
# Problem Description:
# Given a list of non-negative integers nums, arrange them such that they form the largest number and return it.
#
# Since the result may be very large, so you need to return a string instead of an integer.
#
# Example:
# Input: nums = [10,2]
# Output: "210"
#
# Constraints:
# 1 <= nums.length <= 100
# 	0 <= nums[i] <= 109
#
# Helpful references (internal KB):
# - String Sorts (array, string, recursion)
#   • When to use: Use this algorithm to sort a collection of strings lexicographically, especially when string lengths vary or are large, and the character set is limited.
#   • Idea: This algorithm sorts an array of strings lexicographically by recursively applying a counting sort-like distribution based on characters from most significant to least significant digit. It typically achieves O(N*L + R*L) time complexity, where N is the number of strings, L is the average string length, and R is the radix size.
#   • Invariants: All strings in the current `a[lo...hi]` sub-array share a common prefix of length `d`.; After the distribution pass for character `d`, `aux` contains strings from `a[lo...hi]` stably sorted by their `d`-th character.
#   • Tips: Use an auxiliary array for stable distribution during each pass to maintain relative order.; Implement a cutoff to insertion sort for small sub-arrays to improve performance due to lower overhead.
#   • Pitfalls: Can have high overhead for small N or short strings compared to comparison sorts.; Potentially memory intensive due to the auxiliary array and recursion stack depth proportional to max string length.
# - Scheduling jobs on one machine (array, number, greedy, merge-sort)
#   • When to use: When tasks need to be processed sequentially on a single resource to optimize a cumulative metric like total completion time or weighted sum of completion times.
#   • Idea: This algorithm finds an optimal sequence for processing jobs on a single machine by applying a greedy strategy, often involving sorting based on specific criteria. It typically achieves an optimal schedule in O(N log N) time complexity.
#   • Invariants: The list of jobs is sorted according to the chosen greedy criterion.; For any prefix of the sorted jobs, the current schedule minimizes the objective function for those jobs.
#   • Tips: Identify the correct sorting key (e.g., processing time, weight/time ratio) for the objective function.; Prove optimality using an exchange argument to justify the greedy choice.
#   • Pitfalls: Applying an incorrect sorting criterion for the specific optimization objective.; Assuming a greedy approach is always optimal without a formal proof.
# - Generating all K-combinations (array, enumeration, greedy)
#   • When to use: Use this when you need to iterate through all possible subsets of a fixed size K from a larger set, especially when a specific order like lexicographical is required.
#   • Idea: This algorithm systematically generates all unique combinations of K elements from a set of N elements. It typically proceeds in lexicographical order, allowing for efficient enumeration of all C(N, K) possibilities.
#   • Invariants: The current combination C is always sorted: C[0] < C[1] < ... < C[K-1].; All elements C[i] are distinct and within the range [0, N-1] (assuming 0-indexed).
#   • Tips: Start with the smallest lexicographical combination (e.g., {1, 2, ..., K}).; To find the next combination, locate the rightmost element that can be incremented.
#   • Pitfalls: Incorrectly handling boundary conditions when incrementing elements.; Duplicating combinations if not careful with the increment logic.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def largestNumber(self, nums):
        """
        :type nums: List[int]
        :rtype: str
        """
        from functools import cmp_to_key

        # Custom comparator to decide the order based on concatenation
        def compare(x, y):
            if x + y > y + x:
                return -1  # x should come before y
            elif x + y < y + x:
                return 1   # y should come before x
            else:
                return 0   # equal

        # Convert all integers to strings for comparison
        str_nums = list(map(str, nums))

        # Sort the numbers using the custom comparator
        str_nums.sort(key=cmp_to_key(compare))

        # Join the sorted strings
        largest_num = ''.join(str_nums)

        # Handle the case where the result is all zeros
        if largest_num[0] == '0':
            return '0'
        
        return largest_num