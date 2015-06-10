#include "ctable.h"
#include <QFile>
#include <QTextStream>


/**
 * @brief Funcion de comparacion de CTableGen con respecto al valor de indexA
 * @param gen11 gen 1 a comparar
 * @param gen2 gen 2 a comparar
 * @return Verdadero si gen1 es mayor que gen2 con respecto al indice A
 */
inline static bool gen1GreaterThanGen2ByIndexA(CTableGen * gen1, CTableGen * gen2)
{
    return gen1->getIndexA() > gen2->getIndexA();
}

/**
 * @brief Funcion de comparacion de CTableGen con respecto al valor de indexB
 * @param gen11 gen 1 a comparar
 * @param gen2 gen 2 a comparar
 * @return Verdadero si gen1 es mayor que gen2 con respecto al indice B
 */
inline static bool gen1GreaterThanGen2ByIndexB(CTableGen * gen1, CTableGen * gen2)
{
    return gen1->getIndexB() > gen2->getIndexB();
}

/**
 * @brief Funcion de comparacion de CTableGen con respecto al valor de indexC
 * @param gen11 gen 1 a comparar
 * @param gen2 gen 2 a comparar
 * @return Verdadero si gen1 es mayor que gen2 con respecto al indice C
 */
inline static bool gen1GreaterThanGen2ByIndexC(CTableGen * gen1, CTableGen * gen2)
{
    return gen1->getIndexC() > gen2->getIndexC();
}


CTable::CTable(int individualSize, int ctWindow, int index)
{
    cTableWindow = ctWindow;
    indexToSort = index;
}

CTable::~CTable()
{

}

void CTable::addSuperIndividual(QList<CTableGen *> superIndividualGenList, int indexToSort)
{

    int channel = 0;
    double min = 0;
    double max = 0;
    double aps = 0;
    double indexA = 0;
    double indexB = 0;
    double indexC = 0;
    CTableGen * gen;

    for (int i=0; i<superIndividualGenList.size(); i++){
        channel = superIndividualGenList.at(i)->getChannel();
        min = superIndividualGenList.at(i)->getMinChannelTime();
        max = superIndividualGenList.at(i)->getMaxChannelTime();
        aps = superIndividualGenList.at(i)->getAPs();
        indexA = superIndividualGenList.at(i)->getIndexA();
        indexB = superIndividualGenList.at(i)->getIndexB();
        indexC = superIndividualGenList.at(i)->getIndexC();
        gen = new CTableGen(channel, min, max, aps,indexA, indexB, indexC);
        genList.append(gen);
    }

    if (indexToSort == 0)
    {
        qSort(genList.begin(), genList.end(), gen1GreaterThanGen2ByIndexA);
    }else if (indexToSort == 1)
    {
        qSort(genList.begin(), genList.end(), gen1GreaterThanGen2ByIndexB);
    }else
    {
        qSort(genList.begin(), genList.end(), gen1GreaterThanGen2ByIndexC);
    }
}

QList<CTableGen *> CTable::getWindowGenes()
{
    QList<CTableGen *> windowGenesList;
    CTableGen * gen;
    for (int i=0; i<cTableWindow; i++ )
    {
        gen = genList.at(i);
        windowGenesList.append(gen);
    }
    return windowGenesList;
}


QList<CTableGen*> CTable::convertIndividualToCTableGen(Individual* ind)
{
    QList<CTableGen *> list;
    CTableGen * gen;
    int ch = 0;
    double min = 0;
    double max = 0;
    double aps = 0;
    for (int i=0; i< ind->getIndividualSize(); i++)
    {
        ch = ind->getParameter(i*4);
        min = ind->getParameter((i*4)+1);
        max = ind->getParameter((i*4)+2);
        aps = ind->getParameter((i*4)+3);
        gen = new CTableGen(ch, min, max, aps ,0, 0, 0);
        list.append(gen);
    }
    return list;
}


int CTable::searchChannelInList(int ch, QList<CTableGen *> list)
{
    int index = -1;
    for (int i=0; i<list.size(); i++)
    {
        if (list.at(i)->getChannel() == ch)
        {
            index = i;
            break;
        }
    }

    // si index == -1 no se encontro el canal en el offspring
    return index;
    //Q_ASSERT_X(true, "CTable::searchChannelInList", "Se esta buscando un canal en la lista de genes que no existe");
}

void CTable::clearCTable()
{
    // lista temporal de genes
    QList<CTableGen *> tmpList;

    CTableGen * gen;

    // agregar los genes del super individuo actual a la lista tmpList
    for (int i=0; i<genList.size(); i++){
        gen = new CTableGen(*genList.at(i));
        tmpList.append(gen);
    }

    // agregar la lista tmpList al registro historico
    historicSuperIndividualList.append(tmpList);

    // limpiar la lista del super individuo actual
    genList.clear();
}


void CTable::reportCTableHistory(QString resultsDirectory)
{
    // crear archivo de salida
    QFile outputFile(resultsDirectory+"/ctableHistory.txt");
    if (outputFile.exists())
    {
        outputFile.remove();
    }
    if (!outputFile.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Append))
    {
        QString msg = "No se pudo crear el archivo /tmp/.txt";
        Q_ASSERT_X(false, "CTable::reportCTableHistory", "no se pudo generar el archivo historico de CTable");
        qDebug(qPrintable(msg));
        return;
    }
    QTextStream out(&outputFile);

    QString stringLine;

    // lista temporal de genes
    QList<CTableGen *> tmpList;



    for (int i = 0; i < historicSuperIndividualList.size(); i++)
    {
        tmpList = historicSuperIndividualList.at(i);

        CTableGen * gen;

        for (int j = 0; j < tmpList.size(); j++)
        {
            gen = tmpList.at(j);
            stringLine.append(QString::number(gen->getChannel()));
            stringLine.append(",");
            stringLine.append(QString::number(gen->getMinChannelTime()));
            stringLine.append(",");
            stringLine.append(QString::number(gen->getMaxChannelTime()));

            if ( j!= (tmpList.size()-1) )
            {
                stringLine.append(",");
            }
        }
        out << stringLine << "\n";
        stringLine.clear();
    }

}

