// Source: https://leetcode.com/problems/masking-personal-information/   |   Difficulty: Medium
//
// Problem Description:
// You are given a personal information string s, representing either an email address or a phone number. Return the masked personal information using the below rules.
//
// Email address:
//
// An email address is:
//
//
// 	A name consisting of uppercase and lowercase English letters, followed by
// 	The '@' symbol, followed by
// 	The domain consisting of uppercase and lowercase English letters with a dot '.' somewhere in the middle (not the first or last character).
//
//
// To mask an email:
//
//
// 	The uppercase letters in the name and domain must be converted to lowercase letters.
// 	The middle letters of the name (i.e., all but the first and last letters) must be replaced by 5 asterisks "*****".
//
//
// Phone number:
//
// A phone number is formatted as follows:
//
//
// 	The phone number contains 10-13 digits.
// 	The last 10 digits make up the local number.
// 	The remaining 0-3 digits, in the beginning, make up the country code.
// 	Separation characters from the set {'+', '-', '(', ')', ' '} separate the above digits in some way.
//
//
// To mask a phone number:
//
//
// 	Remove all separation characters.
// 	The masked phone number should have the form:
// 	
// 		"***-***-XXXX" if the country code has 0 digits.
// 		"+*-***-***-XXXX" if the country code has 1 digit.
// 		"+**-***-***-XXXX" if the country code has 2 digits.
// 		"+***-***-***-XXXX" if the country code has 3 digits.
// 	
// 	
// 	"XXXX" is the last 4 digits of the local number.
//
// Example:
// Input: s = "LeetCode@LeetCode.com"
// Output: "l*****e@leetcode.com"
// Explanation: s is an email address.
// The name and domain are converted to lowercase, and the middle of the name is replaced by 5 asterisks.
//
// Constraints:
// s is either a valid email or a phone number.
// 	If s is an email:
// 	
// 		8 <= s.length <= 40
// 		s consists of uppercase and lowercase English letters and exactly one '@' symbol and '.' symbol.
// 	
// 	
// 	If s is a phone number:
// 	
// 		10 <= s.length <= 20
// 		s consists of digits, spaces, and the symbols '(', ')', '-', and '+'.
//
// Helpful references (internal KB):
// - String Hashing (string, number, hashing)
//   • When to use: Use when needing to efficiently compare strings or substrings, especially in scenarios involving large texts or numerous comparisons. It's also useful for pattern matching and detecting duplicates in collections of strings.
//   • Idea: String hashing converts a string into a numerical value (hash) to enable fast comparisons and lookups. This technique typically uses polynomial hashing with a base and a modulus, offering O(L) for initial hash computation and O(1) for substring hashes after O(N) precomputation.
//   • Invariants: The hash of a string S of length L is (S[0]*P^(L-1) + S[1]*P^(L-2) + ... + S[L-1]*P^0) % M.; For any substring S[i...j], its hash can be derived from precomputed prefix hashes in O(1) time.
//   • Tips: Use multiple hash functions with different bases and moduli to reduce collision probability.; Choose a large prime modulus (e.g., 10^9 + 7) and a random base for robustness.
//   • Pitfalls: Hash collisions are possible; always verify equality for critical applications or use multiple hashes.; Choosing a small or non-prime modulus significantly increases the risk of collisions.
// - palindrome-partitioning (string, two-pointers, simulation)
//   • When to use: When a string needs to be decomposed into all possible sets of palindromic substrings. It's suitable for problems requiring exhaustive enumeration of such partitions.
//   • Idea: This algorithm finds all possible ways to partition a given string such that every substring in the partition is a palindrome. It typically uses a recursive exploration approach combined with a two-pointer check for palindrome validation, resulting in an exponential time complexity.
//   • Invariants: At any point, the `step` list contains a valid palindromic partition of the prefix processed so far.; The `s` parameter in the recursive function always represents the unpartitioned suffix of the original string.
//   • Tips: Implement the `isPalindrome` check efficiently using two pointers for O(length) time.; Use a recursive helper function to explore all possible partition points.
//   • Pitfalls: Incorrectly handling substring boundaries, leading to off-by-one errors or incorrect partitions.; Forgetting to backtrack (remove the last added substring) after a recursive call returns.
// - Digit DP (array, number, digit-dp)
//   • When to use: Use Digit DP to count numbers within a given range [a, b] that satisfy a property based on their digits. It's effective when the property can be checked digit by digit.
//   • Idea: Digit DP is a dynamic programming technique to count numbers within a given range [A, B] that satisfy specific properties related to their digits. It typically involves a recursive function with memoization, building numbers digit by digit, and has a complexity roughly proportional to (number of digits * state space).
//   • Invariants: The `tight` parameter accurately reflects if the current prefix matches the upper bound's prefix.; The `is_leading_zero` parameter correctly indicates if all preceding digits chosen were zero.
//   • Tips: Define the DP state carefully, including index, tight constraint, and leading zero flag.; Handle leading zeros correctly, as they can affect properties like sum or count of digits.
//   • Pitfalls: Incorrectly handling the 'tight' constraint, leading to overcounting or undercounting.; Forgetting to account for leading zeros or mismanaging their impact on the property.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    string maskPII(string s) {
        if (s.find('@') != string::npos) {
            // Email case
            transform(s.begin(), s.end(), s.begin(), ::tolower);
            int at_pos = s.find('@');
            return s.substr(0, 1) + "*****" + s.substr(at_pos - 1);
        } else {
            // Phone number case
            string digits;
            for (char c : s) {
                if (isdigit(c)) {
                    digits += c;
                }
            }
            int local_len = 10;
            string local = "***-***-" + digits.substr(digits.size() - local_len);
            if (digits.size() > local_len) {
                return "+" + string(digits.size() - local_len, '*') + "-" + local;
            }
            return local;
        }           
    }
};
