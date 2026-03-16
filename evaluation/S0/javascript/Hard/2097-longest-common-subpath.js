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

/**
 * @param {number} n
 * @param {number[][]} paths
 * @return {number}
 */
var longestCommonSubpath = function(n, paths) {
    const base = 131;
    const mod = 1e9 + 7;
    const getHash = (path, length) => {
        let hash = 0;
        for (let i = 0; i < length; i++) {
            hash = (hash * base + path[i]) % mod;
        }
        const hashes = new Set([hash]);
        let power = 1;  
        for (let i = length; i < path.length; i++) {
            hash = (hash * base - path[i - length] * power % mod + mod) % mod;
            hash = (hash + path[i]) % mod;
            hashes.add(hash);
            power = (power * base) % mod;
        }
        return hashes;
    }
    let left = 1, right = Math.min(...paths.map(p => p.length)), result = 0;

    while (left <= right) {
        const mid = Math.floor((left + right) / 2);
        let commonHashes = getHash(paths[0], mid);
        for (let i = 1; i < paths.length; i++) {
            const currentHashes = getHash(paths[i], mid);
            commonHashes = new Set([...commonHashes].filter(x => currentHashes.has(x)));
            if (commonHashes.size === 0) {
                break;
            }
        }
        if (commonHashes.size > 0) {
            result = mid;
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return result;
};
