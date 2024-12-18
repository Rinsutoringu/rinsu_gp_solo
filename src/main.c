#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <direct.h>
#include <dirent.h>
#include <unistd.h>
#include "../inc/userlogin.h"
#include "../inc/userdestine.h"
#include "../inc/define_struct.h"
#include "../inc/txtcreater.h"
#include "../inc/txtreader.h"

    // int need_size;
    // printf("please input room size you want.\n");
    // scanf("%d", need_size);

    // // 根据用户的日期和时间来判断可用教室数量


int main(int argc, char const *argv[])
{
    char account_file[] = "./name_and_password.txt";
    char Classroom_info[] = "Classroom_info.txt";

    // login function

    // if (userlogin(account_file) == 1)
    // {
    //     printf("login fail!");
    //     return 0;
    // }
    // printf("success!\n");


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

    txtcreater(Classroom_info, &userorder);

    struct room_ini room;

    txtreader(&userorder, &room);
    printf("read success!\n");
    
    return 0;
}
