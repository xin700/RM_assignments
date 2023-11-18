# 卡尔曼滤波任务工具包

在这个项目中，提供了两个类，分别是`KalmanFilter`和`Simulator`，分别是卡尔曼滤波器和仿真器。

仿真器用于生成仿真数据，卡尔曼滤波器用于对仿真数据进行滤波。

## Simulator

### 运动模型

对于仿真器，默认状态为观测一个静止状态的物体，你可以通过修改转移方程得到一个运动模型。

```cpp
theoretical = x0;
theoretical = x0 + v*t; // 匀速运动
theoretical = x0 + v*t + 0.5*accelaration*t*t; // 匀加速运动
```

### 噪声模型
最终的观测值是噪声和理论实际值的和。
```cpp
measurement = theoretical + noise;
```
同样可以修改此处的噪声模型。

### 使用方法
1. 初始化
```cpp
Simulator<double, 2> *simulator;
simulator = new Simulator<double, 2>(Eigen::Vector2d(0, 0), 5); // 输入为起始点与方差
```

2. 获取仿真数据
```cpp
measurement = simulator->getMeasurement();
```

## KalmanFilter

### 使用方法

1. 按照步骤设置好卡尔曼滤波器的参数。主要有状态转移矩阵、观测矩阵、过程噪声协方差矩阵、观测噪声协方差矩阵。
2. 预测和更新参数
```cpp
kf->predict(measurement);
kf->update();
```
3. 获取后验估计值
```cpp
Eigen::Vector2d estimate = kf->posteriori_state_estimate;
```

## 可视化
在`main.cpp`的例子中，直接用OpenCV绘制点。

为了更精确地呈现图像，你亦也可以使用`matplotlib`、`VOFA+`、`Foxglove`等软件绘制图像。