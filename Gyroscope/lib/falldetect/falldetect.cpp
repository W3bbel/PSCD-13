#include "falldetect.hpp"

bool FallDetect::initialize()
{
    mpu.initialize();
    if (!mpu.testConnection()) {
        return false;
    }
    mpu.setFullScaleGyroRange(MPU6050_GYRO_FS_250);  // ±250 °/s
    mpu.setFullScaleAccelRange(MPU6050_ACCEL_FS_2); // ±2g
    mpu.setSleepEnabled(false);
    return true;
}

accelgyro_record FallDetect::getRaw()
{
    return data;
}

bool FallDetect::isFalling()
{
    float accelX = data.ax / 16384.0;
    float accelY = data.ay / 16384.0;
    float accelZ = data.az / 16384.0;

    float totalAccel = sqrt(pow(accelX, 2) + pow(accelY, 2) + pow(accelZ, 2));

    if (totalAccel < 0.5) {
        return true;
    }
    return false;
}

void FallDetect::updateData()
{
    mpu.getMotion6(&data.ax, &data.ay, &data.az, &data.gx, &data.gy, &data.gz);
}
