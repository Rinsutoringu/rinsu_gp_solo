#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <direct.h>
#include <dirent.h>
#include <unistd.h>
#include "../inc/define_struct.h"

/*
#####################################

用于搜索可用教室的函数

返回值为一个指针，当指针为NULL时，意味着没有匹配上教室
当指针为一个字符串时，成功匹配最小教室

#####################################
*/
char *roomseacher(int room_number, struct destine_time *userorder, struct room_ini **savefile)
{
    int user_input;
    int suitable[1000] = {0};
    int index = 0;
    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
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
            // printf("保存的房间大小是%d\n", savefile[i]->roomsize);

            // 完成日期与小时匹配
            if ((findstuct->booked)[userorder->time] == 0)
            {
                suitable[index] = i;
                index++;
                // printf("房间%s在%d时段没有被预定\n", savefile[suitable[index]]->roomid, userorder->time);
            }
            // 教室不合适，下一间
            else
                // printf("房间%s在%d时段已经被预定\n", savefile[i]->roomid, userorder->time);
                continue;
        }
    }

    if (index == 0)
    {
        // printf("没有合适的房间\n");
        return NULL;
    }
    
    for (int i = 0; i < index; i++)
    {
        // printf("房间%s在%d时段没有被预定\n", savefile[suitable[i]]->roomid, userorder->time);
    }
    for (int i = 0; i < index - 1; i++)
    {
        for (int j = 0; j < index - i - 1; j++)
        {
            if (savefile[suitable[j]]->roomsize > savefile[suitable[j + 1]]->roomsize)
            {
                int temp = suitable[j];
                suitable[j] = suitable[j + 1];
                suitable[j + 1] = temp;
            }
        }
    }
    // printf("以下输出为完成冒泡排序的结果\n");
    for (int i = 0; i < index; i++)
    {
        // printf("容量为%d的房间%s在%d时段没有被预定\n",savefile[suitable[i]]->roomsize, savefile[suitable[i]]->roomid, userorder->time);
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
    // printf("最终选择的教室是%s,时段%d被预定,日期为%s\n", savefile[suitable[0]]->roomid, userorder->time, userorder->date);

    // 构建文件路径
    char file_path[100] = {0};
    char line[100] = {0};
    char date_matchline[13] = {0};
    char time_matchline[8] = {0};
    char write_line[16] = {0};
    char buffer[1000] = {0};
    int flag = 0;

    snprintf(date_matchline, sizeof(date_matchline), "[%s]\n", userorder->date);
    snprintf(time_matchline, sizeof(time_matchline), "clock%d", userorder->time);
    snprintf(write_line, sizeof(write_line), "clock%d=booked\n", userorder->time);

    // printf("date_matchline is %s\n", date_matchline);
    // printf("time_matchline is %s\n", time_matchline);

    snprintf(file_path, sizeof(file_path), "./config/%s.txt", savefile[suitable[0]]->roomid);
    // printf("path is %s\n", file_path);

    FILE *file = fopen(file_path, "r");
    if (file == NULL)
    {
        perror("File open fail");
        return NULL;
    }
    while (fgets(line, sizeof(line), file))
    {
        // printf("line is %s\n", line);
        if (strstr(line, date_matchline) != NULL)
        {
            flag = 1;
        }
        if (flag == 1)
        {
            if (strstr(line, time_matchline) != NULL)
            {
                strcpy(line, write_line);
                // printf("line change finish\n");
                flag = 0;
            }
        }
        strcat(buffer, line);
    }
    fclose(file);
    fopen(file_path, "w");
    fprintf(file, "%s", buffer);
    fclose(file);

    // printf("room %s is booked\n", savefile[suitable[0]]->roomid);
    return savefile[suitable[0]]->roomid;
}