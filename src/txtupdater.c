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

用于检测配置文件中的日期，删除过期的部分
如果整个文件都过期了，就删除整个文件

##############################################
*/
int txtupdater(int a)
{
    // printf("update start!\n");
    // 先拿到今天的日期配置文件
    // 然后逐个打开config目录下的文件
    // 逐行读取，找到日期匹配的行
    // 与今天的日期比对
    // 如果日期晚于今天就删掉这个文件
    int file_number;
    char line[500] = {0};
    char status[200] = {0};
    int flag = 0;
    char buffer[1000] = {0};

    // 遍历config文件夹下的所有文件
    char *directory_path = "./config";
    DIR *dir = opendir(directory_path);
    struct dirent *entry;

        time_t rawtime;  
    struct tm * timeinfo;  
  
    time(&rawtime);  
    timeinfo = localtime(&rawtime);

    char acquired_date[80];
    char tomorrow_date[80];
    char today_date[80];
    char yesterday_date[80];
    char before_date[80];

    snprintf(today_date, sizeof(today_date),
        "%04d.%02d.%02d",
        timeinfo->tm_year + 1900,  // 年份是从1900年开始的，所以要+1900  
        timeinfo->tm_mon + 1,  // 月份是从0开始的，所以要+1  
        timeinfo->tm_mday);  

    timeinfo->tm_mday--;
    mktime(timeinfo);
    snprintf(yesterday_date, sizeof(today_date),
        "%04d.%02d.%02d",
        timeinfo->tm_year + 1900,  // 年份是从1900年开始的，所以要+1900  
        timeinfo->tm_mon + 1,  // 月份是从0开始的，所以要+1  
        timeinfo->tm_mday);  

    timeinfo->tm_mday--;
    mktime(timeinfo);
    snprintf(before_date, sizeof(today_date),
        "%04d.%02d.%02d",
        timeinfo->tm_year + 1900,  // 年份是从1900年开始的，所以要+1900  
        timeinfo->tm_mon + 1,  // 月份是从0开始的，所以要+1  
        timeinfo->tm_mday);  

    timeinfo->tm_mday+=3;
    mktime(timeinfo);
    snprintf(tomorrow_date, sizeof(today_date),
        "%04d.%02d.%02d",
        timeinfo->tm_year + 1900,  // 年份是从1900年开始的，所以要+1900  
        timeinfo->tm_mon + 1,  // 月份是从0开始的，所以要+1  
        timeinfo->tm_mday);  

    timeinfo->tm_mday++;
    mktime(timeinfo);
    snprintf(acquired_date, sizeof(today_date),
        "%04d.%02d.%02d",
        timeinfo->tm_year + 1900,  // 年份是从1900年开始的，所以要+1900  
        timeinfo->tm_mon + 1,  // 月份是从0开始的，所以要+1  
        timeinfo->tm_mday);  


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
            // 追踪文件数量
            file_number++;


            // printf("File open successed: %s\n", file_path);
            while (fgets(line, sizeof(line), file))
            {
                line[strcspn(line, "\r\n")] = 0;
                // 找到时间信息行
                
                if (strstr(line, "[") != NULL)
                {
                    sscanf(line, "[%10s]\n", status);
                    // printf("status is %s\n", status);
                    
                    // 判断文件中存储的第一份信息是否是今天
                    if (strstr(status, today_date) != NULL)
                    {
                        break;
                    }
                    else if (strstr(status, yesterday_date) != NULL)
                    {
                        flag = 1;
                        break;
                    }
                    else if (strstr(status, before_date) != NULL)
                    {
                        flag = 2;
                        break;
                    }
                    else
                    {
                        flag = 3;
                        break;
                    }
                }
            }
            fclose(file);

            if (flag == 1)
            {
                // 以写模式打开文档
                FILE * file = fopen(file_path, "r");
                if (file == NULL)
                {
                    perror("File open fail");
                    continue;
                }
                // 读取文件内容
                int line_counter = 0;
                // 读取文件内容
                while (fgets(line, sizeof(line), file))
                {
                    // printf("line is %s\n", line);


                    // 如果找到昨天的日期，就跳过10行（要更新日期的，
                    // 不能把旧的数据写进去）
                    if (strstr(line, yesterday_date) != NULL)
                    {
                        line_counter = 10;
                        memset(line, 0, sizeof(line));
                    }
                    if (line_counter > 0)
                    {
                        line_counter--;
                        // memset是为了清空line数组，避免后续strcat时出现问题
                        memset(line, 0, sizeof(line));
                        continue;
                    }

                    
                    strcat(buffer, line);
                }
                snprintf(line, sizeof(line), 
                    "\n"
                    "[%s]\n"
                    "clock9=idle\n"
                    "clock10=idle\n"
                    "clock11=idle\n"
                    "clock12=idle\n"
                    "clock13=idle\n"
                    "clock14=idle\n"
                    "clock15=idle\n"
                    "clock16=idle\n"
                    , 
                    acquired_date);
                strcat(buffer, line);
                fclose(file);
                file = fopen(file_path, "w");
                fprintf(file, "%s", buffer);
                fclose(file);
                flag = 0;
                memset(buffer, 0, sizeof(buffer));
            }


            else if (flag == 2)
            {
                // 以写模式打开文档
                FILE * file = fopen(file_path, "r");
                if (file == NULL)
                {
                    perror("File open fail");
                    continue;
                }
                // 读取文件内容
                int line_counter = 0;
                // 读取文件内容
                while (fgets(line, sizeof(line), file))
                {
                    // printf("%s\n", line);


                    // 如果找到昨天的日期，就跳过10行（要更新日期的，
                    // 不能把旧的数据写进去）
                    if (strstr(line, before_date) != NULL)
                    {
                        line_counter = 20;
                        memset(line, 0, sizeof(line));
                    }
                    if (line_counter > 0)
                    {
                        line_counter--;
                        // memset是为了清空line数组，避免后续strcat时出现问题
                        memset(line, 0, sizeof(line));
                        continue;
                    }

                    
                    strcat(buffer, line);
                }
                snprintf(line, sizeof(line), 
                    "\n"
                    "[%s]\n"
                    "clock9=idle\n"
                    "clock10=idle\n"
                    "clock11=idle\n"
                    "clock12=idle\n"
                    "clock13=idle\n"
                    "clock14=idle\n"
                    "clock15=idle\n"
                    "clock16=idle\n"
                    "\n"
                    "[%s]\n"
                    "clock9=idle\n"
                    "clock10=idle\n"
                    "clock11=idle\n"
                    "clock12=idle\n"
                    "clock13=idle\n"
                    "clock14=idle\n"
                    "clock15=idle\n"
                    "clock16=idle\n"
                    , 
                    tomorrow_date,
                    acquired_date);
                strcat(buffer, line);
                fclose(file);
                file = fopen(file_path, "w");
                fprintf(file, "%s", buffer);
                fclose(file);
                flag = 0;
                memset(buffer, 0, sizeof(buffer));
            }
            else if (flag == 3)
            {
                remove(file_path);
                // printf("delete file %s\n", file_path);
            }
            

        }

    
    }
    return 0;
}