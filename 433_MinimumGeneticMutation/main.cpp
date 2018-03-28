#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <initializer_list>

using std::string;
using std::vector;
using std::queue;



class Solution {
private:
    vector<vector<size_t>>* AdjNodeV;
    enum GeneComparrison { Same, OneStepAway, TooDifferent };

    GeneComparrison CompareGene( const string& geneStrA, const string& geneStrB ) const {
        size_t diff = 0, len = geneStrA.length();
        
        for( size_t i = 0; i < len; ++i ) {
            if( geneStrA[i] != geneStrB[i] ){ ++diff; }
            if( diff > 1 ) { return GeneComparrison::TooDifferent; }
        }
        return diff == 0 ? GeneComparrison::Same : GeneComparrison::OneStepAway;        
    }

    void CreateGraph( const vector<string>& bank ) {
        size_t size = bank.size();
        AdjNodeV = new vector<vector<size_t>>( size );
        
        for( size_t bdx = 0; bdx < size; ++bdx ) {
            for( size_t vdx = 0; vdx < size; ++vdx ) {
                if( bdx == vdx ) { continue; }
                
                if( CompareGene( bank[bdx], bank[vdx]) == GeneComparrison::OneStepAway ) {
                    (*AdjNodeV)[vdx].push_back(bdx);
                    (*AdjNodeV)[bdx].push_back(vdx);
                }
            }            
        }
    }

    inline size_t FindIndex( const string& geneStr, const vector<string>& bank) const {
        size_t size = bank.size();

        for( size_t i = 0; i < size; ++i ) {
            if( bank[i] == geneStr ) {
                return i;
            }
        }
        return size;
    }

    inline queue<size_t> FindAllOneAwayIndexes( const string& geneStr, const vector<string>& bank) const {
        size_t size = bank.size();
        queue<size_t> allOneAwayV;
        for( size_t i = 0; i < size; ++i ) {
            if( CompareGene( bank[i], geneStr ) == GeneComparrison::OneStepAway ) {
                allOneAwayV.push(i);
            }
        }
        return allOneAwayV;
    }
    
    int PerformBFS( const size_t& startIdx, const string& end, const vector<string>& bank,
    size_t offset = 0 ){
        queue<std::pair<size_t, size_t>> Q;
        size_t size = bank.size();
        size_t steps = offset;
        size_t sdx = startIdx;        
        Q.push( std::make_pair(sdx, steps) );
        size_t idx = sdx;
        vector<bool> visited( size, false );

        while( !Q.empty() ) {
            idx = Q.front().first;
            steps = Q.front().second;
            Q.pop();
            
            if( visited[idx] ) {
                continue;
            }

            visited[idx] = true;

            if( bank[idx] == end ){
                return steps;
            }
            auto v = (*AdjNodeV)[idx];
            
            for( auto i : v ) {
                if( !visited[i] ) {
                    Q.push( std::make_pair( i, steps + 1 ) );
                }
            }            
        }
        
        return -1;
    }

   
public:
    
    ~Solution() {
        if( AdjNodeV != nullptr ) { delete(AdjNodeV); }
    }

    int minMutation(string start, string end, vector<string>& bank) {
        CreateGraph(bank);
        auto bankSize = bank.size();
        if( bankSize == 0 ) {
            return -1;
        }

        auto startStrIdx = FindIndex( start, bank );
        
        if( startStrIdx != bankSize ) {   
            return PerformBFS( startStrIdx, end, bank );
        }

        queue<size_t> idxQ = FindAllOneAwayIndexes( start, bank );
        int minSteps = bank.size() + 1;
        int steps = 0;

        while( !idxQ.empty() ) {
            steps = PerformBFS( idxQ.front(), end, bank, 1 );
            idxQ.pop();
            minSteps = std::min( minSteps, steps );
        }
        return minSteps;
    }
};

int main(){
    // string startGene = "AAA";
    // string endGene = "ABC";
    // vector<string> bank {"AAA", "AAB", "ACC", "ABA", "ABC"};

    string startGene = "AAAACCCC";
    string endGene =   "CCCCCCCC";
    vector<string> bank { "AAAACCCA","AAACCCCA","AACCCCCA","AACCCCCC",
        "ACCCCCCC","CCCCCCCC","AAACCCCC","AACCCCCC" };

    int steps = 0;
    Solution s;
    steps = s.minMutation(startGene, endGene, bank);
    std::cout << "Output: " << steps << std::endl;
    return 0;
}