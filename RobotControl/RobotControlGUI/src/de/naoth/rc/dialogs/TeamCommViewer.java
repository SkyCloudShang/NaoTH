/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * TeamCommViewer.java
 *
 * Created on 08.11.2010, 21:41:28
 */

package de.naoth.rc.dialogs;
import de.naoth.rc.AbstractDialog;
import de.naoth.rc.DialogPlugin;
import de.naoth.rc.Helper;
import de.naoth.rc.RobotControl;
import de.naoth.rc.dataformats.SPLMessage;
import de.naoth.rc.dialogs.panels.RobotStatus;
import de.naoth.rc.manager.TeamCommDrawingManager;
import java.io.IOException;
import java.net.InetSocketAddress;
import java.net.SocketAddress;
import java.net.SocketException;
import java.nio.ByteBuffer;
import java.nio.ByteOrder;
import java.nio.channels.AsynchronousCloseException;
import java.nio.channels.DatagramChannel;
import java.util.Collections;
import java.util.HashMap;
import java.util.Map;
import java.util.Map.Entry;
import java.util.Timer;
import java.util.TimerTask;
import java.util.TreeMap;
import java.util.logging.Level;
import java.util.logging.Logger;
import javax.swing.SwingUtilities;
import net.xeoh.plugins.base.annotations.PluginImplementation;
import net.xeoh.plugins.base.annotations.injections.InjectPlugin;

/**
 *
 * @author Heinrich Mellmann
 */
public class TeamCommViewer extends AbstractDialog
{

  @PluginImplementation
  public static class Plugin extends DialogPlugin<TeamCommViewer>
  {
      @InjectPlugin
      public static RobotControl parent;
      @InjectPlugin
      public static TeamCommDrawingManager teamCommDrawingManager;
  }//end Plugin
  
  private final HashMap<String,RobotStatus> robotsMap;
  
  private Timer timerCheckMessages;
  private final TeamCommListener teamCommListener = new TeamCommListener();
  
    /** Creates new form TeamCommViewer */
    public TeamCommViewer() {
      initComponents();

      this.robotsMap = new HashMap<String,RobotStatus>();
    }

    /** This method is called from within the constructor to
     * initialize the form.
     * WARNING: Do NOT modify this code. The content of this method is
     * always regenerated by the Form Editor.
     */
    @SuppressWarnings("unchecked")
  // <editor-fold defaultstate="collapsed" desc="Generated Code">//GEN-BEGIN:initComponents
  private void initComponents()
  {

    robotStatusPanel = new javax.swing.JPanel();
    btListen = new javax.swing.JToggleButton();
    portNumber = new javax.swing.JFormattedTextField();

    robotStatusPanel.setLayout(new java.awt.GridLayout(5, 1, 0, 5));

    btListen.setText("Listen to TeamComm");
    btListen.addActionListener(new java.awt.event.ActionListener()
    {
      public void actionPerformed(java.awt.event.ActionEvent evt)
      {
        btListenActionPerformed(evt);
      }
    });

    portNumber.setColumns(6);
    portNumber.setFormatterFactory(new javax.swing.text.DefaultFormatterFactory(new javax.swing.text.NumberFormatter(new java.text.DecimalFormat("#"))));
    portNumber.setText("10400");
    portNumber.setToolTipText("Port to listen at");

    javax.swing.GroupLayout layout = new javax.swing.GroupLayout(this);
    this.setLayout(layout);
    layout.setHorizontalGroup(
      layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
      .addGroup(layout.createSequentialGroup()
        .addContainerGap()
        .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
          .addGroup(layout.createSequentialGroup()
            .addComponent(btListen)
            .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
            .addComponent(portNumber, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
            .addGap(0, 0, Short.MAX_VALUE))
          .addComponent(robotStatusPanel, javax.swing.GroupLayout.Alignment.TRAILING, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE))
        .addContainerGap())
    );
    layout.setVerticalGroup(
      layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
      .addGroup(layout.createSequentialGroup()
        .addContainerGap()
        .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
          .addComponent(btListen)
          .addComponent(portNumber, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE))
        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
        .addComponent(robotStatusPanel, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE))
    );
  }// </editor-fold>//GEN-END:initComponents

    private void btListenActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_btListenActionPerformed
      if(this.btListen.isSelected())
      {
        robotStatusPanel.setVisible(true);
        
        try {
          int port = Integer.parseInt(portNumber.getText().trim());
          this.teamCommListener.connect(port);
        }
        catch(NumberFormatException ex)
        {
          Helper.handleException("Invalid port number", ex);
        } catch (Exception ex) {}
        
        
        this.timerCheckMessages = new Timer();
        this.timerCheckMessages.scheduleAtFixedRate(new TimerTask() {
            @Override
            public void run() {
                synchronized(teamCommListener.messageMap) 
                {
                    if(teamCommListener.messageMap.isEmpty())
                    {
                      return;
                    }
                    long currentTime = System.currentTimeMillis();
                    Map<String, SPLMessage> splMessageMap = new HashMap<>();
                    
                    for(Entry<String,TeamCommListener.Message> msg: teamCommListener.messageMap.entrySet()) 
                    {
                        if((currentTime - msg.getValue().timestamp) < RobotStatus.MAX_TIME_BEFORE_DEAD)
                        {
                          splMessageMap.put(msg.getKey(), msg.getValue().message);
                        }
                        final String address = msg.getKey();
                        final SPLMessage splMessage = msg.getValue().message;
                        final long timestamp = msg.getValue().timestamp;
                        
                        SwingUtilities.invokeLater(new Runnable()
                        {

                          @Override
                          public void run()
                          {
                            RobotStatus robotStatus = robotsMap.get(address);
                            if(robotStatus == null)
                            {
                              robotStatus = new RobotStatus(Plugin.parent.getMessageServer(), address);
                              robotStatus.setStatus(splMessage.playerNum, timestamp, splMessage);
                              robotsMap.put(address, robotStatus);
                              robotStatusPanel.add(robotStatus);
                            }
                            else
                            {
                              robotStatus.setStatus(splMessage.playerNum, timestamp, splMessage);
                            }
                          }
                        });
                        
                        
                    }
                    
                    if(Plugin.teamCommDrawingManager != null)
                    {
                      Plugin.teamCommDrawingManager.handleSPLMessages(splMessageMap);
                    }
                } // end synchronized
            } // end run
        }, 100, 33);
        
      }else
      {
        this.timerCheckMessages.cancel();
        this.timerCheckMessages.purge();
        this.timerCheckMessages = null;
        
        try {
          this.teamCommListener.disconnect();
        } catch (Exception ex) {}
        
        synchronized(teamCommListener.messageMap) 
        {
          

          teamCommListener.messageMap.clear();
          robotsMap.clear();
          robotStatusPanel.removeAll();
          robotStatusPanel.setVisible(false);
        }
        
      }
    }//GEN-LAST:event_btListenActionPerformed

  @Override
  public void dispose()
  {
  }
  

  
/*
  private void parseMessage(String address, int port, ByteBuffer buffer)
  {
    SPLMessage splMessage = new SPLMessage(buffer);

    try 
    {
        BUUserTeamMessage msg = BUUserTeamMessage.parseFrom(splMessage.data);
    } catch (InvalidProtocolBufferException ex) 
    {
        ex.printStackTrace(System.err);
    }
      
    RobotStatus robotStatus = this.robotsMap.get(address);
    if(robotStatus == null)
    {
      robotStatus = new RobotStatus(Plugin.parent.getMessageServer(), address);
      robotStatus.setStatus(splMessage.playerNum, 0, null);
      this.robotsMap.put(address, robotStatus);
      this.robotStatusPanel.add(robotStatus);
    }else
    {
      robotStatus.setStatus(splMessage.playerNum, 0, null);
    }

    // TODO: make it better
    Plugin.teamCommDrawingManager.setCurrenId(address);
//    Plugin.teamCommDrawingManager.handleResponse(msg.toByteArray(), null);
  }//end parseMessage
*/
 
  class TeamCommListener implements Runnable
  {
    public class Message
    {
          public Message(long timestamp, SPLMessage message) {
              this.timestamp = timestamp;
              this.message = message;
          }
        
        public final long timestamp;
        public final SPLMessage message;
    }
    
    private DatagramChannel channel;
    private Thread trigger;
    
    private final ByteBuffer readBuffer;
    public final Map<String,Message> messageMap;
    
    public TeamCommListener()
    {
      this.readBuffer = ByteBuffer.allocateDirect(SPLMessage.SPL_STANDARD_MESSAGE_SIZE);
      this.readBuffer.order(ByteOrder.LITTLE_ENDIAN);
      this.messageMap = Collections.synchronizedMap(new TreeMap<String,Message>());
    }
    
    boolean isConnected() {
        return this.channel != null && this.trigger != null;
    }
    
    public void connect(int port) throws IOException, InterruptedException
    {
        disconnect();
        
        this.channel = DatagramChannel.open();
        this.channel.configureBlocking(true);
        this.channel.bind(new InetSocketAddress(port));

        this.trigger = new Thread(this);
        this.trigger.start();
    }
    
    public void disconnect() throws IOException, InterruptedException
    {
        if(this.channel != null) {
            this.channel.close();
            this.channel = null;
        }
        if(this.trigger != null) {
            this.trigger.join();
            this.trigger = null;
        }
    }
    
    @Override
    public void run()
    {
        try
        {
          while(true)
          {
            this.readBuffer.clear();
            SocketAddress address = this.channel.receive(this.readBuffer);
            this.readBuffer.flip();
            try {
                SPLMessage msg = new SPLMessage(this.readBuffer);
              
                long timestamp = System.currentTimeMillis();
                if(address instanceof InetSocketAddress) 
                {
                  
                  synchronized(messageMap)
                  {
                    this.messageMap.put(((InetSocketAddress)address).getHostString(), new Message(timestamp, msg));
                  }
                }
                
            } catch( Exception ex ) {
                Logger.getLogger(TeamCommViewer.class.getName()).log(Level.INFO, null, ex);
            }
            //this.messageMap.put(address.toString(), new Message(timestamp, msg));
          }
        }
        catch(AsynchronousCloseException ex) {
          /* socket was closet, that's fine */  
        } catch(SocketException ex) {
          Logger.getLogger(TeamCommViewer.class.getName()).log(Level.SEVERE, null, ex);
        } catch(IOException ex) {
          Logger.getLogger(TeamCommViewer.class.getName()).log(Level.SEVERE, null, ex);
        }
    }
  }//end class TeamCommListener

  // Variables declaration - do not modify//GEN-BEGIN:variables
  private javax.swing.JToggleButton btListen;
  private javax.swing.JFormattedTextField portNumber;
  private javax.swing.JPanel robotStatusPanel;
  // End of variables declaration//GEN-END:variables

}
