package String;

public class Ex2 {

	public static void main(String[] args) {
		String Str = "Java";
		
		for (int i=0;i<4;i++) {
			for (int j=0;j<=i;j++) {
				System.out.print(Str.charAt(j));
			}
			System.out.println();
		}
		
		for (int i=2;i>=0;i--) {
			for (int j=0;j<=i;j++) {
				System.out.print(Str.charAt(j));
			}
			System.out.println();
		}
		
		

	}

}
