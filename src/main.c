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


int roomseacher(int room_number, struct destine_time *userorder, struct room_ini **savefile);
int roomseacher(int room_number, struct destine_time *userorder, struct room_ini **savefile)
{
    int user_input;
    int *suitable[room_number];
    int index = 0;
    printf("please input room size\n");
    scanf("%d", &user_input);
    // 先判断教室大小是否符合要求
    struct room_time_t *findstuct = NULL;
    // 一个简单的状态机，拼接结构体访问语句，根据用户的预定时间来访问指定的成员
    
    for (int i = 0; i < room_number; i++)
    {
        if (strcmp(userorder->date, userorder->today_date) == 0)
        {
            findstuct = &(savefile[i]->room_time_0);
        }
        else if (strcmp(userorder->date, userorder->tomorrow_date) == 0)
        {
            findstuct = &(savefile[i]->room_time_1);
        }
        else if (strcmp(userorder->date, userorder->acquired_date) == 0)
        {
            findstuct = &(savefile[i]->room_time_2);
        }

        if (((savefile[i]->roomsize) > user_input) || ((savefile[i]->roomsize) == user_input))
        {
            printf("保存的房间大小是%d\n", savefile[i]->roomsize);
            if ((findstuct->booked)[userorder->time] == 0)
            {
                // 符合要求的可用房间存入suitable数组中
                (suitable[index]) = &i;
                printf("发现合格教室%d\n", i);
                index++;
            }
        }
    }
    int temp = 0;
    int a = 0;
    // 应用基础的冒泡排序
    for (int i = 0; i < index-1; i++)
    {
        for (int j = 0; j < i-1; j++)
        {
            a = *(suitable[i]);
            printf("room size is %d\n", savefile[a]->roomsize);
            if ((savefile[a]->roomsize) > (savefile[a+1]->roomsize))
            {
                temp = (savefile[*suitable[i+1]]->roomsize);
                savefile[*suitable[i+1]]->roomsize = savefile[*suitable[i]]->roomsize;
                savefile[*suitable[i]]->roomsize = temp;
            }
            
        }
    }

    for (int i = 0; i < index; i++)
    {
        printf("排序后输出的有效值为\n");
        printf("%d", savefile[*suitable[i]]);
        printf("\n");
    }
    
    return 0;
}

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
    struct room_ini room;

    // 函数userdestine的返回值，返回2代表用户选择退出
    // 返回其他非0值代表用户登录出错，返回0代表成功登录
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

    // 函数txtcreater的返回值，返回-1代表没找到配置文件，返回文件数量代表生成成功
    int room_number = txtcreater(Classroom_info, &userorder);
    if (room_number == -1)
    {
        printf("程序根目录未发现教室配置文件！请检查后重试\n");
        return 0;
    }
    printf("有%d份教室配置文件\n", room_number);

    // 函数txtreader的返回值，返回NULL代表读取失败，返回一个结构体指针数组代表读取成功，room_number为其索引
    struct room_ini **savefile = txtreader(&userorder, &room, room_number);
    if (savefile == NULL)
    {
        ("read fail!\n");
    }
    printf("read success!\n");

    roomseacher(room_number, &userorder, savefile);

    return 0;
}
