package lista2;

public class Main {

	public static void main(String[] args) {
		
		Ramo ramo = new Ramo();
		Gato gato = new Gato();
		Mortal mortal = new Mortal();
		
		mortal.mata();
		mortal.isVivo();
		mortal.toString();
		
		while (gato.isVivo() != false) {
			gato.mata();
			gato.isVivo();
		}

		ramo.mata();
		
	}

}
