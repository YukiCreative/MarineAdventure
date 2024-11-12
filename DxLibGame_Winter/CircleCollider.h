#pragma once
#include "Collider.h"

/// <summary>
/// ‰~Œ`‚Ì“–‚½‚è”»’èƒNƒ‰ƒX
/// </summary>
class CircleCollider : public Collider
{
protected:
	/// <summary>
	/// ”¼Œa
	/// </summary>
	float m_radius;
public:
	CircleCollider(Vector2 pos, float radius);

	/// <summary>
	/// “–‚½‚è”»’è‚Ìæ“¾(‘Î‰~Œ`)
	/// </summary>
	/// <param name="other">‰~Œ`‚Ì“–‚½‚è”»’è</param>
	/// <returns>ÚG‚µ‚Ä‚¢‚é‚©‚Ç‚¤‚©</returns>
	virtual bool CheckHit(CircleCollider& other) override;
	/// <summary>
	/// “–‚½‚è”»’è‚Ìæ“¾(‘Î‹éŒ`)
	/// </summary>
	/// <param name="other">‹éŒ`‚Ì“–‚½‚è”»’è</param>
	/// <returns>ÚG‚µ‚Ä‚¢‚é‚©‚Ç‚¤‚©</returns>
	virtual bool CheckHit(BoxCollider& other) override;

	float GetRadius() { return m_radius; }
};

