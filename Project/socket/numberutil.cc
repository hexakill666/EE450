#include"numberutil.h"

/**
 * find the last three digit of a number
 */
int NumberUtil::lastThreeDigit(long uscId){
    int count = 3;
    int temp = 0;
    int res = 0;
    while(count > 0){
        int remainder = uscId % 10;
        uscId /= 10;
        temp = temp * 10 + remainder;
        count--;
    }
    while(temp > 0){
        int remainder = temp % 10;
        temp /= 10;
        res = res * 10 + remainder;
    }
    return res;
}