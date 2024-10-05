#include<iostream>
#include<string>

using namespace std;

//Implementation of dynamic Stack using Templates
template<class ItemType>
class Stack {
private:
	int top;
	ItemType* items;
	int capacity;
public:
	Stack();
	Stack(int n);
	~Stack();
	bool isEmpty();
	bool isFull();
	void push(char newItem);
	char pop();
	char Top();
};

template<class ItemType>
Stack<ItemType>::Stack() {
	capacity = 100;
	items = new ItemType[capacity];
	top = -1;
}

template<class ItemType>
Stack<ItemType>::Stack(int n) {
	capacity = n;
	items = new ItemType[capacity];
	top = -1;
}

template<class ItemType>
Stack<ItemType>::~Stack() {
	delete[] items;
}

template<class ItemType>
bool Stack<ItemType>::isEmpty() {
	return (top == -1);
}

template<class ItemType>
bool Stack<ItemType>::isFull() {
	return (top == capacity - 1);
}

template<class ItemType>
void Stack<ItemType>::push(char newItem) {
	if (isFull()) {
		cout << "STACK OVERFLOW" << endl;
		exit(1);
	}
	top++;
	items[top] = newItem;
}

template<class ItemType>
char Stack<ItemType>::pop() {
	if (isEmpty()) {
		cout << "STACK UNDERFLOW" << endl;
		exit(1);
	}
	char popVal = items[top];
	items[top] = 0;
	top--;
	return popVal;
}

template<class ItemType>
char Stack<ItemType>::Top() {
	if (top == -1) {
		cout << "STACK IS EMPTY";
		exit(1);
	}
	return items[top];
}

//Function Prototypes
int precedence(char op);
bool isOperator(char op); 
bool isOperand(char c);
bool parenthesisBalanced(string& exp);

string postfix(Stack<char>& opStk, string infix_exp);
string prefix(Stack<char>& opStk, string infix_exp);
int multiplication(int a, int b);
double power(int x, int n);

//main Function
int main() {
	Stack<char> opStk;
	string infix;
	int choice;
	char con='y';
	bool continueLoop=true;
	do {
		cout << "------MENU------\n1. INFIX to POSTFIX\n2. INFIX to PREFIX\n3. MULTIPLICATION\n4. POWER\n";
		cin >> choice;

		if (choice == 1) {
			cout << "Enter Infix Expression: ";
			cin >> infix;
			string postfix_exp = postfix(opStk, infix);
			cout << postfix_exp;
		}
		else if (choice == 2) {
			cout << "Enter Infix Expression: ";
			cin >> infix;
			string prefix_exp = prefix(opStk, infix);
			cout << prefix_exp;
		}
		else if (choice == 3) {
			int a, b;
			cout << "\nEnter 2 Integers: ";
			cin >> a >> b;
			cout << "\n" << a << " * " << b << " = " << multiplication(a, b);
		}
		else if (choice == 4) {
			int x, n;
			cout << "\nEnter Integer and its power: ";
			cin >> x >> n;
			cout << "\n" << x << " ^ " << n << " = " << power(x, n);
		}
		else {
			cout << "Invalid Input";
		}
		cout << "\nWould you like to continue?(Y/N)";
		cin >> con;
		if (con == 'n' || con == 'N') {
			cout << "Exiting Program...";
		}
		else if(con == 'y' || con == 'Y'){}
		else {
			cout << "invalid input: enter Y/N";
		}
	} while (con=='y' || con=='Y');

	
}

//Funtion Definitions:
int precedence(char op) {
	if (op == '+' || op == '-') {
		return 1;
	}
	else if (op == '*' || op == '/') {
		return 2;
	}
	else if (op == '^') {
		return 3;
	}
	else
		return -1;
}

bool isOperator(char op) {
	return op == '+' || op == '-' || op == '*' || op == '/' || op == '^';
}
bool isOperand(char c) {
	return c >= 'a' && c <= 'z' || c >= 'A' && c <= 'Z';
}
bool parenthesisBalanced(string& exp) {
	int count=0;
	for (char p : exp) {
		if (p == '(') {
			count++;
		}
		else if (p == ')') {
			count--;
		}
	}
	return count == 0;
}

int multiplication(int a, int b) {
	if (b == 1) {
		return a;
	}
	else {
		return (multiplication(a, (b - 1)) + a);
	}
}

double power(int x, int n) {
	if (n == 0) {
		return 1;
	}
	else {
		return x * power(x, n - 1);
	}
}

string postfix(Stack<char>& opStk, string infix_exp) {
	string postfix_exp = "";
	char op;
	if (!parenthesisBalanced(infix_exp)) {
		return "INVALID INFIX EXPRESSION: Your expression is not balanced. Please ensure expression consists equal number of opening and closing parenthesis";
	}
	for (int i = 0; i < infix_exp.length(); i++) {
		if (isOperand(infix_exp[i])) {
			postfix_exp += infix_exp[i];
		}
		else if (infix_exp[i] == '(') {
			opStk.push(infix_exp[i]);
		}
		else if (infix_exp[i] == ')') {
			while (opStk.Top() != '(' && !opStk.isEmpty() ) {
				char temp=opStk.Top();
				postfix_exp += temp;
				opStk.pop();
			}
			if (opStk.Top() == '(') {
				opStk.pop();
			}
		}
		else if (isOperator(infix_exp[i])) {
			if (opStk.isEmpty()) {
				opStk.push(infix_exp[i]);
			}
			else {
				
				if (precedence(infix_exp[i]) > precedence(opStk.Top())) {
					opStk.push(infix_exp[i]);
				}
				else{
					while (!opStk.isEmpty() && precedence(infix_exp[i]) <= precedence(opStk.Top())) {
						postfix_exp += opStk.Top();
						opStk.pop();
					}
					opStk.push(infix_exp[i]);
				}
			}
		}
	}
	while (!opStk.isEmpty()) {
		postfix_exp += opStk.Top();
		opStk.pop();
	}
	return "Postfix Expression: "+postfix_exp;
}

string prefix(Stack<char>& opStk, string infix_exp) {
	Stack<char> tempStk;
	string reversed_exp = "";
	string prefix_exp = "";
	string exp = "";
	char op;

	if (!parenthesisBalanced(infix_exp)) {
		return "INVALID INFIX EXPRESSION: Your expression is not balanced. Please ensure expression consists equal number of opening and closing parenthesis";
	}

	//reverse infix expression using stack and store in a variable
	for (int i = 0; i < infix_exp.length(); i++) {
		 tempStk.push(infix_exp[i]);
	}
	for (int i = 0; i < infix_exp.length(); i++) {
		reversed_exp += tempStk.pop();
	}
	
	//perform infix-prefix algorithm
	for (int i = 0; i < reversed_exp.length(); i++) {
		if (isOperand(reversed_exp[i])) {
			exp += reversed_exp[i];
		}
		else if (reversed_exp[i] == ')') {
			opStk.push(reversed_exp[i]);
		}
		else if (reversed_exp[i] == '(') {
			while (opStk.Top() != ')' && !opStk.isEmpty()) {
				char temp = opStk.Top();
				exp += temp;
				opStk.pop();
			}
			if (opStk.Top() == ')') {
				opStk.pop();
			}
		}
		else if (isOperator(reversed_exp[i])) {
			if (opStk.isEmpty()) {
				opStk.push(reversed_exp[i]);
			}
			else {

				if (precedence(reversed_exp[i]) > precedence(opStk.Top())) {
					opStk.push(reversed_exp[i]);
				}
				else {
					while (!opStk.isEmpty() && precedence(reversed_exp[i]) <= precedence(opStk.Top())) {
						exp += opStk.Top();
						opStk.pop();
					}
					opStk.push(reversed_exp[i]);
				}
			}
		}
	}
	while (!opStk.isEmpty()) {
		exp += opStk.Top();
		opStk.pop();
	}
	
	//reverse the string again for final prefix expression and return
	for (int i = 0;i < exp.length();i++) {
		tempStk.push(exp[i]);
	}
	for (int i = 0;i <exp.length();i++) {
		prefix_exp +=tempStk.pop();
	}
	return "Prefix Expression: "+prefix_exp;
}