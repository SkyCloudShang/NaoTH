package de.naoth.rc.components.preferences;

import java.io.File;
import javax.swing.filechooser.FileNameExtensionFilter;

/**
 *
 * @author Philipp Strobel <philippstrobel@posteo.de>
 */
public class PreferencesJar extends javax.swing.JPanel implements PreferencesField {

    /**
     * Creates new form JarConfig
     * @param name
     * @param value
     */
    public PreferencesJar(String name, String value) {
        initComponents();
        
        jarName.setText(name);
        jarValue.setText(value);
    }
    
    @Override
    public String getPreferenceName() {
        return jarName.getText();
    }
    
    @Override
    public String getPreferenceValue() {
        return jarValue.getText();
    }
    
    @Override
    public void setPreferenceValue(String value) {
        jarValue.setText(value);
    }

    /**
     * This method is called from within the constructor to initialize the form. WARNING: Do NOT
     * modify this code. The content of this method is always regenerated by the Form Editor.
     */
    @SuppressWarnings("unchecked")
    // <editor-fold defaultstate="collapsed" desc="Generated Code">//GEN-BEGIN:initComponents
    private void initComponents() {

        jarFileChooser = new javax.swing.JFileChooser();
        jarName = new javax.swing.JLabel();
        jarValue = new javax.swing.JTextField();
        jarBrowse = new javax.swing.JButton();

        jarFileChooser.setAcceptAllFileFilterUsed(false);
        jarFileChooser.setDialogTitle("Select NaoSCP jar file");
        jarFileChooser.setFileFilter(new FileNameExtensionFilter("JAR file", "jar"));

        setMaximumSize(new java.awt.Dimension(2147483647, 40));
        setLayout(new java.awt.BorderLayout());

        jarName.setText("Name");
        add(jarName, java.awt.BorderLayout.NORTH);

        jarValue.setEditable(false);
        jarValue.setText("Value");
        jarValue.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                jarValueActionPerformed(evt);
            }
        });
        add(jarValue, java.awt.BorderLayout.CENTER);

        jarBrowse.setText("Browse");
        jarBrowse.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                jarBrowseActionPerformed(evt);
            }
        });
        add(jarBrowse, java.awt.BorderLayout.LINE_END);
    }// </editor-fold>//GEN-END:initComponents

    private void jarValueActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_jarValueActionPerformed
        // TODO add your handling code here:
    }//GEN-LAST:event_jarValueActionPerformed

    private void jarBrowseActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_jarBrowseActionPerformed
        File currentJar = new File(jarValue.getText());
        if(currentJar.exists()) {
            jarFileChooser.setCurrentDirectory(currentJar);
        }
        
        if(jarFileChooser.showOpenDialog(this) ==  javax.swing.JFileChooser.APPROVE_OPTION) {
            File jar = jarFileChooser.getSelectedFile();
            if(jar.isFile() && jar.exists() && jar.getName().endsWith(".jar")) {
                jarValue.setText(jar.getAbsolutePath());
            }
        }
    }//GEN-LAST:event_jarBrowseActionPerformed


    // Variables declaration - do not modify//GEN-BEGIN:variables
    private javax.swing.JButton jarBrowse;
    private javax.swing.JFileChooser jarFileChooser;
    private javax.swing.JLabel jarName;
    private javax.swing.JTextField jarValue;
    // End of variables declaration//GEN-END:variables
}
