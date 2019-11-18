#include <iostream>
#include <string>
#include <cmath>
#include <vector>

using namespace std;

class Base {
public:
	virtual int calc(int m, int n) = 0;
	virtual void print(int k) {}
};

class Binom : public Base
{
	int factorial(int n)
	{
		if (n == 0)
			return 1;

		if (n == 1)
			return 1;

		return n * factorial(n - 1);
	}

	int calc(int m, int n) override
	{
		if (m < 0 || n > m)
			return 0;

		if (n == 0 || n == m)
			return 1;

		return factorial(m) / (factorial(n) * factorial(m - n));
	}
};

void poly_calc(Base &b, int m, int n)
{
	int num = b.calc(m, n);
	for (int i = 0; i < num; ++i) {
		b.print(i);
	}
	cout << "number=" << m << " " << n << " " << num << endl;
	cout << endl;
}

class DyckPath : public Base
{
public:
    // (i, j)
    
    // (m, n)
    
    int calc(int m, int n) override
    {
        vector<pair<int, int>> curr;
        curr.push_back(make_pair(0, 0));
        recCalc(m, n, 0, 0, curr, common);
        return common.size();
    }
    
    void printCommon()
    {
        for (int i = 0; i < common.size(); i++)
        {
            for (int j = 0; j < common.at(i).size(); j++)
            {
                cout << "(" << common.at(i).at(j).first << ", " << common.at(i).at(j).second << "), ";
            }
            cout << endl;
        }
    }
private:
    void recCalc(int m, int n, int i, int j, vector<pair<int, int>> curr, vector<vector<pair<int, int>>>& common)
    {
        if (i == m && j == n)
        {
            common.push_back(curr);
            return;
        }
        
        vector<pair<int, int>> temp1 = curr;
        if (j + 1 <= n && m * (j + 1) <= n * i)
        {
            temp1.push_back(make_pair(i, j + 1));
            recCalc(m, n, i, j + 1, temp1, common);
        }
        vector<pair<int, int>> temp2 = curr;
        if (i + 1 <= m && m * j <= n * (i + 1))
        {
            temp2.push_back(make_pair(i + 1, j));
            recCalc(m, n, i + 1, j, temp2, common);
        }
    }
    
    vector<vector<pair<int, int>>> common;
};


int main()
{
	Base &b = Binom();
	poly_calc(b, 10, 2);
    DyckPath dp;
    
    cout << dp.calc(4, 4) << endl;
    dp.printCommon();
    return 0;
}
