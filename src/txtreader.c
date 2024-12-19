#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <direct.h>
#include <dirent.h>
#include <unistd.h>
#include "../inc/define_struct.h"

/*
##############################################

读取config文件夹下的所有文件，存储为结构体
每个母结构体包含三个子结构体

母结构体中包含
    char roomid[10];
    int roomsize;
    struct room_time_t room_time_0;
    struct room_time_t room_time_1;
    struct room_time_t room_time_2;

子结构体中包含
    char date[10];
    int booked[17];

此外，函数还检测了配置文件的合法性，如果配置文件存在错误，函数将会报错。

##############################################
*/
struct room_ini ** txtreader(struct destine_time *ordertime,int room_number)
{
    struct room_ini room;
    int file_number = 0;
    struct room_ini **savefile = (struct room_ini **)malloc(sizeof(struct room_ini *)*room_number);

    // 遍历config文件夹下的所有文件
    char *directory_path = "./config";
    DIR *dir = opendir(directory_path);
    struct dirent *entry;

    if (dir == NULL) {
        perror("path open fail");
        return NULL; // Exit the function if the directory cannot be opened
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
            // printf("File open successed: %s\n", file_path);

            savefile[file_number] = (struct room_ini *)malloc(sizeof(struct room_ini));

            int line_number = 0;
            char line[100] = {0};
            char currentDate[20] = {0};
            char room_id[5] = {0};
            char room_size[5] = {0};
            int date_counter = 0;
            struct room_time_t* room_time;

            while (fgets(line, sizeof(line), file))
            {
                switch (date_counter)
                {
                case 0:
                    room_time = &savefile[file_number]->room_time_0;
                    break;
                case 1:
                    room_time = &savefile[file_number]->room_time_1;
                    break;
                case 2:
                    room_time = &savefile[file_number]->room_time_2;
                    break;
                
                default:
                    break;
                }
                

                // 手动追踪当前读写的行数
                line_number++;
                // printf("开始循环获取每一行, 现在是第%d行\n", line_number);

                // 查找换行符和回车，替换为0
                line[strcspn(line, "\r\n")] = 0;

                // 找到房间详细信息行
                if (strstr(line, "roomid") != NULL)
                {
                    sscanf(line, "roomid=%s", &(savefile[file_number]->roomid));
                    // printf("This room id is %s\n", savefile[file_number]->roomid);
                }
                else if (strstr(line, "roomsize") != NULL)
                {
                    sscanf(line, "roomsize=%d", &savefile[file_number]->roomsize);
                }
                
                // 找到配置行
                else if (line[0] == '[')
                {
                    sscanf(line, "[%10[^]]]", currentDate);
                    strcpy(room_time->date, currentDate);
                    // printf("This group date is %s\n", room_time->date);
                }

                // 找到时间显示行
                else if (strstr(line, "clock") != NULL)
                {
                    // 在检测到这一行的时候，这一行的指针已经被存入程序，所以先把这一行的内容存入结构体中
                    // 检测到时间显示行时，日期一定已经被存储在内存中了
                    int clock_time = 0;
                    char status[10] = {0};
                    sscanf(line, "clock%d=%s", &clock_time, status);

                    if (strcmp(status, "idle") == 0)
                    {
                        room_time->booked[clock_time] = 0;
                    }
                    else
                    {
                        room_time->booked[clock_time] = 1;
                    }
                    // printf("read %d o'clock status turns to %d\n", clock_time, room_time->booked[clock_time]);
                    if (clock_time == 16)
                    {
                        date_counter++;
                    }
                }
            }
            file_number++;
            // printf("This room id is %s, size is %d\n", room->roomid, room->roomsize);

            // 关闭文件
            fclose(file);
            // printf("line number are %d\n", line_number);
            if (line_number != 32)
            {
                printf("config txt at %s is broken! to fix problem, delete it. \n", file_path);
            }
        char str[5];

        // printf("room number %s ,size %d in file %d\n", 
        //     savefile[file_number]->roomid, 
        //     savefile[file_number]->roomsize, 
        //     file_number);

        
        }      
    }
    closedir(dir);
    return savefile;
}