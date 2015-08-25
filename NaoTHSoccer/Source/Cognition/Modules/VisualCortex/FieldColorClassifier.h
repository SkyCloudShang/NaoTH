/* 
 * File:   FieldColorClassifier.h
 * Author: claas
 * Author: Heinrich Mellmann
 *
 * Created on 15. M�rz 2011, 15:56
 */

#ifndef _FieldColorClassifier_H_
#define _FieldColorClassifier_H_

#include <ModuleFramework/Module.h>

// Representations
#include "Representations/Infrastructure/FrameInfo.h"
#include "Representations/Infrastructure/Image.h" // just for debug
#include "Representations/Perception/FieldColorPercept.h"
#include "Representations/Perception/ArtificialHorizon.h"
#include "Representations/Perception/BodyContour.h"

// Tools
#include <Tools/Math/Vector2.h>
#include <Tools/DataStructures/UniformGrid.h>
#include <Tools/DataStructures/Histogram.h>

// Debug
#include "Representations/Debug/Stopwatch.h"
#include "Tools/Debug/DebugPlot.h"
#include "Tools/Debug/DebugModify.h"
#include "Tools/Debug/DebugRequest.h"
#include "Tools/Debug/DebugImageDrawings.h"
#include "Tools/Debug/DebugParameterList.h"

#include "Tools/DoubleCamHelpers.h"

//////////////////// BEGIN MODULE INTERFACE DECLARATION ////////////////////

BEGIN_DECLARE_MODULE(FieldColorClassifier)
  PROVIDE(StopwatchManager)
  PROVIDE(DebugPlot)
  PROVIDE(DebugModify)
  PROVIDE(DebugRequest)
  PROVIDE(DebugImageDrawings)
  PROVIDE(DebugImageDrawingsTop)
  PROVIDE(DebugParameterList)
  
  REQUIRE(FrameInfo)
  REQUIRE(Image)
  REQUIRE(ImageTop)
  REQUIRE(ArtificialHorizon)
  REQUIRE(ArtificialHorizonTop)
  REQUIRE(BodyContour)
  REQUIRE(BodyContourTop)

  PROVIDE(FieldColorPercept)
  PROVIDE(FieldColorPerceptTop)
END_DECLARE_MODULE(FieldColorClassifier)

//////////////////// END MODULE INTERFACE DECLARATION //////////////////////


class FieldColorClassifier : public  FieldColorClassifierBase
{
public:
  FieldColorClassifier();
  virtual ~FieldColorClassifier();

  void execute()
  {
    execute(CameraInfo::Bottom);
    DEBUG_REQUEST("Vision:FieldColorClassifier:BottomCam:plotV",
      plot("Histograms:BottomCam:V", histogramV);
    );

    execute(CameraInfo::Top);
    DEBUG_REQUEST("Vision:FieldColorClassifier:TopCam:plotV",
      plot("Histograms:TopCam:V", histogramV);
    );
  }

private:
  void execute(const CameraInfo::CameraID id);

  UniformGrid uniformGrid; // subsampling of the image
  Statistics::Histogram<256> histogramV;

private: // debug
  void plot(std::string id, Statistics::HistogramX& histogram) const
  {
    for(int i = 0; i < histogram.size; i++) {
      PLOT_GENERIC(id + ":rawHistogram", i, histogram.rawData[i]);
    }
  }

private: // doublecam
  
  // id of the camera the module is curently running on
  CameraInfo::CameraID cameraID;
  
  DOUBLE_CAM_PROVIDE(FieldColorClassifier, DebugImageDrawings);

  DOUBLE_CAM_REQUIRE(FieldColorClassifier, Image);
  DOUBLE_CAM_REQUIRE(FieldColorClassifier, BodyContour);
  DOUBLE_CAM_REQUIRE(FieldColorClassifier, ArtificialHorizon);
  DOUBLE_CAM_PROVIDE(FieldColorClassifier, FieldColorPercept);
};

#endif  /* _FieldColorClassifier_H_ */
