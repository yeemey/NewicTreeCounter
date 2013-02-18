#ifndef STACK_H_
#define STACK_H_

typedef int Item;

class Stack {
private:
	int MAX;
	std::vector<Item> items;
	int top;
public:
	Stack();
	Stack(int size);
	bool isempty() const;
	bool isfull() const;
	bool push(const Item& item);
	bool pop();
	bool pop(Item& item);
};

#endif
