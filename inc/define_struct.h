#pragma once


// 这里存储用户所输入的预定时间
struct destine_time
{
    char date[30];
    int time;
    char today_date[30];
    char tomorrow_date[30];
    char acquired_date[30];
};


// 这里存储房间的具体状态值
struct room_time_t
{
    char date[11];
    int booked[17]; // booked[9]==0
};


// 这里存储房间的大概信息，包含另一个结构体
struct room_ini
{
    char roomid[10];
    int roomsize;
    struct room_time_t room_time_0;
    struct room_time_t room_time_1;
    struct room_time_t room_time_2;
};
