#pragma once
#include<list>
using namespace std;

class Stage;

// ノード構造体の定義
typedef struct _node {
	short cost;		// 当該ノードまでのコスト
	short score;	// 当該ノード評価値
	char state;		// ノード状態
	char direction;	// 親ノードの方向
} node;

typedef struct _position {
	int x;
	int y;
	// 代入演算子のオーバーロード
	struct _position& operator=(const struct _position& v) {
		this->x = v.x;
		this->y = v.y;
		return *this;
	}
} position;

// 地形の種類
typedef enum _CHIPTYPE { PLANE, HALL, } CHIPTYPE;
// ノード状態定数
typedef enum _STATE { UNCHECKED = 0, IN_OPEN_LIST, IN_CLOSE_LIST } STATE;

#define DIR_MAX 6				// 斜め移動を許可しない場合は4を指定する。6角形移動の場合は6をしていする
#define MAP_WIDTHMAX	7		// マップ幅
#define MAP_HEIGHTMAX	7		// マップ高さ
#define COORDINATE_ELEMENT_MAX 2// x, yの２つ

#define X_ELM 0					// 親子ノードのx成分
#define Y_ELM 1					// 親子ノードのy成分

list<position> a_star(position start, position goal);
void mapChipUpdate(bool canExistTile);