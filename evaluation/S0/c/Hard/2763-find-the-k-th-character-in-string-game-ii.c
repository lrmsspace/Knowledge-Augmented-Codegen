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

char kthCharacter(long long k, int* operations, int operationsSize) {
    long long length = 1; // initial length of "a"
    for (int i = 0; i < operationsSize; ++i) {
        if (operations[i] == 0) {
            length *= 2;
        } else {
            length = length * 2 > k ? length * 2 : k; // only care if length exceeds k
        }
    }

    for (int i = operationsSize - 1; i >= 0; --i) {
        if (operations[i] == 0) {
            length /= 2;
            if (k > length) {
                k -= length;
            }
        } else {
            length /= 2;
            if (k > length) {
                k -= length;
                // character shifts by 1
                // 'a' + ((k - 1 + 1) % 26)
                // but we don't know the character yet, so just note the shift
            }
        }
    }

    // After all operations reversed, we are at the original string "a"
    // The number of shifts is equal to the number of times we subtracted length in the second operation
    int shifts = 0;
    long long tempLength = 1;
    for (int i = 0; i < operationsSize; ++i) {
        if (operations[i] == 0) {
            tempLength *= 2;
        } else {
            if (k > tempLength) {
                shifts++;
                k -= tempLength;
            }
            tempLength *= 2;
        }
    }

    return 'a' + (shifts % 26);     
}
