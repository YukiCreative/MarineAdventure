#pragma once

class Scene
{
public:
	/// <summary>
	/// �X�V����
	/// </summary>
	virtual void Update() = 0;
	/// <summary>
	/// �`��
	/// </summary>
	virtual void Draw() = 0;
};