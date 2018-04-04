#include <iostream>

struct ListNode {
	int val;
	ListNode *next;
	ListNode(int x) : val(x), next(nullptr){}
};

ListNode* GetLinkedList( int k, ListNode* head ){
    if( k < 2 ){
        return nullptr;
    }

    size_t count = 1;
    auto node = head;
    auto prevNode = head;

    while( k > count && node != nullptr ){
        prevNode = node;
        node = node->next;
        ++count;
    }

    if( k != count ){
        //Not enough nodes to fulfill K requirement
        return nullptr;
    }
    
    return node;       
}

void ReverseLinkedList( ListNode* startNode){
    if( startNode == nullptr ){ return; }
	
	ListNode* node = startNode;
	ListNode* nextNode = node->next;
	ListNode* prevNode = nullptr;

	while( node != nullptr ){
 		nextNode= node->next;
		node->next = prevNode;
		prevNode = node;
		node = nextNode;
	}
}

ListNode* reverseKGroup(ListNode* head, int k) {
    if( head == nullptr ){ return head; }
    if( head->next == nullptr ){ return head; }
	if( k < 2 ) { return head; }
    
    ListNode* start = head;
    ListNode* end;
    ListNode* newHead = nullptr;
    ListNode* newTail = nullptr;
    ListNode* nextNode = nullptr;
    
    while( start != nullptr ){
        //Cut a k-node linkedlist from the larger linkedlist
        end = GetLinkedList(k, start);
        
        if( end == nullptr && newHead == nullptr ){
            //Not enough nodes to cut a K-Node linkedlist
            // LinkedList Nodes < K
            return head;
        }
        
        if( end != nullptr ){
            nextNode = end->next;
            end->next = nullptr; //Let ReverseLinkedList know where to stop
            //End and Start are reversed after this call
            ReverseLinkedList(start);
        }
        else{
            //Not enough nodes left
            //Attach what's left of the linkedlist
            newTail->next = start;
            break;
        }
        
        //Start and End have been reversed
        if( newHead == nullptr){
            newHead = end;
        }
        else{
            newTail->next = end;
        }
        newTail = start;
        start = nextNode;
    }
    return newHead;
}

void PrintLinkedList( ListNode* head ) {
	auto node = head;
	std::cout << "[";

	while( node != nullptr ){
		std::cout << node->val;

		if( node->next != nullptr){
			std::cout << ",  ";
		}
		node = node->next;
	}
	std::cout << "]\n";
}

int main(){
	ListNode head(0);
	ListNode* node = &head;
    int max = 5;
    int k = 6;
	for( int i = 1; i < max; ++i ){
		node->next = new ListNode(i);
		node = node->next;	
	}
	PrintLinkedList( &head );
	node = reverseKGroup( &head, k);
    std::cout << "Printing new linked list\n";
	PrintLinkedList( node );
}

