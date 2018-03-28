#include <iostream>
#include <vector>
#include "Trie.hpp"
#include <string>

int main(){
	std::vector<std::string> Words( {"pop", "app"} );	
	Trie::Trie trie;
	trie.Insert(Words);	
	std::cout << "Completed Words insert\n";
	std::string prefix = "app";
	std::string suffix = "app";
	Trie::Node* node;
  	if( trie.ContainsPrefix( prefix , node) ){
  		std::cout << "Found prefix: " << prefix << std::endl;
  	}
  	if( trie.ContainsSuffix( suffix, node ) ){
  		std::cout << "Found suffix: " << suffix << std::endl;
  	}
	std::cout << "Computing F function: \n";
	auto result = trie.GetWeight( prefix, suffix );

	std::cout << "Highest weight with prefix and suffix: " << result << std::endl;
	return 0;
}


