/**
 * @file VisualObstacleLocator.h
 *
 * @author <a href="mailto:mellmann@informatik.hu-berlin.de">Heinrich Mellmann</a>
 * @author <a href="mailto:yasinovs@informatik.hu-berlin.de">Kirill Yasinovskiy</a>
 * Implementation of class RadarObstacleLocator
 */

#include "VisualObstacleLocator.h"
#include "Tools/CameraGeometry.h"

VisualObstacleLocator::VisualObstacleLocator()
{
  DEBUG_REQUEST_REGISTER("VisualObstacleLocator:RadarGrid:drawGrid", "draw the modelled Obstacles on the field", false);
  DEBUG_REQUEST_REGISTER("VisualObstacleLocator:RadarGrid:resetGrid", "reset grid each cognition frame", false);

  DEBUG_REQUEST_REGISTER("VisualObstacleLocator:draw_field_of_view", "draw current field of view", false);
}

void VisualObstacleLocator::execute()
{

  DEBUG_REQUEST("VisualObstacleLocator:draw_field_of_view",
    FIELD_DRAWING_CONTEXT;
    PEN("000000", 10);
  Vector2<double> lu;
  CameraGeometry::imagePixelToFieldCoord(
    getCameraMatrix(), 
    getImage().cameraInfo,
    0.0, 
    0.0, 
    0.0,
    lu);

  Vector2<double> ru;
  CameraGeometry::imagePixelToFieldCoord(
    getCameraMatrix(), 
    getImage().cameraInfo,
    (double)getImage().cameraInfo.resolutionWidth, 
    0.0, 
    0.0,
    ru);

  Vector2<double> rb;
  CameraGeometry::imagePixelToFieldCoord(
    getCameraMatrix(), 
    getImage().cameraInfo,
    (double)getImage().cameraInfo.resolutionWidth, 
    (double)getImage().cameraInfo.resolutionHeight, 
    0.0,
    rb);

  Vector2<double> lb;
  CameraGeometry::imagePixelToFieldCoord(
    getCameraMatrix(), 
    getImage().cameraInfo,
    0.0, 
    (double)getImage().cameraInfo.resolutionHeight, 
    0.0,
    lb);

  LINE(lu.x, lu.y, ru.x, ru.y);
  LINE(ru.x, ru.y, rb.x, rb.y);
  LINE(rb.x, rb.y, lb.x, lb.y);
  LINE(lb.x, lb.y, lu.x, lu.y);
  );

  DEBUG_REQUEST("VisualObstacleLocator:draw_field_of_view",
    getRadarGrid().resetGrid();
  );

  // store odometry data
  odometryDelta = getOdometryData() - lastRobotOdometry;
  lastRobotOdometry = getOdometryData();
  // set grid's time
  getRadarGrid().setCurrentTime(getFrameInfo().getTime());
   
  //set the radar grid
  for(unsigned int i = 0; i < getScanLineEdgelPercept().endPoints.size(); i++)
  {
    const ScanLineEdgelPercept::EndPoint& point = getScanLineEdgelPercept().endPoints[i];
    if(//point.posInImage.y > 10 && 
       //point.posInImage.y < 200 && 
           (point.color != (int) ColorClasses::green)
      )
    {
      getRadarGrid().addObstaclePoint(point.posOnField);
    }
    else
    {
      getRadarGrid().addNonObstaclePoint(point.posOnField);
    }
  }//end for

  getRadarGrid().ageGrid();


  odometryDelta = lastRobotOdometry - getOdometryData();
  getRadarGrid().updateGridByOdometry(odometryDelta);


  DEBUG_REQUEST("VisualObstacleLocator:RadarGrid:drawGrid",
    getRadarGrid().drawFieldContext();
  );

  //check whether we have an obstacle
  getRadarGrid().checkValid();
}//end execute
