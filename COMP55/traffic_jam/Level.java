import java.util.*;


public class Level {	
	private Board board;
	private int numRows, numCols;
	private Space exit = new Space(1, 4);
	
	//default constructor
	public Level() {
		this(0, 0);
	}
	
	//general constructor
	public Level(int nRows, int nCols) {
		numRows = nRows;
		numCols = nCols;
	}
	
	//getter for exit tile 
	public Space getExitTile() {
		return exit;
	}
	
	//gets the vehicles on the board
	public ArrayList<Vehicle> getVehiclesOnBoard() {
		return board.getAllVehicles();
	}
	
	//gets vehicle at a specific board space
	public Vehicle getVehicleAt(Space s) {
		return board.getVehicle(s);
	}
	
	//checks if the player has won, if the car has reached the exit tile
	public boolean win() {
		if(board.getVehicle(exit).getVehicleType() == VehicleType.MYCAR) {
			return true;
		}
		return false;
	}
	
	//moves the vehicle in the level created
	public boolean moveVehicle(Space location, int numSpaces) {
		if(board.moveNumSpaces(location, numSpaces)) {
			return true;
		}
		return false;
	}
 	
	//sets up the single level
	public void setUpLevel() {
		board.clearBoard();
		
		board.addVehicle(VehicleType.TRUCK, 0, 0, 3, false);
		board.addVehicle(VehicleType.AUTO, 1, 4, 2, true);
		board.addVehicle(VehicleType.AUTO, 3, 1, 2, false);
		board.addVehicle(VehicleType.MYCAR, 1, 0, 2, false);
	}
	
	//returns number of columns
	public int getColumns() {
		return numCols;
	}
	
	//returns number of rows
	public int getRows() {
		return numRows;
	}
	
	//Methods already defined for you
	/**
	 * generates the string representation of the level, including the row and column headers to make it look like
	 * a table
	 * 
	 * @return the string representation
	 */
	public String toString() {
		String result = generateColHeader(getColumns());
		result+=addRowHeader(board.toString());
		return result;
	}
	
	/**
	 * This method will add the row information
	 * needed to the board and is used by the toString method
	 * 
	 * @param origBoard the original board without the header information
	 * @return the board with the header information
	 */
	private String addRowHeader(String origBoard) {
		String result = "";
		String[] elems = origBoard.split("\n");
		for(int i = 0; i < elems.length; i++) {
			result += (char)('A' + i) + "|" + elems[i] + "\n"; 
		}
		return result;
	}
	
	/**
	 * This one is responsible for making the row of column numbers at the top and is used by the toString method
	 * 
	 * @param cols the number of columns in the board
	 * @return if the # of columns is five then it would return "12345\n-----\n"
	 */
	private String generateColHeader(int cols) {
		String result = "  ";
		for(int i = 1; i <= cols; i++) {
			result+=i;
		}
		result+="\n  ";
		for(int i = 0; i < cols; i++) {
			result+="-";
		}
		result+="\n";
		return result;
	}
}
