#include<stdlib.h>
    char c[20];
    void numberToChar(int number)
    {
        int i=0;
        if(number==0)
            c[i++]='0';
        else
            while(number!=0)
            {
                int remainder = number%10;
                c[i++]='0'+remainder;
                number = number/10;
            }
        strrev(c);
        c[i]='\0';
    }
