#include<stdio.h>
void test(int a, int b, int c){
    int s1;
    int s2;
    int s3;
    int s4;
    s1=4+a;
    s2=s1-2+b;
    s3=s2-c;
    s4=s1+s2+s3;
    printf("%d \n",s4);
}
int main(){
    test(6,3,4);
    return 0;
}