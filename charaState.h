#pragma once
#include<memory>
using namespace std;
class CharaBase;

/// @brief �X�e�[�g�}�V�[���C���^�[�t�F�[�X
namespace StateMachine
{
	class IState
	{
	public:
		virtual ~IState() = default;

		virtual void changeState(CharaBase* charaBase) = 0;
		virtual void update(CharaBase* charaBase) = 0;
	};
}

/// @brief �L�����X�e�[�g
namespace CharaState
{
	//�J�������
	class OpenState : public StateMachine::IState
	{
	public:
		OpenState();
		~OpenState();
		void changeState(CharaBase* charaBase);
		void update(CharaBase* charaBase);
	};

	//�������
	class CloseState : public StateMachine::IState
	{
	public:
		CloseState();
		~CloseState();
		void changeState(CharaBase* charaBase);
		void update(CharaBase* charaBase);
	};

	//���b�p���
	class TrumpetState : public StateMachine::IState
	{
	public:
		TrumpetState();
		~TrumpetState();
		void changeState(CharaBase* charaBase);
		void update(CharaBase* charaBase);
	};

	//��@���
	class FanState : public StateMachine::IState
	{
	public:
		FanState();
		~FanState();
		void changeState(CharaBase* charaBase);
		void update(CharaBase* charaBase);
	};
}