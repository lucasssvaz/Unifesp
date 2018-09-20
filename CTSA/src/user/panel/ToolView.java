/**
 * Questa classe gestisce la parte che mostra il risultato, all'utente
 * @author Giacomo
 */
package user.panel;

import java.awt.GridLayout;
import java.util.Observable;
/**
 * Questa classe ha il compito di mostrare quello che viene richiesto dall'utente
 * @author Giacomo
 */
import java.util.Observer;

import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JTextArea;
import javax.swing.ScrollPaneConstants;

import utils.Separatore;
import utils.SeparatoreMeno;

public class ToolView extends JPanel implements Observer {
	
	/**
	 * 
	 */
	private static final long serialVersionUID = 1L;
	private Separatore separatore;
	private JTextArea area;
	
	public ToolView(SeparatoreMeno separatoreMeno){
		this.separatore = separatoreMeno;
		separatoreMeno.addObserver(this);
		area = new JTextArea();
		setLayout(new GridLayout(1,1));
		JScrollPane bar = new JScrollPane(area);
		bar.setHorizontalScrollBarPolicy(ScrollPaneConstants.HORIZONTAL_SCROLLBAR_ALWAYS);
		add(bar);
	}
	
	@Override
	public void update(Observable o, Object arg) {
		area.append(separatore.getRisultato());
		area.append("\n");
	}
}
