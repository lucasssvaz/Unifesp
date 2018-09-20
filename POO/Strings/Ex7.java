package String;

import java.util.Scanner;

public class Ex7 {

	public static void main(String[] args) {
		Scanner Input = new Scanner(System.in);
		System.out.println("Name: ");
		String Str = Input.nextLine();
		String[] Split = Str.split(" ");
		String Out = Split[0] + " ";
		for (int i = 1; i < Split.length-1 ; i++) {
			Out += Split[i].charAt(0)+". ";
		}
		Out += Split[Split.length-1];
		System.out.println(Out);
	}

}
