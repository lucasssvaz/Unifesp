package String;

import java.util.Scanner;

public class Ex3 {

	public static void main(String[] args) {
		Scanner Input = new Scanner(System.in);
		System.out.println("Text Uppercase: ");
		String Str = Input.nextLine();
		System.out.println(Str.toLowerCase());
		System.out.println("Text Lowercase: ");
		Str = Input.nextLine();
		System.out.println(Str.toUpperCase());
		
		

	}

}
