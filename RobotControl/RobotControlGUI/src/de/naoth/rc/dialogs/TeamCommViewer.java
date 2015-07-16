/**
 * TeamCommViewer.java
 *
 * Created on 08.11.2010, 21:41:28
 */
package de.naoth.rc.dialogs;

import de.naoth.rc.Helper;
import de.naoth.rc.RobotControl;
import de.naoth.rc.components.RobotStatus;
import de.naoth.rc.core.dialog.AbstractDialog;
import de.naoth.rc.core.dialog.DialogPlugin;
import de.naoth.rc.dataformats.SPLMessage;
import de.naoth.rc.drawingmanager.DrawingEventManager;
import de.naoth.rc.drawings.DrawingCollection;
import de.naoth.rc.drawings.Rotation;
import java.awt.Color;
import java.io.IOException;
import java.net.InetAddress;
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
public class TeamCommViewer extends AbstractDialog {

    @PluginImplementation
    public static class Plugin extends DialogPlugin<TeamCommViewer> {

        @InjectPlugin
        public static RobotControl parent;
        @InjectPlugin
        public static DrawingEventManager drawingEventManager;
    }//end Plugin

    private Timer timerCheckMessages;
    private final TeamCommListener listenerOwn = new TeamCommListener(false);
    private final TeamCommListener listenerOpponent = new TeamCommListener(true);
    private final HashMap<String, RobotStatus> robotsMap = new HashMap<>();

    private final Map<String, TeamCommListener.Message> messageMap = Collections.synchronizedMap(new TreeMap<String, TeamCommListener.Message>());

    /**
     * Creates new form TeamCommViewer
     */
    public TeamCommViewer() {
        initComponents();
    }

    /**
     * This method is called from within the constructor to initialize the form.
     * WARNING: Do NOT modify this code. The content of this method is always
     * regenerated by the Form Editor.
     */
    @SuppressWarnings("unchecked")
    // <editor-fold defaultstate="collapsed" desc="Generated Code">//GEN-BEGIN:initComponents
    private void initComponents() {

        robotStatusPanel = new javax.swing.JPanel();
        btListen = new javax.swing.JToggleButton();
        portNumberOwn = new javax.swing.JFormattedTextField();
        portNumberOpponent = new javax.swing.JFormattedTextField();

        robotStatusPanel.setLayout(new java.awt.GridLayout(5, 1, 0, 5));

        btListen.setText("Listen to TeamComm");
        btListen.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                btListenActionPerformed(evt);
            }
        });

        portNumberOwn.setColumns(6);
        portNumberOwn.setFormatterFactory(new javax.swing.text.DefaultFormatterFactory(new javax.swing.text.NumberFormatter(new java.text.DecimalFormat("#"))));
        portNumberOwn.setText("10004");
        portNumberOwn.setToolTipText("Own team port number");

        portNumberOpponent.setColumns(6);
        portNumberOpponent.setFormatterFactory(new javax.swing.text.DefaultFormatterFactory(new javax.swing.text.NumberFormatter(new java.text.DecimalFormat("#"))));
        portNumberOpponent.setToolTipText("Opponent team port number");

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
                        .addComponent(portNumberOwn, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                        .addComponent(portNumberOpponent, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                        .addGap(0, 119, Short.MAX_VALUE))
                    .addComponent(robotStatusPanel, javax.swing.GroupLayout.Alignment.TRAILING, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE))
                .addContainerGap())
        );
        layout.setVerticalGroup(
            layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(layout.createSequentialGroup()
                .addContainerGap()
                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                    .addComponent(btListen)
                    .addComponent(portNumberOwn, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                    .addComponent(portNumberOpponent, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE))
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addComponent(robotStatusPanel, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE))
        );
    }// </editor-fold>//GEN-END:initComponents

    private void btListenActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_btListenActionPerformed

        try {
            if (this.btListen.isSelected()) {
                String ownPortRaw = portNumberOwn.getText().trim();
                if(!ownPortRaw.isEmpty()) {
                    int portOwn = Integer.parseInt(ownPortRaw);
                    listenerOwn.connect(portOwn);
                }
                String opponentPortRaw = portNumberOpponent.getText().trim();
                if (!opponentPortRaw.isEmpty()) {
                    int portOpponent = Integer.parseInt(opponentPortRaw);
                    listenerOpponent.connect(portOpponent);
                }

                this.timerCheckMessages = new Timer();
                this.timerCheckMessages.scheduleAtFixedRate(new TeamCommListenTask(), 100, 33);
                this.portNumberOwn.setEnabled(false);
                this.portNumberOpponent.setEnabled(false);
                this.robotStatusPanel.setVisible(true);

            } else {

                if(this.timerCheckMessages != null) {
                    this.timerCheckMessages.cancel();
                    this.timerCheckMessages.purge();
                    this.timerCheckMessages = null;
                }
                
                listenerOwn.disconnect();
                listenerOpponent.disconnect();;

                synchronized (messageMap) {
                    messageMap.clear();
                    this.robotsMap.clear();
                    this.robotStatusPanel.removeAll();
                    this.robotStatusPanel.setVisible(false);
                    this.portNumberOwn.setEnabled(true);
                    this.portNumberOpponent.setEnabled(true);
                }
            }
        } catch (NumberFormatException ex) {
            Helper.handleException("Invalid port number", ex);
        } catch (InterruptedException ex) {
            ex.printStackTrace(System.err);
        } catch (IOException ex) {
            ex.printStackTrace(System.err);
        }
    }//GEN-LAST:event_btListenActionPerformed

    @Override
    public void dispose() {
    }

    private class TeamCommListenTask extends TimerTask {

        @Override
        public void run() {
            synchronized (messageMap) {
                if (messageMap.isEmpty()) {
                    return;
                }

                DrawingCollection drawings = new DrawingCollection();

                for (Entry<String, TeamCommListener.Message> msg : messageMap.entrySet()) {
                    final String address = msg.getKey();
                    final SPLMessage splMessage = msg.getValue().message;
                    final long timestamp = msg.getValue().timestamp;
               

                    SwingUtilities.invokeLater(new Runnable() {
                        @Override
                        public void run() {
                            RobotStatus robotStatus = robotsMap.get(address);
                            if (robotStatus == null) {
                                robotStatus = new RobotStatus(Plugin.parent.getMessageServer(), address);
                                robotStatus.setStatus(timestamp, splMessage);
                                robotsMap.put(address, robotStatus);
                                robotStatusPanel.add(robotStatus);
                            } else {
                                robotStatus.setStatus(timestamp, splMessage);
                            }
                        }
                    });
                    
                    if(msg.getValue().isOpponent()) {
                        drawings.add(new Rotation((float) Math.PI));
                    }
                    splMessage.draw(drawings, msg.getValue().isOpponent() ? Color.RED : Color.GRAY);
                }

                TeamCommViewer.Plugin.drawingEventManager.fireDrawingEvent(drawings);

            } // end synchronized
        } // end run
    }

    public class TeamCommListener implements Runnable {

        public class Message {

            public Message(long timestamp, SPLMessage message) {
                this.timestamp = timestamp;
                this.message = message;
            }

            public final long timestamp;
            public final SPLMessage message;

            public boolean isOpponent() {
                return TeamCommListener.this.isOpponent;
            }
        }

        private DatagramChannel channel;
        private Thread trigger;

        private final ByteBuffer readBuffer;

        private final boolean isOpponent;

        public TeamCommListener(boolean isOpponent) {
            this.readBuffer = ByteBuffer.allocateDirect(SPLMessage.SPL_STANDARD_MESSAGE_SIZE);
            this.readBuffer.order(ByteOrder.LITTLE_ENDIAN);
            this.isOpponent = isOpponent;
        }

        boolean isConnected() {
            return this.channel != null && this.trigger != null;
        }

        public void connect(int port) throws IOException, InterruptedException {
            disconnect();

            this.channel = DatagramChannel.open();
            this.channel.configureBlocking(true);
            this.channel.bind(new InetSocketAddress(InetAddress.getByName("0.0.0.0"), port));

            this.trigger = new Thread(this);
            this.trigger.start();
        }

        public void disconnect() throws IOException, InterruptedException {
            if (this.channel != null) {
                this.channel.close();
                this.channel = null;
            }
            if (this.trigger != null) {
                this.trigger.join();
                this.trigger = null;
            }
        }

        @Override
        public void run() {
            try {
                while (true) {
                    this.readBuffer.clear();
                    SocketAddress address = this.channel.receive(this.readBuffer);
                    this.readBuffer.flip();

                    try {
                        SPLMessage msg = new SPLMessage(this.readBuffer);

                        long timestamp = System.currentTimeMillis();
                        if (address instanceof InetSocketAddress) {
                            messageMap.put(((InetSocketAddress) address).getHostString(), new Message(timestamp, msg));
                        }

                    } catch (Exception ex) {
                        Logger.getLogger(TeamCommViewer.class.getName()).log(Level.INFO, null, ex);
                    }

                }
            } catch (AsynchronousCloseException ex) {
                /* socket was closed, that's fine */
            } catch (SocketException ex) {
                Logger.getLogger(TeamCommViewer.class.getName()).log(Level.SEVERE, null, ex);
            } catch (IOException ex) {
                Logger.getLogger(TeamCommViewer.class.getName()).log(Level.SEVERE, null, ex);
            }
        }
    }//end class TeamCommListener

    // Variables declaration - do not modify//GEN-BEGIN:variables
    private javax.swing.JToggleButton btListen;
    private javax.swing.JFormattedTextField portNumberOpponent;
    private javax.swing.JFormattedTextField portNumberOwn;
    private javax.swing.JPanel robotStatusPanel;
    // End of variables declaration//GEN-END:variables

}
