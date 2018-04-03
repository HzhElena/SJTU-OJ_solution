#include <iostream>
#include <cstring>
using namespace std;
const int maxn = 1000;
char number1[maxn];
char number2[maxn];
char result[maxn];

int judge(char *number1,char *number2)
{
    while(*number1 =='0') ++number1;
    while(*number2 == '0') ++number2;
    if(strlen(number1) > strlen(number2))
        return 1;
    else if(strlen(number1) < strlen(number2))
        return -1;
    else
    {
        int i=0;
        while(number1[i] == number2[i] && i<strlen(number1)) ++i;
        if(i==strlen(number1)) return 0;
        if((number1[i]-'0') > (number2[i] -'0')) return 1;
        else if(number1[i]-'0' < number2[i] - '0') return -1;
        else return 0;
    }
}
void sub(char *number1,char *number2)
{
    while(*number1 =='0') ++number1;
    while(*number2 == '0') ++number2;
    if(judge(number1,number2)<0) return;
    else if(judge(number1,number2)==0) {
            for(int i=0;i<strlen(number1);++i) number1[i]='0';
            return;
    }
    int tmp = strlen(number2);
    int carry=0;
//    cout<<"num1: "<<number1<<endl;
 //   cout<<"num2: "<<number2<<endl;
    int i;
    int len1 = strlen(number1);
    for(i=1;i<=tmp;++i)
    {
        int t = (number1[len1-i]-'0') - carry - (number2[tmp-i]-'0');
  //      cout<<"t: "<<t<<endl;
        if(t<0) {t+=10; carry =1;}
        else carry = 0;
        number1[len1-i] = t + '0';
    }
    while(carry && i<=len1)
    {
        int t = (number1[len1-i] - '0') - carry;
        if(t<0) {t+=10; carry = 1;}
        else carry =0 ;
        number1[len1-i] = t + '0';
    }
}
void divide()
{
    int add_bits = strlen(number1) - strlen(number2);
    int len = strlen(number2);
    int rs = 0;
    while(judge(number1,number2)>0) //number1 is greater than number2
    {
        for(int i=len;i<len+add_bits;++i)
            number2[i] = '0';
        number2[len+add_bits] = '\0';
  //      cout<<"number: "<<number2<<endl;
        int tmp = 0;
        while(judge(number1,number2)>=0)
          {
            sub(number1,number2);
            ++tmp;
          }
        number2[len] = '\0';
    //    cout<<"tmp: "<<tmp<<endl;
        result[rs++] = tmp + '0';
        --add_bits;
    }
    ++add_bits;
    while(add_bits--)
        result[rs++] = '0';
    result[rs] = '\0';
}
int main()
{
    cin.getline(number1,maxn);
    cin.getline(number2,maxn);
    if(judge(number1,number2)==0) {cout<<1; return 1;}
    if(judge(number1,number2)<0) {cout<<0; return 1;}
    divide();
    int i=0;
    while(result[i] == '0') ++i;
    cout<<result+i;
}
