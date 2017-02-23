/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package naoscp.tools.usb;

import java.io.BufferedReader;
import java.io.IOException;
import java.util.LinkedList;
import java.util.List;
import java.util.logging.Level;
import java.util.logging.Logger;
import java.util.regex.Matcher;
import java.util.regex.Pattern;
import naoscp.components.USBPanel;
import static naoscp.tools.usb.USBStorageDeviceFinder.executeCommand;

/**
 *
 * @author Robert Martin
 */
public class WindowsUSBStorageDeviceFinder extends USBStorageDeviceFinder {
    
    private static final String DEVICE_LIST_CMD = "wmic logicaldisk where drivetype=2 get deviceid,volumename";
    private final static Pattern DEVICE_LIST_PATTERN = Pattern.compile("(\\w:)\\s+(.+)");
    
    @Override
    public List<USBStorageDevice> getUSBStorageDevices() {
       
        BufferedReader output = executeCommand(DEVICE_LIST_CMD);
        LinkedList<USBStorageDevice> usbDevices = new LinkedList<>();
        String outputLine;

        try {
            while ((outputLine = output.readLine()) != null) {               
                
                Matcher matcher = DEVICE_LIST_PATTERN.matcher(outputLine);

                if (matcher.matches()) {
                    String mountPoint = matcher.group(1);
                    String name = matcher.group(2);
                    
                    usbDevices.add(new USBStorageDevice(name, mountPoint));
                }
                

            }
        } catch (IOException ex) {
            Logger.getLogger(USBPanel.class.getName()).log(Level.SEVERE, null, ex);
        }
        
        return usbDevices;
    }
    
}
