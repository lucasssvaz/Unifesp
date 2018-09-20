package lista2;

public class TrianguloRetangulo extends Triangulo {
	double b,h;
	TrianguloRetangulo(){
		b=3;
		h=4;
	}
	
	TrianguloRetangulo(double x, double y){
		b=x;
		h=y;
	}
	
	double getArea(){
		return b*h/2;
	}
	
	
}
