#include <iostream>
using namespace std;

#include "../ReusableCode/sum.hpp"

int main()
{
    double num1, num2, num3;
    cout << "Enter three numbers: ";
    cin >> num1 >> num2 >> num3;

    double result = sum(num1, num2, num3);
    cout << "Sum: " << result << endl;

    return 0;
}