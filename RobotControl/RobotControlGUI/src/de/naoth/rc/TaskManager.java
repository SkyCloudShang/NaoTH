/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * TaskManager.java
 *
 * Created on 19.04.2011, 20:12:19
 */

package de.naoth.rc;

import java.awt.event.ActionListener;
import javax.swing.JButton;
import javax.swing.table.DefaultTableModel;

/**
 *
 * @author Heinrich Mellmann
 */
public class TaskManager extends javax.swing.JDialog {

    /** Creates new form TaskManager */
    public TaskManager(java.awt.Frame parent, boolean modal) {
        super(parent, modal);
        initComponents();
    }

    public void addTask(String name, String status, ActionListener actionListener)
    {  
      ((DefaultTableModel)this.taskTable.getModel()).addRow(new Object[]{name, status});
      this.taskTable.invalidate();
    }

    /** This method is called from within the constructor to
     * initialize the form.
     * WARNING: Do NOT modify this code. The content of this method is
     * always regenerated by the Form Editor.
     */
    @SuppressWarnings("unchecked")
  // <editor-fold defaultstate="collapsed" desc="Generated Code">//GEN-BEGIN:initComponents
  private void initComponents() {

    taskMenu = new javax.swing.JPopupMenu();
    stop = new javax.swing.JMenuItem();
    jScrollPane1 = new javax.swing.JScrollPane();
    taskTable = new javax.swing.JTable();

    stop.setText("jMenuItem1");
    stop.addActionListener(new java.awt.event.ActionListener() {
      public void actionPerformed(java.awt.event.ActionEvent evt) {
        stopActionPerformed(evt);
      }
    });
    taskMenu.add(stop);

    setDefaultCloseOperation(javax.swing.WindowConstants.DISPOSE_ON_CLOSE);
    setLocationByPlatform(true);
    setModal(true);

    taskTable.setAutoCreateRowSorter(true);
    taskTable.setModel(new javax.swing.table.DefaultTableModel(
      new Object [][] {

      },
      new String [] {
        "Manager", "byte/s"
      }
    ) {
      Class[] types = new Class [] {
        java.lang.String.class, java.lang.String.class
      };
      boolean[] canEdit = new boolean [] {
        false, false
      };

      public Class getColumnClass(int columnIndex) {
        return types [columnIndex];
      }

      public boolean isCellEditable(int rowIndex, int columnIndex) {
        return canEdit [columnIndex];
      }
    });
    taskTable.setComponentPopupMenu(taskMenu);
    jScrollPane1.setViewportView(taskTable);

    getContentPane().add(jScrollPane1, java.awt.BorderLayout.CENTER);

    pack();
  }// </editor-fold>//GEN-END:initComponents

    private void stopActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_stopActionPerformed
      int idx = this.taskTable.getSelectedRow();
      if(idx == -1) return;
      
      Object o = ((DefaultTableModel)this.taskTable.getModel()).getValueAt(idx, 0);
      System.out.println(o);
    }//GEN-LAST:event_stopActionPerformed

    /**
    * @param args the command line arguments
    */
    public static void main(String args[]) {
        java.awt.EventQueue.invokeLater(new Runnable() {
            public void run() {
                TaskManager dialog = new TaskManager(new javax.swing.JFrame(), true);
                dialog.addWindowListener(new java.awt.event.WindowAdapter() {
                    public void windowClosing(java.awt.event.WindowEvent e) {
                        System.exit(0);
                    }
                });
                dialog.setVisible(true);
            }
        });
    }

  // Variables declaration - do not modify//GEN-BEGIN:variables
  private javax.swing.JScrollPane jScrollPane1;
  private javax.swing.JMenuItem stop;
  private javax.swing.JPopupMenu taskMenu;
  private javax.swing.JTable taskTable;
  // End of variables declaration//GEN-END:variables

}
