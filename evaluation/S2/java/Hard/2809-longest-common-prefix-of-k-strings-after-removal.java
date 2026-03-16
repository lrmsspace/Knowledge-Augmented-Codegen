// Source: https://leetcode.com/problems/longest-common-prefix-of-k-strings-after-removal/   |   Difficulty: Hard
//
// Problem Description:
// You are given an array of strings words and an integer k.
//
// For each index i in the range [0, words.length - 1], find the length of the longest common prefix among any k strings (selected at distinct indices) from the remaining array after removing the ith element.
//
// Return an array answer, where answer[i] is the answer for ith element. If removing the ith element leaves the array with fewer than k strings, answer[i] is 0.
//
// Example:
// Input: words = ["jump","run","run","jump","run"], k = 2
//
// Output: [3,4,4,3,4]
//
// Explanation:
//
//
// 	Removing index 0 ("jump"):
//
// 	
// 		words becomes: ["run", "run", "jump", "run"]. "run" occurs 3 times. Choosing any two gives the longest common prefix "run" (length 3).
// 	
// 	
// 	Removing index 1 ("run"):
// 	
// 		words becomes: ["jump", "run", "jump", "run"]. "jump" occurs twice. Choosing these two gives the longest common prefix "jump" (length 4).
// 	
// 	
// 	Removing index 2 ("run"):
// 	
// 		words becomes: ["jump", "run", "jump", "run"]. "jump" occurs twice. Choosing these two gives the longest common prefix "jump" (length 4).
// 	
// 	
// 	Removing index 3 ("jump"):
// 	
// 		words becomes: ["jump", "run", "run", "run"]. "run" occurs 3 times. Choosing any two gives the longest common prefix "run" (length 3).
// 	
// 	
// 	Removing index 4 ("run"):
// 	
// 		words becomes: ["jump", "run", "run", "jump"]. "jump" occurs twice. Choosing these two gives the longest common prefix "jump" (length 4).
//
// Constraints:
// 1 <= k <= words.length <= 105
// 	1 <= words[i].length <= 104
// 	words[i] consists of lowercase English letters.
// 	The sum of words[i].length is smaller than or equal 105.
//
// Helpful references (internal KB):
// - Prefix function. Knuth–Morris–Pratt algorithm (string, array, kmp, dp-2d)
//   • When to use: Use when efficiently finding all occurrences of a pattern in a text, analyzing string periodicity, or counting distinct substrings. It is especially useful for processing extremely long or recursively defined strings where explicit construction is impossible.
//   • Idea: The Knuth-Morris-Pratt (KMP) algorithm leverages a precomputed prefix function (LPS array) to avoid redundant comparisons during string searching, achieving linear time complexity. The prefix function itself determines the longest proper prefix of a string that is also a suffix, enabling various string property analyses in O(N) time.
//   • Invariants: For any index `i`, `pi[i]` stores the length of the longest proper prefix of `s[0...i]` that is also a suffix of `s[0...i]`.; During prefix function computation, `j` always represents the length of the longest proper prefix of `s[0...i-1]` that is also a suffix.
//   • Tips: The prefix function `pi[i]` stores the length of the longest proper prefix of `s[0...i]` that is also a suffix.; Concatenate pattern, a unique separator, and text (`P + # + T`) to find all pattern occurrences.
//   • Pitfalls: Off-by-one errors with array indexing or the precise definition of the prefix function.; Incorrectly handling the unique separator character in concatenated strings, leading to false matches.
// - kth-largest-element-in-an-array (heap, array, heap-select)
//   • When to use: Use this when you need to find the k-th largest (or smallest) element in an unsorted array efficiently without fully sorting it. It is particularly effective when k is much smaller than N.
//   • Idea: This algorithm uses a min-heap of size k to store the k largest elements encountered so far. It iterates through the array, comparing each element with the heap's minimum; if larger, it replaces the minimum, resulting in O(N log K) time complexity and O(K) space complexity.
//   • Invariants: The min-heap always contains at most k elements.; Every element in the min-heap is greater than or equal to any element that has been processed and discarded.
//   • Tips: Use a min-heap to find the k-th largest element, and a max-heap for the k-th smallest.; Initialize the heap with the first k elements from the input array.
//   • Pitfalls: Incorrectly using a max-heap when trying to find the k-th largest element.; Failing to handle edge cases such as k=1 or k equal to the array's length.
// - Lowest Common Ancestor (array, sparse-table)
//   • When to use: Use this when you need to find the lowest common ancestor of many pairs of nodes in a static tree efficiently. It excels in scenarios with numerous queries after initial setup.
//   • Idea: This technique finds the LCA by transforming the problem into a Range Minimum Query (RMQ) on an Euler tour of the tree. It achieves O(N log N) precomputation time and O(1) query time.
//   • Invariants: The sparse_table[k][i] stores the minimum depth in the Euler tour array segment starting at index i and spanning 2^k elements.; The first_occurrence array correctly maps each node to its initial appearance index in the Euler tour.
//   • Tips: Perform an Euler tour (DFS traversal) to linearize the tree into an array of nodes and their depths.; Store the first occurrence index of each node in the Euler tour array.
//   • Pitfalls: Off-by-one errors when calculating range lengths or sparse table indices.; Incorrectly handling the Euler tour array, especially when mapping back to original nodes.
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    public int[] longestCommonPrefix(String[] words, int k) {
        int n = words.length;
        int[] answer = new int[n];
        Map<String, Integer> freqMap = new HashMap<>();

        // Count frequency of each word
        for (String word : words) {
            freqMap.put(word, freqMap.getOrDefault(word, 0) + 1);
        }

        // Create a list of unique words and their frequencies
        List<Map.Entry<String, Integer>> wordFreqList = new ArrayList<>(freqMap.entrySet());
        wordFreqList.sort((a, b) -> b.getValue() - a.getValue()); // Sort by frequency descending

        // Precompute longest common prefix for the top k most frequent words
        String[] topKWords = new String[Math.min(k, wordFreqList.size())];
        for (int i = 0; i < topKWords.length; i++) {
            topKWords[i] = wordFreqList.get(i).getKey();
        }

        // Compute longest common prefix length for each word after removal
        for (int i = 0; i < n; i++) {
            String currentWord = words[i];
            int currentFreq = freqMap.get(currentWord);

            if (currentFreq < k) {
                answer[i] = 0; // Not enough words left to form a prefix
                continue;
            }

            // Find the longest common prefix among the top k most frequent words excluding the current word
            int maxPrefixLength = 0;
            for (String topWord : topKWords) {
                if (!topWord.equals(currentWord)) {
                    maxPrefixLength = Math.max(maxPrefixLength, longestCommonPrefixLength(currentWord, topWord));
                }
            }
            answer[i] = maxPrefixLength;
        }

        return answer;          
    }
}
