public class Ex2 {

	public double media (double[] vet){
		double sum = 0;
		for(int i = 0;i<vet.length;i++){
			sum += vet[i];
		}
		return sum/vet.length;
	}

}