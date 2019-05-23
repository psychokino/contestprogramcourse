#pragma warning(disable:4996)
#include <bits/stdc++.h>
using namespace std;

int main()
{
	int n, q;
	cin >> n >> q;
	int l,r;
	vector<int> arr;
	int buf;
	while (n--) {
		scanf("%d", &buf);
		arr.push_back(buf);
	}
	vector<int> temp_arr;

	temp_arr.assign(arr.size() , 0);
	temp_arr[0] = arr[0];
	for (int i = 1; i < arr.size(); i++) {
		temp_arr[i] = temp_arr[i - 1] ^ arr[i];
	}
	int output;
	
	while (q--) {
		scanf("%d %d", &l,&r);
		if (l - 1 > 0)
			output = temp_arr[r-1] ^ temp_arr[l - 2];
		else
			output = temp_arr[r-1];
		printf("%d\n", output);

		
		
		
	
	}
	
}


