#include <iostream>
#include <vector>

using namespace std;

struct Block {
	uint size;
	string name;
	struct Block *nextBlock;

	Block(int size) {
		this->size = size;
	}

	Block(string name) {
		this->name = name;
	}
};

struct Stack {

	Block *first;

	Stack() {
		first = NULL;
	}

	void addBlock(uint size, uint amount=0) {
		if(amount>0){--amount;}
begin:
		Block *temp_block = new Block(size);
		
		if(first==NULL) {
			first = temp_block;
		}
		else if(first!=NULL && first->nextBlock==NULL) {
			first->nextBlock = temp_block;
		}
		else if(first->nextBlock!=NULL) {
			Block *temp = first;

			while(temp->nextBlock!=NULL) {
				temp = temp->nextBlock;
			}

			temp->nextBlock = temp_block;
		}
		
		if(amount!=0){--amount;goto begin;}
	}
	
	void printBlocks() {

		Block *temp = first;
		uint count = 1;

		do {
			if(count!=1){temp = temp->nextBlock;}
			cout << "\n Block no: " << count << endl;
			cout << "Its size: " << temp->size << endl;
			cout << "Process name: " << temp->name << endl;
			count++;
		}
		while(temp->nextBlock!=NULL);


		cout << "\nNo more blocks" << endl;
	}

	void allocateMemory(string processName, int size) {

		Block *temp = first;
		uint found = 0, count = 0;

		do {
			if(count!=0){temp=temp->nextBlock;}
			
			if(temp->name.empty() && temp->size>=size) {
				temp->name = processName;
				found++;
				cout << "Valid block found!"<<endl;
				break;
			}
			count++;
		}
		while(temp->nextBlock!=NULL);

		if(found==0){cout<<"No valid blocks found."<<endl;

	}
}

	void userInterface(Stack *stack) {
		uint option=0;

		while(1) {
			cout << "\nWelcome" <<endl;
			cout << "To allocate memory for a process press 1"<<endl;
			cout << "Print memory map press 2"<<endl;
			cout << "To exit press 0"<<endl;
			cout << "Your option: ";
			cin >> option;

			if(option==1) {

				string name, temp;
				uint size;
				cout << "Process name: ";
				getline(cin,temp);
				getline(cin,name);
				cout << "Size: ";
				cin >> size;
				
				cout << "Searching for valid block.."<<endl;
				stack->allocateMemory(name,size);
			}
			else if(option==2){
				stack->printBlocks();
			}
			else if(option==0){
				return;
			}
		}
	}

	void blockInit(Stack *mng) {
		mng->addBlock(2,2);
		mng->addBlock(4,2);
		mng->addBlock(16,2);
		mng->addBlock(32,2);
		mng->addBlock(64);
		mng->addBlock(128);
	}
};


int main() {

	Stack mng;
	mng.blockInit(&mng);
	mng.userInterface(&mng);

	


	return 0;
}

