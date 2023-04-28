#include <iostream>
#include <map>
#include <fstream>
#include <string>
#include "TankData.h"
#include<unistd.h>
#include <regex>
#include <chrono>
#include <vector>
using namespace std;

void swap(int& a, int& b);

//quicksort
int partition(vector<int>& vec, int low, int high);
void quickSort(vector<int>& vec, int low, int high);

//merge sort
void merge(vector<int>& vec, int left, int mid, int right);
void mergeSort(vector<int>& vec, int left, int right);

struct tankNames {
    bool operator()(const string &a, const string &b) const {
        string tankA = a.substr(0, a.find("-"));
        string tankB = b.substr(0, b.find("-"));
        if (tankA == tankB) {
            int numA = stoi(a.substr(a.find("-") + 1));
            int numB = stoi(b.substr(b.find("-") + 1));
            return numA < numB;
        }
        return tankA < tankB;
    }
};

void loadData(string fileName, map<string, TankData, tankNames> &data);

void loadData(string fileName, map<string, TankData, tankNames> &data) {
    ifstream file(fileName);
    string line = "";
    string tank;
    int battles;
    int damage;
    int wn8;
    double winRate;

    getline(file, line);
    int count = 1;
    while (true) {
        while (count != 5 && getline(file, line, ',')) {
            //cout << line << endl;
            if (count == 1) {
                tank = line;
            }
            else if (count == 2) {
                battles = stoi(line);
            }
            else if (count == 3) {
                damage = stoi(line);
            }
            else if (count == 4) {
                wn8 = stoi(line);
            }
            count++;
        }
        if (count == 5 && getline(file, line)) {
            winRate = stod(line);
            count = 1;
            TankData newData = TankData(tank, battles, damage, wn8, winRate);
            data.emplace(tank, newData);
            continue;
        }
        break;
    }
    file.close();
}

//swap
void swap(int& a, int& b) {
    int t = a;
    a = b;
    b = t;
}

//print top 10 vec
void printVectorTop(vector<int>& vec, int choice) {
    int backwards = max(0, (int)vec.size() - 50);

    if (choice == 4) {
        for (int i = backwards; i < vec.size(); i++) {
            cout << (vec[i]/((double) 100)) << " ";
        }
    }
    else {
        for (int i = backwards; i < vec.size(); i++)
            cout << vec[i] << " ";
    }
}

//print bottom 10 vec
void printVectorBottom(vector<int>& vec, int choice) {
    if (choice == 4) {
        for (int i = 0; i < vec.size() && i < 50; i++)
            cout << (vec[i]/((double) 100)) << " ";
    }
    else {
        for (int i = 0; i < vec.size() && i < 50; i++)
            cout << vec[i] << " ";
    }
}


int partition(vector<int>& vec, int low, int high)
{
    // pivot
    int pivot = vec[low];
    int up = low, down = high;

    while (up < down)
    {
        for (int j = up; j < high; j++)
        {
            if (vec[up] > pivot)
                break;
            up++;
        }
        for (int j = high; j > low; j--)
        {
            if (vec[down] < pivot)
                break;
            down--;
        }
        if (up < down)
            swap(vec[up], vec[down]);
    }
    swap(vec[low], vec[down]);
    return down;
}

//quick
void quickSort(vector<int>& vec, int low, int high)
{
    if (low < high)
    {
        int pivot = partition(vec, low, high);
        quickSort(vec, low, pivot - 1);
        quickSort(vec, pivot + 1, high);
    }
}

// used the ppt instead w vectors
void merge(vector<int>& vec, int left, int mid, int right)
{
    // Create X ← vec[left..mid] & Y ← vec[mid+1..right]
    int n1 = mid - left + 1;
    int n2 = right - mid;

    vector<int> X(n1), Y(n2);

    for (int i = 0; i < n1; i++)
        X[i] = vec[left + i];
    for (int j = 0; j < n2; j++)
        Y[j] = vec[mid + 1 + j];

    //merging
    int i = 0, j = 0, k = left;

    while (i < n1 && j < n2)
    {
        if (X[i] <= Y[j])
        {
            vec[k] = X[i];
            i++;
        }
        else
        {
            vec[k] = Y[j];
            j++;
        }
        k++;
    }

    // When we run out of elements in either X or Y append the remaining elements

    while (i < n1)
    {
        vec[k] = X[i];
        i++;
        k++;
    }

    while (j < n2)
    {
        vec[k] = Y[j];
        j++;
        k++;
    }
}


void mergeSort(vector<int>& vec, int left, int right)
{
    if (left < right)
    {
        int mid = left + (right - left) / 2;

        mergeSort(vec, left, mid);
        mergeSort(vec, mid + 1, right);

        merge(vec, left, mid, right);
    }
}



int main() {

    map<string, TankData, tankNames> tankData;
    loadData("tanks.csv", tankData);
    string yesOrNo;
    regex parametersY("[Yy]");
    regex parametersN("[Nn]");

    int battles = 0;
    int battleRank;

    int damage = 0;
    int damageRank;
    int wn8 = 0;
    int wn8Rank;

    double winRate = 0;
    int winRateRank;
    int _similarityScore = 0;


    cout << "Hello and welcome to Operation Saving Tank Marshal!" << endl;
    cout << "" << endl;
    sleep(3);
    cout << "Your mission, should you choose to accept it, is to save our Marshal." << endl;
    sleep(3);
    cout << "" << endl;
    cout << "Mission Accept: Y/N" << endl;
    getline(cin, yesOrNo);


    if (regex_match(yesOrNo, parametersY)) {
        //if(yesOrNo == "Y" || "y") {
        cout << "Find your tank to take into battle!" << endl;
        sleep(1);

        cout
                << "Place your ranking of importance from 1 - 4 (1 is highest) to the following categories: Battles, Damage, Rank, Win Rate "
                << endl;
        sleep(1);

        cout
                << "After ranking one of the four, please place your preferred amount for that category in the specified ranges below: "
                << endl;
        sleep(1);

        cout << "" << endl;
        cout << "Battles will range from 100 - 700" << endl;
        cout << "Damage will range from 600 - 3000" << endl;
        cout << "Rank(W8) will range from 1000 - 2500" << endl;
        cout << "Win Rate will range from 40.00 - 70.00, you can be as specific from 2 decimal places" << endl;
        sleep(1);
        cout << "" << endl;

        sleep(1);

        cout << "Please enter your desired rankings, preferred type, and preferred amount:" << endl;

        cout << "Please enter your ranking of Battles (1 - 4): ";
        cin >> battleRank;
        cout << "" << endl;

        cout << "Please enter the desired battles: ";
        cin >> battles;
        cout << "" << endl;

        cout << "Please enter your ranking of Damage (1 - 4): ";
        cin >> damageRank;
        cout << "" << endl;

        cout << "Please enter the desired damage: ";
        cin >> damage;
        cout << "" << endl;

        cout << "Please enter your ranking of WN8(rank tier) of Tank (1 - 4): ";
        cin >> wn8Rank;
        cout << "" << endl;

        cout << "Please enter the desired W8 or rank level of Tank: ";
        cin >> wn8;
        cout << "" << endl;

        cout << "Please enter your ranking of Win Rate (1 - 4): ";
        cin >> winRateRank;
        cout << "" << endl;

        cout << "Please enter the desired Win Rate: ";
        cin >> winRate;
        cout << " " << endl;

        for (auto &iter: tankData) {
            _similarityScore = abs(iter.second.battles - battles) / battleRank
                               + abs(iter.second.damage - damage) / damageRank
                               + abs(iter.second.wn8 - wn8) / wn8Rank
                               + abs((int) (100 * (iter.second.winRate - winRate))) / winRateRank;
            iter.second.similarityScore = _similarityScore;
        }

        int min = 10000;
        //int max = 0;
        string key = "";


        for (const auto &entry: tankData) {

            if (entry.second.similarityScore < min) {
                min = entry.second.similarityScore;
                key = entry.first;
            }
        }

        cout << "The most suitable tank for you is: " << endl;
        auto it = tankData.find(key);
        TankData similar = it->second;
        similar.printData();

        int input;
        cout << " " << endl;
        cout << "Choose which tank category to display the Max/Lowest stats in the database: \n " <<
             "1. Battles \n" <<
             "2. Damage \n" <<
             "3. Wn8 \n" <<
             "4. Win Rate \n" <<
             "5. Exit\n";

        cout << "" << endl;

        vector<int> vec;

        while(input != 5) {
            cin >> input;
            if (input == 1) {
                for (const auto &iter: tankData) {
                    vec.push_back(iter.second.battles);
                }

                int n = vec.size();
                cout << "QuickSort: ||TOP 50|| " << endl;
                cout << " " << endl;
                chrono::time_point<chrono::system_clock> start, end;
                start = chrono::system_clock::now();
                quickSort(vec, 0, n - 1);
                end = chrono::system_clock::now();
                chrono::duration<double> elapsed_seconds = end - start;
                printVectorTop(vec, 1);
                cout << " " << endl;
                cout << " " << endl;
                cout << "QuickSort: ||BOTTOM 50|| " << endl;
                cout << " " << endl;
                printVectorBottom(vec, 1);
                cout << endl << "Elapsed Time: " << elapsed_seconds.count() << endl;
                cout << " " << endl;
                cout << " " << endl;
                cout << "MergeSort: ||TOP 50|| " << endl;
                cout << " " << endl;
                chrono::time_point<chrono::system_clock> start1, end1;
                start1 = chrono::system_clock::now();
                mergeSort(vec, 0, n - 1);
                end1 = chrono::system_clock::now();
                chrono::duration<double> elapsed_seconds1 = end1 - start1;
                printVectorTop(vec, 1);
                cout << " " << endl;
                cout << " " << endl;
                cout << "MergeSort: ||BOTTOM 50|| " << endl;
                cout << " " << endl;
                printVectorBottom(vec, 1);
                cout << endl << "Elapsed Time: " << elapsed_seconds1.count() << endl;

            } else if (input == 2) {
                for (const auto &iter: tankData) {
                    vec.push_back(iter.second.damage);
                }
                int n = vec.size();
                cout << "QuickSort: ||TOP 50|| " << endl;
                cout << " " << endl;
                chrono::time_point<chrono::system_clock> start, end;
                start = chrono::system_clock::now();
                quickSort(vec, 0, n - 1);
                end = chrono::system_clock::now();
                chrono::duration<double> elapsed_seconds = end - start;
                printVectorTop(vec, 2);
                cout << " " << endl;
                cout << " " << endl;
                cout << "QuickSort: ||BOTTOM 50|| " << endl;
                cout << " " << endl;
                printVectorBottom(vec, 2);
                cout << endl << "Elapsed Time: " << elapsed_seconds.count() << endl;
                cout << " " << endl;
                cout << " " << endl;
                cout << "MergeSort: ||TOP 50|| " << endl;
                cout << " " << endl;
                chrono::time_point<chrono::system_clock> start1, end1;
                start1 = chrono::system_clock::now();
                mergeSort(vec, 0, n - 1);
                end1 = chrono::system_clock::now();
                chrono::duration<double> elapsed_seconds1 = end1 - start1;
                printVectorTop(vec, 2);
                cout << " " << endl;
                cout << " " << endl;
                cout << "MergeSort: ||BOTTOM 50|| " << endl;
                cout << " " << endl;
                printVectorBottom(vec, 2);
                cout << endl << "Elapsed Time: " << elapsed_seconds1.count() << endl;
            } else if (input == 3) {
                for (const auto &iter: tankData) {
                    vec.push_back(iter.second.wn8);
                }
                int n = vec.size();
                cout << "QuickSort: ||TOP 50|| " << endl;
                cout << " " << endl;
                chrono::time_point<chrono::system_clock> start, end;
                start = chrono::system_clock::now();
                quickSort(vec, 0, n - 1);
                end = chrono::system_clock::now();
                chrono::duration<double> elapsed_seconds = end - start;
                printVectorTop(vec, 3);
                cout << " " << endl;
                cout << " " << endl;
                cout << "QuickSort: ||BOTTOM 50|| " << endl;
                cout << " " << endl;
                printVectorBottom(vec, 3);
                cout << endl << "Elapsed Time: " << elapsed_seconds.count() << endl;
                cout << " " << endl;
                cout << " " << endl;
                cout << "MergeSort: ||TOP 50|| " << endl;
                cout << " " << endl;
                chrono::time_point<chrono::system_clock> start1, end1;
                start1 = chrono::system_clock::now();
                mergeSort(vec, 0, n - 1);
                end1 = chrono::system_clock::now();
                chrono::duration<double> elapsed_seconds1 = end1 - start1;
                printVectorTop(vec, 3);
                cout << " " << endl;
                cout << " " << endl;
                cout << "MergeSort: ||BOTTOM 50|| " << endl;
                cout << " " << endl;
                printVectorBottom(vec, 3);
                cout << endl << "Elapsed Time: " << elapsed_seconds1.count() << endl;
            } else if (input == 4) {
                for (const auto &iter: tankData) {
                    vec.push_back(iter.second.winRate * 100);
                }
                int n = vec.size();
                cout << "QuickSort: ||TOP 50|| " << endl;
                cout << " " << endl;
                chrono::time_point<chrono::system_clock> start, end;
                start = chrono::system_clock::now();
                quickSort(vec, 0, n - 1);
                end = chrono::system_clock::now();
                chrono::duration<double> elapsed_seconds = end - start;
                printVectorTop(vec, 4);
                cout << " " << endl;
                cout << " " << endl;
                cout << "QuickSort: ||BOTTOM 50|| " << endl;
                cout << " " << endl;
                printVectorBottom(vec, 4);
                cout << endl << "Elapsed Time: " << elapsed_seconds.count() << endl;
                cout << " " << endl;
                cout << " " << endl;
                cout << "MergeSort: ||TOP 50|| " << endl;
                cout << " " << endl;
                chrono::time_point<chrono::system_clock> start1, end1;
                start1 = chrono::system_clock::now();
                mergeSort(vec, 0, n - 1);
                end1 = chrono::system_clock::now();
                chrono::duration<double> elapsed_seconds1 = end1 - start1;
                printVectorTop(vec, 4);
                cout << " " << endl;
                cout << " " << endl;
                cout << "MergeSort: ||BOTTOM 50|| " << endl;
                cout << " " << endl;
                printVectorBottom(vec, 4);
                cout << endl << "Elapsed Time: " << elapsed_seconds1.count() << endl;
            }
        }

        return 0;
    }
    else if (regex_match(yesOrNo, parametersN)) {
        return 0;
    }
}
