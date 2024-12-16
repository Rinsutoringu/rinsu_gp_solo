#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <direct.h>
#include "../inc/userlogin.h"
#include "../inc/userdestine.h"
#include "../inc/user_choose.h"
#include "../inc/txtcreater.h"


int 

int main(int argc, char const *argv[])
{
    char account_file[] = "./name_and_password.txt";

    if (userlogin(account_file) == 1)
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

    // 开始构造mangeroom函数

    char Classroom_info[] = "Classroom_info.txt";
    if ((txtcreater(Classroom_info, &userorder)) != 0)
    {
        printf("Insufficient permissions!");
        return 0;
    }

    
    
    
    return 0;
}
