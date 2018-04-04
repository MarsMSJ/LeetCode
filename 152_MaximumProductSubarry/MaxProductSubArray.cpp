#include <iostream>
#include <vector>
#include <stdlib.h>

int GetMaxProduct( std::vector<int> nums ){
    if(nums.size() == 0 ) { return 0; }
    if(nums.size() == 1) { return nums[0]; }
    //Skip the first iteration
    bool first = true;
    //Declare for loop
    int maxProd, maxProdReturn, minProd;
    //Initalize variables pre-loop
    maxProd = maxProdReturn = minProd = nums[0];
	
	for( auto& num : nums ) {
		if(first) {
            first = false;
            continue;
		}

		if( num < 0 ){
			std::swap(maxProd, minProd);
		}

		maxProd = std::max( num, (maxProd *= num ));
		minProd = std::min( num, (minProd *= num ));
		maxProdReturn = (maxProdReturn > maxProd) ? maxProdReturn : maxProd;
	}
	return maxProdReturn;
}
int main( int argc, char *argv[] ) {
	std::vector<int> V = { 2, 3, -2, 4 };
	std::cout << "MaxProduct: " << GetMaxProduct( V );
	std::cout << std::endl;
	
	return 0;
}
