/**
 * Questa classe ha la responsabilità di gestire il Menu dell'applicazione
 * @author Giacomo
 */
package user.panel;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.JMenu;
import javax.swing.JMenuBar;
import javax.swing.JMenuItem;

public class ToolMenu extends JMenuBar {
	
	/**
	 * 
	 */
	private static final long serialVersionUID = 1L;

	public ToolMenu(){
		JMenu menu = new JMenu("File");
		JMenuItem menuItem = new JMenuItem("Seleziona File");
		menu.add(menuItem);
		add(menu);
		menuItem.addActionListener(new ActionListener() {
			
			@Override
			public void actionPerformed(ActionEvent e) {
				//TODO
				// Occorre aggiungere la funzionalità di aprire da file
			}
		});
	}
}
