#pragma once
#include<list>
using namespace std;

class Stage;

// �m�[�h�\���̂̒�`
typedef struct _node {
	short cost;		// ���Y�m�[�h�܂ł̃R�X�g
	short score;	// ���Y�m�[�h�]���l
	char state;		// �m�[�h���
	char direction;	// �e�m�[�h�̕���
} node;

typedef struct _position {
	int x;
	int y;
	// ������Z�q�̃I�[�o�[���[�h
	struct _position& operator=(const struct _position& v) {
		this->x = v.x;
		this->y = v.y;
		return *this;
	}
} position;

// �n�`�̎��
typedef enum _CHIPTYPE { PLANE, HALL, } CHIPTYPE;
// �m�[�h��Ԓ萔
typedef enum _STATE { UNCHECKED = 0, IN_OPEN_LIST, IN_CLOSE_LIST } STATE;

#define DIR_MAX 6				// �΂߈ړ��������Ȃ��ꍇ��4���w�肷��B6�p�`�ړ��̏ꍇ��6�����Ă�����
#define MAP_WIDTHMAX	7		// �}�b�v��
#define MAP_HEIGHTMAX	7		// �}�b�v����
#define COORDINATE_ELEMENT_MAX 2// x, y�̂Q��

#define X_ELM 0					// �e�q�m�[�h��x����
#define Y_ELM 1					// �e�q�m�[�h��y����

list<position> a_star(position start, position goal);
void mapChipUpdate(bool canExistTile);