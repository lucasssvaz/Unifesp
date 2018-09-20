/**
 * Questo è il codice eseguibile del pannello
 * @author Giacomo
 */
package user.panel;

import java.awt.GridLayout;

import javax.swing.JFrame;
import javax.swing.JPanel;

import utils.SeparatoreMeno;

public class UserPanelMain {
	public static void main(String[] args) {
		SeparatoreMeno separatore = new SeparatoreMeno();
		ToolMenu menuBar = new ToolMenu();
		ToolControlPanel controlPanel = new ToolControlPanel(separatore);
		ToolView view = new ToolView(separatore);
		JFrame jFrame = new JFrame("Arduino AC Tool");
		jFrame.setSize(500,500);
		jFrame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		jFrame.setJMenuBar(menuBar);
		JPanel mainPanel = new JPanel();
		mainPanel.setLayout(new GridLayout(2,1));
		mainPanel.add(controlPanel);
		mainPanel.add(view);
		jFrame.getContentPane().add(mainPanel);
		jFrame.setVisible(true);
	}
}
