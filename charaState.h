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

		virtual void changeState(shared_ptr<IState> state, shared_ptr<CharaBase> charaBase) = 0;
		virtual void update(shared_ptr<CharaBase> charaBase) = 0;
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
		void changeState(shared_ptr<IState> state, shared_ptr<CharaBase> charaBase);
		void update(shared_ptr<CharaBase> charaBase);
	};

	//�������
	class CloseState : public StateMachine::IState
	{
	public:
		CloseState();
		~CloseState();
		void changeState(shared_ptr<IState> state, shared_ptr<CharaBase> charaBase);
		void update(shared_ptr<CharaBase> charaBase);
	};

	//���b�p���
	class TrumpetState : public StateMachine::IState
	{
	public:
		TrumpetState();
		~TrumpetState();
		void changeState(shared_ptr<IState> state, shared_ptr<CharaBase> charaBase);
		void update(shared_ptr<CharaBase> charaBase);
	};

	//��@���
	class FanState : public StateMachine::IState
	{
	public:
		FanState();
		~FanState();
		void changeState(shared_ptr<IState> state, shared_ptr<CharaBase> charaBase);
		void update(shared_ptr<CharaBase> charaBase);
	};
}