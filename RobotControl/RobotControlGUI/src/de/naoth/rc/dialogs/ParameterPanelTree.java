/*
 * ParameterPanel.java
 *
 * Created on 17. Juli 2008, 21:21
 */
package de.naoth.rc.dialogs;

import de.naoth.rc.RobotControl;
import de.naoth.rc.components.treetable.ModifyDataModel;
import de.naoth.rc.components.treetable.ParameterDataModel;
import de.naoth.rc.components.treetable.TreeTable;
import de.naoth.rc.core.dialog.AbstractDialog;
import de.naoth.rc.core.dialog.DialogPlugin;
import de.naoth.rc.core.manager.ObjectListener;
import de.naoth.rc.core.manager.SwingCommandExecutor;
import de.naoth.rc.server.Command;
import java.util.ArrayList;
import javax.swing.DefaultComboBoxModel;
import javax.swing.JScrollPane;
import net.xeoh.plugins.base.annotations.PluginImplementation;
import net.xeoh.plugins.base.annotations.injections.InjectPlugin;

/**
 *
 * @author  Heinrich Mellmann
 */
public class ParameterPanelTree extends AbstractDialog
{

  @PluginImplementation
  public static class Plugin extends DialogPlugin<ParameterPanelTree>
  {
    @InjectPlugin
    public static RobotControl parent;
    @InjectPlugin
    public static SwingCommandExecutor commandExecutor;
  }

  //needed to synchronize the update procedure
  private final ArrayList<ParameterListItem> parameterLists = new ArrayList<ParameterListItem>();
  // number of sources which already performed ther update
  private int updateSources = 0;
  private final int EXPECTED_SOURCES = 2;
  
  private ParameterDataModel treeTableModel = new ParameterDataModel();
  private TreeTable myTreeTable = new TreeTable(treeTableModel);
  
  public ParameterPanelTree()
  {
    initComponents();
	
    jScrollPane.setViewportView(myTreeTable);
    /*
    jTextArea.addKeyListener(new KeyAdapter()
    {
      @Override
      public void keyPressed(KeyEvent e)
      {
        int key = e.getKeyCode();
        if (key == KeyEvent.VK_ENTER)
        {
          sendParameters();
          
          int k = jTextArea.getCaretPosition();
          if(k > 0) {
            jTextArea.setCaretPosition(k-1);
          }
        }
      }
    });
    */
  }//end constructor

    private void updateParameterLists() 
    {
        updateSources++;

        if (updateSources == EXPECTED_SOURCES) {
            
            ParameterListItem selectedList = null;
            if (cbParameterId.getSelectedItem() != null) {
                selectedList = (ParameterListItem) cbParameterId.getSelectedItem();
            }
            
            DefaultComboBoxModel boxModel = new DefaultComboBoxModel();
            for (ParameterListItem i : parameterLists) {
                boxModel.addElement(i);
            }
            
            this.cbParameterId.setModel(boxModel);
            
            if(selectedList != null) {
                this.cbParameterId.setSelectedItem(selectedList);
            } else {
                this.cbParameterId.setSelectedIndex(0);
            }
            
            parameterLists.clear();
            updateSources = 0;
            
            System.out.println(selectedList);
        }
    }

  /** This method is called from within the constructor to
   * initialize the form.
   * WARNING: Do NOT modify this code. The content of this method is
   * always regenerated by the Form Editor.
   */
  @SuppressWarnings("unchecked")
    // <editor-fold defaultstate="collapsed" desc="Generated Code">//GEN-BEGIN:initComponents
    private void initComponents() {

        jToolBar1 = new javax.swing.JToolBar();
        jToggleButtonList = new javax.swing.JToggleButton();
        cbParameterId = new javax.swing.JComboBox();
        jToggleButtonRefresh = new javax.swing.JToggleButton();
        jButtonSend = new javax.swing.JButton();
        jScrollPane = new javax.swing.JScrollPane();

        jToolBar1.setFloatable(false);
        jToolBar1.setRollover(true);

        jToggleButtonList.setText("update");
        jToggleButtonList.setFocusable(false);
        jToggleButtonList.setHorizontalTextPosition(javax.swing.SwingConstants.CENTER);
        jToggleButtonList.setVerticalTextPosition(javax.swing.SwingConstants.BOTTOM);
        jToggleButtonList.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                jToggleButtonListActionPerformed(evt);
            }
        });
        jToolBar1.add(jToggleButtonList);

        cbParameterId.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                cbParameterIdActionPerformed(evt);
            }
        });
        jToolBar1.add(cbParameterId);

        jToggleButtonRefresh.setText("Get");
        jToggleButtonRefresh.setFocusable(false);
        jToggleButtonRefresh.setHorizontalTextPosition(javax.swing.SwingConstants.CENTER);
        jToggleButtonRefresh.setVerticalTextPosition(javax.swing.SwingConstants.BOTTOM);
        jToggleButtonRefresh.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                jToggleButtonRefreshActionPerformed(evt);
            }
        });
        jToolBar1.add(jToggleButtonRefresh);

        jButtonSend.setText("Set");
        jButtonSend.setFocusable(false);
        jButtonSend.setHorizontalTextPosition(javax.swing.SwingConstants.CENTER);
        jButtonSend.setVerticalTextPosition(javax.swing.SwingConstants.BOTTOM);
        jButtonSend.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                jButtonSendActionPerformed(evt);
            }
        });
        jToolBar1.add(jButtonSend);

        javax.swing.GroupLayout layout = new javax.swing.GroupLayout(this);
        this.setLayout(layout);
        layout.setHorizontalGroup(
            layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addComponent(jToolBar1, javax.swing.GroupLayout.DEFAULT_SIZE, 503, Short.MAX_VALUE)
            .addComponent(jScrollPane)
        );
        layout.setVerticalGroup(
            layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(layout.createSequentialGroup()
                .addComponent(jToolBar1, javax.swing.GroupLayout.PREFERRED_SIZE, 25, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addGap(0, 0, 0)
                .addComponent(jScrollPane, javax.swing.GroupLayout.DEFAULT_SIZE, 287, Short.MAX_VALUE))
        );
    }// </editor-fold>//GEN-END:initComponents

private void jToggleButtonRefreshActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_jToggleButtonRefreshActionPerformed
  if (jToggleButtonRefresh.isSelected())
  {
    getParameterList();
  }
}//GEN-LAST:event_jToggleButtonRefreshActionPerformed

private void jButtonSendActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_jButtonSendActionPerformed
  sendParameters();
}//GEN-LAST:event_jButtonSendActionPerformed

private void cbParameterIdActionPerformed(java.awt.event.ActionEvent evt)//GEN-FIRST:event_cbParameterIdActionPerformed
{//GEN-HEADEREND:event_cbParameterIdActionPerformed
    getParameterList();
}//GEN-LAST:event_cbParameterIdActionPerformed

private void jToggleButtonListActionPerformed(java.awt.event.ActionEvent evt)//GEN-FIRST:event_jToggleButtonListActionPerformed
{//GEN-HEADEREND:event_jToggleButtonListActionPerformed
    listParameters();
}//GEN-LAST:event_jToggleButtonListActionPerformed

  private class ParameterListItem
  {
      public final String owner;
      public final String name;
      
      public ParameterListItem(String owner, String name)
      {
          this.owner = owner;
          this.name = name;
      }
      
      Command getCommandGET() {
          return new Command(owner + ":ParameterList:get")
                  .addArg("<name>", name);
      }
      
      Command getCommandSET() {
          return new Command(owner + ":ParameterList:set")
                  .addArg("<name>", name);
      }
      
      @Override
      public String toString() 
      {
          return "[" + owner + "] " + name;
      }

      @Override
      public boolean equals(Object obj) {
        if(obj instanceof ParameterListItem) {
            ParameterListItem other = (ParameterListItem)obj;
            return owner.equals(other.owner) && name.equals(other.name);
        }
        return false;
      }
  }

  class ParameterListHandlerGet implements ObjectListener<byte[]>
  {
    @Override
    public void newObjectReceived(byte[] object)
    {
        treeTableModel = new ParameterDataModel();
        myTreeTable = new TreeTable(treeTableModel);
        
        String str = new String(object);
        String[] params = str.split("\\n");
        
        for(String p: params) {
            String[] s = p.split("=");
            ParameterDataModel.ParameterDataNode n = treeTableModel.insertPath(s[0], "\\.");
            
            try {
                n.setValue(Double.parseDouble(s[1]));
            } catch (NumberFormatException ex) {
                try {
                    n.setValue(Boolean.parseBoolean(s[1]));
                } catch (NumberFormatException bex) 
                {
                }
            }
        }
        jScrollPane.setViewportView(myTreeTable);
        
        jToggleButtonRefresh.setSelected(false);
    }
    
    @Override
    public void errorOccured(String cause)
    {
      dispose();
    }
  }
  
  class ParameterListHandlerSet implements ObjectListener<byte[]>
  {
    @Override
    public void newObjectReceived(byte[] object)
    {
        // do nothing
    }
    
    @Override
    public void errorOccured(String cause)
    {
      dispose();
    }
  }
  
  class ParameterListHandlerList implements ObjectListener<byte[]>
  {
    private final String owner;
    
    public ParameterListHandlerList(String owner)
    {
        this.owner = owner;
    }
    
    @Override
    public void newObjectReceived(byte[] object)
    {
        String strResult = new String(object);
        
        String[] parameterListNames = strResult.split("\n");
        for (String name : parameterListNames) {
          parameterLists.add(new ParameterListItem(owner, name));
        }
        
        jToggleButtonList.setSelected(false);
        updateParameterLists();
    }
    
    @Override
    public void errorOccured(String cause)
    {
      dispose();
    }
  }


private void sendParameters()
{
  if (Plugin.parent.checkConnected())
  {
    Command cmd = ((ParameterListItem) cbParameterId.getSelectedItem()).getCommandSET();

    String text = ""; //this.jTextArea.getText();

    text = text.replaceAll("( |\t)+", "");
    String[] lines = text.split("(\n)+");
    for (String l : lines)
    {
      String[] splitted = l.split("=");
      if (splitted.length == 2)
      {
        String key = splitted[0].trim();
        String value = splitted[1].trim();
        // remove the last ;
        if (value.charAt(value.length() - 1) == ';')
        {
          value = value.substring(0, value.length() - 1);
        }

        cmd.addArg(key, value);
      }
    }//end for
    
    Plugin.commandExecutor.executeCommand(new ParameterListHandlerSet(), cmd);
    
    // update everything
    //listParameters();
    
    // this is better, but less robust
    getParameterList();
  }
  else
  {
    jToggleButtonRefresh.setSelected(false);
  }
}

private void listParameters()
{
    if (Plugin.parent.checkConnected())
    {
      Plugin.commandExecutor.executeCommand(new ParameterListHandlerList("Cognition"), new Command("Cognition:ParameterList:list"));
      Plugin.commandExecutor.executeCommand(new ParameterListHandlerList("Motion"), new Command("Motion:ParameterList:list"));
    }
    else
    {
      jToggleButtonList.setSelected(false);
    }
}//end listParameters

  private void getParameterList()
  {
    System.out.println("test");
    if (Plugin.parent.checkConnected())
    {
      if (cbParameterId.getSelectedItem() != null)
      {
        Command cmd = ((ParameterListItem) cbParameterId.getSelectedItem()).getCommandGET();
        Plugin.commandExecutor.executeCommand(new ParameterListHandlerGet(), cmd);
      }
    }
    else
    {
      jToggleButtonRefresh.setSelected(false);
    }
  }//end refresh

  @Override
  public void dispose()
  {
    System.out.println("Dispose is not implemented for: " + this.getClass().getName());
  }
  
    // Variables declaration - do not modify//GEN-BEGIN:variables
    private javax.swing.JComboBox cbParameterId;
    private javax.swing.JButton jButtonSend;
    private javax.swing.JScrollPane jScrollPane;
    private javax.swing.JToggleButton jToggleButtonList;
    private javax.swing.JToggleButton jToggleButtonRefresh;
    private javax.swing.JToolBar jToolBar1;
    // End of variables declaration//GEN-END:variables
}
