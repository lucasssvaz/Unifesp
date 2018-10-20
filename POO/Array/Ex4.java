public class Ex4 {

	public int maxV (int[] vet){
		int max = -999999999;
		for(int i = 0;i<vet.length;i++){
			if (vet[i] > max){
				max = vet[i];
			}
		}
		return max;
	}

}