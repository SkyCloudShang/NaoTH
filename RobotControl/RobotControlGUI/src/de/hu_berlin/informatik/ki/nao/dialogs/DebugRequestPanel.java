/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * DebugRequestPanel.java
 *
 * Created on 29.10.2010, 15:15:34
 */
package de.hu_berlin.informatik.ki.nao.dialogs;

import de.hu_berlin.informatik.ki.nao.Dialog;
import de.hu_berlin.informatik.ki.nao.checkboxtree.CheckboxTree;
import de.hu_berlin.informatik.ki.nao.checkboxtree.SelectableTreeNode;
import java.awt.BorderLayout;
import java.awt.Color;
import javax.swing.JPanel;
import javax.swing.tree.DefaultTreeModel;
import net.xeoh.plugins.base.annotations.PluginImplementation;
import net.xeoh.plugins.base.annotations.events.Init;

/**
 *
 * @author thomas
 */
@PluginImplementation
public class DebugRequestPanel extends javax.swing.JPanel implements Dialog
{

  private CheckboxTree debugRequestTree;

  /** Creates new form DebugRequestPanel */
  public DebugRequestPanel()
  {
    initComponents();
  }

  /** This method is called from within the constructor to
   * initialize the form.
   * WARNING: Do NOT modify this code. The content of this method is
   * always regenerated by the Form Editor.
   */
  @SuppressWarnings("unchecked")
  // <editor-fold defaultstate="collapsed" desc="Generated Code">//GEN-BEGIN:initComponents
  private void initComponents() {

    setLayout(new java.awt.BorderLayout());
  }// </editor-fold>//GEN-END:initComponents
  // Variables declaration - do not modify//GEN-BEGIN:variables
  // End of variables declaration//GEN-END:variables

  @Init
  public void init()
  {
    debugRequestTree = new CheckboxTree();

    debugRequestTree.insertPath("trajectory/mypath/debug_request1");
    debugRequestTree.insertPath("trajectory/mypath/debug_request2");
    debugRequestTree.insertPath("debug/mypath/debug_request1");

    add(debugRequestTree, BorderLayout.CENTER);
  }

  @Override
  public JPanel getPanel()
  {
    return this;
  }

  @Override
  public void dispose()
  {
    remove(debugRequestTree);
  }
}