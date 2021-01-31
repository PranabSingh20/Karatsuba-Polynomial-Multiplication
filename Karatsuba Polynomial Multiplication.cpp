//Author : Pranab Singh
//Date : 31-01-2021 23:00
#include <bits/stdc++.h>
using namespace std;
typedef int64_t i64;
typedef long long ll;
typedef long double ld;
typedef unsigned long long Ull;

#define endl "\n"
#define all(v) v.begin(), v.end()
#define rall(v) v.rbegin(), v.rend()
#define pb push_back
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

vector<ll> karatsuba_multiply(vector<ll> &v1, vector<ll> &v2) {
	if (v1.size() == 1 && v2.size() == 1) {
		vector<ll> base;
		base.pb(v1[0] * v2[0]);
		return base;
	}
	vector<ll> first_half_a, second_half_a, first_half_b, second_half_b;
	for (int i = 0; i < v1.size() / 2; i++) {
		first_half_a.pb(v1[i]);
		second_half_a.pb(v1[i + v1.size() / 2]);
		first_half_b.pb(v2[i]);
		second_half_b.pb(v2[i + v1.size() / 2]);
	}
	vector<ll> D0D1, E0E1;
	for (int i = 0; i < v1.size() / 2; i++) {
		D0D1.pb(first_half_a[i] + second_half_a[i]);
		E0E1.pb(first_half_b[i] + second_half_b[i]);
	}
	vector<ll> D1E1 = karatsuba_multiply(first_half_a, first_half_b);
	vector<ll> D0E0 = karatsuba_multiply(second_half_a, second_half_b);
	vector<ll> D0D1_E0E1 = karatsuba_multiply(D0D1, E0E1);
	for (int i = 0; i < D0D1_E0E1.size(); i++) {
		D0D1_E0E1[i] -= D1E1[i], D0D1_E0E1[i] -= D0E0[i];
	}
	vector<ll> cur_ans(2 * v1.size() - 1, 0);
	for (int i = 0; i < D0E0.size(); i++) {
		if (i < D1E1.size()) {
			cur_ans[i + v1.size()] += D1E1[i];
		}
		if (i < D0D1_E0E1.size()) {
			cur_ans[i + (v1.size() / 2)] += D0D1_E0E1[i];
		}
		cur_ans[i] += D0E0[i];
	}
	return cur_ans;
}

vector<ll> brute_multiply(vector<ll> &v1, vector<ll> &v2) {
	int n = v1.size(), m = v2.size();
	vector<ll> ans(n + m - 1, 0);
	vector<ll> a = v1, b = v2;
	reverse(all(a)), reverse(all(b));
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			ans[i + j] += a[i] * b[j];
		}
	}
	return ans;
}

void solve() {
	cout << fixed << setprecision(5) << endl;
	vector<ll> a, b;
	int n = 3;							// size of both polynomials
	for (int i = 0; i < n; i++) {
		ll x = rng() % 10;
		a.pb(x);
	}
	for (int i = 0; i < n; i++) {
		ll x = rng() % 10;
		b.pb(x);
	}
	cout << "1st polynomial is\n";
	for (int i = 0; i < n; i++) {
		cout << a[i] << "x^" << n - i - 1 << " ";
	}
	cout << endl;
	cout << "2nd polynomial is\n";
	for (int i = 0; i < n; i++) {
		cout << b[i] << "x^" << n - i - 1 << " ";
	}
	cout << endl << endl;
	reverse(all(a)), reverse(all(b));
	while (true) {
		if (__builtin_popcount((int)a.size()) == 1)break;
		a.pb(0), b.pb(0);
	}
	reverse(all(a)), reverse(all(b));
	bool f = 0;
	vector<ll> brute_ans = brute_multiply(a, b);
	cout << "Polynomial multiplication using brute force\n";
	for (int i = brute_ans.size() - 1; i >= 0; i--) {
		if (brute_ans[i])
			f = 1;
		if (f)
			cout << brute_ans[i] << "x^" << i << " ";
	}
	cout << endl << endl;
	vector<ll> karatsuba = karatsuba_multiply(a, b);
	f = 0;
	cout << "Polynomial multiplication using karatsuba\n";
	for (int i = a.size() + b.size() - 2; i >= 0; i--) {
		if (karatsuba[i])
			f = 1;
		if (f)
			cout << karatsuba[i] << "x^" << i << " ";
	}
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif
	int t = 1;
	while (t--)
	{
		solve();
	}
}
