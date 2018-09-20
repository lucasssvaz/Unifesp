package lista2;

public class Mortal {
	private boolean vivo = true;
	
	Mortal(){
		vivo = true;
	}
	
	boolean isVivo() {
		return vivo;
	}
		 
	void mata() {
		vivo = false;
	}
	
	public String toString() {
		return Boolean.toString(vivo);
	}

}
