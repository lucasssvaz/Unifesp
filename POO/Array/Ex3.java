public class Ex3 {

	public void Funcionario (Funcionario[] vet, int anos){
		for(int i = 0;i<vet.length;i++){
			if (vet[i].getAnosNaEmpresa() > anos){
				System.out.println("Nome: " + vet[i].getNome() + ", Sobrenome: " + vet[i].getSobrenome() + ", Salario: " + Double.parseDouble(vet[i].getSalarioHora()));
			}
		}
	}

}