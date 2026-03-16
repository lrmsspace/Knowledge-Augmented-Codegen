# Source: https://leetcode.com/problems/maximum-binary-string-after-change/   |   Difficulty: Medium
#
# Problem Description:
# You are given a binary string binary consisting of only 0's or 1's. You can apply each of the following operations any number of times:
#
#
#  Operation 1: If the number contains the substring "00", you can replace it with "10".
#
#  
#   For example, "00010" -> "10010"
#  
#  
#  Operation 2: If the number contains the substring "10", you can replace it with "01".
#  
#   For example, "00010" -> "00001"
#  
#  
#
#
# Return the maximum binary string you can obtain after any number of operations. Binary string x is greater than binary string y if x's decimal representation is greater than y's decimal representation.
#
# Example:
# Input: binary = "000110"
# Output: "111011"
# Explanation: A valid transformation sequence can be:
# "000110" -> "000101" 
# "000101" -> "100101" 
# "100101" -> "110101" 
# "110101" -> "110011" 
# "110011" -> "111011"
#
# Constraints:
# 1 <= binary.length <= 105
#  binary consist of '0' and '1'.
#
# Helpful references (internal KB):
# - Scheduling jobs on one machine (array, number, greedy, merge-sort)
#   • When to use: Use when tasks with associated processing times and costs need to be sequenced on a single machine to minimize a total objective function, typically involving weighted completion times or penalties. The optimal sequence is found by a greedy sort.
#   • Idea: This method finds an optimal schedule for jobs on a single machine by sorting them according to a greedy criterion derived from an exchange argument. It achieves an optimal solution with O(N log N) time complexity, dominated by the sorting step.
#   • Invariants: The relative order of any two jobs i and j in the sorted sequence is consistent with the greedy comparison rule.; Any prefix of the sorted schedule represents an optimal ordering for the jobs within that prefix.
#   • Tips: Clearly define the objective function to be minimized.; Formulate the greedy sorting rule using an exchange argument for any two adjacent jobs.
#   • Pitfalls: Incorrectly deriving the greedy comparison criterion.; Applying this method to problems with multiple machines or complex precedence constraints without adaptation.
# - Non-negative Integers without Consecutive Ones (number, recursion, backtracking)
#   • When to use: Use when counting numbers within a range that satisfy a specific digit-based or bit-based pattern constraint, especially when the constraint involves adjacent digits or bits.
#   • Idea: This algorithm recursively generates binary numbers bit by bit, ensuring no two consecutive ones are formed. It prunes branches that exceed a given upper limit or violate the consecutive one constraint, effectively counting valid numbers up to N in O(log N) time.
#   • Invariants: The `sum` generated so far never exceeds the target `num`.; The `prev` boolean accurately reflects whether the last bit added was a '1'.
#   • Tips: Generate numbers bit by bit, typically from LSB or MSB, to build up valid sequences.; Maintain state about the previously placed bit to enforce the 'no consecutive ones' rule.
#   • Pitfalls: Failing to correctly handle the base cases for the recursive function.; Incorrectly managing the 'previous bit' state, leading to invalid sequences.
# - String Sorts (array, string, recursion)
#   • When to use: Use this algorithm to sort a collection of strings lexicographically, especially when string lengths vary or are large, and the character set is limited.
#   • Idea: This algorithm sorts an array of strings lexicographically by recursively applying a counting sort-like distribution based on characters from most significant to least significant digit. It typically achieves O(N*L + R*L) time complexity, where N is the number of strings, L is the average string length, and R is the radix size.
#   • Invariants: All strings in the current `a[lo...hi]` sub-array share a common prefix of length `d`.; After the distribution pass for character `d`, `aux` contains strings from `a[lo...hi]` stably sorted by their `d`-th character.
#   • Tips: Use an auxiliary array for stable distribution during each pass to maintain relative order.; Implement a cutoff to insertion sort for small sub-arrays to improve performance due to lower overhead.
#   • Pitfalls: Can have high overhead for small N or short strings compared to comparison sorts.; Potentially memory intensive due to the auxiliary array and recursion stack depth proportional to max string length.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def maximumBinaryString(self, binary):
        """
        :type binary: str
        :rtype: str
        """
        n = len(binary)
        zero_count = binary.count('0')
        
        if zero_count == 0:
            return binary
        
        first_zero_index = binary.index('0')
        result = ['1'] * n
        
        # Place a '0' at the position determined by the number of zeros
        result[first_zero_index + zero_count - 1] = '0'
        
        return ''.join(result)