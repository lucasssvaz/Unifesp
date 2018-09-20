package lista2;

public class Retangulo extends Figura {
	double a,b;
	
	Retangulo(){
		a=10;
		b=5;
	}

	Retangulo(double x, double y){
		a=x;
		b=y;
	}
	
	double getArea() {
		return this.a*this.b;
	}
	
	public String toString() {
		return Double.toString(getArea());
	}
}
