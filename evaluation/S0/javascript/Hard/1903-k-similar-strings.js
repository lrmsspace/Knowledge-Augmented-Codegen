// Source: https://leetcode.com/problems/k-similar-strings/   |   Difficulty: Hard
//
// Problem Description:
// Strings s1 and s2 are k-similar (for some non-negative integer k) if we can swap the positions of two letters in s1 exactly k times so that the resulting string equals s2.
//
// Given two anagrams s1 and s2, return the smallest k for which s1 and s2 are k-similar.
//
// Example:
// Input: s1 = "ab", s2 = "ba"
// Output: 1
// Explanation: The two string are 1-similar because we can use one swap to change s1 to s2: "ab" --> "ba".
//
// Constraints:
// 1 <= s1.length <= 20
// 	s2.length == s1.length
// 	s1 and s2 contain only lowercase letters from the set {'a', 'b', 'c', 'd', 'e', 'f'}.
// 	s2 is an anagram of s1.
//

/**
 * @param {string} s1
 * @param {string} s2
 * @return {number}
 */
var kSimilarity = function(s1, s2) {
    const queue = [];
    const visited = new Set();
    queue.push(s1);
    visited.add(s1);
    let swaps = 0;

    while (queue.length > 0) {
        const size = queue.length;
        for (let i = 0; i < size; i++) {
            const current = queue.shift();
            if (current === s2) {
                return swaps;
            }
            let j = 0;
            while (current[j] === s2[j]) {
                j++;
            }
            for (let k = j + 1; k < current.length; k++) {
                if (current[k] === s2[j] && current[k] !== s2[k]) {
                    const next = swap(current, j, k);
                    if (!visited.has(next)) {
                        visited.add(next);
                        queue.push(next);
                    }
                }
            }
        }
        swaps++;
    }

    function swap(str, i, j) {
        const arr = str.split('');
        const temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
        return arr.join('');
    }


        
};
