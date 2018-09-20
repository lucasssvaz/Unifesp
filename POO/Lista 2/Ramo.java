package lista2;

public class Ramo extends Mortal {
	boolean vivo = true;
	private Ramo left;
	private Ramo right;
	
	Ramo(){
		vivo = true;
	}
	
	void mata() {
		while (this != null) {
			vivo = false;
			left.mata();
			right.mata();
		}
	}
}
