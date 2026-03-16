// Source: https://leetcode.com/problems/assign-cookies/   |   Difficulty: Easy
//
// Problem Description:
// Assume you are an awesome parent and want to give your children some cookies. But, you should give each child at most one cookie.
//
// Each child i has a greed factor g[i], which is the minimum size of a cookie that the child will be content with; and each cookie j has a size s[j]. If s[j] >= g[i], we can assign the cookie j to the child i, and the child i will be content. Your goal is to maximize the number of your content children and output the maximum number.
//
// Example:
// Input: g = [1,2,3], s = [1,1]
// Output: 1
// Explanation: You have 3 children and 2 cookies. The greed factors of 3 children are 1, 2, 3. 
// And even though you have 2 cookies, since their size is both 1, you could only make the child whose greed factor is 1 content.
// You need to output 1.
//
// Constraints:
// 1 <= g.length <= 3 * 104
// 	0 <= s.length <= 3 * 104
// 	1 <= g[i], s[j] <= 231 - 1
//
//
//  
// Note: This question is the same as  2410: Maximum Matching of Players With Trainers.
//

int findContentChildren(int* g, int gSize, int* s, int sSize) {
    // Sort greed factors and cookie sizes
    qsort(g, gSize, sizeof(int), (int (*)(const void*, const void*))strcmp);
    qsort(s, sSize, sizeof(int), (int (*)(const void*, const void*))strcmp);

    int child = 0;  // Index for children
    int cookie = 0; // Index for cookies

    // Iterate through both arrays
    while (child < gSize && cookie < sSize) {
        if (s[cookie] >= g[child]) {
            // Cookie can satisfy the child
            child++;
        }
        // Move to the next cookie
        cookie++;
    }

    return child; // Number of content children     
}
