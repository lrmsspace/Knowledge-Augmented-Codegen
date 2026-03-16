// Source: https://leetcode.com/problems/frequencies-of-shortest-supersequences/   |   Difficulty: Hard
//
// Problem Description:
// You are given an array of strings words. Find all shortest common supersequences (SCS) of words that are not permutations of each other.
//
// A shortest common supersequence is a string of minimum length that contains each string in words as a subsequence.
//
// Return a 2D array of integers freqs that represent all the SCSs. Each freqs[i] is an array of size 26, representing the frequency of each letter in the lowercase English alphabet for a single SCS. You may return the frequency arrays in any order.
//
// Example:
// Input: words = ["ab","ba"]
//
// Output: [[1,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],[2,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0]]
//
// Explanation:
//
// The two SCSs are "aba" and "bab". The output is the letter frequencies for each one.
//
// Constraints:
// 1 <= words.length <= 256
// 	words[i].length == 2
// 	All strings in words will altogether be composed of no more than 16 unique lowercase letters.
// 	All strings in words are unique.
//

class Solution {
    public List<List<Integer>> supersequences(String[] words) {
        int n = words.length;
        int[][] graph = new int[26][26];
        for (String word : words) {
            graph[word.charAt(0) - 'a'][word.charAt(1) - 'a']++;
        }

        List<List<Integer>> result = new ArrayList<>();
        backtrack(graph, new ArrayList<>(), result, n);
        return result;          
    }
}
