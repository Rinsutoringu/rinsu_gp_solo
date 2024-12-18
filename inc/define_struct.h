#pragma once

struct destine_time
{
    char date[30];
    int time;
    char today_date[30];
    char tomorrow_date[30];
    char acquired_date[30];
};

struct room_time_t
{
    char date[10];
    int booked[17]; // booked[9]==0
};

struct room_ini
{
    char roomid[10];
    int roomsize;
    struct room_time_t room_time_0;
    struct room_time_t room_time_1;
    struct room_time_t room_time_2;
};
