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

class Solution {
public:
    int getMaxRepetitions(string s1, int n1, string s2, int n2) {
        int s1Len = s1.length();
        int s2Len = s2.length();
        
        vector<int> indexr(s2Len + 1, 0);
        vector<int> countr(s2Len + 1, 0);
        
        int index = 0;  // current index in s2
        int count = 0;  // number of times s2 is found
        
        for (int i = 0; i < n1; i++) {
            for (int j = 0; j < s1Len; j++) {
                if (s1[j] == s2[index]) {
                    index++;
                    if (index == s2Len) {
                        index = 0;
                        count++;
                    }
                }
            }
            indexr[i] = index;
            countr[i] = count;
            
            // Check for cycles
            for (int k = 0; k < i; k++) {
                if (indexr[k] == index) {
                    int preCount = countr[k];
                    int patternCount = (countr[i] - countr[k]) * ((n1 - 1 - k) / (i - k));
                    int remainCount = countr[k + (n1 - 1 - k) % (i - k)] - countr[k];
                    return (preCount + patternCount + remainCount) / n2;
                }
            }
        }
        
        return countr[n1 - 1] / n2;         
    }
};
