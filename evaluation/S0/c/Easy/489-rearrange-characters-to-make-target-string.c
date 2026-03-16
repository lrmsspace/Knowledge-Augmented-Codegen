// Source: https://leetcode.com/problems/rearrange-characters-to-make-target-string/   |   Difficulty: Easy
//
// Problem Description:
// You are given two 0-indexed strings s and target. You can take some letters from s and rearrange them to form new strings.
//
// Return the maximum number of copies of target that can be formed by taking letters from s and rearranging them.
//
// Example:
// Input: s = "ilovecodingonleetcode", target = "code"
// Output: 2
// Explanation:
// For the first copy of "code", take the letters at indices 4, 5, 6, and 7.
// For the second copy of "code", take the letters at indices 17, 18, 19, and 20.
// The strings that are formed are "ecod" and "code" which can both be rearranged into "code".
// We can make at most two copies of "code", so we return 2.
//
// Constraints:
// 1 <= s.length <= 100
// 	1 <= target.length <= 10
// 	s and target consist of lowercase English letters.
//
//
//  
// Note: This question is the same as  1189: Maximum Number of Balloons.
//

int rearrangeCharacters(char* s, char* target) {
    int s_count[26] = {0};
    int target_count[26] = {0};
    
    for (int i = 0; s[i] != '\0'; i++) {
        s_count[s[i] - 'a']++;
    }
    
    for (int i = 0; target[i] != '\0'; i++) {
        target_count[target[i] - 'a']++;
    }
    
    int max_copies = INT_MAX;
    
    for (int i = 0; i < 26; i++) {
        if (target_count[i] > 0) {
            int possible_copies = s_count[i] / target_count[i];
            if (possible_copies < max_copies) {
                max_copies = possible_copies;
            }
        }
    }
    
    return max_copies;      
}
