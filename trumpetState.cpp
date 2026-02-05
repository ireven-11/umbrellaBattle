#include"DxLib.h"
#include"charaBase.h"
#include"trumpetState.h"
#include"cpu.h"
#include <typeinfo>

namespace CharaState
{
	TrumpetState::TrumpetState()
	{
		reset();
	}

	TrumpetState::~TrumpetState()
	{

	}

	void TrumpetState::reset()
	{
		directionCount_ = 0;
	}

	void TrumpetState::changeState(CharaBase* charaBase)
	{
		charaBase->changeFan();
	}

	void TrumpetState::update(CharaBase* charaBase)
	{
		++directionCount_;
		charaBase->vibration();

		//otherChara‚ªcpuŒ^‚©‚µ‚ç‚×‚éitypeid‚Í“Á’è‚ÌŒ^ƒ|ƒCƒ“ƒ^‚ª“Á’è‚ÌŒ^Œ^‚©‚Ç‚¤‚©”»•Ê‚·‚é‚â‚Âj
		if (typeid(charaBase) != typeid(CPU))
		{
			//ƒRƒ“ƒgƒ[ƒ‰[‚ðU“®‚³‚¹‚é
			StartJoypadVibration(charaBase->GetcontrolerNumber_(), vibration_power * 2, vibration_time / 2);
		}
		
		if (directionCount_ > max_direction_count)
		{
			changeState(charaBase);
			charaBase->stopSound();
			reset();
		}
	}
}