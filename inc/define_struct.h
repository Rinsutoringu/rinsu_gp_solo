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
    char date[30];
    int booked[24]; // booked[9]==0
};

struct room_ini
{
    int roomsize;
    struct room_time_t room_time;
};
