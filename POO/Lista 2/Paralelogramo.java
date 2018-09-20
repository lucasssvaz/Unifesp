package lista2;

public class Paralelogramo extends Figura {
	double a,b,t;
	
	Paralelogramo(){
		a=3;
		b=5;
		t=Math.toRadians(45);
	}
	
	Paralelogramo(double x, double y,double z){
		a=x;
		b=y;
		t=Math.toRadians(z);
	}
	
	double getArea() {
		return a*b*Math.sin(t);
	}
	
	public String toString() {
		return Double.toString(getArea());
	}
}
