#include "TeamCommunicator.h"


TeamCommunicator::TeamCommunicator()
  :lastSentTimestamp(0)
{
}

void TeamCommunicator::execute()
{
  const naoth::TeamMessageData& teamMessageData = getTeamMessageData();

  for(vector<string>::const_iterator iter = teamMessageData.data.begin();
      iter != teamMessageData.data.end(); ++iter)
  {
    handleMessage(*iter);
  }

  // only send data in intervals of 500ms
  if(getFrameInfo().getTimeSince(lastSentTimestamp) > 500)
  {
    // send data
    naothmessages::TeamCommMessage msg;
    createMessage(msg);

    getRobotMessageData().data = msg.SerializeAsString();
    lastSentTimestamp = getFrameInfo().getTime();
  }
}

void TeamCommunicator::handleMessage(const string& data)
{
  naothmessages::TeamCommMessage msg;
  msg.ParseFromString(data);

  int num = msg.playernumber();

  TeamMessage::Data& content = getTeamMessage().data[num];
  content.frameInfo.setTime( getFrameInfo().getTime() );
  content.message = msg;
}

void TeamCommunicator::createMessage(naothmessages::TeamCommMessage &msg)
{

  msg.set_playernumber(getPlayerInfo().gameData.playerNumber);
  msg.set_teamnumber(getPlayerInfo().gameData.teamNumber);
  msg.set_ispenalized(getPlayerInfo().gameData.gameState == GameData::penalized);
  msg.set_wasstriker(getPlayerInfo().isPlayingStriker);

  // TODO: set falldown state in teamcomm message
  /*
  msg.set_isfallendown(theBodyState.fall_down_state != BodyState::upright
    || theMotionStatus.currentMotion == MotionRequestID::stand_up_from_back
    || theMotionStatus.currentMotion == MotionRequestID::stand_up_from_front);
  */

  // TODO: set ball and pose info in teamcomm message
  /*
  msg.set_timetoball(theSoccerStrategy.timeToBall);

  msg.set_timesinceballwasseen(
    getFrameInfo().getTimeSince(theBallModel.frameInfoWhenBallWasSeen.time));
  msg.mutable_ballposition()->set_x(theBallModel.position.x);
  msg.mutable_ballposition()->set_y(theBallModel.position.y);

  msg.mutable_positiononfield()->set_rotation(theRobotPose.rotation);
  msg.mutable_positiononfield()->mutable_translation()->set_x(theRobotPose.translation.x);
  msg.mutable_positiononfield()->mutable_translation()->set_y(theRobotPose.translation.y);
*/
}

TeamCommunicator::~TeamCommunicator()
{
}
