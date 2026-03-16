// Source: https://leetcode.com/problems/count-number-of-texts/   |   Difficulty: Medium
//
// Problem Description:
// Alice is texting Bob using her phone. The mapping of digits to letters is shown in the figure below.
//
// In order to add a letter, Alice has to press the key of the corresponding digit i times, where i is the position of the letter in the key.
//
//
// 	For example, to add the letter 's', Alice has to press '7' four times. Similarly, to add the letter 'k', Alice has to press '5' twice.
// 	Note that the digits '0' and '1' do not map to any letters, so Alice does not use them.
//
//
// However, due to an error in transmission, Bob did not receive Alice's text message but received a string of pressed keys instead.
//
//
// 	For example, when Alice sent the message "bob", Bob received the string "2266622".
//
//
// Given a string pressedKeys representing the string received by Bob, return the total number of possible text messages Alice could have sent.
//
// Since the answer may be very large, return it modulo 109 + 7.
//
// Example:
// Input: pressedKeys = "22233"
// Output: 8
// Explanation:
// The possible text messages Alice could have sent are:
// "aaadd", "abdd", "badd", "cdd", "aaae", "abe", "bae", and "ce".
// Since there are 8 possible messages, we return 8.
//
// Constraints:
// 1 <= pressedKeys.length <= 105
// 	pressedKeys only consists of digits from '2' - '9'.
//
// Helpful references (internal KB):
// - String Hashing (string, number, hashing, prefix-sum)
//   • When to use: Use string hashing to efficiently compare strings, find duplicate strings, or perform fast substring searches and pattern matching in O(1) time after initial O(N) preprocessing.
//   • Idea: String hashing maps a string to a numerical value using a polynomial function, enabling O(1) comparison of strings or substrings after O(N) preprocessing.
//   • Invariants: prefix_hash[i] stores the polynomial hash of the substring s[0...i-1].; p_power[k] stores p^k mod m for efficient calculation.
//   • Tips: Use two different hash functions with distinct prime `p` and `m` values to minimize collision probability.; Precompute powers of `p` and prefix hashes to enable O(1) substring hash calculation.
//   • Pitfalls: Hash collisions can lead to incorrect results; always consider their possibility.; Integer overflow if modulo operations are not applied correctly at each step of calculation.
// - Digit DP (array, number, digit-dp)
//   • When to use: Use Digit DP to count numbers within a given range [a, b] that satisfy a property based on their digits. It's effective when the property can be checked digit by digit.
//   • Idea: Digit DP is a dynamic programming technique to count numbers within a given range [A, B] that satisfy specific properties related to their digits. It typically involves a recursive function with memoization, building numbers digit by digit, and has a complexity roughly proportional to (number of digits * state space).
//   • Invariants: The `tight` parameter accurately reflects if the current prefix matches the upper bound's prefix.; The `is_leading_zero` parameter correctly indicates if all preceding digits chosen were zero.
//   • Tips: Define the DP state carefully, including index, tight constraint, and leading zero flag.; Handle leading zeros correctly, as they can affect properties like sum or count of digits.
//   • Pitfalls: Incorrectly handling the 'tight' constraint, leading to overcounting or undercounting.; Forgetting to account for leading zeros or mismanaging their impact on the property.
// - Factorial modulo 
// p (number, counting, recursion)
//   • When to use: Use when the problem asks for the total count of possibilities or arrangements that can be naturally broken down into smaller, self-similar subproblems. It's effective for exploring decision trees or state spaces.
//   • Idea: Counting determines the number of elements or event occurrences. It uses combinatorial or iterative/recursive methods, often with O(N) or O(log N) complexity.
//   • Invariants: Each recursive call processes a smaller, well-defined subproblem.; The base cases correctly return the count for the simplest scenarios.
//   • Tips: Identify the smallest subproblem and its base cases to stop recursion.; Define the recursive relation clearly, showing how larger problems depend on smaller ones.
//   • Pitfalls: Incorrectly defining base cases can lead to infinite recursion or incorrect results.; Overlapping subproblems without memoization can lead to exponential time complexity.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

int countTexts(char* pressedKeys) {
    // The maximum length of pressedKeys is 10^5, so we can use a dynamic programming approach.
    // We will use an array dp where dp[i] represents the number of ways to decode the substring pressedKeys[0..i-1].
    // The base case is dp[0] = 1 (there's one way to decode an empty string).
    
    int mod = 1000000007;
    int n = strlen(pressedKeys);
    
    // Create a dp array to store the number of ways to decode up to each index
    long long dp[n + 1];
    dp[0] = 1; // Base case: there's one way to decode an empty string
    
    for (int i = 1; i <= n; i++) {
        char current_char = pressedKeys[i - 1];
        int count = 0;
        
        // Count how many times the current character repeats
        int j = i - 1;
        while (j >= 0 && pressedKeys[j] == current_char) {
            j--;
            count++;
        }
        
        // Now count is the number of times current_char repeats consecutively
        // We can decode this block of characters in different ways depending on the digit
        if (current_char == '7' || current_char == '9') {
            // Digits '7' and '9' can map to 4 letters, so we can take up to 4 characters
            for (int k = 1; k <= count && k <= 4; k++) {
                dp[i] = (dp[i] + dp[i - k]) % mod;
            }
        } else {
            // Digits '2', '3', '4', '5', '6', '8' can map to 3 letters, so we can take up to 3 characters
            for (int k = 1; k <= count && k <= 3; k++) {
                dp[i] = (dp[i] + dp[i - k]) % mod;
            }
        }
    }
    
    return dp[n];       
}
