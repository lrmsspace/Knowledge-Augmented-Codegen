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

class Solution {
public:
    int longestCommonSubpath(int n, vector<vector<int>>& paths) {
        const int MOD1 = 1e9 + 7;
        const int MOD2 = 1e9 + 9;
        const int BASE1 = 100007;
        const int BASE2 = 100009;

        int left = 0, right = 0;
        for (const auto& path : paths) {
            right = max(right, (int)path.size());
        }

        int result = 0;

        while (left <= right) {
            int mid = left + (right - left) / 2;

            unordered_set<long long> commonHashes;
            bool firstPath = true;

            for (const auto& path : paths) {
                unordered_set<long long> currentHashes;
                long long hash1 = 0, hash2 = 0;
                long long power1 = 1, power2 = 1;

                for (int i = 0; i < mid; ++i) {
                    hash1 = (hash1 * BASE1 + path[i]) % MOD1;
                    hash2 = (hash2 * BASE2 + path[i]) % MOD2;
                    if (i < mid - 1) {
                        power1 = (power1 * BASE1) % MOD1;
                        power2 = (power2 * BASE2) % MOD2;
                    }
                }
                currentHashes.insert((hash1 << 32) | hash2);

                for (int i = mid; i < path.size(); ++i) {
                    hash1 = (hash1 - path[i - mid] * power1 % MOD1 + MOD1) % MOD1;
                    hash1 = (hash1 * BASE1 + path[i]) % MOD1;

                    hash2 = (hash2 - path[i - mid] * power2 % MOD2 + MOD2) % MOD2;
                    hash2 = (hash2 * BASE2 + path[i]) % MOD2;

                    currentHashes.insert((hash1 << 32) | hash2);
                }

                if (firstPath) {
                    commonHashes = currentHashes;
                    firstPath = false;
                } else {
                    unordered_set<long long> temp;
                    for (const auto& h : commonHashes) {
                        if (currentHashes.count(h)) {
                            temp.insert(h);
                        }
                    }
                    commonHashes = move(temp);
                }

                if (commonHashes.empty()) {
                    break;
                }
                
            }

            if (!commonHashes.empty()) {
                result = mid;
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }

        return result;
    }
};
