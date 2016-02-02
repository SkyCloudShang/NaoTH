/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package de.naoth.rc.dataformats;

import de.naoth.rc.components.ExceptionDialog;
import de.naoth.rc.tools.BasicReader;
import de.naoth.rc.logmanager.LogDataFrame;
import java.io.EOFException;
import java.io.File;
import java.io.IOException;
import java.io.RandomAccessFile;
import java.io.Serializable;
import java.nio.channels.FileChannel;
import java.util.ArrayList;
import java.util.HashMap;

/**
 *
 * @author thomas
 */
public class LogFile implements Serializable
{

  private final String originalFile;
  private final ArrayList<Frame> frameList = new ArrayList<>();
  private transient BasicReader reader = null;

  public LogFile(String originalFile) throws IOException
  {
    this.originalFile = originalFile;
    getReader();
    //this.raf = new RandomAccessFile(this.openedFile, "r");
  }

  private void scan(BasicReader data_in) throws IOException
  {
    int currentFrameNumber = -1;
    int currentFrameSize = 0;
    int currentFramePos = 0;
    while (true)
    {
      try
      {
        int fragmentFrameSize = 0;
        int frameNumber = data_in.readInt();
        fragmentFrameSize += 4;
        // plausibility check
        if (currentFrameNumber > -1 && (frameNumber < currentFrameNumber || frameNumber < 0))
        {
          ExceptionDialog dlg = new ExceptionDialog(null, new IOException("corrupt frame number: " + frameNumber + " after " + currentFrameNumber));
          dlg.setVisible(true);
          break;
        }
        if (frameNumber - currentFrameNumber > 30)
        {
          System.out.println("frame jump: " + currentFrameNumber + " -> " + frameNumber);
        }
        String currentName = data_in.readString();
        fragmentFrameSize += currentName.length() + 1;
        int currentSize = data_in.readInt();
        fragmentFrameSize += 4;
        fragmentFrameSize += currentSize;

        if (currentFrameNumber != frameNumber && currentFrameNumber != -1)
        {
          Frame frame = new Frame(currentFrameNumber, currentFrameSize, currentFramePos);
          frameList.add(frame);
          currentFramePos += currentFrameSize;
          currentFrameSize = 0;
        } //end if
        currentFrameSize += fragmentFrameSize;
        currentFrameNumber = frameNumber;
        long skippedSize = data_in.skip(currentSize);
      } catch (EOFException eof)
      {
        System.out.println("End of File");
        break;
      }
    } //end while
  } //end parseLogFile

  public HashMap<String, LogDataFrame> readFrame(int frameId) throws IOException
  {
    if (frameId >= this.frameList.size())
    {
      return null;
    }

    Frame frame = this.frameList.get(frameId);
    if (frame == null)
    {
      return null;
    }
    // jump to the begin of the frame
    getReader().seek(frame.position);
    int numberOfReadBytes = 0;
    HashMap<String, LogDataFrame> currentFrame = new HashMap<>();
    while (numberOfReadBytes < frame.size)
    {
      int frameNumber = getReader().readInt();
      numberOfReadBytes += 4;
      if (frameNumber != frame.number)
      {
        throw new IOException("corrupt frame number: " + frameNumber + " expected " + frame.number);
      }
      String currentName = getReader().readString();
      numberOfReadBytes += currentName.length() + 1;
      int currentSize = getReader().readInt();
      numberOfReadBytes += 4;
      byte[] buffer = new byte[currentSize];
      numberOfReadBytes += getReader().read(buffer);
      LogDataFrame logDataFrame = new LogDataFrame(frameNumber, currentName, buffer);
      currentFrame.put(currentName, logDataFrame);
    } //end while
    return currentFrame;
  } //end readFrame

  class Frame implements Serializable
  {

    final int number;
    final int size;
    final int position;

    public Frame(int number, int size, int position)
    {
      this.number = number;
      this.size = size;
      this.position = position;
    }
  } //end class Frame

  public int getFrameCount()
  {
    return frameList.size();
  }

  public File getOriginalFile()
  {
    return new File(originalFile);
  }

  private BasicReader getReader() throws IOException
  {
    if (reader == null)
    {
      File file = new File(originalFile);
      FileChannel channel = FileChannel.open(file.toPath());
      if (channel.size() >= Integer.MAX_VALUE)
      {
        reader = new BasicReader(new RandomAccessFile(file, "r"));
      } else
      {
        reader = new BasicReader(channel.map(FileChannel.MapMode.READ_ONLY, 0, channel.size()));
      }
      scan(reader);
      return reader;
    } else
    {
      return reader;
    }
  }

}
