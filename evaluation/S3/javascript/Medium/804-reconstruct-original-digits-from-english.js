// Source: https://leetcode.com/problems/reconstruct-original-digits-from-english/   |   Difficulty: Medium
//
// Problem Description:
// Given a string s containing an out-of-order English representation of digits 0-9, return the digits in ascending order.
//
// Example:
// Input: s = "owoztneoer"
// Output: "012"
//
// Constraints:
// 1 <= s.length <= 105
// 	s[i] is one of the characters ["e","g","f","i","h","o","n","s","r","u","t","w","v","x","z"].
// 	s is guaranteed to be valid.
//
// Helpful references (internal KB):
// - The Inclusion-Exclusion Principle (string, counting)
//   • When to use: Use when you need to determine the frequency of characters or substrings within a string. It is essential for tasks like anagram detection or checking character distribution.
//   • Idea: This technique involves iterating through a string to tally the occurrences of its constituent elements, typically characters or words. It generally operates in O(N) time complexity, where N is the string's length.
//   • Invariants: The count for each character reflects its total occurrences processed so far.; All characters encountered up to the current position have been tallied.
//   • Tips: Use a hash map (dictionary) for arbitrary character sets.; Use an array for fixed-size character sets (e.g., ASCII, lowercase English).
//   • Pitfalls: Forgetting to handle case sensitivity or ignore non-alphanumeric characters.; Incorrectly handling Unicode characters with fixed-size arrays.
// - Digit DP (array, number, digit-dp)
//   • When to use: Use Digit DP to count numbers within a given range [a, b] that satisfy a property based on their digits. It's effective when the property can be checked digit by digit.
//   • Idea: Digit DP is a dynamic programming technique to count numbers within a given range [A, B] that satisfy specific properties related to their digits. It typically involves a recursive function with memoization, building numbers digit by digit, and has a complexity roughly proportional to (number of digits * state space).
//   • Invariants: The `tight` parameter accurately reflects if the current prefix matches the upper bound's prefix.; The `is_leading_zero` parameter correctly indicates if all preceding digits chosen were zero.
//   • Tips: Define the DP state carefully, including index, tight constraint, and leading zero flag.; Handle leading zeros correctly, as they can affect properties like sum or count of digits.
//   • Pitfalls: Incorrectly handling the 'tight' constraint, leading to overcounting or undercounting.; Forgetting to account for leading zeros or mismanaging their impact on the property.
// - String Sorts (array, string, number, radix-sort, counting-sort)
//   • When to use: Use when sorting a large collection of fixed-length strings or integers, especially when the key range (alphabet size) is small. It is efficient for data with uniform key lengths.
//   • Idea: LSD Radix Sort sorts elements by processing digits or characters from the least significant to the most significant, using a stable counting sort for each position. It achieves a time complexity of O(W * (N + R)), where W is the key length, N is the number of items, and R is the radix.
//   • Invariants: After each pass 'd' (from 'w-1' down to '0'), the array 'a' is stably sorted based on characters from position 'd' to 'w-1'.; The 'count' array accurately reflects the frequency of each character at the current digit 'd' before cumulation.
//   • Tips: Utilize counting sort as the stable inner sorting algorithm for each digit pass.; Process characters or digits from right to left (least significant to most significant).
//   • Pitfalls: Inefficient for variable-length strings without proper padding or specialized handling.; Can be slower than comparison sorts for small input sizes or very large radix (R).
//
// Notes:
// - Keep the given function signature unchanged.
// - Do not add custom input parsing or console I/O unless the template explicitly requires it; rely on parameters/return value only.
// - Use standard ECMAScript features supported by LeetCode (Node.js runtime); no external packages.
// - Be careful with number precision: JavaScript Number is double; use BigInt only when necessary and keep return type consistent with the problem requirements.
// - If you introduce helper functions, define them in the same file and avoid relying on global mutable state across test cases.

/**
 * @param {string} s
 * @return {string}
 */
var originalDigits = function(s) {
    // Count frequency of each character in the input string
    const count = new Array(26).fill(0);
    for (const char of s) {
        count[char.charCodeAt(0) - 'a'.charCodeAt(0)]++;
    }
    
    // Count of each digit based on unique characters in English words
    const digits = new Array(10).fill(0);
    
    // Unique characters for each digit
    digits[0] = count['z'.charCodeAt(0) - 'a'.charCodeAt(0)]; // zero
    digits[2] = count['w'.charCodeAt(0) - 'a'.charCodeAt(0)]; // two
    digits[4] = count['u'.charCodeAt(0) - 'a'.charCodeAt(0)]; // four
    digits[6] = count['x'.charCodeAt(0) - 'a'.charCodeAt(0)]; // six
    digits[8] = count['g'.charCodeAt(0) - 'a'.charCodeAt(0)]; // eight
    
    // Derived counts based on unique characters and overlaps
    digits[3] = count['h'.charCodeAt(0) - 'a'.charCodeAt(0)] - digits[8]; // three (h is in three and eight)
    digits[5] = count['f'.charCodeAt(0) - 'a'.charCodeAt(0)] - digits[4]; // five (f is in five and four)
    digits[7] = count['s'.charCodeAt(0) - 'a'.charCodeAt(0)] - digits[6]; // seven (s is in seven and six)
    digits[9] = count['i'.charCodeAt(0) - 'a'.charCodeAt(0)] - digits[5] - digits[6] - digits[8]; // nine (i is in five, six, eight)
    digits[1] = count['o'.charCodeAt(0) - 'a'.charCodeAt(0)] - digits[2] - digits[4] - digits[0]; // one (o is in one, two, four, zero)
    
    let result = '';
    for (let i = 0; i < 10; i++) {
        result += i.toString().repeat(digits[i]);
    }
    
    return result;
};
