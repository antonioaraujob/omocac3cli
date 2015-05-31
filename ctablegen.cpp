#include "ctablegen.h"

CTableGen::CTableGen(int ch, double min, double max, double ap, double indA, double indB, double indC)
{
    channel = ch;
    minChannelTime = min;
    maxChannelTime = max;
    aps = ap;
    indexA = indA;
    indexB = indB;
    indexC = indC;
}

CTableGen::CTableGen(const CTableGen &g)
{
    channel = g.getChannel();
    minChannelTime = g.getMinChannelTime();
    maxChannelTime = g.getMaxChannelTime();
    aps = g.getAPs();
    indexA = g.getIndexA();
    indexB = g.getIndexB();
    indexC = g.getIndexC();
}

CTableGen::~CTableGen()
{
}

double CTableGen::getChannel() const
{
    return channel;
}

void CTableGen::setChannel(int ch)
{
    channel = ch;
}

double CTableGen::getMinChannelTime() const
{
    return minChannelTime;
}

void CTableGen::setMinChannelTime(double min)
{
    minChannelTime = min;
}

double CTableGen::getMaxChannelTime() const
{
    return maxChannelTime;
}

void CTableGen::setMaxChannelTime(double max)
{
    maxChannelTime = max;
}

double CTableGen::getAPs() const
{
    return aps;
}

void CTableGen::setAPs(double ap)
{
    aps = ap;
}

double CTableGen::getIndexA() const
{
    return indexA;
}

void CTableGen::setIndexA(double indA)
{
    indexA = indA;
}

void CTableGen::calculateIndexA()
{
    double foa = (aps/minChannelTime)*0.20 + (aps/maxChannelTime)*0.80;
    indexA = foa;
}

double CTableGen::getIndexB() const
{
    return indexB;
}

void CTableGen::setIndexB(double indB)
{
    indexB = indB;
}

void CTableGen::calculateIndexB()
{
    double fob = (aps/minChannelTime)*0.40 + (aps/maxChannelTime)*0.60;
    indexB = fob;
}

double CTableGen::getIndexC() const
{
    return indexC;
}

void CTableGen::setIndexC(double indC)
{
    indexC = indC;
}

void CTableGen::calculateIndexC()
{
    double foc = (aps/minChannelTime)*0.60 + (aps/maxChannelTime)*0.40;
    indexC = foc;
}
