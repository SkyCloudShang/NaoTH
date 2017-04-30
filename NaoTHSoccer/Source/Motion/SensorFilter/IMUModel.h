#ifndef IMUMODEL_H
#define IMUMODEL_H

#include <ModuleFramework/Module.h>

#include "Tools/Debug/DebugRequest.h"
#include "Tools/Debug/DebugPlot.h"
#include "Tools/Debug/DebugDrawings3D.h"
#include "Tools/Debug/DebugParameterList.h"

#include <Representations/Infrastructure/GyrometerData.h>
#include <Representations/Infrastructure/AccelerometerData.h>

#include "Representations/Infrastructure/FrameInfo.h"
#include <Representations/Modeling/IMUData.h>

#include "Tools/Filters/KalmanFilter/UnscentedKalmanFilter/UnscentedKalmanFilter.h"

#include "IMURotationMeasurement.h"
#include "IMURotationState.h"

BEGIN_DECLARE_MODULE(IMUModel)

    PROVIDE(DebugRequest)
    PROVIDE(DebugDrawings3D)
    PROVIDE(DebugPlot)
    PROVIDE(DebugParameterList)

    REQUIRE(FrameInfo)

    REQUIRE(GyrometerData)
    REQUIRE(AccelerometerData)

    PROVIDE(IMUData)
END_DECLARE_MODULE(IMUModel)

class IMUModel: private IMUModelBase
{
public:
    EIGEN_MAKE_ALIGNED_OPERATOR_NEW

public:
    IMUModel();

    void execute();
    void writeIMUData(double dt);
    void plots();

private:
    FrameInfo lastFrameInfo;

    //UKF<3,3,RotationState<RotationMeasurement<3>, Measurement<3>,3> > ukf_rot;
    UKF<3,3,RotationState<RotationMeasurement<3>,3> > ukf_rot;
    UKF<3,3,State<Measurement<3>, 3> > ukf_acc_global;

    typedef RotationMeasurement<3> IMU_RotationMeasurement;
    typedef Measurement<3>         IMU_RotVelMeasurement;
    typedef Measurement<3>         IMU_AccMeasurementGlobal;

    Eigen::Vector3d quaternionToRotationVector(const Eigen::Quaterniond& q) const{
        Eigen::AngleAxisd temp(q);
        return temp.angle() * temp.axis();
    }

    bool updated_by_both;

    Eigen::Matrix<double,3,3> R_acc;
    Eigen::Matrix<double,3,3> R_rotation;

    // --- for testing integration around z
    double angle_about_z;

    // --- end

//    class I   MUParameters:  public ParameterList
//    {
//    public:
//       IMUParameters() : ParameterList("IMUModel")
//       {
//           PARAMETER_REGISTER(processNoiseStdQ00) = 15;
//           PARAMETER_REGISTER(processNoiseStdQ01) = 0;
//           PARAMETER_REGISTER(processNoiseStdQ10) = 0;
//           PARAMETER_REGISTER(processNoiseStdQ11) = 20;

//           // experimental determined
//           PARAMETER_REGISTER(measurementNoiseR00) =  0.00130217; //[rad^2]
//           PARAMETER_REGISTER(measurementNoiseR10) = -0.00041764; //[rad^2]
//           PARAMETER_REGISTER(measurementNoiseR11) =  0.00123935; //[rad^2]

//           syncWithConfig();
//       }

//       double processNoiseAccStdQ00;
//       double processNoiseAccStdQ11;
//       double processNoiseAccStdQ22;
//    } imuParameters;

};

#endif // IMUMODEL_H
