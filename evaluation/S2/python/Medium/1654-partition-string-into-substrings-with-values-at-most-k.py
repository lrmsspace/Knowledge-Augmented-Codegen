# Source: https://leetcode.com/problems/partition-string-into-substrings-with-values-at-most-k/   |   Difficulty: Medium
#
# Problem Description:
# You are given a string s consisting of digits from 1 to 9 and an integer k.
#
# A partition of a string s is called good if:
#
#
# 	Each digit of s is part of exactly one substring.
# 	The value of each substring is less than or equal to k.
#
#
# Return the minimum number of substrings in a good partition of s. If no good partition of s exists, return -1.
#
# Note that:
#
#
# 	The value of a string is its result when interpreted as an integer. For example, the value of "123" is 123 and the value of "1" is 1.
# 	A substring is a contiguous sequence of characters within a string.
#
# Example:
# Input: s = "165462", k = 60
# Output: 4
# Explanation: We can partition the string into substrings "16", "54", "6", and "2". Each substring has a value less than or equal to k = 60.
# It can be shown that we cannot partition the string into less than 4 substrings.
#
# Constraints:
# 1 <= s.length <= 105
# 	s[i] is a digit from '1' to '9'.
# 	1 <= k <= 109
#
#
#  
# .spoilerbutton {display:block; border:dashed; padding: 0px 0px; margin:10px 0px; font-size:150%; font-weight: bold; color:#000000; background-color:cyan; outline:0; 
# }
# .spoiler {overflow:hidden;}
# .spoiler > div {-webkit-transition: all 0s ease;-moz-transition: margin 0s ease;-o-transition: all 0s ease;transition: margin 0s ease;}
# .spoilerbutton[value="Show Message"] + .spoiler > div {margin-top:-500%;}
# .spoilerbutton[value="Hide Message"] + .spoiler {padding:5px;}
#
# Helpful references (internal KB):
# - Digit DP (array, number, digit-dp)
#   • When to use: Use Digit DP to count numbers within a given range [a, b] that satisfy a property based on their digits. It's effective when the property can be checked digit by digit.
#   • Idea: Digit DP is a dynamic programming technique to count numbers within a given range [A, B] that satisfy specific properties related to their digits. It typically involves a recursive function with memoization, building numbers digit by digit, and has a complexity roughly proportional to (number of digits * state space).
#   • Invariants: The `tight` parameter accurately reflects if the current prefix matches the upper bound's prefix.; The `is_leading_zero` parameter correctly indicates if all preceding digits chosen were zero.
#   • Tips: Define the DP state carefully, including index, tight constraint, and leading zero flag.; Handle leading zeros correctly, as they can affect properties like sum or count of digits.
#   • Pitfalls: Incorrectly handling the 'tight' constraint, leading to overcounting or undercounting.; Forgetting to account for leading zeros or mismanaging their impact on the property.
# - kth-largest-element-in-an-array (heap, array, heap-select)
#   • When to use: Use this when you need to find the k-th largest (or smallest) element in an unsorted array efficiently without fully sorting it. It is particularly effective when k is much smaller than N.
#   • Idea: This algorithm uses a min-heap of size k to store the k largest elements encountered so far. It iterates through the array, comparing each element with the heap's minimum; if larger, it replaces the minimum, resulting in O(N log K) time complexity and O(K) space complexity.
#   • Invariants: The min-heap always contains at most k elements.; Every element in the min-heap is greater than or equal to any element that has been processed and discarded.
#   • Tips: Use a min-heap to find the k-th largest element, and a max-heap for the k-th smallest.; Initialize the heap with the first k elements from the input array.
#   • Pitfalls: Incorrectly using a max-heap when trying to find the k-th largest element.; Failing to handle edge cases such as k=1 or k equal to the array's length.
# - Linear Diophantine Equation (number, greedy)
#   • When to use: Use when a problem can be solved by making the locally optimal choice at each step, hoping this leads to a globally optimal solution. This strategy is often simpler and faster than dynamic programming.
#   • Idea: The greedy algorithm makes the best choice at each stage with the hope of finding a global optimum, without reconsidering previous choices. Its time complexity is typically O(N log N) or O(N).
#   • Invariants: At each step, the chosen element is the best available according to the greedy criterion.; The partial solution constructed so far remains optimal for the subproblem considered.
#   • Tips: Prove correctness by exchange argument or induction.; Sort input data if it helps identify the greedy choice.
#   • Pitfalls: Failing to prove the greedy choice property.; Making a locally optimal choice that prevents a global optimum.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def minimumPartition(self, s, k):
        """
        :type s: str
        :type k: int
        :rtype: int
        """
        count = 0
        current_num = 0

        for char in s:
            digit = int(char)
            if current_num * 10 + digit > k:
                count += 1
                current_num = digit
            else:
                current_num = current_num * 10 + digit

        if current_num > 0:
            count += 1

        return count