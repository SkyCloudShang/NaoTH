/*
 * 
 */

package de.hu_berlin.informatik.ki.nao.dialogs.drawings;

import java.awt.Graphics2D;

/**
 *
 * @author Heinrich Mellmann
 */
public class FillOval extends Oval
{
  public FillOval(String[] args)
  {
      super(args);
  }

  @Override
  public void draw(Graphics2D g2d)
  {
      g2d.fillOval(x - radiusX, y - radiusY, 2*radiusX, 2*radiusY);
  }//end draw
}//end class FillOval