// Source: https://leetcode.com/problems/reconstruct-original-digits-from-english/   |   Difficulty: Medium
//
// Problem Description:
// Given a string s containing an out-of-order English representation of digits 0-9, return the digits in ascending order.
//
// Example:
// Input: s = "owoztneoer"
// Output: "012"
//
// Constraints:
// 1 <= s.length <= 105
// 	s[i] is one of the characters ["e","g","f","i","h","o","n","s","r","u","t","w","v","x","z"].
// 	s is guaranteed to be valid.
//

char* originalDigits(char* s) {
    int count[10] = {0};
    int letter_count[26] = {0};
    for (char* p = s; *p; p++) {
        letter_count[*p - 'a']++;
    }

    // Identify digits with unique letters
    count[0] = letter_count['z' - 'a']; // zero
    count[2] = letter_count['w' - 'a']; // two
    count[4] = letter_count['u' - 'a']; // four
    count[6] = letter_count['x' - 'a']; // six
    count[8] = letter_count['g' - 'a']; // eight

    // Identify remaining digits
    count[3] = letter_count['h' - 'a'] - count[8]; // three
    count[5] = letter_count['f' - 'a'] - count[4]; // five
    count[7] = letter_count['s' - 'a'] - count[6]; // seven
    count[1] = letter_count['o' - 'a'] - count[0] - count[2] - count[4]; // one
    count[9] = letter_count['i' - 'a'] - count[5] - count[6] - count[8]; // nine

    // Construct the result string
    char* result = (char*)malloc(strlen(s) + 1);
    char* p = result;
    for (int i = 0; i <= 9; i++) {
        for (int j = 0; j < count[i]; j++) {
            *p++ = '0' + i;
        }
    }
    *p = '\0';
    return result;      
}
