隐藏``QScrollBar``的箭头，图省事的可以直接设置样式表。

```css
::add-line,
::sub-line {
	/*隐藏无谓的箭头*/
	width: 0;
}
```

但因为一些嵌入式设备的性能不足不允许使用样式表，需要从根本上禁用箭头的绘制，而这就相当麻烦，至少Qt没给相应API，得自己继承``QScrollBar``并重写``paintEvent``函数(大概?因为当时没试成功，或许和``QStyleOption``有关？)当时甚至想过不如直接继承``QAbstractSlider``从头实现滑动条但忍住了，因为太麻烦了

