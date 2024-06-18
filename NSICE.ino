#include <Servo.h>

Servo serv;

void setup() {
    pinMode(3, INPUT_PULLUP); // 上水限位
    pinMode(4, OUTPUT);       // 冰满发射
    pinMode(5, INPUT_PULLUP); // 下水限位
    pinMode(6, OUTPUT);       // 压缩机散热风扇
    pinMode(7, OUTPUT);       // 水泵
    pinMode(8, OUTPUT);       // 压缩机电磁阀（下冰）
    pinMode(9, OUTPUT);       // 水槽电机（不用，但需要拉低）
    pinMode(10, OUTPUT);      // 压缩机
    serv.attach(13);          // 水槽舵机

    // A6   旧限位（不用）
    // A5   缺水检测（水泵反馈）
    // A4   压缩机散热片温感
    // A3   冰满接收
    // A2   面板按键
    pinMode(A1, OUTPUT);      // 冰满指示
    pinMode(A0, OUTPUT);      // 缺水指示

    digitalWrite(4, LOW);
    digitalWrite(6, LOW);
    digitalWrite(7, LOW);
    digitalWrite(8, LOW);
    digitalWrite(9, LOW);
    digitalWrite(10, LOW);

    digitalWrite(A1, LOW);
    digitalWrite(A0, LOW);
}

void loop() {
    if (Serial.available() > 0) {
        char cmd = Serial.read();
        int par = Serial.parseInt();
        switch (cmd) {
        case 'C':
            digitalWrite(10, par == 0 ? LOW : HIGH);
            break;
        case 'V':
            digitalWrite(8, par == 0 ? LOW : HIGH);
            break;
        case 'P':
            digitalWrite(7, par == 0 ? LOW : HIGH);
            break;
        case 'F':
            digitalWrite(6, par == 0 ? LOW : HIGH);
            break;
        case 'R':
            digitalWrite(4, par == 0 ? LOW : HIGH);
            break;
        case 'S':
            serv.write(par);
            break;
        }
    }
    Serial.print("LimU:");
    Serial.print(digitalRead(3));
    Serial.print(",LimD:");
    Serial.print(digitalRead(5));
    Serial.print(",NoWater:");
    Serial.print(analogRead(A5));
    Serial.print(",Temp:");
    Serial.print(analogRead(A4));
    Serial.print(",Full:");
    Serial.print(analogRead(A3));
    Serial.print(",Key:");
    Serial.println(analogRead(A2));
}
