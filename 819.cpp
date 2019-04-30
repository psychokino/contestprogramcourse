#include <iostream>
#include <sstream>
#include <string>
#include <algorithm>
#include <cstddef>
using namespace std;

string big_integer_adder(string sum ,string add){
	bool sign_add,sign_sum,sign_tempx;
	bool borrow = false, carry = false ;
	string temp;
	
	int diff_of_bit,size_int;
	/*if(add[0]=='-'){
		sign_add= true ;
		add.erase(add.begin());
	}
	else sign_add = false ;
	if(sum[0]=='-'){
		sign_sum= true ;
		sum.erase(sum.begin());
	}
	else sign_sum = false;*/
	sign_add=false;
	sign_sum=false;
	size_int = max(add.size(),sum.size());
	if(size_int == add.size()){
		temp = sum ;
		diff_of_bit = add.size()-sum.size();
		sum.assign(diff_of_bit,'0');
		sum = sum + temp ;
		
	}
	else{
		temp = add ;
		diff_of_bit = sum.size()-add.size();
		add.assign(diff_of_bit,'0');
		add = add + temp ;
		
	}
	if(sum.compare(add) < 0 ){ /// if sum < buf
		
		sign_tempx = sign_add ;
		sign_add = sign_sum;
		sign_sum = sign_tempx;
		temp = add;
		add = sum;
		sum = temp;
		
		
	}
	
	
	for(int i=sum.size()-1;i>=-1;i--){
		switch(sign_add ^ sign_sum){
			case false :	
							if(i == -1){
								if(carry){
									temp = sum;
									sum.clear();
									
									sum.push_back('1');
									sum += temp ;
								}
								if(sign_add && sign_sum){
									temp = sum;
									sum.clear();
									sum.push_back('-');
									sum += temp;
								}
								
								
							
							}
							else if( (sum[i]-48)+ (add[i]-48) + carry > 9 ){

								sum[i] = sum[i] + add[i] - 48 -10 + carry;
								carry = true;						
								
							}
							else{
								sum[i] = sum[i] + add[i] - 48 + carry;
								carry = false ;
							}
							break;
			case true :		
							if(i == -1 ){
								
								if(sign_sum){
									
									temp = sum ;
									sum.clear();
									sum.push_back('-');
									sum += temp ;
									sign_sum = false ;
								}
								break;
								
								
							}
							else if( (sum[i]-48) - (add[i]-48) - borrow  < 0 ){
								 sum[i] = sum[i] - add[i] + 48 + 10 - borrow ;
								 borrow = true ;
							}
							else{
								 sum[i] = sum[i] - add[i] + 48 - borrow ;
								 borrow = false;
							 }
		}
		
	}
	return sum;
	
}

int main(){
	string sum,buf,read_line;
	bool sign_sum;
	
	
	while(getline(cin,read_line)){
		sum = "0";
		sign_sum = false;
		stringstream ss(read_line);
		while(ss>>buf){
			sum = big_integer_adder(sum,buf);
			
		}
		
		
		size_t delete_zero ; 
		
		if(sum[0]=='-'){
			delete_zero = sum.find_first_not_of("0",1);
			sum.erase(sum.begin()+1,sum.begin()+delete_zero);
		}
		else{
			delete_zero = sum.find_first_not_of("0");
			sum.erase(sum.begin(),sum.begin()+delete_zero);
		}
		
		//cout<<"delete z : "<<delete_zero<<endl;
		if(delete_zero == sum.npos){
			sum.clear();
			sum = "0";
		}
		
		
		
		
		cout<<sum<<endl;
		sum.clear();
		
	}
}