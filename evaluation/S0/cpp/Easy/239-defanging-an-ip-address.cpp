// Source: https://leetcode.com/problems/defanging-an-ip-address/   |   Difficulty: Easy
//
// Problem Description:
// Given a valid (IPv4) IP address, return a defanged version of that IP address.
//
// A defanged IP address replaces every period "." with "[.]".
//
// Example:
// Input: address = "1.1.1.1"
// Output: "1[.]1[.]1[.]1"
//
// Constraints:
// The given address is a valid IPv4 address.
//

class Solution {
public:
    string defangIPaddr(string address) {
        string defanged;
        for (char c : address) {
            if (c == '.') {
                defanged += "[.]";
            } else {
                defanged += c;
            }
        }
        return defanged;            
    }
};
