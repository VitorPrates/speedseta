
// botões configurados no hardware

const uint8_t bot_up = 7;
const uint8_t bot_down = 12;
const uint8_t bot_left = 8;
const uint8_t bot_right = 11;
const uint8_t bot_1 = 9;
const uint8_t bot_2 = 10;
//

void setup_hardware()
{
    pinMode(bot_1, INPUT_PULLUP);
    pinMode(bot_2, INPUT_PULLUP);
    pinMode(bot_up, INPUT_PULLUP);
    pinMode(bot_down, INPUT_PULLUP);
    pinMode(bot_left, INPUT_PULLUP);
    pinMode(bot_right, INPUT_PULLUP);   
}
String read_buttons()
{
    unsigned long previousMillis = 0;
    const unsigned long delayTime = 10;
    // bool new_frame = false;
    unsigned long currentMillis = millis();
    if (currentMillis - previousMillis >= delayTime)
    {
        previousMillis = currentMillis;
        if (digitalRead(bot_1) == LOW)
        {
            return "b1";
        }
        else if (digitalRead(bot_2) == LOW)
        {
            return "b2";
        }
        else if (digitalRead(bot_down) == LOW)
        {
            return "down"; // baixo
        }
        else if (digitalRead(bot_left) == LOW)
        {
            return "left"; // esquerda
        }
        else if (digitalRead(bot_up) == LOW)
        {
            return "up"; // cima
        }
        else if (digitalRead(bot_right) == LOW)
        {
            return "right"; // direito
        }
        else
        {
            return "none";
        }
    }
    return "default";
}