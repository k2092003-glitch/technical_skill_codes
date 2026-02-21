
#include <bits/stdc++.h>
using namespace std;

int N;
int cost[20][20];
int dp[1 << 20];

int solve(int mask) {
    int worker = __builtin_popcount(mask);

    if (worker == N)
        return 0;

    if (dp[mask] != -1)
        return dp[mask];

    int ans = INT_MAX;

    for (int task = 0; task < N; task++) {
        if (!(mask & (1 << task))) {
            ans = min(ans,
                      cost[worker][task] +
                      solve(mask | (1 << task)));
        }
    }

    return dp[mask] = ans;
}

int main() {
    N = 3;
    int temp[3][3] = {
        {9,2,7},
        {6,4,3},
        {5,8,1}
    };

    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            cost[i][j] = temp[i][j];

    memset(dp, -1, sizeof(dp));

    cout << solve(0) << "\n";
}
