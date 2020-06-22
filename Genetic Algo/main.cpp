#include "environment.h"
#include "ThreadPool.h"
#include <fstream>
#include <windows.h>
#include <mutex>

int numExperiments, numGeneration, populationSize, boardSize;
float mutationRate;
int successCount = 0;
mutex lock_mutex;

void RunToCountSuccess(int currentId) {
    Environment env(populationSize, boardSize, mutationRate);
    State best = env.Evaluate(numGeneration);
    lock_mutex.lock();
    cout << "-----\nExperiment: " << currentId << endl <<
         "FitnessValue: " << best.FitnessValue() << "/" << env.MaxFitnessValue() << endl;
    lock_mutex.unlock();
    if (env.GetBestResult()) {
        ++successCount;
        cout << best.ToString() << endl;
    }
}


int main() {
    int op;
    // log file
    ifstream input("E:\\Files\\algorithm\\Genetic Algo\\input3");
    string filename("Mutate_result.txt");
    ofstream output(filename);
    for (int n = 1; n <= 10; n++) {
        successCount=0;
        printf("Please input the type of Genetic Algorithm:\n1.Thread Mode\n2.Common Mode\n");
        input >> op;

        cout << "num of experiment: ";
        input >> numExperiments;
        cout << "num of generation per experiment: ";
        input >> numGeneration;
        cout << "mutation rate: ";
        input >> mutationRate;
        cout << "population size: ";
        input >> populationSize;
        cout << "board size: ";
        input >> boardSize;


        cout << "num of experiment: " << numExperiments << endl \
        << "num of generation per experiment: " << numGeneration << endl \
        << "mutation rate: " << mutationRate << endl \
        << "population size: " << populationSize << endl \
        << "board size: " << boardSize << endl \
         << "-------------------\n\n";

        State::SetRandomSeed();
        LARGE_INTEGER large_interger;
        double dff;
        __int64 c1, c2;
        QueryPerformanceFrequency(&large_interger); //设置时钟频率
        dff = large_interger.QuadPart;
        QueryPerformanceCounter(&large_interger); //设置时钟计时器
        c1 = large_interger.QuadPart;             //计时开始
        if (op == 1) {
            /*vector<thread> envs(numExperiments);
            for (int i = 0; i < numExperiments; i++) {
                envs[i] = thread(RunToCountSuccess, i+1);
            }
            for (int i = 0; i < numExperiments; i++) {
                envs[i].join();
            }*/
            ThreadPool Pool(numExperiments);
            vector<future<void>> results;
            for (int i = 0; i < numExperiments; i++) {
                results.emplace_back(Pool.submit(RunToCountSuccess, i));
            }
        } else if (op == 2) {
            int currentExperiment = 0;
            while (currentExperiment < numExperiments) {
                Environment env(populationSize, boardSize, mutationRate);
                State best = env.Evaluate(numGeneration);
                cout << "-----\nExperiment: " << currentExperiment << endl << "FitnessValue: " << best.FitnessValue()
                     << "/"
                     << env.MaxFitnessValue() << endl;
                if (env.GetBestResult()) {
                    ++successCount;
                    cout << best.ToString() << endl;
                }
                ++currentExperiment;
            }
        }

        QueryPerformanceCounter(&large_interger);
        c2 = large_interger.QuadPart; //计时结束

        double rate = successCount * 1.0 / numExperiments;
        //cout << boardSize << endl;
        output << "Rate of success: " << rate << endl;
        output << "Average time: " << (c2 - c1) * 1000 / (dff * numExperiments) << "ms" << endl;
    }
    input.close();
    output.close();
    return 0;
}
