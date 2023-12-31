# PID

参考：《由入门到精通 -- 吃透PID2.0版》

- 比例控制：
  - 通过改变比例带来调节
  - 局限：不容易达到设定的目标值，存在**静态偏差**
- 积分控制：
  - 每时刻根据上一时刻的偏差，自动修改参数，使得偏差不为0的时候，执行机构一直动作下去。
- 微分控制：
  - 预动作

## 调节器

调节器是调节系统的核心。

有两个输入量：

- **被调量**：调节对象的实际波动量
- **设定值**：被调量的期望理想值

**输入偏差**：被调量和设定值之间的差值。

调节器至少会有一个模拟输出量：**输出指令**。

## PID的意义

比例/积分/微分

- 比例：把输入偏差乘以一个系数，作为调节器的输出；
- 积分：对输入偏差进行积分运算；
- 微分：对输入偏差进行微分运算；

控制参数基本公式：

$$
K_{p} = 0.6 \times  K_{m} \\
K_{d} = K_{p} \times \frac{\pi}{4} \times \omega \\
K_{i} = K_{p} \times \frac{\omega}{\pi}
$$

Km为系统开始震荡时的比例值；

ω为极坐标下震荡时的频率；

## 整定参数

### 术语

- 判断修改确认PID参数的过程，即为**整定参数**。
- **单回路**：只有一个PID的调节系统。
- **串级**：把两个 PID 串接起来，形成一个串级调节系统。又叫双回路调节系统。在第三章里面，
- **主调**：串级系统中，要调节被调量的那个 PID 叫做主调。 
- **副调**：串级系统中，输出直接去指挥执行器动作的那个 PID 叫做副调。

主调的输出进入副调作为副调的设定值。一般来说，主调为了调节被调量，副调为了消除干扰。 

- **正作用**：对于 PID 调节器 来说，输出随着被调量增高而增高，降低而降低的作用，叫做正作用。 
- **负作用**：对于 PID 调节器来说，输出随着被调量的增高而降低的作用叫做负作用。 
- **动态偏差**：在调节过程中，被调量和设定值之间的偏差随时改变，任意时刻两者之间的偏差叫做动态偏差。简称动差。 
- **静态偏差**：调解趋于稳定之后，被调量和设定值之间还存在的偏差叫做静态偏差。简称静差。 
- **回调**：调节器调节作用显现，使得被调量开始由上升变为下降，或者由下降变为上升。 
- **阶跃**：被观察的曲线呈垂直上升或者下降，这种情况在异常情况下是存在的，比如人为修改数值，或者短路开路。

### 曲线收集

1. 设定值
2. 被调量波动曲线
3. PID输出曲线

如果为串联调节系统，还需收集：

1. 副调的被调量曲线
2. PID输出曲线

### 方法

- 理论计算法（较少使用）
- 趋势读定法
  - 分析曲线特性，根据比例、积分、微分的性质对PID参数进行整定。

趋势读定法三要素：

1. 设定值
2. 被调量
3. 输出

### PID作用趋势分析

一、纯比例作用

结论：对于一个单回路调节系统，单纯的比例作用下，输出的波形与被调量的波形完全相似。

推论：

- 对于正作用的调节系统，顶点、谷底均发生在同一时刻。
- 对于负作用的调节系统，被调量的顶点就是输出的谷底，谷底就是输出的顶点。
- 对于正作用的调节系统，被调量的曲线上升，输出曲线就上升；被调量曲线下降， 输出曲线就下降。两者趋势完全一样。
- 对于负作用的调节系统，被调量曲线和输出曲线相对。 波动周期完全一致。
- 只要被调量变化，输出就变化；被调量不变化，不管静态偏差有多大，输出也不会变化。

二、纯积分作用

> “如果调节器的输入偏差不为0，则让调节器的输出按一定的速度一直朝一个方向累加下去。”

结论：积分相当于一个斜率发生器，存在的前提是调节器的输入偏差不为0。斜率的大小与**输入偏差的大小**和**积分时间**有关。

一般积分作用都和比例作用一起使用，**没有纯积分作用**。为了方便分析，纯积分的推论：

- 输出的升降与被调量的升降无关，与输入偏差的正负有关。
- 输出的升降与被调量的大小无关。
- 输出的斜率与被调量的大小有关。
- 被调量不管怎么变化，输出始终不会出现阶跃扰动。
- 被调量达到顶点的时候，输出的变化趋势不变，速率开始减缓。
- 输出曲线达到顶点的时候，必然是输入偏差等于零的时候。

积分作用可以消除静态误差，但也有可能造成积分干扰。

三、纯微分作用

> “一句话简述：被调量不动，输出不动；被调量一动，输出马上跳。”

一般微分作用都和比例作用一起使用，**没有纯微分作用**。为了方便分析，纯微分的推论：

- 微分作用与被调量的大小无关，与被调量的变化 速率有关；
- 与被调量的正负无关，与被调量的变化趋势有关； 
- 如果被调量有一个阶跃，就相当于输入变化的速度无穷大，那么输出会直接到最小或者最大； 
- 微分参数有的是一个，用微分时间表示。有的分为两个：微分增益和微分时间。微分增益表示输出波动的幅度，波动后还要输出回归，微分时间表示回归的快慢。
- 由第 4 条得出推论：波动调节之后，输出还会自动拐回头。

微分作用能够超前调节，合理搭配微分增益和微分时间可以起到很好的作用。

**总结**

比例作用：输出与输入曲线相似。 

积分作用：只要输入有偏差输出就变化。 

微分作用：输入有抖动输出才变化，且会猛变化。

### 整定参数的原则

1. 把串级调节系统孤立成两个单回路。把主、副调隔离开来，先整定一个回路，再全面考虑；
2.  至于先整定内回路还是先整定外回路，因系统而异。一般来说，对于调节周期长的系统可以先整定内回路。我们还可以手动调整系统稳定后，投入自动，先整定内回路；
3. 把相互耦合的系统解耦为几个独立的系统，在稳态下，进行参数判断。让各个系统 之间互不干扰，然后再考虑耦合；
4. 把 P、I、D 隔离开来。先去掉积分、微分作用，让系统变为纯比例调节方式。然后再考虑积分，然后再考虑微分。



一、比例带的整定

**前提：**系统仅存在纯比例作用，即积分时间无穷大，微分增益为0 。

**比例带**是输入偏差和输出数值相除的商，比例带越大，比例作用越弱，比例增益越小。

**方法：**

系统允许的情况下：

- “逐渐增大比例作用，直到系统发生等幅振荡，然后在这 个基础上适当减小比例作用即可，或者把比例增益乘以 0.6~0.8。”

> 震荡的判断方法：对于一个简单的单回路调节系统，比例作用很强的时候，振荡周期是很有规律的，基本上呈正弦波形状。而极弱参数下的波动也有一定的周期， 但是在一个波动周期内，往往参杂了几个小波峰。

系统不允许的情况下：

- “亲自操作执行机构，或者查找运行操作的历史趋势，查找或者令执行机构的输出有一个 足够的阶跃量——这个阶跃量要足够大，但是千万不能给稳定运行带来危险——然后观察被 调量多久之后开始有响应。记录下响应时间。然后在整定参数的时候，你所整定的系统的波动周期，大约是你记录**响应时间的 3-8 倍**。<u>原文作者声明：这只是个大约的数值。我也仅仅是在近几天内观察考虑的。没有经过长久大量的观察。目前来看，这个思路应该是对的，不排除意外的可能。</u>”

**整定结果**：

最终你所整定的系统，其调节效果应该是被调量波动小而平缓。在一个扰动过来之后， 被调量的波动应该是一很有名的说法：“一大一小两个波”。

> 调节效果好的情况下，不管是被调量还是调节输出，其曲线都不应该有强烈的周期特征。

以及，系统难以稳定不一定是调节策略的问题，**能够通过整定参数解决的问题，最好不通过控制策略来解决**。



二、整定积分时间

**目的：**消除静态偏差。

**前提：**设置好比例参数！

**方法：**

> 图中，我们最需要关注的几个点是：t5、t6、t7。在 t5，t7 之间，t6 的时刻反映了积分的强度。t6 过于靠近 t5，则积分作用过弱；t6 过于靠近 t7，则积分作用过强。t6 所处的位置，应该在 t5、t7 之间的 1/3 靠前一 点。也就是说，t6 的位置在 t5 ～（t7 —t5）\* 1/2 之间。 为了记住（t7—t5） 之间的这个特征点， 我们可以把（t7— t5）\* 1/3 的这个区域叫做积分拐点。**积分拐点这个概念很重要，输出的拐点不能比积分拐点更靠后。**

<img src=".\Images\PID_img\积分作用.png" style="zoom:75%;" />

**结论：**积分作用和比例作用是相对的。当比例作用强的时候，积分也可以随之增强；比例作用弱的时候，积分也必须随之下调。积分作用只是辅助比例作用进行调节，它仅仅是为了消除静态偏差。



三、整定微分作用

**目的：**实现超前调节。

**注意事项：**

- 在微分增益增大的时候，一定要考虑到微分时间的调整。否则调节曲线上会有很多毛刺。 毛刺直接影响到执行机构的频繁动作，一般来说，它是有害的。好的调节效果，往往在调节 曲线上是看不到毛刺的。只可以在输出曲线上看到一个突出的陡升或者陡降。要合理利用微分增益和微分时间的搭配，会取得很好的调节效果。
- 微分调节不是对所有系统都适用的。微分的使用条件有：
  - 被调量是水位、气压、风压的调节系统不宜使用微分。它们本身的数值容易受各种因素影 响，即使稳定的系统，被调量也很难稳定在一个数值。微分作用会因为被调量的小波动，使得输出大幅度来回动作，形成干扰，而且对执行机构也不利
  - 被调量有微小扰动的时候，要先消除扰动再使用微分。
  - 系统有大迟延的情况下应使用微分。
- 震荡产生的时候不要急着使用微分调节来使系统回调，震荡的产生可能和3个参数都有关系，需要对症下药解决问题。

### 自动调节系统的质量指标

- 衰减率：大约为 0.75 最好。好的自动调节系统，用俗话说“一大一小两个波”最好。 用数学方法表示出来，就是合适的衰减率。 

- 最大偏差：一个扰动来临之后，经过调节，系统稳定后，被调量与设定值的最大偏差。一个整定好的稳定的调节系统，一般第一个波动最大，因为“一大一小两个波”， 后面就趋于稳定了。如果不能趋于稳定，也就是说不是稳态，那就谈不上调节质量，也就无所谓最大偏差了。

- 波动范围：顾名思义，没必要多说。实际运行中的调节系统，扰动因素是不断存在的，因而被调量是不断波动着的，所以波动范围基本要达到一个区间。 

- 执行机构动作次数。动作次数决定了执行机构的寿命。这里说的执行机构不光包括执行器，还包括调节阀门。执行机构频繁动作不光损坏执行器，还会让阀门线性恶化。

> 一般来说，不管对于直行程还是角行程，对于国产还是进口，对于智能还是简单的执行 器，动作次数不大于 10 次/分钟。对于一些进口执行器，尤其是日本的，次数还要减少。

- 稳定时间：阶跃扰动后，被调量回到稳态所需要的时间。稳定时间决定了系统抑制干扰的速度。

> 最应关注的有两个指标：被调量波动范围、执行机构动作次数，其他都不是最必要的。

## 资料

1. [瓦特蒸汽机自动调节原理](https://v.qq.com/x/page/n07086haqw5.html)
2. [历史介绍部分图片补充](https://zhuanlan.zhihu.com/p/90632377)
3. 