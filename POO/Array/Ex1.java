import java.util.Scanner;
import java.util.Arrays;

public class Ex1 {

	public static void main(String[] args) {
		int[100] Vet;
		int i = 0;
		
		Scanner IO = new Scanner(System.in);

		do{
			Vet[i] = Integer.parseInt(IO.nextLine());
			i++;
		} while (i<100 && Vet[i-1]!=0);
		
		Arrays.sort(Vet);	
	
	}

}