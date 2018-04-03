#include <iostream>
#include <cstring>
using namespace std;
void multiply(char *num1,char *num2)
{
    char rs[strlen(num1)+strlen(num2)];
    rs[strlen(num1)+strlen(num2)] = '\0';
    for(int i=0;i<strlen(num1)+strlen(num2);++i)
        rs[i] = '0';
    for(int i = strlen(num1)-1, d = strlen(rs)-1; i >= 0; i--, d--)
        {
            int carry = 0, k = d;
            for (int j = strlen(num2)-1; j >= 0; j--, k--)
            {
                int a = num1[i] - '0';
                int b = num2[j] - '0';
                a = a*b+carry + (rs[k]-'0');
                carry = a/10;
                rs[k] = a%10 + '0';
            }
            while (carry)
            {
                int sum = carry + (rs[k]-'0');
                carry = sum / 10;
                rs[k--] = sum % 10 + '0';
            }
        }
    int t = 0;
    while(strlen(rs)>=t && rs[t]=='0') ++t;
    cout<<rs+t;
}
int main()
{
    char num1[1000],num2[1000];
    cin.getline(num1,1000);
    cin.getline(num2,1000);
    multiply(num1,num2);
    return 0;
}
