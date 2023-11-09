# Fourth Assignment

## 偶对卡尔曼滤波器的理解

卡尔曼滤波器的作用是用来减小趋势噪声的干扰，并且对于下一个运动的状态进行一个较为准确的预测。

预测步骤（预测状态和协方差）：
1. 预测状态：使用系统的动态模型和上一时刻的状态估计，通过状态转移矩阵和控制输入预测当前时刻的状态。
2. 预测协方差：使用系统的动态模型、上一时刻的状态估计和状态协方差，通过状态转移矩阵和过程噪声协方差预测当前时刻的状态协方差。

量测更新步骤（计算卡尔曼增益和更新状态和协方差）：
1. 计算卡尔曼增益：使用测量模型、预测的状态协方差和测量噪声协方差，计算卡尔曼增益。卡尔曼增益反映了预测状态和测量值之间的权衡。
2. 更新状态：使用卡尔曼增益和测量值，将预测的状态与测量值结合起来，得到更准确的状态估计。
3. 更新协方差：使用卡尔曼增益和测量模型，更新状态协方差，以反映测量值对状态估计的影响。

使用代码实现一维的卡尔曼滤波器

```python
measurements = [
5.200,
5.158,
5.129,
5.143,
5.178,
5.126,
5.166,
5.164,
5.185,
5.194,
5.129,
5.108,
5.108,
5.169,
5.163]

initial_state = measurements[0]
initial_covariance = 1 
process_noise = 0.1     
measurement_noise = 0.5 

for i in range(len(measurements)):

    predicted_state = initial_state 
    predicted_covariance = initial_covariance + process_noise  

    measurement = measurements[i]  
    residual = measurement - predicted_state  
    kalman_gain = predicted_covariance / (predicted_covariance + measurement_noise)  # 卡尔曼增益

    updated_state = predicted_state + kalman_gain * residual
    updated_covariance = (1 - kalman_gain) * predicted_covariance

    initial_state = updated_state
    initial_covariance = updated_covariance

    print("Time step:", i+1)
    print("Predicted position:", updated_state)
```

因为线性代数还不太会，所以还没办法理解辣个矩阵的东西

用一个Excel做一个仿真。

搞了一堆数据，大概误差在-2 ~ 2之间，但是围绕25

使用这个函数进行数据生成：`=25+(-1)^RANDBETWEEN(1,2) *RANDBETWEEN(100,200) / 100`

之后制作图标观察趋势：

![](./img/excel_kalman.jpg)

~~学了b站大佬的思路~~

能看到卡尔曼滤波器把波动的趋势变得很缓，使数据更向真实值去靠拢

~~还得多学学线性代数~~