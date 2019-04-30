

#include <iostream>

#include <algorithm>
#include <vector>
#include <limits>
#define INT_1E7 10000000
using namespace std;



/*
universe = l l+1 l+2 l+3 .... r
subset = sequence ... length 10e6
find the minimum not in the subset

bool array .... record least least+1 ... least+1e6

U > S
U = S
U < S

*/



int main() {
	int testcase;
	cin >> testcase;

	int sequence_length;
	
	vector<bool> record_input;
	record_input.assign(INT_1E7, 0);// 0 ~ 9,999,999

	long long int least, upper, temp, exclude;
	for (int case_number = 0; case_number < testcase; case_number++) {

		 
		cin >> sequence_length;
		cin >> least;
		cin >> upper;
		
		
		
		
		for (int i = 0; i < sequence_length ; i++)
			record_input.at(i) = record_input.at(i) & 0x0;

		for (int index = 0; index < sequence_length; index++) {
			cin >> temp;
			if ((temp >= least) && (temp < (least + INT_1E7 ) && temp <= upper ) ) {
				temp -= least;
				record_input.at(temp) = true;
			}
			
		}

		int limit = static_cast<int>( min( static_cast<long long int>(sequence_length) ,  upper - least + 1 ) ) ;  // only store the value from L to L + sequence size
		
		bool is_all_subset_meet_the_universe = true ; 

		for (int i = 0; i < limit  ; i++) {  // U > S
			if ( !record_input.at(i) ) {
				cout << i + least << endl;
				is_all_subset_meet_the_universe = false ;  //exist a number such that not meet
				break;
			}
		}

		// U <= S
		if (is_all_subset_meet_the_universe ){ 
				
			if(upper >= least + limit) 
				cout << least + limit  << endl; 
			else 
				cout << "^v^" << endl;

			continue;
		}
			
		
		
	


	}


	return 0;
}



