#include <vector>
#include <iostream>
#include "stack.h"

Stack::Stack(){
	top = 0;
	MAX = 1;
}

Stack::Stack(int size){
	top = 0;
	MAX = size;
}

bool Stack::isempty() const
{
	return top == 0;
}

bool Stack::isfull() const
{
	return top == MAX;
}

bool Stack::push(const Item& item){
	if(top < MAX){
		items.push_back(item);
		top++;
		return true;
	}
	else
		return false;
}

bool Stack::pop(){
	if(top > 0){
		items.erase(items.end());
		//std::cout << "It was this one that got popped." << std::endl;
		--top;
		return true;
	}
	else
		return false;
}

bool Stack::pop(Item& item){
	if(top > 0){
		//int* itemptr = &items.back();
		//item = *itemptr;
		//item = items[items.size() - 1];
		//std::cout << "Popping " << item << std::endl;
		item = (int)items.back();
		items.pop_back();
		//items.erase(items.end());
		//items.erase(items.end());
		--top;
		return true;
	}
	else
		item = -1;
		return false;
}
