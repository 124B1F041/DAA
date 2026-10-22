
#include <iostream>
using namespace std;

int main() {
    int n, W;

    cout << "Enter number of items: ";
    cin >> n;

    int weight[100], value[100];

    cout << "Enter weight and utility of each item:\n";
    for (int i = 1; i <= n; i++) {
        cin >> weight[i] >> value[i];
    }

    cout << "Enter truck capacity: ";
    cin >> W;

    int dp[101][1001] = {0};

    for (int i = 1; i <= n; i++) {
        for (int w = 0; w <= W; w++) {
            if (weight[i] <= w) {
                dp[i][w] = max(dp[i - 1][w],
                    value[i] + dp[i - 1][w - weight[i]]);
            } else {
                dp[i][w] = dp[i - 1][w];
            }
        }
    }

    cout << "\nMaximum utility: " << dp[n][W] << endl;

    cout << "Selected items: ";
    int w = W;

    for (int i = n; i >= 1; i--) {
        if (dp[i][w] != dp[i - 1][w]) {
            cout << i << " ";
            w -= weight[i];
        }
    }

    cout << endl;
    return 0;
}
