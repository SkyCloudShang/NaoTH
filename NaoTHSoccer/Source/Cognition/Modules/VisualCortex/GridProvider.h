/**
* @file GridProvider.h
*
* @author <a href="mailto:mellmann@informatik.hu-berlin.de">Heinrich Mellmann</a>
* Declaration of class GridProvider
*/

#ifndef _GridProvider_h_
#define _GridProvider_h_

#include <ModuleFramework/Module.h>

// Representations
#include "Representations/Infrastructure/Image.h"
#include "Representations/Infrastructure/ColoredGrid.h"
#include "Representations/Perception/Histograms.h"
#include "Representations/Modeling/ColorClassificationModel.h"

//Debug
#include "Representations/Debug/Stopwatch.h"
#include "Tools/Debug/DebugRequest.h"
#include "Tools/Debug/DebugImageDrawings.h"


#include "Tools/DoubleCamHelpers.h"

//////////////////// BEGIN MODULE INTERFACE DECLARATION ////////////////////

BEGIN_DECLARE_MODULE(GridProvider)
  PROVIDE(StopwatchManager)
  PROVIDE(DebugRequest)
  PROVIDE(DebugImageDrawings)
  PROVIDE(DebugImageDrawingsTop)
  
  REQUIRE(Image)
  REQUIRE(ImageTop)
  REQUIRE(ColorClassificationModel)
  REQUIRE(ColorClassificationModelTop)

  PROVIDE(ColorClassesHistograms)
  PROVIDE(ColorClassesHistogramsTop)
  PROVIDE(ColoredGrid)
  PROVIDE(ColoredGridTop)
END_DECLARE_MODULE(GridProvider)

//////////////////// END MODULE INTERFACE DECLARATION //////////////////////

class GridProvider : public GridProviderBase
{
public:

  GridProvider();
  ~GridProvider(){}


  /** executes the module */
  virtual void execute(CameraInfo::CameraID id);

  void execute()
  {
    execute(CameraInfo::Bottom);
    execute(CameraInfo::Top);
  }

private:
  CameraInfo::CameraID cameraID;

  void calculateColoredGrid();

  DOUBLE_CAM_PROVIDE(GridProvider, DebugImageDrawings);

  DOUBLE_CAM_REQUIRE(GridProvider, Image);
  DOUBLE_CAM_REQUIRE(GridProvider, ColorClassificationModel);

  DOUBLE_CAM_PROVIDE(GridProvider, ColorClassesHistograms);
  DOUBLE_CAM_PROVIDE(GridProvider, ColoredGrid);
};

#endif // _GridProvider_h_
