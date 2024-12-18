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
    int suitable[room_number];
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
                // 符合要求的可用房间存入suitable数组中
                (suitable[index]) = i;
                printf("发现合格教室%d, 索引%d\n", suitable[index], index);
                index++;
            }
            // 没有合适的教室
            // else return NULL;
            
        }
    }
    int temp = 0;
    // 应用基础的冒泡排序
    for (int i = 0; i < index - 1; i++) {
        for (int j = 0; j < index - i - 1; j++) {
            int current = suitable[j];
            int next = suitable[j + 1];

            // 比较当前元素和下一个元素的大小
            if (savefile[current]->roomsize > savefile[next]->roomsize) {
                // 如果当前元素大于下一个元素，则交换它们
                // temp = savefile[current]->roomsize;
                // savefile[current]->roomsize = savefile[next]->roomsize;
                // savefile[next]->roomsize = temp;

                // 同时交换 suitable 数组中的索引，以保持追踪
                temp = suitable[j];
                suitable[j] = suitable[j + 1];
                suitable[j + 1] = temp;
            }
        }
    }

    printf("排序后输出的有效值为\n");
    for (int i = 0; i < index; i++) {
        printf("%d ", savefile[i]->roomsize);
    }
    printf("\n");
    char *room_name = (savefile[0]->roomid);
    if (userorder->date == userorder->today_date)
    {
        findstuct = &(savefile[0]->room_time_0);
    }
    else if (userorder->date == userorder->tomorrow_date)
    {
        findstuct = &(savefile[0]->room_time_1);
    }
    else if (userorder->date == userorder->acquired_date)
    {
        findstuct = &(savefile[0]->room_time_2);
    }
    findstuct->booked[userorder->time]=1;

            // 构建文件路径
            char file_path[100];
            char line[100];
            snprintf(file_path, sizeof(file_path), "./config/%s.txt", savefile[0]->roomid);
            printf("path is %s\n", file_path);

            // 打开并处理文件
            FILE *file = fopen(file_path, "w");
            char dayconfig[830];
            // snprintf(dayconfig, sizeof(dayconfig),"this is a test %d", savefile[0]->roomsize);
            // fprintf(file, "%s", dayconfig);
            // fclose(file);
            char **sign[300];
            char c_idle[] = "idle";
            char c_booked[] = "booked";
            int k = 0;
            for (int j = 0; j < 3; j++)
            {
                for (int i = 9; i < 17; i++)
                {
                    if (savefile[j]->room_time_0.booked[i] == 0)
                    {
                        *sign[k] = c_idle;
                    }
                    else
                    {
                        *sign[k] = c_booked;
                    }
                    

                    printf(" the sign is %s\n", *sign[k]);
                    k++;
                }                
            }
            

            snprintf(dayconfig, sizeof(dayconfig), 
                "roomid=%s\n"
                "roomsize=%d\n"
                "\n"
                "[%s]\n"
                "clock9=%d\n"
                "clock10=%d\n"
                "clock11=%d\n"
                "clock12=%d\n"
                "clock13=%d\n"
                "clock14=%d\n"
                "clock15=%d\n"
                "clock16=%d\n"
                "\n"
                "[%s]\n"
                "clock9=%d\n"
                "clock10=%d\n"
                "clock11=%d\n"
                "clock12=%d\n"
                "clock13=%d\n"
                "clock14=%d\n"
                "clock15=%d\n"
                "clock16=%d\n"
                "\n"
                "[%s]\n"
                "clock9=%d\n"
                "clock10=%d\n"
                "clock11=%d\n"
                "clock12=%d\n"
                "clock13=%d\n"
                "clock14=%d\n"
                "clock15=%d\n"
                "clock16=%d\n", 
                &savefile[0]->roomid,
                savefile[0]->roomsize,

                &savefile[0]->room_time_0.date,
                savefile[0]->room_time_0.booked[9],
                savefile[0]->room_time_0.booked[10],
                savefile[0]->room_time_0.booked[11],
                savefile[0]->room_time_0.booked[12],
                savefile[0]->room_time_0.booked[13],
                savefile[0]->room_time_0.booked[14],
                savefile[0]->room_time_0.booked[15],
                savefile[0]->room_time_0.booked[16],

                &savefile[0]->room_time_1.date,
                savefile[0]->room_time_1.booked[9],
                savefile[0]->room_time_1.booked[10],
                savefile[0]->room_time_1.booked[11],
                savefile[0]->room_time_1.booked[12],
                savefile[0]->room_time_1.booked[13],
                savefile[0]->room_time_1.booked[14],
                savefile[0]->room_time_1.booked[15],
                savefile[0]->room_time_1.booked[16],

                &savefile[0]->room_time_2.date,
                savefile[0]->room_time_2.booked[9],
                savefile[0]->room_time_2.booked[10],
                savefile[0]->room_time_2.booked[11],
                savefile[0]->room_time_2.booked[12],
                savefile[0]->room_time_2.booked[13],
                savefile[0]->room_time_2.booked[14],
                savefile[0]->room_time_2.booked[15],
                savefile[0]->room_time_2.booked[16]
                );
            fprintf(file, "%s", dayconfig);
            fclose(file);

    
    

    return room_name;


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

    char *room_name = roomseacher(room_number, &userorder, savefile);
    // room_name
    if (room_name == NULL)
    {
        printf("Sorry, we can't match your classroom.\n");
    }
    

    return 0;
}
