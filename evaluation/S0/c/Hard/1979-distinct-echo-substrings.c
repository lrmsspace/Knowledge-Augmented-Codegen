// Source: https://leetcode.com/problems/distinct-echo-substrings/   |   Difficulty: Hard
//
// Problem Description:
// Return the number of distinct non-empty substrings of text that can be written as the concatenation of some string with itself (i.e. it can be written as a + a where a is some string).
//
// Example:
// Input: text = "abcabcabc"
// Output: 3
// Explanation: The 3 substrings are "abcabc", "bcabca" and "cabcab".
//
// Constraints:
// 1 <= text.length <= 2000
// 	text has only lowercase English letters.
//

int distinctEchoSubstrings(char* text) {
    int n = strlen(text);
    int mod = 1000000007;
    int base = 31;

    /* Precompute prefix hashes and powers of base */
    long long *prefix_hash = (long long*)calloc(n + 1, sizeof(long long));
    long long *p_power = (long long*)calloc(n + 1, sizeof(long long));
    p_power[0] = 1;
    for (int i = 0; i < n; ++i) {
        prefix_hash[i + 1] = (prefix_hash[i] * base + (text[i] - 'a' + 1)) % mod;
        p_power[i + 1] = (p_power[i] * base) % mod;
    }

    int result = 0;
    for (int length = 1; length <= n / 2; ++length) {
        int seen_size = mod; /* size of hash set */
        char *seen = (char*)calloc(seen_size, sizeof(char));
        for (int start = 0; start + 2 * length <= n; ++start) {
            /* Compute hash of substring text[start:start+length] */
            long long hash1 = (prefix_hash[start + length] - (prefix_hash[start] * p_power[length]) % mod + mod) % mod;
            /* Compute hash of substring text[start+length:start+2*length] */
            long long hash2 = (prefix_hash[start + 2 * length] - (prefix_hash[start + length] * p_power[length]) % mod + mod) % mod;
            if (hash1 == hash2) {
                /* Combine the two hashes to form a unique key */
                long long combined_hash = (hash1 * base + hash2) % mod;
                if (!seen[combined_hash % seen_size]) {
                    seen[combined_hash % seen_size] = 1;
                    result++;
                }
            }
        }
        free(seen);
    }

    free(prefix_hash);
    free(p_power);
    return result;      
}
