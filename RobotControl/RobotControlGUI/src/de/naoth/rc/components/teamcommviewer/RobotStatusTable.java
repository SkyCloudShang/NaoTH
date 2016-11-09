
package de.naoth.rc.components.teamcommviewer;

import java.awt.Component;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.util.Arrays;
import java.util.Enumeration;
import java.util.List;
import java.util.Vector;
import java.util.function.Function;
import java.util.stream.Collectors;
import javax.swing.DefaultRowSorter;
import javax.swing.JButton;
import javax.swing.JComponent;
import javax.swing.JOptionPane;
import javax.swing.JTable;
import javax.swing.table.AbstractTableModel;
import javax.swing.table.DefaultTableCellRenderer;
import javax.swing.table.DefaultTableColumnModel;
import javax.swing.table.TableCellRenderer;
import javax.swing.table.TableColumn;
import javax.swing.table.TableColumnModel;

/**
 * @author Philipp Strobel <philippstrobel@posteo.de>
 */
public class RobotStatusTable extends javax.swing.JPanel {
    
    /**
     * Container class, which summarize the data to adding the column.
     */
    public static class Column {
        public Column(String name, 
                      Class<?> type, 
                      Function<RobotStatus, Object> value,
                      TableCellRenderer renderer,
                      boolean sortable,
                      boolean showbydefault,
                      boolean editable
        ){
            this.name = name;
            this.type = type;
            this.value = value;
            this.renderer = renderer;
            this.sortable = sortable;
            this.showbydefault = showbydefault;
            this.editable = editable;
        }
        public String name;
        public Class<?> type;
        public Function<RobotStatus, Object> value;
        public TableCellRenderer renderer;
        public boolean sortable;
        public boolean showbydefault;
        public boolean editable;
        
        public String toString() {
            return name;
        }
    }
    
    /**
     * A list of all available columns.
     */
    public final List<Column> ALL_COLUMNS = Arrays.asList(
        new Column(
            "#TN", // name/heading
            Byte.class, // column type
            (RobotStatus r)->r.teamNum, // column value
            new CellRenderer(), // column renderer
            true, // sortable
            true, // show by default?
            false
        ),
        new Column("#PN",Byte.class,(RobotStatus r) -> r.playerNum,null,true,true,false),
        new Column("IP",String.class,(RobotStatus r) -> r.ipAddress,null,true,true,false),
        new Column("msg/s", Double.class, (RobotStatus r) -> r.msgPerSecond, new PingRenderer(), true,true,false),
        new Column("BallAge (s)", Float.class, (RobotStatus r) -> r.ballAge, null, true,true,false),
        new Column("State", String.class, (RobotStatus r) -> (r.isDead ? "DEAD" : (r.fallen == 1 ? "FALLEN" : "NOT FALLEN")), null, true,true,false),
        new Column("Temperature", Float.class, (RobotStatus r) -> r.temperature, new TemperatureRenderer(), true,true,false),
        new Column("Battery", Float.class, (RobotStatus r) -> r.batteryCharge, new BatteryRenderer(), true,true,false),
        new Column("TimeToBall", Float.class, (RobotStatus r) -> r.timeToBall, null, true,false,false),
        new Column("wantToBeStriker", Boolean.class, (RobotStatus r) -> r.wantsToBeStriker, null, true,false,false),
        new Column("wasStriker", Boolean.class, (RobotStatus r) -> r.wasStriker, null, true,false,false),
        new Column("isPenalized", Boolean.class, (RobotStatus r) -> r.isPenalized, null, true,false,false),
        new Column("show on field", Boolean.class, (RobotStatus r) -> r.showOnField, null, true,false,true),
        new Column("", RobotStatus.class, (RobotStatus r) -> r, new ButtonRenderer(), false,true,false)
    );
    
    /**
     * Creates new form RobotStatusTable
     */
    public RobotStatusTable() {
        initComponents();
        // the button column is added by default
        addColumn("");
        // sets the mouse listener for the button column (connect button)
        table.addMouseListener(new JTableButtonMouseListener(table));
        ((JComponent) table.getDefaultRenderer(Boolean.class)).setOpaque(true);
    }

    /**
     * This method is called from within the constructor to initialize the form.
     * WARNING: Do NOT modify this code. The content of this method is always
     * regenerated by the Form Editor.
     */
    @SuppressWarnings("unchecked")
    // <editor-fold defaultstate="collapsed" desc="Generated Code">//GEN-BEGIN:initComponents
    private void initComponents() {

        scrollPane = new javax.swing.JScrollPane();
        table = new javax.swing.JTable();

        table.setAutoCreateRowSorter(true);
        table.setModel(new RobotTableModel());
        table.setAutoResizeMode(javax.swing.JTable.AUTO_RESIZE_OFF);
        scrollPane.setViewportView(table);
        table.setColumnModel(new DefaultTableColumnModel());

        javax.swing.GroupLayout layout = new javax.swing.GroupLayout(this);
        this.setLayout(layout);
        layout.setHorizontalGroup(
            layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addComponent(scrollPane, javax.swing.GroupLayout.DEFAULT_SIZE, 400, Short.MAX_VALUE)
        );
        layout.setVerticalGroup(
            layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addComponent(scrollPane, javax.swing.GroupLayout.DEFAULT_SIZE, 300, Short.MAX_VALUE)
        );
    }// </editor-fold>//GEN-END:initComponents

    private class RobotTableModel extends AbstractTableModel implements RobotStatusListener {
        private final Vector<RobotStatus> robots = new Vector<>();
        
        public RobotTableModel() {
        }
        
        public void addRobot(RobotStatus robot) {
            robots.add(robot);
            robot.addListener(this);
            this.fireTableRowsInserted(robots.size()-1, robots.size()-1);
        }
        
        public RobotStatus getRobot(int rowIndex) {
            return robots.get(rowIndex);
        }
        
        public void removeAll() {
            int lastRow = robots.size()-1;
            robots.clear();
            if(lastRow >= 0) {
                this.fireTableRowsDeleted(0, lastRow);
            }
        }

        @Override
        public int getColumnCount() {
            return ALL_COLUMNS.size();
        }
        
        @Override
        public int getRowCount() {
            return robots == null ? 0 : robots.size();
        }

        @Override
        public String getColumnName(int columnIndex) {
            return ALL_COLUMNS.get(columnIndex).name;
        }

        @Override
        public Class<?> getColumnClass(int columnIndex) {
            return ALL_COLUMNS.get(columnIndex).type;
        }
        
        @Override
        public Object getValueAt(int rowIndex, int columnIndex) {
            RobotStatus robot = robots.get(rowIndex);
            return ALL_COLUMNS.get(columnIndex).value.apply(robot);
        }

        @Override
        public void setValueAt(Object aValue, int rowIndex, int columnIndex) {
            if(ALL_COLUMNS.get(columnIndex).editable) {
                robots.get(rowIndex).showOnField = (boolean)aValue;
            }
        }

        /**
         * Notifies the table, that some cell data changed.
         * RobotStatus calls this method (listener).
         */
        @Override
        public void statusChanged(RobotStatus changed) {
            int idx = robots.indexOf(changed);
            this.fireTableRowsUpdated(idx, idx);
        }

        @Override
        public boolean isCellEditable(int row, int columnIndex) {
            return ALL_COLUMNS.get(columnIndex).editable;
        }
    }
    
    /**
     * Adds a robot to the table.
     * @param robot 
     */
    public void addRobot(RobotStatus robot) {
        ((RobotTableModel)this.table.getModel()).addRobot(robot);
    }
    
    /**
     * Removes all robots from the table.
     */
    public void removeAll() {
        ((RobotTableModel)this.table.getModel()).removeAll();
    }
    
    /**
     * Adds a column by name (heading) to the table.
     * @param name name of the column
     */
    public void addColumn(String name) {
        // tries to find the (predefined) column
        List<Column> column = ALL_COLUMNS.stream().filter((Column c)->(c.name!=null&&c.name.equals(name))).collect(Collectors.toList());
        // check if name is in the columns-list
        if(column.isEmpty()) {
            return;
        }
        // gets the column definition
        Column col = column.get(0);
        // creates the new table column and sets the attributes
        TableColumn tc = new TableColumn();
        tc.setModelIndex(ALL_COLUMNS.indexOf(col)); // corresponding model index!
        tc.setIdentifier(col.name);
        tc.setHeaderValue(col.name);
        if(col.renderer != null) {
            tc.setCellRenderer(col.renderer);
        }
        // set sortable attribute; referenced via model index
        ((DefaultRowSorter)table.getRowSorter()).setSortable(ALL_COLUMNS.indexOf(col), col.sortable);
        
        TableColumnModel tcm = table.getColumnModel();
        tcm.addColumn(tc);
        
        // move column to "correct" index
        int columnIndex = ALL_COLUMNS.indexOf(col);
        Enumeration<TableColumn> tableColumns = tcm.getColumns();
        while(tableColumns.hasMoreElements()) {
            TableColumn tableColumn = tableColumns.nextElement();
            if(tableColumn.getModelIndex() > columnIndex) {
                tcm.moveColumn(tcm.getColumnCount()-1, tcm.getColumnIndex(tableColumn.getIdentifier()));
                break;
            }
        }
        
        // makes the button column the last column
        tcm.moveColumn(tcm.getColumnIndex(""), tcm.getColumnCount()-1);
    }
    
    /**
     * Removes the column.
     * @param name the heading/name of the column
     */
    public void removeColumn(String name) {
        TableColumnModel tcm = table.getColumnModel();
        tcm.removeColumn(tcm.getColumn(tcm.getColumnIndex(name)));
    }
    
    /**
     * Renders the table cell with the background color of the robot.
     */
    private class CellRenderer extends DefaultTableCellRenderer {

        @Override
        public Component getTableCellRendererComponent(JTable table, Object value, boolean isSelected, boolean hasFocus, int row, int column) {
            // if the table is sorted, we need to convert the ui row index to the (internal) model index to get the color of the "correct" robot
            this.setBackground(((RobotTableModel)table.getModel()).getRobot(table.getRowSorter().convertRowIndexToModel(row)).robotColor);
            return super.getTableCellRendererComponent(table, value, isSelected, hasFocus, row, column);
        }
    }
    
    /**
     * Renders the table cell for the battery value.
     */
    private class BatteryRenderer extends DefaultTableCellRenderer {

        @Override
        public Component getTableCellRendererComponent(JTable table, Object value, boolean isSelected, boolean hasFocus, int row, int column) {
            double bat = ((float) value)/100.0;
            /*
            // value-based color
            Color c2 = RobotStatus.COLOR_INFO;
            Color c1 = RobotStatus.COLOR_DANGER;
            int red = (int) (c2.getRed() * bat + c1.getRed() * (1 - bat));
            int green = (int) (c2.getGreen() * bat + c1.getGreen() * (1 - bat));
            int blue = (int) (c2.getBlue() * bat + c1.getBlue() * (1 - bat));
            this.setBackground(new Color(red, green, blue));
            */
            if (bat <= 0.3) {
                this.setBackground(RobotStatus.COLOR_DANGER);
            } else if (bat <= 0.6) {
                this.setBackground(RobotStatus.COLOR_WARNING);
            } else {
                this.setBackground(RobotStatus.COLOR_INFO);
            }
            
            return super.getTableCellRendererComponent(table, bat == -1 ? "?" : String.format("%3.1f%%", value), isSelected, hasFocus, row, column);
        }
    }
    
    /**
     * Renders the table cell for the temperature value.
     */
    private class TemperatureRenderer extends DefaultTableCellRenderer {

        @Override
        public Component getTableCellRendererComponent(JTable table, Object value, boolean isSelected, boolean hasFocus, int row, int column) {
            float temp = (float) value;
            
            if (temp >= 75.0) { // 75 °C
                this.setBackground(RobotStatus.COLOR_DANGER);
            } else if (temp >= 60.0) { // 60 °C
                this.setBackground(RobotStatus.COLOR_WARNING);
            } else {
                this.setBackground(null);
            }

            return super.getTableCellRendererComponent(table, temp == -1 ? "?" : String.format(" %3.1f °C", value), isSelected, hasFocus, row, column);
        }
    }
    
    /**
     * Renders the table cell for the msg/s value.
     */
    private class PingRenderer extends DefaultTableCellRenderer {

        @Override
        public Component getTableCellRendererComponent(JTable table, Object value, boolean isSelected, boolean hasFocus, int row, int column) {
            return super.getTableCellRendererComponent(table, String.format("%4.2f", value), isSelected, hasFocus, row, column);
        }
    }
    
    /**
     * Renders the table cell for the connect button.
     */
    class ButtonRenderer extends JButton implements TableCellRenderer {
        
        public ButtonRenderer() {
            setOpaque(true);
        }

        @Override
        public Component getTableCellRendererComponent(JTable table, Object value, boolean isSelected, boolean hasFocus, int row, int column) {
            setEnabled(!((RobotStatus)value).isConnected);
            setText("Connect" + (!((RobotStatus)value).isConnected?"":"ed"));
            return this;
        }
    }
    
    /**
     * Implements a simple mouse/button listener for the connect button.
     */
    private static class JTableButtonMouseListener extends MouseAdapter {
		private final JTable table;
		
		public JTableButtonMouseListener(JTable table) {
			this.table = table;
		}

		public void mouseClicked(MouseEvent e) {
			int column = table.getColumnModel().getColumnIndexAtX(e.getX());
			int row    = e.getY()/table.getRowHeight(); 

			if (row < table.getRowCount() && row >= 0 && column < table.getColumnCount() && column >= 0) {
                // only for column 8 (connect button) and if it's enabled
                if(table.getCellRenderer(row, column) instanceof ButtonRenderer && ((ButtonRenderer)table.getCellRenderer(row, column)).isEnabled()) {
                    // let RobotStatus connect to robot (MessageServer)
                    if(!((RobotTableModel)table.getModel()).getRobot(table.getRowSorter().convertRowIndexToModel(row)).connect()) {
                        // show dialog on error
                        JOptionPane.showMessageDialog(null, "Couldn't connect!", "Couldn't connect", JOptionPane.WARNING_MESSAGE);
                    }
                }
			}
		}
	}

    // Variables declaration - do not modify//GEN-BEGIN:variables
    private javax.swing.JScrollPane scrollPane;
    private javax.swing.JTable table;
    // End of variables declaration//GEN-END:variables
}
