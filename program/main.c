#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
// #include"../function/userlogin/userlogin.h"
/*
##############################################


正确登录后，程序应该开始让用户选择登录日期和选择具体时间

函数返回一个结构体，这样更易于理解

##############################################
*/

struct destine_time
{
    int date;
    int time;
};

int userdestine(struct destine_time time);


int main(int argc, char const *argv[])
{

    // if (userlogin() == 1)
    // {
    //     printf("login fail!");
    //     return 0;
    // }
    // printf("success!");
    struct destine_time userorder;
    userdestine(userorder);
    return 0;
}

int userdestine(struct destine_time ordertime)
{
    time_t rawtime;  
    struct tm * timeinfo;  
  
    time(&rawtime);  
    timeinfo = localtime(&rawtime);  
    char today_time[80];
    char tomorrow_time[80];
    char acquired_time[80];
    snprintf(today_time, sizeof(today_time),
        "%04d.%02d.%02d",
        timeinfo->tm_year + 1900,  // 年份是从1900年开始的，所以要+1900  
        timeinfo->tm_mon + 1,  // 月份是从0开始的，所以要+1  
        timeinfo->tm_mday);  

    timeinfo->tm_mday++;
    mktime(timeinfo);
    snprintf(tomorrow_time, sizeof(today_time),
        "%04d.%02d.%02d",
        timeinfo->tm_year + 1900,  // 年份是从1900年开始的，所以要+1900  
        timeinfo->tm_mon + 1,  // 月份是从0开始的，所以要+1  
        timeinfo->tm_mday);  

    timeinfo->tm_mday++;
    mktime(timeinfo);
    snprintf(acquired_time, sizeof(today_time),
        "%04d.%02d.%02d",
        timeinfo->tm_year + 1900,  // 年份是从1900年开始的，所以要+1900  
        timeinfo->tm_mon + 1,  // 月份是从0开始的，所以要+1  
        timeinfo->tm_mday);  

    printf("Which day you want order?\n");
    printf("1. %s\n2. %s\n3. %s\n4. exit\n", today_time, tomorrow_time, acquired_time);

    // 初始化用户日期选项
    int date_select;
    // 选项编号
    int number = 0;
    // 初始化用户选项
    int select_time = 0;

    scanf("%d", &date_select);
    if (date_select == 4)
    {
        return 1;
    }

    switch (date_select)
    {
    case 1:
        printf("you choose today!\n");

        // 调试点
        printf("input test minute\n");
        scanf("%d", &(timeinfo->tm_min));
        printf("input test hour\n");
        scanf("%d", &(timeinfo->tm_hour));    

        // 以下为时间处理逻辑，返回的东西是24小时制的*用户所预定的时段*

        int hour = timeinfo->tm_hour;
        if ((timeinfo->tm_min)>0)
        {
            hour+=1;
        }
        int logintime = hour;

        if (hour < 9)
        {
            hour = 9;
        }
        
        for (int i = hour; i < 17; i++)
        {
            number++;

            if (i == 12)
            {
                printf("%d. %d:00 pm - %d:50 pm\n", number, i, i);
            }
            else if (i>12)
            {
                int n = i;
                n-=12;
                printf("%d. %d:00 pm - %d:50 pm\n", number, n, n);
            }
            else
            {
                printf("%d. %d:00 am - %d:50 am\n", number, i, i);
            }
        }
        printf("9. 退出\n");
        
        scanf("%d", &select_time);
        if (select_time == 9)
        {
            printf("user exit.\n");
            return 1;
        }
        else
        {
            // 补齐选项与实际时间的差值
            select_time+=8;
            if (logintime > 9)
            {
                // 用户的选项编号+登录的时间差
                select_time+=(logintime-9);
            }
            // 现在select_time变量存储的值就是用户选择的实际时间了(以24小时制存储)。
            printf("%d",select_time);
        }
        printf("your select time is %d", select_time);
        break;

    case 2:
        printf("you choose tomorrow!\n");

        for (int i = 9; i < 17; i++)
        {
            number++;
            if (i<12)
            {
                printf("%d. %d:00 am - %d:50 am\n", number, i, i);
            }
            else if (i==12)
            {
                printf("%d. %d:00 pm - %d:50 pm\n", number, i, i);
            }
            else if (i>12)
            {
                int n = i;
                n-=12;
                printf("%d. %d:00 pm - %d:50 pm\n", number, n, n);
            }
        }
        printf("9. 退出\n");

        // 菜单打印完成，下方开始接收用户输入
        scanf("%d", &select_time);
        // 当用户选择9时将退出
        if (select_time == 9)
        {
            printf("user exit.\n");
            return 1;
        }
        else if (select_time<9)
        {
            select_time+=8;
        }
        printf("your select time is %d", select_time);

        
        break;

    case 3:
        printf("you choose acquired!\n");



        for (int i = 9; i < 17; i++)
        {
            number++;
            if (i<12)
            {
                printf("%d. %d:00 am - %d:50 am\n", number, i, i);
            }
            else if (i==12)
            {
                printf("%d. %d:00 pm - %d:50 pm\n", number, i, i);
            }
            else if (i>12)
            {
                int n = i;
                n-=12;
                printf("%d. %d:00 pm - %d:50 pm\n", number, n, n);
            }
        }
        printf("9. 退出\n");

        // 菜单打印完成，下方开始接收用户输入
        scanf("%d", &select_time);
        // 当用户选择9时将退出
        if (select_time == 9)
        {
            printf("user exit.\n");
            return 1;
        }
        else if (select_time<9)
        {
            select_time+=8;
        }
        printf("your select time is %d", select_time);

        break;

    default:
        break;
    }
}
