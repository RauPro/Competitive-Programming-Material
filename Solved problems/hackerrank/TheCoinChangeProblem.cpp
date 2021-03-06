// tags: DP
#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for(int i = a; i <= b; ++i)
typedef long long int ll;
int n, m;
int coins[50];
ll memo[251][50];
// ways(k, i) = number of ways we can
//   generate the amount of money 'k'
//   using coin types i, i+1, ..., m-1
ll ways(int k, int i) {
    if (k == 0) return 1; // base case: no money -> 1 way (use 0 coins)
    if (i == m) return 0; // base case: invalid coin type -> impossible
    ll& ans = memo[k][i];
    if (ans != -1) return ans; // already solved
    // general case
    ll tmp = 0;
    // option 1: use i-th coin type (if possible)
    if (coins[i] <= k) tmp += ways(k - coins[i], i);
    // option 2: don't use i-th coin type
    tmp += ways(k, i+1);
    return ans = tmp;
}
int main() {
    cin >> n >> m;
    rep(i,0,m-1) cin >> coins[i];
    memset(memo, -1, sizeof memo);
    cout << ways(n,0) << '\n';
    return 0;
}