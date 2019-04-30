
#include <iostream>
#include <bits/stdc++.h>
using namespace std;
int main()
{
	int n, k;
	int buf;
	vector<int> permuted;
	cin >> n;
	cin >> k;
	while (n--) {
		cin >> buf;
		permuted.push_back(buf);
	}

	bool greater_than;
	
	
	vector<int> copy;
	copy = permuted;
	if (!next_permutation(copy.begin(), copy.end())) {
		cout << "hello world!" << endl;
		return 0;
	}
	do
	{
		greater_than = next_permutation(permuted.begin(), permuted.end());
		for (int i = 0; i < permuted.size(); i++) {
			if (!greater_than) {
				break;
			}
			printf("%d ", permuted.at(i));
		}
		printf("\n");
	} while (greater_than && --k );
	
}
