#include "TankData.h"


TankData::TankData(string _name, int _battles, int _damage, int _wn8, double _winRate) {
    name = _name;
    battles = _battles;
    damage = _damage;
    wn8 = _wn8;
    winRate = _winRate;
    similarityScore = 0;
}

void TankData::printData() {
    cout << "Name:" << name << endl;
    cout <<"Battles: " << battles << endl;
    cout <<"Damage: " << damage << endl;
    cout << "wn8: " << wn8 << endl;
    cout <<"Win Rate: " << winRate << endl;

}

/*
string TankData::getName() {
	return this->name;
}
int TankData::getBattles() {
	return this->battles;
}
int TankData::getDamage() {
	return this->damage;
}
int TankData::getWn8() {
	return this->wn8;
}
double TankData::getWinRate() {
	return this->winRate;
}
int TankData::getSimilarityScore() {
	return this->similarityScore;
}

void TankData::setSimilarityScore(int _similarityScore) {
	this->similarityScore = _similarityScore;
}
*/