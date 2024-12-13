#pragma once
#include "GameObject.h"
#include <string>

/// <summary>
/// �w�i�摜��\��������
/// ���i�Ȃ̂Ŏ�O(�}�b�v�`�b�v�A�v���C���[)��������蓮��������
/// </summary>
class BackGround : public GameObject
{
private:
	int m_graphHandle;
public:
	BackGround(const std::string& pass);
	~BackGround();

	void Update() override;
	void Draw() const override;

	void SetGraph(const int& handle) { m_graphHandle = handle; }
	void SetGraph(const std::string&);
};

