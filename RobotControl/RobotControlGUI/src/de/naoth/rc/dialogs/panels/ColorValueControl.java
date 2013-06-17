/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package de.naoth.rc.dialogs.panels;

import java.beans.PropertyChangeListener;

/**
 *
 * @author claas
 */
public class ColorValueControl extends javax.swing.JPanel //implements PropertyChangeListener 
{
  private boolean sliderChanged = false;
  private boolean constructing = true;
  private String coloredObjectName;
  
  /**
   * Creates new form ColorValueControl
   */
  public ColorValueControl(String coloredObjectName, String propertyName, PropertyChangeListener listener) 
  {
    initComponents();   
    
    this.coloredObjectName = coloredObjectName;
    this.jLabel.setText(propertyName);
    this.addPropertyChangeListener(listener);
  }

  public void setValue(int value)
  {
    sliderChanged = false;
    this.jSpinner.setValue(value);
  }
  
  public int getValue()
  {
    return (Integer) this.jSpinner.getValue();
  }
  
  @Override
  public void setEnabled(boolean value) 
  {
    this.jSpinner.setEnabled(value);
    this.jSlider.setEnabled(value);
  }
    
  
  /**
   * This method is called from within the constructor to initialize the form.
   * WARNING: Do NOT modify this code. The content of this method is always
   * regenerated by the Form Editor.
   */
  @SuppressWarnings("unchecked")
    // <editor-fold defaultstate="collapsed" desc="Generated Code">//GEN-BEGIN:initComponents
    private void initComponents() {

        jLabel = new javax.swing.JLabel();
        jSlider = new javax.swing.JSlider();
        jSpinner = new javax.swing.JSpinner();

        setMaximumSize(new java.awt.Dimension(240, 53));
        setMinimumSize(new java.awt.Dimension(240, 53));

        jLabel.setText("jLabel1");

        jSlider.setMajorTickSpacing(10);
        jSlider.setMaximum(255);
        jSlider.setMinorTickSpacing(1);
        jSlider.setPaintTicks(true);
        jSlider.setMaximumSize(new java.awt.Dimension(200, 27));
        jSlider.setMinimumSize(new java.awt.Dimension(200, 27));
        jSlider.addMouseListener(new java.awt.event.MouseAdapter() {
            public void mouseReleased(java.awt.event.MouseEvent evt) {
                jSliderMouseReleased(evt);
            }
        });
        jSlider.addMouseMotionListener(new java.awt.event.MouseMotionAdapter() {
            public void mouseDragged(java.awt.event.MouseEvent evt) {
                jSliderMouseDragged(evt);
            }
        });
        jSlider.addPropertyChangeListener(new java.beans.PropertyChangeListener() {
            public void propertyChange(java.beans.PropertyChangeEvent evt) {
                jSliderPropertyChange(evt);
            }
        });

        jSpinner.setModel(new javax.swing.SpinnerNumberModel(0, 0, 255, 1));
        jSpinner.addMouseListener(new java.awt.event.MouseAdapter() {
            public void mouseClicked(java.awt.event.MouseEvent evt) {
                jSpinnerMouseClicked(evt);
            }
            public void mouseReleased(java.awt.event.MouseEvent evt) {
                jSpinnerMouseReleased(evt);
            }
        });
        jSpinner.addChangeListener(new javax.swing.event.ChangeListener() {
            public void stateChanged(javax.swing.event.ChangeEvent evt) {
                jSpinnerStateChanged(evt);
            }
        });
        jSpinner.addPropertyChangeListener(new java.beans.PropertyChangeListener() {
            public void propertyChange(java.beans.PropertyChangeEvent evt) {
                jSpinnerPropertyChange(evt);
            }
        });

        javax.swing.GroupLayout layout = new javax.swing.GroupLayout(this);
        this.setLayout(layout);
        layout.setHorizontalGroup(
            layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(layout.createSequentialGroup()
                .addComponent(jLabel, javax.swing.GroupLayout.PREFERRED_SIZE, 165, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addComponent(jSpinner, javax.swing.GroupLayout.PREFERRED_SIZE, 63, javax.swing.GroupLayout.PREFERRED_SIZE))
            .addComponent(jSlider, javax.swing.GroupLayout.PREFERRED_SIZE, 240, javax.swing.GroupLayout.PREFERRED_SIZE)
        );
        layout.setVerticalGroup(
            layout.createParallelGroup(javax.swing.GroupLayout.Alignment.TRAILING)
            .addGroup(layout.createSequentialGroup()
                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                    .addComponent(jSpinner, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                    .addComponent(jLabel))
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addComponent(jSlider, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE))
        );
    }// </editor-fold>//GEN-END:initComponents

  private void jSliderPropertyChange(java.beans.PropertyChangeEvent evt) {//GEN-FIRST:event_jSliderPropertyChange
  }//GEN-LAST:event_jSliderPropertyChange

  private void jSpinnerPropertyChange(java.beans.PropertyChangeEvent evt) {//GEN-FIRST:event_jSpinnerPropertyChange
   if(!sliderChanged && !constructing)
    {
      firePropertyChange("ColorCalibrationTool:" + coloredObjectName + ":changed", null, (Integer) this.jSpinner.getValue());
      this.jSlider.setValue((Integer) this.jSpinner.getValue());
    }
    else
    {
      sliderChanged = false;
    }
    constructing = false;                                    
  }//GEN-LAST:event_jSpinnerPropertyChange

  private void jSpinnerMouseClicked(java.awt.event.MouseEvent evt) {//GEN-FIRST:event_jSpinnerMouseClicked
               
  }//GEN-LAST:event_jSpinnerMouseClicked

  private void jSliderMouseReleased(java.awt.event.MouseEvent evt) {//GEN-FIRST:event_jSliderMouseReleased
    this.jSpinner.setValue(this.jSlider.getValue());
    firePropertyChange("ColorCalibrationTool:" + coloredObjectName + ":changed", null, this.jSlider.getValue());
    sliderChanged = true;
  }//GEN-LAST:event_jSliderMouseReleased

  private void jSpinnerMouseReleased(java.awt.event.MouseEvent evt) {//GEN-FIRST:event_jSpinnerMouseReleased
     
  }//GEN-LAST:event_jSpinnerMouseReleased

  private void jSpinnerStateChanged(javax.swing.event.ChangeEvent evt) {//GEN-FIRST:event_jSpinnerStateChanged
   if(!sliderChanged && !constructing)
    {
      firePropertyChange("ColorCalibrationTool:" + coloredObjectName + ":changed", null, (Integer) this.jSpinner.getValue());
      this.jSlider.setValue((Integer) this.jSpinner.getValue());
    }
    else
    {
      sliderChanged = false;
    }
    constructing = false;
  }//GEN-LAST:event_jSpinnerStateChanged

  private void jSliderMouseDragged(java.awt.event.MouseEvent evt) {//GEN-FIRST:event_jSliderMouseDragged
    this.jSpinner.setValue(this.jSlider.getValue());
    firePropertyChange("ColorCalibrationTool:" + coloredObjectName + ":changed", null, this.jSlider.getValue());
    sliderChanged = true;
  }//GEN-LAST:event_jSliderMouseDragged

    // Variables declaration - do not modify//GEN-BEGIN:variables
    private javax.swing.JLabel jLabel;
    private javax.swing.JSlider jSlider;
    private javax.swing.JSpinner jSpinner;
    // End of variables declaration//GEN-END:variables

//  @Override
//  public void propertyChange(PropertyChangeEvent evt) 
//  {
//    
//  }
}