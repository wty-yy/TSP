#include <bits/stdc++.h>
using namespace std;
const int N = 100 + 10;
struct City{
    double x, y;
    City(){}
}C[N];
struct Node{
    int x, y;
    double d;
    Node(){}
    Node(int a, int b, double c) {x = a, y = b, d = c;}
    friend bool operator < (Node a, Node b) {return a.d > b.d;}
};
double dis(int i, int j) {return sqrt((C[i].x - C[j].x)*(C[i].x - C[j].x)+(C[i].y - C[j].y)*(C[i].y - C[j].y));}
int n, in[N], out[N];
double ans;
bool vis[N][N], fg[N];
priority_queue<Node> q;
int nt[N];
vector<double> xx[N], yy[N];
void print(int i, int x) {
    if (fg[i] || !i) return;
    fg[i] = 1;
    cout << i << "->";
    xx[x].push_back(C[i].x);
    yy[x].push_back(C[i].y);
    print(nt[i], x);
}
signed main() {
    freopen("in1.in", "r", stdin);
    freopen("out.out", "w", stdout);
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> n;
    for (int i = 1; i <= n; i++) {
        int id;
        cin >> id >> C[i].x >> C[i].y;
        in[i] = out[i] = n - 1;
    }
    for (int i = 1; i <= n; i++)
    for (int j = 1; j <= n; j++) if (i != j)
        q.push(Node(i, j, dis(i, j)));
    while (!q.empty()) {
        Node t = q.top(); q.pop();
        vis[t.x][t.y] = 1;
        if (!in[t.x] || !out[t.y]) continue;
        if (--in[t.x] == 0 || --out[t.y] == 0) {
            in[t.x] = out[t.y] = 0;
            nt[t.x] = t.y;
            //cout << t.x << "->" << t.y << endl;
            //ans += dis(t.x, t.y);
            ans += t.d;
            for (int i = 1; i <= n; i++) {
                if (i != t.x && in[i] && out[t.x] && vis[i][t.x]) {q.push(Node(i, t.x, dis(i, t.x))); vis[i][t.x] = 0;}
                if (i != t.y && in[t.y] && out[i] && vis[t.y][i]) {q.push(Node(t.y, i, dis(t.y, i))); vis[t.y][i] = 0;}
            }
        }
    }
    int cnt = 0;
    for (int i = 1; i <= n; i++) if (!fg[i]) print(i, ++cnt), cout << endl;;
    cout << endl;
    cout << cnt << endl;
    for (int j = 1; j <= cnt; j++) {
        //cout << "Circle:" << j << endl;
        cout << xx[j].size() + 1 << endl;
        for (auto i : xx[j]) cout << i << " ";
        cout << xx[j][0];
        cout << endl;
        for (auto i : yy[j]) cout << i << " ";
        cout << yy[j][0];
        cout << endl;
    }
    cout << ans << endl;
    //system("pause");
    return 0;
}