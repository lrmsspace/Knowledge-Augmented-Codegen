# Source: https://leetcode.com/problems/distant-barcodes/   |   Difficulty: Medium
#
# Problem Description:
# In a warehouse, there is a row of barcodes, where the ith barcode is barcodes[i].
#
# Rearrange the barcodes so that no two adjacent barcodes are equal. You may return any answer, and it is guaranteed an answer exists.
#
# Example:
# Input: barcodes = [1,1,1,2,2,2]
# Output: [2,1,2,1,2,1]
#
# Constraints:
# 1 <= barcodes.length <= 10000
# 	1 <= barcodes[i] <= 10000
#
# Helpful references (internal KB):
# - Data Compression (tree, heap, greedy, recursion, counting)
#   • When to use: Use when you need to losslessly compress data by assigning shorter bit sequences to more frequent symbols, aiming for the shortest possible average code length. It is effective for data with non-uniform character distributions.
#   • Idea: Huffman coding is a greedy algorithm that constructs an optimal prefix code for a given set of symbols and their frequencies. It builds a binary tree (Huffman trie) by repeatedly merging the two nodes with the smallest frequencies, resulting in an encoding with O(N + K log K) time complexity, where N is input length and K is alphabet size.
#   • Invariants: The priority queue always contains valid Huffman nodes, each representing a subtree or a leaf character.; Every internal node in the Huffman tree has exactly two children, and its frequency is the sum of its children's frequencies.
#   • Tips: Use a min-priority queue to efficiently retrieve and combine the two lowest-frequency nodes.; Represent the Huffman tree explicitly to generate codes and for decoding.
#   • Pitfalls: The overhead of storing the Huffman tree or frequency table can negate compression benefits for small inputs.; Not truly optimal for all data types; it's a statistical compression method.
# - Priority Queues (array, heap, heap-select)
#   • When to use: Use when you need to efficiently retrieve the highest or lowest priority item from a dynamic collection. It's ideal for scenarios requiring frequent insertions and extractions of extreme values without full sorting.
#   • Idea: A Priority Queue is an abstract data type that provides efficient retrieval of the maximum or minimum element. It is typically implemented using a binary heap, which stores elements in an array representing a complete binary tree, maintaining the heap-ordered property for O(log N) insertion and deletion.
#   • Invariants: For a max-heap, every parent node's key is greater than or equal to its children's keys.; The heap structure is always a complete binary tree, represented contiguously in an array.
#   • Tips: Represent the complete binary tree using an array, often 1-indexed for simpler parent/child calculations.; Use 'swim' (bottom-up reheapify) after insertion to restore heap order.
#   • Pitfalls: Forgetting to handle 0-indexed vs 1-indexed array representations correctly (parent/child formulas differ).; Violating the heap-ordered property during updates or custom operations.
# - Priority Queues (heap, stack, heap-select)
#   • When to use: Use when you need to efficiently retrieve the element with the highest (or lowest) priority from a collection, especially when elements are added or removed frequently.
#   • Idea: A priority queue is a data structure that allows efficient retrieval of the element with the highest or lowest priority, and efficient insertion of new elements. Operations typically run in logarithmic time, O(log N).
#   • Invariants: The priority queue maintains the heap property: parent nodes are always greater than/equal to (or less than/equal to) their children.; For a K-selection problem, the priority queue contains at most K elements, representing the K largest/smallest seen so far.
#   • Tips: Use a min-priority queue to find the K largest elements by keeping at most K elements.; Use a max-priority queue to find the K smallest elements by keeping at most K elements.
#   • Pitfalls: Confusing min-priority queue with max-priority queue for the desired extremum.; Inefficient underlying implementation leading to O(N) operations instead of O(log N).
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def rearrangeBarcodes(self, barcodes):
        """
        :type barcodes: List[int]
        :rtype: List[int]
        """
        from collections import Counter
        import heapq

        # Count the frequency of each barcode
        count = Counter(barcodes)
        # Create a max-heap based on the frequency
        max_heap = [(-freq, barcode) for barcode, freq in count.items()]
        heapq.heapify(max_heap)

        result = []
        prev_freq, prev_barcode = 0, None

        while max_heap:
            freq, barcode = heapq.heappop(max_heap)
            result.append(barcode)

            # If there is a previously used barcode, push it back into the heap
            if prev_freq < 0:
                heapq.heappush(max_heap, (prev_freq, prev_barcode))

            # Update previous barcode and frequency
            prev_freq, prev_barcode = freq + 1, barcode  # Increment frequency since it's negative

        return result