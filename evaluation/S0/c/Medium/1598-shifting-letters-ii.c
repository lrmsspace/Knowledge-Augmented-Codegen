// Source: https://leetcode.com/problems/shifting-letters-ii/   |   Difficulty: Medium
//
// Problem Description:
// You are given a string s of lowercase English letters and a 2D integer array shifts where shifts[i] = [starti, endi, directioni]. For every i, shift the characters in s from the index starti to the index endi (inclusive) forward if directioni = 1, or shift the characters backward if directioni = 0.
//
// Shifting a character forward means replacing it with the next letter in the alphabet (wrapping around so that 'z' becomes 'a'). Similarly, shifting a character backward means replacing it with the previous letter in the alphabet (wrapping around so that 'a' becomes 'z').
//
// Return the final string after all such shifts to s are applied.
//
// Example:
// Input: s = "abc", shifts = [[0,1,0],[1,2,1],[0,2,1]]
// Output: "ace"
// Explanation: Firstly, shift the characters from index 0 to index 1 backward. Now s = "zac".
// Secondly, shift the characters from index 1 to index 2 forward. Now s = "zbd".
// Finally, shift the characters from index 0 to index 2 forward. Now s = "ace".
//
// Constraints:
// 1 <= s.length, shifts.length <= 5 * 104
// 	shifts[i].length == 3
// 	0 <= starti <= endi < s.length
// 	0 <= directioni <= 1
// 	s consists of lowercase English letters.
//

char* shiftingLetters(char* s, int** shifts, int shiftsSize, int* shiftsColSize) {
    int n = strlen(s);
    int* diff = (int*)calloc(n + 1, sizeof(int));

    for (int i = 0; i < shiftsSize; i++) {
        int start = shifts[i][0];
        int end = shifts[i][1];
        int direction = shifts[i][2] == 1 ? 1 : -1;

        diff[start] += direction;
        diff[end + 1] -= direction;
    }

    int cumulativeShift = 0;
    for (int i = 0; i < n; i++) {
        cumulativeShift += diff[i];
        int originalPos = s[i] - 'a';
        int newPos = (originalPos + cumulativeShift) % 26;
        if (newPos < 0) newPos += 26;
        s[i] = 'a' + newPos;
    }

    free(diff);
    return s;       
}
