# Source: https://leetcode.com/problems/maximum-ice-cream-bars/   |   Difficulty: Medium
#
# Problem Description:
# It is a sweltering summer day, and a boy wants to buy some ice cream bars.
#
# At the store, there are n ice cream bars. You are given an array costs of length n, where costs[i] is the price of the ith ice cream bar in coins. The boy initially has coins coins to spend, and he wants to buy as many ice cream bars as possible. 
#
# Note: The boy can buy the ice cream bars in any order.
#
# Return the maximum number of ice cream bars the boy can buy with coins coins.
#
# You must solve the problem by counting sort.
#
# Example:
# Input: costs = [1,3,2,4,1], coins = 7
# Output: 4
# Explanation: The boy can buy ice cream bars at indices 0,1,2,4 for a total price of 1 + 3 + 2 + 1 = 7.
#
# Constraints:
# costs.length == n
# 	1 <= n <= 105
# 	1 <= costs[i] <= 105
# 	1 <= coins <= 108
#
# Helpful references (internal KB):
# - bucket-sort (array, bucket-sort)
#   • When to use: When the input elements are uniformly distributed across a specific range, allowing for efficient partitioning and sorting.
#   • Idea: Bucket sort distributes elements into a fixed number of buckets, sorts each bucket, then concatenates them. It achieves O(N+K) average time complexity, where N is elements and K is buckets, assuming uniform distribution.
#   • Invariants: All elements from the input are initially present in the unsorted collection.; After distribution, each element resides in exactly one bucket, corresponding to its value range.
#   • Tips: Choose the number of buckets carefully based on data range and distribution.; Use an efficient sorting algorithm for individual buckets (e.g., insertion sort for small buckets).
#   • Pitfalls: Poor performance with non-uniform data distribution, leading to elements clustering in few buckets.; Requires knowing the range of input values beforehand to define bucket boundaries.
# - bucket-sort (array, bucket-sort)
#   • When to use: Use when sorting elements with a known, uniform distribution over a specific range. It is efficient for numbers that are uniformly distributed across a range, often achieving linear time complexity.
#   • Idea: Bucket sort distributes elements into a fixed number of buckets, sorts each bucket individually, and then concatenates them. It can achieve O(N+K) average time complexity for uniformly distributed data.
#   • Invariants: After distributing elements, each element `x` is in bucket `floor(N * x)`.; After sorting buckets, every bucket `buckets[i]` contains its elements in sorted order.
#   • Tips: Choose the number of buckets appropriately based on data distribution and range.; Normalize input data to a [0, 1) range for simpler bucket indexing.
#   • Pitfalls: Poor performance with non-uniform data distribution, potentially degrading to O(N^2).; Requires extra space for the buckets, proportional to N+K.
# - String Sorts (array, string, number, radix-sort, counting-sort)
#   • When to use: Use when sorting a large collection of fixed-length strings or integers, especially when the key range (alphabet size) is small. It is efficient for data with uniform key lengths.
#   • Idea: LSD Radix Sort sorts elements by processing digits or characters from the least significant to the most significant, using a stable counting sort for each position. It achieves a time complexity of O(W * (N + R)), where W is the key length, N is the number of items, and R is the radix.
#   • Invariants: After each pass 'd' (from 'w-1' down to '0'), the array 'a' is stably sorted based on characters from position 'd' to 'w-1'.; The 'count' array accurately reflects the frequency of each character at the current digit 'd' before cumulation.
#   • Tips: Utilize counting sort as the stable inner sorting algorithm for each digit pass.; Process characters or digits from right to left (least significant to most significant).
#   • Pitfalls: Inefficient for variable-length strings without proper padding or specialized handling.; Can be slower than comparison sorts for small input sizes or very large radix (R).
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def maxIceCream(self, costs, coins):
        """
        :type costs: List[int]
        :type coins: int
        :rtype: int
        """
        # Step 1: Find the maximum cost to determine the size of the counting array
        max_cost = max(costs)
        
        # Step 2: Create a counting array to count the frequency of each cost
        count = [0] * (max_cost + 1)
        for cost in costs:
            count[cost] += 1
        
        # Step 3: Calculate how many ice cream bars can be bought with the given coins
        total_bars = 0
        for cost in range(1, max_cost + 1):
            if count[cost] > 0:
                # Calculate how many bars of this cost can be bought
                bars_can_buy = min(count[cost], coins // cost)
                total_bars += bars_can_buy
                coins -= bars_can_buy * cost
            
            # If we have no more coins left, break out of the loop
            if coins <= 0:
                break
        
        return total_bars