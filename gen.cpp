#include "gen.h"

Gen::Gen()
{
    channel = 0;
    maxChannelTime = 0;
    minCHannelTime = 0;
    APs = 0;
}

Gen::~Gen()
{
}

Gen::Gen(int ch, int min, int max, int aps)
{
    channel = ch;
    maxChannelTime = min;
    minCHannelTime = max;
    APs = aps;
}

int Gen::getLatency()
{
    return minCHannelTime+maxChannelTime;
}

double Gen::getValue(int index)
{
    if (index ==0)
        return channel;
    else if (index == 1)
        return minCHannelTime;
    else if (index == 2)
        return maxChannelTime;
    else
        return APs;
}

void Gen::setChannel(int c)
{
    channel = c;
}

void Gen::setMinChannelTime(double min)
{
    minCHannelTime = min;
}

void Gen::setMaxChannelTime(double max)
{
    maxChannelTime = max;
}

void Gen::setAPs(double aps)
{
    APs = aps;
}
