/**
 * Questa classe contiene i metodi per la gestione dell'interazione tra utente e applicazione
 * @author Giacomo
 */
package user.panel;

import java.awt.BorderLayout;
import java.awt.GridLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.JButton;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JTextField;
import javax.swing.ScrollPaneConstants;

import utils.SeparatoreMeno;

public class ToolControlPanel extends JPanel {
	
	/**
	 * 
	 */
	private static final long serialVersionUID = 1L;

	public ToolControlPanel(final SeparatoreMeno separatoreMeno){
		final JTextField field = new JTextField();
		JScrollPane bar = new JScrollPane(field);
		bar.setHorizontalScrollBarPolicy(ScrollPaneConstants.HORIZONTAL_SCROLLBAR_ALWAYS);
		add(bar);
		setLayout(new GridLayout(2,1));
		JButton button = new JButton("Invio");
		button.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				separatoreMeno.estratiSegnaliValido(field.getText());
				separatoreMeno.update();
			}
		});
		add(button,BorderLayout.SOUTH);
	}
}
