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
// - Balanced Ternary (number, string, enumeration, simulation)
//   • When to use: Use when a number system is required that can represent both positive and negative integers symmetrically without an explicit sign bit, or for specific arithmetic properties.
//   • Idea: Balanced ternary is a non-standard positional numeral system using digits -1 (Z), 0, and 1. The conversion from decimal typically involves an intermediate standard ternary representation, then iteratively adjusting digits from least significant to most significant with carry operations, achieving O(log N) time complexity.
//   • Invariants: All digits to the right of the current processing position are already in valid balanced ternary form (Z, 0, or 1).; The sum of the value represented by the processed digits and the value represented by the remaining digits (including current carry) equals the original number.
//   • Tips: First convert the decimal number to standard ternary (base 3).; Process digits from right to left (least significant to most significant).
//   • Pitfalls: Forgetting to propagate carries correctly, especially when a '2' or '3' appears.; Incorrectly handling the sign of 'Z' (-1) during back-conversion to decimal.
// - String Hashing (string, array, hashing, enumeration)
//   • When to use: Use string hashing to efficiently compare substrings or patterns within a larger text, or to quickly check for duplicate strings. It's ideal for problems requiring fast equality checks on string segments.
//   • Idea: String hashing converts a string or substring into a numerical hash value, allowing for O(1) comparison of substrings after O(N) precomputation. It typically uses polynomial hashing with a prime base and modulus to minimize collisions.
//   • Invariants: The hash value for the prefix S[0...i] is correctly computed and stored, based on the chosen polynomial hashing scheme.; The base 'p' and modulus 'm' remain constant throughout the hash computation for consistent results.
//   • Tips: Choose a large prime number for the base 'p' (e.g., 31, 53) to reduce collisions.; Select a large prime number for the modulus 'm' (e.g., 10^9+7, 10^9+9) to further minimize collision probability.
//   • Pitfalls: Avoid using 2^64 as a modulus, as specific collision-generating strings exist for this choice.; A small modulus 'm' or base 'p' drastically increases the likelihood of hash collisions.
// - Manhattan Distance (array, number, enumeration, max-window)
//   • When to use: When calculating distances on a grid where movement is restricted to cardinal directions, or when optimizing expressions involving sums of absolute differences of coordinates.
//   • Idea: Manhattan distance, or L1 distance, measures the distance between two points as the sum of the absolute differences of their Cartesian coordinates. It is commonly used to find optimal paths on a grid or to transform coordinate systems for specific optimizations, often with O(N) or O(N log N) complexity for common problems like farthest pair.
//   • Invariants: For any two points P1(x1, y1) and P2(x2, y2), the Manhattan distance is |x1-x2| + |y1-y2|.; The maximum Manhattan distance between any two points is found by considering the maximum of (max(x+y) - min(x+y)) and (max(x-y) - min(x-y)) over all points.
//   • Tips: For 2D points (x, y), Manhattan distance can be transformed by rotating coordinates: (x', y') = (x+y, x-y).; After coordinate rotation, the Manhattan distance problem often simplifies to finding min/max values of the transformed coordinates.
//   • Pitfalls: Confusing Manhattan distance with Euclidean distance (L2 distance) or Chebyshev distance (L-infinity).; Incorrectly applying coordinate rotation for problems not involving sums of absolute differences.
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
        string res;
        if (s.find('@') != string::npos) {
            // Email address
            auto at_pos = s.find('@');
            res += tolower(s[0]);
            res += "*****";
            res += tolower(s[at_pos - 1]);
            res += '@';
            for (size_t i = at_pos + 1; i < s.size(); ++i) {
                res += tolower(s[i]);
            }
        } else {
            // Phone number
            string digits;
            for (char c : s) {
                if (isdigit(c)) {
                    digits += c;
                }
            }
            int local_len = 10;
            int country_len = digits.size() - local_len;
            if (country_len > 0) {
                res += '+';
                for (int i = 0; i < country_len; ++i) {
                    res += '*';
                }
                res += '-';
            }
            res += "***-***-";
            res += digits.substr(digits.size() - local_len);
        }
        return res;         
    }
};
