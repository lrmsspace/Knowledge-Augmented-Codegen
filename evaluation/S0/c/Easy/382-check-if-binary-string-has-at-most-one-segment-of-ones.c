// Source: https://leetcode.com/problems/check-if-binary-string-has-at-most-one-segment-of-ones/   |   Difficulty: Easy
//
// Problem Description:
// Given a binary string s ​​​​​without leading zeros, return true​​​ if s contains at most one contiguous segment of ones. Otherwise, return false.
//
// Example:
// Input: s = "1001"
// Output: false
// Explanation: The ones do not form a contiguous segment.
//
// Constraints:
// 1 <= s.length <= 100
// 	s[i]​​​​ is either '0' or '1'.
// 	s[0] is '1'.
//

bool checkOnesSegment(char* s) {
    int i = 0;
    int len = strlen(s);
    int one_segment_found = 0;

    while (i < len) {
        if (s[i] == '1') {
            if (one_segment_found) {
                return false; // More than one segment of ones found
            }
            one_segment_found = 1;
            while (i < len && s[i] == '1') {
                i++; // Skip the entire segment of ones
            }
        } else {
            i++; // Move to the next character
        }
    }

    return true; // At most one segment of ones found       
}
