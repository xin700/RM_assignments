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