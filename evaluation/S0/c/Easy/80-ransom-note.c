// Source: https://leetcode.com/problems/ransom-note/   |   Difficulty: Easy
//
// Problem Description:
// Given two strings ransomNote and magazine, return true if ransomNote can be constructed by using the letters from magazine and false otherwise.
//
// Each letter in magazine can only be used once in ransomNote.
//
// Example:
// Input: ransomNote = "a", magazine = "b"
// Output: false
//
// Constraints:
// 1 <= ransomNote.length, magazine.length <= 105
// 	ransomNote and magazine consist of lowercase English letters.
//

bool canConstruct(char* ransomNote, char* magazine) {
    int count[26] = {0};
    
    for (int i = 0; magazine[i] != '\0'; i++) {
        count[magazine[i] - 'a']++;
    }
    
    for (int i = 0; ransomNote[i] != '\0'; i++) {
        count[ransomNote[i] - 'a']--;
        if (count[ransomNote[i] - 'a'] < 0) {
            return false;
        }
    }
    
    return true;        
}
