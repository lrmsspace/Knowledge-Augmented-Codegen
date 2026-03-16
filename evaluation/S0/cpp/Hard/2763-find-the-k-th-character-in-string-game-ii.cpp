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

class Solution {
public:
    char kthCharacter(long long k, vector<int>& operations) {
        long long length = 1;  // initial length of word "a"
        int n = operations.size();
        
        // Calculate final length after all operations
        for (int i = 0; i < n; i++) {
            if (operations[i] == 0) {
                length *= 2;
            } else {
                length *= 2;
            }
        }
        
        // Backtrack to find the k-th character
        for (int i = n - 1; i >= 0; i--) {
            if (operations[i] == 0) {
                length /= 2;
                if (k > length) {
                    k -= length;  // k is in the second half
                }
            } else {
                length /= 2;
                if (k > length) {
                    k -= length;  // k is in the second half
                    // Move to next character in alphabet
                    if (--k < 0) k += 26;  // wrap around if needed
                }
            }
        }
        
        // The first character is 'a', so we add (k-1) to it
        return 'a' + (k - 1) % 26;          
    }
};
