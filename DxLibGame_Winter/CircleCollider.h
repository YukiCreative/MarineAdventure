#pragma once
#include "Collider.h"
#include <memory>

class BoxCollider;
class LineCollider;

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
	CircleCollider(Vector2& pos, float radius);

	float GetRadius() const { return m_radius; }

protected:
	/// <summary>
	/// “–‚½‚è”»’è‚Ìæ“¾(‘Î‰~Œ`)
	/// </summary>
	/// <param name="otherCircle">‰~Œ`‚Ì“–‚½‚è”»’è</param>
	/// <returns>ÚG‚µ‚Ä‚¢‚é‚©‚Ç‚¤‚©</returns>
	CollisionStatus CheckHitCircle(const CircleCollider& otherCircle) const override;
	CollisionStatus CheckHitCircle(const CircleCollider& otherCircle, const Vector2& offset) const override;
	/// <summary>
	/// “–‚½‚è”»’è‚Ìæ“¾(‘Î‹éŒ`)
	/// </summary>
	/// <param name="otherRect">‹éŒ`‚Ì“–‚½‚è”»’è</param>
	/// <returns>ÚG‚µ‚Ä‚¢‚é‚©‚Ç‚¤‚©</returns>
	CollisionStatus CheckHitBox(const BoxCollider& otherRect) const override;
	CollisionStatus CheckHitBox(const BoxCollider& otherRect, const Vector2& offset) const override;

	CollisionStatus CheckHitLine(const LineCollider& otherLine, const Vector2& velocity) const override;
};

