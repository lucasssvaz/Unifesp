package lista2;

public class Triangulo extends Figura {
	double a,b,c;
	
	Triangulo(){
		a=3;
		b=4;
		c=5;
	}
	
	Triangulo(double x, double y, double z){
		a=x;
		b=y;
		c=z;
	}

	double getArea(){
		double p = (a+b+c)/2;
		return Math.sqrt(p*(p-a)*(p-b)*(p-c));
	}
	
}
