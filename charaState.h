#pragma once
#include<memory>
using namespace std;
class CharaBase;

/// @brief ステートマシーンインターフェース
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

/// @brief キャラステート
namespace CharaState
{
	//開いた状態
	class OpenState : public StateMachine::IState
	{
	public:
		OpenState();
		~OpenState();
		void changeState(shared_ptr<IState> state, shared_ptr<CharaBase> charaBase);
		void update(shared_ptr<CharaBase> charaBase);
	};

	//閉じた状態
	class CloseState : public StateMachine::IState
	{
	public:
		CloseState();
		~CloseState();
		void changeState(shared_ptr<IState> state, shared_ptr<CharaBase> charaBase);
		void update(shared_ptr<CharaBase> charaBase);
	};

	//ラッパ状態
	class TrumpetState : public StateMachine::IState
	{
	public:
		TrumpetState();
		~TrumpetState();
		void changeState(shared_ptr<IState> state, shared_ptr<CharaBase> charaBase);
		void update(shared_ptr<CharaBase> charaBase);
	};

	//扇風機状態
	class FanState : public StateMachine::IState
	{
	public:
		FanState();
		~FanState();
		void changeState(shared_ptr<IState> state, shared_ptr<CharaBase> charaBase);
		void update(shared_ptr<CharaBase> charaBase);
	};
}