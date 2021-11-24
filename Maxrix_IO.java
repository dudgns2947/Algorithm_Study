import java.io.*;
import java.util.StringTokenizer;

public class main {
	static int map[][];
	
	public static void main(String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st;
		st = new StringTokenizer(br.readLine());	
		int nr_maxrix = Integer.parseInt(st.nextToken());
		System.out.println();
		for(int n = 0; n < nr_maxrix; n++) {
		st = new StringTokenizer(br.readLine());	
		int row = Integer.parseInt(st.nextToken());
		int column = Integer.parseInt(st.nextToken());

		map = new int[column][row];
				
		for(int i = 0; i < column; i++) {
			st = new StringTokenizer(br.readLine());
			for(int j = 0; j < row; j++) {
				map[i][j] = Integer.parseInt(st.nextToken());
			}
		}		
		
		//출력
		for(int i = 0; i < column; i++) {
			for(int j = 0; j < row; j++) {
				System.out.print(map[i][j]);
			}
			System.out.println();
		 }
		System.out.println();
	    }
	}
}
