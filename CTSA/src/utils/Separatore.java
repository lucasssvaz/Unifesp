package utils;

public interface Separatore {
	/**
	 * Questo metodo permette di formattare in modo corretto un segnale
	 * @param string
	 */
	public void estratiSegnaliValido(String string);
	/**
	 * Questo metodo permette di recuperare il risultato, dopo l'operazione di estrazione del
	 * risltato
	 * @return
	 */
	public String getRisultato();

}