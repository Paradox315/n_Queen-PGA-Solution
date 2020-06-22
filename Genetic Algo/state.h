//
// Created by 胡耀文 on 2020/6/14.
//

#ifndef GENETIC_ALGO_STATE_H
#define GENETIC_ALGO_STATE_H

#include <vector>
#include <algorithm>
#include <iostream>
#include <string>
#include <sstream>
#include <ctime>
#include <cstdlib>
using namespace std;
// class for board state
class State {
private:
    int m_fitnessValue;//当前状态适应值
    vector<int> m_board;//棋盘状态

public:
    State() = default;
    State(size_t boardSize, bool needInitialization=true)//boardsize:棋盘大小 needInitialzation:是否需要初始化
            : m_board(vector<int>(boardSize)) {
        if (needInitialization) {
            generateState();//随机产生一组棋盘
            m_fitnessValue = computeFitnessValue(m_board);//计算当前状态适应值
        }
        else
            m_fitnessValue = 0;
    }

    // 获取数值的公用接口函数
    size_t BoardSize() const { return m_board.size(); }//获取当前棋盘大小
    int FitnessValue() const { return m_fitnessValue; }//获取当前适应度

    // 函数部分
    void Mutate() {
        size_t index = rand() % BoardSize();//发生变异的染色体位置
        m_board[index] = rand() % BoardSize();//发生变异
        m_fitnessValue = computeFitnessValue(m_board);//重新计算适应度
    }

    void SetBoard(const vector<int> & newBoard) {//重新设置棋盘状态
        m_board = newBoard;
        m_fitnessValue = computeFitnessValue(m_board);
    }
    string ToString() const {//打印棋盘
        ostringstream s;
        for (auto i : m_board) {
            for (auto j = 0; j < BoardSize(); ++j) {
                s << (i == j) << " ";
            }
            s << endl;
        }
        return s.str();
    }
    void Print() const {
        cout << ToString();
    }
    static void SetRandomSeed() {//设置随机数种子
        srand(time(0));
    }

    // operators
    int operator[](int i) const { return m_board[i]; }

private:
    static int computeFitnessValue(const vector<int> &board) {//计算适应度
        int boardSize = static_cast<int>(board.size());
        int fitnessValue = 0;
        for (int i = 0; i < boardSize; ++i)
            for (int j = i; j < boardSize; ++j)
                if (board[j] != board[i] && \
                    board[j] != board[i] + j - i && \
                    board[j] != board[i] + i - j)
                    fitnessValue += 1;
        return fitnessValue;
    }
    void generateState() {
        size_t boardSize = BoardSize();
        for_each(m_board.begin(), m_board.end(), [boardSize](int &i) { i = rand() % boardSize; } );
    }
};
#endif //GENETIC_ALGO_STATE_H
