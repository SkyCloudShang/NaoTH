/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package de.naoth.rc.dialogs;

import de.naoth.rc.RobotControl;
import de.naoth.rc.components.RemoteRobotPanel;
import de.naoth.rc.core.dialog.AbstractDialog;
import de.naoth.rc.core.dialog.DialogPlugin;
import de.naoth.rc.core.dialog.RCDialog;
import de.naoth.rc.core.manager.ObjectListener;
import de.naoth.rc.core.manager.SwingCommandExecutor;
import de.naoth.rc.dataformats.SPLMessage;
import de.naoth.rc.manager.GenericManagerFactory;
import de.naoth.rc.messages.Representations;
import de.naoth.rc.messages.Representations.RemoteControlCommand.SecondActionType;
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
import java.util.Timer;
import java.util.TimerTask;
import java.util.TreeMap;
import java.util.logging.Level;
import java.util.logging.Logger;
import javax.swing.SwingUtilities;
import javax.swing.text.BadLocationException;
import javax.swing.text.Document;
import net.xeoh.plugins.base.annotations.PluginImplementation;
import net.xeoh.plugins.base.annotations.injections.InjectPlugin;
import net.java.games.input.Component;
import net.java.games.input.Controller;
import net.java.games.input.ControllerEnvironment;
import net.java.games.input.Event;
import net.java.games.input.EventQueue;

/**
 *
 * @author Verena
 */
public class RemoteTeamControl extends AbstractDialog {

    @RCDialog(category = RCDialog.Category.Debug, name = "RemoteControl")
    @PluginImplementation
    public static class Plugin extends DialogPlugin<RemoteTeamControl> {

        @InjectPlugin
        public static RobotControl parent;
        @InjectPlugin
        public static SwingCommandExecutor commandExecutor;
        @InjectPlugin
        public static GenericManagerFactory genericManagerFactory;
    }//end Plugin

    private final Map<String, TeamCommMessage> messageMap = Collections.synchronizedMap(new TreeMap<String, TeamCommMessage>());
    private final HashMap<String, RemoteRobotPanel> robotsMap = new HashMap<>();
    private TeamCommListener teamCommListener;
    private Timer timerCheckMessages;
    
    public RemoteTeamControl() 
    {
        initComponents();
        
        try {
            teamCommListener = new TeamCommListener();
            teamCommListener.connect(10004);
        } catch (IOException | InterruptedException ex) {
            ex.printStackTrace(System.err);
        }
        
        // dummy robot for tests
        //robotsMap.put("10.0.4.77", new RemoteRobotPanel(Plugin.parent.getMessageServer(),"10.0.4.77", new SPLMessage()));
        //updateRoboPanel();
        
        this.timerCheckMessages = new Timer();
        this.timerCheckMessages.scheduleAtFixedRate(new TeamCommListenTask(), 100, 100);
        
        Controller[] controllers = ControllerEnvironment.getDefaultEnvironment().getControllers();
        for(Controller c: controllers) 
        {
            registerControl(c);
        }
    }

    @Override
    public void dispose() {
        try {
            teamCommListener.disconnect();
        } catch (IOException | InterruptedException ex) {
            ex.printStackTrace(System.err);
        }
    }
    
    
    private void registerControl(Controller controller) {
        try {
            if(controller.getType() == Controller.Type.KEYBOARD) {
                log("INFO: register keyboard");
                RobotController rc = new KeyBoardControl(controller);
                this.timerCheckMessages.scheduleAtFixedRate(rc, 100, 10);
            } else if(controller.getType() == Controller.Type.GAMEPAD) {
                log("INFO: register GAMEPAD " + controller.getName());
                RobotController rc = new GamePadControl(controller);
                this.timerCheckMessages.scheduleAtFixedRate(rc, 100, 10);
            }
        } catch(IOException ex) {
            ex.printStackTrace(System.err);
        }
    }

    /**
     * This method is called from within the constructor to initialize the form.
     * WARNING: Do NOT modify this code. The content of this method is always
     * regenerated by the Form Editor.
     */
    @SuppressWarnings("unchecked")
    // <editor-fold defaultstate="collapsed" desc="Generated Code">//GEN-BEGIN:initComponents
    private void initComponents() {

        jScrollPane2 = new javax.swing.JScrollPane();
        robotPanel = new javax.swing.JPanel();
        jScrollPane1 = new javax.swing.JScrollPane();
        logOutput = new javax.swing.JEditorPane();
        jToolBar1 = new javax.swing.JToolBar();
        filterTeam = new javax.swing.JToggleButton();
        teamSelectionBox = new javax.swing.JComboBox();
        teamSelectionBoxTwo = new javax.swing.JComboBox();

        javax.swing.GroupLayout robotPanelLayout = new javax.swing.GroupLayout(robotPanel);
        robotPanel.setLayout(robotPanelLayout);
        robotPanelLayout.setHorizontalGroup(
            robotPanelLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGap(0, 340, Short.MAX_VALUE)
        );
        robotPanelLayout.setVerticalGroup(
            robotPanelLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGap(0, 154, Short.MAX_VALUE)
        );

        robotPanel.setLayout(new de.naoth.rc.components.WrapLayout(java.awt.FlowLayout.LEFT));

        jScrollPane2.setViewportView(robotPanel);

        jScrollPane1.setViewportView(logOutput);

        jToolBar1.setFloatable(false);
        jToolBar1.setRollover(true);

        filterTeam.setText("Filter by Team");
        filterTeam.setFocusable(false);
        filterTeam.setHorizontalTextPosition(javax.swing.SwingConstants.CENTER);
        filterTeam.setVerticalTextPosition(javax.swing.SwingConstants.BOTTOM);
        filterTeam.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                filterTeamActionPerformed(evt);
            }
        });
        jToolBar1.add(filterTeam);

        teamSelectionBox.setModel(new javax.swing.DefaultComboBoxModel(new String[] { "0", "1", "2", "3", "4", "5", "6" }));
        teamSelectionBox.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                teamSelectionBoxActionPerformed(evt);
            }
        });
        jToolBar1.add(teamSelectionBox);

        teamSelectionBoxTwo.setModel(new javax.swing.DefaultComboBoxModel(new String[] { "0", "1", "2", "3", "4", "5", "6" }));
        teamSelectionBoxTwo.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                teamSelectionBoxTwoActionPerformed(evt);
            }
        });
        jToolBar1.add(teamSelectionBoxTwo);

        javax.swing.GroupLayout layout = new javax.swing.GroupLayout(this);
        this.setLayout(layout);
        layout.setHorizontalGroup(
            layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(layout.createSequentialGroup()
                .addComponent(jScrollPane2, javax.swing.GroupLayout.DEFAULT_SIZE, 344, Short.MAX_VALUE)
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addComponent(jScrollPane1, javax.swing.GroupLayout.PREFERRED_SIZE, 308, javax.swing.GroupLayout.PREFERRED_SIZE))
            .addComponent(jToolBar1, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
        );
        layout.setVerticalGroup(
            layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(layout.createSequentialGroup()
                .addComponent(jToolBar1, javax.swing.GroupLayout.PREFERRED_SIZE, 25, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                    .addComponent(jScrollPane1, javax.swing.GroupLayout.DEFAULT_SIZE, 154, Short.MAX_VALUE)
                    .addComponent(jScrollPane2, javax.swing.GroupLayout.PREFERRED_SIZE, 0, Short.MAX_VALUE)))
        );
    }// </editor-fold>//GEN-END:initComponents

    private void filterTeamActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_filterTeamActionPerformed
        updateRoboPanel();
    }//GEN-LAST:event_filterTeamActionPerformed

    private void teamSelectionBoxActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_teamSelectionBoxActionPerformed
        updateRoboPanel();
    }//GEN-LAST:event_teamSelectionBoxActionPerformed

    private void teamSelectionBoxTwoActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_teamSelectionBoxTwoActionPerformed
        // TODO add your handling code here:
    }//GEN-LAST:event_teamSelectionBoxTwoActionPerformed

    class RemoteCommandResultHandler implements ObjectListener<byte[]> {

        @Override
        public void newObjectReceived(byte[] object) {
            if (!new String(object).isEmpty()) {
                System.out.println(new String(object));
            }
        }

        @Override
        public void errorOccured(String cause) {
            System.out.println(cause);
        }
    }

    static class RemoteCommand 
    {
        private Representations.RemoteControlCommand.ControlMode mode = Representations.RemoteControlCommand.ControlMode.DIRECT_CONTROL;
        private Representations.RemoteControlCommand.ActionType action = Representations.RemoteControlCommand.ActionType.STAND;
        private Representations.RemoteControlCommand.SecondActionType second_action = Representations.RemoteControlCommand.SecondActionType.SECOND_NONE;
        
        public double x = 0;
        public double y = 0;
        public double alpha = 0;
        
        private boolean modeSet = false;
        private boolean actionSet = false;
        private boolean secondActionSet = false;

        public Representations.RemoteControlCommand.ControlMode getMode() {
            return mode;
        }

        public void setMode(Representations.RemoteControlCommand.ControlMode mode) {
            this.mode = mode;
            this.modeSet = true;
        }

        public Representations.RemoteControlCommand.ActionType getAction() {
            return action;
        }

        public void setAction(Representations.RemoteControlCommand.ActionType action) {
            this.action = action;
            this.actionSet = true;
        }

        public Representations.RemoteControlCommand.SecondActionType getSecond_action() {
            return second_action;
        }

        public void setSecond_action(Representations.RemoteControlCommand.SecondActionType second_action) {
            this.second_action = second_action;
            this.secondActionSet = true;
        }
        
        
        public boolean modeIsSet() {
            return modeSet;
        }
        
        public boolean actionIsSet() {
            return actionSet;
        }
        
        public boolean secondActionIsSet() {
            return secondActionSet;
        }
    }
    
    
    private void log(final String str) {
        SwingUtilities.invokeLater(new Runnable() {
            @Override
            public void run() {
                try {
                    Document doc = logOutput.getDocument();
                    doc.insertString(doc.getLength(), str + "\n", null);
                } catch(BadLocationException exc) {
                    exc.printStackTrace(System.err);
                }
            }
        });
    }
    
    private class CommandSenderTask extends TimerTask
    {
        private final DatagramChannel channel;
        private final InetSocketAddress targetAddress;
        private RemoteCommand command = new RemoteCommand();
        private boolean updated = false;
        
        public CommandSenderTask(InetSocketAddress targetAddress)  throws IOException {
            this.channel = DatagramChannel.open();
            this.targetAddress = targetAddress;
        }
        
        public String getAddress() {
            return targetAddress.toString();
        }
        
        @Override
        public void run() 
        {
            //System.out.println("Command sender running.");
            if(targetAddress == null || !this.updated) {
                return;
            }
            
            Representations.RemoteControlCommand.Builder cmd = Representations.RemoteControlCommand.newBuilder();
            synchronized(this) {
                cmd.setAction(command.getAction());
                cmd.getTargetBuilder()
                    .setRotation(command.alpha)
                    .getTranslationBuilder().setX(command.x).setY(command.y);
                cmd.setControlMode(command.getMode());
                cmd.setSecondAction(command.getSecond_action());
                this.updated = false;
            }
            
            try {
                ByteBuffer buffer = ByteBuffer.wrap(cmd.build().toByteArray());
                this.channel.send(buffer, targetAddress);
                
            } catch (IOException ex) {
                ex.printStackTrace(System.err);
            }
        }
        
        public void send(RemoteCommand command) 
        {
            synchronized(this) {
                this.command = command;
                this.updated = true;
            }
        }
    }
    
    
    private abstract class RobotController extends TimerTask implements RemoteRobotPanel.UnbindListerer
    {
        private final Controller control;
        
        private CommandSenderTask commandSender = null;
        protected RemoteRobotPanel robot = null;
        
        protected HashMap<String, RemoteCommand> commands = new HashMap<>();
        
        public RobotController(Controller control) {
            this.control = control;
        }
        
        public boolean isBound() {
            return commandSender != null;
        }
        
        public CommandSenderTask bind(RemoteRobotPanel robot) throws IOException{
            this.robot = robot;
            commandSender = new CommandSenderTask(new InetSocketAddress(InetAddress.getByName(robot.getAddress()), 10401));
            robot.bind(this);
            timerCheckMessages.scheduleAtFixedRate(commandSender, 100, 100);
            return commandSender;
        }

        @Override
        public void unbind() {
            log("unbind from " + commandSender.getAddress());
            commandSender.cancel();
            commandSender = null;
            this.robot = null;
        }
        
        protected void log(String str) {
            RemoteTeamControl.this.log(control.getName() + ": " + str);
        }
        
        @Override
        public void run() 
        {
            if(control.poll())
            {
                EventQueue queue = control.getEventQueue();
                Event event = new Event();
                while(queue.getNextEvent(event)) 
                {
                    Component component = event.getComponent();
                        
                    if(component.getIdentifier() == Component.Identifier.Button._7) 
                    {
                        if(!isBound())
                        {
                            if(Math.abs(component.getPollData()) > 0.0)
                            {
                                for(Map.Entry<String, RemoteRobotPanel> robot: robotsMap.entrySet()) {
                                    if(robot.getValue().isReadyToBind()) 
                                    {
                                        log("bind to " + robot.getKey());

                                        try {
                                            bind(robot.getValue());
                                        } catch(IOException ex) {
                                            ex.printStackTrace(System.err);
                                        }
                                    }
                                }
                                return;
                            }
                        }
                        else
                        {
                            if(Math.abs(component.getPollData()) > 0.0) {
                                RemoteCommand c = new RemoteCommand();
                                c.setSecond_action(SecondActionType.BLINK);
                                commands.put(component.getIdentifier().getName(), c);

                                this.robot.setChestColor(new Color(1.0f,0.0f,0.0f,0.7f));
                            } else {
                                commands.remove(component.getIdentifier().getName());
                                this.robot.setChestColor(new Color(0.0f,0.0f,0.0f,0.7f));
                            }
                            System.out.println(component.getName() + " - " + component.getPollData());
                        }
                    }
                    else if(isBound())
                    {
                        update(component);
                    }
                }
                
                /*
                Component[] components = control.getComponents();
                for(int i=0; i < control.getComponents().length;i++) {
                    update(components[i]);
                }
                */

                if(commandSender != null)
                {
                    RemoteCommand remoteCommand = new RemoteCommand();
                    remoteCommand.setAction(Representations.RemoteControlCommand.ActionType.STAND);
                    for(RemoteCommand c : this.commands.values()) {
                        if(c != null) {
                            if(c.actionIsSet()) {
                                remoteCommand.setAction(c.getAction());
                                remoteCommand.x += c.x;
                                remoteCommand.y += c.y;
                                remoteCommand.alpha += c.alpha;
                            }
                            
                            if(c.modeIsSet()) {
                                remoteCommand.setMode(c.getMode());
                            }
                            
                            if(c.secondActionIsSet()) {
                                remoteCommand.setSecond_action(c.getSecond_action());
                            }
                        }
                    }
                    
                    // HACK
                    if(Math.abs(remoteCommand.x) > Math.abs(remoteCommand.y)) {
                        remoteCommand.y = 0;
                        if(remoteCommand.x > 0) {
                            remoteCommand.x = 50;
                        } else if(remoteCommand.x < 0) {
                            remoteCommand.x = -50;
                        }
                    } else if(Math.abs(remoteCommand.y) > Math.abs(remoteCommand.x)) {
                        remoteCommand.x = 0;
                        if(remoteCommand.y > 0) {
                            remoteCommand.y = 50;
                        } else if(remoteCommand.y < 0) {
                            remoteCommand.y = -50;
                        }
                    }
                    
                    commandSender.send(remoteCommand);
                }
            } else {
                this.cancel();
            }
        }
        
        protected abstract void update(Component component);
    }
    
    private class GamePadControl extends RobotController
    {
        public GamePadControl(Controller control) throws IOException {
            super(control);
        }
        
        @Override
        protected void update(Component component)
        {
            
            Component.Identifier id = component.getIdentifier();
            System.out.println(component.getName() + " - " + component.getPollData());
            
            if(id == Component.Identifier.Button._2) { // (X)
                if(Math.abs(component.getPollData()) > 0.0) {
                    RemoteCommand c = new RemoteCommand();
                    c.setSecond_action(SecondActionType.SAY);
                    commands.put(id.getName(), c);
                } else {
                    commands.remove(id.getName());
                }
            }

            if(id == Component.Identifier.Button._4) { // (LB)
                if(Math.abs(component.getPollData()) > 0.0) {
                    RemoteCommand c = new RemoteCommand();
                    c.setAction(Representations.RemoteControlCommand.ActionType.KICK_LEFT);
                    commands.put(id.getName(), c);
                } else {
                    commands.remove(id.getName());
                }
                System.out.println(component.getName() + " - " + component.getPollData());
            }
            else if(id == Component.Identifier.Button._5) {  // (RB)
                if(Math.abs(component.getPollData()) > 0.0) {
                    RemoteCommand c = new RemoteCommand();
                    c.setAction(Representations.RemoteControlCommand.ActionType.KICK_RIGHT);
                    commands.put(id.getName(), c);
                } else {
                    commands.remove(id.getName());
                }
            }
            else if(id == Component.Identifier.Axis.Z) {  // (LT) (RT)
                if(component.getPollData() > 0.5) { //(LT)
                    RemoteCommand c = new RemoteCommand();
                    c.setAction(Representations.RemoteControlCommand.ActionType.KICK_FORWARD_LEFT);
                    commands.put(id.getName(), c);
                } else if(component.getPollData() < -0.5) { //(RT)
                    RemoteCommand c = new RemoteCommand();
                    c.setAction(Representations.RemoteControlCommand.ActionType.KICK_FORWARD_RIGHT);
                    commands.put(id.getName(), c);
                }else {
                    commands.remove(id.getName());
                }
            }
            else if(id == Component.Identifier.Axis.POV) 
            {
                if(component.getPollData() == 0.25 || component.getPollData() == 0.125 || component.getPollData() == 0.375) {
                    RemoteCommand c = new RemoteCommand();
                    c.setAction(Representations.RemoteControlCommand.ActionType.WALK);
                    c.x = 50;
                    commands.put(id.getName(), c);
                } else if(component.getPollData() == 0.75) {
                    RemoteCommand c = new RemoteCommand();
                    c.setAction(Representations.RemoteControlCommand.ActionType.WALK);
                    c.x = -50;
                    commands.put(id.getName(), c);
                } else if(component.getPollData() == 1.0 || component.getPollData() == 0.875) {
                    RemoteCommand c = new RemoteCommand();
                    c.setAction(Representations.RemoteControlCommand.ActionType.WALK);
                    c.y = 50;
                    commands.put(id.getName(), c);
                } else if(component.getPollData() == 0.5 || component.getPollData() == 0.625) {
                    RemoteCommand c = new RemoteCommand();
                    c.setAction(Representations.RemoteControlCommand.ActionType.WALK);
                    c.y = -50;
                    commands.put(id.getName(), c);
                } else {
                    commands.remove(id.getName());
                }
            } 
            else if(id == Component.Identifier.Axis.X)
            {
                double dead_radius = 0.5;
                if(Math.abs(component.getPollData()) > dead_radius) {
                    RemoteCommand c = new RemoteCommand();
                    c.setAction(Representations.RemoteControlCommand.ActionType.WALK);
                    c.y = -50*component.getPollData();
                    commands.put(id.getName(), c);
                } else {
                    commands.remove(id.getName());
                }
            }
            else if(id == Component.Identifier.Axis.Y)
            {
                double dead_radius = 0.5;
                if(Math.abs(component.getPollData()) > dead_radius) {
                    RemoteCommand c = new RemoteCommand();
                    c.setAction(Representations.RemoteControlCommand.ActionType.WALK);
                    c.x = -50*component.getPollData();
                    commands.put(id.getName(), c);
                } else {
                    commands.remove(id.getName());
                }
            }
            else if(id == Component.Identifier.Axis.RX)
            {
                double dead_radius = 0.32;
                if(Math.abs(component.getPollData()) > dead_radius) {
                    RemoteCommand c = new RemoteCommand();
                    c.setAction(Representations.RemoteControlCommand.ActionType.WALK);
                    c.alpha = -15.0*component.getPollData();
                    commands.put(id.getName(), c);
                } else {
                    commands.remove(id.getName());
                }
            }
        }

    }// end class GamePadControl

    private class KeyBoardControl extends RobotController 
    {
        public KeyBoardControl(Controller control) throws IOException {
            super(control);
        }
        
        @Override
        protected void update(Component component)
        {
            Component.Identifier id = component.getIdentifier();
            if(id == Component.Identifier.Key.W) {
                if(component.getPollData() > 0) {
                    RemoteCommand c = new RemoteCommand();
                    c.setAction(Representations.RemoteControlCommand.ActionType.WALK);
                    c.x = 50;
                    commands.put(id.getName(), c);
                } else {
                    commands.remove(id.getName());
                }
            } else if(id == Component.Identifier.Key.S) {
                if(component.getPollData() > 0) {
                    RemoteCommand c = new RemoteCommand();
                    c.setAction(Representations.RemoteControlCommand.ActionType.WALK);
                    c.x = -50;
                    commands.put(id.getName(), c);
                } else {
                    commands.remove(id.getName());
                }
            } else if(id == Component.Identifier.Key.A) {
                if(component.getPollData() > 0) {
                    RemoteCommand c = new RemoteCommand();
                    c.setAction(Representations.RemoteControlCommand.ActionType.WALK);
                    c.y = 50;
                    commands.put(id.getName(), c);
                } else {
                    commands.remove(id.getName());
                }
            } else if(id == Component.Identifier.Key.D) {
                if(component.getPollData() > 0) {
                    RemoteCommand c = new RemoteCommand();
                    c.setAction(Representations.RemoteControlCommand.ActionType.WALK);
                    c.y = -50;
                    commands.put(id.getName(), c);
                } else {
                    commands.remove(id.getName());
                }
            }
        } 
    }// end class KeyBoardControl
    
    
    public class Sender {
        private final DatagramChannel channel;

        public Sender() throws IOException {
            this.channel = DatagramChannel.open();
            this.channel.configureBlocking(true);
            //this.channel.bind(new InetSocketAddress(InetAddress.getByName("0.0.0.0"), port));
        }
        
        void send(Representations.RemoteControlCommand rcc, InetSocketAddress address) throws IOException {
            ByteBuffer buffer = ByteBuffer.wrap(rcc.toByteArray());
            this.channel.send(buffer, new InetSocketAddress(InetAddress.getByName("10.0.4.85"), 10401));
        }
    }
    
    
    private void updateRoboPanel() {
        //if(filterTeam.isSelected()) 
        {
            this.robotPanel.removeAll();

            for (Map.Entry<String, RemoteRobotPanel> msgEntry : robotsMap.entrySet()) 
            {
                addPanel(msgEntry.getValue());
            }
            this.robotPanel.repaint();
        }
    }
    
    private void addPanel(RemoteRobotPanel robotStatus) {
        if(!filterTeam.isSelected() || teamSelectionBox.getSelectedIndex() == robotStatus.getMessage().teamNum ||
            teamSelectionBoxTwo.getSelectedIndex() == robotStatus.getMessage().teamNum)
        {
            robotPanel.add(robotStatus);
            robotPanel.repaint();
        }
    }

    private class TeamCommListenTask extends TimerTask {

        @Override
        public void run() {
            synchronized (messageMap) {
                if (messageMap.isEmpty()) {
                    return;
                }

                
                
                for (Map.Entry<String, TeamCommMessage> msgEntry : messageMap.entrySet()) 
                {
                    final String address = msgEntry.getKey();
                    final TeamCommMessage msg = msgEntry.getValue();
                    
                    SwingUtilities.invokeLater(new Runnable() {
                        @Override
                        public void run() {
                            RemoteRobotPanel robotStatus = robotsMap.get(address);
                            if (robotStatus == null) {
                                robotStatus = new RemoteRobotPanel(Plugin.parent.getMessageServer(), address, msg.message);
                                robotsMap.put(address, robotStatus);
                                addPanel(robotStatus);
                            }
                            // update
                            robotStatus.setStatus(msg.timestamp, msg.message);
                        }
                    });
                }
            } // end synchronized
        } // end run
    }

    public class TeamCommListener implements Runnable {
        private DatagramChannel channel;
        private Thread trigger;

        private final ByteBuffer readBuffer;

        public TeamCommListener() {
            this.readBuffer = ByteBuffer.allocateDirect(SPLMessage.SPL_STANDARD_MESSAGE_SIZE);
            this.readBuffer.order(ByteOrder.LITTLE_ENDIAN);
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
                        long timestamp = System.currentTimeMillis();
                        SPLMessage spl_msg = new SPLMessage(this.readBuffer);
                        TeamCommMessage tc_msg = new TeamCommMessage(timestamp, spl_msg);
                        
                        if (address instanceof InetSocketAddress) {
                            messageMap.put(((InetSocketAddress) address).getHostString(), tc_msg);
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

    public class TeamCommMessage {

        public TeamCommMessage(long timestamp, SPLMessage message) {
            this.timestamp = timestamp;
            this.message = message;
        }

        public final long timestamp;
        public final SPLMessage message;
        
    }

    // Variables declaration - do not modify//GEN-BEGIN:variables
    private javax.swing.JToggleButton filterTeam;
    private javax.swing.JScrollPane jScrollPane1;
    private javax.swing.JScrollPane jScrollPane2;
    private javax.swing.JToolBar jToolBar1;
    private javax.swing.JEditorPane logOutput;
    private javax.swing.JPanel robotPanel;
    private javax.swing.JComboBox teamSelectionBox;
    private javax.swing.JComboBox teamSelectionBoxTwo;
    // End of variables declaration//GEN-END:variables
}
