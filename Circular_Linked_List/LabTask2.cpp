#include<iostream>
using namespace std;
struct Node{
	int data;
	Node* next;
};
void insert(Node*& pNode,int value) {
	Node* p=new Node;
	p->data=value;
	if(pNode==NULL) {
		p->next=p;
		pNode=p;
	}
	else {
		p->next=pNode->next;
		pNode->next=p;
		pNode=p;
	}
}
int josephus(int n,int k){
	Node* pNode=NULL;
	for(int i=1;i<=n;i++) {
		insert(pNode,i);
	}
	Node* current=pNode;
	Node* previous=pNode;
	while(previous->next!=pNode) {
		previous=previous->next;
	}
	cout<<"Elimination order: ";
	while(current->next!=current) {
		for(int count=1;count<k;count++) {
			previous=current;
			current=current->next;
		}
		cout<<current->data<<" ";
		previous->next=current->next;
		Node* temp=current;
		current=current->next;
		delete temp;
	}
	int survivor=current->data;
	delete current;
	pNode=NULL;
	return survivor;
}
int main() {
	int n,k;
	cout<<"Enter number of people: ";
	cin>>n;
	cout<<"Enter k: ";
	cin>>k;
	int survivor=josephus(n,k);
	cout<<"\nSurvivor: "<<survivor<<endl;
	return 0;
}
