#pragma once

class Scene
{
public:
	/// <summary>
	/// �����I�Ƀf�X�g���N�^��virtual�ɂ��Ȃ��Ƃ����Ȃ��ƕ�����
	/// </summary>
	virtual ~Scene() {}
	/// <summary>
	/// �X�V����
	/// </summary>
	virtual void Update() = 0;
	/// <summary>
	/// �`��
	/// </summary>
	virtual void Draw() = 0;
};