package String;

import java.util.Scanner;

public class Ex6 {

	public static void main(String[] args) {
		Scanner Input = new Scanner(System.in);
		System.out.println("Text: ");
		String Str = Input.nextLine();
		System.out.println("Search Word: ");
		String Sch = Input.nextLine();
		System.out.println(Str.indexOf(Sch));
	}

}
