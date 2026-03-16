// Source: https://leetcode.com/problems/check-distances-between-same-letters/   |   Difficulty: Easy
//
// Problem Description:
// You are given a 0-indexed string s consisting of only lowercase English letters, where each letter in s appears exactly twice. You are also given a 0-indexed integer array distance of length 26.
//
// Each letter in the alphabet is numbered from 0 to 25 (i.e. 'a' -> 0, 'b' -> 1, 'c' -> 2, ... , 'z' -> 25).
//
// In a well-spaced string, the number of letters between the two occurrences of the ith letter is distance[i]. If the ith letter does not appear in s, then distance[i] can be ignored.
//
// Return true if s is a well-spaced string, otherwise return false.
//
// Example:
// Input: s = "abaccb", distance = [1,3,0,5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0]
// Output: true
// Explanation:
// - 'a' appears at indices 0 and 2 so it satisfies distance[0] = 1.
// - 'b' appears at indices 1 and 5 so it satisfies distance[1] = 3.
// - 'c' appears at indices 3 and 4 so it satisfies distance[2] = 0.
// Note that distance[3] = 5, but since 'd' does not appear in s, it can be ignored.
// Return true because s is a well-spaced string.
//
// Constraints:
// 2 <= s.length <= 52
// 	s consists only of lowercase English letters.
// 	Each letter appears in s exactly twice.
// 	distance.length == 26
// 	0 <= distance[i] <= 50
//

bool checkDistances(char* s, int* distance, int distanceSize) {
    int firstIndex[26];
    for (int i = 0; i < 26; i++) {
        firstIndex[i] = -1;
    }

    for (int i = 0; s[i] != '\0'; i++) {
        int charIndex = s[i] - 'a';
        if (firstIndex[charIndex] == -1) {
            firstIndex[charIndex] = i;
        } else {
            int expectedDistance = distance[charIndex];
            int actualDistance = i - firstIndex[charIndex] - 1;
            if (expectedDistance != actualDistance) {
                return false;
            }
        }
    }

    return true;        
}
