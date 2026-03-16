// Source: https://leetcode.com/problems/longest-happy-string/   |   Difficulty: Medium
//
// Problem Description:
// A string s is called happy if it satisfies the following conditions:
//
//
// 	s only contains the letters 'a', 'b', and 'c'.
// 	s does not contain any of "aaa", "bbb", or "ccc" as a substring.
// 	s contains at most a occurrences of the letter 'a'.
// 	s contains at most b occurrences of the letter 'b'.
// 	s contains at most c occurrences of the letter 'c'.
//
//
// Given three integers a, b, and c, return the longest possible happy string. If there are multiple longest happy strings, return any of them. If there is no such string, return the empty string "".
//
// A substring is a contiguous sequence of characters within a string.
//
// Example:
// Input: a = 1, b = 1, c = 7
// Output: "ccaccbcc"
// Explanation: "ccbccacc" would also be a correct answer.
//
// Constraints:
// 0 <= a, b, c <= 100
// 	a + b + c > 0
//

class Solution {
public:
    string longestDiverseString(int a, int b, int c) {
        string result;
        priority_queue<pair<int, char>> maxHeap;
        if (a > 0) maxHeap.push({a, 'a'});
        if (b > 0) maxHeap.push({b, 'b'});
        if (c > 0) maxHeap.push({c, 'c'});

        while (!maxHeap.empty()) {
            auto [count1, char1] = maxHeap.top();
            maxHeap.pop();

            int len = result.size();
            if (len >= 2 && result[len - 1] == char1 && result[len - 2] == char1) {
                if (maxHeap.empty()) break; // No other character to use

                auto [count2, char2] = maxHeap.top();
                maxHeap.pop();

                result += char2;
                count2--;
                if (count2 > 0) {
                    maxHeap.push({count2, char2});
                }
                maxHeap.push({count1, char1}); // Push back the first character
            } else {
                result += char1;
                count1--;
                if (count1 > 0) {
                    maxHeap.push({count1, char1});
                }
            }
        }

        return result;          
    }
};
