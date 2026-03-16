// Source: https://leetcode.com/problems/next-greater-numerically-balanced-number/   |   Difficulty: Medium
//
// Problem Description:
// An integer x is numerically balanced if for every digit d in the number x, there are exactly d occurrences of that digit in x.
//
// Given an integer n, return the smallest numerically balanced number strictly greater than n.
//
// Example:
// Input: n = 1
// Output: 22
// Explanation: 
// 22 is numerically balanced since:
// - The digit 2 occurs 2 times. 
// It is also the smallest numerically balanced number strictly greater than 1.
//
// Constraints:
// 0 <= n <= 106
//

int nextBeautifulNumber(int n) {
    int balanced_numbers[] = {
        0, 1, 22, 122, 212, 221, 333, 1333, 3133, 3313,
        3333, 4444, 14444, 22333, 23233, 23323, 23332,
        32233, 32323, 32332, 33223, 33232, 33322,
        44444, 155555, 225555, 252555, 255255, 255525,
        255552, 315555, 351555, 355155, 355515, 355551,
        513555, 531555, 535155, 535515, 535551,
        551355, 553155, 553315, 553351, 553513,
        553531, 555133, 555313, 555331, 555511,
        555515, 555551, 666666
    };
    
    int size = sizeof(balanced_numbers) / sizeof(balanced_numbers[0]);
    for (int i = 0; i < size; i++) {
        if (balanced_numbers[i] > n) {
            return balanced_numbers[i];
        }
    }
    
    return -1; // This line should never be reached given the problem constraints.      
}
