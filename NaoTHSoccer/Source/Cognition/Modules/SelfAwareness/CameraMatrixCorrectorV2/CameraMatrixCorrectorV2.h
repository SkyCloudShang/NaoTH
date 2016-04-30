/**
* @file CameraMatrixCorrectorV2.h
*
* @author <a href="mailto:mellmann@informatik.hu-berlin.de">Heinrich Mellmann</a>
* Declaration of class CameraMatrixProvider
*/

#ifndef _CameraMatrixCorrectorV2_h_
#define _CameraMatrixCorrectorV2_h_

#include <ModuleFramework/Module.h>

#include "Representations/Perception/CameraMatrix.h"
#include "Representations/Perception/GoalPercept.h"
#include "Representations/Infrastructure/Image.h"
#include "Representations/Infrastructure/JointData.h"
#include "Representations/Infrastructure/FSRData.h"
#include "Representations/Infrastructure/FieldInfo.h"
#include "Representations/Infrastructure/AccelerometerData.h"
#include "Representations/Infrastructure/FrameInfo.h"
#include "Representations/Modeling/InertialModel.h"
#include "Representations/Modeling/CameraMatrixOffset.h"

// motion stuff
#include "Representations/Modeling/KinematicChain.h"

#include "Tools/DoubleCamHelpers.h"

// debug
#include "Tools/Debug/DebugRequest.h"
#include <Tools/Debug/DebugDrawings3D.h>
#include <Tools/Debug/DebugImageDrawings.h>
#include "Tools/Debug/DebugModify.h"

//////////////////// BEGIN MODULE INTERFACE DECLARATION ////////////////////

BEGIN_DECLARE_MODULE(CameraMatrixCorrectorV2)
  PROVIDE(DebugRequest)
  PROVIDE(DebugDrawings3D)
  PROVIDE(DebugImageDrawings)
  PROVIDE(DebugImageDrawingsTop)
  PROVIDE(DebugModify)
  
  REQUIRE(InertialModel)
  REQUIRE(Image)
  REQUIRE(FieldInfo)
  REQUIRE(AccelerometerData)
  REQUIRE(FrameInfo)

  REQUIRE(GoalPercept) // needed for calibration of the camera matrix
  REQUIRE(GoalPerceptTop)
  REQUIRE(CameraMatrix)
  REQUIRE(CameraMatrixTop)

  REQUIRE(CameraInfo)
  REQUIRE(CameraInfoTop)

  REQUIRE(KinematicChain)

  PROVIDE(CameraMatrixOffset)
END_DECLARE_MODULE(CameraMatrixCorrectorV2)

//////////////////// END MODULE INTERFACE DECLARATION //////////////////////

class CameraMatrixCorrectorV2: public CameraMatrixCorrectorV2Base
{
public:

  CameraMatrixCorrectorV2();
  ~CameraMatrixCorrectorV2();


  void execute(CameraInfo::CameraID id);

  void execute()
  {
    execute(CameraInfo::Top);
    execute(CameraInfo::Bottom);
  }

private:
  CameraInfo::CameraID cameraID;

  typedef double (CameraMatrixCorrectorV2::*ErrorFunction)(double, double);

  void calibrate(ErrorFunction errorFunction);
  void reset_calibration();
  double projectionError(double offsetX, double offsetY);
  double horizonError(double offsetX, double offsetY);

  void calibrate1965();

  DOUBLE_CAM_PROVIDE(CameraMatrixCorrectorV2,DebugImageDrawings);
  DOUBLE_CAM_REQUIRE(CameraMatrixCorrectorV2,CameraMatrix);
  DOUBLE_CAM_REQUIRE(CameraMatrixCorrectorV2,GoalPercept);
  DOUBLE_CAM_REQUIRE(CameraMatrixCorrectorV2,CameraInfo);
};

#endif //_CameraMatrixCorrectorV2_h_
