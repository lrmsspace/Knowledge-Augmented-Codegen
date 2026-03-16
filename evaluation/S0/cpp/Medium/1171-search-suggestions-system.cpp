// Source: https://leetcode.com/problems/search-suggestions-system/   |   Difficulty: Medium
//
// Problem Description:
// You are given an array of strings products and a string searchWord.
//
// Design a system that suggests at most three product names from products after each character of searchWord is typed. Suggested products should have common prefix with searchWord. If there are more than three products with a common prefix return the three lexicographically minimums products.
//
// Return a list of lists of the suggested products after each character of searchWord is typed.
//
// Example:
// Input: products = ["mobile","mouse","moneypot","monitor","mousepad"], searchWord = "mouse"
// Output: [["mobile","moneypot","monitor"],["mobile","moneypot","monitor"],["mouse","mousepad"],["mouse","mousepad"],["mouse","mousepad"]]
// Explanation: products sorted lexicographically = ["mobile","moneypot","monitor","mouse","mousepad"].
// After typing m and mo all products match and we show user ["mobile","moneypot","monitor"].
// After typing mou, mous and mouse the system suggests ["mouse","mousepad"].
//
// Constraints:
// 1 <= products.length <= 1000
// 	1 <= products[i].length <= 3000
// 	1 <= sum(products[i].length) <= 2 * 104
// 	All the strings of products are unique.
// 	products[i] consists of lowercase English letters.
// 	1 <= searchWord.length <= 1000
// 	searchWord consists of lowercase English letters.
//

class Solution {
public:
    vector<vector<string>> suggestedProducts(vector<string>& products, string searchWord) {
        sort(products.begin(), products.end());
        vector<vector<string>> result;
        string prefix;
        for (char c : searchWord) {
            prefix += c;
            vector<string> suggestions;
            for (const string& product : products) {
                if (product.compare(0, prefix.size(), prefix) == 0) {
                    suggestions.push_back(product);
                    if (suggestions.size() == 3) {
                        break;
                    }
                }
            }
            result.push_back(suggestions);
        }
        return result;          
    }
};
