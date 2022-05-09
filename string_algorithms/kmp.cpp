#include <iostream>
#include <string>
#include <vector>

using namespace std;

vector<int> createShifts(string &pattern) {
    int n = pattern.length();

    vector<int> lps(n, 0);

    // first one
    lps[0] = 0;
    int len = 0;

    int i=1;

    while (i < n) {
        if (pattern[i] == pattern[len]) {
            len++;
            lps[i] = len;
            ++i;
        } else {
            if (len != 0) {
                len = lps[len-1];
            } else {
                ++i;
            }
        }
    }

    return lps;
}

bool isMatch(string &src, string &pattern) {
    auto shifts = createShifts(pattern);

    // for (int i = 0; i < pattern.length(); ++i) {
    //     cout << shifts[i] << " ";
    // }
    // cout << endl;

    int  i = 0, j = 0;

    while (i < src.length()) {
        if (src[i] == pattern[j]) {
            ++i;
            ++j;
        } else {
            if (j!= 0) {
                j = shifts[j-1];
            } else {
                ++i;
            }
        }

        if (j == pattern.length()) {
            return true;
            j = shifts[j-1];
        }
    }
    return false;
}

int main() {
    string src = "ASCSSJABABCFVABABACHGYYFGH";
    string pattern = "ABABCFVABABAC";

    cout << isMatch(src, pattern) << endl;
    return 0;
}