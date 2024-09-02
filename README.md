# TFT-ST7789

English | [简体中文]()

## Build the operating environment

Reference: https://github.com/milkv-duo/duo-examples

## Compile c

```
git clone https://github.com/zwyzwm/TFT-ST7789.git
```

After generating st7789, run the command `scp st7789 root@192.168.42.1:/root/` to copy the program to the board terminal.

Run the program on the board terminal.

## Display
-> Display color

```
TFT_full(RED);
delay_ms(5000);
TFT_full(GREEN);
delay_ms(5000);
TFT_full(BLUE);
delay_ms(5000);

```
-> Display picture

```
Picture_display(point);

```
