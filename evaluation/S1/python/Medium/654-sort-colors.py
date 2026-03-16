# Source: https://leetcode.com/problems/sort-colors/   |   Difficulty: Medium
#
# Problem Description:
# Given an array nums with n objects colored red, white, or blue, sort them in-place so that objects of the same color are adjacent, with the colors in the order red, white, and blue.
#
# We will use the integers 0, 1, and 2 to represent the color red, white, and blue, respectively.
#
# You must solve this problem without using the library's sort function.
#
# Example:
# Input: nums = [2,0,2,1,1,0]
# Output: [0,0,1,1,2,2]
#
# Constraints:
# n == nums.length
# 	1 <= n <= 300
# 	nums[i] is either 0, 1, or 2.
#
#
#  
# Follow up: Could you come up with a one-pass algorithm using only constant extra space?
#
# Helpful references (internal KB):
# - Quicksort (array, two-pointers, randomized)
#   • When to use: Use Quicksort for efficient in-place sorting of arrays, especially when average-case performance and cache efficiency are prioritized. It is suitable for large datasets where memory usage is a concern.
#   • Idea: Quicksort is a divide-and-conquer sorting algorithm that partitions an array around a pivot element, then recursively sorts the two resulting subarrays. Its average time complexity is O(N log N), but can degrade to O(N^2) in the worst case.
#   • Invariants: All elements to the left of the `lt` pointer are less than the pivot value.; All elements to the right of the `gt` pointer are greater than the pivot value.
#   • Tips: Randomly shuffle the input or choose a random pivot to ensure average-case performance.; Employ 3-way partitioning to efficiently handle duplicate keys and avoid quadratic worst-case scenarios.
#   • Pitfalls: Failing to handle duplicate keys can lead to quadratic time complexity.; Incorrect pointer crossing logic can cause infinite loops or array out-of-bounds errors.
# - String Sorts (array, string, number, radix-sort, counting-sort)
#   • When to use: Use when sorting a large collection of fixed-length strings or integers, especially when the key range (alphabet size) is small. It is efficient for data with uniform key lengths.
#   • Idea: LSD Radix Sort sorts elements by processing digits or characters from the least significant to the most significant, using a stable counting sort for each position. It achieves a time complexity of O(W * (N + R)), where W is the key length, N is the number of items, and R is the radix.
#   • Invariants: After each pass 'd' (from 'w-1' down to '0'), the array 'a' is stably sorted based on characters from position 'd' to 'w-1'.; The 'count' array accurately reflects the frequency of each character at the current digit 'd' before cumulation.
#   • Tips: Utilize counting sort as the stable inner sorting algorithm for each digit pass.; Process characters or digits from right to left (least significant to most significant).
#   • Pitfalls: Inefficient for variable-length strings without proper padding or specialized handling.; Can be slower than comparison sorts for small input sizes or very large radix (R).
# - Elementary Sorts (array, enumeration)
#   • When to use: Selection sort is simple but inefficient. It's suitable for very small datasets or educational purposes where simplicity of implementation is prioritized over performance.
#   • Idea: Selection sort repeatedly finds the minimum element from the unsorted portion of the array and places it at the beginning of the sorted portion. It has a time complexity of O(N^2) and a space complexity of O(1).
#   • Invariants: The elements in the prefix of the array are sorted.; All elements in the sorted prefix are less than or equal to all elements in the unsorted suffix.
#   • Tips: Easy to understand and implement.; Performs a minimal number of swaps (exactly N-1 swaps).
#   • Pitfalls: Inefficient for large datasets due to O(N^2) time complexity.; Performance is not affected by the initial order of elements.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def sortColors(self, nums):
        """
        :type nums: List[int]
        :rtype: None Do not return anything, modify nums in-place instead.
        """
        lt, i, gt = 0, 0, len(nums) - 1
        while i <= gt:
            if nums[i] < 1:
                nums[lt], nums[i] = nums[i], nums[lt]
                lt += 1
                i += 1
            elif nums[i] > 1:
                nums[i], nums[gt] = nums[gt], nums[i]
                gt -= 1
            else:
                i += 1