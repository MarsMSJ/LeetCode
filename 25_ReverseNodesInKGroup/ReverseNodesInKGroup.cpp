#include <iostream>

struct ListNode {
	int val;
	ListNode *next;
	ListNode(int x) : val(x), next(NULL){}
};

ListNode* GetLinkedList( int k, ListNode* head ){
    if( k < 2 ){
        return NULL;
    }
    int count = 1;
    auto node = head;
    auto prevNode = head;
    while( k > count && node != NULL ){
        prevNode = node;
        node = node->next;
        ++count;
    }
    if( k != count ){
        //Not enough nodes to fulfill K requirement
        return NULL;
    }
    else{
        return node;
    }
   
}

void ReverseLinkedList( ListNode* startNode){
    if( startNode == NULL ){ return; }
	
	ListNode* node = startNode;
	ListNode* nextNode = node->next;
	ListNode* prevNode = NULL;

	while( node != NULL ){
		nextNode = node->next;
		node->next = prevNode;
		prevNode = node;
		node = nextNode;
	}
}

ListNode* reverseKGroup(ListNode* head, int k) {
    if( head == NULL ){ return head; }
    if( head->next == NULL ){ return head; }
	if( k < 2 ) { return head; }
    
    ListNode* start = head;
    ListNode* end;
    ListNode* newHead = NULL;
    ListNode* newTail = NULL;
    ListNode* nextNode = NULL;
    
    while( start != NULL ){
        //Cut a k-node linkedlist from the larger linkedlist
        end = GetLinkedList(k, start);
        
        if( end == NULL && newHead == NULL ){
            //Not enough nodes to cut a K-Node linkedlist
            // LinkedList Nodes < K
            return head;
        }
        
        if( end != NULL ){
            nextNode = end->next;
            end->next = NULL; //Let ReverseLinkedList know where to stop
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
        if( newHead == NULL ){
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
	while( node != NULL ){
		std::cout << node->val;
		if( node->next != NULL ){
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

