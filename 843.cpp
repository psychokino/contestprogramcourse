
#include <iostream>
#include <bits/stdc++.h>

using namespace std;

long long int row_size, column_size, eat_times ;
long long int remain;
map<long long int,long long int>::iterator it;

template<class T>
bool yummy( map<T,T>& chocolate,T& x ,T& y , T& ate) { // false for QAQ , true for eat
	ate = 0;
	it = chocolate.lower_bound(x);// find the key first greater than x
	T last_x ;

	T origin_y = (it != chocolate.end() ) ? it->second : 0;

	if (y > origin_y) {  // 會多吃
		chocolate[x] = max(y , chocolate[x] ); //確定多吃 插入這一點
		chocolate[0] = 0;//補0
		it = chocolate.find(x); //start from x
		it--;
		if ( it != chocolate.end()) { // if lower of x exist
			T now_x = x;
			last_x = it->first; // lower bound x
			do {
				ate += (now_x - last_x)*(y - origin_y);

				if (y >= it->second) {
					origin_y = it->second; // lower y
					now_x = last_x;
					chocolate.erase(it--);
					last_x = it != chocolate.end() ? it->first : 0 ;
				}
				else break;
				

			} while (it != chocolate.end());
		}
		else ate += x * (y - origin_y); // lowerbound not exist	
		remain -= ate;
		return true;
	}
	else
		return false;
}
/*
void not_eat(map<int, int>& chocolate) {
	auto it = chocolate.begin();
	
	int last_x = 0;

	for (; it != chocolate.end(); it++) {
		remain += (it->first - last_x) * (column_size - it->second);
		last_x = it->first;

	}
	cout << remain << endl;
}*/

int main()
{
	map<long long int,long long int> chocolate;
	
	cin >> row_size;
	cin >> column_size;
	cin >> eat_times;
	
	remain = row_size * column_size;
	
	long long int x, y , ate = 0;
	while (eat_times--) {
		//cin >> x >> y;
		scanf_s("%lld %lld", &x, &y);
		if (x > row_size) while (1) { ; };
		if(y > column_size)while (1) { ; };
		if ( yummy( chocolate , x , y , ate ) ) {
			//cout << ate << endl;
			printf("%lld\n", ate);
		}
		else printf("QAQ\n");//cout << "QAQ" << endl;
	} 
	//not_eat(chocolate);
	cout << remain << endl;
}

