public class Word implements Comparable{
	
	public String str;
	public int count;
	
	public Word(String inStr){
		count = 0;
		str = inStr;
	}
	
	public void addCount(){
		count++;
	}
	
	public int getCount(){
		return count;
	}
	
	public String getString(){
		return str;
	}
	
@Override
	public int compareTo(Object w){
		int tmp = (count >= ((Word)w).getCount()) ? ((count > ((Word)w).getCount()) ? 1 : 0) : -1;
		return tmp;
	}
}
