package String;

import java.util.Scanner;
import java.lang.*;

public class Ex8 {

	public static void main(String[] args) {
		String Str = "";
		Scanner Input = new Scanner(System.in);
		do {
			System.out.println("Word:");
			Str = Input.nextLine();
			System.out.println(Str.charAt(0) + " " + Str.charAt(Str.length()-1));
		} while ( Character.toLowerCase(Str.charAt(0)) != 'f' );
	}

}
