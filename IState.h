#pragma once
class CharaBase;

/// @brief ステートマシーンインターフェース
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