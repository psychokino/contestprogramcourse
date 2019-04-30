#include<iostream>
#include<sstream>
#include<string>
#include <math.h>
#include <algorithm>
#include <iomanip>
using namespace std;
/*****
unsigned long long int : 0 ~ 2^64  = 0 ~ 1e19
not overflow when multiplicate : 9.9999 * 1e8 = 999 999 999
so a int store : 0 ~ 9.99 * 1e8
at most 9 digits per int
200 / 9  = 22.22
23 unsigned long long int needed 


*****/

const unsigned long long int e10 = 1000000000 ;

template<size_t T ,class X ,class Y>
void Clear_Array(X (&num)[T],Y (&used)[T]){
	for(int i=0 ; i<T ; i++){
		num[i] = 0;
		used[i] = 0;
	}
}


template<size_t T>
void Put_Integer_Into_Array(unsigned long long int (&num)[T] ,string input ,bool (&num_used)[T] ){
	
	string buf;
	int i=0;
	
	string::reverse_iterator rit = input.rbegin();
	
	int size = 0;
	//cout<<"check intput size : "<<input.size()<<endl;
	//cout<<"chech input "<<input<<endl;
	while(rit != input.rend() ){
		buf.clear();
		for(int i=0; (i<9) && (rit != input.rend() ) ;i++){
			buf.insert(buf.begin(),rit,rit+1);
			rit++;
		}
		
		stringstream cast_to_int(buf);
		cast_to_int>>num[size];
		num_used[size] = true ;
		size++;
		//cout<<"size of sumused : "<<size<<endl;
	}
	
}

template<size_t T>
void Long_Array_Multiplication(unsigned long long int (&sum)[T] ,unsigned long long int (&mul)[T] ,bool (&sum_used)[T] ,bool (&add_used)[T]){
	unsigned long long int partial_product[T]= {} ;
	if(mul[0]==0){
		bool zero = true;
		for(int i=T-1;i>0;i--)
			if(add_used[i])zero = false ;
		if(zero){
			for(int i=0 ; i<T-1;i++){
				sum[i]=0;
				sum_used[i] = 0;
			}
			sum_used[0] = true ;
		}
	}
	else
	{ 	for(int i = 0 ; (add_used[i] == true) && (i < T) ; i++){
			for(int j = 0 ; (sum_used[j] == true) && (j < T) ; j++){
				//cout<<"product : "<<mul[i] * sum[j]<<"   partial : "<<partial_product[i+j]<<endl;
				partial_product[i+j] = mul[i] * sum[j] + partial_product[i+j];
				
				/*if( (!sum_used[i+j]) && partial_product[i+j]!=0 )sum_used[i+j] = true ;
				if(partial_product[i+j] >= e10 ){
					
					unsigned long long int temp;
					temp = partial_product[i+j] ;
					temp = temp / e10;
					partial_product[i+j+1] = temp + partial_product[i+j+1];
					partial_product[i+j] = partial_product[i+j] % e10 ;
				}*/
				//cout<<"partial : "<<partial_product[i+1+j]<<endl;
			}
		}
		
		unsigned long long int temp2,temp ;
		for(int i=0 ; i<T ; i++){
			//cout<<"product "<<i<<"  = "<<partial_product[i]<<endl;
			if(partial_product[i] >= e10 ){
				sum_used[i+1]=true ;
				temp = partial_product[i] / e10 ;
				if(temp >= e10){
					temp2 = temp / e10;
					partial_product[i+2] += temp2;
					sum_used[i+2]=true;
				}
				temp %= e10;
				partial_product[i+1]  = partial_product[i+1] + temp ;
				partial_product[i] %= e10 ;
				
			}
		}
		int correct = 0;
		for(int i=T-1 ;i>=0 ; i--){
			sum[i] = partial_product[i] ;
			if( i > correct && partial_product[i]!=0)correct = i;
		}
		
		for(int i=0 ; i <= correct;i++){
			sum_used[i] = true ;
		}
	}
	
}


template<size_t T>
void Long_Array_Addition(unsigned long long int (&sum)[T] ,unsigned long long int (&add)[T] ,bool (&sum_used)[T] ,bool (&add_used)[T]){
	bool carry_bit[T] = {false} ;
	for(int i=0 ; i<T;i++){
		if( sum[i] || add[i] ){
			sum_used[i] = true ;
		}
	}
	for(int i=0; (i < T) && (sum_used[i]) ; i++){
		sum[i] = sum[i] + add[i] + carry_bit[i];
		if(sum[i]>= e10 ){
			carry_bit[i+1] =true;
			sum[i] -= e10 ;
			sum_used[i+1]=true;
		}
	}
	
	
}

template<size_t T>
void output_process_leadingzero(unsigned long long int (&sum)[T],bool(&sum_used)[T]){
	int max_byte=0;
	for(int i = T-1 ; i>=0 ; i--){
			//cout<<"sum : "<<i<<" = "<<sum_used[i]<<endl;
			if(sum_used[i]){
				if(i >= max_byte){
					max_byte = i;
					cout<<sum[i];
				}
				if( i < max_byte){
					cout<<setfill('0')<<setw(9)<<sum[i];	
				}
			}
	}
	cout<<endl;
}



int main(){
	
	
	unsigned long long int sum[24] = {};
	unsigned long long int added[24] = {};
	bool sum_used[24] = { false } ;
	bool add_used[24] = { false };
	sum_used[0] = true ;
	add_used[0] = true ;
	
	string buf;
	string num;
	size_t found_plus , found_mul;
	
	while(getline(cin,buf)){
		//cout<<buf<<endl;
		if(buf.empty())buf = "0";
		num.clear();
		
		found_plus = buf.find_first_of("+");
		found_mul  = buf.find_first_of("*");		
		unsigned long long int temp_int = min(found_mul,found_plus);		
		
		
		
		if(temp_int == string::npos)num.assign(buf.begin(),buf.end());
		else num.assign(buf.begin(),buf.begin()+temp_int);		

		
		Put_Integer_Into_Array(sum,num,sum_used);		

		
		if(temp_int == string::npos)buf.erase(buf.begin(),buf.end());
		else buf.erase(buf.begin(),buf.begin()+temp_int);	
		
		//output_process_leadingzero(sum,sum_used);
		size_t cursor = 0;
		
		while(true){
			num.clear();
			found_plus = buf.find_first_not_of("0123456789",cursor + 1);
			found_mul = buf.find_first_not_of("0123456789",cursor + 1);
			temp_int = min(found_mul,found_plus);
			
			if(buf[cursor]=='+'){
				
				
				//cout<<"start find next = end ? "<<(temp_int==string::npos)<<" cur "<<(cursor)<<" next_cur "<<temp_int<<" minus "<<temp_int-cursor<<endl;
				//cout<<"cursor size  "<<(temp_int==string::npos?buf.size()-cursor:temp_int - cursor )<<endl ;
				if(temp_int == string::npos)num.assign(buf.begin()+cursor+1,buf.end());
				else num.assign(buf.begin()+cursor+1,buf.begin()+temp_int);
				
				//cout<<"err0"<<endl;
				Put_Integer_Into_Array(added,num,add_used);
				
				//cout<<"err1"<<endl;
				Long_Array_Addition(sum,added,sum_used,add_used);
				
				//cout<<"err2"<<endl;
				
				
				//cout<<"now cursor point "<<buf[cursor]<<" cursor = "<<cursor<<endl;;
			}
			else if(buf[cursor]=='*'){

				
				if(temp_int == string::npos)num.assign(buf.begin()+cursor+1,buf.end());
				else num.assign(buf.begin()+cursor+1,buf.begin()+temp_int);
				
				Put_Integer_Into_Array(added,num,add_used);
				Long_Array_Multiplication(sum,added,sum_used,add_used);
				

			}
			else{
				break;
			}
			
			if(temp_int == string::npos) cursor = buf.size();
			else cursor = temp_int	;
			Clear_Array(added,add_used);
			
			
		}
		
		output_process_leadingzero(sum,sum_used);
		
		for(int i = 24 ; i>=0 ; i--){
			sum[i] = 0;
			added[i] = 0;
			sum_used[i] = false ;
			add_used[i] = false ;
		}
		
	}
	return 0;
}