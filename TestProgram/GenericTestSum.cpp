#include <iostream>
using namespace std;

#include "../ReusableCode/GenericSum.cpp" // Needed because it is templated

int main()
{
    double num1, num2, num3;
    cout << "Enter three integers: ";
    cin >> num1 >> num2 >> num3;

    double result = sum(num1, num2, num3);
    cout << "Sum: " << result << endl;

    return 0;
}