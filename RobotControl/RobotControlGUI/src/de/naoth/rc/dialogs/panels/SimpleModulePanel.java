/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

package de.naoth.rc.dialogs.panels;

import de.naoth.rc.dataformats.ModuleConfiguration;
import java.awt.Color;
import java.awt.Component;
import java.awt.Dimension;
import java.awt.Graphics;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import javax.swing.JButton;

/**
 *
 * @author gxy
 */
public class SimpleModulePanel extends javax.swing.JPanel {

    /**
     * Creates new form SimpleModulePanel
     */
    public SimpleModulePanel() {
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

        spRequire = new javax.swing.JScrollPane();
        requirePanel = new javax.swing.JPanel();
        nodePanel = new javax.swing.JPanel();
        spProvide = new javax.swing.JScrollPane();
        providePanel = new javax.swing.JPanel();

        setLayout(new java.awt.GridLayout(1, 3));

        spRequire.setBorder(null);

        requirePanel.setLayout(new javax.swing.BoxLayout(requirePanel, javax.swing.BoxLayout.PAGE_AXIS));
        spRequire.setViewportView(requirePanel);

        add(spRequire);

        nodePanel.setBackground(new java.awt.Color(204, 204, 255));
        nodePanel.setLayout(new javax.swing.BoxLayout(nodePanel, javax.swing.BoxLayout.PAGE_AXIS));
        add(nodePanel);

        spProvide.setBorder(null);

        providePanel.setLayout(new javax.swing.BoxLayout(providePanel, javax.swing.BoxLayout.PAGE_AXIS));
        spProvide.setViewportView(providePanel);

        add(spProvide);
    }// </editor-fold>//GEN-END:initComponents

  public static final Color moduleColor = new Color(160,160,255);
  public static final Color representationColor = new Color(255,192,128);  

    
  public void setNode(ModuleConfiguration.Node node) 
  {
    requirePanel.removeAll();
    nodePanel.removeAll();
    providePanel.removeAll();

    if(node != null)
    {
        nodePanel.add(createButton(node));
        for(ModuleConfiguration.Node n: node.require) {
            requirePanel.add(createButton(n));
        }
        for(ModuleConfiguration.Node n: node.provide) {
            providePanel.add(createButton(n));
        }
    }
    
    this.revalidate();
    this.repaint();
  }
      
  private JButton createButton(final ModuleConfiguration.Node n) 
  {
    ColorButton b = new ColorButton(n.getName());
    b.addActionListener(new ActionListener() {
        @Override
        public void actionPerformed(ActionEvent ae) {
            setNode(n);
        }
    });
    if(n.getType() == ModuleConfiguration.NodeType.Represenation) {
        //b.setForeground(Color.red);
        b.setBackground(representationColor);
        //b.setBorder(new LineBorder(Color.black, 1));
    } else if(n.getType() == ModuleConfiguration.NodeType.Module) {
        b.setBackground(moduleColor);
        //b.setBorder(new LineBorder(Color.black, 1));
        if(!n.isEnabled()) {
            b.setForeground(Color.gray);
        }
    }

    b.setMaximumSize(new Dimension(1000,1000));
    b.setAlignmentX(Component.CENTER_ALIGNMENT);
    b.setAlignmentY(Component.CENTER_ALIGNMENT);
    return b;
  }
  
  
  class ColorButton extends JButton 
  {
        private Color backgroundColor;
        private Color hoverBackgroundColor;
        private Color pressedBackgroundColor;

        public ColorButton() {
            this(null);
        }

        public ColorButton(String text) {
            super(text);
        }

        @Override
        protected void paintComponent(Graphics g) {
            if (getModel().isPressed()) {
                super.setBackground(pressedBackgroundColor);
            } else if (getModel().isRollover()) {
                super.setBackground(hoverBackgroundColor);
            } else {
                super.setBackground(backgroundColor);
            }
            super.paintComponent(g);
        }
        
        @Override
        public void setBackground(Color color) {
            this.backgroundColor = color;
            this.hoverBackgroundColor = color.brighter();
            this.pressedBackgroundColor = color.darker();
            super.setBackground(color);
        }
    }

    // Variables declaration - do not modify//GEN-BEGIN:variables
    private javax.swing.JPanel nodePanel;
    private javax.swing.JPanel providePanel;
    private javax.swing.JPanel requirePanel;
    private javax.swing.JScrollPane spProvide;
    private javax.swing.JScrollPane spRequire;
    // End of variables declaration//GEN-END:variables
}
