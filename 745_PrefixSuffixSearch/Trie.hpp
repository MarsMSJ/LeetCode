#ifndef _TRIE_HPP
#define _TRIE_HPP

#include <iostream>
#include <vector>
#include <string>

namespace Trie {

	using Word = std::string;
	using WordVector = std::vector<std::string>;

	class Node{
		char _C;
		std::vector<int> _WeightVector;
		std::vector<Node> _NodeVector;

	public:
		Node( char c ) : _C(c){
		}

		const char & GetChar(){
			return _C;
		}

		const auto& GetWeightVector(){
			return _WeightVector;
		}

		Node& Connect( char&& c, int&& weight ){
			Node* nodePtr = nullptr;
			if ( IsConnected( c, nodePtr ) ){
				nodePtr->AddWeight( weight );
			}
			else {
				_NodeVector.emplace_back( c );
				_NodeVector.back().AddWeight( weight );
				nodePtr = &_NodeVector.back();
			}
			return *nodePtr;
		}	

		bool IsConnected( const char& c, Node*& nodePtr ){
			for( auto& node : _NodeVector ){
				if( node.GetChar() == c ){
					nodePtr = &node;
					return true;
				}
			}
			nodePtr = nullptr;
			return false;
		}
		
		void AddWeight( size_t&& weight ){
			_WeightVector.emplace_back(weight);
		}
	};

	class Trie{
		Node* _Root;
		Node* _RootReverse;
		size_t _MaxWeight = 0;

		public:
		Trie( ) {
			_Root = new Node('$');
			_RootReverse = new Node('#');
		}

		~Trie(){
			delete(_Root);
			delete(_RootReverse);
		}

		void Insert( WordVector wordVector ){
			size_t wLeft = 0, wIdx = 0;
			size_t wordWeight = 0;

			for( auto& word : wordVector ){
				auto node = _Root;
				auto nodeR = _RootReverse;
				wIdx = 0;
				wLeft = word.length();
				while(wLeft > 0 ){
					--wLeft;
					node = &node->Connect(std::move(word[wIdx]), wordWeight);
					nodeR = &nodeR->Connect(std::move(word[wLeft]), wordWeight);
					++wIdx;
				}
				wordWeight++;
			}
			_MaxWeight = --wordWeight;
		}

		bool ContainsPrefix( const Word& prefix, Node*& node){
			node = _Root;
			
			for( auto& c : prefix ){
				if( !node->IsConnected( c, node ) ){
					node = nullptr;
					return false;	
				}
			}
			return true;
		}

		bool ContainsSuffix( const Word& suffix, Node*& node){
			node = _RootReverse;
			size_t sLeft = suffix.length();

			while( sLeft > 0 ){
				--sLeft;
				if( !node->IsConnected(suffix[sLeft], node) ){
					node = nullptr;
					return false;
				}
			}
			return true;	
		}

		int GetWeight( const Word& prefix, const Word& suffix ){
			Node *sEndPathNode = _RootReverse;
			Node *pEndPathNode = _Root;
			bool isPrefixEmpty = prefix.length() == 0;
			bool isSuffixEmpty = suffix.length() == 0;
			//Prefix and Suffix are empty
			if( isPrefixEmpty && isSuffixEmpty ){
				return _MaxWeight;
			}
			//Just Prefix
			if( isSuffixEmpty ){
				if( ContainsPrefix( prefix, pEndPathNode ) ){
					return pEndPathNode->GetWeightVector().back();	
				}
				else{
					return -1;
				}

			}

			//Just Suffix
			if( isPrefixEmpty ) {
				if( ContainsSuffix( suffix, sEndPathNode ) ){
					return sEndPathNode->GetWeightVector().back();
				}
				else{
					return -1;
				}
			}

			//Both Prefix and Suffix
			//
			int result = -1;

			if( ContainsPrefix( prefix, pEndPathNode ) && 
					ContainsSuffix( suffix , sEndPathNode ) ){
				auto pVector = pEndPathNode->GetWeightVector();
				auto sVector = sEndPathNode->GetWeightVector();
				auto pItr = pVector.rbegin();
				auto sItr = sVector.rbegin();
				auto pEnd = pVector.rend();
				auto sEnd = sVector.rend();

				while( pItr != pEnd && sItr != sEnd ){
					if( *pItr > *sItr ){
						pItr++;
						continue;
					}
					if( *sItr > *pItr ){
						sItr++;
						continue;
					}
					if( *pItr == *sItr ) {
						result = *pItr;
						break;
					}
				}
			}
			return result;;
		}

		
	};
}

#endif
