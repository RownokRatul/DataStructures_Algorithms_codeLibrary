#include <iostream>
#include <vector>
#include <string>
using namespace std;

vector<int> prefix_function(string s) {
    vector<int> pi;
    int len = s.size();
    pi.resize(len);
    pi[0] = 0;
    for(int i=1; i < len; i++) {
        int prev_best_suffix = pi[i-1];
        while((prev_best_suffix > 0) && (s[i] != s[prev_best_suffix])) {
            prev_best_suffix = pi[prev_best_suffix - 1];
        }
        pi[i] = (s[i] == s[prev_best_suffix]) ? (prev_best_suffix + 1) : prev_best_suffix;
    }
    return pi;
}

int main() {
    string s;
    cin >> s;
    vector<int> prefix = prefix_function(s);
    for(int each : prefix) {
        cout << each << " ";
    }
    cout << "\n";
    return 0;
}