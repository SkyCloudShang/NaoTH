/*
 * RobotStatus.java
 *
 * Created on 09.11.2010, 23:10:57
 */

package de.naoth.rc.components.teamcommviewer;

import java.awt.Color;
import javax.swing.SwingUtilities;

/**
 *
 * @author Heinrich Mellmann
 */
public class RobotStatusPanel extends javax.swing.JPanel implements RobotStatusListener {
    
    private RobotStatus rs;
    
    /** Creates new form RobotStatus */
    public RobotStatusPanel(RobotStatus rs) {
        this.rs = rs;
        this.setBackground(rs.robotColor);
        rs.addListener(this);
        initComponents();
        // get and set info, if the robot should be drawn on the field
        this.cbShowRobot.setSelected(rs.showOnField);
    }
    
    public RobotStatusPanel(RobotStatus rs, Color backgroundColor) {
        this(rs);
        this.setBackground(backgroundColor);
    }

    /** This method is called from within the constructor to
     * initialize the form.
     * WARNING: Do NOT modify this code. The content of this method is
     * always regenerated by the Form Editor.
     */
    @SuppressWarnings("unchecked")
    // <editor-fold defaultstate="collapsed" desc="Generated Code">//GEN-BEGIN:initComponents
    private void initComponents() {

        jLabel5 = new javax.swing.JLabel();
        jPanel1 = new javax.swing.JPanel();
        jlPlayerNumber = new javax.swing.JLabel();
        jlTimestamp = new javax.swing.JLabel();
        jlTeamNumber = new javax.swing.JLabel();
        jlFallenTime = new javax.swing.JLabel();
        jlBallAge = new javax.swing.JLabel();
        jlBatteryCharge = new javax.swing.JLabel();
        jlTemperature = new javax.swing.JLabel();
        jlAddress = new javax.swing.JLabel();
        connectButton = new javax.swing.JButton();
        cbShowRobot = new javax.swing.JCheckBox();

        jLabel5.setText("jLabel5");

        javax.swing.GroupLayout jPanel1Layout = new javax.swing.GroupLayout(jPanel1);
        jPanel1.setLayout(jPanel1Layout);
        jPanel1Layout.setHorizontalGroup(
            jPanel1Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGap(0, 100, Short.MAX_VALUE)
        );
        jPanel1Layout.setVerticalGroup(
            jPanel1Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGap(0, 100, Short.MAX_VALUE)
        );

        setBorder(new javax.swing.border.LineBorder(new java.awt.Color(0, 0, 0), 1, true));
        setMaximumSize(new java.awt.Dimension(150, 200));
        setMinimumSize(new java.awt.Dimension(150, 100));
        setPreferredSize(new java.awt.Dimension(150, 100));
        setLayout(new java.awt.GridLayout(5, 2));

        jlPlayerNumber.setIcon(new javax.swing.ImageIcon(getClass().getResource("/de/naoth/rc/res/user-info.png"))); // NOI18N
        jlPlayerNumber.setText("PN");
        jlPlayerNumber.setToolTipText("Player Number");
        add(jlPlayerNumber);

        jlTimestamp.setIcon(new javax.swing.ImageIcon(getClass().getResource("/de/naoth/rc/res/appointment-new.png"))); // NOI18N
        jlTimestamp.setText("DEAD");
        add(jlTimestamp);

        jlTeamNumber.setIcon(new javax.swing.ImageIcon(getClass().getResource("/de/naoth/rc/res/system-users.png"))); // NOI18N
        jlTeamNumber.setText("TN");
        jlTeamNumber.setToolTipText("Team Number");
        add(jlTeamNumber);

        jlFallenTime.setText("FT");
        add(jlFallenTime);

        jlBallAge.setIcon(new javax.swing.ImageIcon(getClass().getResource("/de/naoth/rc/res/media-record.png"))); // NOI18N
        jlBallAge.setText("BA");
        jlBallAge.setToolTipText("Ball age");
        add(jlBallAge);

        jlBatteryCharge.setIcon(new javax.swing.ImageIcon(getClass().getResource("/de/naoth/rc/res/battery.png"))); // NOI18N
        jlBatteryCharge.setText("BATTERY 100%");
        jlBatteryCharge.setToolTipText("Battery charge");
        add(jlBatteryCharge);

        jlTemperature.setIcon(new javax.swing.ImageIcon(getClass().getResource("/de/naoth/rc/res/thermometer.png"))); // NOI18N
        jlTemperature.setText("TEMP 000°C");
        jlTemperature.setToolTipText("Temperature");
        add(jlTemperature);

        jlAddress.setIcon(new javax.swing.ImageIcon(getClass().getResource("/de/naoth/rc/res/network-idle.png"))); // NOI18N
        jlAddress.setText("-");
        add(jlAddress);

        connectButton.setText("Connect");
        connectButton.setMaximumSize(new java.awt.Dimension(50, 23));
        connectButton.setMinimumSize(new java.awt.Dimension(50, 23));
        connectButton.setPreferredSize(new java.awt.Dimension(50, 23));
        connectButton.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                connectButtonActionPerformed(evt);
            }
        });
        add(connectButton);

        cbShowRobot.setSelected(true);
        cbShowRobot.setText("Show robot");
        cbShowRobot.setHorizontalAlignment(javax.swing.SwingConstants.RIGHT);
        cbShowRobot.setHorizontalTextPosition(javax.swing.SwingConstants.LEFT);
        cbShowRobot.setOpaque(false);
        cbShowRobot.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                cbShowRobotActionPerformed(evt);
            }
        });
        add(cbShowRobot);
    }// </editor-fold>//GEN-END:initComponents

    private void connectButtonActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_connectButtonActionPerformed
        rs.connect();
    }//GEN-LAST:event_connectButtonActionPerformed

    private void cbShowRobotActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_cbShowRobotActionPerformed
        rs.showOnField = this.cbShowRobot.isSelected();
    }//GEN-LAST:event_cbShowRobotActionPerformed

    @Override
    public void statusChanged(RobotStatus changed) {
        SwingUtilities.invokeLater(new Runnable() {
            @Override
            public void run() {
                updatePanelUi();
            }
        });
    }

    private void updatePanelUi() {
        this.jlPlayerNumber.setText("" + rs.playerNum);
        this.jlAddress.setText(rs.ipAddress);
        if (rs.isDead) {
            this.jlTimestamp.setText("DEAD");
            this.jlTimestamp.setForeground(Color.red);
        } else {
            this.jlTimestamp.setText(String.format("%4.2f msg/s", rs.msgPerSecond));
            this.jlTimestamp.setForeground(Color.black);
        }
        this.jlFallenTime.setText(rs.fallen == 1 ? "FALLEN" : "NOT FALLEN");
        this.jlBallAge.setText("" + rs.ballAge + "s");
        
        jlTemperature.setForeground(Color.black);
        jlBatteryCharge.setForeground(Color.black);
      
        if (rs.temperature == -1 && rs.batteryCharge == -1) {
            jlTemperature.setText("TEMP ??");
            jlBatteryCharge.setText("??");
        } else {
            //Representations.BUUserTeamMessage user = Representations.BUUserTeamMessage.parseFrom(msg.data);
            jlTemperature.setText(String.format(" %3.1f °C", rs.temperature));
            jlBatteryCharge.setText(String.format("%3.1f%%", rs.batteryCharge));

            if (rs.temperature >= 60.0f) {
                jlTemperature.setForeground(RobotStatus.COLOR_DANGER);
            }
            if (rs.temperature >= 75.0f) {
                jlTemperature.setForeground(Color.red);
            }

            if (rs.batteryCharge <= 0.3f) {
                jlBatteryCharge.setForeground(RobotStatus.COLOR_WARNING);
            }
            if (rs.batteryCharge <= 0.1f) {
                jlBatteryCharge.setForeground(Color.red);
            }

            
            this.jlTeamNumber.setText("" + rs.teamNum);
        }
        connectButton.setEnabled(!rs.isConnected);
        cbShowRobot.setSelected(rs.showOnField);
        this.repaint();
    }
    
    // Variables declaration - do not modify//GEN-BEGIN:variables
    private javax.swing.JCheckBox cbShowRobot;
    private javax.swing.JButton connectButton;
    private javax.swing.JLabel jLabel5;
    private javax.swing.JPanel jPanel1;
    private javax.swing.JLabel jlAddress;
    private javax.swing.JLabel jlBallAge;
    private javax.swing.JLabel jlBatteryCharge;
    private javax.swing.JLabel jlFallenTime;
    private javax.swing.JLabel jlPlayerNumber;
    private javax.swing.JLabel jlTeamNumber;
    private javax.swing.JLabel jlTemperature;
    private javax.swing.JLabel jlTimestamp;
    // End of variables declaration//GEN-END:variables
}
