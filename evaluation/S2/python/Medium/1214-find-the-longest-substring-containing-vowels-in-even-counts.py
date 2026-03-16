# Source: https://leetcode.com/problems/find-the-longest-substring-containing-vowels-in-even-counts/   |   Difficulty: Medium
#
# Problem Description:
# Given the string s, return the size of the longest substring containing each vowel an even number of times. That is, 'a', 'e', 'i', 'o', and 'u' must appear an even number of times.
#
# Example:
# Input: s = "eleetminicoworoep"
# Output: 13
# Explanation: The longest substring is "leetminicowor" which contains two each of the vowels: e, i and o and zero of the vowels: a and u.
#
# Constraints:
# 1 <= s.length <= 5 x 10^5
# 	s contains only lowercase English letters.
#
# Helpful references (internal KB):
# - Manacher's Algorithm - Finding all sub-p (string, array, simulation, enumeration)
#   • When to use: When you need to find all palindromic substrings or the longest palindromic substring within a given string efficiently. It is particularly useful for achieving linear time complexity for this task.
#   • Idea: Manacher's algorithm finds all maximal palindromic substrings centered at each position in a string by leveraging symmetry and previously computed results. It achieves an optimal O(N) time complexity.
#   • Invariants: d_odd[i] stores the radius of the longest odd-length palindrome centered at i.; The (l, r) interval always defines the rightmost palindrome found so far.
#   • Tips: Preprocess the string with delimiters to unify odd and even length palindromes.; Maintain the current rightmost boundary `r` of the largest palindrome found.
#   • Pitfalls: Forgetting to update the `(l, r)` boundaries after processing each center.; Incorrectly calculating mirror positions or handling boundary cases for `i > r`.
# - The Inclusion-Exclusion Principle (string, counting)
#   • When to use: Use when you need to determine the frequency of characters or substrings within a string. It is essential for tasks like anagram detection or checking character distribution.
#   • Idea: This technique involves iterating through a string to tally the occurrences of its constituent elements, typically characters or words. It generally operates in O(N) time complexity, where N is the string's length.
#   • Invariants: The count for each character reflects its total occurrences processed so far.; All characters encountered up to the current position have been tallied.
#   • Tips: Use a hash map (dictionary) for arbitrary character sets.; Use an array for fixed-size character sets (e.g., ASCII, lowercase English).
#   • Pitfalls: Forgetting to handle case sensitivity or ignore non-alphanumeric characters.; Incorrectly handling Unicode characters with fixed-size arrays.
# - Finding the Eulerian path in O(M) (graph, enumeration, bfs)
#   • When to use: Use when the problem requires visiting every edge in a graph exactly once, either starting and ending at the same vertex (cycle) or at two different vertices (path).
#   • Idea: An Eulerian path is a trail in a graph which visits every edge exactly once. An Eulerian cycle is an Eulerian path that starts and ends on the same vertex.
#   • Invariants: Every edge in the graph is considered exactly once for inclusion in the path.; The current path segment always forms a valid trail in the graph.
#   • Tips: Check vertex degrees to determine path/cycle existence before attempting to find it.; For an Eulerian path, start traversal from one of the two odd-degree vertices.
#   • Pitfalls: Incorrectly handling multi-edges or self-loops can lead to errors in degree calculation or traversal.; Failing to check graph connectivity can result in incomplete paths or infinite loops.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def findTheLongestSubstring(self, s):
        """
        :type s: str
        :rtype: int
        """
        # 1. 状态编码：使用一个整数来表示每个元音字母的出现次数（偶数或奇数）
        #    - a, e, i, o, u 分别对应二进制位 0-4
        #    - 0 表示偶数，1 表示奇数
        # 2. 前缀状态：遍历字符串，记录每个位置的前缀状态
        # 3. 哈希表：使用哈希表记录每个状态第一次出现的位置
        # 4. 计算最长长度：当遇到相同状态时，计算当前索引与第一次出现该状态的索引之间的距离

        state_to_index = {0: -1}  # 初始状态，所有元音字母出现次数为偶数
        current_state = 0
        max_length = 0

        for index, char in enumerate(s):
            if char == 'a':
                current_state ^= (1 << 0)  # 切换 a 的状态
            elif char == 'e':
                current_state ^= (1 << 1)  # 切换 e 的状态
            elif char == 'i':
                current_state ^= (1 << 2)  # 切换 i 的状态
            elif char == 'o':
                current_state ^= (1 << 3)  # 切换 o 的状态
            elif char == 'u':
                current_state ^= (1 << 4)  # 切换 u 的状态

            if current_state in state_to_index:
                max_length = max(max_length, index - state_to_index[current_state])
            else:
                state_to_index[current_state] = index

        return max_length