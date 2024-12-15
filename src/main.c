#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include"../inc/userlogin.h"
#include"../inc/userdestine.h"
#include"../inc/user_choose.h"

int main(int argc, char const *argv[])
{
    if (userlogin() == 1)
    {
        printf("login fail!");
        return 0;
    }
    printf("success!");
    struct destine_time userorder;
    // userorder.date = "1";
    // userorder.time = 1;
    if (userdestine(&userorder) != 0)
    {
        printf("Something Error...\n");
        return 0;
    }
    printf("you order date is %s\n", userorder.date);
    printf("you order time is %d\n", userorder.time);

    return 0;
}

