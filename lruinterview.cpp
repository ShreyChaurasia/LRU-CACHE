#include<iostream>
#include<map>
using namespace std;


// structure of a double linked list
struct node{
	int key;
	struct node *next;
	struct node *prev;
};

// head and tail of a DLL
struct node* head;
struct node* tail;

// to make the node
struct node* newNode(){
	struct node* temp = (struct node*)malloc(sizeof(struct node));
	temp->key = 0;
	temp->prev = NULL;
	temp->next = NULL;
	return temp;
}




// define the size of a LRU cache
int cacheSize;

// defines the current size of a lru cache
int currCacheSize = 0;

// map to hold the address of a particular key
map <int, struct node* > keyToAddress;
// map to hold the value of a particular key
map <int, int> keyToValue;


void removeTheNode(struct node* temp){
    // head node is to be deleted
	if(!temp->prev){
		head = head->next;
		if(head)head->prev = NULL;
		else tail = NULL;
		return;
	}
	temp->prev->next = temp->next;
	if(temp->next)temp->next->prev = temp->prev;
	else tail = temp->prev;
	temp->next = NULL;
	temp->prev = NULL;
	free(temp);
}

// function to fix the new node in DLL
struct node* fixTheNode(int key){
	struct node* temp = newNode();
	temp->key = key;
	temp->next = head;
	if(head)head->prev = temp;
	head = temp;
	if(!tail) tail = temp;
	return temp;
}



// funtion to insert the key, value pair in a map
void put(int key, int value){
	if(keyToAddress.find(key) != keyToAddress.end()){
		removeTheNode(keyToAddress[key]);
	}
	else{
		if(currCacheSize == cacheSize){
			int lastKey = tail->key;
			removeTheNode(tail);
			keyToAddress.erase(lastKey);
			keyToValue.erase(lastKey);
		}
	}
	struct node* temp = fixTheNode(key);
	keyToAddress[key] = temp;
	keyToValue[key] = value;
}



// to get the value from the key
int get(int key){
	// if the key is not found in the map, then return -1.
	if(keyToValue.find(key) == keyToValue.end())return -1;
	// else return the value but now the accessed node will be the most recently used node
	// so transfering it to the head.
	int value = keyToValue[key];
	removeTheNode(keyToAddress[key]);
	struct node* temp = fixTheNode(key);
	keyToAddress[key] = temp;
	return value;
}

// function to print the DLL
void print(){
	struct node*p = head;
	while(p){
		cout<<p->key<<" ";
		p = p->next;
	}
	cout<<"\n";
}


// used to set the cache size
void setCacheSize(int len){
	cacheSize = len;
}

int main(){
	head = NULL;
	tail = NULL;
	setCacheSize(3);
	put(2, 5);
	print();
	put(1, 6);
	print();
	put(1, 7);
	print();
	cout<<get(3)<<"\n";
	cout<<get(1)<<"\n";
	cout<<get(2)<<"\n";
	put(4, 10);
	print();
	cout<<get(4)<<"\n";
	print();
	cout<<get(1)<<"\n";
	print();
	cout<<get(4)<<"\n";
}