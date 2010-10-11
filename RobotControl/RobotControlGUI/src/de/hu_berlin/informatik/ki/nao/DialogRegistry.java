/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

package de.hu_berlin.informatik.ki.nao;

import java.awt.Color;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.LinkedList;
import java.util.Set;
import javax.swing.JMenu;
import javax.swing.JMenuItem;
import javax.swing.JPanel;
import javax.swing.border.LineBorder;
import org.flexdock.docking.Dockable;
import org.flexdock.docking.DockingConstants;
import org.flexdock.docking.DockingPort;
import org.flexdock.view.View;
import org.flexdock.view.Viewport;

/**
 *
 * @author thomas
 */
public class DialogRegistry
{

  private JMenu menu;
  private DockingPort dock;
  private LinkedList<View> viewChronologicalOrder;

  public DialogRegistry(JMenu menu, DockingPort dock)
  {
    this.viewChronologicalOrder = new LinkedList<View>();
    this.menu = menu;
    this.dock = dock;
  }

  public void registerDialog(final Dialog dialog)
  {
    String dialogName = dialog.getClass().getSimpleName();
    
    if(menu != null)
    {
      JMenuItem newItem = new JMenuItem(dialogName);
      newItem.addActionListener(new ActionListener()
      {

        public void actionPerformed(ActionEvent e)
        {
          dockDialog(dialog);
        }
      });
      menu.add(newItem);
    }
  
  }

  private View createView(String id, String text, JPanel panel)
  {
    final View result = new View(id, text);
    panel.setBorder(new LineBorder(Color.GRAY, 1));
    result.setContentPane(panel);

    result.addAction(DockingConstants.CLOSE_ACTION);
    result.addAction(DockingConstants.PIN_ACTION);

    return result;
  }

  public void dockDialog(Dialog dialog)
  {

    String dialogName = dialog.getClass().getSimpleName();

    // check if view already exists
    Set<Dockable> dockables = dock.getDockables();
    boolean isAlreadyDocked = false;
    for(Dockable d : dockables)
    {
      if(dialogName.equals(d.getPersistentId()))
      {
        isAlreadyDocked = true;
        d.getDockingProperties().setActive(true);
        break;
      }
    }

    if(!isAlreadyDocked)
    {
      View newView = createView(dialogName, dialogName, dialog.getPanel());

      if(viewChronologicalOrder.isEmpty())
      {
        dock.dock((Dockable) newView, Viewport.EAST_REGION);
      }
      else
      {
        viewChronologicalOrder.getLast().dock(newView);
      }
      viewChronologicalOrder.addLast(newView);
    }
  }
  

}