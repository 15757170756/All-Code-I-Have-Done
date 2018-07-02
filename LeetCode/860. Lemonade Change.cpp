/*
860. Lemonade Change
User Accepted: 1826
User Tried: 1980
Total Accepted: 1842
Total Submissions: 3657
Difficulty: Easy
At a lemonade stand, each lemonade costs $5. 

Customers are standing in a queue to buy from you, and order one at a time (in the order specified by bills).

Each customer will only buy one lemonade and pay with either a $5, $10, or $20 bill.  You must provide the correct change to each customer, so that the net transaction is that the customer pays $5.

Note that you don't have any change in hand at first.

Return true if and only if you can provide every customer with correct change.

 

Example 1:

Input: [5,5,5,10,20]
Output: true
Explanation: 
From the first 3 customers, we collect three $5 bills in order.
From the fourth customer, we collect a $10 bill and give back a $5.
From the fifth customer, we give a $10 bill and a $5 bill.
Since all customers got correct change, we output true.
Example 2:

Input: [5,5,10]
Output: true
Example 3:

Input: [10,10]
Output: false
Example 4:

Input: [5,5,10,10,20]
Output: false
Explanation: 
From the first two customers in order, we collect two $5 bills.
For the next two customers in order, we collect a $10 bill and give back a $5 bill.
For the last customer, we can't give change of $15 back because we only have two $10 bills.
Since not every customer received correct change, the answer is false.
 

Note:

0 <= bills.length <= 10000
bills[i] will be either 5, 10, or 20.
*/



class Solution {
public:
	bool lemonadeChange(vector<int>& bills) {
		int totalPrice = 5 * bills.size();
		vector<int> trueBills;
		for (int i = 0; i < bills.size(); ++i) {
			if (bills[i] == 5)
				trueBills.push_back(5);
			else if(bills[i] == 10) {
				auto iter = find(trueBills.begin(), trueBills.end(), 5);
				if (iter == trueBills.end())
					return false;
				trueBills.erase(iter);
				trueBills.push_back(10);
			}
			else if (bills[i] == 20) {
				auto iter10 = find(trueBills.begin(), trueBills.end(), 10);
				auto iter51 = find(trueBills.begin(), trueBills.end(), 5);
				if (iter51 == trueBills.end())
					return false;

				else if (iter10 != trueBills.end() && iter51 != trueBills.end()) {
					trueBills.erase(iter10);
					auto iter51 = find(trueBills.begin(), trueBills.end(), 5);
					trueBills.erase(iter51);
					trueBills.push_back(20);
				}
				
				else if (iter10 == trueBills.end()) {
					for (int i = 0; i < 3; ++i) {
						auto iter51 = find(trueBills.begin(), trueBills.end(), 5);
						if (iter51 == trueBills.end())
							return false;
						trueBills.erase(iter51);
					}
					trueBills.push_back(20);
				}
			}
		}
		int sum = accumulate(trueBills.begin(), trueBills.end(), 0);
		if (sum == totalPrice)
			return true;
		else
			return false;
	}
};
//Submission Result: Accepted 