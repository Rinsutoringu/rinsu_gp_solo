#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <direct.h>
#include <dirent.h>
#include "../inc/userlogin.h"
#include "../inc/userdestine.h"
#include "../inc/define_struct.h"
#include "../inc/txtcreater.h"


int matchroom(struct destine_time *ordertime);

int matchroom(struct destine_time *ordertime)
{
    int need_size;
    printf("please input room size you want.\n");
    scanf("%d", need_size);

    // 根据用户的日期和时间来判断可用教室数量

    // 遍历config文件夹下的所有文件
    char *directory_path = "./config";
    DIR *dir = opendir(directory_path);
    struct dirent *entry;

    if (dir == NULL) {

        perror("path open fail");
    }

    while ((entry = readdir(dir)) != NULL) {
        // 检查文件扩展名是否为 .txt
        if (strstr(entry->d_name, ".txt") != NULL) {
            // 构建文件路径
            char file_path[1024];
            snprintf(file_path, sizeof(file_path), "%s/%s", directory_path, entry->d_name);

            // 打开文件
            FILE *file = fopen(file_path, "r");
            if (file == NULL) {
                perror("File open fail");
                continue; // 尝试打开下一个文件
            }

            // 在这里对文件进行处理
            printf("打开文件: %s\n", file_path);

            // 关闭文件
            fclose(file);
        }
    }

    closedir(dir);


    return 0;
}

int main(int argc, char const *argv[])
{
    char account_file[] = "./name_and_password.txt";
    char Classroom_info[] = "Classroom_info.txt";

    if (userlogin(account_file) == 1)
    {
        printf("login fail!");
        return 0;
    }
    printf("success!\n");
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

    matchroom(&userorder);
    
    
    return 0;
}
