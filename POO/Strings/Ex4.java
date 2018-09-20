package String;

public class Ex4 {

	public static void main(String[] args) {
		String Str = "Java";
		
		for (int i=1;i<5;i++) {
			System.out.println(Str.substring(0, i));
		}
		
		for (int i=3;i>=1;i--) {
			System.out.println(Str.substring(0, i));
		}
		
		

	}

}