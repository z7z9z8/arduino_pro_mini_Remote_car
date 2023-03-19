# arduino_pro_mini_Remote_car
>这是使用Arduino Nano 开发板制作的遥控小车，支持蓝牙和手柄控制。
# 硬件
- Arduino Nano
- HC-05 蓝牙模块
- 无线PS2手柄
- 小车底盘
# 注意
1. 菜鸟一个，代码写的不好
2. 该小车底盘有刷电调驱动的，然后没有找到相关的资料，只能通过试的方式找的控制正反转的PWM占空比，目前只能控制正反转和刹车。
3. 该小车底盘还有一个铲斗和振盘。
4. 这是我第一次开源。

# 解释
**这里定义的、是有刷电调的PWM的值**
>signal_backwards_l 这个是向后走的时候，左轮的PWM值。
>signal_backwards_r 这个是向后走的时候，右轮的PWM值。
>依次类推   
```
#define signal_ahead_l 100
#define signal_ahead_r 100

#define signal_backwards_l 200
#define signal_backwards_r 200

#define signal_left_l 100
#define signal_left_r 200

#define signal_right_l 200
#define signal_right_r 100

#define signal_stop 150
```
