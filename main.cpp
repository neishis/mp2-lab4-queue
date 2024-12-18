#include "TQueue.h"
#include <iostream>

int main() {
	setlocale(LC_ALL, "RUS");
	try {
		int s, val;
		TQueue<int> q(4);
		while (true) {
			cout << "1 - add, 0 - remove" << endl;
			cin >> s;
			if (s) {
				cout << "enter a number: ";
				cin >> val;
				q.push(val);
			}
			else
				q.pop();
			cout << q << "cntr = " << q.GetCntr() << endl;
		}
	}
	catch (int er) {
		cout << "oof: " << er;
	}
	return 0;
}