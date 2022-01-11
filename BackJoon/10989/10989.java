import java.io.*;
import java.util.StringTokenizer;

public class Main {
   public static int[] num;
   
   public static void main(String[] args) throws IOException {
      BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
      BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(System.out));
      
      String tmp = br.readLine();
      int nr_number = Integer.parseInt(tmp);
      num = new int[10001];
      
      for(int i=0; i < nr_number; i++) {
    	  tmp = br.readLine();
    	  int tmpp = Integer.parseInt(tmp);
    	  num[tmpp]++;
      }
      
      for(int i = 1; i < 10001; i++) {
    	  if(num[i] == 0) {
    		  continue;
    	  }
    	  for(int j=0; j <num[i]; j++) {
    		  bw.write(Integer.toString(i) + "\n");
    	  }
      }
      
      
      bw.flush();
      bw.close();
      br.close();
   }
   
}
