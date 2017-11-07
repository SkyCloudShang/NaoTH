#!/usr/bin/env python3
# -*- coding: utf8 -*-

'''
    Using the 'GoPro API for Python' to communicate with the GoPro:
    https://github.com/KonradIT/gopro-py-api
'''

import sys
import socket
import traceback
import argparse
import logging

from GameControlData import GameControlData
from goprocam import GoProCamera, constants
import Network

LOGGER_NAME = __name__
LOGGER_FMT  = '%(levelname)s: %(message)s'
LOGGER_FMT_CHILD = '%(levelname)s[%(name)s]: %(message)s'

def parseArguments():
    parser = argparse.ArgumentParser(description='Starts a GoPro controller (on linux!)', epilog="Example: {} -n 10.0.4.255 -p 10004".format(sys.argv[0]))
    parser.add_argument('-v', '--verbose', action='store_true', help='activate verbose mode')
    parser.add_argument('-d', '--device', action='store', help='the device used to connect to the GoPro wifi network (eg. "wifi0")')
    parser.add_argument('-s', '--ssid',   action='store', required=True, help='the SSID name of the GoPro wifi network (eg. "NAOCAM")')
    parser.add_argument('-p', '--passwd', action='store', required=True, help='the password of the GoPro wifi network')

    return parser.parse_args()

def setupLogger(verbose:bool = False):
    lh = logging.StreamHandler()
    lh.setFormatter(LogFormatter())

    lvl = logging.DEBUG if verbose else logging.INFO
    logging.basicConfig(level=lvl, format=LOGGER_FMT)
    logger = logging.getLogger(LOGGER_NAME)
    logger.propagate = False
    logger.addHandler(lh)

    Network.logger.addHandler(lh)
    Network.logger.propagate = False

    #GoProCamera.logger.addHandler(lh)
    #GoProCamera.logger.propagate = False

    return logger

class LogFormatter(logging.Formatter):
    def format(self, record):
        if record.name != LOGGER_NAME:
            self._style._fmt = LOGGER_FMT_CHILD
        else:
            self._style._fmt = LOGGER_FMT

        return logging.Formatter.format(self, record) #super(LogFormatter, self).format(format)


if __name__ == '__main__':
    if not sys.platform.startswith('linux'):
        sys.stderr.write("Only linux based systems are currently supported!")
        exit(1)

    #args = { 'device': 'wifi0', 'ssid': 'NAOCAM', 'password':'a1b0a1b0a1' }
    #  GP26329941 / cycle9210
    args = parseArguments()

    logger = setupLogger(args.verbose)

    # TODO: check device state? (enabled/disabled)

    logger.info("Setting up network")

    # check wifi device
    device = Network.getWifiDevice(args.device)
    if device is not None:
        logger.info("Using device %s", device)
        # check/connect to wifi network
        network = Network.connectToSSID(device, args.ssid, args.passwd)
        if network is not None:
            logger.info("Connected to %s", network)
            # get GoPro
            logger.info("Connecting to GoPro ...")
            cam = GoProCamera.GoPro()
            if cam.getStatusRaw():
                # set GoPro to video mode
                logger.debug("Set GoPro to 'video' mode")
                cam.mode(constants.Mode.VideoMode)

                # listen to gamecontroller
                logger.debug("Listen to GameController")
                s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
                s.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
                s.setsockopt(socket.SOL_SOCKET, socket.SO_BROADCAST, 1)
                s.bind(('', 3838))

                previous_state = GameControlData.STATE_INITIAL
                gc_data = GameControlData()
                while True:
                    try:
                        message, address = s.recvfrom(8192)
                        gc_data.unpack(message)

                        # TODO: also print recording state!
                        print("\rcurrent game state: %s"%(gc_data.getGameState()), end="", flush=True)

                        if previous_state == GameControlData.STATE_INITIAL and gc_data.gameState == GameControlData.STATE_READY:
                            logger.debug("Start recording")
                            # TODO: check recording mode before start recording!
                            cam.shutter(constants.start)
                        if previous_state == GameControlData.STATE_PLAYING and gc_data.gameState == GameControlData.STATE_FINISHED:
                            logger.debug("Stop recording")
                            cam.shutter(constants.stop)

                        # TODO:
                        #cam.KeepAlive()

                        previous_state = gc_data.gameState
                    except (KeyboardInterrupt, SystemExit):
                        print("") # intentionally print empty line
                        break
                    except:
                        traceback.print_exc()
                # close socket
                s.close()