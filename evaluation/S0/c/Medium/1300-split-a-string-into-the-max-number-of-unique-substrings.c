// Source: https://leetcode.com/problems/split-a-string-into-the-max-number-of-unique-substrings/   |   Difficulty: Medium
//
// Problem Description:
// Given a string s, return the maximum number of unique substrings that the given string can be split into.
//
// You can split string s into any list of non-empty substrings, where the concatenation of the substrings forms the original string. However, you must split the substrings such that all of them are unique.
//
// A substring is a contiguous sequence of characters within a string.
//
// Example:
// Input: s = "ababccc"
// Output: 5
// Explanation: One way to split maximally is ['a', 'b', 'ab', 'c', 'cc']. Splitting like ['a', 'b', 'a', 'b', 'c', 'cc'] is not valid as you have 'a' and 'b' multiple times.
//
// Constraints:
// 1 <= s.length <= 16
// 	
// 	
// 	s contains only lower case English letters.
//

int maxUniqueSplit(char* s) {
    int maxCount = 0;
    int len = strlen(s);

    void backtrack(int start, int count, int used[26][26]) {
        if (start == len) {
            if (count > maxCount) {
                maxCount = count;
            }
            return;
        }

        for (int end = start; end < len; end++) {
            int index1 = s[start] - 'a';
            int index2 = s[end] - 'a';
            if (!used[index1][index2]) {
                used[index1][index2] = 1;
                backtrack(end + 1, count + 1, used);
                used[index1][index2] = 0;
            }
        }
    }

    int used[26][26] = {0};
    backtrack(0, 0, used);
    return maxCount;        
}
