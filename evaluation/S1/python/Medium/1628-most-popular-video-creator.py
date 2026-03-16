# Source: https://leetcode.com/problems/most-popular-video-creator/   |   Difficulty: Medium
#
# Problem Description:
# You are given two string arrays creators and ids, and an integer array views, all of length n. The ith video on a platform was created by creators[i], has an id of ids[i], and has views[i] views.
#
# The popularity of a creator is the sum of the number of views on all of the creator's videos. Find the creator with the highest popularity and the id of their most viewed video.
#
#
# 	If multiple creators have the highest popularity, find all of them.
# 	If multiple videos have the highest view count for a creator, find the lexicographically smallest id.
#
#
# Note: It is possible for different videos to have the same id, meaning that ids do not uniquely identify a video. For example, two videos with the same ID are considered as distinct videos with their own viewcount.
#
# Return a 2D array of strings answer where answer[i] = [creatorsi, idi] means that creatorsi has the highest popularity and idi is the id of their most popular video. The answer can be returned in any order.
#
# Example:
# Input: creators = ["alice","bob","alice","chris"], ids = ["one","two","three","four"], views = [5,10,5,4]
#
# Output: [["alice","one"],["bob","two"]]
#
# Explanation:
#
# The popularity of alice is 5 + 5 = 10.
# The popularity of bob is 10.
# The popularity of chris is 4.
# alice and bob are the most popular creators.
# For bob, the video with the highest view count is "two".
# For alice, the videos with the highest view count are "one" and "three". Since "one" is lexicographically smaller than "three", it is included in the answer.
#
# Constraints:
# n == creators.length == ids.length == views.length
# 	1 <= n <= 105
# 	1 <= creators[i].length, ids[i].length <= 5
# 	creators[i] and ids[i] consist only of lowercase English letters.
# 	0 <= views[i] <= 105
#
# Helpful references (internal KB):
# - Search the subarray with the maximum/minimum sum (array, greedy, dp-1d)
#   • When to use: When you need to find the contiguous subarray within a one-dimensional array of numbers that has the largest or smallest sum, typically in linear time.
#   • Idea: This algorithm efficiently finds the maximum (or minimum) sum of a contiguous subarray by iterating through the array and maintaining a current sum, resetting it if it becomes detrimental. It operates in O(N) time complexity with O(1) space complexity.
#   • Invariants: `global_max` holds the maximum sum of any contiguous subarray encountered up to the current element.; `current_max` holds the maximum sum of a contiguous subarray ending at the current element.
#   • Tips: Initialize current and global maximums appropriately (e.g., to negative infinity or first element).; Adapt for minimum sum by resetting current sum if it becomes positive.
#   • Pitfalls: Failing to correctly initialize maximum/minimum sum variables.; Not handling arrays where all elements are negative (for max sum) or positive (for min sum).
# - String Hashing (string, number, hashing)
#   • When to use: When comparing strings or substrings efficiently, especially for equality checks or finding duplicates, to reduce comparison time from O(m) to O(1) on average.
#   • Idea: String hashing converts a string into a numerical value (hash) using a polynomial rolling hash function, allowing for O(1) average-case comparison of strings or substrings. This technique typically involves modular arithmetic to keep hash values within a manageable range.
#   • Invariants: The hash of any prefix s[0...i] is correctly calculated based on the chosen base and modulus.; Precomputed powers of the base 'p' are available and correct for all required string lengths.
#   • Tips: Convert characters to integers starting from 1 (e.g., 'a' -> 1) to avoid zero hashes for strings like 'a', 'aa'.; Precompute powers of the base 'p' and their modular inverses for efficient rolling hash calculations.
#   • Pitfalls: Choosing 'a' -> 0 can lead to identical hashes for strings like 'a', 'aa', 'aaa', causing false positives.; Using a single hash function can lead to collisions, where different strings produce the same hash, requiring careful handling.
# - Games on arbitrary graphs (graph, array, dfs, game-theory)
#   • When to use: Use this algorithm to determine the outcome (win, lose, or draw) for every possible starting position in a two-player game played on a directed graph, assuming both players play optimally.
#   • Idea: This algorithm classifies each vertex in a directed graph as a winning, losing, or draw state for a two-player game. It iteratively applies rules based on neighbor states, optimized by a Depth-First Search on the reversed graph, achieving an O(M) time complexity.
#   • Invariants: A vertex `u` is a winning state if and only if it has at least one successor `v` that is a losing state.; A vertex `u` is a losing state if and only if all its successors `v` are winning states.
#   • Tips: Construct the reversed graph to efficiently propagate state classifications from successors to predecessors.; Initialize states for terminal vertices (those with no outgoing edges) as losing states.
#   • Pitfalls: Forgetting to account for draw states, which occur when neither winning nor losing conditions are met.; Incorrectly classifying terminal nodes; they are typically losing states in normal play games.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def mostPopularCreator(self, creators, ids, views):
        """
        :type creators: List[str]
        :type ids: List[str]
        :type views: List[int]
        :rtype: List[List[str]]
        """
        from collections import defaultdict

        creator_popularity = defaultdict(int)
        creator_top_video = {}

        # Calculate total views per creator and track top video
        for creator, vid_id, view_count in zip(creators, ids, views):
            creator_popularity[creator] += view_count
            
            if creator not in creator_top_video:
                creator_top_video[creator] = (vid_id, view_count)
            else:
                top_vid_id, top_view_count = creator_top_video[creator]
                if view_count > top_view_count or (view_count == top_view_count and vid_id < top_vid_id):
                    creator_top_video[creator] = (vid_id, view_count)

        # Find the maximum popularity
        max_popularity = max(creator_popularity.values())

        # Collect all creators with maximum popularity
        result = []
        for creator, total_views in creator_popularity.items():
            if total_views == max_popularity:
                top_vid_id, _ = creator_top_video[creator]
                result.append([creator, top_vid_id])

        return result