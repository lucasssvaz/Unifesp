package String;

import java.util.Scanner;

public class Ex1 {

	public static void main(String[] args) {
		String Str;
		
		System.out.println("Text: ");
		Scanner IO = new Scanner(System.in);
		Str = IO.nextLine();
		System.out.println("Lenght: "+Str.length());
	}

}
