#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <direct.h>
#include <unistd.h>
#include "../inc/define_struct.h"

/*
##############################################

根据教室列表文件
Classroom_info.txt
生成每间教室的配置文件

##############################################
*/
int txtcreater(char filename[], struct destine_time *ordertime)
{
    // char* arr[10];

    int i = 0;
    char *line = NULL;
    char buffer[100] = {0};

    // 从教室信息文件读取教室详情以用于生成教室配置文件
    FILE *file;
    file = fopen(filename, "r");
    if (file == NULL)
    {
        // printf("file open error\n");

        // 未发现存储教室信息的txt文档
        return -1;
    }
    // 获取文件行数
    while (fgets(buffer, 100, file) != NULL)
    {
        i++;
    }

    // 重置文件读写指针
    fseek(file, 0, SEEK_SET);

    // 创建存储文件内每一行字符串的数组
    char *getline[i];
    char *roomname[i];
    char *roomspace[i];

    // 获取存储文件每一行的字符串指针
    for (int n = 0; n < i; n++)
    {
        fgets(buffer, 100, file);
        buffer[strcspn(buffer, "\n")] = '\0';
        // 现在把文件的第一行读进了一个固定长度字符型数组里面
        line = (char *)malloc((strlen(buffer) + 1) * sizeof(char));
        strcpy(line, buffer);
        getline[n] = line;
    }

    const char *dir_name = "./config"; // 要创建的目录名
    
    if (_mkdir(dir_name) == -1)
    {
        // perror("path create fail(maybe it already exists?)");
    }
    

    for (int n = 0; n < i; n++)
    {
        roomname[n] = strtok(getline[n], " ");
        roomspace[n] = strtok(NULL, " ");
        // 打印获取到的房间信息
        // printf("The room name is %s\n", roomname[n]);
        // printf("The room space is %s\n", roomspace[n]);
        char ini_path[20] = {0};
        snprintf(ini_path, sizeof(ini_path), "./config/%s.txt", roomname[n]);

        // 如果文件已经存在，开始尝试生成下一个文件。
        if (access(ini_path, F_OK) == 0)
        {
            // perror("File already exist.");
            continue;
            
        }
        
        
        FILE * file = fopen(ini_path, "w");
        char dayconfig[830];
        snprintf(dayconfig, sizeof(dayconfig), 
            "roomid=%s\n"
            "roomsize=%s\n"
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
            "\n"
            "[%s]\n"
            "clock9=idle\n"
            "clock10=idle\n"
            "clock11=idle\n"
            "clock12=idle\n"
            "clock13=idle\n"
            "clock14=idle\n"
            "clock15=idle\n"
            "clock16=idle\n", 
            roomname[n],
            roomspace[n],
            ordertime->today_date,
            ordertime->tomorrow_date,
            ordertime->acquired_date);
        fprintf(file, "%s", dayconfig);
        fclose(file);
    }

    // i是生成的文件数量
    return i;
}