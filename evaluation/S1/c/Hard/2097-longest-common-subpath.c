// Source: https://leetcode.com/problems/longest-common-subpath/   |   Difficulty: Hard
//
// Problem Description:
// There is a country of n cities numbered from 0 to n - 1. In this country, there is a road connecting every pair of cities.
//
// There are m friends numbered from 0 to m - 1 who are traveling through the country. Each one of them will take a path consisting of some cities. Each path is represented by an integer array that contains the visited cities in order. The path may contain a city more than once, but the same city will not be listed consecutively.
//
// Given an integer n and a 2D integer array paths where paths[i] is an integer array representing the path of the ith friend, return the length of the longest common subpath that is shared by every friend's path, or 0 if there is no common subpath at all.
//
// A subpath of a path is a contiguous sequence of cities within that path.
//
// Example:
// Input: n = 5, paths = [[0,1,2,3,4],
//                        [2,3,4],
//                        [4,0,1,2,3]]
// Output: 2
// Explanation: The longest common subpath is [2,3].
//
// Constraints:
// 1 <= n <= 105
// 	m == paths.length
// 	2 <= m <= 105
// 	sum(paths[i].length) <= 105
// 	0 <= paths[i][j] < n
// 	The same city is not listed multiple times consecutively in paths[i].
//
// Helpful references (internal KB):
// - Substring Search (string, number, hashing, randomized, rolling-hash)
//   • When to use: Use when efficiently finding occurrences of a pattern string within a larger text string, especially for average-case fast string matching. It is suitable for scenarios involving large texts or multiple patterns.
//   • Idea: The Rabin-Karp algorithm finds pattern occurrences in a text by comparing hash values of the pattern and text substrings. It uses a rolling hash function for O(1) substring hash updates, achieving O(N+M) average time complexity and O(NM) worst-case.
//   • Invariants: The pattern's hash value patHash remains constant throughout the search.; At each step i, txtHash accurately represents the hash of txt[i...i+m-1].
//   • Tips: Choose a large prime modulus to minimize hash collisions.; Use a random base for polynomial hashing to enhance collision resistance.
//   • Pitfalls: Hash collisions can lead to false positives, increasing worst-case time.; Improper choice of prime modulus or base can degrade performance.
// - Flows with demands (graph, binary-search-answer)
//   • When to use: Use when a problem involves finding a flow in a network where edges have both lower and upper capacity bounds, or nodes have supply/demand requirements, and an optimal value needs to be found.
//   • Idea: This technique transforms a network with lower and upper capacity bounds on edges (or node demands) into a standard max-flow problem. It often involves adding a new source and sink to handle demands, and then binary searching on the answer if an optimal value is sought, typically with O(MaxFlow * log(Range)) complexity.
//   • Invariants: The total flow out of the super source equals the total demand that needs to be satisfied.; For any node, the sum of incoming flow minus outgoing flow equals its net demand (0 for internal nodes in a circulation).
//   • Tips: Convert lower bounds to demands by adjusting capacities and adding a super source/sink.; A feasible flow exists if the max flow in the transformed network equals the total demand.
//   • Pitfalls: Incorrectly calculating residual capacities after demand satisfaction.; Forgetting to add a super source/sink for handling demands.
// - String Hashing (string, array, hashing, enumeration)
//   • When to use: Use string hashing to efficiently compare substrings or patterns within a larger text, or to quickly check for duplicate strings. It's ideal for problems requiring fast equality checks on string segments.
//   • Idea: String hashing converts a string or substring into a numerical hash value, allowing for O(1) comparison of substrings after O(N) precomputation. It typically uses polynomial hashing with a prime base and modulus to minimize collisions.
//   • Invariants: The hash value for the prefix S[0...i] is correctly computed and stored, based on the chosen polynomial hashing scheme.; The base 'p' and modulus 'm' remain constant throughout the hash computation for consistent results.
//   • Tips: Choose a large prime number for the base 'p' (e.g., 31, 53) to reduce collisions.; Select a large prime number for the modulus 'm' (e.g., 10^9+7, 10^9+9) to further minimize collision probability.
//   • Pitfalls: Avoid using 2^64 as a modulus, as specific collision-generating strings exist for this choice.; A small modulus 'm' or base 'p' drastically increases the likelihood of hash collisions.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

int longestCommonSubpath(int n, int** paths, int pathsSize, int* pathsColSize) {
    if (pathsSize == 0) return 0;
    
    int minLen = INT_MAX;
    for (int i = 0; i < pathsSize; i++) {
        if (pathsColSize[i] < minLen) {
            minLen = pathsColSize[i];
        }
    }
    
    // Binary search on the answer
    int left = 1, right = minLen;
    int result = 0;
    
    const long long MOD = 1e9 + 7;
    const long long BASE = 31;
    
    while (left <= right) {
        int mid = (left + right) / 2;
        
        // Check if a common subpath of length mid exists
        // Compute hash of all subpaths of length mid in the first path
        int* path0 = paths[0];
        int path0Len = pathsColSize[0];
        
        // Use set to store hashes from first path
        // Since we need to use C standard library, we'll use a different approach
        // Store all hashes and check if they appear in all other paths
        
        long long* hashes = (long long*)malloc((path0Len - mid + 1) * sizeof(long long));
        
        long long hash = 0;
        long long basePow = 1;
        for (int i = 0; i < mid; i++) {
            hash = (hash * BASE + path0[i]) % MOD;
            if (i < mid - 1) basePow = (basePow * BASE) % MOD;
        }
        
        hashes[0] = hash;
        int hashCount = 1;
        
        // Rolling hash for remaining subpaths in first path
        for (int i = mid; i < path0Len; i++) {
            hash = (hash - (long long)path0[i - mid] * basePow % MOD + MOD) % MOD;
            hash = (hash * BASE + path0[i]) % MOD;
            hashes[hashCount++] = hash;
        }
        
        // Check if any of these hashes appear in all other paths
        int found = 1;
        
        for (int p = 1; p < pathsSize && found; p++) {
            int* curPath = paths[p];
            int curLen = pathsColSize[p];
            
            if (curLen < mid) {
                found = 0;
                break;
            }
            
            // Compute hashes for current path
            int* curHashes = (int*)malloc((curLen - mid + 1) * sizeof(int));
            
            long long curHash = 0;
            for (int i = 0; i < mid; i++) {
                curHash = (curHash * BASE + curPath[i]) % MOD;
            }
            curHashes[0] = curHash;
            int curHashCount = 1;
            
            // Rolling hash for remaining subpaths
            for (int i = mid; i < curLen; i++) {
                curHash = (curHash - (long long)curPath[i - mid] * basePow % MOD + MOD) % MOD;
                curHash = (curHash * BASE + curPath[i]) % MOD;
                curHashes[curHashCount++] = curHash;
            }
            
            // Check if any hash from first path appears in current path
            int pathFound = 0;
            for (int i = 0; i < hashCount; i++) {
                for (int j = 0; j < curHashCount; j++) {
                    if (hashes[i] == curHashes[j]) {
                        pathFound = 1;
                        break;
                    }
                }
                if (pathFound) break;
            }
            
            free(curHashes);
            if (!pathFound) found = 0;
        }
        
        free(hashes);
        
        if (found) {
            result = mid;
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    
    return result;
}