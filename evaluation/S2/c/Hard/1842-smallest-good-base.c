// Source: https://leetcode.com/problems/smallest-good-base/   |   Difficulty: Hard
//
// Problem Description:
// Given an integer n represented as a string, return the smallest good base of n.
//
// We call k >= 2 a good base of n, if all digits of n base k are 1's.
//
// Example:
// Input: n = "13"
// Output: "3"
// Explanation: 13 base 3 is 111.
//
// Constraints:
// n is an integer in the range [3, 1018].
// 	n does not contain any leading zeros.
//
// Helpful references (internal KB):
// - N/A
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

char* smallestGoodBase(char* n) {
    // Convert the input string to a long long integer
    long long num = atoll(n);
    
    // The maximum possible value for m (the number of digits) can be calculated
    // using the formula: num >= 1 + k + k^2 + ... + k^(m-1) = (k^m - 1) / (k - 1)
    // For m = 2, we have num >= 1 + k => k <= num - 1
    // For m = 3, we have num >= 1 + k + k^2 => k <= sqrt(num - 1)
    // Therefore, we can limit our search for m to log2(num) since the smallest base is at least 2.
    
    for (int m = 2; m < 64; m++) {
        long long low = 2;
        long long high = pow(num, 1.0 / (m - 1)) + 1; // upper bound for k
        
        while (low < high) {
            long long mid = low + (high - low) / 2;
            long long sum = (pow(mid, m) - 1) / (mid - 1); // sum of geometric series
            
            if (sum == num) {
                // If we found a valid base, return it as a string
                char* result = malloc(20 * sizeof(char)); // allocate memory for result
                sprintf(result, "%lld", mid); // convert mid to string
                return result;
            } else if (sum < num) {
                low = mid + 1; // search in the upper half
            } else {
                high = mid; // search in the lower half
            }
        }
    }
    
    // If no valid base is found, return the default base which is num - 1
    char* result = malloc(20 * sizeof(char)); // allocate memory for result
    sprintf(result, "%lld", num - 1); // convert num - 1 to string
    return result;      
}
