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



char * defangIPaddr(char * address){
    char *defanged = malloc(4 * strlen(address) + 1);
    char *p = defanged;
    while (*address) {
        if (*address == '.') {
            *p++ = '[';
            *p++ = '.';
            *p++ = ']';
        } else {
            *p++ = *address;
        }
        address++;
    }
    *p = '\0';
    return defanged;
}
