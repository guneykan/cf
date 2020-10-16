#include <algorithm>
#include <chrono>
#include <cmath>
#include <iostream>
#include <map>
#include <numeric>
#include <set>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

// useful type alises
using ll = int64_t;
using vi = vector<int>;
using vl = vector<long>;
using vii = vector<vector<int>>;
using vll = vector<vector<long>>;

// useful abbreviations
#define REP(i, N) for (size_t i = 0; i < (N); i++)
#define PB push_back
#define MP make_pair
#define umap unordered_map
#define uset unordered_set

// logger
template<typename T> std::ostream &operator<<(std::ostream &os, const std::vector<T> &vt) {
    if (vt.empty())
        return os;
    for (size_t i = 0; i + 1 < vt.size(); i++) {
        os << vt[i] << " ";
    }
    os << vt.back();
    return os;
}
template<typename T> std::ostream &operator<<(std::ostream &os, const std::vector<vector<T>> &vt) {
    if (vt.empty())
        return os;
    for (size_t i = 0; i < vt.size(); i++) {
        print(vt[i]);
    }
    return os;
}
template<typename T> void print(const T &v) {
    cout << v << endl;
}
template<typename T> void prints(const T &v) {
    cout << v;
}
template<typename T> void debug(const T &v) {
#ifndef LOCAL_M
    return;
#endif
    print(v);
}
template<typename T> void debugs(const T &v) {
#ifndef LOCAL_M
    return;
#endif
    prints(v);
}

// timer - measures its lifetime in ms
struct Timer {
    std::chrono::system_clock::time_point start;
    Timer() {
        start = std::chrono::system_clock::now();
    }

    ~Timer() {
        auto now = std::chrono::system_clock::now();
        std::chrono::system_clock::duration duration = now - start;
        auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(duration);
        std::string str;
        str = str + "Runtime: " + std::to_string(ms.count()) + " ms";
        debug(str);
    }
};

// mod helpers
const ll __P = 1e9 + 7;
ll mod(ll x, ll y = __P) {
    ll ans = x % y;
    if (ans < 0)
        ans += y;
    return ans;
}
// To compute x^y under modulo m
ll power(ll x, ll y, ll m = __P) {
    if (y == 0)
        return 1;
    ll p = power(x, y / 2, m) % m;
    p = (p * p) % m;

    return (y % 2 == 0) ? p : (x * p) % m;
}
// To compute 1/x under modulo m
ll inv_mod(ll x, ll m = __P) {
    ll g = gcd(x, m);
    if (g != 1) {
        throw "Inverse doesn't exist";
        return g;
    } else {
        // If a and m are relatively prime, then modulo inverse
        // is a^(m-2) mode m
        ll ans = power(x, m - 2, m);
        return ans;
    }
}

// mod P based long integer
template<ll P = __P> struct mdll {
    ll num;
    mdll(ll x) {
        num = mod(x, P);
    }
    mdll<P> operator+(ll x) {
        return {mod(num + mod(x, P), P)};
    }
    mdll<P> operator*(ll x) {
        return {mod(num * mod(x, P), P)};
    }
    mdll<P> operator-(ll x) {
        return {mod(num - mod(x, P), P)};
    }
    mdll<P> operator/(ll x) {
        return {mod(num * inv_mod(x, P), P)};
    }
    mdll<P> operator^(ll x) {
        return {power(num, mod(x, P), P)};
    }
    mdll<P> operator+(mdll<P> x) {
        return {mod(num + mod(x.num, P), P)};
    }
    mdll<P> operator*(mdll<P> x) {
        return {mod(num * mod(x.num, P), P)};
    }
    mdll<P> operator-(mdll<P> x) {
        return {mod(num - mod(x.num, P), P)};
    }
    mdll<P> operator/(mdll<P> x) {
        return {mod(num * inv_mod(x.num, P), P)};
    }
    mdll<P> operator^(mdll<P> x) {
        return {power(num, mod(x.num, P), P)};
    }
};

template<ll T> std::ostream &operator<<(std::ostream &os, const mdll<T> &md) {
    os << md.num;
    return os;
}

template<typename T> struct seg_tree {
    int N;
    vector<T> _d;
    seg_tree(const vector<T> &arr) {
        N = arr.size();
        _d = vector<T>(4 * N);
        build(1, 0, N - 1, arr);
    }

    void build(int vid, int l, int r, const vector<T> &arr) {
        if (l == r) {
            _d[vid] = arr[l];
            return;
        }
        int mid = (l + r) / 2;
        build(2 * vid, l, mid, arr);
        build(2 * vid + 1, mid + 1, r, arr);
        _d[vid] = _d[2 * vid] + _d[2 * vid + 1];
    }

    T query(int vid, int tl, int tr, int l, int r) {
        if (l > r)
            return 0;
        if (tl == l && tr == r) {
            return _d[vid];
        }
        int mid = (tl + tr) / 2;
        return query(vid * 2, tl, mid, l, min(r, mid)) + query(vid * 2 + 1, mid + 1, tr, max(l, mid + 1), r);
    }

    T query(int l, int r) {
        return query(1, 0, N - 1, l, r);
    }
};

void solve();
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
#ifdef LOCAL_M
    freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);
#endif
    int t = 1;
    // cin >> t;
    Timer timer;
    while (t--) {
        solve();
    }
}

vector<bool> visited;
void dfs(const vector<vector<int>> &adjList, int node) {
    if (visited[node])
        return;
    visited[node] = true;
    for (int i = 0; i < adjList[node].size(); i++) {
        if (visited[adjList[node][i]])
            continue;
        dfs(adjList, adjList[node][i]);
    }
}

void solve() {
    mdll x = 5;
    x = 720;
    print(x);
}

// check before submit
// testcase size
// integer overflow
// mod base
// remove debug code
