# LightTest
NTHU meichu FastLED LightTeset

## 2018/01/18 Final_LightTest.ino
8 effects with NTHU pattern
### 8 effects
* **1.WhitePurple** - 白紫相間、上下淡出
* **2.Jungle** - 忽明忽暗的多條sin波、白色閃爍
* **3.MiddleOut** - 條狀動畫
* **4.Blink** - 白紫不同亮度閃爍
* **5.SparkSlowToFast** - 漸層白紫、區塊切換
* **6.GlowGradient** - 忽明忽暗漸層、黑色閃爍
* **7.Confetti** - 紫色hsv附近色的閃爍
* **8.Sinelon** - 白紫兩條sin波交互移動
### NTHU pattern
```
 - - - - - - - - - - - - - - - - - - - - - - - - - - - -  led[num_led/5*0]
| | |❚| | | |❚| | |❚|❚|❚|❚|❚| | |❚| | | |❚| | |❚| | | |❚|
 - - - - - - - - - - - - - - - - - - - - - - - - - - - -  led[num_led/5*1]
| | |❚|❚| | |❚| | | | |❚| | | | |❚| | | |❚| | |❚| | | |❚|
 - - - - - - - - - - - - - - - - - - - - - - - - - - - -  led[num_led/5*2]
| | |❚| |❚| |❚| | | | |❚| | | | |❚|❚|❚|❚|❚| | |❚| | | |❚|
 - - - - - - - - - - - - - - - - - - - - - - - - - - - -  led[num_led/5*3]
| | |❚| | |❚|❚| | | | |❚| | | | |❚| | | |❚| | |❚| | | |❚| 
 - - - - - - - - - - - - - - - - - - - - - - - - - - - -  led[num_led/5*4]
| | |❚| | | |❚| | | | |❚| | | | |❚| | | |❚| | |❚|❚|❚|❚|❚|
 - - - - - - - - - - - - - - - - - - - - - - - - - - - -  led[num_led/5*5]
 time-> p.s:each| |=delay(delatime)
 ```
pov led : 等待測試舞者奔跑速度與暫留效果
