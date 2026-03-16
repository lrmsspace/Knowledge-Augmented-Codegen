// Source: https://leetcode.com/problems/find-the-k-th-character-in-string-game-ii/   |   Difficulty: Hard
//
// Problem Description:
// Alice and Bob are playing a game. Initially, Alice has a string word = "a".
//
// You are given a positive integer k. You are also given an integer array operations, where operations[i] represents the type of the ith operation.
//
// Now Bob will ask Alice to perform all operations in sequence:
//
//
// 	If operations[i] == 0, append a copy of word to itself.
// 	If operations[i] == 1, generate a new string by changing each character in word to its next character in the English alphabet, and append it to the original word. For example, performing the operation on "c" generates "cd" and performing the operation on "zb" generates "zbac".
//
//
// Return the value of the kth character in word after performing all the operations.
//
// Note that the character 'z' can be changed to 'a' in the second type of operation.
//
// Example:
// Input: k = 5, operations = [0,0,0]
//
// Output: "a"
//
// Explanation:
//
// Initially, word == "a". Alice performs the three operations as follows:
//
//
// 	Appends "a" to "a", word becomes "aa".
// 	Appends "aa" to "aa", word becomes "aaaa".
// 	Appends "aaaa" to "aaaa", word becomes "aaaaaaaa".
//
// Constraints:
// 1 <= k <= 1014
// 	1 <= operations.length <= 100
// 	operations[i] is either 0 or 1.
// 	The input is generated such that word has at least k characters after all operations.
//
// Helpful references (internal KB):
// - N/A
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    char kthCharacter(long long k, vector<int>& operations) {
        long long n = 1; // Initial length of the string "a"
        
        // Calculate the length of the string after all operations
        for (int op : operations) {
            if (op == 0) {
                n *= 2; // Doubling the string
            } else {
                n *= 2; // Doubling the string again for the next character operation
            }
        }
        
        // Traverse the operations in reverse to find the k-th character
        for (int i = operations.size() - 1; i >= 0; --i) {
            int op = operations[i];
            if (op == 0) {
                if (k > n / 2) {
                    k -= n / 2; // Move to the second half of the string
                }
                n /= 2; // Update n to reflect the previous state of the string
            } else {
                if (k > n / 2) {
                    k -= n / 2; // Move to the second half of the string
                    k = (k - 1) % 26 + 1; // Adjust k for the next character operation
                }
                n /= 2; // Update n to reflect the previous state of the string
            }
        }
        
        // The final character is determined by k, which is now between 1 and 26
        return 'a' + (k - 1) % 26;          
    }
};
