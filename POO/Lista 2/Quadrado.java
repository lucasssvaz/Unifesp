package lista2;

public class Quadrado extends Retangulo {
	double l;
	
	Quadrado(){
		l = 5;
	}
	
	double getArea() {
		return l*l;
	}
}
