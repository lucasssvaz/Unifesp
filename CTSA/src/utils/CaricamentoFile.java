/**
 * Questa classe contiene il metodo per impostare il nome di un file
 * da aprire
 * @author Giacomo
 */
package utils;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;

public class CaricamentoFile {
	private static BufferedReader reader;
	private ArrayList<String> list;
	/**
	 * Questo metodo permette di impostare il nome del file 
	 * da leggere
	 * @param string
	 */
	public void setFileName(String string){
		try {
			reader = new BufferedReader(new FileReader(new File(string)));
			String line = reader.readLine();
			list = new ArrayList<>();
			while(line!=null){
				list.add(line);
				line = reader.readLine();
			}
			reader.close();
		} catch (FileNotFoundException e) {
			e.printStackTrace();
		} catch (IOException e) {
			e.printStackTrace();
		}
	}
	public ArrayList<String> getList() {
		return list;
	}
	public void setList(ArrayList<String> list) {
		this.list = list;
	}
}
