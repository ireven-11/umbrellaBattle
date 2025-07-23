#include"AStar.h"
#include"DxLib.h"
#include"stage.h"

//隣接するマスの方向を表す数値
int direction_delta[DIR_MAX][2] = {
#if DIR_MAX == 8//隣接マスが8個
	{ -1,-1 },{  0,-1 },{ +1,-1 },
	{ -1, 0 },{ +1, 0 },
	{ -1,+1 },{  0,+1 },{ +1,+1 },
#elif DIR_MAX == 4//隣接マスが4個(斜め移動なし)
	{  0,-1 },{ -1, 0 },{ +1, 0 },{ 0, +1 },
#elif DIR_MAX == 6//隣接マスが6個(奇数行を基準としてやる)
	{ 0, -1 },{ +1, -1 },
	{ -1, 0 },{ +1, 0 },
	{ 0, +1 }, { +1, +1 },
#endif
};

// 地形コスト(地形によるコスト差がない場合は壁以外をすべて1にする)
short chip_cost[] = { 0, 255 };

// マップ
char map[MAP_HEIGHTMAX][MAP_WIDTHMAX] = {
	{ 1,1,1,1,1,1,1, },
	{  1,0,0,0,0,0,1, },
	{ 1,0,0,0,0,0,1, },
	{  1,0,0,0,0,0,1, },
	{ 1,0,0,0,0,0,1, },
	{  1,0,0,0,0,0,1, },
	{ 1,1,1,1,1,1,1, },
};

bool operator==(const position& o1, const position& o2) {
	return o1.x == o2.x && o1.y == o2.y;
}

bool operator!=(const position& o1, const position& o2) {
	return o1.x != o2.x || o1.y != o2.y;
}

std::list<position> a_star(position start, position goal) {
	// ノード用メモリの確保
	node map_node[MAP_HEIGHTMAX][MAP_WIDTHMAX];
	// ノード用ワーク変数
	position current;
	int neighborX, neighborY;		// 隣接座標
	int deltax, deltay;				// x,y差分
	short cost, score, heuristic;	// 評価値計算用
	std::list<position> result;

	// nodeデータの初期化
	memset(map_node, 0, sizeof(map_node));

	// オープンリストの作成
	std::list<position> open_list = { start };
	// とりあえずスタート地点をオープンリストに追加したフラグを立てる
	map_node[start.y][start.x].state = IN_OPEN_LIST;

	// メインループ：オープンリストが空になるまで繰り返し
	while (!open_list.empty()) {
		if (open_list.front() == goal) {
			// ゴールに到達した
			result.push_front(goal);
			// ゴールから親ノードへ順に辿りながらルートを格納する
			// 先頭に挿入することで、反転処理を省略している
			for (current = open_list.front(); current != start; result.push_front(current)) {
				node& current_node = map_node[current.y][current.x];
				if (direction_delta[current_node.direction][Y_ELM] == 1 || direction_delta[current_node.direction][Y_ELM] == -1)
				{
					//現在のマスが奇数行、偶数行で隣接するマスの方向の数値(x)を変える用の変数
					int eo = current.y % 2 == 0 ? 0 : 1;
					current.x -= direction_delta[current_node.direction][X_ELM] - eo;
				}
				else
				{
					current.x -= direction_delta[current_node.direction][X_ELM];
				}
				current.y -= direction_delta[current_node.direction][Y_ELM];
			}
			// ループ脱出
			break;
		}
		// オープンリストの先頭要素を取得する。
		current = open_list.front();
		node& current_node = map_node[current.y][current.x];

		// 未到達なので周囲のセルを検査(iが各方向を表すことに注意する)
		for (int i = 0; i < DIR_MAX; i++) {
			// 隣セル位置を計算(未完成？eoの足し方が違う?)
			if (direction_delta[i][Y_ELM] == 1 || direction_delta[i][Y_ELM] == -1)
			{
				//現在のマスが奇数行、偶数行で隣接するマスの方向の数値(x)を変える用の変数
				int eo = current.y % 2 == 0 ? 1 : 0;
				neighborX = current.x + direction_delta[i][X_ELM] - eo;
			}
			else
			{
				neighborX = current.x + direction_delta[i][X_ELM];
			}
			neighborY = current.y + direction_delta[i][Y_ELM];
			// 隣セルがマップ外だったらチェックしない
			if (neighborX < 0 || neighborX == MAP_WIDTHMAX) {
				continue;
			}
			if (neighborY < 0 || neighborY == MAP_HEIGHTMAX) {
				continue;
			}
			// 壁だったらチェックしない
			char chip_type = map[neighborY][neighborX];
			if (chip_type == HALL) {
				continue;
			}
			node& next_node = map_node[neighborY][neighborX];
			// オープンリストかクローズリスト入りだったらチェックしない
			if (next_node.state != UNCHECKED) {
				continue;
			}
			// 隣セルのコスト、スコア、ヒューリスティックの計算
			cost = current_node.cost + chip_cost[chip_type];
			deltax = neighborX > goal.x ? neighborX - goal.x : goal.x - neighborX;
			deltay = neighborY > goal.y ? neighborY - goal.y : goal.y - neighborY;
#if DIR_MAX == 8
			// 8方向移動の場合のヒューリスティック
			heuristic = (short)(deltax > deltay ? deltax : deltay);
#elif DIR_MAX == 4
			// 4方向移動の場合のヒューリスティック
			heuristic = (short)(deltax + deltay);
#elif DIR_MAX == 6
			// 6方向移動のヒューリスティック
			heuristic = (short)(deltax > deltay ? deltax : deltay);
#endif
			score = cost + heuristic;
			// コスト、スコアを隣セルノードに記入
			next_node.cost = cost;
			next_node.score = score;
			next_node.direction = (char)i;			// 親セルの方向
			// 隣セルノードをオープンリストに追加する
			next_node.state = IN_OPEN_LIST;
			std::list<position>::iterator iter;
			// オープンリスト内のノードがスコアの昇順になるように新ノードを挿入する
			for (iter = open_list.begin(); iter != open_list.end(); ++iter) {
				if (score <= map_node[iter->y][iter->x].score) {
					open_list.insert(iter, { neighborX, neighborY });
					break;
				}
			}
			// イテレータがリストの終端の「次」に到達したならば、挿入できていない
			// （＝過去最悪のスコア）なので、オープンリストの末尾に新ノードを挿入する
			if (iter == open_list.end()) {
				open_list.push_back({ neighborX, neighborY });
			}
		}
		// 現在位置をクローズする
		current_node.state = IN_CLOSE_LIST;
		open_list.remove(current);
	}
	// コンテナを返す
	return result;
}

/// <summary>
/// マップチップの更新
/// </summary>
/// <param name="stage">タイル存在フラグ</param>
void mapChipUpdate(bool canExistTile, int tileXNumber, int tileYNumber)
{
	if (canExistTile)
	{
		map[tileYNumber][tileXNumber] = 0;
	}
	else
	{
		map[tileYNumber][tileXNumber] = 1;
	}
}