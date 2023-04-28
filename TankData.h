#ifndef PROJECT3WOT_TANKDATA_H
#define PROJECT3WOT_TANKDATA_H
#pragma once
#include <iostream>
using namespace std;

struct TankData {
    string name;
    int battles;
    int damage;
    int wn8;
    double winRate;
    int similarityScore;

//public:
    TankData(string _name, int _battles, int _damage, int _wn8, double _winRate);

    void printData();

    /*string getName();
    int getBattles();
    int getDamage();
    int getWn8();
    double getWinRate();
    int getSimilarityScore();

    void setSimilarityScore(int _similarityScore);
    */
};


#endif //PROJECT3WOT_TANKDATA_H
