#pragma warning(disable:4996)
#include <bits/stdc++.h>
using namespace std;

tuple<int, int, int> extended_gcd(int a, int b)
{
	if (a == 0)
		return make_tuple(b, 0, 1);

	int gcd, x, y;

	// unpack tuple  returned by function into variables
	tie(gcd, x, y) = extended_gcd(b % a, a);

	return make_tuple(gcd, (y - (b / a) * x), x);
}


int main()
{
	int testcase;
	scanf("%d", &testcase);
	int a, prime;
	while (testcase--) {
		scanf("%d",&a);
		scanf("%d", &prime);

		tuple<int, int, int> t = extended_gcd(a, prime);
		int gcd = get<0>(t);
		int x = get<1>(t);
		int y = get<2>(t);
		if (x < 0) x += prime;
		printf("%d\n", x);/*
		cout << "GCD is " << gcd << endl;
		cout << "x = " << x << " y = " << y << endl;

		cout << a << "*" << x << " + " << prime << "*" << y << " = " << gcd;*/

		

	}

}

