//#pragma once
//#include<memory>
//using namespace std;
//class CharaBase;
//
///// @brief ステートマシーンインターフェース
//namespace StateMachine
//{
//	class IState
//	{
//	public:
//		virtual ~IState() = default;
//
//		virtual void changeState(CharaBase* charaBase) = 0;
//		virtual void update(CharaBase* charaBase) = 0;
//	};
//}
//
///// @brief キャラステート
//namespace CharaState
//{
//	//開いた状態
//	class OpenState : public StateMachine::IState
//	{
//	public:
//		OpenState();
//		~OpenState();
//		void changeState(CharaBase* charaBase);
//		void update(CharaBase* charaBase);
//	};
//
//	//閉じた状態
//	class CloseState : public StateMachine::IState
//	{
//	public:
//		CloseState();
//		~CloseState();
//		void changeState(CharaBase* charaBase);
//		void update(CharaBase* charaBase);
//	};
//
//	//ラッパ状態
//	class TrumpetState : public StateMachine::IState
//	{
//	public:
//		TrumpetState();
//		~TrumpetState();
//		void changeState(CharaBase* charaBase);
//		void update(CharaBase* charaBase);
//	};
//
//	//扇風機状態
//	class FanState : public StateMachine::IState
//	{
//	public:
//		FanState();
//		~FanState();
//		void changeState(CharaBase* charaBase);
//		void update(CharaBase* charaBase);
//	};
//}
//
///// @brief アクションステート
//namespace ActionState
//{
//	class WaitState : public StateMachine::IState
//	{
//	public:
//		WaitState();
//		~WaitState();
//		void changeState(CharaBase* charaBase);
//		void update(CharaBase* charaBase);
//	};
//
//	class EscapeState : public StateMachine::IState
//	{
//	public:
//		EscapeState();
//		~EscapeState();
//		void changeState(CharaBase* charaBase);
//		void update(CharaBase* charaBase);
//	};
//
//	class ChaseState : public StateMachine::IState
//	{
//	public:
//		ChaseState();
//		~ChaseState();
//		void changeState(CharaBase* charaBase);
//		void update(CharaBase* charaBase);
//	};
//
//	class AttackState : public StateMachine::IState
//	{
//	public:
//		AttackState();
//		~AttackState();
//		void changeState(CharaBase* charaBase);
//		void update(CharaBase* charaBase);
//	};
//
//	class ThinkState : public StateMachine::IState
//	{
//	public:
//		ThinkState();
//		~ThinkState();
//		void changeState(CharaBase* charaBase);
//		void update(CharaBase* charaBase);
//	};
//}