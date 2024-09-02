# TFT-ST7789

## 构建运行环境

参考:https://github.com/milkv-duo/duo-examples

## 编译c

```
git clone https://github.com/zwyzwm/TFT-ST7789.git
```

生成st7789后，运行命令 `scp st7789 root@192.168.42.1:/root/`,将程序复制到板端终端。

在板端终端上运行程序。

## 显示
- > 显示颜色

```
TFT_full(RED);
delay_ms(5000);
TFT_full(GREEN);
delay_ms(5000);
TFT_full(BLUE);
delay_ms(5000);
	
```
- > 显示图片

```
Picture_display(point);

```
