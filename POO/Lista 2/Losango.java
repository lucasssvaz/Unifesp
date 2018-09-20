package lista2;

public class Losango extends Paralelogramo {
	double D, d;
	
	Losango(){
		D = 5;
		d = 4;
	}
	
	Losango(double x, double y){
		D = x;
		d = y;
	}
	
	double getArea() {
		return d*D/2;
	}
}
