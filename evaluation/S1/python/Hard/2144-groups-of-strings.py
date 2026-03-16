# Source: https://leetcode.com/problems/groups-of-strings/   |   Difficulty: Hard
#
# Problem Description:
# You are given a 0-indexed array of strings words. Each string consists of lowercase English letters only. No letter occurs more than once in any string of words.
#
# Two strings s1 and s2 are said to be connected if the set of letters of s2 can be obtained from the set of letters of s1 by any one of the following operations:
#
#
# 	Adding exactly one letter to the set of the letters of s1.
# 	Deleting exactly one letter from the set of the letters of s1.
# 	Replacing exactly one letter from the set of the letters of s1 with any letter, including itself.
#
#
# The array words can be divided into one or more non-intersecting groups. A string belongs to a group if any one of the following is true:
#
#
# 	It is connected to at least one other string of the group.
# 	It is the only string present in the group.
#
#
# Note that the strings in words should be grouped in such a manner that a string belonging to a group cannot be connected to a string present in any other group. It can be proved that such an arrangement is always unique.
#
# Return an array ans of size 2 where:
#
#
# 	ans[0] is the maximum number of groups words can be divided into, and
# 	ans[1] is the size of the largest group.
#
# Example:
# Input: words = ["a","b","ab","cde"]
# Output: [2,3]
# Explanation:
# - words[0] can be used to obtain words[1] (by replacing 'a' with 'b'), and words[2] (by adding 'b'). So words[0] is connected to words[1] and words[2].
# - words[1] can be used to obtain words[0] (by replacing 'b' with 'a'), and words[2] (by adding 'a'). So words[1] is connected to words[0] and words[2].
# - words[2] can be used to obtain words[0] (by deleting 'b'), and words[1] (by deleting 'a'). So words[2] is connected to words[0] and words[1].
# - words[3] is not connected to any string in words.
# Thus, words can be divided into 2 groups ["a","b","ab"] and ["cde"]. The size of the largest group is 3.
#
# Constraints:
# 1 <= words.length <= 2 * 104
# 	1 <= words[i].length <= 26
# 	words[i] consists of lowercase English letters only.
# 	No letter occurs more than once in words[i].
#
# Helpful references (internal KB):
# - Submask Enumeration
#  (number, bitset, enumeration)
#   • When to use: When you need to iterate through all possible submasks of a given bitmask efficiently, typically for problems involving subsets or combinations represented by bits.
#   • Idea: This algorithm efficiently iterates through all submasks of a given bitmask in descending order using a clever bitwise trick. It processes each submask in O(1) time, leading to an overall complexity of O(2^k) where k is the number of set bits in the original mask.
#   • Invariants: Each `s` generated is a valid submask of the original mask `m`.; The value of `s` strictly decreases in each iteration until it reaches 0 (or the loop terminates).
#   • Tips: Always consider processing the submask 0 separately if it's a valid case for your problem.; The iteration naturally generates submasks in strictly descending numerical order.
#   • Pitfalls: Forgetting that the standard loop structure `for (int s = m; s > 0; s = (s - 1) & m)` omits submask 0.; Incorrectly assuming the iteration order is ascending; it is always descending.
# - Disjoint Set Union (ds, tree, array, union-find)
#   • When to use: Use when you need to maintain a collection of disjoint sets and efficiently perform union operations to merge sets or find the representative of an element's set.
#   • Idea: Disjoint Set Union (DSU) is a data structure that stores a collection of disjoint sets and supports two primary operations: finding the representative of an element's set and merging two sets. With path compression and union by rank/size, these operations achieve nearly constant amortized time complexity, O(alpha(N)).
#   • Invariants: Each element `v` is either a root (parent[v] == v) or has a parent pointer to another element in its set.; The `find_set` operation, after path compression, ensures that all nodes on the path from `v` to its root directly point to the root.
#   • Tips: Implement path compression in `find_set` for optimal performance.; Use union by rank or union by size to keep trees flat and balanced.
#   • Pitfalls: Forgetting path compression or union by rank/size leads to O(N) worst-case operations.; Incorrectly merging sets by only updating one root without considering the other's rank/size.
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
    def groupStrings(self, words):
        """
        :type words: List[str]
        :rtype: List[int]
        """
        # Step 1: Convert each word to a bitmask representation
        def word_to_mask(word):
            mask = 0
            for char in word:
                mask |= (1 << (ord(char) - ord('a')))
            return mask

        masks = [word_to_mask(word) for word in words]

        # Step 2: Use a dictionary to count the frequency of each unique mask
        from collections import defaultdict
        freq = defaultdict(int)
        for mask in masks:
            freq[mask] += 1

        # Step 3: Use a Disjoint Set Union (DSU) to group connected masks
        parent = {}
        size = {}

        def find(x):
            if parent[x] != x:
                parent[x] = find(parent[x])
            return parent[x]

        def union(x, y):
            rootX = find(x)
            rootY = find(y)
            if rootX != rootY:
                if size[rootX] < size[rootY]:
                    rootX, rootY = rootY, rootX
                parent[rootY] = rootX
                size[rootX] += size[rootY]

        # Initialize DSU
        for mask in freq:
            parent[mask] = mask
            size[mask] = freq[mask]

        # Step 4: Connect masks based on the defined operations
        for mask in freq:
            # Check for adding one letter (26 possibilities)
            for i in range(26):
                new_mask = mask | (1 << i)
                if new_mask in freq:
                    union(mask, new_mask)

            # Check for deleting one letter (only if there's at least one letter)
            if mask != 0:
                for i in range(26):
                    if mask & (1 << i):
                        new_mask = mask & ~(1 << i)
                        if new_mask in freq:
                            union(mask, new_mask)

            # Check for replacing one letter (26 possibilities)
            for i in range(26):
                if mask & (1 << i):
                    for j in range(26):
                        if j != i:
                            new_mask = (mask & ~(1 << i)) | (1 << j)
                            if new_mask in freq:
                                union(mask, new_mask)

        # Step 5: Count the number of groups and the size of the largest group
        group_count = 0
        largest_group_size = 0
        group_sizes = defaultdict(int)
        for mask in freq:
            root = find(mask)
            group_sizes[root] += freq[mask]
        for size in group_sizes.values():
            group_count += 1
            largest_group_size = max(largest_group_size, size)
        return [group_count, largest_group_size]    