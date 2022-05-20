#include <Wyvern.h>

struct ScoreKeeper : public Wyvern::NativeScriptComponent
{
	Wyvern::Entity Score;

	WV_SERIALIZE_COMPONENT(ScoreKeeper)
	WV_SERIALIZE_VARIABLE(Wyvern::Entity, Score)
	WV_SERIALIZE_COMPONENT_END
};