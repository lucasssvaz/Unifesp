/**
 * Quesya classe ha la responsabilità di gestire la modifica di una stringa, togliendo il segno meno,
 * come richiesto dalla libreria IRemote per Arduino
 * @author Giacomo
 */
package utils;

import java.util.ArrayList;
import java.util.Observable;
import java.util.Observer;
import java.util.StringTokenizer;

public class SeparatoreMeno extends Observable implements Separatore {
	
	private String risultato;
	private static String carattereSeparatore = "-";
	private int indiceSegnale = 0;
	
	/**
	 * Questo metodo permette di estrarre da una stringa, il segnale RAW da far
	 * trasmettere da Arduino
	 * @param string
	 */
	public void estratiSegnaliValido(String string) {
		StringTokenizer stringTokenizer = new StringTokenizer(string);
		ArrayList<String> arrayList = new ArrayList<>();
		while(stringTokenizer.hasMoreElements()){
			String parziale = stringTokenizer.nextToken();
			if(parziale.contains(carattereSeparatore)){
				arrayList.add(parziale.replace(carattereSeparatore, ""));
			}else{
				arrayList.add(parziale);
			}
		}
		impostaRisultato(arrayList);
	}

	public void impostaRisultato(ArrayList<String> arrayList) {
		risultato = "";
		risultato+="unsigned signal_"+indiceSegnale+"[] ={";
		// Il ciclo parte da 3, perché prima c'è Raw(...);
		for (int i = 3; i < arrayList.size()-1; i++) {
			risultato += arrayList.get(i)+",";
		}
		risultato+=arrayList.get(arrayList.size()-1);
		risultato+="};";
		indiceSegnale++;
	}
	
	public String getRisultato() {
		return risultato;
	}

	public void setRisultato(String risultato) {
		this.risultato = risultato;
	}	
	
	@Override
	public synchronized void addObserver(Observer o) {
		// TODO Auto-generated method stub
		super.addObserver(o);
	}
	
	public void update(){
		setChanged();
		notifyObservers();
	}
}
