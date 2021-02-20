sp;
</span>return offDate.get(Calendar.DAY_OF_MONTH);<span style='mso-tab-count:
1'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; </span>//</span><span style='font-family:
宋体;mso-ascii-font-family:"Times New Roman";mso-hansi-font-family:"Times New Roman"'>将具体的天数返回</span></p>

<p class=a2><span lang=EN-US>}</span></p>

<p class=MsoNormal><span style='font-family:宋体;mso-ascii-font-family:"Times New Roman";
mso-hansi-font-family:"Times New Roman"'>（</span><span lang=EN-US>4</span><span
style='font-family:宋体;mso-ascii-font-family:"Times New Roman";mso-hansi-font-family:
"Times New Roman"'>）编写获取农历某年闰月的天数方法</span><span lang=EN-US>leapDays()</span><span
style='font-family:宋体;mso-ascii-font-family:"Times New Roman";mso-hansi-font-family:
"Times New Roman"'>，该方法有一个</span><span lang=EN-US>int</span><span
style='font-family:宋体;mso-ascii-font-family:"Times New Roman";mso-hansi-font-family:
"Times New Roman"'>型参数，用于指定年份，返回值为农历某年闰月的天数，具体代码如下：</span></p>

<p class=a2><span lang=EN-US>final private static int leapDays(int y) {</span></p>

<p class=a2><span lang=EN-US><span style="mso-spacerun: yes">&nbsp;&nbsp;&nbsp;
</span>if (leapMonth(y) != 0) {<span style='mso-tab-count:5'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; </span>//</span><span
style='font-family:宋体;mso-ascii-font-family:"Times New Roman";mso-hansi-font-family:
"Times New Roman"'>如果指定参数不为</span><span lang=EN-US>0</span></p>

<p class=a2><span lang=EN-US><span style="mso-spacerun:
yes">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; </span>if ((lunarInfo[y - 1900]
&amp; 0x10000) != 0) {</span></p>

<p class=a2><span lang=EN-US><span style="mso-spacerun:
yes">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
</span>return 30;</span></p>

<p class=a2><span lang=EN-US><span style="mso-spacerun:
yes">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; </span>} else {</span></p>

<p class=a2><span lang=EN-US><span style="mso-spacerun:
yes">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
</span>return 29;</span></p>

<p class=a2><span lang=EN-US><span style="mso-spacerun:
yes">&nbsp;&nbsp;&nbsp;&nbsp; </span><span style="mso-spacerun:
yes">&nbsp;&nbsp;&nbsp;</span>}</span></p>

<p class=a2><span lang=EN-US><span style="mso-spacerun: yes">&nbsp;&nbsp;&nbsp;
</span>} else {</span></p>

<p class=a2><span lang=EN-US><span style="mso-spacerun:
yes">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; </span>return 0;</span></p>

<p class=a2><span lang=EN-US><span style="mso-spacerun: yes">&nbsp;&nbsp;&nbsp;
</span>}</span></p>

<p class=a2><span lang=EN-US>}</span></p>

<p class=MsoNormal><span style='font-family:宋体;mso-ascii-font-family:"Times New Roman";
mso-hansi-font-family:"Times New Roman"'>（</span><span lang=EN-US>5</span><span
style='font-family:宋体;mso-ascii-font-family:"Times New Roman";mso-hansi-font-family:
"Times New Roman"'>）创建获取农历</span><span lang=EN-US>y</span><span
style='font-family:宋体;mso-ascii-font-family:"Times New Roman";mso-hansi-font-family:
"Times New Roman"'>年的总天数方法</span><span lang=EN-US>yearDays()</spa