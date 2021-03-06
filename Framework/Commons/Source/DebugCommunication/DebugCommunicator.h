/* 
 * File:   DebugCommunicator.h
 * Author: thomas
 *
 * Created on 8. march 2009, 19:31
 */

#ifndef _DEBUGCOMMUNICATOR_H
#define _DEBUGCOMMUNICATOR_H

#include <gio/gio.h>

/**
* TCP/IP based debug communication.
* Please note that this class is not thread-safe, use an external
* synchronization mechanism to ensure that only one threads interacts with
* the communicator at the same time.
*/
class DebugCommunicator
{
public:
  DebugCommunicator();
  virtual ~DebugCommunicator();

  /**
  * Inits the DebugCommunicator, binds and listens to its underlying socket.
  *
  * @param port The port the socket will listen to.
  */
  void init(unsigned short port);

  /**
  * Accept a connection made by the outside world.
  *
  * @param timeout Time in seconds which should be waited for connection.
  *                 0 means forever.
  *
  * @return True if connection was etablished. False on error.
  */
  bool connect(int timeout);
  /**
  * Disconnects a existing connection.
  */
  void disconnect();

  bool isConnected();

  /**
  * Send a message. Will block until whole message was send.
  *
  * @param raw data to send
  * @param size size of the data
  *
  * @return True if message could be send, false if some error occured.
  */
  bool sendMessage(gint32 id, const char* data, size_t size);

  /**
  * Read a new message. Blocks until a complete message was received or an
  * error occured.
  * Complete Messages are always ended by a "\n" character (which is not part
  * of the result)
  *
  * @return A null terminated message string or NULL if nothing to read after timeout
  */
  GString* readMessage(gint32& id);

  /** 
  * Set the time after which the connection should be closed in case of inactivity.
  * 0 - means the connection never times out.
  */
  void setTimeOut(unsigned int t) {
    this->time_out_delta = t;
  }

private:
  GSocket* serverSocket;
  GSocket* connection;

  unsigned short port;
  bool fatalFail;
  unsigned long long time_of_last_message;
  unsigned int time_out_delta;

  GError* internalSendMessage(gint32 id, const char* data, size_t size);
  GError* internalInit();
  gint32 internalReadMessage(GString** result, GError** err);
};

#endif  /* _DEBUGCOMMUNICATOR_H */

