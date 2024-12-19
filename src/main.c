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


char* roomseacher(int room_number, struct destine_time *userorder, struct room_ini **savefile);


/*
#####################################

用于搜索可用教室的函数

返回值为一个指针，当指针为NULL时，意味着没有匹配上教室
当指针为一个字符串时，成功匹配最小教室

#####################################
*/
char* roomseacher(int room_number, struct destine_time *userorder, struct room_ini **savefile)
{
    int user_input;
    int suitable[1000] = {0};
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

            // 完成日期与小时匹配
            if ((findstuct->booked)[userorder->time] == 0)
            {
                suitable[index] = i;
                index++;
                // printf("房间%s在%d时段没有被预定\n", savefile[suitable[index]]->roomid, userorder->time);
            }
            // 没有合适的教室
            else return NULL;
        }
    }
    for (int i = 0; i < index; i++)
    {
        printf("房间%s在%d时段没有被预定\n", savefile[suitable[i]]->roomid, userorder->time);
    }
    for (int i = 0; i < index-1; i++)
    {
        for (int j = 0; j < index-i-1; j++)
        {
            if (savefile[suitable[j]]->roomsize > savefile[suitable[j+1]]->roomsize)
            {
                int temp = suitable[j];
                suitable[j] = suitable[j+1];
                suitable[j+1] = temp;
            }
        }
    }
    printf("以下输出为完成冒泡排序的结果\n");
    for (int i = 0; i < index; i++)
    {    
        printf("容量为%d的房间%s在%d时段没有被预定\n",savefile[suitable[i]]->roomsize, savefile[suitable[i]]->roomid, userorder->time);
    }
    

    // 选择最小的教室,并且将其时间段标记为已预定
    
    if (strcmp(userorder->date, savefile[suitable[0]]->room_time_0.date) == 0)
    {
        savefile[suitable[0]]->room_time_0.booked[userorder->time] = 1;
    }
    else if (strcmp(userorder->date, savefile[suitable[0]]->room_time_1.date) == 0)
    {
        savefile[suitable[0]]->room_time_1.booked[userorder->time] = 1;
    }
    else if (strcmp(userorder->date, savefile[suitable[0]]->room_time_1.date) == 0)
    {
        savefile[suitable[0]]->room_time_2.booked[userorder->time] = 1;
    }
    printf("最终选择的教室是%s,时段%d被预定,日期为%s\n", savefile[suitable[0]]->roomid, userorder->time, userorder->date);
    
    // 构建文件路径
    char file_path[100];
    char line[100];
    snprintf(file_path, sizeof(file_path), "./config/%s.txt", savefile[0]->roomid);
    printf("path is %s\n", file_path);
    return NULL;
}

int main(int argc, char const *argv[])
{
    char account_file[] = "../src/account.txt";
    char Classroom_info[] = "classroom_info.txt";

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

    char *room_name = roomseacher(room_number, &userorder, savefile);
    // room_name
    if (room_name == NULL)
    {
        // printf("Sorry, we can't match your classroom.\n");
    }
    

    return 0;
}
