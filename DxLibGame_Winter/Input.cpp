#include "Input.h"
#include <DxLib.h>
#include <string>
#include <cassert>

namespace
{
    constexpr int kPadA      = PAD_INPUT_1;
    constexpr int kPadB      = PAD_INPUT_2;
    constexpr int kPadX      = PAD_INPUT_3;
    constexpr int kPadY      = PAD_INPUT_4;
    constexpr int kPadL      = PAD_INPUT_5;
    constexpr int kPadR      = PAD_INPUT_6;
    constexpr int kPadSelect = PAD_INPUT_7;
    constexpr int kPadStart  = PAD_INPUT_8;
    constexpr int kPadLStick = PAD_INPUT_9;
    constexpr int kPadRStick = PAD_INPUT_10;
    constexpr int kPadUp     = PAD_INPUT_UP;
    constexpr int kPadDown   = PAD_INPUT_DOWN;
    constexpr int kPadRight  = PAD_INPUT_RIGHT;
    constexpr int kPadLeft   = PAD_INPUT_LEFT;
}

Input::Input() :
    m_padInput(0),
    m_beforePadInput(0),
    m_inputAxis(),
    m_keyInput(),
    m_beforeKeyInput()
{
    m_inputEvent["Dash"] =
    {
        {PeripheralType::kKeyboard, KEY_INPUT_LSHIFT},
        {PeripheralType::kPad, kPadB},
    };
    m_inputEvent["Attack"] =
    {
        {PeripheralType::kKeyboard, KEY_INPUT_Z},
        {PeripheralType::kPad, kPadA},
    };
    m_inputEvent["Up"] =
    {
        {PeripheralType::kKeyboard, KEY_INPUT_UP},
        {PeripheralType::kPad, PAD_INPUT_UP},
    };
    m_inputEvent["Right"] =
    {
        {PeripheralType::kKeyboard, KEY_INPUT_RIGHT},
        {PeripheralType::kPad, PAD_INPUT_RIGHT},
    };
    m_inputEvent["Left"] =
    {
        {PeripheralType::kKeyboard, KEY_INPUT_LEFT},
        {PeripheralType::kPad, PAD_INPUT_LEFT},
    };
    m_inputEvent["Down"] =
    {
        {PeripheralType::kKeyboard, KEY_INPUT_DOWN},
        {PeripheralType::kPad, PAD_INPUT_DOWN},
    };
    m_inputEvent["Srow_Debug"] =
    {
        {PeripheralType::kKeyboard, KEY_INPUT_LCONTROL},
        {PeripheralType::kPad, kPadR},
    };
    m_inputEvent["ChangeScene_Debug"] =
    {
        {PeripheralType::kKeyboard, KEY_INPUT_RETURN},
        {PeripheralType::kPad, kPadL},
    };
    m_inputEvent["Jump"] =
    {
        {PeripheralType::kKeyboard, KEY_INPUT_SPACE},
        {PeripheralType::kPad, kPadY},
    };
    m_inputEvent["Pause"] =
    {
        {PeripheralType::kKeyboard, KEY_INPUT_ESCAPE},
        {PeripheralType::kPad, kPadStart},
    };
    m_inputEvent["Submit"] =
    {
        {PeripheralType::kKeyboard, KEY_INPUT_Z},
        {PeripheralType::kPad, kPadA},
    };
    m_inputEvent["RecoverPlayerHp_Debug"] =
    {
        {PeripheralType::kKeyboard, KEY_INPUT_H},
        {PeripheralType::kPad, kPadRStick},
    };
    m_inputEvent["DamagePlayer_Debug"] =
    {
        {PeripheralType::kKeyboard, KEY_INPUT_D},
        {PeripheralType::kPad, kPadLStick},
    };
}

Input& Input::GetInstance()
{
    static Input instance;
    return instance;
}

void Input::Update()
{
    // PAD�̑O�̃t���[���̂��L��
    m_beforePadInput = m_padInput;
    m_padInput = GetJoypadInputState(DX_INPUT_PAD1);
    // �L�[
    m_beforeKeyInput = m_keyInput;
    GetHitKeyStateAll(m_keyInput.state);

    // �X�e�B�b�N�̓��͂��擾
    int analogX, analogY;
    GetJoypadAnalogInput(&analogX, &analogY, DX_INPUT_PAD1);
    // �L�[�{�[�h�A�\���L�[���擾
    if (IsPressed("Up"))    analogY = -1000;
    if (IsPressed("Down"))  analogY =  1000;
    if (IsPressed("Right")) analogX =  1000;
    if (IsPressed("Left"))  analogX = -1000;

    // �A�i���O���͂̑傫����1000�܂łɐ�������
    Vector2 inputAxis(analogX, analogY);
    if (inputAxis.SqrMagnitude() > 1000 * 1000)
    {
        inputAxis.Normalize();
        inputAxis *= 1000;
    }

    // �����őO�t���[���̓��͂��o���Ă���
	m_beforeInputAxis = m_inputAxis;
    // �����čX�V
    m_inputAxis.x = static_cast<float>(inputAxis.x);
    m_inputAxis.y = static_cast<float>(inputAxis.y);
}

bool Input::IsTrigger(std::string key) const
{
    bool isTrigger = false;
    // �^����ꂽ�L�[�ɑΉ�����S�Ă̎��Ӌ@��̓��̓R�[�h�𒲂ׂ�
    for (const auto& inputEvent : m_inputEvent.at(key))
    {
        switch (inputEvent.type)
        {
        case PeripheralType::kKeyboard:
            // �L�[�{�[�h�̂����œ��͂��擾
            isTrigger = isTrigger || m_keyInput.state[inputEvent.inputCode] && !m_beforeKeyInput.state[inputEvent.inputCode];
            break;
        case PeripheralType::kPad:
            // �p�b�h
            isTrigger = isTrigger || (m_padInput & inputEvent.inputCode) && !(m_beforePadInput & inputEvent.inputCode);
            break;
        default:
            assert(false && "�񋓑̗̂v�f�ɑ΂��ď�������������Ă��Ȃ�");
            break;
        }
    }
    return isTrigger;
}

bool Input::IsPressed(std::string key) const
{
    bool isPressed = false;
    // �^����ꂽ�L�[�ɑΉ�����S�Ă̎��Ӌ@��̓��̓R�[�h�𒲂ׂ�
    for (const auto& inputEvent : m_inputEvent.at(key))
    {
        switch (inputEvent.type)
        {
        case PeripheralType::kKeyboard:
            // �L�[�{�[�h�̂����œ��͂��擾
            isPressed = isPressed || m_keyInput.state[inputEvent.inputCode];
            break;
        case PeripheralType::kPad:
            // �p�b�h
            isPressed = isPressed || m_padInput & inputEvent.inputCode;
            break;
        default:
            assert(false && "�񋓑̗̂v�f�ɑ΂��ď�������������Ă��Ȃ�");
            break;
        }
    }
    return isPressed;
}

Vector2 Input::GetInputAxis() const
{
    return m_inputAxis;
}

Vector2 Input::GetBeforeInputAxis() const
{
    return m_beforeInputAxis;
}
