import java.util.*;
import java.util.Collections;

public class gradbot{
	
	public static String inStr;
	public static ArrayList<Word> wordList;
	public static String[] strWords;
	
	public static void main(String[] args){
		System.out.printf("- Program Start -\n");
		System.out.printf("Usage: enter string for analysis:\n");
		
		wordList = new ArrayList<Word>();
		wordList.add(new Word("<placeHolder>"));
		
		try{
			while(true){
				Scanner sc = new Scanner(System.in);
				inStr = sc.nextLine();
		
				cleanString(inStr);
				countString();
				orderList();
				
				for(int i=1; i<wordList.size(); i++)
					System.out.printf(">%s, %d\n", wordList.get(i).getString(), wordList.get(i).getCount());
				
			}
		} catch(Exception e) {
			e.printStackTrace();
		}
	}
	
	//remove punctuation and capitalization
	public static void cleanString(String s){
		System.out.printf(">cleanString called\n");
		strWords = inStr.replaceAll("\\p{P}", "").toLowerCase().split("\\s+");
		/*for(int i=0; i<strWords.length; i++){
			System.out.println(strWords[i]);
		}*/
	}
	
	public static void countString(){
		System.out.printf(">countString called\n");
		System.out.printf(">strWords length = %d\n", strWords.length);
		//iterate through strWords (array of new word Strings)
		for(int i=0; i<strWords.length; i++){
			//iterate through wordList (arrayList of recorded words)
			for(int j=0; j<wordList.size(); j++){
				//System.out.printf(">%d\n", strWords[i].compareTo(wordList.get(j).getString()) );
				if(strWords[i].compareTo(wordList.get(j).getString())==0){
					wordList.get(j).addCount();
					//System.out.printf("added count to %s\n", wordList.get(j).getString() );
					break;
				}
				if(j == wordList.size()-1) {
					wordList.add(new Word(strWords[i]));
					wordList.get(j+1).addCount();
					break;
				}
			}
		}
	}
	
	public static void orderList(){
		Collections.sort(wordList);
	}
}
