// Source: https://leetcode.com/problems/multiply-strings/   |   Difficulty: Medium
//
// Problem Description:
// Given two non-negative integers num1 and num2 represented as strings, return the product of num1 and num2, also represented as a string.
//
// Note: You must not use any built-in BigInteger library or convert the inputs to integer directly.
//
// Example:
// Input: num1 = "2", num2 = "3"
// Output: "6"
//
// Constraints:
// 1 <= num1.length, num2.length <= 200
// 	num1 and num2 consist of digits only.
// 	Both num1 and num2 do not contain any leading zero, except the number 0 itself.
//

class Solution {
public:
    string multiply(string num1, string num2) {
        if (num1 == "0" || num2 == "0") return "0";

        int n = num1.size();
        int m = num2.size();
        vector<int> result(n + m, 0);

        for (int i = n - 1; i >= 0; --i) {
            for (int j = m - 1; j >= 0; --j) {
                int mul = (num1[i] - '0') * (num2[j] - '0');
                int sum = mul + result[i + j + 1];

                result[i + j + 1] = sum % 10;
                result[i + j] += sum / 10;
            }
        }

        string product;
        for (int num : result) {
            if (!(product.empty() && num == 0)) {
                product.push_back(num + '0');
            }
        }

        return product.empty() ? "0" : product;         
    }
};
