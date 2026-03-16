// Source: https://leetcode.com/problems/count-the-repetitions/   |   Difficulty: Hard
//
// Problem Description:
// We define str = [s, n] as the string str which consists of the string s concatenated n times.
//
//
// 	For example, str == ["abc", 3] =="abcabcabc".
//
//
// We define that string s1 can be obtained from string s2 if we can remove some characters from s2 such that it becomes s1.
//
//
// 	For example, s1 = "abc" can be obtained from s2 = "abdbec" based on our definition by removing the bolded underlined characters.
//
//
// You are given two strings s1 and s2 and two integers n1 and n2. You have the two strings str1 = [s1, n1] and str2 = [s2, n2].
//
// Return the maximum integer m such that str = [str2, m] can be obtained from str1.
//
// Example:
// Input: s1 = "acb", n1 = 4, s2 = "ab", n2 = 2
// Output: 2
//
// Constraints:
// 1 <= s1.length, s2.length <= 100
// 	s1 and s2 consist of lowercase English letters.
// 	1 <= n1, n2 <= 106
//

/**
 * @param {string} s1
 * @param {number} n1
 * @param {string} s2
 * @param {number} n2
 * @return {number}
 */
var getMaxRepetitions = function(s1, n1, s2, n2) {
    const m = s1.length, n = s2.length;
    const indexMap = new Map();
    let count1 = 0, count2 = 0, index2 = 0;
    while (count1 < n1) {
        for (let i = 0; i < m; i++) {
            if (s1[i] === s2[index2]) {
                index2++;
                if (index2 === n) {
                    index2 = 0;
                    count2++;
                }
            }
        }
        count1++;
        if (indexMap.has(index2)) {
            const [prevCount1, prevCount2] = indexMap.get(index2);
            const cycleLength = count1 - prevCount1;
            const cycleCount2 = count2 - prevCount2;
            const remainingCycles = Math.floor((n1 - count1) / cycleLength);
            count1 += remainingCycles * cycleLength;
            count2 += remainingCycles * cycleCount2;
        } else {
            indexMap.set(index2, [count1, count2]);
        }
    }
    return Math.floor(count2 / n2); 
};
