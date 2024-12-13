#pragma once
#include <list>
#include <memory>

class Scene
{
protected:

	// �d�l
	// ���������ɃR���X�g���N�^�Ńp�����[�^�����߂�
	// ���X�g���L���[�Ƃ��Ďg���A���X�g�̐擪�ɂ�����̂������s����
	// �I�������A���̎|��`���č폜���Ă��炤
	class ScreenEffect
	{
	protected:
		using UpdateFunc_t = void (ScreenEffect::*) ();
		bool m_isFinished = false;
	public:
		virtual void Update() = 0;
		virtual void Draw() const = 0;
		bool IsFinished() const { return m_isFinished; }
	};

	class ScreenFade : public ScreenEffect
	{
	private:
		// �ǂꂾ�����Ԃ����邩
		int m_lifeFrame;
		// �ŏI�I�ɓ��B���铧���x
		float m_percent;
		unsigned int m_color;
	public:
		ScreenFade(int frame, float fadePercent, unsigned int color);
		void Update() override;
		void Draw() const override;
	};

	// list���w�F�X�N���[�����ʂ̃L���[�B�I���Ȃ��Ǝ��ɍs���Ȃ�
	// ���w�F�X�N���[�����ʁi���������Ɏ��s�ł���j
	using ScreenEffects_t = std::list<std::list<std::shared_ptr<ScreenEffect>>>;
	ScreenEffects_t m_screenEffects;
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
	virtual void Draw() const = 0;

	void UpdateScreenEffect()
	{
		if (m_screenEffects.empty()) return;

		bool isFinished = true;
		for (auto& effect : m_screenEffects.front())
		{
			isFinished &= effect->IsFinished();
		}
		// ���̃L���[�̂��ׂẲ摜���ʂ��I�������
		if (isFinished)
		{
			// ���o��
			m_screenEffects.pop_front();
		}
		// �C����蒼����Update
		for (auto& effect : m_screenEffects.front())
		{
			effect->Update();
		}
	}

	void DrawScreenEffect() const
	{
		if (m_screenEffects.empty()) return;
		for (auto& effect : m_screenEffects.front())
		{
			effect->Draw();
		}
	}
};