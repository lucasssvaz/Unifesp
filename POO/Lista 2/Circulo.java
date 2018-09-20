package lista2;

public class Circulo extends Figura {
	double raio;
	
	Circulo(){
		raio = 5;
	}
	
	Circulo(double x){
		raio = x;
	}
	
	double getArea(){
		return Math.PI*raio*raio;
	}
	
	public String toString() {
		return Double.toString(this.getArea());
	}

}
