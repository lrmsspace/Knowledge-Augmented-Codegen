# Source: https://leetcode.com/problems/maximum-good-people-based-on-statements/   |   Difficulty: Hard
#
# Problem Description:
# There are two types of persons:
#
#
# 	The good person: The person who always tells the truth.
# 	The bad person: The person who might tell the truth and might lie.
#
#
# You are given a 0-indexed 2D integer array statements of size n x n that represents the statements made by n people about each other. More specifically, statements[i][j] could be one of the following:
#
#
# 	0 which represents a statement made by person i that person j is a bad person.
# 	1 which represents a statement made by person i that person j is a good person.
# 	2 represents that no statement is made by person i about person j.
#
#
# Additionally, no person ever makes a statement about themselves. Formally, we have that statements[i][i] = 2 for all 0 <= i < n.
#
# Return the maximum number of people who can be good based on the statements made by the n people.
#
# Example:
# Input: statements = [[2,1,2],[1,2,2],[2,0,2]]
# Output: 2
# Explanation: Each person makes a single statement.
# - Person 0 states that person 1 is good.
# - Person 1 states that person 0 is good.
# - Person 2 states that person 1 is bad.
# Let's take person 2 as the key.
# - Assuming that person 2 is a good person:
#     - Based on the statement made by person 2, person 1 is a bad person.
#     - Now we know for sure that person 1 is bad and person 2 is good.
#     - Based on the statement made by person 1, and since person 1 is bad, they could be:
#         - telling the truth. There will be a contradiction in this case and this assumption is invalid.
#         - lying. In this case, person 0 is also a bad person and lied in their statement.
#     - Following that person 2 is a good person, there will be only one good person in the group.
# - Assuming that person 2 is a bad person:
#     - Based on the statement made by person 2, and since person 2 is bad, they could be:
#         - telling the truth. Following this scenario, person 0 and 1 are both bad as explained before.
#             - Following that person 2 is bad but told the truth, there will be no good persons in the group.
#         - lying. In this case person 1 is a good person.
#             - Since person 1 is a good person, person 0 is also a good person.
#             - Following that person 2 is bad and lied, there will be two good persons in the group.
# We can see that at most 2 persons are good in the best case, so we return 2.
# Note that there is more than one way to arrive at this conclusion.
#
# Constraints:
# n == statements.length == statements[i].length
# 	2 <= n <= 15
# 	statements[i][j] is either 0, 1, or 2.
# 	statements[i][i] == 2
#
# Helpful references (internal KB):
# - Generating all K-combinations (array, enumeration, greedy)
#   • When to use: Use this when you need to iterate through all possible subsets of a fixed size K from a larger set, especially when a specific order like lexicographical is required.
#   • Idea: This algorithm systematically generates all unique combinations of K elements from a set of N elements. It typically proceeds in lexicographical order, allowing for efficient enumeration of all C(N, K) possibilities.
#   • Invariants: The current combination C is always sorted: C[0] < C[1] < ... < C[K-1].; All elements C[i] are distinct and within the range [0, N-1] (assuming 0-indexed).
#   • Tips: Start with the smallest lexicographical combination (e.g., {1, 2, ..., K}).; To find the next combination, locate the rightmost element that can be incremented.
#   • Pitfalls: Incorrectly handling boundary conditions when incrementing elements.; Duplicating combinations if not careful with the increment logic.
# - The Inclusion-Exclusion Principle (array, number, counting, sieve)
#   • When to use: Use when direct counting of elements satisfying specific conditions is difficult due to overlaps, and you need to find the count of elements satisfying at least one, exactly k, or none of several properties.
#   • Idea: The Inclusion-Exclusion Principle counts the size of a union of sets by alternately adding and subtracting the sizes of intersections of increasing numbers of sets. Its complexity is often exponential in the number of properties.
#   • Invariants: At the start of processing subsets of size k, the running total correctly accounts for all intersections of size less than k.; For every element x, its contribution to the total sum is 1 if it satisfies the target condition, and 0 otherwise.
#   • Tips: Clearly define the properties (P1, P2, ..., Pn) for which elements are counted.; Systematically calculate the sizes of all relevant intersections of properties.
#   • Pitfalls: Incorrectly defining the properties or the universe of elements being counted.; Errors in calculating the sizes of specific intersections of properties.
# - 2-SAT (graph, scc)
#   • When to use: When a problem can be modeled as finding a satisfying assignment for a Boolean formula where each clause contains exactly two literals. It is used to determine if such an assignment exists and to construct one if it does.
#   • Idea: 2-SAT solves the Boolean satisfiability problem for formulas in conjunctive normal form where each clause has exactly two literals. It converts the formula into an implication graph and uses Strongly Connected Components (SCCs) to find a satisfying assignment or determine unsatisfiability in O(N+M) time.
#   • Invariants: Each clause (A OR B) is correctly represented by two implications: (NOT A => B) and (NOT B => A).; The implication graph correctly reflects all logical implications derived from the 2-CNF formula.
#   • Tips: Convert each clause (A OR B) into two implications: (NOT A => B) and (NOT B => A).; Represent each variable X and its negation NOT X as distinct nodes in the implication graph.
#   • Pitfalls: Incorrectly converting clauses to implications, missing one of the two directions.; Failing to handle the critical case where a variable and its negation are in the same SCC.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def maximumGood(self, statements):
        """
        :type statements: List[List[int]]
        :rtype: int
        """
        n = len(statements)
        max_good = 0

        # Iterate through all possible combinations of good and bad people
        for mask in range(1 << n):
            good_people = [i for i in range(n) if (mask & (1 << i)) > 0]
            is_valid = True

            # Check if the current combination is valid based on the statements
            for i in range(n):
                for j in range(n):
                    if statements[i][j] == 2:
                        continue
                    if statements[i][j] == 1 and ((mask & (1 << j)) == 0):
                        is_valid = False
                        break
                    if statements[i][j] == 0 and ((mask & (1 << j)) > 0):
                        is_valid = False
                        break
                if not is_valid:
                    break

            if is_valid:
                max_good = max(max_good, len(good_people))

        return max_good