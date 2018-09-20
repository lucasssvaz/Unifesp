/**
 * Questo test verifica il corretto funzionamento di generazione di un segnale, nel formato corretto
 * @author Giacomo
 */
package tests;

import utils.SeparatoreMeno;

public class Tests01 {
	public static void main(String[] args) {
		String string = "Raw (150): -5320 3000 -3000 3000 -4400 550 -1600 600 -550 550 -1650 550 -550 550 -550 550 -1650 550 -550 550 -1650 500 -550 550 -1650 550 -550 550 -500 600 -500 600 -550 550 -550 550 -1650 500 -550 550 -600 500 -1700 500 -550 550 -550 550 -550 550 -600 500 -550 550 -550 550 -550 550 -550 550 -1650 550 -1650 550 -1650 500 -1650 550 -1650 550 -550 550 -550 550 -550 550 -550 550 -1650 550 -1650 550 -500 550 -550 550 -1700 500 -1650 550 -550 550 -500 600 -550 550 -550 550 -550 550 -550 550 -550 550 -1650 500 -1700 500 -550 550 -550 550 -550 550 -550 550 -550 550 -600 500 -550 550 -550 550 -550 550 -550 550 -550 550 -550 550 -550 550 -550 550 -1650 550 -500 550 -1700 500 -550 550 -550 550 -550 550 -1650 550 ";
		SeparatoreMeno separatore = new SeparatoreMeno();
		separatore.estratiSegnaliValido(string);
		System.out.println(separatore.getRisultato());
		}
}
