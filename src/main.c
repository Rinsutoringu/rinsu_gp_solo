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
#include "../inc/roomseacher.h"
#include "../inc/txtupdater.h"
/*
##############################################

ver 0.2

##############################################
*/
int main(int argc, char const *argv[])
{

    struct destine_time userorder;
    struct room_ini room;
    
    char account_file[] = "../src/account.txt";
    char Classroom_info[] = "classroom_info.txt";

    int b = 1;
    // 用于更新配置文件
    txtupdater(b);

    // login function
    int login_state = userlogin(account_file);
    if (login_state == 1)
    {
        printf("your password or username is wrong. login fail!");
        return 0;
    }
    printf("login success!\n");
    // 函数userdestine的返回值，返回2代表用户选择退出
    // 返回其他非0值代表用户登录出错，返回0代表成功登录

    // 第二步所在位置
    label: signed;

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

    // printf("you order date is %s\n", userorder.date);
    // printf("you order time is %d\n", userorder.time);

    // 函数txtcreater的返回值，返回-1代表没找到配置文件，返回文件数量代表生成成功

    int txtupdater();

    int room_number = txtcreater(Classroom_info, &userorder);
    if (room_number == -1)
    {
        printf("程序根目录未发现教室配置文件！请检查后重试\n");
        return 0;
    }
    // printf("有%d份教室配置文件\n", room_number);

    // 函数txtreader的返回值，返回NULL代表读取失败，返回一个结构体指针数组代表读取成功，room_number为其索引
    struct room_ini **savefile = txtreader(&userorder, room_number);
    if (savefile == NULL)
    {
        ("read fail!\n");
        return 0;
    }
    // printf("read success!\n");

    char *booked_room = roomseacher(room_number, &userorder, savefile);
    if (booked_room == NULL)
    {
        printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
        printf("Sorry, The room type you require is already available.\n");
        printf("Continue (y/n)?\n");
        char a;
        while (1)
        {
            scanf("%c", &a);
            if (a == 'y')
            {
                goto label;
            }
            else if (a == 'n')
            {
                printf("see you next time!\n");
                return 0;
            }
            else
            {
                continue;
            }
        }
    }
    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
    printf("Your room number: %s\nYour order time: %d O'Clock start. (This reservation lasts 50 minutes, please plan your time in advance)\nYour order date: %s\n\n", booked_room, userorder.time, userorder.date);

    printf("Book another room? (y/n)\n");
    char a;
    while (1)
    {
        scanf("%c", &a);
        if (a == 'y')
        {
            printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
            goto label;
        }
        else if (a == 'n')
        {
            printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
            printf("see you next time!\n");
            return 0;
        }
        else
        {
            continue;
        }
    }
return 0;
}