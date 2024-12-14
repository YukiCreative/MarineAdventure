#pragma once
#include <list>
#include <memory>

/// <summary>
/// �V�[���ŁA��ʂ��t�F�[�h��������A�J������h�炵���肵����
/// </summary>
class ScreenEffectController
{
private:
	/// <summary>
	/// �l�p�`����ʂ����ς��`�悷�邾��
	/// </summary>
	class FadePanel
	{
	private:
		uint8_t m_alpha;
		unsigned int m_color;
	public:
		FadePanel() = default;
		void Draw() const;
	};

	// �d�l
	// ���������ɃR���X�g���N�^�Ńp�����[�^�����߂�
	// ���X�g���L���[�Ƃ��Ďg���A���X�g�̐擪�ɂ�����̂������s����
	// �I�������A���̎|��`���č폜���Ă��炤
	class ScreenEffect
	{
	protected:
		bool m_isFinished = false;
	public:
		virtual void Update() = 0;
		bool IsFinished() const { return m_isFinished; }
	};

	class ScreenFade : public ScreenEffect
	{
		//friend FadePanel;
	private:
		// �ǂꂾ�����Ԃ����邩
		int m_lifeFrame;
		// �ŏI�I�ɓ��B���铧���x
		float m_percent;
		unsigned int m_color;
	public:
		ScreenFade(int frame, float fadePercent, unsigned int color);
		void Update() override;
	};

	std::shared_ptr<FadePanel> m_fadePanel;

	// list���w�F�X�N���[�����ʂ̃L���[�B�I���Ȃ��Ǝ��ɍs���Ȃ�
	// ���w�F�X�N���[�����ʁi���������Ɏ��s�ł���j
	using ScreenEffects_t = std::list<std::list<std::shared_ptr<ScreenEffect>>>;
	ScreenEffects_t m_screenEffects;

public:
	void Update();
	void Draw() const;
};

