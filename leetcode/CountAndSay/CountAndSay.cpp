#include <iostream>
#include <string>
using namespace std;
string countAndSay(int n)
{
    if( n <= 0 )
        return "";

    string resStr = "1";
    if( n == 1 )
        return resStr;

    int count = 0;
    char tempCh = '\0';
    string tempResStr = "";
    for( int i = 2; i <= n; i++)
    {
        int j = 0;
        tempResStr = "";
        tempCh = resStr[j];
        count = 0;
        for(; j < resStr.length(); j++)
        {
            if(tempCh == resStr[j])
            {
                count++;
            }
            else
            {
                tempResStr += std::to_string(count);
                tempResStr += tempCh;
                count = 1;
                tempCh = resStr[j];
            }
        }
        tempResStr += std::to_string(count);
        tempResStr += tempCh;
        cout<<i<<":\t"<<tempResStr<<endl;
        resStr = tempResStr;
    }
    return resStr;
}
int main()
{
	int i = 0;
	countAndSay(4);
	return 0;
}
