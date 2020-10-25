/**
 * Simple class that represents a row and a column, with simple getters and setters for both
 * @author Osvaldo
 */

public class Space {
	int col, row;
	
	//testing the space function
	public static void main(String[] args) {
		Space one = new Space(3, 4);
		Space two = new Space(1, 6);
		two.setRow(two.getRow()+1);
		two.setCol(two.getCol()-1);
		System.out.println("one r: " + one.getRow() + ", c: " + one.getCol());
		System.out.println("two r: " + two.getRow() + ", c: " + two.getCol());
	}

	public void setCol(int c) {
		col = c;
	}

	public void setRow(int r) {
		row = r;
	}

	/**
	 * The constructor that will set up the object to store a row and column
	 * 
	 * @param row
	 * @param col
	 */
	public Space(int r, int c) {
		row = r;
		col = c;		
	}
	
	public int getRow() {
		return row;
	}
	
	public int getCol() {
		return col;
	}
	
	
}