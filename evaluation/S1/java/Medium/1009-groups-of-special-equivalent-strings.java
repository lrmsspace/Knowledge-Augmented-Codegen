// Source: https://leetcode.com/problems/groups-of-special-equivalent-strings/   |   Difficulty: Medium
//
// Problem Description:
// You are given an array of strings of the same length words.
//
// In one move, you can swap any two even indexed characters or any two odd indexed characters of a string words[i].
//
// Two strings words[i] and words[j] are special-equivalent if after any number of moves, words[i] == words[j].
//
//
// 	For example, words[i] = "zzxy" and words[j] = "xyzz" are special-equivalent because we may make the moves "zzxy" -> "xzzy" -> "xyzz".
//
//
// A group of special-equivalent strings from words is a non-empty subset of words such that:
//
//
// 	Every pair of strings in the group are special equivalent, and
// 	The group is the largest size possible (i.e., there is not a string words[i] not in the group such that words[i] is special-equivalent to every string in the group).
//
//
// Return the number of groups of special-equivalent strings from words.
//
// Example:
// Input: words = ["abcd","cdab","cbad","xyzz","zzxy","zzyx"]
// Output: 3
// Explanation: 
// One group is ["abcd", "cdab", "cbad"], since they are all pairwise special equivalent, and none of the other strings is all pairwise special equivalent to these.
// The other two groups are ["xyzz", "zzxy"] and ["zzyx"].
// Note that in particular, "zzxy" is not special equivalent to "zzyx".
//
// Constraints:
// 1 <= words.length <= 1000
// 	1 <= words[i].length <= 20
// 	words[i] consist of lowercase English letters.
// 	All the strings are of the same length.
//
// Helpful references (internal KB):
// - String Sorts (array, string, number, radix-sort, counting-sort)
//   • When to use: Use when sorting a large collection of fixed-length strings or integers, especially when the key range (alphabet size) is small. It is efficient for data with uniform key lengths.
//   • Idea: LSD Radix Sort sorts elements by processing digits or characters from the least significant to the most significant, using a stable counting sort for each position. It achieves a time complexity of O(W * (N + R)), where W is the key length, N is the number of items, and R is the radix.
//   • Invariants: After each pass 'd' (from 'w-1' down to '0'), the array 'a' is stably sorted based on characters from position 'd' to 'w-1'.; The 'count' array accurately reflects the frequency of each character at the current digit 'd' before cumulation.
//   • Tips: Utilize counting sort as the stable inner sorting algorithm for each digit pass.; Process characters or digits from right to left (least significant to most significant).
//   • Pitfalls: Inefficient for variable-length strings without proper padding or specialized handling.; Can be slower than comparison sorts for small input sizes or very large radix (R).
// - Manacher's Algorithm - Finding all sub-p (string, array, enumeration)
//   • When to use: Use when you need to find all palindromic substrings within a given string, or determine the longest palindromic substring, in optimal linear time.
//   • Idea: Manacher's Algorithm efficiently finds the length of the longest palindromic substring centered at each position in a given string, handling both odd and even lengths uniformly via preprocessing. It achieves this in optimal O(N) time complexity.
//   • Invariants: p[i] correctly stores the radius of the longest palindrome centered at i in the transformed string.; The right_boundary always marks the rightmost extent of the largest palindrome found so far.
//   • Tips: Preprocess the string with a unique delimiter to unify odd and even length palindromes.; Leverage the mirror property around the current center to initialize palindrome radii.
//   • Pitfalls: Off-by-one errors when converting `p` array values back to original string indices or lengths.; Incorrectly handling the boundaries of the preprocessed string.
// - String Hashing (string, number, hashing)
//   • When to use: Use when needing to efficiently compare strings or substrings, especially in scenarios involving large texts or numerous comparisons. It's also useful for pattern matching and detecting duplicates in collections of strings.
//   • Idea: String hashing converts a string into a numerical value (hash) to enable fast comparisons and lookups. This technique typically uses polynomial hashing with a base and a modulus, offering O(L) for initial hash computation and O(1) for substring hashes after O(N) precomputation.
//   • Invariants: The hash of a string S of length L is (S[0]*P^(L-1) + S[1]*P^(L-2) + ... + S[L-1]*P^0) % M.; For any substring S[i...j], its hash can be derived from precomputed prefix hashes in O(1) time.
//   • Tips: Use multiple hash functions with different bases and moduli to reduce collision probability.; Choose a large prime modulus (e.g., 10^9 + 7) and a random base for robustness.
//   • Pitfalls: Hash collisions are possible; always verify equality for critical applications or use multiple hashes.; Choosing a small or non-prime modulus significantly increases the risk of collisions.
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    public int numSpecialEquivGroups(String[] words) {
        java.util.Set<String> groups = new java.util.HashSet<>();

        for (String word : words) {
            char[] evenChars = new char[(word.length() + 1) / 2];
            char[] oddChars = new char[word.length() / 2];

            for (int i = 0; i < word.length(); i++) {
                if (i % 2 == 0) {
                    evenChars[i / 2] = word.charAt(i);
                } else {
                    oddChars[i / 2] = word.charAt(i);
                }
            }

            java.util.Arrays.sort(evenChars);
            java.util.Arrays.sort(oddChars);

            String key = new String(evenChars) + new String(oddChars);
            groups.add(key);
        }

        return groups.size();           
    }
}
