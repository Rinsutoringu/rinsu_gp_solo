#pragma once

struct destine_time
{
    char date[30];
    int time;
    char today_date[30];
    char tomorrow_date[30];
    char acquired_date[30];
};

struct room_time
{
    char date[30];
    int clock9;
    int clock10;
    int clock11;
    int clock12;
    int clock13;
    int clock14;
    int clock15;
    int clock16;
};

struct room_ini
{
    int roomsize;
    struct room_time;
};
