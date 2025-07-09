#pragma once
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