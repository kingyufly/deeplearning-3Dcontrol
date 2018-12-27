import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.util.ArrayList;

public class FileOp {

	/**
	 * Write the content to the file
	 * 
	 * @param contents
	 * 			The content that want to write to the file
	 * @param fileName
	 * 			The file that will be processed
	 * @param flag
	 * 			True: Continue write at the end of the file
	 * 			False: Overwrite the file
	 */

	public void writeFile(String contents, String fileName, boolean flag) {
		try {
			FileWriter fileWriter = new FileWriter(fileName, flag);
			BufferedWriter bufferedWriter = new BufferedWriter(fileWriter);
			bufferedWriter.write(contents);
			bufferedWriter.flush();
			bufferedWriter.close();
			fileWriter.close();
		} catch (IOException e) {
			e.printStackTrace();
		}
	}

	/**
	 * Read all the information in file
	 * 
	 * @param fileName
	 * 			The file that will be processed
	 * @return Return all the information in the file in an arraylist
	 */

	public ArrayList<String> readFile(String fileName) {
		ArrayList<String> contents = new ArrayList<String>();
		try {
			FileReader fileReader = new FileReader(fileName);
			BufferedReader bufferedReader = new BufferedReader(fileReader);
			String str = bufferedReader.readLine();
			while (str != null) {
				contents.add(str);
				str = bufferedReader.readLine();
			}
			bufferedReader.close();
			fileReader.close();
		} catch (IOException e) {
			e.printStackTrace();
		}
		return contents;
	}
}
