# Source: https://leetcode.com/problems/most-beautiful-item-for-each-query/   |   Difficulty: Medium
#
# Problem Description:
# You are given a 2D integer array items where items[i] = [pricei, beautyi] denotes the price and beauty of an item respectively.
#
# You are also given a 0-indexed integer array queries. For each queries[j], you want to determine the maximum beauty of an item whose price is less than or equal to queries[j]. If no such item exists, then the answer to this query is 0.
#
# Return an array answer of the same length as queries where answer[j] is the answer to the jth query.
#
# Example:
# Input: items = [[1,2],[3,2],[2,4],[5,6],[3,5]], queries = [1,2,3,4,5,6]
# Output: [2,4,5,5,6,6]
# Explanation:
# - For queries[0]=1, [1,2] is the only item which has price <= 1. Hence, the answer for this query is 2.
# - For queries[1]=2, the items which can be considered are [1,2] and [2,4]. 
#   The maximum beauty among them is 4.
# - For queries[2]=3 and queries[3]=4, the items which can be considered are [1,2], [3,2], [2,4], and [3,5].
#   The maximum beauty among them is 5.
# - For queries[4]=5 and queries[5]=6, all items can be considered.
#   Hence, the answer for them is the maximum beauty of all items, i.e., 6.
#
# Constraints:
# 1 <= items.length, queries.length <= 105
# 	items[i].length == 2
# 	1 <= pricei, beautyi, queries[j] <= 109
#
# Helpful references (internal KB):
# - Mergesort (array, merge-sort, recursion)
#   • When to use: Use when a stable sort with guaranteed O(N log N) time complexity is required, especially for large datasets or external sorting where data might not fit in memory.
#   • Idea: Mergesort is a divide-and-conquer sorting algorithm that recursively divides an array into halves, sorts them, and then merges the sorted halves. It has a time complexity of O(N log N) and requires O(N) auxiliary space.
#   • Invariants: The elements `index[lo...k-1]` are sorted and contain the smallest `k-lo` elements from the original `aux[lo...mid]` and `aux[mid+1...hi]` segments.; Pointer `i` always indicates the next element to consider from the left sorted sub-array (`aux[lo...mid]`).
#   • Tips: Implement the merge step carefully to ensure stability.; Consider an iterative bottom-up approach to avoid recursion overhead.
#   • Pitfalls: High auxiliary space complexity (O(N)) can be a concern for memory-constrained systems.; Recursive calls can lead to stack overflow for very large inputs without tail call optimization.
# - Minkowski sum of convex polygons (geometry, array, two-pointers, sweep-line)
#   • When to use: Use this algorithm to compute the Minkowski sum of two convex polygons efficiently. It is ideal for applications requiring the union of shapes or collision detection between convex objects.
#   • Idea: This algorithm computes the Minkowski sum of two convex polygons by merging their edge vectors, sorted by polar angle, into a new sequence of edges. The resulting sum polygon is also convex and can be constructed in O(|P| + |Q|) time.
#   • Invariants: The current vertex of the resulting sum polygon is the sum of the current vertices from P and Q.; All edges processed so far from both input polygons have been added to the output in polar angle order.
#   • Tips: Pre-sort polygon vertices to start from the lowest Y-coordinate to ensure consistent orientation.; Orient both input polygons counter-clockwise for correct edge vector generation.
#   • Pitfalls: Incorrectly handling polygon orientation (e.g., mixing clockwise and counter-clockwise).; Precision issues when using floating-point numbers for angle comparisons or vector additions.
# - Range Minimum Query (array, ds, union-find)
#   • When to use: Use when range minimum queries are needed on an array where elements can be dynamically removed or merged, and Union-Find is employed to manage the active state or connectivity of indices.
#   • Idea: Union-Find can be adapted to assist in range minimum queries, particularly when elements are dynamically removed or merged. It helps maintain connectivity of active elements or segments, allowing efficient traversal to find the minimum among available items, often with near-constant amortized time per Union-Find operation.
#   • Invariants: The `find` operation correctly returns the canonical representative for any element `i`.; Each set in the Union-Find structure maintains a property (e.g., minimum value, next available index) relevant to its merged elements.
#   • Tips: Utilize path compression and union by rank/size for optimal Union-Find performance.; Store relevant properties (e.g., minimum value, next available index) within the representative of each set.
#   • Pitfalls: Union-Find alone does not directly provide range minimums; it typically manages connectivity or availability.; Naive iteration through active elements found by Union-Find can be too slow for large ranges.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def maximumBeauty(self, items, queries):
        """
        :type items: List[List[int]]
        :type queries: List[int]
        :rtype: List[int]
        """
        # Sort items by price
        items.sort()
        
        # Preprocess to create a list of maximum beauties up to each price point
        max_beauty = []
        current_max = 0
        for price, beauty in items:
            current_max = max(current_max, beauty)
            max_beauty.append((price, current_max))
        
        # Function to perform binary search
        def binary_search(query):
            left, right = 0, len(max_beauty) - 1
            ans = 0
            while left <= right:
                mid = (left + right) // 2
                if max_beauty[mid][0] <= query:
                    ans = max_beauty[mid][1]
                    left = mid + 1
                else:
                    right = mid - 1
            return ans
        
        # Process each query using binary search
        result = []
        for query in queries:
            result.append(binary_search(query))
        
        return result