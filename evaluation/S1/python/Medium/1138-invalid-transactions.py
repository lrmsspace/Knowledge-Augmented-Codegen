# Source: https://leetcode.com/problems/invalid-transactions/   |   Difficulty: Medium
#
# Problem Description:
# A transaction is possibly invalid if:
#
#
# 	the amount exceeds $1000, or;
# 	if it occurs within (and including) 60 minutes of another transaction with the same name in a different city.
#
#
# You are given an array of strings transaction where transactions[i] consists of comma-separated values representing the name, time (in minutes), amount, and city of the transaction.
#
# Return a list of transactions that are possibly invalid. You may return the answer in any order.
#
# Example:
# Input: transactions = ["alice,20,800,mtv","alice,50,100,beijing"]
# Output: ["alice,20,800,mtv","alice,50,100,beijing"]
# Explanation: The first transaction is invalid because the second transaction occurs within a difference of 60 minutes, have the same name and is in a different city. Similarly the second one is invalid too.
#
# Constraints:
# transactions.length <= 1000
# 	Each transactions[i] takes the form "{name},{time},{amount},{city}"
# 	Each {name} and {city} consist of lowercase English letters, and have lengths between 1 and 10.
# 	Each {time} consist of digits, and represent an integer between 0 and 1000.
# 	Each {amount} consist of digits, and represent an integer between 0 and 2000.
#
# Helpful references (internal KB):
# - String Hashing (string, array, hashing, enumeration)
#   • When to use: Use string hashing to efficiently compare substrings or patterns within a larger text, or to quickly check for duplicate strings. It's ideal for problems requiring fast equality checks on string segments.
#   • Idea: String hashing converts a string or substring into a numerical hash value, allowing for O(1) comparison of substrings after O(N) precomputation. It typically uses polynomial hashing with a prime base and modulus to minimize collisions.
#   • Invariants: The hash value for the prefix S[0...i] is correctly computed and stored, based on the chosen polynomial hashing scheme.; The base 'p' and modulus 'm' remain constant throughout the hash computation for consistent results.
#   • Tips: Choose a large prime number for the base 'p' (e.g., 31, 53) to reduce collisions.; Select a large prime number for the modulus 'm' (e.g., 10^9+7, 10^9+9) to further minimize collision probability.
#   • Pitfalls: Avoid using 2^64 as a modulus, as specific collision-generating strings exist for this choice.; A small modulus 'm' or base 'p' drastically increases the likelihood of hash collisions.
# - palindrome-partitioning (string, two-pointers, simulation)
#   • When to use: When a string needs to be decomposed into all possible sets of palindromic substrings. It's suitable for problems requiring exhaustive enumeration of such partitions.
#   • Idea: This algorithm finds all possible ways to partition a given string such that every substring in the partition is a palindrome. It typically uses a recursive exploration approach combined with a two-pointer check for palindrome validation, resulting in an exponential time complexity.
#   • Invariants: At any point, the `step` list contains a valid palindromic partition of the prefix processed so far.; The `s` parameter in the recursive function always represents the unpartitioned suffix of the original string.
#   • Tips: Implement the `isPalindrome` check efficiently using two pointers for O(length) time.; Use a recursive helper function to explore all possible partition points.
#   • Pitfalls: Incorrectly handling substring boundaries, leading to off-by-one errors or incorrect partitions.; Forgetting to backtrack (remove the last added substring) after a recursive call returns.
# - Non-negative Integers without Consecutive Ones (number, enumeration, simulation)
#   • When to use: Use when counting numbers up to a given limit that satisfy a specific bit pattern constraint, particularly when the limit is small enough for direct iteration and checking.
#   • Idea: This approach iterates through every non-negative integer from 0 up to the given limit num. For each integer, it simulates checking its binary representation to determine if it contains any two consecutive '1's.
#   • Invariants: count stores the number of integers k (where 0 <= k < i) that do not have consecutive ones.; All integers j such that 0 <= j < i have been processed.
#   • Tips: Use bitwise operations like (i & (i >> 1)) to efficiently detect consecutive ones.; Remember to include 0 in the count as it satisfies the condition (no consecutive ones).
#   • Pitfalls: Performance degradation for large num due to linear scan and per-number bit check.; Incorrectly handling the upper bound of the iteration (e.g., i < num instead of i <= num).
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def invalidTransactions(self, transactions):
        """
        :type transactions: List[str]
        :rtype: List[str]
        """
        from collections import defaultdict

        # Parse transactions and group by name
        transactions_by_name = defaultdict(list)
        for transaction in transactions:
            name, time, amount, city = transaction.split(',')
            transactions_by_name[name].append((int(time), int(amount), city, transaction))
        invalid = set()
        # Check for invalid transactions
        for name, trans_list in transactions_by_name.items():
            trans_list.sort()  # Sort by time
            for i in range(len(trans_list)):
                time_i, amount_i, city_i, original_i = trans_list[i]
                # Check if amount exceeds 1000
                if amount_i > 1000:
                    invalid.add(original_i)
                # Check for same-city transactions within 60 minutes
                for j in range(i + 1, len(trans_list)):
                    time_j, amount_j, city_j, original_j = trans_list[j]
                    if city_i == city_j and time_j - time_i <= 60:
                        invalid.add(original_i)
                        invalid.add(original_j)
                    if time_j - time_i > 60:
                        break
        return list(invalid)    