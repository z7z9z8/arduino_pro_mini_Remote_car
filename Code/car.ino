#include <SoftwareSerial.h>
#include <PS2X_lib.h> 

/**********手柄引脚定义**********/
#define PS2_DAT 4  
#define PS2_CMD 5  
#define PS2_SEL 6  
#define PS2_CLK 7  

PS2X ps2x;

char serial_data;  // 将从串口读入的消息存储在该变量中

int wheel_R_1 = 10;  // 右轮in1对应Arduino 5号引脚
int wheel_L_1 = 9;   // 左轮in3对应Arduino 9号引脚

int chanDou = 11;  // 铲斗
int DouDong = 12;  // 振盘
  

int speed = 100;

/*0
顺 100
*150
逆200
*255
*/

#define signal_ahead_l 100
#define signal_ahead_r 100

#define signal_backwards_l 200
#define signal_backwards_r 200

#define signal_left_l 100
#define signal_left_r 200

#define signal_right_l 200
#define signal_right_r 100

#define signal_stop 150

#define signal_chanDou 0

//RX---2
//TX---3

SoftwareSerial softSerial1(2, 3);

void setup() {
  ps2x.config_gamepad(PS2_CLK, PS2_CMD, PS2_SEL, PS2_DAT, false, false);
  // 配置所有控制轮的引脚为输出
  pinMode(wheel_L_1, OUTPUT);
  pinMode(wheel_R_1, OUTPUT);
  pinMode(chanDou, OUTPUT);
  pinMode(DouDong, OUTPUT);
  // 配置蓝牙串口波特率
  Serial.begin(9600);
  softSerial1.begin(9600);
  Serial.println("The car is ok!");
}

int pwm_value_pin=0;

void loop() {
  ps2x.read_gamepad();
  if (ps2x.Button(PSB_PAD_UP)) {
      move_ahead();                                //直行的函数
      Serial.println("The car is moving ahead!");  //手机蓝牙端显示
      softSerial1.println("The car is moving ahead!");
    }
    // 如果接收到 x ，后退
    else if (ps2x.Button(PSB_PAD_DOWN)) {
      move_backwards();
      Serial.println("The car is moving backwards!");
      softSerial1.println("The car is moving backwards!");
    }
    // 如果接收到 a ，左转
    else if (ps2x.Button(PSB_PAD_LEFT)) {
      turn_left();
      Serial.println("The car is turning left!");
      softSerial1.println("The car is turning left!");
    }
    // 如果接收到 d ，右转
    else if (ps2x.Button(PSB_PAD_RIGHT)) {
      turn_right();
      Serial.println("The car is turning right!");
      softSerial1.println("The car is turning right!");
    }
    // 如果接收到 s ，停止
    else if (ps2x.Button(PSB_R2)||ps2x.Button(PSB_R3)) {
      stop();
      Serial.println("The car is stopping!");
      softSerial1.println("The car is stopping!");
    }
    // 如果接收到 h ，提升铲斗
    else if (ps2x.Button(PSB_TRIANGLE)) {
      up_chanDou();
      Serial.println("Chan dou UP!");
      softSerial1.println("Chan dou UP!");
    }
    else if (ps2x.Button(PSB_SQUARE)) {
      down_chanDou();
      Serial.println("Chan dou Down!");
      softSerial1.println("Chan dou Down!");
    }
    else if (ps2x.Button(PSB_R3)) {
      stop_chanDou();
      Serial.println("Chan dou stop!");
      softSerial1.println("Chan dou stop!");
    } 
    // 如果接收到 j ，振动盘打开
    else if (ps2x.Button(PSB_CIRCLE)) {
      DouDong_on();
      Serial.println("Zhen Pan ON!");
      softSerial1.println("Zhen Pan ON!");
    }
    // 如果接收到 k ，振动盘关闭
    else if (ps2x.Button(PSB_CROSS)) {
      DouDong_off();
      Serial.println("Zhen Pan OFF!");
      softSerial1.println("Zhen Pan OFF!");
    } 
  delay(200);  
  if (softSerial1.available()) {
    // 将从串口读入的消息存储在该变量中
    serial_data = softSerial1.read();
    //Serial.begin(serial_data);
    // 如果接收到 w ，直行
    if (serial_data == 'W') {
      move_ahead();                                //直行的函数
      Serial.println("The car is moving ahead!");  //手机蓝牙端显示
      softSerial1.println("The car is moving ahead!");
    }
    // 如果接收到 x ，后退
    else if (serial_data == 'S') {
      move_backwards();
      Serial.println("The car is moving backwards!");
      softSerial1.println("The car is moving backwards!");
    }
    // 如果接收到 a ，左转
    else if (serial_data == 'A') {
      turn_left();
      Serial.println("The car is turning left!");
      softSerial1.println("The car is turning left!");
    }
    // 如果接收到 d ，右转
    else if (serial_data == 'D') {
      turn_right();
      Serial.println("The car is turning right!");
      softSerial1.println("The car is turning right!");
    }
    // 如果接收到 s ，停止
    else if (serial_data == 'B') {
      stop();
      Serial.println("The car is stopping!");
      softSerial1.println("The car is stopping!");
    }
    // 如果接收到 h ，提升铲斗
    else if (serial_data == 'E') {
      up_chanDou();
      Serial.println("Chan dou UP!");
      softSerial1.println("Chan dou UP!");
    }
    else if (serial_data == 'F') {
      down_chanDou();
      Serial.println("Chan dou Down!");
      softSerial1.println("Chan dou Down!");
    }
    else if (serial_data == 'I') {
      stop_chanDou();
      Serial.println("Chan dou stop!");
      softSerial1.println("Chan dou stop!");
    } 
    // 如果接收到 j ，振动盘打开
    else if (serial_data == 'G') {
      DouDong_on();
      Serial.println("Zhen Pan ON!");
      softSerial1.println("Zhen Pan ON!");
    }
    // 如果接收到 k ，振动盘关闭
    else if (serial_data == 'H') {
      DouDong_off();
      Serial.println("Zhen Pan OFF!");
      softSerial1.println("Zhen Pan OFF!");
    } 
  }
}

// 定义直行函数
void move_ahead() {
  analogWrite(wheel_L_1, signal_ahead_l);
  analogWrite(wheel_R_1, signal_ahead_r);
}

// 定义后退函数
void move_backwards() {
  analogWrite(wheel_L_1, signal_backwards_l);
  analogWrite(wheel_R_1, signal_backwards_r);
}

// 定义左转函数
void turn_left() {
  analogWrite(wheel_L_1, signal_left_l);
  analogWrite(wheel_R_1, signal_left_r);
}

// 定义右转函数
void turn_right() {
  analogWrite(wheel_L_1, signal_right_l);
  analogWrite(wheel_R_1, signal_right_r);
}
//刹车
void stop() {
  analogWrite(wheel_L_1, signal_stop);
  analogWrite(wheel_R_1, signal_stop);
}

//提升铲斗
void up_chanDou() {
  analogWrite(chanDou, signal_ahead_l);
}
//降低铲斗
void down_chanDou() {
  analogWrite(chanDou, signal_backwards_l);
}

//停止铲斗
void stop_chanDou(){
  analogWrite(chanDou, signal_stop);  
}

//振动盘打开
void DouDong_on() {
  digitalWrite(DouDong, 1);
}

//振动盘关闭
void DouDong_off() {
  digitalWrite(DouDong, 0);
}