#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"userlogin.h"
/*

*/



int main(int argc, char const *argv[])
{
    char input_username[20] = {0};
    char input_password[20] = {0};
    printf("please input your username\n");
    scanf("%s", input_username);
    printf("please input your password\n");
    scanf("%s", input_password);
    if (userlogin(input_username, input_password) == 1)
    {
        printf("login fail!");
        return 0;
    }
    printf("success!");
    return 0;
}
