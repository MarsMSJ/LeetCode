#include <iostream>
#include <vector>

using std::vector;

vector<int> SumVector;

void InitSumVector(const vector<int>& nums) {
	int runningSum = 0;
	SumVector.clear();
	for( auto& num : nums ) {
		runningSum += num;
		SumVector.push_back( runningSum );
	}
}

int GetRangeSumQuery(size_t i, size_t j, vector<int>& nums){
	if( i >= nums.size() ){
		return 0;
	}
	if( j >= nums.size() ){
		return 0;
	}
	if( i > j ) {
		return 0;
	}
	//Optimization 
	if( i == j ) { return nums[i]; }
	if( SumVector.size() != nums.size() ){
		InitSumVector( nums );
	}

	int sum = 0;
	while( i <= j ){
		sum += nums[i++];
	}
	return sum;
}

int main() {

	return 0;
}
