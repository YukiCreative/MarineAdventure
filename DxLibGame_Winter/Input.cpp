#include "Input.h"
#include <DxLib.h>

Input::Input() :
    m_padInput(GetJoypadInputState(DX_INPUT_KEY_PAD1)),
    m_beforePadInput(0),
    m_inputAxis()
{
    m_inputEvent["Dash"] =
    {
        {PeripheralType::kKeyboard, KEY_INPUT_LSHIFT},
        {PeripheralType::kPad, PAD_INPUT_1},
    };
    m_inputEvent["Attack"] =
    {
        {PeripheralType::kKeyboard, KEY_INPUT_E},
        {PeripheralType::kPad, PAD_INPUT_2},
    };
}

Input& Input::GetInstance()
{
    static Input instance;
    return instance;
}

void Input::Update()
{
    // 前のフレームのを記憶
    m_beforePadInput = m_padInput;
    m_padInput = GetJoypadInputState(DX_INPUT_KEY_PAD1);
    // スティックの入力を取得
    int analogX, analogY;
    GetJoypadAnalogInput(&analogX, &analogY, DX_INPUT_PAD1);
    m_inputAxis.x = static_cast<float>(analogX);
    m_inputAxis.y = static_cast<float>(analogY);
}

bool Input::IsTrigger(int id)
{
    // こんなにカッコいらないだろ
    return ((m_padInput & id) && !(m_beforePadInput & id));
}

bool Input::IsPressed(int id)
{
    return (m_padInput & id);
}

Vector2 Input::GetInputAxis()
{
    return m_inputAxis;
}
