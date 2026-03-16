// Source: https://leetcode.com/problems/count-almost-equal-pairs-ii/   |   Difficulty: Hard
//
// Problem Description:
// Attention: In this version, the number of operations that can be performed, has been increased to twice.
//
// You are given an array nums consisting of positive integers.
//
// We call two integers x and y almost equal if both integers can become equal after performing the following operation at most twice:
//
//
// 	Choose either x or y and swap any two digits within the chosen number.
//
//
// Return the number of indices i and j in nums where i < j such that nums[i] and nums[j] are almost equal.
//
// Note that it is allowed for an integer to have leading zeros after performing an operation.
//
// Example:
// Input: nums = [1023,2310,2130,213]
//
// Output: 4
//
// Explanation:
//
// The almost equal pairs of elements are:
//
//
// 	1023 and 2310. By swapping the digits 1 and 2, and then the digits 0 and 3 in 1023, you get 2310.
// 	1023 and 213. By swapping the digits 1 and 0, and then the digits 1 and 2 in 1023, you get 0213, which is 213.
// 	2310 and 213. By swapping the digits 2 and 0, and then the digits 3 and 2 in 2310, you get 0213, which is 213.
// 	2310 and 2130. By swapping the digits 3 and 1 in 2310, you get 2130.
//
// Constraints:
// 2 <= nums.length <= 5000
// 	1 <= nums[i] < 107
//
// Helpful references (internal KB):
// - String Sorts (array, string, number, radix-sort, counting-sort)
//   • When to use: Use when sorting a large collection of fixed-length strings or integers, especially when the key range (alphabet size) is small. It is efficient for data with uniform key lengths.
//   • Idea: LSD Radix Sort sorts elements by processing digits or characters from the least significant to the most significant, using a stable counting sort for each position. It achieves a time complexity of O(W * (N + R)), where W is the key length, N is the number of items, and R is the radix.
//   • Invariants: After each pass 'd' (from 'w-1' down to '0'), the array 'a' is stably sorted based on characters from position 'd' to 'w-1'.; The 'count' array accurately reflects the frequency of each character at the current digit 'd' before cumulation.
//   • Tips: Utilize counting sort as the stable inner sorting algorithm for each digit pass.; Process characters or digits from right to left (least significant to most significant).
//   • Pitfalls: Inefficient for variable-length strings without proper padding or specialized handling.; Can be slower than comparison sorts for small input sizes or very large radix (R).
// - Non-negative Integers without Consecutive Ones (number, enumeration, simulation)
//   • When to use: Use when counting numbers up to a given limit that satisfy a specific bit pattern constraint, particularly when the limit is small enough for direct iteration and checking.
//   • Idea: This approach iterates through every non-negative integer from 0 up to the given limit num. For each integer, it simulates checking its binary representation to determine if it contains any two consecutive '1's.
//   • Invariants: count stores the number of integers k (where 0 <= k < i) that do not have consecutive ones.; All integers j such that 0 <= j < i have been processed.
//   • Tips: Use bitwise operations like (i & (i >> 1)) to efficiently detect consecutive ones.; Remember to include 0 in the count as it satisfies the condition (no consecutive ones).
//   • Pitfalls: Performance degradation for large num due to linear scan and per-number bit check.; Incorrectly handling the upper bound of the iteration (e.g., i < num instead of i <= num).
// - String Hashing (string, array, hashing, enumeration)
//   • When to use: Use string hashing to efficiently compare substrings or patterns within a larger text, or to quickly check for duplicate strings. It's ideal for problems requiring fast equality checks on string segments.
//   • Idea: String hashing converts a string or substring into a numerical hash value, allowing for O(1) comparison of substrings after O(N) precomputation. It typically uses polynomial hashing with a prime base and modulus to minimize collisions.
//   • Invariants: The hash value for the prefix S[0...i] is correctly computed and stored, based on the chosen polynomial hashing scheme.; The base 'p' and modulus 'm' remain constant throughout the hash computation for consistent results.
//   • Tips: Choose a large prime number for the base 'p' (e.g., 31, 53) to reduce collisions.; Select a large prime number for the modulus 'm' (e.g., 10^9+7, 10^9+9) to further minimize collision probability.
//   • Pitfalls: Avoid using 2^64 as a modulus, as specific collision-generating strings exist for this choice.; A small modulus 'm' or base 'p' drastically increases the likelihood of hash collisions.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    int countPairs(vector<int>& nums) {
        const int n = nums.size();
        unordered_map<string, int> freq;

        for (int num : nums) {
            string key(10, '0');
            int idx = 9;
            while (num > 0) {
                key[idx--] = '0' + (num % 10);
                num /= 10;
            }
            freq[key]++;
        }

        long long result = 0;
        for (const auto& entry : freq) {
            long long count = entry.second;
            result += count * (count - 1) / 2;
        }

        return static_cast<int>(result);            
    }
};
