#include"AStar.h"
#include"DxLib.h"
#include"stage.h"

//�אڂ���}�X�̕�����\�����l
int direction_delta[DIR_MAX][2] = {
#if DIR_MAX == 8//�אڃ}�X��8��
	{ -1,-1 },{  0,-1 },{ +1,-1 },
	{ -1, 0 },{ +1, 0 },
	{ -1,+1 },{  0,+1 },{ +1,+1 },
#elif DIR_MAX == 4//�אڃ}�X��4��(�΂߈ړ��Ȃ�)
	{  0,-1 },{ -1, 0 },{ +1, 0 },{ 0, +1 },
#elif DIR_MAX == 6//�אڃ}�X��6��(��s����Ƃ��Ă��)
	{ 0, -1 },{ +1, -1 },
	{ -1, 0 },{ +1, 0 },
	{ 0, +1 }, { +1, +1 },
#endif
};

// �n�`�R�X�g(�n�`�ɂ��R�X�g�����Ȃ��ꍇ�͕ǈȊO�����ׂ�1�ɂ���)
short chip_cost[] = { 0, 255 };

// �}�b�v
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
	// �m�[�h�p�������̊m��
	node map_node[MAP_HEIGHTMAX][MAP_WIDTHMAX];
	// �m�[�h�p���[�N�ϐ�
	position current;
	int neighborX, neighborY;		// �אڍ��W
	int deltax, deltay;				// x,y����
	short cost, score, heuristic;	// �]���l�v�Z�p
	std::list<position> result;

	// node�f�[�^�̏�����
	memset(map_node, 0, sizeof(map_node));

	// �I�[�v�����X�g�̍쐬
	std::list<position> open_list = { start };
	// �Ƃ肠�����X�^�[�g�n�_���I�[�v�����X�g�ɒǉ������t���O�𗧂Ă�
	map_node[start.y][start.x].state = IN_OPEN_LIST;

	// ���C�����[�v�F�I�[�v�����X�g����ɂȂ�܂ŌJ��Ԃ�
	while (!open_list.empty()) {
		if (open_list.front() == goal) {
			// �S�[���ɓ��B����
			result.push_front(goal);
			// �S�[������e�m�[�h�֏��ɒH��Ȃ��烋�[�g���i�[����
			// �擪�ɑ}�����邱�ƂŁA���]�������ȗ����Ă���
			for (current = open_list.front(); current != start; result.push_front(current)) {
				node& current_node = map_node[current.y][current.x];
				if (direction_delta[current_node.direction][Y_ELM] == 1 || direction_delta[current_node.direction][Y_ELM] == -1)
				{
					//���݂̃}�X����s�A�����s�ŗאڂ���}�X�̕����̐��l(x)��ς���p�̕ϐ�
					int eo = current.y % 2 == 0 ? 0 : 1;
					current.x -= direction_delta[current_node.direction][X_ELM] - eo;
				}
				else
				{
					current.x -= direction_delta[current_node.direction][X_ELM];
				}
				current.y -= direction_delta[current_node.direction][Y_ELM];
			}
			// ���[�v�E�o
			break;
		}
		// �I�[�v�����X�g�̐擪�v�f���擾����B
		current = open_list.front();
		node& current_node = map_node[current.y][current.x];

		// �����B�Ȃ̂Ŏ��͂̃Z��������(i���e������\�����Ƃɒ��ӂ���)
		for (int i = 0; i < DIR_MAX; i++) {
			// �׃Z���ʒu���v�Z(�������Heo�̑��������Ⴄ?)
			if (direction_delta[i][Y_ELM] == 1 || direction_delta[i][Y_ELM] == -1)
			{
				//���݂̃}�X����s�A�����s�ŗאڂ���}�X�̕����̐��l(x)��ς���p�̕ϐ�
				int eo = current.y % 2 == 0 ? 1 : 0;
				neighborX = current.x + direction_delta[i][X_ELM] - eo;
			}
			else
			{
				neighborX = current.x + direction_delta[i][X_ELM];
			}
			neighborY = current.y + direction_delta[i][Y_ELM];
			// �׃Z�����}�b�v�O��������`�F�b�N���Ȃ�
			if (neighborX < 0 || neighborX == MAP_WIDTHMAX) {
				continue;
			}
			if (neighborY < 0 || neighborY == MAP_HEIGHTMAX) {
				continue;
			}
			// �ǂ�������`�F�b�N���Ȃ�
			char chip_type = map[neighborY][neighborX];
			if (chip_type == HALL) {
				continue;
			}
			node& next_node = map_node[neighborY][neighborX];
			// �I�[�v�����X�g���N���[�Y���X�g���肾������`�F�b�N���Ȃ�
			if (next_node.state != UNCHECKED) {
				continue;
			}
			// �׃Z���̃R�X�g�A�X�R�A�A�q���[���X�e�B�b�N�̌v�Z
			cost = current_node.cost + chip_cost[chip_type];
			deltax = neighborX > goal.x ? neighborX - goal.x : goal.x - neighborX;
			deltay = neighborY > goal.y ? neighborY - goal.y : goal.y - neighborY;
#if DIR_MAX == 8
			// 8�����ړ��̏ꍇ�̃q���[���X�e�B�b�N
			heuristic = (short)(deltax > deltay ? deltax : deltay);
#elif DIR_MAX == 4
			// 4�����ړ��̏ꍇ�̃q���[���X�e�B�b�N
			heuristic = (short)(deltax + deltay);
#elif DIR_MAX == 6
			// 6�����ړ��̃q���[���X�e�B�b�N
			heuristic = (short)(deltax > deltay ? deltax : deltay);
#endif
			score = cost + heuristic;
			// �R�X�g�A�X�R�A��׃Z���m�[�h�ɋL��
			next_node.cost = cost;
			next_node.score = score;
			next_node.direction = (char)i;			// �e�Z���̕���
			// �׃Z���m�[�h���I�[�v�����X�g�ɒǉ�����
			next_node.state = IN_OPEN_LIST;
			std::list<position>::iterator iter;
			// �I�[�v�����X�g���̃m�[�h���X�R�A�̏����ɂȂ�悤�ɐV�m�[�h��}������
			for (iter = open_list.begin(); iter != open_list.end(); ++iter) {
				if (score <= map_node[iter->y][iter->x].score) {
					open_list.insert(iter, { neighborX, neighborY });
					break;
				}
			}
			// �C�e���[�^�����X�g�̏I�[�́u���v�ɓ��B�����Ȃ�΁A�}���ł��Ă��Ȃ�
			// �i���ߋ��ň��̃X�R�A�j�Ȃ̂ŁA�I�[�v�����X�g�̖����ɐV�m�[�h��}������
			if (iter == open_list.end()) {
				open_list.push_back({ neighborX, neighborY });
			}
		}
		// ���݈ʒu���N���[�Y����
		current_node.state = IN_CLOSE_LIST;
		open_list.remove(current);
	}
	// �R���e�i��Ԃ�
	return result;
}

/// <summary>
/// �}�b�v�`�b�v�̍X�V
/// </summary>
/// <param name="stage">�^�C�����݃t���O</param>
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