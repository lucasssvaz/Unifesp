package lista2;

public class Gato extends Mortal {
	boolean vivo = true;
	private int i = 7;
	
	Gato(){
		vivo = true;
	}
	
	void mata() {
		i--;
		if (i == 0) {
			vivo = false;
		}
	}
}
