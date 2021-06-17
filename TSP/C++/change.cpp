#include <bits/stdc++.h>
using namespace std;
const int N = 1000;
double xx[N], yy[N];
int main() {
    freopen("48points.in", "r", stdin);
    freopen("city_48.in", "w", stdout);
    int n; cin >> n; cout << n << endl;
    for (int i = 1; i <= n; i++) {
        int id; cin >> id;
        cin >> xx[i] >> yy[i];
    }
    for (int i = 1; i <= n; i++) cout << i << " ";
    cout << endl;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            cout << sqrt((xx[i]-xx[j])*(xx[i]-xx[j])+(yy[i]-yy[j])*(yy[i]-yy[j])) << " ";
        }
        cout << endl;
    }
}