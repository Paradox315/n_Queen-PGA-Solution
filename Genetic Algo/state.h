//
// Created by ��ҫ�� on 2020/6/14.
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
    int m_fitnessValue;//��ǰ״̬��Ӧֵ
    vector<int> m_board;//����״̬

public:
    State() = default;
    State(size_t boardSize, bool needInitialization=true)//boardsize:���̴�С needInitialzation:�Ƿ���Ҫ��ʼ��
            : m_board(vector<int>(boardSize)) {
        if (needInitialization) {
            generateState();//�������һ������
            m_fitnessValue = computeFitnessValue(m_board);//���㵱ǰ״̬��Ӧֵ
        }
        else
            m_fitnessValue = 0;
    }

    // ��ȡ��ֵ�Ĺ��ýӿں���
    size_t BoardSize() const { return m_board.size(); }//��ȡ��ǰ���̴�С
    int FitnessValue() const { return m_fitnessValue; }//��ȡ��ǰ��Ӧ��

    // ��������
    void Mutate() {
        size_t index = rand() % BoardSize();//���������Ⱦɫ��λ��
        m_board[index] = rand() % BoardSize();//��������
        m_fitnessValue = computeFitnessValue(m_board);//���¼�����Ӧ��
    }

    void SetBoard(const vector<int> & newBoard) {//������������״̬
        m_board = newBoard;
        m_fitnessValue = computeFitnessValue(m_board);
    }
    string ToString() const {//��ӡ����
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
    static void SetRandomSeed() {//�������������
        srand(time(0));
    }

    // operators
    int operator[](int i) const { return m_board[i]; }

private:
    static int computeFitnessValue(const vector<int> &board) {//������Ӧ��
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
