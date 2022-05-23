#include <Wyvern.h>

struct ScoreKeeper : public Wyvern::NativeScriptComponent
{
	Wyvern::Entity Score1;
	Wyvern::Entity Score2;
	Wyvern::Entity Score3;

	virtual void OnCollision2D(const Wyvern::Collision2D& collision) override;

	WV_SERIALIZE_COMPONENT(ScoreKeeper)
	WV_SERIALIZE_VARIABLE(Wyvern::Entity, Score1)
	WV_SERIALIZE_VARIABLE(Wyvern::Entity, Score2)
	WV_SERIALIZE_VARIABLE(Wyvern::Entity, Score3)
	WV_SERIALIZE_COMPONENT_END
};