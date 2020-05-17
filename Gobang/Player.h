#pragma once

enum PlayerType
{
	human = 1,
	robot = 2
};

enum ChessmanType
{
	White = 0,
	Black = 1
};

class Player
{
public:
	Player();
	Player(PlayerType player, ChessmanType chessman);
	~Player();

private:
	//������ͣ�������/����
	PlayerType player;
	//�÷�
	int score;
	//��ִ���ӵ���ɫ
	ChessmanType chessman;

public:
	int getScore();
	int addScore();
};
