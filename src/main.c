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

    // int need_size;
    // printf("please input room size you want.\n");
    // scanf("%d", need_size);

    // // 根据用户的日期和时间来判断可用教室数量

int txtreader(struct destine_time *ordertime, struct room_ini *room);

int txtreader(struct destine_time *ordertime, struct room_ini *room)
{

    // 遍历config文件夹下的所有文件
    char *directory_path = "./config";
    DIR *dir = opendir(directory_path);
    struct dirent *entry;

    if (dir == NULL) {
        perror("path open fail");
        return 1; // Exit the function if the directory cannot be opened
    }

    while ((entry = readdir(dir)) != NULL) {
        // 检查文件扩展名是否为 .txt
        if (strstr(entry->d_name, ".txt") != NULL) {
            // 构建文件路径
            char file_path[100];
            snprintf(file_path, sizeof(file_path), "%s/%s", directory_path, entry->d_name);

            // 打开文件
            FILE *file = fopen(file_path, "r");
            if (file == NULL) {
                perror("File open fail");
                continue; // 尝试打开下一个文件
            }
            printf("File open successed: %s\n", file_path);

            int line_number = 0;
            char line[100] = {0};
            char currentDate[20] = {0};
            char room_id[5] = {0};
            char room_size[5] = {0};
            while (fgets(line, sizeof(line), file))
            {
                line_number++;
                printf("开始循环获取每一行, 现在是第%d行\n", line_number);

                // 查找换行符和回车，替换为0
                line[strcspn(line, "\r\n")] = 0;

                // 找到房间详细信息行
                if (strstr(line, "roomid") != NULL)
                {
                    sscanf(line, "roomid=%s", room_id);
                }
                else if (strstr(line, "roomsize") != NULL)
                {
                    sscanf(line, "roomsize=%s", room_size);
                }
                
                // 找到配置行
                else if (line[0] == '[')
                {
                    sscanf(line, "[%10[^]]]", currentDate);
                    strcpy(room->room_time.date, currentDate);
                    printf("This group date is %s\n", room->room_time.date);
                }

                // 找到时间显示行
                else if (strstr(line, "clock") != NULL)
                {
                    int clock_time = 0;
                    char status[10] = {0};
                    sscanf(line, "clock%d=%s", &clock_time, status);
                    if (strcmp(status, "idle") == 0)
                    {
                        room->room_time.booked[clock_time] = 0;
                    }
                    else
                    {
                        room->room_time.booked[clock_time] = 1;
                    }
                    printf("read %d o'clock status turns to %d\n", clock_time, room->room_time.booked[clock_time]);
                    
                }

            }
            printf("This room id is %s, size is %s\n", room_id, room_size);


            // 关闭文件
            fclose(file);
        }
        else
        {
            printf("it is null\n");
        }
        
    }

    closedir(dir);

    printf("program runs to here");
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
