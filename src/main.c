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
    printf("success!\n");
    struct destine_time userorder;
    int state = userdestine(&userorder);
    if (state == 2)
    {
        printf("user exit...\n");
        return 0;
    }
    if (state != 0)
    {
        printf("Something Error...\n");
        return 0;
    }

    
    printf("you order date is %s\n", userorder.date);
    printf("you order time is %d\n", userorder.time);

    return 0;
}

