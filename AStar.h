#pragma once
#include<list>

class Stage;

//ノード構造体の定義
struct node
{
	short cost;		//当該ノードまでのコスト
	short score;	//当該ノード評価値
	char state;		//ノード状態
	char direction;	//親ノードの方向
};

struct position
{
	int x;
	int y;

	//代入演算子のオーバーロード
	struct position& operator=(const struct position& v)
	{
		this->x = v.x;
		this->y = v.y;
		return *this;
	}
};

// 地形の種類
enum CHIPTYPE { PLANE, HALL, };

// ノード状態定数
enum STATE { UNCHECKED = 0, IN_OPEN_LIST, IN_CLOSE_LIST };

#define DIR_OCTA 8;
#define DIR_HEXA 6;
#define DIR_QUAD 4;

#define DIR_MAX 6	//斜め移動を許可しない場合は4を、許可する場合は8を、6角形移動の場合は6指定。

constexpr char MAP_WIDTHMAX				= 7;		//マップ幅
constexpr char MAP_HEIGHTMAX			= 7;		//マップ高さ
constexpr char COORDINATE_ELEMENT_MAX	= 2;		//x, yの２つ

constexpr short X_ELM = 0;	//親子ノードのx成分
constexpr short Y_ELM = 1;	//親子ノードのy成分

std::list<position> aSter(position start, position goal);
void mapChipUpdate(short tileType, int tileXNumber, int tileYNumber);