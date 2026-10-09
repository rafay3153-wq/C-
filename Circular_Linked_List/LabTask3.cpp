#include <iostream>
using namespace std;
struct Node {
	int data;
	Node* next;
};
void insert(Node*& pNode,int value) {
	Node*p=new Node;
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
void display(Node* pNode) {
	if(pNode==NULL) {
		cout<<"List is empty." <<endl;
		return;
	}
	Node* p=pNode->next;
	do {
		cout<<p->data<<" ";
		p=p->next;
	} while(p!=pNode->next);
	cout<<endl;
}
void deleteEvenPositions(Node*& pNode) {
	if(pNode==NULL)
	return;
	if(pNode->next==pNode)
	return;
	Node* current=pNode->next;
	Node* previous=pNode;
	int position=1;
	while(true) {
		if(position%2==0) {
			previous->next=current->next;
			if(current==pNode)
			pNode=previous;
			Node* temp=current;
			current=current->next;
			delete temp;
		}
		else {
			previous=current;
			current=current->next;
		}
		position++;
		if(current==pNode->next)
		break;
	}
}
int main() {
	Node* pNode=NULL;
	insert(pNode,10);
	insert(pNode,20);
	insert(pNode,30);
	insert(pNode,40);
	insert(pNode,50);
	insert(pNode,60);
	cout<<"Original list: ";
	display(pNode);
	cout<<"After deleting even positions: ";
	deleteEvenPositions(pNode);
	display(pNode);
	return 0;
}
